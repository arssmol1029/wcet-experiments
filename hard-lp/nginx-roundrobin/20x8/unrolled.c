typedef unsigned char Byte;typedef unsigned long uintptr_t;typedef long ngx_int_t;typedef unsigned long ngx_uint_t;typedef long time_t;
#define NULL ((void*)0)
#define ngx_time() 1000
#define NGX_SUPPRESS_WARN 1
typedef struct peer { struct peer *next; ngx_int_t current_weight,effective_weight,weight; ngx_uint_t down,max_fails,fails,max_conns,conns;time_t checked,fail_timeout;} ngx_http_upstream_rr_peer_t;
typedef struct {ngx_http_upstream_rr_peer_t *peer;} peers_t;
typedef struct {peers_t *peers;ngx_http_upstream_rr_peer_t *current;uintptr_t *tried;} ngx_http_upstream_rr_peer_data_t;
Byte input[256],output[4096];unsigned result,bound_failure;

unsigned benchmark_entry(void) { static ngx_http_upstream_rr_peer_t nodes[20]; static uintptr_t tried[2]; static peers_t peers; static ngx_http_upstream_rr_peer_data_t rrp_data; tried[0]=tried[1]=0;peers.peer=nodes;rrp_data.peers=&peers;rrp_data.tried=tried;rrp_data.current=0;
nodes[0].next=&nodes[1];nodes[0].current_weight=(int)input[0]*4+-8;nodes[0].effective_weight=1;nodes[0].weight=1;nodes[0].down=input[3];nodes[0].max_fails=nodes[0].fails=nodes[0].max_conns=nodes[0].conns=0;nodes[0].checked=1000;nodes[0].fail_timeout=10;
nodes[1].next=&nodes[2];nodes[1].current_weight=(int)input[1]*4+-1;nodes[1].effective_weight=2;nodes[1].weight=2;nodes[1].down=input[4];nodes[1].max_fails=nodes[1].fails=nodes[1].max_conns=nodes[1].conns=0;nodes[1].checked=1000;nodes[1].fail_timeout=10;
nodes[2].next=&nodes[3];nodes[2].current_weight=(int)input[2]*4+6;nodes[2].effective_weight=3;nodes[2].weight=3;nodes[2].down=input[5];nodes[2].max_fails=nodes[2].fails=nodes[2].max_conns=nodes[2].conns=0;nodes[2].checked=1000;nodes[2].fail_timeout=10;
nodes[3].next=&nodes[4];nodes[3].current_weight=(int)input[3]*4+-4;nodes[3].effective_weight=1;nodes[3].weight=1;nodes[3].down=input[6];nodes[3].max_fails=nodes[3].fails=nodes[3].max_conns=nodes[3].conns=0;nodes[3].checked=1000;nodes[3].fail_timeout=10;
nodes[4].next=&nodes[5];nodes[4].current_weight=(int)input[4]*4+3;nodes[4].effective_weight=2;nodes[4].weight=2;nodes[4].down=input[7];nodes[4].max_fails=nodes[4].fails=nodes[4].max_conns=nodes[4].conns=0;nodes[4].checked=1000;nodes[4].fail_timeout=10;
nodes[5].next=&nodes[6];nodes[5].current_weight=(int)input[5]*4+-7;nodes[5].effective_weight=3;nodes[5].weight=3;nodes[5].down=input[0];nodes[5].max_fails=nodes[5].fails=nodes[5].max_conns=nodes[5].conns=0;nodes[5].checked=1000;nodes[5].fail_timeout=10;
nodes[6].next=&nodes[7];nodes[6].current_weight=(int)input[6]*4+0;nodes[6].effective_weight=1;nodes[6].weight=1;nodes[6].down=input[1];nodes[6].max_fails=nodes[6].fails=nodes[6].max_conns=nodes[6].conns=0;nodes[6].checked=1000;nodes[6].fail_timeout=10;
nodes[7].next=&nodes[8];nodes[7].current_weight=(int)input[7]*4+7;nodes[7].effective_weight=2;nodes[7].weight=2;nodes[7].down=input[2];nodes[7].max_fails=nodes[7].fails=nodes[7].max_conns=nodes[7].conns=0;nodes[7].checked=1000;nodes[7].fail_timeout=10;
nodes[8].next=&nodes[9];nodes[8].current_weight=(int)input[0]*4+-3;nodes[8].effective_weight=3;nodes[8].weight=3;nodes[8].down=input[3];nodes[8].max_fails=nodes[8].fails=nodes[8].max_conns=nodes[8].conns=0;nodes[8].checked=1000;nodes[8].fail_timeout=10;
nodes[9].next=&nodes[10];nodes[9].current_weight=(int)input[1]*4+4;nodes[9].effective_weight=1;nodes[9].weight=1;nodes[9].down=input[4];nodes[9].max_fails=nodes[9].fails=nodes[9].max_conns=nodes[9].conns=0;nodes[9].checked=1000;nodes[9].fail_timeout=10;
nodes[10].next=&nodes[11];nodes[10].current_weight=(int)input[2]*4+-6;nodes[10].effective_weight=2;nodes[10].weight=2;nodes[10].down=input[5];nodes[10].max_fails=nodes[10].fails=nodes[10].max_conns=nodes[10].conns=0;nodes[10].checked=1000;nodes[10].fail_timeout=10;
nodes[11].next=&nodes[12];nodes[11].current_weight=(int)input[3]*4+1;nodes[11].effective_weight=3;nodes[11].weight=3;nodes[11].down=input[6];nodes[11].max_fails=nodes[11].fails=nodes[11].max_conns=nodes[11].conns=0;nodes[11].checked=1000;nodes[11].fail_timeout=10;
nodes[12].next=&nodes[13];nodes[12].current_weight=(int)input[4]*4+8;nodes[12].effective_weight=1;nodes[12].weight=1;nodes[12].down=input[7];nodes[12].max_fails=nodes[12].fails=nodes[12].max_conns=nodes[12].conns=0;nodes[12].checked=1000;nodes[12].fail_timeout=10;
nodes[13].next=&nodes[14];nodes[13].current_weight=(int)input[5]*4+-2;nodes[13].effective_weight=2;nodes[13].weight=2;nodes[13].down=input[0];nodes[13].max_fails=nodes[13].fails=nodes[13].max_conns=nodes[13].conns=0;nodes[13].checked=1000;nodes[13].fail_timeout=10;
nodes[14].next=&nodes[15];nodes[14].current_weight=(int)input[6]*4+5;nodes[14].effective_weight=3;nodes[14].weight=3;nodes[14].down=input[1];nodes[14].max_fails=nodes[14].fails=nodes[14].max_conns=nodes[14].conns=0;nodes[14].checked=1000;nodes[14].fail_timeout=10;
nodes[15].next=&nodes[16];nodes[15].current_weight=(int)input[7]*4+-5;nodes[15].effective_weight=1;nodes[15].weight=1;nodes[15].down=input[2];nodes[15].max_fails=nodes[15].fails=nodes[15].max_conns=nodes[15].conns=0;nodes[15].checked=1000;nodes[15].fail_timeout=10;
nodes[16].next=&nodes[17];nodes[16].current_weight=(int)input[0]*4+2;nodes[16].effective_weight=2;nodes[16].weight=2;nodes[16].down=input[3];nodes[16].max_fails=nodes[16].fails=nodes[16].max_conns=nodes[16].conns=0;nodes[16].checked=1000;nodes[16].fail_timeout=10;
nodes[17].next=&nodes[18];nodes[17].current_weight=(int)input[1]*4+-8;nodes[17].effective_weight=3;nodes[17].weight=3;nodes[17].down=input[4];nodes[17].max_fails=nodes[17].fails=nodes[17].max_conns=nodes[17].conns=0;nodes[17].checked=1000;nodes[17].fail_timeout=10;
nodes[18].next=&nodes[19];nodes[18].current_weight=(int)input[2]*4+-1;nodes[18].effective_weight=1;nodes[18].weight=1;nodes[18].down=input[5];nodes[18].max_fails=nodes[18].fails=nodes[18].max_conns=nodes[18].conns=0;nodes[18].checked=1000;nodes[18].fail_timeout=10;
nodes[19].next=NULL;nodes[19].current_weight=(int)input[3]*4+6;nodes[19].effective_weight=2;nodes[19].weight=2;nodes[19].down=input[6];nodes[19].max_fails=nodes[19].fails=nodes[19].max_conns=nodes[19].conns=0;nodes[19].checked=1000;nodes[19].fail_timeout=10;
ngx_http_upstream_rr_peer_t *selected;{ ngx_http_upstream_rr_peer_data_t *rrp=&rrp_data;
    time_t                        now;
    uintptr_t                     m;
    ngx_int_t                     total;
    ngx_uint_t                    i, n, p;
    ngx_http_upstream_rr_peer_t  *peer, *best;

    now = ngx_time();

    best = NULL;
    total = 0;

#if (NGX_SUPPRESS_WARN)
    p = 0;
#endif

    peer = rrp->peers->peer; i = 0;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_0;
        }

        if (peer->down) {
            goto next_0;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_0;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_0;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_0:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_1;
        }

        if (peer->down) {
            goto next_1;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_1;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_1;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_1:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_2;
        }

        if (peer->down) {
            goto next_2;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_2;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_2;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_2:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_3;
        }

        if (peer->down) {
            goto next_3;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_3;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_3;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_3:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_4;
        }

        if (peer->down) {
            goto next_4;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_4;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_4;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_4:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_5;
        }

        if (peer->down) {
            goto next_5;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_5;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_5;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_5:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_6;
        }

        if (peer->down) {
            goto next_6;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_6;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_6;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_6:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_7;
        }

        if (peer->down) {
            goto next_7;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_7;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_7;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_7:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_8;
        }

        if (peer->down) {
            goto next_8;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_8;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_8;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_8:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_9;
        }

        if (peer->down) {
            goto next_9;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_9;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_9;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_9:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_10;
        }

        if (peer->down) {
            goto next_10;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_10;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_10;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_10:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_11;
        }

        if (peer->down) {
            goto next_11;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_11;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_11;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_11:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_12;
        }

        if (peer->down) {
            goto next_12;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_12;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_12;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_12:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_13;
        }

        if (peer->down) {
            goto next_13;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_13;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_13;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_13:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_14;
        }

        if (peer->down) {
            goto next_14;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_14;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_14;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_14:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_15;
        }

        if (peer->down) {
            goto next_15;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_15;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_15;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_15:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_16;
        }

        if (peer->down) {
            goto next_16;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_16;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_16;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_16:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_17;
        }

        if (peer->down) {
            goto next_17;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_17;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_17;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_17:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_18;
        }

        if (peer->down) {
            goto next_18;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_18;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_18;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_18:
    peer = peer->next; i++;
    if (!peer) goto after_loop;
    {

        n = i / (8 * sizeof(uintptr_t));
        m = (uintptr_t) 1 << i % (8 * sizeof(uintptr_t));

        if (rrp->tried[n] & m) {
            goto next_19;
        }

        if (peer->down) {
            goto next_19;
        }

        if (peer->max_fails
            && peer->fails >= peer->max_fails
            && now - peer->checked <= peer->fail_timeout)
        {
            goto next_19;
        }

        if (peer->max_conns && peer->conns >= peer->max_conns) {
            goto next_19;
        }

        peer->current_weight += peer->effective_weight;
        total += peer->effective_weight;

        if (peer->effective_weight < peer->weight) {
            peer->effective_weight++;
        }

        if (best == NULL || peer->current_weight > best->current_weight) {
            best = peer;
            p = i;
        }

    }
next_19:
    peer = peer->next; i++;
after_loop: ;

    if (best == NULL) {
        {selected=NULL;goto inline_done;}
    }

    rrp->current = best;

    n = p / (8 * sizeof(uintptr_t));
    m = (uintptr_t) 1 << p % (8 * sizeof(uintptr_t));

    rrp->tried[n] |= m;

    best->current_weight -= total;

    if (now - best->checked > best->fail_timeout) {
        best->checked = now;
    }

    {selected=best;goto inline_done;}

inline_done: ;} ngx_http_upstream_rr_peer_t *best=selected;
output[0]=(Byte)nodes[0].current_weight;output[1]=(Byte)nodes[0].effective_weight;
output[2]=(Byte)nodes[1].current_weight;output[3]=(Byte)nodes[1].effective_weight;
output[4]=(Byte)nodes[2].current_weight;output[5]=(Byte)nodes[2].effective_weight;
output[6]=(Byte)nodes[3].current_weight;output[7]=(Byte)nodes[3].effective_weight;
output[8]=(Byte)nodes[4].current_weight;output[9]=(Byte)nodes[4].effective_weight;
output[10]=(Byte)nodes[5].current_weight;output[11]=(Byte)nodes[5].effective_weight;
output[12]=(Byte)nodes[6].current_weight;output[13]=(Byte)nodes[6].effective_weight;
output[14]=(Byte)nodes[7].current_weight;output[15]=(Byte)nodes[7].effective_weight;
output[16]=(Byte)nodes[8].current_weight;output[17]=(Byte)nodes[8].effective_weight;
output[18]=(Byte)nodes[9].current_weight;output[19]=(Byte)nodes[9].effective_weight;
output[20]=(Byte)nodes[10].current_weight;output[21]=(Byte)nodes[10].effective_weight;
output[22]=(Byte)nodes[11].current_weight;output[23]=(Byte)nodes[11].effective_weight;
output[24]=(Byte)nodes[12].current_weight;output[25]=(Byte)nodes[12].effective_weight;
output[26]=(Byte)nodes[13].current_weight;output[27]=(Byte)nodes[13].effective_weight;
output[28]=(Byte)nodes[14].current_weight;output[29]=(Byte)nodes[14].effective_weight;
output[30]=(Byte)nodes[15].current_weight;output[31]=(Byte)nodes[15].effective_weight;
output[32]=(Byte)nodes[16].current_weight;output[33]=(Byte)nodes[16].effective_weight;
output[34]=(Byte)nodes[17].current_weight;output[35]=(Byte)nodes[17].effective_weight;
output[36]=(Byte)nodes[18].current_weight;output[37]=(Byte)nodes[18].effective_weight;
output[38]=(Byte)nodes[19].current_weight;output[39]=(Byte)nodes[19].effective_weight;
return best ? (unsigned)(best-nodes)+1:0; }
