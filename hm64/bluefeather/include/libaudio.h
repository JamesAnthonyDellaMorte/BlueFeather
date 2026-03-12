#ifndef BLUEFEATHER_LIBAUDIO_H
#define BLUEFEATHER_LIBAUDIO_H

#include <ultra64.h>
#include <libultraship/libultra/abi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef s32 ALMicroTime;
typedef u8 ALPan;

#define AL_FX_BIGROOM 2
#define AL_ADPCM_WAVE 0
#define AL_RAW16_WAVE 1

typedef struct ALLink_s {
    struct ALLink_s* next;
    struct ALLink_s* prev;
} ALLink;

typedef struct {
    u8* base;
    u8* cur;
    s32 len;
    s32 count;
} ALHeap;

void alHeapInit(ALHeap* hp, u8* base, s32 len);
void* alHeapDBAlloc(u8* file, s32 line, ALHeap* hp, s32 num, s32 size);

#ifdef _DEBUG
#define alHeapAlloc(hp, elem, size) alHeapDBAlloc((u8*)__FILE__, __LINE__, (hp), (elem), (size))
#else
#define alHeapAlloc(hp, elem, size) alHeapDBAlloc(0, 0, (hp), (elem), (size))
#endif

typedef struct {
    s32 order;
    s32 npredictors;
    s16 book[1];
} ALADPCMBook;

typedef struct {
    u32 start;
    u32 end;
    u32 count;
    ADPCM_STATE state;
} ALADPCMloop;

typedef struct {
    u32 start;
    u32 end;
    u32 count;
} ALRawLoop;

typedef struct {
    ALADPCMloop* loop;
    ALADPCMBook* book;
} ALADPCMWaveInfo;

typedef struct {
    ALRawLoop* loop;
} ALRAWWaveInfo;

typedef struct ALWaveTable_s {
    u8* base;
    s32 len;
    u8 type;
    u8 flags;
    union {
        ALADPCMWaveInfo adpcmWave;
        ALRAWWaveInfo rawWave;
    } waveInfo;
} ALWaveTable;

typedef struct {
    s16* pcm;
    u32 pcmLength;
    s16* loopPcm;
    u32 loopPcmLength;
    double cursor;
    float pitch;
    u32 volume;
    u8 pan;
    u8 fxMix;
    u8 active;
    ALWaveTable* wave;
} ALVoice;

typedef struct {
    float unityPitch;
    s32 priority;
    u8 fxBus;
} ALVoiceConfig;

typedef ALMicroTime (*ALPlayerHandler)(void* clientData);

typedef struct ALPlayer_s {
    struct ALPlayer_s* next;
    ALPlayerHandler handler;
    void* clientData;
} ALPlayer;

typedef struct {
    int dummy;
} ALSynth;

typedef struct {
    ALSynth drvr;
} ALGlobals;

typedef ALGlobals N_ALGlobals;

void alSynAddPlayer(ALSynth* drvr, ALPlayer* player);
void alSynRemovePlayer(ALSynth* drvr, ALPlayer* player);
void alSynAllocVoice(ALSynth* drvr, ALVoice* voice, ALVoiceConfig* config);
void alSynStartVoice(ALSynth* drvr, ALVoice* voice, ALWaveTable* wave);
void alSynStopVoice(ALSynth* drvr, ALVoice* voice);
void alSynSetVol(ALSynth* drvr, ALVoice* voice, u32 volume, ALMicroTime delta);
void alSynSetPan(ALSynth* drvr, ALVoice* voice, ALPan pan);
void alSynSetPitch(ALSynth* drvr, ALVoice* voice, float pitch);
void alSynSetFXMix(ALSynth* drvr, ALVoice* voice, u8 fxmix);

#ifdef __cplusplus
}
#endif

#endif
