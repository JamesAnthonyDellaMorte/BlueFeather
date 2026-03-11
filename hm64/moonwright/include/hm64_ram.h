#ifndef HM64_RAM_H
#define HM64_RAM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char gHM64Ram[0x00800000];
void HM64Host_ClearRam(void);
void* HM64_TranslateAddress(uint32_t n64Addr);

#ifdef __cplusplus
}
#endif

#define HM64_RAM_BASE 0x80000000u
#define HM64_RAM_SIZE 0x00800000u
#define HM64_RAM_PTR(addr) (gHM64Ram + ((uintptr_t)(addr) - (uintptr_t)HM64_RAM_BASE))

#endif
