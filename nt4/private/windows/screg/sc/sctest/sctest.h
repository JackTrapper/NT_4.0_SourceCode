/*++

Copyright (c) 1992  Microsoft Corporation

Module Name:

    ScTest.h

Abstract:

    This file contains tests of the Service Controller's config APIs:

        CreateService
        ChangeServiceConfig
        DeleteService
        QueryServiceConfig

Author:

    John Rogers (JohnRo) 21-Apr-1992

Environment:

    User Mode - Win32

Revision History:

    21-Apr-1992 JohnRo
        Created.

--*/


#ifndef _SCTEST_
#define _SCTEST_


//
// BUGBUG: Uncomment-this when DLL stubs return correct error codes when
// bad binding handles are passed.  (Right now, we get 0xC0030006, from
// rpcnterr.h, instead of a Win32 error code.)
//
//#define TEST_BINDING_HANDLES


#include <stdio.h>      // printf()


#define TRACE_MSG0( fmt )       (VOID) printf( fmt )
#define TRACE_MSG1( fmt, x )    (VOID) printf( fmt, x )
#define TRACE_MSG2( fmt, x, y ) (VOID) printf( fmt, x, y )

#define UNEXPECTED_MSG( text, retcode ) \
    { \
        (VOID) printf( "***UNEXPECTED RETURN CODE*** " FORMAT_DWORD " " \
                FORMAT_LPSTR "\n", retcode, text ); \
    }


VOID
TestConfigAPIs(
    VOID
    );

VOID
TestLocks(
    VOID
    );

#endif // _SCTEST_
