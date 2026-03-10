// nuGfx Compatibility Layer for HM64 PC Port
// Maps N64 nuGfx functions to libultraship

#include "nugfx.h"
#include "hm64_host_rom.h"
#include <libultraship/libultra.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <ship/Context.h>

#include <cstring>
#include <iostream>
#include <memory>
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
bool FlushPendingDisplayLists() {
    if (s_pendingDisplayLists.empty()) {
        return true;
    }

    auto context = Ship::Context::GetInstance();
    auto window = context ? std::dynamic_pointer_cast<Fast::Fast3dWindow>(context->GetWindow()) : nullptr;
    if (!window) {
        s_pendingDisplayLists.clear();
        s_pendingSwap = false;
        nuGfxTaskSpool = 0;
        return false;
    }

    std::vector<Gfx> wrapperDisplayList;
    wrapperDisplayList.reserve(s_pendingDisplayLists.size() + 1);

    Gfx* dl = wrapperDisplayList.data();
    (void)dl;

    for (Gfx* taskDisplayList : s_pendingDisplayLists) {
        wrapperDisplayList.push_back({});
    }
    wrapperDisplayList.push_back({});

    dl = wrapperDisplayList.data();
    for (Gfx* taskDisplayList : s_pendingDisplayLists) {
        gSPDisplayList(dl++, OS_K0_TO_PHYSICAL(taskDisplayList));
    }
    gSPEndDisplayList(dl++);

    const std::unordered_map<Mtx*, MtxF> noMtxReplacements;
    const bool drewFrame = window->DrawAndRunGraphicsCommands(wrapperDisplayList.data(), noMtxReplacements);

    if (s_pendingSwap) {
        nuGfxSwapCfb(nuGfxCfb_ptr);
    }

    s_pendingDisplayLists.clear();
    s_pendingSwap = false;
    nuGfxTaskSpool = 0;
    return drewFrame;
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
    
    // Fix for ld_symbols: if romAddr is a PC pointer (not in N64 ROM range),
    // it might be &symbol where symbol is a pointer variable. Dereference it.
    if (romAddr < 0x01000000 || romAddr > 0x02000000) {
        // This looks like a PC pointer. Check if it's a pointer to a ROM address.
        // Valid PC pointers on ARM64 macOS are typically 0x100000000+
        if (romAddr > 0x100000000ULL) {
            // Try to dereference as a pointer to a pointer
            uintptr_t dereferenced = *(uintptr_t*)romAddr;
            if (debugCount < 25) {
                std::cerr << "[HM64_ROM_DEBUG] Dereferencing 0x" << std::hex << romAddr 
                          << " -> 0x" << dereferenced << std::dec << std::endl;
            }
            // Verify the dereferenced value looks like a ROM address
            if (dereferenced >= 0x01000000 && dereferenced <= 0x02000000) {
                romAddr = dereferenced;
                if (debugCount < 25) {
                    std::cerr << "[HM64_ROM_DEBUG] Using dereferenced: 0x" << std::hex << romAddr << std::dec << std::endl;
                }
            }
        }
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
    
    if (pcBufPtr != nullptr && HM64Host_ReadRom(romAddr, pcBufPtr, size)) {
        // HM64 streams sprite and logo textures into reused RAM buffers.
        // With clean upstream libultraship we only have whole-cache invalidation.
        gfx_texture_cache_clear();
        return;
    }

    if (pcBufPtr != nullptr) {
        static int warnedCount = 0;
        if (warnedCount < 8) {
            std::cerr << "[HM64_ROM] Unmapped ROM read at 0x" << std::hex << romAddr << std::dec
                      << " for " << size << " bytes" << std::endl;
        }
        warnedCount++;
    }
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

    if (nuGfxSwapCfbFunc != nullptr && nuGfxSwapCfbFunc != nuGfxSwapCfb) {
        nuGfxSwapCfbFunc(frameBuf != nullptr ? frameBuf : nuGfxCfb_ptr);
    }
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

    if (dl != nullptr) {
        s_pendingDisplayLists.push_back(dl);
    }
    nuGfxTaskSpool = static_cast<u32>(s_pendingDisplayLists.size());

    if (flags == NU_SC_SWAPBUFFER) {
        s_pendingSwap = true;
        FlushPendingDisplayLists();
    }
}

void nuGfxTaskAllEndWait(void) {
    FlushPendingDisplayLists();
}

// Call the registered retrace callback
void nuGfxCallFunc(int frame) {
    if (nuGfxFunc) {
        nuGfxFunc(frame);
    }
}

// Check if a task is pending
int nuGfxTaskNum(void) {
    return static_cast<int>(s_pendingDisplayLists.size());
}

// Get current CFB pointer
u16* nuGfxGetCfb(void) {
    return nuGfxCfb_ptr;
}
