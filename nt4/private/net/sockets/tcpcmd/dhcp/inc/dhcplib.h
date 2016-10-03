/*++

Copyright (c) 1994  Microsoft Corporation

Module Name:

    dhcplib.h

Abstract:

    This file contains proto type definitions for the dhcp lib
    functions.

Author:

    Madan Appiah  (madana)  12-Aug-1993

Environment:

    User Mode - Win32 - MIDL

Revision History:

--*/

//
// network.c
//

DHCP_IP_ADDRESS
DhcpDefaultSubnetMask(
    DHCP_IP_ADDRESS IpAddress
    );

//
// dhcp.c
//



PVOID
DhcpAllocateMemory(
    DWORD Size
    );

VOID
DhcpFreeMemory(
    PVOID Memory
    );


LPOPTION
DhcpAppendOption(
    LPOPTION Option,
    BYTE OptionType,
    PVOID OptionValue,
    BYTE OptionLength,
    LPBYTE OptionEnd
    );

LPOPTION
DhcpAppendClientIDOption(
    LPOPTION Option,
    BYTE ClientHWType,
    LPBYTE ClientHWAddr,
    BYTE ClientHWAddrLength,
    LPBYTE OptionEnd

    );

LPBYTE
DhcpAppendMagicCookie(
    LPBYTE Option,
    LPBYTE OptionEnd

    );

DATE_TIME
DhcpCalculateTime(
    DWORD RelativeTime
    );

DATE_TIME
DhcpGetDateTime(
    VOID
    );

DWORD
DhcpReportEventW(
    LPWSTR Source,
    DWORD EventID,
    DWORD EventType,
    DWORD NumStrings,
    DWORD DataLength,
    LPWSTR *Strings,
    LPVOID Data
    );

DWORD
DhcpReportEventA(
    LPWSTR Source,
    DWORD EventID,
    DWORD EventType,
    DWORD NumStrings,
    DWORD DataLength,
    LPSTR *Strings,
    LPVOID Data
    );

DWORD
DhcpLogUnknownOption(
    LPWSTR Source,
    DWORD EventID,
    LPOPTION Option
    );

//
// convert.c
//

LPWSTR
DhcpOemToUnicodeN(
    IN      LPSTR   Ansi,
    IN OUT  LPWSTR  Unicode,
    IN      USHORT  cChars
    );

LPWSTR
DhcpOemToUnicode(
    IN LPSTR Ansi,
    IN OUT LPWSTR Unicode
    );

LPSTR
DhcpUnicodeToOem(
    IN LPWSTR Unicode,
    IN LPSTR Ansi
    );

#if 0

VOID
DhcpIpAddressToString(
    LPWSTR Buffer,
    DWORD HexNumber
    );

VOID
DhcpStringToIpAddress(
    LPSTR Buffer,
    LPDHCP_IP_ADDRESS IpAddress,
    BOOL NetOrder
    );

#endif

VOID
DhcpHexToString(
    LPWSTR Buffer,
    LPBYTE HexNumber,
    DWORD Length
    );

VOID
DhcpHexToAscii(
    LPSTR Buffer,
    LPBYTE HexNumber,
    DWORD Length
    );

VOID
DhcpDecimalToString(
    LPWSTR Buffer,
    BYTE Number
    );

DWORD
DhcpDottedStringToIpAddress(
    LPSTR String
    );

LPSTR
DhcpIpAddressToDottedString(
    DWORD IpAddress
    );

DWORD
DhcpStringToHwAddress(
    LPSTR AddressBuffer,
    LPSTR AddressString
    );

#if 0

DHCP_IP_ADDRESS
DhcpHostOrder(
    DHCP_IP_ADDRESS NetworkOrderAddress
    );

DHCP_IP_ADDRESS
DhcpNetworkOrder(
    DHCP_IP_ADDRESS NetworkOrderAddress
    );

#endif

LPWSTR
DhcpRegIpAddressToKey(
    DHCP_IP_ADDRESS IpAddress,
    LPWSTR KeyBuffer
    );

DWORD
DhcpRegKeyToIpAddress(
    LPWSTR Key
    );

LPWSTR
DhcpRegOptionIdToKey(
    DHCP_OPTION_ID OptionId,
    LPWSTR KeyBuffer
    );

DHCP_OPTION_ID
DhcpRegKeyToOptionId(
    LPWSTR Key
    );

#if DBG

VOID
DhcpDumpMessage(
    DWORD DhcpDebugFlag,
    LPDHCP_MESSAGE DhcpMessage
    );

VOID
DhcpAssertFailed(
    LPSTR FailedAssertion,
    LPSTR FileName,
    DWORD LineNumber,
    LPSTR Message
    );

#define DhcpAssert(Predicate) \
    { \
        if (!(Predicate)) \
            DhcpAssertFailed( #Predicate, __FILE__, __LINE__, NULL ); \
    }


#define DhcpVerify(Predicate) \
    { \
        if (!(Predicate)) \
            DhcpAssertFailed( #Predicate, __FILE__, __LINE__, NULL ); \
    }


#else

#define DhcpAssert(_x_)
#define DhcpDumpMessage(_x_, _y_)
#define DhcpVerify(_x_) (_x_)

#endif // not DBG
