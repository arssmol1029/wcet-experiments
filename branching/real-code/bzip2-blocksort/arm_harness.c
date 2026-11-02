/* Portable preparation and single-call entry for future GCC 12.2 ARM build.
 * Algorithm source and the real BZ_RUN/RLE preparation stay unmodified. */
#define BZ_NO_STDIO 1
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "source/bzip2-1.0.8/bzlib.c"

#ifndef RAW_CAP
#define RAW_CAP 8192
#endif
#ifndef WORK_FACTOR
#define WORK_FACTOR 30
#endif
static union { long double alignment; unsigned char bytes[2*1024*1024]; } arena;
static size_t arena_used;
static unsigned char raw[RAW_CAP];
static EState *prepared;
static volatile unsigned task_allocation_violation;
static unsigned inside_task;

static void *bounded_alloc(void *opaque,int count,int size) {
    size_t amount,start;
    (void)opaque;
    if(inside_task){task_allocation_violation=1;return NULL;}
    if(count<0||size<0||(size&&(size_t)count>SIZE_MAX/(size_t)size))return NULL;
    amount=(size_t)count*(size_t)size;
    start=(arena_used+15u)&~(size_t)15u;
    if(start>sizeof(arena.bytes)||amount>sizeof(arena.bytes)-start)return NULL;
    arena_used=start+amount;
    /* Fully initialize scratch bytes, including the fallback bitmap tail. */
    memset(arena.bytes+start,0,amount);
    return arena.bytes+start;
}
static void bounded_free(void *opaque,void *p) {
    (void)opaque;(void)p;
    if(inside_task)task_allocation_violation=1;
    /* This arena's complete lifetime ends after one initialized stream. */
}
void bz_internal_error(int code) { (void)code;abort(); }
__attribute__((noinline)) void task_bzip2_blocksort(void) {
    BZ2_blockSort(prepared);
}
int main(int argc,char **argv) {
    bz_stream stream={0};char out[1];unsigned i,kind=(unsigned)argc%4u;
    (void)argv;
    for(i=0;i<RAW_CAP;i++) {
        if(kind==0)raw[i]=(unsigned char)(i*129u);
        else if(kind==1)raw[i]=(unsigned char)(i&1u);
        else if(kind==2)raw[i]=(unsigned char)((i/3u)%251u);
        else raw[i]=(unsigned char)(i%7u);
    }
    stream.bzalloc=bounded_alloc;stream.bzfree=bounded_free;
    if(BZ2_bzCompressInit(&stream,1,0,WORK_FACTOR)!=BZ_OK)return 10;
    stream.next_in=(char*)raw;stream.avail_in=RAW_CAP;
    stream.next_out=out;stream.avail_out=1;
    if(BZ2_bzCompress(&stream,BZ_RUN)!=BZ_RUN_OK||stream.avail_in||stream.total_out_lo32)return 11;
    prepared=(EState*)stream.state;flush_RL(prepared);
    /* The analysis contract caps the ACTUAL post-RLE length, not raw_n.
     * Other caller inputs that expand beyond this cap must be rejected here. */
    if(prepared->nblock<=0||prepared->nblock>RAW_CAP)return 12;
    inside_task=1;task_bzip2_blocksort();inside_task=0;
    if(task_allocation_violation)return 13;
    if(prepared->origPtr<0||prepared->ptr[prepared->origPtr]!=0)return 14;
    BZ2_bzCompressEnd(&stream);
    return 0;
}
