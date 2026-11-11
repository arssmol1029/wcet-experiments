typedef unsigned char Byte; Byte input[256],output[4096]; unsigned result,bound_failure;
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#define TRUE true
#define FALSE false
#define ISBLANK(c) ((c)==' '||(c)=='\t')
#define Curl_inet_pton inet_pton
#define strncasecompare(a,b,n) (strncasecmp((a),(b),(n))==0)
static bool Curl_cidr4_match(const char*a,const char*b,unsigned c){(void)a;(void)b;(void)c;return false;}
static bool Curl_cidr6_match(const char*a,const char*b,unsigned c){(void)a;(void)b;(void)c;return false;}
enum nametype {TYPE_HOST,TYPE_IPV4,TYPE_IPV6};
bool Curl_check_noproxy(const char *name, const char *no_proxy)
{
  char hostip[128];

  /*
   * If we do not have a hostname at all, like for example with a FILE
   * transfer, we have nothing to interrogate the noproxy list with.
   */
  if(!name || name[0] == '\0')
    return FALSE;

  /* no_proxy=domain1.dom,host.domain2.dom
   *   (a comma-separated list of hosts which should
   *   not be proxied, or an asterisk to override
   *   all proxy variables)
   */
  if(no_proxy && no_proxy[0]) {
    const char *p = no_proxy;
    size_t namelen;
    enum nametype type = TYPE_HOST;
    if(!strcmp("*", no_proxy))
      return TRUE;

    /* NO_PROXY was specified and it was not just an asterisk */

    if(name[0] == '[') {
      char *endptr;
      /* IPv6 numerical address */
      endptr = strchr(name, ']');
      if(!endptr)
        return FALSE;
      name++;
      namelen = endptr - name;
      if(namelen >= sizeof(hostip))
        return FALSE;
      memcpy(hostip, name, namelen);
      hostip[namelen] = 0;
      name = hostip;
      type = TYPE_IPV6;
    }
    else {
      unsigned int address;
      namelen = strlen(name);
      if(1 == Curl_inet_pton(AF_INET, name, &address))
        type = TYPE_IPV4;
      else {
        /* ignore trailing dots in the hostname */
        if(name[namelen - 1] == '.')
          namelen--;
      }
    }

    while(*p) {
      const char *token;
      size_t tokenlen = 0;
      bool match = FALSE;

      /* pass blanks */
      while(*p && ISBLANK(*p))
        p++;

      token = p;
      /* pass over the pattern */
      while(*p && !ISBLANK(*p) && (*p != ',')) {
        p++;
        tokenlen++;
      }

      if(tokenlen) {
        switch(type) {
        case TYPE_HOST:
          /* ignore trailing dots in the token to check */
          if(token[tokenlen - 1] == '.')
            tokenlen--;

          if(tokenlen && (*token == '.')) {
            /* ignore leading token dot as well */
            token++;
            tokenlen--;
          }
          /* A: example.com matches 'example.com'
             B: www.example.com matches 'example.com'
             C: nonexample.com DOES NOT match 'example.com'
          */
          if(tokenlen == namelen)
            /* case A, exact match */
            match = strncasecompare(token, name, namelen);
          else if(tokenlen < namelen) {
            /* case B, tailmatch domain */
            match = (name[namelen - tokenlen - 1] == '.') &&
              strncasecompare(token, name + (namelen - tokenlen),
                              tokenlen);
          }
          /* case C passes through, not a match */
          break;
        case TYPE_IPV4:
        case TYPE_IPV6: {
          const char *check = token;
          char *slash;
          unsigned int bits = 0;
          char checkip[128];
          if(tokenlen >= sizeof(checkip))
            /* this cannot match */
            break;
          /* copy the check name to a temp buffer */
          memcpy(checkip, check, tokenlen);
          checkip[tokenlen] = 0;
          check = checkip;

          slash = strchr(check, '/');
          /* if the slash is part of this token, use it */
          if(slash) {
            /* if the bits variable gets a crazy value here, that is fine as
               the value will then be rejected in the cidr function */
            bits = (unsigned int)atoi(slash + 1);
            *slash = 0; /* null terminate there */
          }
          if(type == TYPE_IPV6)
            match = Curl_cidr6_match(name, check, bits);
          else
            match = Curl_cidr4_match(name, check, bits);
          break;
        }
        }
        if(match)
          return TRUE;
      } /* if(tokenlen) */
      /* pass blanks after pattern */
      while(ISBLANK(*p))
        p++;
      /* if not a comma, this ends the loop */
      if(*p != ',')
        break;
      /* pass any number of commas */
      while(*p == ',')
        p++;
    } /* while(*p) */
  } /* NO_PROXY was specified and it was not just an asterisk */

  return FALSE;
}
unsigned benchmark_entry(void) {return Curl_check_noproxy((const char*)input,"bbab.aa.t,baba.bb.t,bbaa.bb.t,bbbb.ba.t,baba.aa.t,abba.ba.t,aaab.aa.t,aaab.ab.t,bbab.ab.t,bbbb.bb.t,aaab.ba.t,aaaa.aa.t,bbba.ba.t,aaba.aa.t,bbaa.aa.t,aaba.ba.t,.aa.t.,bbbb.ab.t,baaa.bb.t,abaa.ba.t,babb.ba.t,aaaa.ab.t,baba.ab.t,abaa.bb.t,abab.bb.t,bbba.ab.t,bbba.aa.t,baab.ab.t,abab.ba.t,aaab.bb.t,aabb.ba.t,baba.ba.t,bb.t,baaa.ab.t,aaaa.ba.t,abba.ab.t,baab.bb.t,abbb.ba.t,babb.bb.t,aaba.bb.t,aabb.aa.t,aabb.ab.t,abbb.ab.t,bbbb.aa.t,abba.aa.t,abaa.aa.t,babb.ab.t,abab.ab.t");}
