// ultra64_compat.cpp - Implementation of extra N64 functions for PC

#include "ultra64_compat.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

extern "C" {

s32 osTvType = OS_TV_NTSC;
OSViMode osViModeTable[56] = {};
long long int gspF3DEX2_fifoTextStart[1] = {};
long long int gspF3DEX2_fifoDataStart[1] = {};

// Assertion handler
void __assert(const char* exp, const char* file, int line) noexcept {
    std::cerr << "[ASSERT] " << exp << " at " << file << ":" << line << std::endl;
    std::abort();
}

void osStopThread(OSThread* thread) {
    (void)thread;
}

void osEPiLinkHandle(OSPiHandle* handle) {
    (void)handle;
}

s32 __osSpSetPc(u32 pc) {
    (void)pc;
    return 0;
}

} // extern "C"
