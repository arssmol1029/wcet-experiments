/* DPDK v24.11 build_trie and stock tb_mem unchanged, shared with acl-port.
 * Only prepared finite rule data, pool reservation, and test oracle differ.
 * The performance entry has no instrumentation. */
#include "../dpdk-acl-port/compat.h"
#include "../dpdk-acl-port/rte_log.h"
#include "../dpdk-acl-port/upstream/acl_log.h"
#include "../dpdk-acl-port/generated/acl-build-slice.inc"

#ifndef CASE_RULES
#define CASE_RULES 16
#endif
#ifndef CASE_FAMILIES
#define CASE_FAMILIES 4
#endif
#define MAX_RULES 256
RTE_ACL_RULE_DEF(ipv4_rule, 5);
static struct ipv4_rule input[MAX_RULES];
static struct rte_acl_build_rule prepared[MAX_RULES];
static struct acl_build_context context;
static struct rte_acl_node *answer;
static uint32_t processed;

unsigned char abi_size_node[sizeof(struct rte_acl_node)];
unsigned char abi_size_ptrset[sizeof(struct rte_acl_ptr_set)];
unsigned char abi_size_mrt[sizeof(struct rte_acl_match_results)];
unsigned char abi_size_memblock[sizeof(struct tb_mem_block)];

__attribute__((noinline)) uint32_t task_dpdk_acl(void)
{
    struct rte_acl_build_rule *last;
    answer = build_trie(&context, prepared, &last, &processed);
    return processed;
}

/* Preparation only: all-allocation upper bound, no allocator reuse assumed. */
static size_t payload_bound(unsigned n)
{
    const uint64_t j = CASE_FAMILIES == 2 ? 136 : 448;
    const uint64_t nodes = 1 + 19 * (uint64_t)n + j * (n - 1);
    const uint64_t arrays = 1 + 18 * (uint64_t)n + j * (n - 1);
    const uint64_t q = RTE_ALIGN_CEIL(sizeof(struct rte_acl_node), 8) * nodes +
        RTE_ALIGN_CEIL(32 * sizeof(struct rte_acl_ptr_set), 8) * arrays +
        RTE_ALIGN_CEIL(sizeof(struct rte_acl_match_results), 8) * (uint64_t)n;
    return q > SIZE_MAX ? 0 : (size_t)q;
}

static int initialize(unsigned n)
{
    static const uint8_t protocol_value[] = {0, 1, 1, 0};
    static const uint8_t protocol_mask[] = {0xf0, 0x0f, 0x03, 0x0c};
    static const uint32_t source_value[] = {
        UINT32_C(0x0a000000), UINT32_C(0x08000000),
        UINT32_C(0x0c000000), UINT32_C(0x00000000)};
    static const unsigned source_prefix[] = {8, 6, 6, 4};
    if ((CASE_FAMILIES != 2 && CASE_FAMILIES != 4) ||
        (n != 16 && n != 64 && n != 256) || (CASE_FAMILIES == 2 && n != 16))
        return 1;
    memset(&context, 0, sizeof(context));
    memset(input, 0, sizeof(input));
    memset(prepared, 0, sizeof(prepared));
    processed = 0;
    answer = NULL;
    context.pool.alignment = ACL_POOL_ALIGN;
    size_t q = payload_bound(n), reserve = ACL_POOL_ALLOC_MIN;
    if (!q) return 1;
    while (reserve < q) {
        if (reserve > SIZE_MAX / 2) return 1;
        reserve *= 2;
    }
    context.pool.min_alloc = reserve;
    context.cur_node_max = INT32_MAX;
    context.cfg.num_categories = 1;
    context.cfg.num_fields = 5;
    context.cfg.defs[0] = (struct rte_acl_field_def){RTE_ACL_FIELD_TYPE_BITMASK,1,0,0,0};
    context.cfg.defs[1] = (struct rte_acl_field_def){RTE_ACL_FIELD_TYPE_MASK,4,1,1,1};
    context.cfg.defs[2] = (struct rte_acl_field_def){RTE_ACL_FIELD_TYPE_MASK,4,2,2,5};
    context.cfg.defs[3] = (struct rte_acl_field_def){RTE_ACL_FIELD_TYPE_RANGE,2,3,3,9};
    context.cfg.defs[4] = (struct rte_acl_field_def){RTE_ACL_FIELD_TYPE_RANGE,2,4,3,11};
    for (unsigned i = 0; i < n; ++i) {
        unsigned f = i % CASE_FAMILIES;
        input[i].data.category_mask = 1;
        input[i].data.priority = (int32_t)i + 1;
        input[i].data.userdata = i + 1;
        input[i].field[0].value.u8 = protocol_value[f];
        input[i].field[0].mask_range.u8 = protocol_mask[f];
        input[i].field[1].value.u32 = source_value[f];
        input[i].field[1].mask_range.u32 = source_prefix[f];
        input[i].field[2].value.u32 = UINT32_C(0xc0000200);
        input[i].field[2].mask_range.u32 = 24;
        input[i].field[3].value.u16 = UINT16_C(0x1200);
        input[i].field[3].mask_range.u16 = UINT16_C(0x127f);
        input[i].field[4].value.u16 = UINT16_C(0x3400);
        input[i].field[4].mask_range.u16 = UINT16_C(0x34ff);
        prepared[i].config = &context.cfg;
        prepared[i].f = (const struct rte_acl_rule *)&input[i];
        prepared[i].next = i + 1 < n ? &prepared[i+1] : NULL;
    }
    return 0;
}

