/* Actual byte semantics. n is not clipped. Caller-derived bounds are pending.
 * Separate TU: -fno-builtin -fno-tree-loop-distribute-patterns prevents libc
 * recognition from replacing these bodies with recursive self-calls. */
#include <stddef.h>
#include <stdint.h>
__attribute__((noinline)) void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d=dst;const unsigned char *s=src;
    for (size_t i=0;i<n;i++) d[i]=s[i];
    return dst;
}
__attribute__((noinline)) void *memset(void *dst, int value, size_t n)
{
    unsigned char *d=dst;
    for (size_t i=0;i<n;i++) d[i]=(unsigned char)value;
    return dst;
}
__attribute__((noinline)) int memcmp(const void *left, const void *right, size_t n)
{
    const unsigned char *a=left,*b=right;
    for (size_t i=0;i<n;i++) if(a[i]!=b[i]) return (int)a[i]-(int)b[i];
    return 0;
}
__attribute__((noinline)) void *memmove(void *dst, const void *src, size_t n)
{
    unsigned char *d=dst;const unsigned char *s=src;
    if ((uintptr_t)d<(uintptr_t)s) {for(size_t i=0;i<n;i++)d[i]=s[i];}
    else {for(size_t i=n;i>0;i--)d[i-1]=s[i-1];}
    return dst;
}
void __aeabi_memcpy(void*d,const void*s,size_t n){memcpy(d,s,n);}
void __aeabi_memcpy4(void*d,const void*s,size_t n){memcpy(d,s,n);}
void __aeabi_memcpy8(void*d,const void*s,size_t n){memcpy(d,s,n);}
void __aeabi_memmove(void*d,const void*s,size_t n){memmove(d,s,n);}
void __aeabi_memmove4(void*d,const void*s,size_t n){memmove(d,s,n);}
void __aeabi_memmove8(void*d,const void*s,size_t n){memmove(d,s,n);}
void __aeabi_memset(void*d,size_t n,int c){memset(d,c,n);}
void __aeabi_memset4(void*d,size_t n,int c){memset(d,c,n);}
void __aeabi_memset8(void*d,size_t n,int c){memset(d,c,n);}
void __aeabi_memclr(void*d,size_t n){memset(d,0,n);}
void __aeabi_memclr4(void*d,size_t n){memset(d,0,n);}
void __aeabi_memclr8(void*d,size_t n){memset(d,0,n);}
