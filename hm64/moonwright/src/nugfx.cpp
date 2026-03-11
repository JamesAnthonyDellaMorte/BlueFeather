// nuGfx Compatibility Layer for HM64 PC Port
// Maps N64 nuGfx functions to libultraship

#include "nugfx.h"
#include <libultraship/libultra.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <ship/Context.h>
#include <ship/resource/ResourceManager.h>

#include "tables/runtime_archive_rom_table.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mach-o/dyld.h>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

// Forward declarations
void nuGfxThreadStart(void);
void nuGfxTaskMgrInit(void);

// nuGfx state
static u16** s_frameBuf = NULL;
static u16* s_zBuffer = NULL;
static int s_frameBufCount = 0;
static int s_frameIndex = 0;
static std::vector<Gfx*> s_pendingDisplayLists;
static bool s_pendingSwap = false;
static std::mutex s_pendingDisplayListsMutex;
static std::condition_variable s_pendingDisplayListsCv;
static uint64_t s_submissionSerial = 0;
static uint64_t s_completedSerial = 0;

// Globals defined here
extern "C" u16** nuGfxCfb = NULL;
extern "C" u16* nuGfxCfb_ptr = NULL;
extern "C" u32 nuGfxCfbNum = 0;
extern "C" u16* nuGfxZBuffer = NULL;
extern "C" volatile u32 nuGfxTaskSpool = 0;
extern "C" u32 nuGfxDisplay = 0;
extern "C" u32 nuGfxDisplayNum = 0;
extern "C" u32 nuGfxCfbCounter = 0;
extern "C" NUUcode* nuGfxUcode = NULL;
extern "C" NUSched nusched = {};
extern "C" OSContStatus nuContStatus[NU_CONT_MAXCONTROLLERS] = {};
extern "C" NUGfxFunc nuGfxFunc = NULL;
extern "C" NUGfxSwapCfbFunc nuGfxSwapCfbFunc = NULL;
extern "C" NUGfxPreNMIFunc nuGfxPreNMIFunc = NULL;

namespace {
constexpr size_t kOtrHeaderSize = 64;
constexpr uint32_t kBlobResourceType = 0x4F424C42; // OBLB written little-endian as BLBO in files.

uint32_t ReadLittleU32(const std::vector<char>& buffer, size_t offset) {
    return static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset])) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 1])) << 8) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 2])) << 16) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 3])) << 24);
}

std::filesystem::path GetExecutablePath() {
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::vector<char> buffer(size + 1, '\0');
    if (_NSGetExecutablePath(buffer.data(), &size) != 0) {
        return {};
    }
    return std::filesystem::weakly_canonical(std::filesystem::path(buffer.data()));
}

