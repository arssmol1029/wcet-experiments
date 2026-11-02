/* Public upstream whole-block entry, with all context preparation outside task. */
#define ZSTD_STATIC_LINKING_ONLY
#include "zstd.h"
#include <stddef.h>

ZSTD_CCtx *block_task_context;
void *block_task_destination;
size_t block_task_capacity;
const void *block_task_source;
size_t block_task_size;

__attribute__((noinline)) size_t task_zstd_block(void)
{
    return ZSTD_compressBlock(block_task_context, block_task_destination,
                             block_task_capacity, block_task_source,
                             block_task_size);
}
