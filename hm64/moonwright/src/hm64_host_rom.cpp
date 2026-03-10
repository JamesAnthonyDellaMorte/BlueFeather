#include "hm64_host_rom.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

namespace {
struct SegmentSpec {
    uintptr_t start;
    uintptr_t end;
    const char* relativePath;
};

struct RomSegment {
    uintptr_t start;
    uintptr_t end;
    std::vector<uint8_t> bytes;
};

std::vector<RomSegment> s_segments;
std::vector<uint8_t> s_fullRom;
fs::path s_executablePath;

constexpr uintptr_t kRomSegmentAddressBase = 0x10000000;

// Keep sprite/index segments as overrides, but let cutscene bytecode come from the
// full ROM image. The extracted cutscene .bin files are not reliable runtime
// replacements for the original ROM banks in the current PC path.
constexpr std::array<SegmentSpec, 11> kIntroSegments = {{
    // Title screen assets
    { HM64_ROM_TITLE_SPRITES_TEXTURE_START, HM64_ROM_TITLE_SPRITES_TEXTURE_END,
      "sprites/overlayScreens/titleSprites/titleSpritesTexture.bin" },
    { HM64_ROM_TITLE_SPRITES_INDEX_START, HM64_ROM_TITLE_SPRITES_INDEX_END,
      "sprites/overlayScreens/titleSprites/titleSpritesAssetsIndex.bin" },
    { HM64_ROM_DIALOGUE_ICONS_TEXTURE_START, HM64_ROM_DIALOGUE_ICONS_TEXTURE_END,
      "sprites/overlayScreens/dialogueButtonIcons/dialogueButtonIconsTexture.bin" },
    { HM64_ROM_DIALOGUE_ICONS_INDEX_START, HM64_ROM_DIALOGUE_ICONS_INDEX_END,
      "sprites/overlayScreens/dialogueButtonIcons/dialogueButtonIconsAssetsIndex.bin" },
    { HM64_ROM_DOG_TEXTURE_START, HM64_ROM_DOG_TEXTURE_END,
      "sprites/entitySprites/animals/dog/dogTexture.bin" },
    { HM64_ROM_DOG_INDEX_START, HM64_ROM_DOG_INDEX_END,
      "sprites/entitySprites/animals/dog/dogAssetsIndex.bin" },
    { HM64_ROM_DOG_SHEET_START, HM64_ROM_DOG_SHEET_END,
      "sprites/entitySprites/animals/dog/dogSpritesheetIndex.bin" },
    // Opening logos and funeral intro sprite assets
    { HM64_ROM_LOGOS_TEXTURE_START, HM64_ROM_LOGOS_TEXTURE_END,
      "sprites/overlayScreens/logos/logosTexture.bin" },
    { HM64_ROM_LOGOS_INDEX_START, HM64_ROM_LOGOS_INDEX_END,
      "sprites/overlayScreens/logos/logosAssetsIndex.bin" },
    { HM64_ROM_FUNERAL_INTRO_SPRITES_TEXTURE_START, HM64_ROM_FUNERAL_INTRO_SPRITES_TEXTURE_END,
      "sprites/effects/funeralIntro/funeralIntroTexture.bin" },
    { HM64_ROM_FUNERAL_INTRO_SPRITES_INDEX_START, HM64_ROM_FUNERAL_INTRO_SPRITES_INDEX_END,
      "sprites/effects/funeralIntro/funeralIntroAssetsIndex.bin" },
}};

bool ReadFileBytes(const fs::path& path, std::vector<uint8_t>& out) {
    std::ifstream stream(path, std::ios::binary);
    if (!stream) {
        return false;
    }

    stream.seekg(0, std::ios::end);
    const std::streamsize size = stream.tellg();
    if (size < 0) {
        return false;
    }
    stream.seekg(0, std::ios::beg);

    out.resize(static_cast<size_t>(size));
    if (size == 0) {
        return true;
    }

    stream.read(reinterpret_cast<char*>(out.data()), size);
    return stream.good();
}

fs::path FindRepoFile(const char* fileName) {
    fs::path current = fs::current_path();
    while (true) {
        const fs::path candidate = current / fileName;
        if (fs::exists(candidate)) {
            return candidate;
        }

        if (current == current.root_path()) {
            break;
        }
        current = current.parent_path();
    }

    return {};
}

void AddCandidate(std::vector<fs::path>& candidates, std::unordered_set<std::string>& seen, const fs::path& path) {
    if (path.empty()) {
        return;
    }

    fs::path canonicalPath;
    try {
        canonicalPath = fs::weakly_canonical(path);
    } catch (...) {
        canonicalPath = path.lexically_normal();
    }

    if (!fs::exists(canonicalPath)) {
        return;
    }

    const std::string key = canonicalPath.string();
    if (seen.insert(key).second) {
        candidates.push_back(canonicalPath);
    }
}

void AddAncestorAssetCandidates(std::vector<fs::path>& candidates, std::unordered_set<std::string>& seen,
                                const fs::path& start) {
    if (start.empty()) {
        return;
    }

    fs::path current = start;
    while (true) {
        AddCandidate(candidates, seen, current / "build" / "assets");
        AddCandidate(candidates, seen, current / "build-debug" / "assets");
        AddCandidate(candidates, seen, current / "build-relwithdeb" / "assets");
        AddCandidate(candidates, seen, current / "hm64" / "assets");
        AddCandidate(candidates, seen, current / "assets");

        if (current == current.root_path()) {
            break;
        }
        current = current.parent_path();
    }
}

fs::path FindAssetRoot() {
    std::vector<fs::path> candidates;
    std::unordered_set<std::string> seen;

    if (!s_executablePath.empty()) {
        fs::path executableDir = s_executablePath;
        if (!fs::is_directory(executableDir)) {
            executableDir = executableDir.parent_path();
        }

        AddCandidate(candidates, seen, executableDir / ".." / "Resources" / "assets");
        AddCandidate(candidates, seen, executableDir / "assets");
        AddCandidate(candidates, seen, executableDir / ".." / "assets");
        AddAncestorAssetCandidates(candidates, seen, executableDir);
    }

    AddAncestorAssetCandidates(candidates, seen, fs::current_path());

    for (const auto& candidate : candidates) {
        return candidate;
    }

    return {};
}

bool EnsureFullRomLoaded() {
    if (!s_fullRom.empty()) {
        return true;
    }

    fs::path romPath = FindRepoFile("hm64.z64");
    if (romPath.empty()) {
        romPath = FindRepoFile("baserom.us.z64");
    }

    if (romPath.empty()) {
        std::cout << "[HM64_ROM] Full ROM image not found; segment-only reads enabled" << std::endl;
        return false;
    }

    if (!ReadFileBytes(romPath, s_fullRom)) {
        std::cerr << "[HM64_ROM] Failed to load ROM image: " << romPath << std::endl;
        return false;
    }

    std::cout << "[HM64_ROM] Loaded full ROM image from " << romPath
              << " (" << s_fullRom.size() << " bytes)" << std::endl;
    return true;
}

uintptr_t NormalizeRomAddress(uintptr_t romAddr) {
    if (romAddr >= kRomSegmentAddressBase) {
        const uintptr_t normalized = romAddr - kRomSegmentAddressBase;
        if (s_fullRom.empty() || normalized < s_fullRom.size()) {
            return normalized;
        }
    }

    return romAddr;
}
} // namespace

