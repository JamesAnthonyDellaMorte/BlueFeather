// common.h - PC version of HM64 common.h
#ifndef _COMMON_H_
#define _COMMON_H_

#include "include_asm.h"

#include <ultra64.h>
#include <nusys.h>
#include <libmus.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <math.h>
#include <string.h>

#include "structs.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef u32 Addr;

static inline u16 hm64ReadRawU16(const void* ptr) {
    const u8* bytes = (const u8*)ptr;
    return ((u16)bytes[0] << 8) | bytes[1];
}

static inline s16 hm64ReadRawS16(const void* ptr) {
    return (s16)hm64ReadRawU16(ptr);
}

static inline u16 hm64ReadRawLEU16(const void* ptr) {
    const u8* bytes = (const u8*)ptr;
    return ((u16)bytes[1] << 8) | bytes[0];
}

static inline s16 hm64ReadRawLES16(const void* ptr) {
    return (s16)hm64ReadRawLEU16(ptr);
}

static inline u32 hm64ReadIndexedU32(const u32* table, u32 index) {
    const u8* bytes = (const u8*)table + (index * sizeof(u32));
    return ((u32)bytes[0] << 24) |
           ((u32)bytes[1] << 16) |
           ((u32)bytes[2] << 8) |
           (u32)bytes[3];
}

static inline u32 hm64ReadRawU32(const void* ptr) {
    const u8* bytes = (const u8*)ptr;
    return ((u32)bytes[0] << 24) |
           ((u32)bytes[1] << 16) |
           ((u32)bytes[2] << 8) |
           (u32)bytes[3];
}

#ifndef BE16SWAP
#define BE16SWAP(x) __builtin_bswap16(x)
#endif

#ifndef BE32SWAP
#define BE32SWAP(x) __builtin_bswap32(x)
#endif

// libultraship names controller error fields err_no, while the HM64 codebase uses errno.
#ifndef errno
#define errno err_no
#endif

// FIXME: signature from ultra64.h; not getting picked up by sprite.c
#ifdef __assert
#undef __assert
#endif
void __assert(const char* exp, const char* filename, int line);     

#endif
