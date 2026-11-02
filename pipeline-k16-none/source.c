/* ============================================================
 *  Network processing pipeline — single packet, no MPLS
 *
 *  Stages:
 *    L2-L3 header extraction  (Ethernet / VLAN)
 *    Classification           (VLAN tbl -> MAC-DST via cuckoo)
 *    Modification             (VLAN add / replace / delete)
 *
 *  Classification priority (first match wins):
 *      1) VLAN   (VID, or -2 for untagged)
 *      2) MAC-DST (only if VLAN produced no rule)
 *
 *  MAC-SRC learning always runs at ingress.
 *
 *  Constraints:
 *    - only int as simple type
 *    - no includes, no library functions
 *    - no pointer arithmetic (array subscripting only)
 *    - one-dimensional arrays everywhere
 *    - sizes set by #define
 *    - MAC stored as last 3 octets (vendor part stripped)
 *    - packet is assumed to be pre-initialized externally
 *
 *  Dead header fields (never read anywhere in the program)
 *  have been removed together with the code that wrote them.
 * ============================================================ */

/* ---------- configuration ---------- */
#define PACKET_SIZE      160

#define MAC_TABLE_SIZE   64
#define VLAN_TABLE_SIZE  32

#define MAC_MAX_KICKS    16
#define VLAN_MAX_KICKS   16

#define EMPTY_KEY        (-1)

/* ---------- structs (only fields that are read remain) ---------- */
struct field { int key; int value; };

struct eth_header  { int dst_mac; int src_mac; };
struct vlan_header { int vid; };

struct packet_headers {
    struct eth_header  eth;
    int                vlan_present;
    struct vlan_header vlan;
};

struct classify_result {
    int dst_port;          /* -1 = flood (output of MAC-DST lookup) */
    int vlan_action;       /* 0=none,1=add,2=replace,3=delete        */
    int vlan_new_id;
};

/* ---------- single-packet global state ---------- */
int pkt_data[PACKET_SIZE];
int pkt_len;

struct packet_headers hdr;
struct classify_result cres;

/* cuckoo tables */
struct field mac_table [2 * MAC_TABLE_SIZE];
struct field vlan_table[2 * VLAN_TABLE_SIZE];

/* observable results */
int out_vlan;
int pkt_ok;

/* ============================================================
 *  HASH FUNCTIONS
 * ============================================================ */
int hash1(int key, int n) {
    int h = ((key % n) * 31 + 17) % n;
    if (h < 0) h += n;
    return h;
}

int hash2(int key, int n) {
    int h = ((key % n) * 131 + 71) % n;
    if (h < 0) h += n;
    return h;
}

/* ============================================================
 *  CUCKOO TABLE OPS
 * ============================================================ */
int mac_lookup(int key) {
    int p1 = hash1(key, MAC_TABLE_SIZE);
    int p2 = MAC_TABLE_SIZE + hash2(key, MAC_TABLE_SIZE);
    if (mac_table[p1].key == key) return mac_table[p1].value;
    if (mac_table[p2].key == key) return mac_table[p2].value;
    return -1;
}

int mac_insert(int key, int value) {
    int n = MAC_TABLE_SIZE;
    int p1 = hash1(key, n);
    int p2 = n + hash2(key, n);
    int pos, ck, cv, i, tk, tv;
    if (mac_table[p1].key == key) { mac_table[p1].value = value; return 0; }
    if (mac_table[p2].key == key) { mac_table[p2].value = value; return 0; }
    if (mac_table[p1].key == EMPTY_KEY) { mac_table[p1].key = key; mac_table[p1].value = value; return 0; }
    if (mac_table[p2].key == EMPTY_KEY) { mac_table[p2].key = key; mac_table[p2].value = value; return 0; }
    ck = key; cv = value; pos = p1;
    for (i = 0; i < MAC_MAX_KICKS; i++) {
        tk = mac_table[pos].key; tv = mac_table[pos].value;
        mac_table[pos].key = ck;  mac_table[pos].value = cv;
        ck = tk; cv = tv;
        if (pos < n) pos = n + hash2(ck, n);
        else         pos = hash1(ck, n);
        if (mac_table[pos].key == EMPTY_KEY) {
            mac_table[pos].key = ck; mac_table[pos].value = cv; return 0;
        }
    }
    return -1;
}

int vlan_lookup(int key) {
    int p1 = hash1(key, VLAN_TABLE_SIZE);
    int p2 = VLAN_TABLE_SIZE + hash2(key, VLAN_TABLE_SIZE);
    if (vlan_table[p1].key == key) return vlan_table[p1].value;
    if (vlan_table[p2].key == key) return vlan_table[p2].value;
    return -1;
}

int vlan_insert(int key, int value) {
    int n = VLAN_TABLE_SIZE;
    int p1 = hash1(key, n);
    int p2 = n + hash2(key, n);
    int pos, ck, cv, i, tk, tv;
    if (vlan_table[p1].key == key) { vlan_table[p1].value = value; return 0; }
    if (vlan_table[p2].key == key) { vlan_table[p2].value = value; return 0; }
    if (vlan_table[p1].key == EMPTY_KEY) { vlan_table[p1].key = key; vlan_table[p1].value = value; return 0; }
    if (vlan_table[p2].key == EMPTY_KEY) { vlan_table[p2].key = key; vlan_table[p2].value = value; return 0; }
    ck = key; cv = value; pos = p1;
    for (i = 0; i < VLAN_MAX_KICKS; i++) {
        tk = vlan_table[pos].key; tv = vlan_table[pos].value;
        vlan_table[pos].key = ck;  vlan_table[pos].value = cv;
        ck = tk; cv = tv;
        if (pos < n) pos = n + hash2(ck, n);
        else         pos = hash1(ck, n);
        if (vlan_table[pos].key == EMPTY_KEY) {
            vlan_table[pos].key = ck; vlan_table[pos].value = cv; return 0;
        }
    }
    return -1;
}

