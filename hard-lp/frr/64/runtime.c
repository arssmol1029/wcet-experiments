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
