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

#if defined(_MSC_VER)
#include <intrin.h>
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

#ifndef HM64_IN_RANGE
#define HM64_IN_RANGE(value, low, high) ((value) >= (low) && (value) <= (high))
#endif

#ifndef HM64_COMPILER_BARRIER
#if defined(_MSC_VER)
#define HM64_COMPILER_BARRIER() _ReadWriteBarrier()
#else
#define HM64_COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")
#endif
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
#if defined(_MSC_VER)
#define BE16SWAP(x) _byteswap_ushort(x)
#else
#define BE16SWAP(x) __builtin_bswap16(x)
#endif
#endif

#ifndef BE32SWAP
#if defined(_MSC_VER)
#define BE32SWAP(x) _byteswap_ulong(x)
#else
#define BE32SWAP(x) __builtin_bswap32(x)
#endif
#endif

// libultraship names controller error fields err_no, while the HM64 codebase uses errno.
#ifndef errno
#define errno err_no
#endif

// FIXME: signature from ultra64.h; not getting picked up by sprite.c
#ifdef __assert
#undef __assert
#endif
#ifdef __cplusplus
#define HM64_COMMON_ASSERT_NOEXCEPT noexcept
#else
#define HM64_COMMON_ASSERT_NOEXCEPT
#endif
#if defined(__GNUC__) || defined(__clang__)
#define HM64_COMMON_NORETURN __attribute__((noreturn))
#else
#define HM64_COMMON_NORETURN
#endif
void __assert(const char* exp, const char* filename, int line) HM64_COMMON_ASSERT_NOEXCEPT HM64_COMMON_NORETURN;
#undef HM64_COMMON_ASSERT_NOEXCEPT
#undef HM64_COMMON_NORETURN

#endif
