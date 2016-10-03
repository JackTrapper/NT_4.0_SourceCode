/*** 
* mbsstr.c - Search for one MBCS string inside another
*
*	Copyright (c) 1988-1992, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*	Search for one MBCS string inside another
*
*Revision History:
*	11-19-92  KRS	Ported from 16-bit sources.
*
*******************************************************************************/

#ifdef _MBCS
#include <cruntime.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>
#include <stddef.h>
#include <string.h>

#define _BYTELEN(s)	(strlen(s))
#define _MBSINC(s)	(_mbsinc(s))
#define PCHAR		char *

/***
* _mbsstr - Search for one MBCS string inside another
*
*Purpose:
*	Find the first occurrence of str2 in str1.
*
*Entry:
*	unsigned char *str1 = beginning of string
*	unsigned char *str2 = string to search for
*
*Exit:
*	Returns a pointer to the first occurrence of str2 in
*	str1, or NULL if str2 does not occur in str1
*
*Exceptions:
*
*******************************************************************************/

unsigned char * _CRTAPI1 _mbsstr( str1, str2 )
const unsigned char *str1;
const unsigned char *str2;
{
	unsigned char *cp = (unsigned char *) str1;
	unsigned char *s1, *s2, *endp;

	endp = (unsigned PCHAR) (str1 + (_BYTELEN(str1) - _BYTELEN(str2)));

	while (*cp && (cp <= endp))
	{
		s1 = cp;
		s2 = (PCHAR) str2;

		/*
		 * MBCS: ok to ++ since doing equality comparison.
		 * [This depends on MBCS strings being "legal".]
		 */

		while ( *s1 && *s2 && (*s1 == *s2) )
			s1++, s2++;

		if (!(*s2))
			return(cp);	/* success! */

		/*
		 * bump pointer to next char
		 */

		cp = _MBSINC(cp);

	}

	return(NULL);

}
#endif	/* _MBCS */