std::shared_ptr<std::vector<char>> LoadArchiveBlob(const char* path) {
    static std::mutex s_archiveBlobCacheMutex;
    static std::unordered_map<std::string, std::shared_ptr<std::vector<char>>> s_archiveBlobCache;
    static std::unordered_set<std::string> s_archiveBlobLoadFailures;

    {
        std::lock_guard<std::mutex> lock(s_archiveBlobCacheMutex);
        auto cached = s_archiveBlobCache.find(path);
        if (cached != s_archiveBlobCache.end()) {
            return cached->second;
        }
        if (s_archiveBlobLoadFailures.contains(path)) {
            return nullptr;
        }
    }

    auto context = Ship::Context::GetInstance();
    auto resourceManager = context ? context->GetResourceManager() : nullptr;
    if (resourceManager == nullptr) {
        return nullptr;
    }

    auto file = resourceManager->LoadFileProcess(path);
    if (file == nullptr || !file->IsLoaded || file->Buffer == nullptr) {
        std::lock_guard<std::mutex> lock(s_archiveBlobCacheMutex);
        s_archiveBlobLoadFailures.emplace(path);
        return nullptr;
    }

    // Custom assets in Moonwright.o2r are exported as OTR Blob resources.
    // We need the blob payload, not the wrapped OTR file bytes.
    if (file->Buffer->size() >= (kOtrHeaderSize + sizeof(uint32_t))) {
        const uint32_t resourceType = ReadLittleU32(*file->Buffer, 4);
        if (resourceType == kBlobResourceType) {
            const uint32_t payloadSize = ReadLittleU32(*file->Buffer, kOtrHeaderSize);
            const size_t payloadOffset = kOtrHeaderSize + sizeof(uint32_t);
            if (payloadOffset <= file->Buffer->size() && payloadSize <= (file->Buffer->size() - payloadOffset)) {
                file->Buffer = std::make_shared<std::vector<char>>(file->Buffer->begin() + payloadOffset,
                                                                   file->Buffer->begin() + payloadOffset + payloadSize);
            } else {
                std::cerr << "[Moonwright] Invalid blob payload for " << path << ": payloadSize=" << payloadSize
                          << " wrappedSize=" << file->Buffer->size() << std::endl;
                std::lock_guard<std::mutex> lock(s_archiveBlobCacheMutex);
                s_archiveBlobLoadFailures.emplace(path);
                return nullptr;
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(s_archiveBlobCacheMutex);
        s_archiveBlobCache.emplace(path, file->Buffer);
    }
    return file->Buffer;
}

bool ReadArchiveRuntimeRange(uintptr_t romAddr, void* dst, size_t size) {
    static std::unordered_set<std::string> s_loggedArchivePaths;

    for (const auto& entry : kMWRuntimeArchiveRomRanges) {
        if (romAddr < entry.Start || romAddr > entry.End) {
            continue;
        }
        if (size > (entry.End - romAddr)) {
            continue;
        }

        // Moonwright [Port] Imported HM64 systems still issue ROM-style reads. Serve the
        // known runtime ranges from exported archive blobs while the game-side callers are
        // migrated to direct resource ownership.
        auto blob = LoadArchiveBlob(entry.Path);
        if (blob == nullptr) {
            continue;
        }

        const size_t offset = romAddr - entry.Start;
        if (offset > blob->size() || size > (blob->size() - offset)) {
            std::cerr << "[Moonwright] Archive blob size mismatch for " << entry.Path << ": romRange=0x" << std::hex
                      << entry.Start << "-0x" << entry.End << std::dec << " blobSize=" << blob->size()
                      << " offset=" << offset << " size=" << size << std::endl;
            return false;
        }

        std::memcpy(dst, blob->data() + offset, size);

        if (!s_loggedArchivePaths.contains(entry.Path)) {
            std::cout << "[Moonwright] Serving runtime ROM reads from archive: " << entry.Path << std::endl;
            s_loggedArchivePaths.emplace(entry.Path);
        }
        return true;
    }

    return false;
}

const std::vector<uint8_t>* GetRomImage() {
    static std::vector<uint8_t> romImage;
    static bool loaded = false;

    if (loaded) {
        return romImage.empty() ? nullptr : &romImage;
    }

    loaded = true;

    const auto executablePath = GetExecutablePath();
    const auto executableDir = executablePath.empty() ? std::filesystem::path() : executablePath.parent_path();
    const auto cwd = std::filesystem::current_path();

    const std::vector<std::filesystem::path> candidates = {
        cwd / "hm64.z64",
        cwd / "baserom.us.z64",
        executableDir / "hm64.z64",
        executableDir / "baserom.us.z64",
        executableDir / ".." / ".." / ".." / ".." / "hm64.z64",
        executableDir / ".." / ".." / ".." / ".." / "baserom.us.z64",
        executableDir / ".." / ".." / ".." / ".." / ".." / "hm64.z64",
        executableDir / ".." / ".." / ".." / ".." / ".." / "baserom.us.z64",
    };

    for (const auto& candidate : candidates) {
        std::error_code ec;
        const auto canonical = std::filesystem::weakly_canonical(candidate, ec);
        const auto path = ec ? candidate : canonical;
        if (!std::filesystem::exists(path)) {
            continue;
        }

        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file) {
            continue;
        }

        const auto size = file.tellg();
        if (size <= 0) {
            continue;
        }

        romImage.resize(static_cast<size_t>(size));
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(romImage.data()), size);
        if (!file) {
            romImage.clear();
            continue;
        }

        std::cout << "[Moonwright] Loaded ROM image from " << path << " (" << romImage.size() << " bytes)" << std::endl;
        return &romImage;
    }

    std::cerr << "[Moonwright] Failed to locate hm64.z64 or baserom.us.z64 for nuPiReadRomCompat()" << std::endl;
    return nullptr;
}

bool ReadRomRange(uintptr_t romAddr, void* dst, size_t size) {
    const auto* romImage = GetRomImage();
    if (romImage == nullptr) {
        return false;
    }

    if (romAddr > romImage->size() || size > (romImage->size() - romAddr)) {
        std::cerr << "[Moonwright] Invalid ROM read: romAddr=0x" << std::hex << romAddr << std::dec
                  << " size=" << size << " romSize=" << romImage->size() << std::endl;
        return false;
    }

    std::memcpy(dst, romImage->data() + romAddr, size);
    return true;
}

