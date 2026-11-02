/* Counted portable C environment for ARM; no algorithmic call is omitted. */
#include <stddef.h>
#include <stdint.h>

void *memset(void *dst, int c, size_t n)
{
    unsigned char *p=dst;
    for (size_t i=0;i<n;++i) p[i]=(unsigned char)c;
    return dst;
}
void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d=dst;
    const unsigned char *s=src;
    for (size_t i=0;i<n;++i) d[i]=s[i];
    return dst;
}
/* AAPCS32 UIDIVMOD: quotient in r0, remainder in r1, matching uint64_t. */
uint64_t __aeabi_uidivmod(uint32_t n, uint32_t d)
{
    uint32_t q=0,r=0;
    if (d==0) return 0; /* Outside the valid C-division input domain. */
    for (int bit=31;bit>=0;--bit) {
        uint32_t carry=r>>31;
        r=(r<<1)|((n>>(unsigned)bit)&1u);
        if (carry || r>=d) {r-=d; q|=1u<<(unsigned)bit;}
    }
    return ((uint64_t)r<<32)|q;
}
uint32_t __aeabi_uidiv(uint32_t n,uint32_t d)
{
    return (uint32_t)__aeabi_uidivmod(n,d);
}

/* AAPCS32: quotient r0, remainder r1. Valid domain: denominator != 0,
 * excluding INT_MIN/-1, exactly the defined domain of C signed division. */
uint64_t __aeabi_idivmod(int32_t n, int32_t d)
{
    uint32_t un=n<0 ? 0u-(uint32_t)n : (uint32_t)n;
    uint32_t ud=d<0 ? 0u-(uint32_t)d : (uint32_t)d;
    uint64_t both=__aeabi_uidivmod(un,ud);
    uint32_t q=(uint32_t)both, r=(uint32_t)(both>>32);
    if ((n<0)!=(d<0)) q=0u-q;
    if (n<0) r=0u-r;
    return ((uint64_t)r<<32)|q;
}
int32_t __aeabi_idiv(int32_t n, int32_t d)
{
    return (int32_t)(uint32_t)__aeabi_idivmod(n,d);
}
