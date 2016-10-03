;/*++ BUILD Version: 0001    // Increment this if a change has global effects
;
;Copyright (c) 1994  Microsoft Corporation
;
;Module Name:
;
;    locmsg.h
;
;Abstract:
;
;    Definitions for DHCP messages.
;
;Author:
;
;    Manny Weiser 8-Dec-1992
;
;Revision History:
;
;Notes:
;
;    This file is generated by the MC tool from the dhcpmsg.mc file.
;
;--*/
;
;#ifndef _LOCMESSAGE_
;#define _LOCMESSAGE_
;

;//
;//  1000 - 1099   Reserved for DHCP client events.
;//

MessageId=1000 SymbolicName=DHCP_ROGUE_SERVER_MESSAGE
Language=English
Rogue DHCP server detection program received a(n) "%1" message from %2.
The IpAddress seen in the message is %3.
.

;#endif // _LOCMESSAGE_
