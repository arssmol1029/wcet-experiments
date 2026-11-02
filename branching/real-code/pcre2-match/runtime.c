/* Actual portable byte/string operations. No algorithmic calls are omitted. */
#include <stddef.h>
#include <stdint.h>
void *memcpy(void *dst,const void *src,size_t n)
{unsigned char *d=dst;const unsigned char *s=src;size_t i;for(i=0;i<n;i++)d[i]=s[i];return dst;}
void *memmove(void *dst,const void *src,size_t n)
{unsigned char *d=dst;const unsigned char *s=src;size_t i;if((uintptr_t)d<(uintptr_t)s){for(i=0;i<n;i++)d[i]=s[i];}else{for(i=n;i>0;i--)d[i-1]=s[i-1];}return dst;}
void *memset(void *dst,int c,size_t n)
{unsigned char *d=dst;size_t i;for(i=0;i<n;i++)d[i]=(unsigned char)c;return dst;}
void bzero(void *dst,size_t n)
{unsigned char *d=dst;size_t i;for(i=0;i<n;i++)d[i]=0;}
int memcmp(const void *left,const void *right,size_t n)
{const unsigned char *a=left,*b=right;size_t i;for(i=0;i<n;i++)if(a[i]!=b[i])return (int)a[i]-(int)b[i];return 0;}
void *memchr(const void *ptr,int c,size_t n)
{const unsigned char *p=ptr;size_t i;for(i=0;i<n;i++)if(p[i]==(unsigned char)c)return (void *)(p+i);return NULL;}
size_t strlen(const char *s)
{size_t n=0;while(s[n])n++;return n;}
char *strchr(const char *s,int c)
{for(;;s++){if(*s==(char)c)return (char *)s;if(!*s)return NULL;}}
