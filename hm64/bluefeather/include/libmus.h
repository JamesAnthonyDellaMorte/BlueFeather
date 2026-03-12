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

int MusInitialize(musConfig* config);

void MusSetMasterVolume(unsigned long flags, int volume);

unsigned long MusStartSong(void* addr);
unsigned long MusStartEffect(int number);
unsigned long MusStartEffect2(int number, int volume, int pan, int restartflag, int priority);

void MusStop(unsigned long flags, int speed);
int MusAsk(unsigned long flags);

int MusHandleStop(unsigned long handle, int speed);
int MusHandleAsk(unsigned long handle);
int MusHandleSetVolume(unsigned long handle, int volume);
int MusHandleSetPan(unsigned long handle, int pan);
int MusHandleSetFreqOffset(unsigned long handle, float offset);
int MusHandleSetTempo(unsigned long handle, int tempo);
int MusHandleSetReverb(unsigned long handle, int reverb);

void MusBankInitialize(void* pbank, void* wbank);
unsigned long MusBankStartSong(void* ipbank, void* addr);
unsigned long MusBankStartEffect(void* ipbank, int number);
unsigned long MusBankStartEffect2(void* ipbank, int number, int volume, int pan, int restartflag, int priority);
void* MusHandleGetPtrAddr(int handle);

#ifdef __cplusplus
}
#endif

#endif
