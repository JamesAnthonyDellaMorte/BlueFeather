// nuGfx Compatibility Layer for HM64 PC Port
// Maps N64 nuGfx functions to libultraship

#include "nugfx.h"
#include "buffers/buffers.h"
#include "hm64_ram.h"
#include "system/globalSprites.h"
#include <libultraship/libultra.h>
#include <fast/Fast3dWindow.h>
#include <fast/interpreter.h>
#include <spdlog/spdlog.h>
#include <ship/Context.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <ship/resource/ResourceManager.h>

#include "generated/runtime_archive_rom_table.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
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
static bool s_shuttingDown = false;

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

extern "C" {
extern u8 messageBoxTextureBuffer[0x2900];
extern u16 messageBoxPaletteBuffer[0x80];
extern AnimationFrameMetadata messageBoxAnimationFrameMetadataBuffer[0x40];
extern u32 messageBoxAnimationTextureToPaletteLookupBuffer[0x40];

extern u8 dialogueIconTextureBuffer[0x1800];
extern u16 dialogueIconPaletteBuffer[0x100];
extern u8 dialogueIconAnimationFrameMetadataBuffer[0x400];
extern u32 dialogueIconTextureToPaletteLookupBuffer[0x100];

extern u8 characterAvatarsTexture1Buffer[0x800];
extern u8 characterAvatarsTexture2Buffer[0x800];
extern u16 characterAvatarsPaletteBuffer[0x600];
extern AnimationFrameMetadata characterAvatarsAnimationMetadataBuffer[0x400];
extern u32 characterAvatarsSpritesheetIndexBuffer[0x200];
extern u32 characterAvatarsTextureToPaletteLookupBuffer[0x40];

extern u8 shadowSpriteTextureBuffer[0x500];
extern u16 shadowSpritePaletteBuffer[0x100];
extern u32 shadowSpriteSpriteToPaletteBuffer[0x100];
extern u32 shadowSpriteSpritesheetIndexBuffer[0x100];

extern u8 playerTexture1Buffer[0x3000];
extern u8 playerTexture2Buffer[0x3000];
extern u16 playerPaletteBuffer[0x2000];
extern u32 playerAnimationMetadataBuffer[0x1E00];
extern u32 playerSpritesheetIndexBuffer[0x200];
extern u32 playerTextureToPaletteLookupBuffer[0x400];

extern u8 namingScreenBuffer[0x1500];
extern u8 mapDataBuffer[0x1A000];
extern u8 spriteBuffer[0x73CC0];
extern u8 mapObjectsBuffer[0x10000];
extern u8 cutsceneBytecodeBuffer[0xB000];
extern u8 fontTextureBuffer[0xB000];
extern u16 font1PaletteBuffer[0x200];
extern u16 font2PaletteBuffer[0x200];
extern u8 textAddressesIndexBuffer[0x800];
extern u8 messageBox1TextBuffer[0x400];
extern u8 messageBox2TextBuffer[0x400];
extern u8 messageBox3TextBuffer[0x400];
extern u8 messageBox4TextBuffer[0x400];
extern u8 messageBox5TextBuffer[0x400];
extern u8 messageBox6TextBuffer[0x400];
extern u8 dialogueBytecodeBuffer[0x800];
extern u8 frameBuffer[0x70800];
}

