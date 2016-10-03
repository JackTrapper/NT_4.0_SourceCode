/***
*stddef.h - definitions/declarations for common constants, types, variables
*
*	Copyright (c) 1985-1992, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*	This file contains definitions and declarations for some commonly
*	used constants, types, and variables.
*	[ANSI]
*
****/

#ifndef _INC_STDDEF

#ifdef __cplusplus
extern "C" {
#endif

#if (_MSC_VER <= 600)
#define __cdecl     _cdecl
#define __far       _far
#define __near      _near
#endif

/* define the NULL pointer value and the offsetof() macro */

#ifndef NULL
#ifdef __cplusplus
#define NULL	0
#else
#define NULL	((void *)0)
#endif
#endif


/* offset of field m in a struct s */

#define offsetof(s,m)		(size_t)(unsigned long)&(((s *)0)->m)


/* errno declaration */

extern int __near __cdecl volatile errno;


/* define the implementation dependent size types */

#ifndef _PTRDIFF_T_DEFINED
typedef int ptrdiff_t;
#define _PTRDIFF_T_DEFINED
#endif

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

#ifndef _WCHAR_T_DEFINED
typedef	unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif



#ifdef __cplusplus
}
#endif

#define _INC_STDDEF
#endif	/* _INC_STDDEF */
