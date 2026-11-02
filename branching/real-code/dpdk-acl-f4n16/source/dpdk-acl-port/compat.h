/* Portable environment for the unchanged DPDK build-trie source slice. */
#ifndef BENCH_ACL_COMPAT_H
#define BENCH_ACL_COMPAT_H
#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _RTE_ACL_OSDEP_H_
#define RTE_DIM(a) (sizeof(a) / sizeof((a)[0]))
#define RTE_LEN2MASK(n,t) ((t)((UINT64_C(1) << (n)) - 1))
#define RTE_ALIGN_CEIL(v,a) (((v) + (a) - 1) & ~((a) - 1))
#define RTE_PTR_ALIGN_CEIL(v,a) ((void *)RTE_ALIGN_CEIL((uintptr_t)(v),(uintptr_t)(a)))
#define XMM_SIZE 16
#define rte_free free
#include "upstream/rte_acl.h"
#include "upstream/acl.h"
#include "upstream/tb_mem.h"
#endif