/* ============================================================
 *  PACKET HELPERS
 * ============================================================ */
int pkt_byte(int off) { return pkt_data[off]; }

int pkt_shift_right(int from, int n) {
    int i;
    if (pkt_len + n > PACKET_SIZE) return -1;
    for (i = pkt_len - 1; i >= from; i--)
        pkt_data[i + n] = pkt_data[i];
    pkt_len += n;
    return 0;
}

void pkt_shift_left(int from, int n) {
    int i;
    for (i = from; i < pkt_len; i++)
        pkt_data[i] = pkt_data[i + n];
    pkt_len -= n;
}

/* ============================================================
 *  STEP 1 — HEADER EXTRACTION (L2 + VLAN only)
 *  IPv4 parsing was removed: none of its fields were read.
 * ============================================================ */
void extract_headers(void) {
    hdr.eth.dst_mac = (pkt_byte(3) << 16) | (pkt_byte(4) << 8) | pkt_byte(5);
    hdr.eth.src_mac = (pkt_byte(9) << 16) | (pkt_byte(10) << 8) | pkt_byte(11);

    if (((pkt_byte(12) << 8) | pkt_byte(13)) == 0x8100) {
        hdr.vlan_present = 1;
        hdr.vlan.vid = ((pkt_byte(14) << 8) | pkt_byte(15)) & 0xfff;
    } else {
        hdr.vlan_present = 0;
        hdr.vlan.vid = 0;
    }
}

/* ============================================================
 *  STEP 2 — CLASSIFICATION
 *  Priority: VLAN -> MAC-DST
 *  MAC-SRC learning always runs first.
 * ============================================================ */
void classify(void) {
    int v;
    int matched = 0;

    /* ingress: always learn source MAC */
    mac_insert(hdr.eth.src_mac, 1);

    /* output default: flood */
    cres.dst_port    = -1;
    cres.vlan_action = 0;
    cres.vlan_new_id = 0;

    /* --- priority 1: VLAN --- */
    if (hdr.vlan_present) v = vlan_lookup(hdr.vlan.vid);
    else                  v = vlan_lookup(-2);       /* key: untagged */

    if (v >= 0) {
        cres.vlan_action =  v        & 0xf;
        cres.vlan_new_id = (v >> 4) & 0xfff;
        if (cres.vlan_action != 0) matched = 1;
    }

    /* --- priority 2: MAC-DST (only if VLAN did not classify) --- */
    if (matched == 0) {
        v = mac_lookup(hdr.eth.dst_mac);
        if (v >= 0) cres.dst_port = v;
    }
}

/* ============================================================
 *  STEP 3 — VLAN MODIFICATION
 * ============================================================ */
void modify_vlan(void) {
    int tci, act = cres.vlan_action;

    if (act == 1 && !hdr.vlan_present) {
        tci = cres.vlan_new_id & 0xfff;
        if (pkt_shift_right(12, 4) != 0) return;
        pkt_data[12] = 0x81;
        pkt_data[13] = 0x00;
        pkt_data[14] = (tci >> 8) & 0xff;
        pkt_data[15] =  tci       & 0xff;
        hdr.vlan_present = 1;
        hdr.vlan.vid = cres.vlan_new_id;

    } else if (act == 2 && hdr.vlan_present) {
        tci = cres.vlan_new_id & 0xfff;
        pkt_data[14] = (tci >> 8) & 0xff;
        pkt_data[15] =  tci       & 0xff;
        hdr.vlan.vid = cres.vlan_new_id;

    } else if (act == 3 && hdr.vlan_present) {
        pkt_shift_left(12, 4);
        hdr.vlan_present = 0;
        hdr.vlan.vid = 0;
    }
}

/* ============================================================
 *  PROCESS THE PACKET
 * ============================================================ */
int process_packet(void) {
    if (pkt_len <= 0)              return -1;
    if (pkt_len > PACKET_SIZE)     return -1;
    if (pkt_len < 14)              return -1;
    if (pkt_len + 4 > PACKET_SIZE) return -1;   /* VLAN push headroom */

    extract_headers();
    classify();
    modify_vlan();

    out_vlan = hdr.vlan_present ? hdr.vlan.vid : 0;
    return 0;
}

/* ============================================================
 *  PIPELINE
 * ============================================================ */
void pipeline(void) {
    pkt_ok = 0;
    if (process_packet() == 0) pkt_ok = 1;
    else                       pkt_len = 0;
}

/* ============================================================
 *  INITIALISATION
 *  Packet data (pkt_data / pkt_len) is external — not touched.
 * ============================================================ */
void init_tables(void) {
    int i;
    for (i = 0; i < 2 * MAC_TABLE_SIZE;  i++) { mac_table [i].key = EMPTY_KEY; mac_table [i].value = 0; }
    for (i = 0; i < 2 * VLAN_TABLE_SIZE; i++) { vlan_table[i].key = EMPTY_KEY; vlan_table[i].value = 0; }
}

void init_rules(void) {
    mac_insert(0xddee01, 2);              /* dst MAC -> port 2 */
    vlan_insert(-2,  1 | (300 << 4));     /* untagged -> push 300 */
    vlan_insert(100, 2 | (200 << 4));     /* VID 100 -> replace 200 */
}

void init_all(void) {
    out_vlan = 0;
    pkt_ok   = 0;
    init_tables();
    init_rules();
}

/* ============================================================
 *  ENTRY POINT
 * ============================================================ */
int main(void) {
    init_all();
    pipeline();
    return 0;
}