#ifdef NATIVE_TEST
/* Flat rule evaluator independent of node/DAG construction, all five fields.
 * It reads actual prepared field definitions, masks/ranges, and priorities. */
static unsigned oracle(unsigned n, uint8_t proto, uint32_t src, uint32_t dst,
                       uint16_t sport, uint16_t dport)
{
    const uint32_t values[5] = {proto, src, dst, sport, dport};
    int32_t best = INT32_MIN;
    unsigned result = 0;
    for (unsigned i = 0; i < n; ++i) {
        int matches = (input[i].data.category_mask & 1) != 0;
        for (unsigned j = 0; matches && j < context.cfg.num_fields; ++j) {
            const struct rte_acl_field_def *def = &context.cfg.defs[j];
            const struct rte_acl_field *f = &input[i].field[def->field_index];
            uint32_t v = def->size == 1 ? f->value.u8 : def->size == 2 ? f->value.u16 : f->value.u32;
            uint32_t m = def->size == 1 ? f->mask_range.u8 : def->size == 2 ? f->mask_range.u16 : f->mask_range.u32;
            uint32_t x = values[def->field_index];
            if (def->type == RTE_ACL_FIELD_TYPE_BITMASK) matches = (x & m) == v;
            else if (def->type == RTE_ACL_FIELD_TYPE_RANGE) matches = v <= x && x <= m;
            else if (def->type == RTE_ACL_FIELD_TYPE_MASK) {
                if (m > 32) abort();
                uint32_t mask = m == 0 ? 0 : UINT32_MAX << (32 - m);
                matches = (x & mask) == (v & mask);
            } else abort();
        }
        if (matches && input[i].data.priority > best) {
            best = input[i].data.priority;
            result = input[i].data.userdata;
        }
    }
    return result;
}

static unsigned classify(uint8_t proto, uint32_t src, uint32_t dst,
                         uint16_t sport, uint16_t dport)
{
    const unsigned char key[13] = {proto,src>>24,src>>16,src>>8,src,
        dst>>24,dst>>16,dst>>8,dst,sport>>8,sport,dport>>8,dport};
    const struct rte_acl_node *node = answer;
    for (unsigned k=0;k<13 && node;++k) {
        const struct rte_acl_node *next = NULL;
        for (unsigned p=0;p<node->num_ptrs;++p) {
            if (node->ptrs[p].ptr &&
                (node->ptrs[p].values.bits[key[k]/32] & (1u<<(key[k]%32)))) {
                if (next) abort();
                next=node->ptrs[p].ptr;
            }
        }
        node=next;
    }
    return node && node->match_flag ? node->mrt->results[0] : 0;
}

static unsigned membership(unsigned byte, unsigned field)
{
    unsigned signature = 0;
    for (unsigned f=0;f<CASE_FAMILIES;++f) {
        uint32_t v, mask;
        if (!field) {v=input[f].field[0].value.u8;mask=input[f].field[0].mask_range.u8;}
        else {
            unsigned bits=input[f].field[1].mask_range.u32;
            mask=(UINT32_C(255) << (8-bits)) & 255;
            v=(input[f].field[1].value.u32>>24)&mask;
        }
        signature |= ((byte & mask) == v) << f;
    }
    return signature;
}

