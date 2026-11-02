#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"
#include "compress/zstd_compress_internal.h"
#include <stddef.h>

const unsigned zstd_block_arm_abi_values[]={
    sizeof(void*),sizeof(size_t),sizeof(ZSTD_CCtx),sizeof(ZSTD_compressedBlockState_t),
    TMP_WORKSPACE_SIZE,ENTROPY_WORKSPACE_SIZE,
    offsetof(ZSTD_CCtx,blockState),offsetof(ZSTD_CCtx,seqStore),
    offsetof(ZSTD_CCtx,tmpWorkspace),offsetof(ZSTD_CCtx,tmpWkspSize),
    offsetof(ZSTD_CCtx,appliedParams),offsetof(ZSTD_CCtx,isFirstBlock),
    offsetof(ZSTD_CCtx,externSeqStore),offsetof(ZSTD_CCtx,seqCollector),
    offsetof(ZSTD_CCtx,bmi2),offsetof(ZSTD_CCtx,stage),
    offsetof(ZSTD_MatchState_t,window),offsetof(ZSTD_MatchState_t,nextToUpdate),
    offsetof(ZSTD_MatchState_t,cParams),offsetof(ZSTD_MatchState_t,ldmSeqStore),
    offsetof(ZSTD_MatchState_t,opt),sizeof(ZSTD_window_t),
    offsetof(ZSTD_window_t,base),offsetof(ZSTD_window_t,nextSrc),
    offsetof(ZSTD_window_t,dictLimit),offsetof(ZSTD_window_t,lowLimit),
    offsetof(ZSTD_window_t,nbOverflowCorrections),
    sizeof(ZSTD_entropyCTables_t),sizeof(ZSTD_hufCTables_t),sizeof(ZSTD_fseCTables_t),
    HUF_TABLELOG_MAX,LitHufLog,LLFSELog,MLFSELog,OffFSELog,
    ZSTD_WINDOW_OVERFLOW_CORRECT_FREQUENTLY,ZSTD_CURRENT_MAX
};
_Static_assert(sizeof(void*)==4,"ARM32");
