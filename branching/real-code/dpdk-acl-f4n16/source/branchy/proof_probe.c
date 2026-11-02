/* Separate proof experiment. NEVER use this translation unit for WCET/IPET.
 * Compiler hooks do not alter upstream bodies or the performance harness. */
#define NATIVE_TEST
#define main native_harness_main_unused
#include "harness.c"
#undef main
#include "../dpdk-acl-port/upstream/tb_mem.c"

static int tracking;
static struct {
    uint64_t node_events,free_events,merge_events,duplicate_events,tb_calls,pool_calls;
    uint64_t merge_nest_calls,merge_nest_max,free_nest_calls,free_nest_max;
    unsigned merge_active,free_active,merge_depth_max,free_depth_max;
    int live,live_max;
} counts;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *fn,void *site)
{
    (void)site;
    if(!tracking)return;
    if(fn==(void*)acl_alloc_node) {
        counts.node_events++;counts.live++;
        if(counts.live>counts.live_max)counts.live_max=counts.live;
    }
    if(fn==(void*)acl_free_node) {
        counts.free_events++;counts.live--;
        if(!counts.free_active)counts.free_nest_calls=0;
        counts.free_active++;counts.free_nest_calls++;
        if(counts.free_active>counts.free_depth_max)counts.free_depth_max=counts.free_active;
    }
    if(fn==(void*)acl_merge_trie) {
        counts.merge_events++;
        if(!counts.merge_active)counts.merge_nest_calls=0;
        counts.merge_active++;counts.merge_nest_calls++;
        if(counts.merge_active>counts.merge_depth_max)counts.merge_depth_max=counts.merge_active;
    }
    if(fn==(void*)acl_dup_node)counts.duplicate_events++;
    if(fn==(void*)tb_alloc)counts.tb_calls++;
    if(fn==(void*)tb_pool)counts.pool_calls++;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *fn,void *site)
{
    (void)site;
    if(!tracking)return;
    if(fn==(void*)acl_merge_trie && --counts.merge_active==0 && counts.merge_nest_calls>counts.merge_nest_max)
        counts.merge_nest_max=counts.merge_nest_calls;
    if(fn==(void*)acl_free_node && --counts.free_active==0 && counts.free_nest_calls>counts.free_nest_max)
        counts.free_nest_max=counts.free_nest_calls;
}

static const struct rte_acl_node *unique_nodes[512];
static unsigned incoming[512],unique_count,unfolded_count,branching_nodes;

static unsigned intern(const struct rte_acl_node *node)
{
    for(unsigned i=0;i<unique_count;++i)if(unique_nodes[i]==node)return i;
    if(unique_count>=RTE_DIM(unique_nodes))abort();
    unique_nodes[unique_count]=node;
    return unique_count++;
}

static void check_unfolding(const struct rte_acl_node *node,unsigned depth)
{
    const unsigned lo[13]={0,0,0,0,0,192,0,2,0,0x12,0,0x34,0};
    const unsigned hi[13]={255,255,255,255,255,192,0,2,255,0x12,127,0x34,255};
    unsigned limit=CASE_FAMILIES==2?149:489;
    if(!node || ++unfolded_count>limit || depth>13)abort();
    unsigned index=intern(node);
    if(depth==13) {
        if(!node->match_flag||node->num_ptrs||!node->mrt||!node->mrt->results[0])abort();
        return;
    }
    if(node->match_flag||node->max_ptrs!=32)abort();
    unsigned bound=depth==0?(CASE_FAMILIES==2?4:8):depth==1?(CASE_FAMILIES==2?3:5):1;
    if(node->num_ptrs>bound)abort();
    if(node->num_ptrs>1)branching_nodes++;
    unsigned selected[256]={0};
    for(unsigned p=0;p<node->num_ptrs;++p) {
        if(!node->ptrs[p].ptr)abort();
        unsigned nonempty=0;
        for(unsigned b=0;b<256;++b) {
            unsigned bit=(node->ptrs[p].values.bits[b/32]>>(b%32))&1;
            if(bit) {if(selected[b]++)abort();nonempty++;}
        }
        if(!nonempty)abort();
        if(depth<2) {
            /* Each actual label is a union of complete source-domain cells. */
            int cells[16];for(unsigned s=0;s<16;++s)cells[s]=-1;
            for(unsigned b=0;b<256;++b) {
                unsigned sig=membership(b,depth),bit=(node->ptrs[p].values.bits[b/32]>>(b%32))&1;
                if(cells[sig]>=0 && cells[sig]!=(int)bit)abort();cells[sig]=bit;
            }
        }
        check_unfolding(node->ptrs[p].ptr,depth+1);
    }
    if(depth>=2)for(unsigned b=0;b<256;++b)
        if(selected[b]!=(b>=lo[depth]&&b<=hi[depth]))abort();
    (void)index;
}

