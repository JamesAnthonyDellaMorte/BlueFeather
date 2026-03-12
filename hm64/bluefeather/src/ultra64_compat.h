// ultra64_compat.h - Additional compatibility for HM64 on PC
#ifndef _ULTRA64_COMPAT_H_
#define _ULTRA64_COMPAT_H_

#include <stdint.h>

// Use libultraship's base types
#include <libultraship/libultra.h>

// N64 memory alignment
#define ALIGNED(x) __attribute__((aligned(x)))

// N64 segment mapping macros
#ifndef OS_K0_TO_PHYSICAL
#define OS_K0_TO_PHYSICAL(addr) ((uintptr_t)(addr))
#endif
#ifndef OS_PHYSICAL_TO_K0
#define OS_PHYSICAL_TO_K0(addr) ((void*)(addr))
#endif

#ifndef gSPDisplayList
#define gSPDisplayList __gSPDisplayList
#endif

#ifndef gSPSegment
#define gSPSegment __gSPSegment
#endif

#ifndef gSPVertex
#define gSPVertex __gSPVertex
#endif

// Additional function declarations that HM64 needs
// but might not be in libultraship

#ifdef __cplusplus
extern "C" {
#endif

// Assertion — undefine the macOS SDK macro so we can declare the N64 shim
#ifdef __assert
#undef __assert
#endif
void __assert(const char* exp, const char* file, s32 line);

// Virtual/physical address conversion (if not provided)
uintptr_t osVirtualToPhysical(void* addr);
void osStopThread(OSThread* thread);

// Additional N64 types that HM64 expects (only if not in libultraship)
#ifndef _OSTHREAD_H_
typedef u32 OSError;
#endif

extern s32 osTvType;
extern OSViMode osViModeTable[56];
#ifdef __cplusplus
}
#endif

#endif // _ULTRA64_COMPAT_H_
