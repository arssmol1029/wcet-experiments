/* Real unbuffered upstream setup precedes one public whole-block task. */
#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"
#include "compress/zstd_compress_internal.h"
#include <stdint.h>

#define N 4096
#define CAP (N + N/128 + 1024)
extern ZSTD_CCtx *block_task_context;
extern void *block_task_destination;
extern size_t block_task_capacity;
extern const void *block_task_source;
extern size_t block_task_size;
extern size_t task_zstd_block(void);
unsigned char prepared_storage[N+2+64];
static unsigned char compressed[CAP];
volatile size_t compression_result;

int main(void)
{
    ZSTD_CCtx *c=ZSTD_createCCtx();
    ZSTD_parameters p=ZSTD_getParams(19,N,0);
    ZSTD_MatchState_t *m;
    unsigned char *src=prepared_storage+2;
    uint32_t state=0x21ba73d5u;
    size_t i,result;
    if(!c)return 10;
    p.cParams.windowLog=16;p.cParams.hashLog=14;p.cParams.chainLog=16;
    p.cParams.searchLog=5;p.cParams.minMatch=4;
    p.cParams.targetLength=64;p.cParams.strategy=ZSTD_btultra;
    p.fParams.contentSizeFlag=1;p.fParams.checksumFlag=0;p.fParams.noDictIDFlag=1;
    if(ZSTD_isError(ZSTD_checkCParams(p.cParams)))return 11;
    for(i=0;i<N;++i){state^=state<<13;state^=state>>17;state^=state<<5;src[i]=(unsigned char)(state%9);}
    for(i=0;i<64;++i)src[N+i]=0xa5;
    if(ZSTD_isError(ZSTD_compressBegin_advanced(c,NULL,0,p,N)))return 12;
    m=&c->blockState.matchState;
    if(c->stage!=ZSTDcs_init || c->consumedSrcSize!=0 || c->producedCSize!=0
       || c->isFirstBlock!=1 || c->blockSizeMax<N
       || m->cParams.strategy!=ZSTD_btultra || m->cParams.minMatch!=4
       || m->cParams.searchLog!=5 || m->cParams.targetLength!=64
       || m->cParams.windowLog>16 || m->cParams.hashLog>14 || m->cParams.chainLog>16
       || m->dictMatchState!=NULL || m->ldmSeqStore!=NULL || m->loadedDictEnd!=0
       || m->nextToUpdate!=2 || m->window.dictLimit!=2 || m->window.lowLimit!=2
       || m->window.nbOverflowCorrections!=0 || m->forceNonContiguous!=0
       || c->externSeqStore.size!=0 || c->externSeqStore.pos!=0
       || c->appliedParams.extSeqProdFunc!=NULL || c->seqCollector.collectSequences!=0
       || c->appliedParams.ldmParams.enableLdm==ZSTD_ps_enable
       || c->blockState.prevCBlock->entropy.huf.repeatMode!=HUF_repeat_none
       || c->blockState.prevCBlock->entropy.fse.litlength_repeatMode!=FSE_repeat_none
       || c->blockState.prevCBlock->entropy.fse.matchlength_repeatMode!=FSE_repeat_none
       || c->blockState.prevCBlock->entropy.fse.offcode_repeatMode!=FSE_repeat_none
       || c->tmpWorkspace==NULL || c->tmpWkspSize<ENTROPY_WORKSPACE_SIZE
       || c->seqStore.maxNbSeq!=N/4 || c->seqStore.maxNbLit!=N
       || c->seqStore.sequencesStart==NULL || c->seqStore.litStart==NULL
       || m->opt.litLengthSum!=0 || c->bmi2!=0)return 13;
    block_task_context=c;block_task_destination=compressed;block_task_capacity=CAP;
    block_task_source=src;block_task_size=N;
    result=task_zstd_block();compression_result=result;
    if(ZSTD_isError(result))return 14;
    return ZSTD_isError(ZSTD_freeCCtx(c))?15:0;
}