bool FlushPendingDisplayLists() {
    std::vector<Gfx*> pendingDisplayLists;
    bool pendingSwap = false;
    uint64_t completedSerial = 0;

    {
        std::lock_guard<std::mutex> lock(s_pendingDisplayListsMutex);
        if (s_pendingDisplayLists.empty()) {
            return false;
        }

        pendingDisplayLists.swap(s_pendingDisplayLists);
        pendingSwap = s_pendingSwap;
        s_pendingSwap = false;
        completedSerial = s_submissionSerial;
        nuGfxTaskSpool = 0;
    }

    auto context = Ship::Context::GetInstance();
    auto window = context ? std::dynamic_pointer_cast<Fast::Fast3dWindow>(context->GetWindow()) : nullptr;
    if (!window) {
        {
            std::lock_guard<std::mutex> lock(s_pendingDisplayListsMutex);
            s_completedSerial = completedSerial;
        }
        s_pendingDisplayListsCv.notify_all();
        return false;
    }

    std::vector<Gfx> wrapperDisplayList;
    wrapperDisplayList.reserve(pendingDisplayLists.size() + 1);

    Gfx* dl = wrapperDisplayList.data();
    (void)dl;

    for (Gfx* taskDisplayList : pendingDisplayLists) {
        wrapperDisplayList.push_back({});
    }
    wrapperDisplayList.push_back({});

    dl = wrapperDisplayList.data();
    for (Gfx* taskDisplayList : pendingDisplayLists) {
        gSPDisplayList(dl++, OS_K0_TO_PHYSICAL(taskDisplayList));
    }
    gSPEndDisplayList(dl++);

    const std::unordered_map<Mtx*, MtxF> noMtxReplacements;
    window->DrawAndRunGraphicsCommands(wrapperDisplayList.data(), noMtxReplacements);

    if (pendingSwap) {
        if (nuGfxSwapCfbFunc != nullptr) {
            nuGfxSwapCfbFunc(nuGfxCfb_ptr);
        } else {
            nuGfxSwapCfb(nuGfxCfb_ptr);
        }
    }

    {
        std::lock_guard<std::mutex> lock(s_pendingDisplayListsMutex);
        s_completedSerial = completedSerial;
    }
    s_pendingDisplayListsCv.notify_all();
    return true;
}
} // namespace

// Controller data
extern "C" u8 nuContInit(void) {
    // Pretend controller 1 is available until proper input bridging is in place.
    std::memset(nuContStatus, 0, sizeof(nuContStatus));
    return 1;
}

extern "C" void nuContDataGetEx(void* contData, u32 padNo) {
    (void)padNo;
    std::memset(contData, 0, sizeof(NUContData));
}

extern "C" void nuContDataGetExAll(void* contData) {
    std::memset(contData, 0, sizeof(NUContData) * NU_CONT_MAXCONTROLLERS);
}

extern "C" void nuContPakOpen(NUContPakFile* file, u32 contNo) {
    (void)contNo;
    if (file != nullptr) {
        std::memset(file, 0, sizeof(*file));
    }
}

extern "C" s32 nuContPakGetFree(NUContPakFile* file) {
    (void)file;
    return 0;
}

extern "C" void nuContPakCodeSet(u8* companyCode, u8* gameCode) {
    (void)companyCode;
    (void)gameCode;
}

extern "C" void nuContPakRepairId(NUContPakFile* file) {
    (void)file;
}

extern "C" void nuContPakFileOpenJis(NUContPakFile* file, u8* noteName, u8* extName, u32 mode, s32 size) {
    (void)noteName;
    (void)extName;
    (void)mode;
    (void)size;

    if (file != nullptr) {
        file->error = 0;
    }
}

extern "C" void nuContPakFileReadWriteCompat(NUContPakFile* file, s32 offset, s32 size, void* buf, u32 mode) {
    (void)offset;
    (void)size;
    (void)buf;
    (void)mode;

    if (file != nullptr) {
        file->error = 0;
    }
}

extern "C" void nuContPakFileDeleteJis(NUContPakFile* file, u8* noteName, u8* extName) {
    (void)noteName;
    (void)extName;

    if (file != nullptr) {
        file->error = 0;
    }
}

extern "C" void nuContPakFileNum(NUContPakFile* file, s32* maxFiles, s32* usedFiles) {
    (void)file;
    if (maxFiles != nullptr) {
        *maxFiles = 0;
    }
    if (usedFiles != nullptr) {
        *usedFiles = 0;
    }
}

// Forward declaration for address translation
extern "C" void* HM64_TranslateAddress(u32 n64Addr);