extern "C" void HM64Host_SetExecutablePath(const char* executablePath) {
    if (executablePath == nullptr || executablePath[0] == '\0') {
        s_executablePath.clear();
        return;
    }

    try {
        s_executablePath = fs::weakly_canonical(fs::path(executablePath));
    } catch (...) {
        s_executablePath = fs::path(executablePath).lexically_normal();
    }
}

extern "C" bool HM64Host_LoadTitleRomSegments(void) {
    s_segments.clear();

    const fs::path assetsRoot = FindAssetRoot();
    if (assetsRoot.empty()) {
        std::cerr << "[HM64_ROM] Could not locate extracted intro assets; falling back to full ROM only" << std::endl;
        return EnsureFullRomLoaded();
    }

    int loaded = 0;
    int failed = 0;

    for (const auto& spec : kIntroSegments) {
        RomSegment segment = {
            spec.start,
            spec.end,
            {},
        };

        const fs::path path = assetsRoot / spec.relativePath;
        if (!ReadFileBytes(path, segment.bytes)) {
            // Log but continue - some segments may not exist yet
            std::cout << "[HM64_ROM] Optional segment not found: " << path << std::endl;
            failed++;
            continue;
        }

        const size_t expectedSize = static_cast<size_t>(spec.end - spec.start);
        // Allow size mismatch for now during development
        if (segment.bytes.size() != expectedSize) {
            std::cout << "[HM64_ROM] Size mismatch for " << path << ": expected " << expectedSize
                      << " bytes, got " << segment.bytes.size() << " (using anyway)" << std::endl;
        }

        s_segments.push_back(std::move(segment));
        loaded++;
    }

    std::cout << "[HM64_ROM] Loaded " << loaded << " ROM segments from " << assetsRoot
              << " (" << failed << " optional segments not found)" << std::endl;
    const bool hasFullRom = EnsureFullRomLoaded();
    return loaded > 0 || hasFullRom;
}

