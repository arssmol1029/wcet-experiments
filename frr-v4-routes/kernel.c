/* Harness for the supplied SYNTHETIC adaptation; original code is unchanged. */
#include "source.c"

void benchmark_init(unsigned variant)
{
    rmap = variant == 2 ? 0 : 17;
    vrf.status = 1;
    for (int afi = 0; afi < AFI_MAX; ++afi) {
        for (int type = 0; type <= ZEBRA_ROUTE_MAX; ++type) {
            vrf.info.proto_rm[afi][type].name = 200 + type;
            vrf.info.proto_rm[afi][type].map.name = 200 + type;
            vrf.info.proto_rm[afi][type].map.use_count = 2;
            vrf.info.nht_rm[afi][type].name = type % 3 == 0 ? 17 : 18;
            vrf.info.nht_rm[afi][type].map.name = type % 3 == 0 ? 17 : 18;
            vrf.info.nht_rm[afi][type].map.use_count = type % 2 ? 7 : 0;
        }
        for (int safi = 0; safi < SAFI_MAX; ++safi) {
            vrf.info.table[afi][safi].status = 1;
            for (int nh = 0; nh < NEXT_HOPS_MAX_NUM; ++nh)
                vrf.info.table[afi][safi].next_hops[nh].status = 10 + nh;
        }
    }
    if (variant == 1)
        rmap = 91; /* nonzero, absent policy: no matching map */
}

void benchmark_run_current(void)
{
    zebra_nht_rm_update();
}

/* Self-contained synthetic control: initialization is part of this task. */
void benchmark_entry(void)
{
    benchmark_init(0);
    benchmark_run_current();
}

#ifdef BENCHMARK_STANDALONE
int main(void)
{
    benchmark_entry();
    return zvrf.nht_rm[AFI_IP][0].map.use_count == 1 ? 0 : 1;
}
#endif
