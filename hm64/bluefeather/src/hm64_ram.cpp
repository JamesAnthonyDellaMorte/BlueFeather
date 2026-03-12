#include "hm64_ram.h"

#include <cstring>

// N64 has 4MB RAM (8MB with Expansion Pak)
// We need to cover the full address space up to 0x80400000
// For cutscene buffers at 0x802F4000+, we need at least 0x00400000 bytes
alignas(16) unsigned char gHM64Ram[0x00800000];

extern "C" void HM64Host_ClearRam(void) {
    std::memset(gHM64Ram, 0, sizeof(gHM64Ram));
}