extern "C" bool HM64Host_ReadRom(uintptr_t romAddr, void* bufPtr, u32 size) {
    if (bufPtr == nullptr || size == 0) {
        return true;
    }

    const uintptr_t normalizedRomAddr = NormalizeRomAddress(romAddr);

    const auto it = std::find_if(s_segments.begin(), s_segments.end(), [romAddr](const RomSegment& segment) {
        return romAddr >= segment.start && romAddr < segment.end;
    });

    if (it != s_segments.end()) {
        const size_t offset = static_cast<size_t>(romAddr - it->start);
        const size_t available = it->bytes.size() - offset;
        const size_t bytesToCopy = std::min<size_t>(size, available);
        std::memcpy(bufPtr, it->bytes.data() + offset, bytesToCopy);
        return bytesToCopy == size;
    }

    if ((normalizedRomAddr + static_cast<uintptr_t>(size)) <= s_fullRom.size()) {
        std::memcpy(bufPtr, s_fullRom.data() + normalizedRomAddr, size);
        return true;
    }

    if (s_fullRom.empty()) {
        EnsureFullRomLoaded();
        if ((normalizedRomAddr + static_cast<uintptr_t>(size)) <= s_fullRom.size()) {
            std::memcpy(bufPtr, s_fullRom.data() + normalizedRomAddr, size);
            return true;
        }
    }

    {
        // Only log first few unmapped reads to avoid spam
        static int unmappedCount = 0;
        if (unmappedCount < 5) {
            std::cerr << "[HM64_ROM] Unmapped ROM read at 0x" << std::hex << romAddr 
                      << std::dec << " for " << size << " bytes" << std::endl;
            unmappedCount++;
            if (unmappedCount == 5) {
                std::cerr << "[HM64_ROM] Suppressing further unmapped read messages..." << std::endl;
            }
        }
        return false;
    }
}

// Full ROM loader - delegates to segment loader for now
extern "C" bool HM64Host_LoadFullRom(void) {
    return EnsureFullRomLoaded();
}

extern "C" const uint8_t* HM64Host_GetRomPointer(uintptr_t romAddr) {
    for (auto& segment : s_segments) {
        if (romAddr >= segment.start && romAddr < segment.end) {
            size_t offset = static_cast<size_t>(romAddr - segment.start);
            return segment.bytes.data() + offset;
        }
    }
    const uintptr_t normalizedRomAddr = NormalizeRomAddress(romAddr);
    if ((normalizedRomAddr < s_fullRom.size()) ||
        (s_fullRom.empty() && EnsureFullRomLoaded() && normalizedRomAddr < s_fullRom.size())) {
        return s_fullRom.data() + normalizedRomAddr;
    }
    return nullptr;
}

extern "C" size_t HM64Host_GetRomSize(void) {
    if (!s_fullRom.empty()) {
        return s_fullRom.size();
    }
    size_t total = 0;
    for (const auto& segment : s_segments) {
        total += segment.bytes.size();
    }
    return total;
}
