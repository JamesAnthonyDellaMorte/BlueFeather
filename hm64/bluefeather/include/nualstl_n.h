#ifndef HM64_MOONWRIGHT_NUALSTL_N_H
#define HM64_MOONWRIGHT_NUALSTL_N_H

#include <nusys.h>
#include <libmus.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline void nuAuStlInit(musConfig* config) {
    MusInitialize(config);
}

static inline void nuAuStlBankSet(u8* pbk_addr, u32 pbk_size, u8* wbk_addr) {
    (void)pbk_addr;
    (void)pbk_size;
    (void)wbk_addr;
}

static inline void nuAuStlSeqPlayerDataSet(u8 player_no, u8* seq_addr, u32 seq_size) {
    (void)player_no;
    (void)seq_addr;
    (void)seq_size;
}

static inline musHandle nuAuStlSeqPlayerPlay2(u8 player_no) {
    (void)player_no;
    return 0;
}

static inline u32 nuAuStlSndPlayerPlay(u32 sndNo) {
    (void)sndNo;
    return 0;
}

static inline u32 nuAuStlSndPlayerPlay2(u32 sndNo, s32 volume, s32 pan, s32 restartflag, s32 priority) {
    (void)sndNo;
    (void)volume;
    (void)pan;
    (void)restartflag;
    (void)priority;
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif
