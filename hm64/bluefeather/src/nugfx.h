#ifndef _NUGFX_H_
#define _NUGFX_H_

#include <nusys.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialization
void nuGfxInit(void);
void nuGfxThreadStart(void);
void nuGfxTaskMgrInit(void);

// Configuration
void nuGfxSetCfb(u16** frameBuf, u32 count);
void nuGfxSetZBuffer(u16* zBuffer);
void nuGfxSwapCfbFuncSet(NUGfxSwapCfbFunc func);
void nuGfxPreNMIFuncSet(NUGfxPreNMIFunc func);
void nuGfxFuncSet(NUGfxFunc func);

// Display control
void nuGfxDisplayOn(void);
void nuGfxDisplayOff(void);
void nuGfxShutdown(void);

// Task management
void nuGfxTaskStart(Gfx* dl, u32 size, u32 ucode, u32 flags);
void nuGfxTaskAllEndWait(void);
int nuGfxTaskNum(void);

// Buffer management
void nuGfxSwapCfb(void* frameBuf);
u16* nuGfxGetCfb(void);

// Callback execution
void nuGfxCallFunc(int frame);
bool nuGfxProcessPendingMainThread(void);

// Widescreen helpers
u32 BF_GetRenderWidth(void);

#ifdef __cplusplus
}
#endif

#endif // _NUGFX_H_
