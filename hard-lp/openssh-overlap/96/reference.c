/* $OpenBSD: match.c,v 1.44 2023/04/06 03:19:32 djm Exp $ */
/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 * Simple pattern matching, with '*' and '?' as wildcards.
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */
/*
 * Copyright (c) 2000 Markus Friedl.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <string.h>
#include <ctype.h>
typedef unsigned int u_int;typedef unsigned char u_char;
int
match_pattern(const char *s, const char *pattern)
{
	for (;;) {
		/* If at end of pattern, accept if also at end of string. */
		if (!*pattern)
			return !*s;

		if (*pattern == '*') {
			/* Skip this and any consecutive asterisks. */
			while (*pattern == '*')
				pattern++;

			/* If at end of pattern, accept immediately. */
			if (!*pattern)
				return 1;

			/* If next character in pattern is known, optimize. */
			if (*pattern != '?' && *pattern != '*') {
				/*
				 * Look instances of the next character in
				 * pattern, and try to match starting from
				 * those.
				 */
				for (; *s; s++)
					if (*s == *pattern &&
					    match_pattern(s + 1, pattern + 1))
						return 1;
				/* Failed. */
				return 0;
			}
			/*
			 * Move ahead one character at a time and try to
			 * match at each position.
			 */
			for (; *s; s++)
				if (match_pattern(s, pattern))
					return 1;
			/* Failed. */
			return 0;
		}
		/*
		 * There must be at least one more character in the string.
		 * If we are at the end, fail.
		 */
		if (!*s)
			return 0;

		/* Check if the next character of the string is acceptable. */
		if (*pattern != '?' && *pattern != *s)
			return 0;

		/* Move to the next character, both in string and in pattern. */
		s++;
		pattern++;
	}
	/* NOTREACHED */
}

/*
 * Tries to match the string against the
 * comma-separated sequence of subpatterns (each possibly preceded by ! to
 * indicate negation).  Returns -1 if negation matches, 1 if there is
 * a positive match, 0 if there is no match at all.
 */
int
match_pattern_list(const char *string, const char *pattern, int dolower)
{
	char sub[1024];
	int negated;
	int got_positive;
	u_int i, subi, len = strlen(pattern);

	got_positive = 0;
	for (i = 0; i < len;) {
		/* Check if the subpattern is negated. */
		if (pattern[i] == '!') {
			negated = 1;
			i++;
		} else
			negated = 0;

		/*
		 * Extract the subpattern up to a comma or end.  Convert the
		 * subpattern to lowercase.
		 */
		for (subi = 0;
		    i < len && subi < sizeof(sub) - 1 && pattern[i] != ',';
		    subi++, i++)
			sub[subi] = dolower && isupper((u_char)pattern[i]) ?
			    tolower((u_char)pattern[i]) : pattern[i];
		/* If subpattern too long, return failure (no match). */
		if (subi >= sizeof(sub) - 1)
			return 0;

		/* If the subpattern was terminated by a comma, then skip it. */
		if (i < len && pattern[i] == ',')
			i++;

		/* Null-terminate the subpattern. */
		sub[subi] = '\0';

		/* Try to match the subpattern against the string. */
		if (match_pattern(string, sub)) {
			if (negated)
				return -1;		/* Negative */
			else
				got_positive = 1;	/* Positive */
		}
	}

	/*
	 * Return success if got a positive match.  If there was a negative
	 * match, we have already returned -1 and never get here.
	 */
	return got_positive;
}


int reference(const char *s){return match_pattern_list(s,"babbbbab,abababba,bbb?bbba,bbabbbaa,!bbabbbaa,babbaaaa,bab?aaaa,aaababab,bababbbb,!bababbbb,bbb?baaa,ababaaab,abbbbaab,aaabaaab,!aaabaaab,bbabbabb,aaaabbbb,baaababa,bba?bbab,!bbabbbab,bbaaabba,abbaabaa,bba?abaa,aabaabaa,!aabaabaa,babbabbb,bba?bbab,bbabbaba,abbbbaba,!abbbbaba,abb?aaab,abbbaaba,bbbaabba,aaabbaba,!aaabbaba,bbaaabab,babbabaa,bbabbaaa,aab?bbba,!aababbba,aabababb,aaabaabb,bbb?abbb,aaaaabba,!aaaaabba,bbbabbab,bba?abaa,abbbabaa,babbbbaa,!babbbbaa,bbb?aaba,aababaab,babababa,aaababaa,!aaababaa,aaaaaabb,baaaabab,bbbababa,bab?bbaa,!bababbaa,bbbaabbb,babaabab,baa?bbbb,aabbbaaa,!aabbbaaa,bbaaaabb,bab?bbba,babbbabb,abababbb,!abababbb,aab?abba,bbbbabba,bbaabaaa,aaabbbbb,!aaabbbbb,bbbabbaa,aaabbaab,bbaaaaaa,bab?abba,!babbabba,baabaaaa,ababbabb,bba?aaab,aaaaaaaa,!aaaaaaaa,abaaaaab,abb?aaaa,baababab,abaabbaa,!abaabbaa,aaa?aaaa,aabbbbab,aabaabab,aababbaa,!aababbaa,bbabaaba",0);}
