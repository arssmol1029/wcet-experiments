#define REPEAT_LOOP_2(DO) DO(0); DO(1); DO(2); DO(3); DO(4); DO(5); DO(6); DO(7); DO(8); DO(9); DO(10); DO(11); DO(12); DO(13); DO(14); DO(15); DO(16); DO(17); DO(18); DO(19); DO(20); DO(21); DO(22); DO(23); DO(24); DO(25); DO(26); DO(27); DO(28); DO(29); DO(30); DO(31); DO(32); DO(33);
#define UNROLL_LOOP_2(k) do { if (i <= ZEBRA_ROUTE_MAX) { rmap_name = NHT_RM_NAME(zvrf, AFI_IP, i); if (rmap_name && rmap_name == rmap) { old = NHT_RM_MAP(zvrf, AFI_IP, i); if (!old.use_count) route_map_counter_increment( &NHT_RM_MAP(zvrf, AFI_IP, i)); if (afi_ip == 0) { table = zvrf.table[AFI_IP] [SAFI_UNICAST]; afi_ip = 1; zebra_evaluate_rnh( &zvrf, vrf_id, AFI_IP, 1, 0, SAFI_UNICAST); } } rmap_name = NHT_RM_NAME(zvrf, AFI_IP6, i); if (rmap_name && (rmap_name == rmap)) { old = NHT_RM_MAP(zvrf, AFI_IP6, i); if (!old.use_count) route_map_counter_increment( &NHT_RM_MAP(zvrf, AFI_IP6, i)); if (afi_ipv6 == 0) { table = zvrf.table[AFI_IP6] [SAFI_UNICAST]; afi_ipv6 = 1; zebra_evaluate_rnh( &zvrf, vrf_id, AFI_IP6, 1, 0, SAFI_UNICAST); } } _placeholder = 447; i++; } } while (0)
#define REPEAT_LOOP_1(DO) DO(0); DO(1); DO(2); DO(3);
#define UNROLL_LOOP_1(k) do { if (vrf_id < NUM_VRFS) { zvrf = vrf.info; do { i = 0; REPEAT_LOOP_2(UNROLL_LOOP_2) } while (0); vrf_id++; } } while (0)
#define REPEAT_LOOP_0(DO) DO(0); DO(1); DO(2); DO(3);
#define UNROLL_LOOP_0(k) do { if (i < NEXT_HOPS_MAX_NUM) { zvrf->table[afi][safi].next_hops[i].status = 1; i++; } } while (0)
#define ZEBRA_ROUTE_MAX 33// Maximum 33
#define NUM_VRFS        4 // Can be any number
#define NEXT_HOPS_MAX_NUM 4

struct vrf vrf; // 643
struct zebra_vrf zvrf; // 642
int rmap; // INT

// Count size in blocks of 4 bytes

struct next_hop { // 1
    int status;
};

typedef enum {
	AFI_IP = 1,
	AFI_IP6 = 2,
	AFI_MAX = 3
} afi_t;

/* Subsequent Address Family Identifier. */
typedef enum {
	SAFI_UNICAST = 1,
	SAFI_MAX = 2
} safi_t;

struct route_table{ // 1 + 1 * NEXT_HOPS_MAX_NUM = 5
    int status;
    struct next_hop next_hops[NEXT_HOPS_MAX_NUM]; // 1 * NEXT_HOPS_MAX_NUM
};

struct route_map{ // 2
    int name;
    int use_count;
};

struct zebra_rmap{  // 3
	int name;
	struct route_map map;
};

struct zebra_vrf { //642
	struct zebra_rmap proto_rm[AFI_MAX][ZEBRA_ROUTE_MAX + 1]; // 3 * 3 * (ZEBRA_ROUTE_MAX + 1) = 306
	struct zebra_rmap nht_rm[AFI_MAX][ZEBRA_ROUTE_MAX + 1]; // 3 * 3 * (ZEBRA_ROUTE_MAX + 1) = 306
	struct route_table table[AFI_MAX][SAFI_MAX]; // 3 * 2 * 5 = 30
};

struct vrf { // 49
	/* Zebra internal VRF status */
	int status;
	struct zebra_vrf info;
};

void route_map_counter_increment(struct route_map *map)
{
	if (map)
		map->use_count++;
}

void zebra_evaluate_rnh(struct zebra_vrf *zvrf, int vrf_id, afi_t afi, int force,
			int p, safi_t safi)
{
    do { int i = 0; REPEAT_LOOP_0(UNROLL_LOOP_0) } while (0);
}

#define PROTO_RM_NAME(zvrf, afi, rtype) zvrf.proto_rm[afi][rtype].name
#define NHT_RM_NAME(zvrf, afi, rtype) zvrf.nht_rm[afi][rtype].name
#define PROTO_RM_MAP(zvrf, afi, rtype) zvrf.proto_rm[afi][rtype].map
#define NHT_RM_MAP(zvrf, afi, rtype) zvrf.nht_rm[afi][rtype].map


void zebra_nht_rm_update()
{
	int i = 0;
	struct route_table table;
	int rmap_name;
	int afi_ip = 0;
	int afi_ipv6 = 0;
	struct route_map old;
	int _placeholder = 0;

        do { int vrf_id = 0; REPEAT_LOOP_1(UNROLL_LOOP_1) } while (0);
}
