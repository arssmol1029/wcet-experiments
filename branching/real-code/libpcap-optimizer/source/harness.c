/* Upstream optimizer is included unchanged to expose its static pass. */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libpcap-libpcap-1.10.5/optimize.c"
#include "fixture.h"

__attribute__((noinline)) void bench_kernel(void)
{
    /* Exactly one upstream statement-optimization iteration, no fixed point. */
    find_levels(&fixture_state, &fixture_ic);
    find_dom(&fixture_state, fixture_ic.root);
    find_closure(&fixture_state, fixture_ic.root);
    find_ud(&fixture_state, fixture_ic.root);
    find_edom(&fixture_state, fixture_ic.root);
    opt_blks(&fixture_state, &fixture_ic, 1);
}

#ifdef NATIVE_TEST
static uint32_t interpret(uint32_t packet)
{
    struct block *b = fixture_ic.root;
    uint32_t acc = 0;
    for (unsigned visited=0; visited<CASE_BLOCKS; ++visited) {
        for (struct slist *s=b->stmts; s; s=s->next) {
            switch (s->s.code) {
            case NOP: break;
            case BPF_LD|BPF_H|BPF_ABS: acc=packet; break;
            case BPF_LD|BPF_W|BPF_IMM: acc=s->s.k; break;
            case BPF_ALU|BPF_ADD|BPF_K: acc+=s->s.k; break;
            case BPF_ALU|BPF_AND|BPF_K: acc&=s->s.k; break;
            default: fprintf(stderr,"unexpected opcode %d\n",s->s.code); abort();
            }
        }
        if (b->s.code==(BPF_RET|BPF_K)) return b->s.k;
        if (b->s.code!=(BPF_JMP|BPF_JEQ|BPF_K)) abort();
        b=(acc==b->s.k) ? JT(b) : JF(b);
    }
    abort();
}

int main(void)
{
    static unsigned char expected[65536];
    for (unsigned p=0;p<65536;++p) expected[p]=(interpret(p)!=0);
    bench_kernel();
    for (unsigned p=0;p<65536;++p) {
        unsigned oracle=0;
        for (unsigned i=0;i<CASE_TESTS;++i)
            if (((p+i%16)&65535u)==257u*i+7u) oracle=1;
        if ((interpret(p)!=0)!=expected[p] || oracle!=expected[p]) {
            fprintf(stderr,"mismatch packet=%u before=%u after=%u oracle=%u\n",p,expected[p],interpret(p)!=0,oracle);
            return 1;
        }
    }
    if (fixture_state.curval>=CASE_MAXVAL) return 2;
    printf("PASS blocks=%u packets=65536 value_nodes=%u capacity=%u\n",
           CASE_BLOCKS,fixture_state.curval,CASE_MAXVAL);
    return 0;
}
#else
int main(void) { bench_kernel(); return 0; }
#endif
