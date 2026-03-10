// nusys.h - PC replacement for N64 NuSystem
#ifndef _NUSYS_H_
#define _NUSYS_H_

#include "ultra64_compat.h"
#include "hm64_ram.h"

// NuSystem graphics
#define NU_GFX_UCODE_F3DEX  0
#define NU_GFX_UCODE_S2DEX  1
#define NU_GFX_UCODE_L3DEX  2

#define NU_SC_NOSWAPBUFFER  0
#define NU_SC_SWAPBUFFER    1

#define NU_GFX_FRAMEBUFFER_NUM 3
#define NU_GFX_FRAMEBUFFER_ADDR ((uintptr_t)HM64_RAM_PTR(0x8038F800))
#define NU_GFX_FRAMEBUFFER0_ADDR (NU_GFX_FRAMEBUFFER_ADDR)
#define NU_GFX_FRAMEBUFFER1_ADDR (NU_GFX_FRAMEBUFFER0_ADDR + 320 * 240 * 2)
#define NU_GFX_FRAMEBUFFER2_ADDR (NU_GFX_FRAMEBUFFER1_ADDR + 320 * 240 * 2)
#define NU_GFX_ZBUFFER_ADDR ((uintptr_t)HM64_RAM_PTR(0x80000400))
#define NU_GFX_INIT_SCREEN_WD 320
#define NU_GFX_INIT_SCREEN_HT 240
#define NU_GFX_DISPLAY_ON 1
#define NU_GFX_DISPLAY_OFF 0

// NuSystem controller constants
#define NU_CONT_MAXCONTROLLERS 4
#define NU_CONT_PAK_MODE_NOCREATE 0
#define NU_CONT_PAK_MODE_CREATE 1

typedef struct {
    u64* ucode;
    u64* ucode_data;
} NUUcode;

typedef struct {
    OSThread graphicsThread;
    OSThread audioThread;
    u32 retraceCount;
} NUSched;

typedef void (*NUGfxFunc)(u32);
typedef void (*NUGfxSwapCfbFunc)(void*);
typedef void (*NUGfxPreNMIFunc)(void);

typedef struct {
    u16 button;
    s8 stick_x;
    s8 stick_y;
    u8 errno;
    u16 trigger;
} NUContData;

typedef struct {
    OSPfs* pfs;
    s32 file_no;
    s32 error;
    u32 type;
} NUContPakFile;

typedef struct {
    u32 gameCode;
    u16 companyCode;
    u8 extName[4];
    u8 status;
} NUContPakCode;

// NuSystem globals
#ifdef __cplusplus
extern "C" {
#endif

extern NUSched nusched;

extern u16** nuGfxCfb;
extern u16* nuGfxCfb_ptr;
extern u32 nuGfxCfbNum;
extern u16* nuGfxZBuffer;
extern volatile u32 nuGfxTaskSpool;
extern u32 nuGfxDisplay;
extern u32 nuGfxDisplayNum;
extern u32 nuGfxCfbCounter;
extern NUUcode* nuGfxUcode;

extern OSContStatus nuContStatus[NU_CONT_MAXCONTROLLERS];

// NuSystem init
void nuGfxInit(void);
void nuGfxThreadStart(void);
void nuGfxTaskMgrInit(void);

// NuSystem display control
void nuGfxDisplayOn(void);
void nuGfxDisplayOff(void);

// NuSystem task management
void nuGfxTaskStart(Gfx* dl, u32 size, u32 ucode, u32 flags);
void nuGfxTaskAllEndWait(void);

void nuGfxFuncSet(NUGfxFunc func);
void nuGfxSwapCfbFuncSet(NUGfxSwapCfbFunc func);
void nuGfxPreNMIFuncSet(NUGfxPreNMIFunc func);

// NuSystem buffer management
void nuGfxSetCfb(u16** frameBuf, u32 count);
void nuGfxSetZBuffer(u16* zBuffer);
void nuGfxSwapCfb(void* frameBuf);

// NuSystem controller
u8 nuContInit(void);
void nuContDataGetEx(void* contData, u32 padNo);
void nuContDataGetExAll(void* contData);

void nuContPakOpen(NUContPakFile* file, u32 contNo);
s32 nuContPakGetFree(NUContPakFile* file);
void nuContPakCodeSet(u8* companyCode, u8* gameCode);
void nuContPakRepairId(NUContPakFile* file);
void nuContPakFileOpenJis(NUContPakFile* file, u8* noteName, u8* extName, u32 mode, s32 size);
void nuContPakFileReadWriteCompat(NUContPakFile* file, s32 offset, s32 size, void* buf, u32 mode);
void nuContPakFileDeleteJis(NUContPakFile* file, u8* noteName, u8* extName);
void nuContPakFileNum(NUContPakFile* file, s32* maxFiles, s32* usedFiles);

void nuPiReadRomCompat(uintptr_t romAddr, uintptr_t bufAddr, u32 size);
void nuPiReadRom2Compat(uintptr_t romAddr, uintptr_t bufAddr, u32 size);

#define nuContPakFileReadWrite(file, offset, size, buf, mode) \
    nuContPakFileReadWriteCompat((file), (offset), (size), (void*)(uintptr_t)(buf), (mode))

#define nuPiReadRom(romAddr, bufPtr, size) nuPiReadRomCompat((uintptr_t)(romAddr), (uintptr_t)(bufPtr), (size))
#define nuPiReadRom2(romAddr, bufPtr, size) nuPiReadRom2Compat((uintptr_t)(romAddr), (uintptr_t)(bufPtr), (size))

// NuSystem audio
void nuAuInit(void);
void nuAuSeqPlayerInit(void);
void nuAuSeqPlayerSetNo(u8 playerNo, u8 seqNo, u16 offset);
void nuAuSeqPlayerPlay(u8 playerNo);
void nuAuSeqPlayerStop(u8 playerNo);
void nuAuSeqPlayerFadeOut(u8 playerNo, u16 speed);

#ifdef __cplusplus
}
#endif

#endif // _NUSYS_H_