static unsigned check_tuple(unsigned n, uint8_t p, uint32_t s, uint32_t d,
                            uint16_t sp, uint16_t dp)
{
    unsigned got=classify(p,s,d,sp,dp), want=oracle(n,p,s,d,sp,dp);
    if (got!=want) {
        fprintf(stderr,"oracle mismatch F=%u N=%u p=%u s=%08x d=%08x sp=%u dp=%u got=%u expected=%u\n",
            CASE_FAMILIES,n,p,s,d,sp,dp,got,want);
        exit(5);
    }
    return 1;
}

static uint64_t verify_oracle(unsigned n)
{
    uint64_t checked=0;
    /* Exhaust every possible protocol and first source byte. */
    for (unsigned p=0;p<256;++p) for(unsigned s=0;s<256;++s)
        checked+=check_tuple(n,p,((uint32_t)s<<24)|0x123456,0xc00002ab,0x1234,0x3480);
    /* Every joint membership cell, plus boundaries of every remaining field. */
    unsigned repr[2][16],count[2]={0,0};
    for(unsigned field=0;field<2;++field) {
        unsigned seen[16]={0};
        for(unsigned b=0;b<256;++b) {
            unsigned sig=membership(b,field);
            if(!seen[sig]) {seen[sig]=1;repr[field][count[field]++]=b;}
        }
    }
    const uint32_t tail[]={0,0x7fffff,0xffffff};
    const uint32_t dst[]={0,0xc00001ff,0xc0000200,0xc000027f,0xc00002ff,0xc0000300,UINT32_MAX};
    const uint16_t sport[]={0,0x11ff,0x1200,0x1201,0x127e,0x127f,0x1280,UINT16_MAX};
    const uint16_t dport[]={0,0x33ff,0x3400,0x3401,0x34fe,0x34ff,0x3500,UINT16_MAX};
    for(unsigned p=0;p<count[0];++p) for(unsigned s=0;s<count[1];++s)
    for(unsigned t=0;t<RTE_DIM(tail);++t) for(unsigned d=0;d<RTE_DIM(dst);++d)
    for(unsigned sp=0;sp<RTE_DIM(sport);++sp) for(unsigned dp=0;dp<RTE_DIM(dport);++dp)
        checked+=check_tuple(n,repr[0][p],((uint32_t)repr[1][s]<<24)|tail[t],dst[d],sport[sp],dport[dp]);
    return checked;
}

int main(void)
{
    const unsigned n=CASE_RULES;
    if(initialize(n)) return 1;
    if(sigsetjmp(context.pool.fail,0)) return 2;
    (void)tb_alloc(&context.pool,0); /* stock reserve, outside the analysis entry */
    struct tb_mem_block *original=context.pool.block;
    size_t original_remaining=original->size;
    if(task_dpdk_acl()!=n || !answer) return 3;
    if(context.pool.block!=original || original->next) return 4;
    size_t fresh=original_remaining-original->size;
    if(fresh>payload_bound(n)) return 6;
    uint64_t comparisons=verify_oracle(n);
    printf("{\"status\":\"PASS\",\"F\":%u,\"N\":%u,\"oracle_comparisons\":%"PRIu64
        ",\"final_live_nodes\":%u,\"fresh_payload\":%zu,\"source_payload_upper\":%zu"
        ",\"min_alloc\":%zu,\"pool_alloc\":%zu,\"node_size\":%zu,\"ptrset_size\":%zu"
        ",\"mrt_size\":%zu,\"block_size\":%zu,\"kernel_refills\":0}\n",
        CASE_FAMILIES,n,comparisons,context.num_nodes,fresh,payload_bound(n),context.pool.min_alloc,
        context.pool.alloc,sizeof(struct rte_acl_node),sizeof(struct rte_acl_ptr_set),
        sizeof(struct rte_acl_match_results),sizeof(struct tb_mem_block));
    tb_free_pool(&context.pool);
    return 0;
}
#else
int main(void)
{
    if(initialize(CASE_RULES)) return 1;
    if(sigsetjmp(context.pool.fail,0)) return 2;
    (void)tb_alloc(&context.pool,0);
    return task_dpdk_acl()==CASE_RULES && answer ? 0 : 3;
}
#endif