namespace {
constexpr size_t kOtrHeaderSize = 64;
constexpr uint32_t kBlobResourceType = 0x4F424C42; // OBLB written little-endian as BLBO in files.

#define HM64_RUNTIME_OFFSET_PTR(buffer, base, addr) (reinterpret_cast<u8*>(buffer) + ((addr) - (base)))

void* ResolveRuntimeBufferAddress(uint32_t n64Addr) {
    if (n64Addr >= MESSAGE_BOX_TEXTURE_BUFFER && n64Addr < MESSAGE_BOX_PALETTE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBoxTextureBuffer, MESSAGE_BOX_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_PALETTE_BUFFER && n64Addr < MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBoxPaletteBuffer, MESSAGE_BOX_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBoxAnimationFrameMetadataBuffer, MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < DIALOGUE_ICON_TEXTURE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBoxAnimationTextureToPaletteLookupBuffer, MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= DIALOGUE_ICON_TEXTURE_BUFFER && n64Addr < DIALOGUE_ICON_PALETTE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(dialogueIconTextureBuffer, DIALOGUE_ICON_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_ICON_PALETTE_BUFFER && n64Addr < DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(dialogueIconPaletteBuffer, DIALOGUE_ICON_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(dialogueIconAnimationFrameMetadataBuffer, DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < CHARACTER_AVATAR_TEXTURE_1_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(dialogueIconTextureToPaletteLookupBuffer, DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= CHARACTER_AVATAR_TEXTURE_1_BUFFER && n64Addr < CHARACTER_AVATAR_TEXTURE_2_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(characterAvatarsTexture1Buffer, CHARACTER_AVATAR_TEXTURE_1_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_TEXTURE_2_BUFFER && n64Addr < CHARACTER_AVATAR_PALETTE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(characterAvatarsTexture2Buffer, CHARACTER_AVATAR_TEXTURE_2_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_PALETTE_BUFFER && n64Addr < CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(characterAvatarsPaletteBuffer, CHARACTER_AVATAR_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(characterAvatarsAnimationMetadataBuffer, CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER && n64Addr < CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(characterAvatarsSpritesheetIndexBuffer, CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < SHADOW_TEXTURE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(characterAvatarsTextureToPaletteLookupBuffer, CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= SHADOW_TEXTURE_BUFFER && n64Addr < SHADOW_PALETTE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(shadowSpriteTextureBuffer, SHADOW_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= SHADOW_PALETTE_BUFFER && n64Addr < SHADOW_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(shadowSpritePaletteBuffer, SHADOW_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= SHADOW_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(shadowSpriteSpriteToPaletteBuffer, SHADOW_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < PLAYER_TEXTURE_1_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(shadowSpriteSpritesheetIndexBuffer, SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= PLAYER_TEXTURE_1_BUFFER && n64Addr < PLAYER_TEXTURE_2_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(playerTexture1Buffer, PLAYER_TEXTURE_1_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_TEXTURE_2_BUFFER && n64Addr < PLAYER_PALETTE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(playerTexture2Buffer, PLAYER_TEXTURE_2_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_PALETTE_BUFFER && n64Addr < PLAYER_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(playerPaletteBuffer, PLAYER_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < PLAYER_SPRITESHEET_INDEX_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(playerAnimationMetadataBuffer, PLAYER_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_SPRITESHEET_INDEX_BUFFER && n64Addr < PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(playerSpritesheetIndexBuffer, PLAYER_SPRITESHEET_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < NAMING_SCREEN_TEXTURE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(playerTextureToPaletteLookupBuffer, PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= NAMING_SCREEN_TEXTURE_BUFFER && n64Addr < MAP_DATA_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(namingScreenBuffer, NAMING_SCREEN_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= MAP_DATA_BUFFER && n64Addr < ENTITY_VRAM_START) {
        return HM64_RUNTIME_OFFSET_PTR(mapDataBuffer, MAP_DATA_BUFFER, n64Addr);
    }
    if (n64Addr >= ENTITY_VRAM_START && n64Addr < 0x802E2CC0) {
        return HM64_RUNTIME_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, n64Addr);
    }
    if (n64Addr >= MAP_OBJECT_SLOT_1_TEXTURE_1 && n64Addr < CUTSCENE_BYTECODE_BUFFER_1) {
        return HM64_RUNTIME_OFFSET_PTR(mapObjectsBuffer, MAP_OBJECT_SLOT_1_TEXTURE_1, n64Addr);
    }
    if (n64Addr >= CUTSCENE_BYTECODE_BUFFER_1 && n64Addr < FONT_TEXTURE_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(cutsceneBytecodeBuffer, CUTSCENE_BYTECODE_BUFFER_1, n64Addr);
    }

    if (n64Addr >= FONT_TEXTURE_BUFFER && n64Addr < FONT_PALETTE_1_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(fontTextureBuffer, FONT_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= FONT_PALETTE_1_BUFFER && n64Addr < FONT_PALETTE_2_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(font1PaletteBuffer, FONT_PALETTE_1_BUFFER, n64Addr);
    }
    if (n64Addr >= FONT_PALETTE_2_BUFFER && n64Addr < TEXT_ADDRESSES_INDEX_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(font2PaletteBuffer, FONT_PALETTE_2_BUFFER, n64Addr);
    }
    if (n64Addr >= TEXT_ADDRESSES_INDEX_BUFFER && n64Addr < MESSAGE_BOX_1_TEXT_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(textAddressesIndexBuffer, TEXT_ADDRESSES_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_1_TEXT_BUFFER && n64Addr < MESSAGE_BOX_2_TEXT_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBox1TextBuffer, MESSAGE_BOX_1_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_2_TEXT_BUFFER && n64Addr < MESSAGE_BOX_3_TEXT_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBox2TextBuffer, MESSAGE_BOX_2_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_3_TEXT_BUFFER && n64Addr < MESSAGE_BOX_4_TEXT_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBox3TextBuffer, MESSAGE_BOX_3_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_4_TEXT_BUFFER && n64Addr < MESSAGE_BOX_5_TEXT_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBox4TextBuffer, MESSAGE_BOX_4_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_5_TEXT_BUFFER && n64Addr < MESSAGE_BOX_6_TEXT_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBox5TextBuffer, MESSAGE_BOX_5_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_6_TEXT_BUFFER && n64Addr < DIALOGUE_BYTECODE_INDEX_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(messageBox6TextBuffer, MESSAGE_BOX_6_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_BYTECODE_INDEX_BUFFER && n64Addr < SRAM_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(dialogueBytecodeBuffer, DIALOGUE_BYTECODE_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= SRAM_BUFFER && n64Addr < FARM_RANKINGS_BUFFER) {
        return HM64_RUNTIME_OFFSET_PTR(&sramBuffer, SRAM_BUFFER, n64Addr);
    }
    if (n64Addr >= FARM_RANKINGS_BUFFER && n64Addr < 0x8030F800) {
        return HM64_RUNTIME_OFFSET_PTR(&farmRankingsBuffer, FARM_RANKINGS_BUFFER, n64Addr);
    }
    if (n64Addr >= FRAME_BUFFER && n64Addr < (FRAME_BUFFER + sizeof(frameBuffer))) {
        return HM64_RUNTIME_OFFSET_PTR(frameBuffer, FRAME_BUFFER, n64Addr);
    }

    if (n64Addr >= HM64_RAM_BASE && n64Addr < (HM64_RAM_BASE + HM64_RAM_SIZE)) {
        return HM64_RAM_PTR(n64Addr);
    }

    return nullptr;
}

uint32_t ReadLittleU32(const std::vector<char>& buffer, size_t offset) {
    return static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset])) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 1])) << 8) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 2])) << 16) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 3])) << 24);
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
                SPDLOG_ERROR("Invalid blob payload for {}: payloadSize={} wrappedSize={}", path, payloadSize,
                             file->Buffer->size());
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
        if (romAddr < entry.Start || romAddr >= entry.End) {
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
            SPDLOG_ERROR("Archive blob size mismatch for {}: romRange=0x{:08x}-0x{:08x} blobSize={} offset={} size={}",
                         entry.Path, entry.Start, entry.End, blob->size(), offset, size);
            return false;
        }

        std::memcpy(dst, blob->data() + offset, size);

        if (!s_loggedArchivePaths.contains(entry.Path)) {
            SPDLOG_DEBUG("Serving runtime ROM reads from archive: {}", entry.Path);
            s_loggedArchivePaths.emplace(entry.Path);
        }
        return true;
    }

    return false;
}

bool FlushPendingDisplayLists() {
    if (s_shuttingDown) {
        return false;
    }

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

static void HM64_RefreshGamepadState() {
    auto context = Ship::Context::GetInstance();
    auto controlDeck = context ? context->GetControlDeck() : nullptr;
    if (controlDeck == nullptr) {
        return;
    }

    auto deviceManager = controlDeck->GetConnectedPhysicalDeviceManager();
    if (deviceManager != nullptr) {
        deviceManager->RefreshConnectedSDLGamepads();
    }

    auto controller = controlDeck->GetControllerByPort(0);
    if (controller != nullptr && controller->HasConfig() &&
        !controller->HasMappingsForPhysicalDeviceType(Ship::PhysicalDeviceType::SDLGamepad)) {
        controller->AddDefaultMappings(Ship::PhysicalDeviceType::SDLGamepad);
    }
}

// Controller data
extern "C" u8 nuContInit(void) {
    std::memset(nuContStatus, 0, sizeof(nuContStatus));
    u8 bits = 0;
    osContInit(nullptr, &bits, nuContStatus);
    HM64_RefreshGamepadState();
    nuContStatus[0].type = CONT_TYPE_NORMAL;
    nuContStatus[0].status = 0;
    nuContStatus[0].err_no = 0;
    return bits;
}

extern "C" void nuContDataGetEx(void* contData, u32 padNo) {
    std::memset(contData, 0, sizeof(NUContData));

    auto context = Ship::Context::GetInstance();
    auto controlDeck = context ? context->GetControlDeck() : nullptr;
    if (controlDeck == nullptr || padNo >= NU_CONT_MAXCONTROLLERS) {
        return;
    }

    OSContPad pads[NU_CONT_MAXCONTROLLERS] = {};
    controlDeck->WriteToPad(pads);

    NUContData* dst = static_cast<NUContData*>(contData);
    dst->button = pads[padNo].button;
    dst->stick_x = pads[padNo].stick_x;
    dst->stick_y = pads[padNo].stick_y;
}

extern "C" void nuContDataGetExAll(void* contData) {
    std::memset(contData, 0, sizeof(NUContData) * NU_CONT_MAXCONTROLLERS);

    auto context = Ship::Context::GetInstance();
    auto controlDeck = context ? context->GetControlDeck() : nullptr;
    if (controlDeck == nullptr) {
        return;
    }

    OSContPad pads[NU_CONT_MAXCONTROLLERS] = {};
    controlDeck->WriteToPad(pads);

    NUContData* dst = static_cast<NUContData*>(contData);
    for (u32 i = 0; i < NU_CONT_MAXCONTROLLERS; i++) {
        dst[i].button = pads[i].button;
        dst[i].stick_x = pads[i].stick_x;
        dst[i].stick_y = pads[i].stick_y;
    }
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

extern "C" void nuPiReadRomCompat(uintptr_t romAddr, uintptr_t bufAddr, u32 size) {
    // Translate N64 RAM address to PC pointer if needed
    void* pcBufPtr = (void*)bufAddr;
    if (bufAddr >= 0x80000000ULL && bufAddr < 0x80800000ULL) {
        pcBufPtr = ResolveRuntimeBufferAddress((u32)bufAddr);
        if (pcBufPtr == nullptr) {
            SPDLOG_ERROR("Failed to translate N64 buffer address 0x{:08x}", static_cast<uint32_t>(bufAddr));
            return;
        }
    }
    
    if (pcBufPtr == nullptr) {
        return;
    }

    if (ReadArchiveRuntimeRange(romAddr, pcBufPtr, size)) {
        return;
    }

    SPDLOG_ERROR("Missing archive-backed runtime asset for ROM range 0x{:08x} ({} bytes).",
                 static_cast<uint32_t>(romAddr), size);
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

void nuGfxShutdown(void) {
    s_shuttingDown = true;
    nuGfxDisplayOff();

    {
        std::lock_guard<std::mutex> lock(s_pendingDisplayListsMutex);
        s_pendingDisplayLists.clear();
        s_pendingSwap = false;
        s_completedSerial = s_submissionSerial;
    }
    s_pendingDisplayListsCv.notify_all();
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
    while (true) {
        uint64_t targetSerial = 0;

        {
            std::unique_lock<std::mutex> lock(s_pendingDisplayListsMutex);
            targetSerial = s_submissionSerial;

            if (targetSerial == s_completedSerial && s_pendingDisplayLists.empty()) {
                return;
            }
        }

        if (!FlushPendingDisplayLists()) {
            std::unique_lock<std::mutex> lock(s_pendingDisplayListsMutex);
            s_pendingDisplayListsCv.wait(lock, [&]() {
                return s_completedSerial >= targetSerial && s_pendingDisplayLists.empty();
            });
        }
    }
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

// Returns the logical render width scaled for the current aspect ratio
// (fixed 240 height, width adjusted for widescreen)
uint32_t BF_GetRenderWidth(void) {
    auto context = Ship::Context::GetInstance();
    auto window = context ? std::dynamic_pointer_cast<Fast::Fast3dWindow>(context->GetWindow()) : nullptr;
    if (!window) {
        return 320;
    }
    uint32_t winW = window->GetWidth();
    uint32_t winH = window->GetHeight();
    if (winH == 0) {
        return 320;
    }
    float aspect = (float)winW / (float)winH;
    return (uint32_t)(240.0f * aspect);
}
