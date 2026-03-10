// libmus.h - PC replacement for N64 libmus
#ifndef _LIBMUS_H_
#define _LIBMUS_H_

#include <ultra64.h>
#include <nusys.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long musHandle;

typedef struct {
    unsigned long control_flag;
    int channels;
    NUSched* sched;
    int thread_priority;
    unsigned char* heap;
    int heap_length;
    unsigned char* ptr;
    unsigned char* wbk;
    char** fxs;
    int* priority;
    int syn_updates;
    int syn_output_rate;
    int syn_rsp_cmds;
    int syn_retraceCount;
    int syn_num_dma_bufs;
    int syn_dma_buf_size;
} musConfig;

#define MUSCONTROL_RAM (1 << 0)
#define MUSFLAG_EFFECTS 1
#define MUSFLAG_SONGS 2

// Stub functions
static inline int MusInitialize(musConfig* config) {
    (void)config;
    return 0;
}

static inline void MusSetMasterVolume(unsigned long flags, int volume) {
    (void)flags;
    (void)volume;
}

static inline unsigned long MusStartSong(void* song) {
    (void)song;
    return 0;
}

static inline void MusStop(unsigned long flags, int speed) {
    (void)flags;
    (void)speed;
}

static inline int MusHandleStop(unsigned long handle, int speed) {
    (void)handle;
    (void)speed;
    return 0;
}

static inline int MusHandleAsk(unsigned long handle) {
    (void)handle;
    return 0;
}

static inline int MusHandleSetVolume(unsigned long handle, int volume) {
    (void)handle;
    (void)volume;
    return 0;
}

static inline int MusHandleSetPan(unsigned long handle, int pan) {
    (void)handle;
    (void)pan;
    return 0;
}

static inline int MusHandleSetFreqOffset(unsigned long handle, float offset) {
    (void)handle;
    (void)offset;
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // _LIBMUS_H_
