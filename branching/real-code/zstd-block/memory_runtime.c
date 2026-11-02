/* Portable C implementation of normal C memory semantics. These complete
 * functions are analysed by OTAWA when they survive GCC lowering; no nocall.
 * Volatile accesses prevent GCC recognising their bodies as recursive libc
 * idioms. Allocator/setup uses the ordinary linked libc, outside the task. */
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dst, const void *src, size_t n)
{
    volatile unsigned char *d = (volatile unsigned char *)dst;
    const volatile unsigned char *s = (const volatile unsigned char *)src;
    size_t i;
    for (i = 0; i < n; ++i) d[i] = s[i];
    return dst;
}

void *memmove(void *dst, const void *src, size_t n)
{
    volatile unsigned char *d = (volatile unsigned char *)dst;
    const volatile unsigned char *s = (const volatile unsigned char *)src;
    size_t i;
    if ((uintptr_t)dst > (uintptr_t)src) {
        for (i = n; i; --i) d[i - 1] = s[i - 1];
    } else {
        for (i = 0; i < n; ++i) d[i] = s[i];
    }
    return dst;
}

void *memset(void *dst, int value, size_t n)
{
    volatile unsigned char *d = (volatile unsigned char *)dst;
    size_t i;
    for (i = 0; i < n; ++i) d[i] = (unsigned char)value;
    return dst;
}
