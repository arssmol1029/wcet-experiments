#include <config.h>
#include <sys/types.h>
#include <stdint.h>
#include <pcap/bpf.h>

extern u_int pcapint_filter(const struct bpf_insn *,const u_char *,u_int,u_int);
#ifndef CASCADE_POLICY_INCLUDE
#define CASCADE_POLICY_INCLUDE "cascade-monitored-profiles/triangle/policies.inc"
#endif
#ifndef CASCADE_CALLS_INCLUDE
#define CASCADE_CALLS_INCLUDE "cascade-monitored-profiles/triangle/calls.inc"
#endif
#include CASCADE_POLICY_INCLUDE

_Alignas(4) unsigned char cascade_packet[128];
volatile unsigned cascade_accepted;
volatile unsigned cascade_anchor_positive[CASCADE_VERTICES];

/* A normal conjunction of two userland capture policies; all code is counted. */
extern void record_accepted(void);
extern void record_anchor(unsigned);
__attribute__((noinline)) unsigned task_libpcap_cascade(void)
{
#include CASCADE_CALLS_INCLUDE
    return cascade_accepted;
}

#ifdef STANDALONE
int main(void)
{
    return task_libpcap_cascade() > CASCADE_POLICY_PAIRS;
}
#endif
