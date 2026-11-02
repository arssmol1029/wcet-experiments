#define PCRE2_CODE_UNIT_WIDTH 8
#define HAVE_CONFIG_H 1
#include "pcre2_internal.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "patterns.h"

#define SUBJECT_CAP 2048
#define ARENA_BYTES (2u*1024u*1024u)
#define FRAME_BYTES (512u*1024u)
#define MATCH_LIMIT 4096u
#define DEPTH_LIMIT 128u
static union{max_align_t a;unsigned char bytes[ARENA_BYTES];} arena;
static union{max_align_t a;unsigned char bytes[FRAME_BYTES];} frame_storage;
static size_t arena_used;
volatile unsigned kernel_allocator_calls;
static void *bounded_malloc(PCRE2_SIZE n,void *memory_data)
{size_t align=_Alignof(max_align_t),start=(arena_used+align-1)/align*align;
 (void)memory_data;kernel_allocator_calls++;
 if(!n || n>ARENA_BYTES || start>ARENA_BYTES-n)return NULL;
 arena_used=start+n;return arena.bytes+start;}
static void bounded_free(void *p,void *memory_data)
{(void)p;(void)memory_data;/* finite monotone arena, no reclamation */}
static pcre2_code *prepared_code;
static pcre2_match_context *prepared_context;
static pcre2_match_data *prepared_data;
unsigned char packet_subject[SUBJECT_CAP];
PCRE2_SIZE packet_subject_length;
volatile int kernel_result;

__attribute__((noinline,used)) void pcre2_packet_match_kernel(void)
{kernel_result=pcre2_match(prepared_code,packet_subject,packet_subject_length,0,
  PCRE2_ANCHORED,prepared_data,prepared_context);}

/* Preparation and diagnostics are outside the task. No match arithmetic is
 * replaced: private upstream layout is used only to provide a real preallocated
 * frame vector, as in ordinary prepared-context function analysis. */
static int prepare(unsigned index)
{int error;PCRE2_SIZE offset,compiled_bytes;uint32_t captures;
 pcre2_general_context *general;
 if(index>=sizeof(patterns)/sizeof(patterns[0]))return 0;
 general=pcre2_general_context_create(bounded_malloc,bounded_free,NULL);
 if(!general)return 0;
 prepared_context=pcre2_match_context_create(general);
 prepared_code=pcre2_compile((PCRE2_SPTR)patterns[index],PCRE2_ZERO_TERMINATED,
   pattern_options[index],&error,&offset,NULL);
 if(!prepared_context || !prepared_code){fprintf(stderr,"compile error%d offset%zu\n",error,(size_t)offset);return 0;}
 /* Compile used the ordinary public default allocator outside the task.
  * Match data and context carry the explicit real bounded runtime callbacks. */
 prepared_data=pcre2_match_data_create_from_pattern(prepared_code,general);
 if(!prepared_data)return 0;
 pcre2_set_match_limit(prepared_context,MATCH_LIMIT);
 pcre2_set_depth_limit(prepared_context,DEPTH_LIMIT);
 pcre2_set_heap_limit(prepared_context,FRAME_BYTES/1024);
 prepared_data->heapframes=(heapframe *)frame_storage.bytes;
 prepared_data->heapframes_size=FRAME_BYTES;
 pcre2_pattern_info(prepared_code,PCRE2_INFO_CAPTURECOUNT,&captures);
 pcre2_pattern_info(prepared_code,PCRE2_INFO_SIZE,&compiled_bytes);
 fprintf(stderr,"prepared pattern%u compiled%zu captures%u frame_base%zu arena%zu limit%u depth%u\n",
   index,(size_t)compiled_bytes,captures,offsetof(heapframe,ovector),arena_used,MATCH_LIMIT,DEPTH_LIMIT);
 return 1;}

int main(int argc,char **argv)
{unsigned pattern,before;size_t n;PCRE2_SIZE *ovector;
 if(argc!=3)return 2;
 pattern=(unsigned)strtoul(argv[1],NULL,10);
 if(!prepare(pattern))return 3;
 n=strlen(argv[2]);if(n>SUBJECT_CAP)return 4;
 memcpy(packet_subject,argv[2],n);packet_subject_length=n;
 before=kernel_allocator_calls;
 pcre2_packet_match_kernel();
 ovector=pcre2_get_ovector_pointer(prepared_data);
 printf("{\"rc\":%d,\"start\":%zu,\"end\":%zu,\"kernel_allocations\":%u,\"length\":%zu}\n",
  kernel_result,kernel_result>=0?(size_t)ovector[0]:0,
  kernel_result>=0?(size_t)ovector[1]:0,kernel_allocator_calls-before,n);
 return kernel_allocator_calls==before?0:5;}
