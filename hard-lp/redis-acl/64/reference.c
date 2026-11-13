/*
 * Copyright (c) 2018, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <string.h>
#include <ctype.h>
#include <stddef.h>
#define SELECTOR_FLAG_ALLKEYS 1
#define CMD_KEY_ACCESS 1
#define CMD_KEY_INSERT 2
#define CMD_KEY_DELETE 4
#define CMD_KEY_UPDATE 8
#define ACL_READ_PERMISSION 1
#define ACL_WRITE_PERMISSION 2
#define ACL_OK 0
#define ACL_DENIED_KEY 1
typedef struct {char *pattern;int flags;} keyPattern;
typedef struct {keyPattern *arr; int len;} list;
typedef struct {list *items;int i;} listIter;
typedef keyPattern listNode;
typedef struct {int flags;list *patterns;} aclSelector;
static void listRewind(list *l,listIter *i) {i->items=l;i->i=0;}
static listNode *listNext(listIter *i) {return i->i<i->items->len? &i->items->arr[i->i++]:NULL;}
#define listNodeValue(p) (p)
#define sdslen(p) strlen(p)
static int stringmatchlen_impl(const char *pattern, int patternLen,
        const char *string, int stringLen, int nocase, int *skipLongerMatches)
{
    while(patternLen && stringLen) {
        switch(pattern[0]) {
        case '*':
            while (patternLen && pattern[1] == '*') {
                pattern++;
                patternLen--;
            }
            if (patternLen == 1)
                return 1; /* match */
            while(stringLen) {
                if (stringmatchlen_impl(pattern+1, patternLen-1,
                            string, stringLen, nocase, skipLongerMatches))
                    return 1; /* match */
                if (*skipLongerMatches)
                    return 0; /* no match */
                string++;
                stringLen--;
            }
            /* There was no match for the rest of the pattern starting
             * from anywhere in the rest of the string. If there were
             * any '*' earlier in the pattern, we can terminate the
             * search early without trying to match them to longer
             * substrings. This is because a longer match for the
             * earlier part of the pattern would require the rest of the
             * pattern to match starting later in the string, and we
             * have just determined that there is no match for the rest
             * of the pattern starting from anywhere in the current
             * string. */
            *skipLongerMatches = 1;
            return 0; /* no match */
            break;
        case '?':
            string++;
            stringLen--;
            break;
        case '[':
        {
            int not, match;

            pattern++;
            patternLen--;
            not = pattern[0] == '^';
            if (not) {
                pattern++;
                patternLen--;
            }
            match = 0;
            while(1) {
                if (pattern[0] == '\\' && patternLen >= 2) {
                    pattern++;
                    patternLen--;
                    if (pattern[0] == string[0])
                        match = 1;
                } else if (pattern[0] == ']') {
                    break;
                } else if (patternLen == 0) {
                    pattern--;
                    patternLen++;
                    break;
                } else if (patternLen >= 3 && pattern[1] == '-') {
                    int start = pattern[0];
                    int end = pattern[2];
                    int c = string[0];
                    if (start > end) {
                        int t = start;
                        start = end;
                        end = t;
                    }
                    if (nocase) {
                        start = tolower(start);
                        end = tolower(end);
                        c = tolower(c);
                    }
                    pattern += 2;
                    patternLen -= 2;
                    if (c >= start && c <= end)
                        match = 1;
                } else {
                    if (!nocase) {
                        if (pattern[0] == string[0])
                            match = 1;
                    } else {
                        if (tolower((int)pattern[0]) == tolower((int)string[0]))
                            match = 1;
                    }
                }
                pattern++;
                patternLen--;
            }
            if (not)
                match = !match;
            if (!match)
                return 0; /* no match */
            string++;
            stringLen--;
            break;
        }
        case '\\':
            if (patternLen >= 2) {
                pattern++;
                patternLen--;
            }
            /* fall through */
        default:
            if (!nocase) {
                if (pattern[0] != string[0])
                    return 0; /* no match */
            } else {
                if (tolower((int)pattern[0]) != tolower((int)string[0]))
                    return 0; /* no match */
            }
            string++;
            stringLen--;
            break;
        }
        pattern++;
        patternLen--;
        if (stringLen == 0) {
            while(*pattern == '*') {
                pattern++;
                patternLen--;
            }
            break;
        }
    }
    if (patternLen == 0 && stringLen == 0)
        return 1;
    return 0;
}

int stringmatchlen(const char *pattern, int patternLen,
        const char *string, int stringLen, int nocase) {
    int skipLongerMatches = 0;
    return stringmatchlen_impl(pattern,patternLen,string,stringLen,nocase,&skipLongerMatches);
}

static int ACLSelectorCheckKey(aclSelector *selector, const char *key, int keylen, int keyspec_flags) {
    /* The selector can access any key */
    if (selector->flags & SELECTOR_FLAG_ALLKEYS) return ACL_OK;

    listIter li;
    listNode *ln;
    listRewind(selector->patterns,&li);

    int key_flags = 0;
    if (keyspec_flags & CMD_KEY_ACCESS) key_flags |= ACL_READ_PERMISSION;
    if (keyspec_flags & CMD_KEY_INSERT) key_flags |= ACL_WRITE_PERMISSION;
    if (keyspec_flags & CMD_KEY_DELETE) key_flags |= ACL_WRITE_PERMISSION;
    if (keyspec_flags & CMD_KEY_UPDATE) key_flags |= ACL_WRITE_PERMISSION;

    /* Test this key against every pattern. */
    while((ln = listNext(&li))) {
        keyPattern *pattern = listNodeValue(ln);
        if ((pattern->flags & key_flags) != key_flags)
            continue;
        size_t plen = sdslen(pattern->pattern);
        if (stringmatchlen(pattern->pattern,plen,key,keylen,0))
            return ACL_OK;
    }
    return ACL_DENIED_KEY;
}


int reference(const char *key,int flags) {
 keyPattern ps[]={{"abbaab",1},{"aaaaaa",2},{"baabaa",3},{"bb?bab",1},{"baaaba",2},{"aaabaa",3},{"bbbaba",1},{"aabbbb",2},{"aa?bab",3},{"babbbb",1},{"bbabaa",2},{"bbbaaa",3},{"babbaa",1},{"ba?abb",2},{"abbbba",3},{"ababaa",1},{"bbaaba",2},{"babbba",3},{"aa?abb",1},{"abbbbb",2},{"baaaab",3},{"bbbbba",1},{"baaaaa",2},{"ba?aaa",3},{"babaab",1},{"bababa",2},{"bbaabb",3},{"bbaaaa",1},{"bb?baa",2},{"aaabba",3},{"bbabba",1},{"ababba",2},{"aabbab",3},{"aa?bba",1},{"bbabbb",2},{"bababb",3},{"bbaaab",1},{"aaaaab",2},{"ba?bbb",3},{"baabab",1},{"abbbab",2},{"bbbabb",3},{"bbabab",1},{"ab?bab",2},{"aababa",3},{"abaaba",1},{"baabba",2},{"aabaab",3},{"ba?bab",1},{"abaaaa",2},{"abaaab",3},{"aabbaa",1},{"abbabb",2},{"ab?abb",3},{"aaabbb",1},{"bbbaab",2},{"abbaba",3},{"aaaaba",1},{"ab?baa",2},{"bbbbbb",3},{"aabaaa",1},{"ababbb",2},{"aababb",3},{"ab?aaa",1}};
 list l={ps,sizeof(ps)/sizeof(ps[0])}; aclSelector s={0,&l}; return ACLSelectorCheckKey(&s,key,6,flags);
}