int main(void)
{
    unsigned n=CASE_RULES;
    const uint64_t r=CASE_FAMILIES==2?148:488,j=CASE_FAMILIES==2?136:448;
    const uint64_t a=1+19*(uint64_t)n+j*(n-1);
    if(initialize(n))return 1;
    if(sigsetjmp(context.pool.fail,0))return 2;
    tb_alloc(&context.pool,0);
    struct tb_mem_block *original=context.pool.block;
    size_t before=original->size;
    memset(&counts,0,sizeof(counts));tracking=1;
    unsigned got=task_dpdk_acl();
    tracking=0;
    if(got!=n||!answer||original!=context.pool.block||original->next)return 3;
    if(counts.node_events>a||counts.free_events>a||counts.duplicate_events>j*(n-1)||
       counts.merge_events>6*(uint64_t)n+r*(n-1)||counts.pool_calls||
       counts.merge_nest_max>r+1||counts.free_nest_max>a||
       counts.merge_depth_max>14||counts.free_depth_max>13||
       counts.live!=(int)context.num_nodes||before-original->size>payload_bound(n))return 4;
    check_unfolding(answer,0);
    if(unique_count!=context.num_nodes || !branching_nodes)return 6;
    /* Count each physical edge once, independently of tree unfolding. */
    for(unsigned i=0;i<unique_count;++i)for(unsigned p=0;p<unique_nodes[i]->num_ptrs;++p)
        incoming[intern(unique_nodes[i]->ptrs[p].ptr)]++;
    for(unsigned i=1;i<unique_count;++i)if(incoming[i]!=unique_nodes[i]->ref_count)return 7;
    uint64_t comparisons=verify_oracle(n);
    printf("{\"status\":\"PASS\",\"F\":%u,\"N\":%u,\"node_events\":%"PRIu64
        ",\"free_events\":%"PRIu64",\"merge_events\":%"PRIu64",\"duplicate_events\":%"PRIu64
        ",\"merge_total_per_nest_max\":%"PRIu64",\"free_total_per_nest_max\":%"PRIu64
        ",\"merge_active_depth_max\":%u,\"free_active_depth_max\":%u,\"live_peak\":%d"
        ",\"final_unique_nodes\":%u,\"final_unfolded_nodes\":%u,\"unfolded_branching_nodes\":%u"
        ",\"fresh_payload\":%zu,\"source_payload_upper\":%zu,\"tb_alloc_calls\":%"PRIu64
        ",\"kernel_refills\":%"PRIu64",\"oracle_comparisons\":%"PRIu64"}\n",
        CASE_FAMILIES,n,counts.node_events,counts.free_events,counts.merge_events,counts.duplicate_events,
        counts.merge_nest_max,counts.free_nest_max,counts.merge_depth_max,counts.free_depth_max,counts.live_max,
        unique_count,unfolded_count,branching_nodes,before-original->size,payload_bound(n),counts.tb_calls,counts.pool_calls,comparisons);
    tb_free_pool(&context.pool);
    return 0;
}
