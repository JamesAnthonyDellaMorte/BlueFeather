#ifndef BLUEFEATHER_NUALSTL_N_H
#define BLUEFEATHER_NUALSTL_N_H

#include <libmus.h>
#include <nusys.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NU_AU_SYN_PVOICE_MAX 32
#define NU_AU_OUTPUT_RATE 32000
#define NU_AU_HEAP_SIZE 0x80000

void nuAuStlInit(musConfig* config);
void nuAuStlBankSet(u8* pbk_addr, u32 pbk_size, u8* wbk_addr);
void nuAuStlSeqPlayerDataSet(u8 player_no, u8* seq_addr, u32 seq_size);
musHandle nuAuStlSeqPlayerPlay2(u8 player_no);
u32 nuAuStlSndPlayerPlay(u32 sndNo);
u32 nuAuStlSndPlayerPlay2(u32 sndNo, s32 volume, s32 pan, s32 restartflag, s32 priority);
void nuAuStlTick(void);

#ifdef __cplusplus
}
#endif

#endif
