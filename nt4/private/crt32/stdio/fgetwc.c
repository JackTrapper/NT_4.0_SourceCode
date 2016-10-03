/***
*fgetwc.c - get a wide character from a stream
*
*	Copyright (c) 1993, Microsoft Corporation. All rights reserved.
*
*Purpose:
*	defines fgetwc() - read a wide character from a stream
*
*Revision History:
*	04-26-93  CFW	Module created.
*	04-30-93  CFW	Bring wide char support from fgetc.c.
*	05-03-93  CFW	Add getwc function.
*	05-10-93  CFW	Optimize, fix error handling.
*	06-02-93  CFW	Wide get/put use wint_t.
*	09-14-93  CFW	Fix EOF cast bug.
*       10-22-93  CFW   Test for invalid MB chars using global preset flag.
*       10-28-93  CFW   Test for both IOSTRG and TEXT.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <assert.h>
#include <file2.h>
#include <internal.h>
#include <os2dll.h>
#include <msdos.h>
#include <errno.h>
#include <wchar.h>
#include <tchar.h>
#include <setlocal.h>

#ifdef MTHREAD	/* multi-thread; define both fgetwc and _getwc_lk */

/***
*wint_t fgetwc(stream) - read a wide character from a stream
*
*Purpose:
*	reads a wide character from the given stream
*
*Entry:
*	FILE *stream - stream to read wide character from
*
*Exit:
*	returns the wide character read
*	returns WEOF if at end of file or error occurred
*
*Exceptions:
*
*******************************************************************************/

wint_t _CRTAPI1 fgetwc (
	REG1 FILE *stream
	)
{
	wint_t retval;
	int index;

	assert(stream != NULL);

	index = _iob_index(stream);
	_lock_str(index);
	retval = _getwc_lk(stream);
	_unlock_str(index);

	return(retval);
}

/***
*_getwc_lk() -  getwc() core routine (locked version)
*
*Purpose:
*	Core getwc() routine; assumes stream is already locked.
*
*	[See getwc() above for more info.]
*
*Entry: [See getwc()]
*
*Exit:	[See getwc()]
*
*Exceptions:
*
*******************************************************************************/

wint_t _CRTAPI1 _getwc_lk (
	REG1 FILE *stream
	)
{

#else	/* non multi-thread; just define fgetwc */

wint_t _CRTAPI1 fgetwc (
	REG1 FILE *stream
	)
{

#endif	/* rejoin common code */

#ifndef _NTSUBSET_
	if (!(stream->_flag & _IOSTRG) && (_osfile[_fileno(stream)] & FTEXT))
	{
		int size = 1;
        int ch;
		char mbc[4];
		wchar_t wch;
		
		/* text (multi-byte) mode */
		if ((ch = _getc_lk(stream)) == EOF)
			return WEOF;

        mbc[0] = (char)ch;

		if (isleadbyte((unsigned char)mbc[0]))
		{
			if ((ch = _getc_lk(stream)) == EOF)
			{
				ungetc(mbc[0], stream);
				return WEOF;
			}
            mbc[1] = (char)ch;
			size = 2;
		}
		if (MultiByteToWideChar(_lc_codepage,
					MB_PRECOMPOSED|__invalid_mb_chars,
					mbc,
					size,
					&wch,
					1) == 0)
		{
			/*
			 * Conversion failed! Set errno and return
			 * failure.
			 */
			errno = EILSEQ;
			return WEOF;
		}
		return wch;
	}
#endif
	/* binary (Unicode) mode */
	if ((stream->_cnt -= sizeof(wchar_t)) >= 0)
		return *((wchar_t *)(stream->_ptr))++;
	else
		return _filwbuf(stream);
}

#undef getwc

wint_t _CRTAPI1 getwc (
	FILE *stream
	)
{
	return fgetwc(stream);
}