extern "C" void nuPiReadRomCompat(uintptr_t romAddr, uintptr_t bufAddr, u32 size) {
    // Debug: print every ROM read attempt
    static int debugCount = 0;
    if (debugCount < 20) {
        std::cerr << "[HM64_ROM_DEBUG] Read request: romAddr=0x" << std::hex << romAddr 
                  << " bufAddr=0x" << bufAddr << std::dec << " size=" << size << std::endl;
        debugCount++;
    }
    
    // Translate N64 RAM address to PC pointer if needed
    void* pcBufPtr = (void*)bufAddr;
    if (bufAddr >= 0x80000000ULL && bufAddr < 0x80800000ULL) {
        // This is an N64 RAM address - translate it
        pcBufPtr = HM64_TranslateAddress((u32)bufAddr);
        if (debugCount < 20) {
            std::cerr << "[HM64_ROM_DEBUG] Translated buffer 0x" << std::hex << bufAddr 
                      << " -> " << pcBufPtr << std::dec << std::endl;
        }
        if (pcBufPtr == nullptr) {
            std::cerr << "[HM64_ROM_ERROR] Failed to translate N64 buffer address 0x" 
                      << std::hex << bufAddr << std::dec << std::endl;
            return;
        }
    }
    
    if (pcBufPtr == nullptr) {
        return;
    }

    if (ReadArchiveRuntimeRange(romAddr, pcBufPtr, size)) {
        return;
    }

    if (ReadRomRange(romAddr, pcBufPtr, size)) {
        return;
    }

    std::cerr << "[Moonwright] Unexpected nuPiReadRom failure at runtime: 0x" << std::hex << romAddr
              << std::dec << " (" << size << " bytes)." << std::endl;
    std::abort();
}

extern "C" void nuPiReadRom2Compat(uintptr_t romAddr, uintptr_t bufAddr, u32 size) {
    nuPiReadRomCompat(romAddr, bufAddr, size);
}

// Graphics task structure
void nuGfxThreadStart(void) {
    // libultraship handles threading internally
}

void nuGfxTaskMgrInit(void) {
    // libultraship handles task management internally
}

void nuGfxSetCfb(u16** frameBuf, u32 count) {
    s_frameBuf = frameBuf;
    s_frameBufCount = static_cast<int>(count);
    s_frameIndex = 0;
    nuGfxCfb = frameBuf;
    nuGfxCfbNum = count;
    nuGfxCfb_ptr = nullptr;
    if (frameBuf != nullptr && count > 0) {
        nuGfxCfb_ptr = frameBuf[0];
    }
}

void nuGfxSetZBuffer(u16* zBuffer) {
    s_zBuffer = zBuffer;
    nuGfxZBuffer = zBuffer;
}

void nuGfxSwapCfbFuncSet(NUGfxSwapCfbFunc func) {
    nuGfxSwapCfbFunc = func;
}

void nuGfxPreNMIFuncSet(NUGfxPreNMIFunc func) {
    nuGfxPreNMIFunc = func;
}

void nuGfxFuncSet(NUGfxFunc func) {
    nuGfxFunc = func;
}

void nuGfxSwapCfb(void* frameBuf) {
    // Called when buffer swap happens
    // Advance to next framebuffer
    if (s_frameBufCount > 0) {
        s_frameIndex = (s_frameIndex + 1) % s_frameBufCount;
        nuGfxCfb_ptr = s_frameBuf[s_frameIndex];
        nuGfxCfbCounter = static_cast<u32>(s_frameIndex);
    }
    (void)frameBuf;
}

void nuGfxDisplayOn(void) {
    nuGfxDisplay = 1;
    nuGfxDisplayNum = 1;
}

void nuGfxDisplayOff(void) {
    nuGfxDisplay = 0;
    nuGfxDisplayNum = 0;
}

void nuGfxTaskStart(Gfx* dl, u32 size, u32 ucode, u32 flags) {
    (void)size;
    (void)ucode;

    {
        std::lock_guard<std::mutex> lock(s_pendingDisplayListsMutex);

        if (dl != nullptr) {
            s_pendingDisplayLists.push_back(dl);
            s_submissionSerial++;
        }

        if (flags == NU_SC_SWAPBUFFER) {
            s_pendingSwap = true;
        }

        nuGfxTaskSpool = static_cast<u32>(s_pendingDisplayLists.size());
    }

    s_pendingDisplayListsCv.notify_all();
}

void nuGfxTaskAllEndWait(void) {
    std::unique_lock<std::mutex> lock(s_pendingDisplayListsMutex);
    const uint64_t targetSerial = s_submissionSerial;

    if (targetSerial == s_completedSerial && s_pendingDisplayLists.empty()) {
        return;
    }

    s_pendingDisplayListsCv.wait(lock, [&]() {
        return s_completedSerial >= targetSerial && s_pendingDisplayLists.empty();
    });
}

// Call the registered retrace callback
void nuGfxCallFunc(int frame) {
    if (nuGfxFunc) {
        nuGfxFunc(frame);
    }
}

// Check if a task is pending
int nuGfxTaskNum(void) {
    std::lock_guard<std::mutex> lock(s_pendingDisplayListsMutex);
    return static_cast<int>(s_pendingDisplayLists.size());
}

// Get current CFB pointer
u16* nuGfxGetCfb(void) {
    return nuGfxCfb_ptr;
}

bool nuGfxProcessPendingMainThread(void) {
    return FlushPendingDisplayLists();
}
