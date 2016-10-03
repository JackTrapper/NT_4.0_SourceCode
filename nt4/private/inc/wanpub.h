/*++

Copyright (c) 1990-1995  Microsoft Corporation

Module Name:

	Wanpub.h

Abstract:

	This file contains all public data structures and defines used
	by NdisWan.  It defines the Ioctl interface to NdisWan as well
	as the LineUp/LineDown interface between NdisWan and the transports.

Author:

	Tony Bell	(TonyBe) June 06, 1995

Environment:

	Kernel Mode

Revision History:

	TonyBe		06/06/95		Created

--*/

#ifndef _NDISWAN_PUB_
#define _NDISWAN_PUB_

#ifndef NTSTATUS
typedef LONG	NTSTATUS;
#endif

#ifndef NDIS_HANDLE
typedef PVOID	NDIS_HANDLE, *PNDIS_HANDLE;
#endif

#ifndef NDIS_STRING
typedef UNICODE_STRING NDIS_STRING, *PNDIS_STRING;
#endif

#ifndef NDIS_WAN_QUALITY

#endif

#include <ntddndis.h>

//
// Different handle types that ndiswan expects
//
#define LINKHANDLE				0xABB0
#define BUNDLEHANDLE			0xABB1
#define CANCELEDHANDLE			0xABB2

//
// Different threshold event types
//
#define UPPER_THRESHOLD			0x00000000
#define LOWER_THRESHOLD			0x00000001

//
// Unroute a bundle
//
#define PROTOCOL_UNROUTE		0xFFFF

//
// Get Bundle's Idle time
//
#define BUNDLE_IDLE_TIME		0xFFFF

#define	MAX_PPP_HEADER			8

#define MAX_NAME_LENGTH			64

//
// NDISWAN_IO_PACKET flags
//
#define PACKET_IS_DIRECT		0x0001
#define PACKET_IS_BROADCAST		0x0002
#define PACKET_IS_MULTICAST		0x0004


//
// Ioctl function codes should be kept contiguous.  Dispatch
// table is in io.c.  If a new function is added the dispatch
// table has to be updated!
//
#define	FUNC_MAP_CONNECTION_ID			0
#define	FUNC_GET_BUNDLE_HANDLE			1
#define	FUNC_SET_FRIENDLY_NAME			2
#define	FUNC_ROUTE						3
#define	FUNC_ADD_LINK_TO_BUNDLE			4
#define	FUNC_ENUM_LINKS_IN_BUNDLE		5
#define	FUNC_SET_PROTOCOL_PRIORITY		6
#define	FUNC_SET_BANDWIDTH_ON_DEMAND	7
#define	FUNC_SET_THRESHOLD_EVENT		8
#define	FUNC_FLUSH_THRESHOLD_EVENTS		9
#define	FUNC_SEND_PACKET				10
#define	FUNC_RECEIVE_PACKET				11
#define	FUNC_FLUSH_RECEIVE_PACKETS		12
#define	FUNC_GET_STATS					13
#define	FUNC_SET_LINK_INFO				14
#define	FUNC_GET_LINK_INFO				15
#define	FUNC_SET_COMPRESSION_INFO		16
#define	FUNC_GET_COMPRESSION_INFO		17
#define	FUNC_SET_BRIDGE_INFO			18
#define	FUNC_GET_BRIDGE_INFO			19
#define	FUNC_SET_VJ_INFO				20
#define	FUNC_GET_VJ_INFO				21
#define	FUNC_SET_CIPX_INFO				22
#define	FUNC_GET_CIPX_INFO				23
#define	FUNC_SET_ENCRYPTION_INFO		24
#define	FUNC_GET_ENCRYPTION_INFO		25
#define	FUNC_SET_DEBUG_INFO				26
#define	FUNC_ENUM_ACTIVE_BUNDLES		27
#define FUNC_GET_NDISWANCB				28
#define FUNC_GET_ADAPTERCB				29
#define	FUNC_GET_WAN_ADAPTERCB			30
#define FUNC_GET_BANDWIDTH_UTILIZATION	31
#define FUNC_ENUM_PROTOCOL_UTILIZATION	32
#define FUNC_ENUM_ADAPTERCB				33
#define FUNC_ENUM_WAN_ADAPTERCB			34
#define FUNC_GET_WAN_INFO				35
#define FUNC_GET_IDLE_TIME				36
#define FUNC_UNROUTE					37


#ifdef NT	// NT Specific stuff

#define FILE_DEVICE_NDISWAN			0x030

#define	NDISWAN_CTL_CODE(_Function)	CTL_CODE(FILE_DEVICE_NDISWAN, _Function, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define	IOCTL_NDISWAN_MAP_CONNECTION_ID			NDISWAN_CTL_CODE(FUNC_MAP_CONNECTION_ID     )
#define	IOCTL_NDISWAN_GET_BUNDLE_HANDLE			NDISWAN_CTL_CODE(FUNC_GET_BUNDLE_HANDLE     )
#define	IOCTL_NDISWAN_SET_FRIENDLY_NAME			NDISWAN_CTL_CODE(FUNC_SET_FRIENDLY_NAME     )
#define	IOCTL_NDISWAN_ROUTE						NDISWAN_CTL_CODE(FUNC_ROUTE        			)
#define	IOCTL_NDISWAN_ADD_LINK_TO_BUNDLE		NDISWAN_CTL_CODE(FUNC_ADD_LINK_TO_BUNDLE    )
#define	IOCTL_NDISWAN_ENUM_LINKS_IN_BUNDLE		NDISWAN_CTL_CODE(FUNC_ENUM_LINKS_IN_BUNDLE  )
#define	IOCTL_NDISWAN_SET_PROTOCOL_PRIORITY		NDISWAN_CTL_CODE(FUNC_SET_PROTOCOL_PRIORITY )
#define	IOCTL_NDISWAN_SET_BANDWIDTH_ON_DEMAND	NDISWAN_CTL_CODE(FUNC_SET_BANDWIDTH_ON_DEMAND)
#define	IOCTL_NDISWAN_SET_THRESHOLD_EVENT		NDISWAN_CTL_CODE(FUNC_SET_THRESHOLD_EVENT   )
#define	IOCTL_NDISWAN_FLUSH_THRESHOLD_EVENTS	NDISWAN_CTL_CODE(FUNC_FLUSH_THRESHOLD_EVENTS)
#define	IOCTL_NDISWAN_SEND_PACKET				NDISWAN_CTL_CODE(FUNC_SEND_PACKET			)
#define	IOCTL_NDISWAN_RECEIVE_PACKET			NDISWAN_CTL_CODE(FUNC_RECEIVE_PACKET		)
#define	IOCTL_NDISWAN_FLUSH_RECEIVE_PACKETS		NDISWAN_CTL_CODE(FUNC_FLUSH_RECEIVE_PACKETS )
#define	IOCTL_NDISWAN_GET_STATS					NDISWAN_CTL_CODE(FUNC_GET_STATS             )
#define	IOCTL_NDISWAN_SET_LINK_INFO				NDISWAN_CTL_CODE(FUNC_SET_LINK_INFO         )
#define	IOCTL_NDISWAN_GET_LINK_INFO				NDISWAN_CTL_CODE(FUNC_GET_LINK_INFO         )
#define	IOCTL_NDISWAN_SET_COMPRESSION_INFO		NDISWAN_CTL_CODE(FUNC_SET_COMPRESSION_INFO  )
#define	IOCTL_NDISWAN_GET_COMPRESSION_INFO		NDISWAN_CTL_CODE(FUNC_GET_COMPRESSION_INFO  )
#define	IOCTL_NDISWAN_SET_BRIDGE_INFO			NDISWAN_CTL_CODE(FUNC_SET_BRIDGE_INFO		)
#define	IOCTL_NDISWAN_GET_BRIDGE_INFO			NDISWAN_CTL_CODE(FUNC_GET_BRIDGE_INFO		)
#define	IOCTL_NDISWAN_SET_VJ_INFO				NDISWAN_CTL_CODE(FUNC_SET_VJ_INFO           )
#define	IOCTL_NDISWAN_GET_VJ_INFO				NDISWAN_CTL_CODE(FUNC_GET_VJ_INFO           )
#define	IOCTL_NDISWAN_SET_CIPX_INFO				NDISWAN_CTL_CODE(FUNC_SET_CIPX_INFO         )
#define	IOCTL_NDISWAN_GET_CIPX_INFO				NDISWAN_CTL_CODE(FUNC_GET_CIPX_INFO         )
#define	IOCTL_NDISWAN_SET_ENCRYPTION_INFO		NDISWAN_CTL_CODE(FUNC_SET_ENCRYPTION_INFO   )
#define	IOCTL_NDISWAN_GET_ENCRYPTION_INFO		NDISWAN_CTL_CODE(FUNC_GET_ENCRYPTION_INFO   )
#define	IOCTL_NDISWAN_SET_DEBUG_INFO			NDISWAN_CTL_CODE(FUNC_SET_DEBUG_INFO        )
#define	IOCTL_NDISWAN_ENUM_ACTIVE_BUNDLES		NDISWAN_CTL_CODE(FUNC_ENUM_ACTIVE_BUNDLES	)
#define IOCTL_NDISWAN_GET_NDISWANCB				NDISWAN_CTL_CODE(FUNC_GET_NDISWANCB			)
#define IOCTL_NDISWAN_GET_ADAPTERCB				NDISWAN_CTL_CODE(FUNC_GET_ADAPTERCB			)
#define	IOCTL_NDISWAN_GET_WAN_ADAPTERCB			NDISWAN_CTL_CODE(FUNC_GET_WAN_ADAPTERCB		)
#define IOCTL_NDISWAN_GET_BANDWIDTH_UTILIZATION	NDISWAN_CTL_CODE(FUNC_GET_BANDWIDTH_UTILIZATION)
#define	IOCTL_NDISWAN_ENUM_PROTOCOL_UTILIZATION	NDISWAN_CTL_CODE(FUNC_ENUM_PROTOCOL_UTILIZATION)
#define IOCTL_NDISWAN_ENUM_ADAPTERCB			NDISWAN_CTL_CODE(FUNC_ENUM_ADAPTERCB		)
#define	IOCTL_NDISWAN_ENUM_WAN_ADAPTERCB		NDISWAN_CTL_CODE(FUNC_ENUM_WAN_ADAPTERCB	)
#define	IOCTL_NDISWAN_GET_WAN_INFO				NDISWAN_CTL_CODE(FUNC_GET_WAN_INFO			)
#define	IOCTL_NDISWAN_GET_IDLE_TIME				NDISWAN_CTL_CODE(FUNC_GET_IDLE_TIME			)
#define	IOCTL_NDISWAN_UNROUTE					NDISWAN_CTL_CODE(FUNC_UNROUTE      			)

#endif		// end NT

//
// NdisWan error messages
//
#define NDISWAN_ERROR_BASE					600
#define NDISWAN_ERROR_INVALID_HANDLE		NDISWAN_ERROR_BASE + 1
#define NDISWAN_ERROR_ALREADY_ROUTED		NDISWAN_ERROR_BASE + 2
#define NDISWAN_ERROR_NO_ROUTE				NDISWAN_ERROR_BASE + 3
#define NDISWAN_ERROR_INVALID_HANDLE_TYPE	NDISWAN_ERROR_BASE + 4
#define NDISWAN_ERROR_INVALID_ADDRESS		NDISWAN_ERROR_BASE + 5

//
// Structure used to store wan statistics
//
typedef struct _WAN_STATS {
	ULONG	BytesTransmitted;
	ULONG	BytesReceived;
	ULONG	FramesTransmitted;
	ULONG	FramesReceived;

	ULONG	CRCErrors;
	ULONG	TimeoutErrors;
	ULONG	AlignmentErrors;
	ULONG	SerialOverrunErrors;
	ULONG	FramingErrors;
	ULONG	BufferOverrunErrors;

	ULONG	BytesTransmittedUncompressed;
	ULONG	BytesReceivedUncompressed;
	ULONG	BytesTransmittedCompressed;
	ULONG	BytesReceivedCompressed;
} WAN_STATS, *PWAN_STATS;

//
// Structure used to get and set WAN Link Information
// Needs to be kept in sync with NDIS_WAN_SET_LINK_INFO
// and NDIS_WAN_GET_LINK_INFO in ndiswan.h
//
typedef struct _WAN_LINK_INFO {
	IN	ULONG		MaxSendFrameSize;
	IN	ULONG		MaxRecvFrameSize;
		ULONG		HeaderPadding;
		ULONG		TailPadding;
	IN	ULONG		SendFramingBits;
	IN	ULONG		RecvFramingBits;
	IN	ULONG		SendCompressionBits;
	IN	ULONG		RecvCompressionBits;
	IN	ULONG		SendACCM;
	IN	ULONG		RecvACCM;
	IN	ULONG		MaxRSendFrameSize;
	IN	ULONG		MaxRRecvFrameSize;
} WAN_LINK_INFO, *PWAN_LINK_INFO;

//
// Structure used to get general information about
// a wan link
//
typedef struct _WAN_INFO {
    OUT ULONG	MaxFrameSize;
	OUT	ULONG	MaxTransmit;
    OUT ULONG	FramingBits;
    OUT ULONG	DesiredACCM;
	OUT	ULONG	MaxReconstructedFrameSize;
	OUT	ULONG	LinkSpeed;
} WAN_INFO, *PWAN_INFO;

//
// Structure used to set Protocol Utilization
//
typedef struct _PROTOCOL_UTILIZATION {
	USHORT	usProtocolType;
	USHORT	usUtilization;
} PROTOCOL_UTILIZATION, *PPROTOCOL_UTILIZATION;

//
// Encryption key sizes
//
#ifndef MAX_SESSIONKEY_SIZE
#define MAX_SESSIONKEY_SIZE		8
#endif

#ifndef MAX_USERSESSIONKEY_SIZE
#define MAX_USERSESSIONKEY_SIZE	16
#endif

#ifndef MAX_CHALLENGE_SIZE
#define MAX_CHALLENGE_SIZE		8
#endif
//
// Structure used to get and set compression information
//
typedef struct _COMPRESS_INFO {
	UCHAR	LMSessionKey[MAX_SESSIONKEY_SIZE];
	UCHAR	UserSessionKey[MAX_USERSESSIONKEY_SIZE];
	UCHAR	Challenge[MAX_CHALLENGE_SIZE];
	ULONG	MSCompType;

	UCHAR	CompType;
	USHORT	CompLength;

	union {
		struct {
			UCHAR	CompOUI[3];
			UCHAR	CompSubType;
			UCHAR	CompValues[32];
		} Proprietary;

		struct {
			UCHAR	CompValues[32];
		} Public;
	};
} COMPRESS_INFO, *PCOMPRESS_INFO;

//
// Structure used to get and set VJ header compression information
//
typedef struct _VJ_INFO {
	USHORT	IPCompressionProtocol;
	UCHAR	MaxSlotID;
	UCHAR	CompSlotID;
} VJ_INFO, *PVJ_INFO;

//
// Structure used to get and set IPX header compression information
//
typedef struct _CIPX_INFO {
	USHORT	IPXCompressionProtocol;
} CIPX_INFO, *PCIPX_INFO;

//
// Structure used to get and set encryption information
//
typedef struct __ENCRYPT_INFO {
	UCHAR	EncryptType;
	USHORT	EncryptLength;

	union {
		struct {
			UCHAR	EncryptOUI[3];
			UCHAR	EncryptSubtype;
			UCHAR	EncryptValues[1];
		} Proprietary;

		struct {
			UCHAR	EncryptValues[1];
		} Public;
	};
} ENCRYPT_INFO, *PENCRYPT_INFO;

//
// Structure used in IOCTL_NDISWAN_MAP_CONNECTION_ID
//
typedef struct _NDISWAN_MAP_CONNECTION_ID {
	OUT	NDIS_HANDLE	hLinkHandle;
	OUT	NDIS_HANDLE	hBundleHandle;
	IN	NDIS_HANDLE	hConnectionID;
	IN	NDIS_HANDLE	hLinkContext;
	IN	NDIS_HANDLE	hBundleContext;
	IN	ULONG		ulNameLength;
	IN	CHAR		szName[1];
} NDISWAN_MAP_CONNECTION_ID, *PNDISWAN_MAP_CONNECTION_ID;

//
// Structure used in IOCTL_NDISWAN_GET_BUNDLE_HANDLE
//
typedef struct _NDISWAN_GET_BUNDLE_HANDLE {
	OUT	NDIS_HANDLE	hBundleHandle;
	IN	NDIS_HANDLE	hLinkHandle;
} NDISWAN_GET_BUNDLE_HANDLE, *PNDISWAN_GET_BUNDLE_HANDLE;

//
// Structure used in IOCTL_NDISWAN_SET_FRIENDLY_NAME
//
typedef struct _NDISWAN_SET_FRIENDLY_NAME {
	IN	NDIS_HANDLE	hHandle;
	IN	USHORT		usHandleType;
	IN	ULONG		ulNameLength;
	IN	CHAR		szName[1];
} NDISWAN_SET_FRIENDLY_NAME, *PNDISWAN_SET_FRIENDLY_NAME;

//
// Structure used in IOCTL_NDISWAN_ROUTE
//
typedef struct _NDISWAN_ROUTE {
	IN	NDIS_HANDLE	hBundleHandle;
	IN	USHORT		usProtocolType;
	IN	USHORT		usBindingNameLength;
	IN	WCHAR		BindingName[MAX_NAME_LENGTH];
	OUT	USHORT		usDeviceNameLength;
	OUT	WCHAR		DeviceName[MAX_NAME_LENGTH];
	IN	ULONG		ulBufferLength;
	IN	UCHAR		Buffer[1];
} NDISWAN_ROUTE, *PNDISWAN_ROUTE;

//
// Structure used in IOCTL_NDISWAN_UNROUTE
//
typedef struct _NDISWAN_UNROUTE {
	IN	NDIS_HANDLE	hBundleHandle;
	IN	USHORT		usProtocolType;
} NDISWAN_UNROUTE, *PNDISWAN_UNROUTE;


//
// Structure used in IOCTL_NDISWAN_ADD_LINK_TO_BUNDLE
//
typedef struct _NDISWAN_ADD_LINK_TO_BUNDLE {
	IN	NDIS_HANDLE	hBundleHandle;
	IN	NDIS_HANDLE	hLinkHandle;
} NDISWAN_ADD_LINK_TO_BUNDLE, *PNDISWAN_ADD_LINK_TO_BUNDLE;

//
// Structure used in IOCTL_NDISWAN_ENUM_LINKS_IN_BUNDLE
//
typedef struct _NDISWAN_ENUM_LINKS_IN_BUNDLE {
	IN	NDIS_HANDLE	hBundleHandle;
	OUT	ULONG		ulNumberOfLinks;
	OUT	NDIS_HANDLE	hLinkHandleArray[1];
} NDISWAN_ENUM_LINKS_IN_BUNDLE, *PNDISWAN_ENUM_LINKS_IN_BUNDLE;

//
// Structure used in IOCTL_NDISWAN_SET_PROTOCOL_PRIORITY
//
typedef struct _NDISWAN_SET_PROTOCOL_PRIORITY {
	IN	NDIS_HANDLE	hBundleHandle;
	IN	USHORT		usProtocolType;
	IN	USHORT		usPriority;
} NDISWAN_SET_PROTOCOL_PRIORITY, *PNDISWAN_SET_PROTOCOL_PRIORITY;

//
// Structure used in IOCTL_NDISWAN_SET_BANDWIDTH_ON_DEMAND
//
typedef struct _NDISWAN_SET_BANDWIDTH_ON_DEMAND {
	IN	NDIS_HANDLE	hBundleHandle;
	IN	USHORT		usLowerThreshold;
	IN	USHORT		usUpperThreshold;
	IN	ULONG		ulLowerSamplePeriod;
	IN	ULONG		ulUpperSamplePeriod;
} NDISWAN_SET_BANDWIDTH_ON_DEMAND, *PNDISWAN_SET_BANDWIDTH_ON_DEMAND;

//
// Structure used in IOCTL_NDISWAN_SET_THRESHOLD_EVENT
//
typedef struct _NDISWAN_SET_THRESHOLD_EVENT {
	OUT	NDIS_HANDLE	hBundleHandle;
	OUT	ULONG		ulThreshold;
} NDISWAN_SET_THRESHOLD_EVENT, *PNDISWAN_SET_THRESHOLD_EVENT;

//
// Structure used in IOCTL_NDISWAN_SEND_PACKET and IOCTL_NDISWAN_RECEIVE_PACKET
//
typedef struct _NDISWAN_IO_PACKET {
	IN OUT	NDIS_HANDLE	hHandle;
	IN OUT	USHORT      usHandleType;
	IN OUT	USHORT      usHeaderSize;
	IN OUT	USHORT      usPacketSize;
	IN OUT	USHORT      usPacketFlags;
	IN OUT	UCHAR       PacketData[1];
} NDISWAN_IO_PACKET, *PNDISWAN_IO_PACKET;

//
// Structure used in IOCTL_NDISWAN_GET_STATS
//
typedef struct _NDISWAN_GET_STATS {
	IN	NDIS_HANDLE	hHandle;
	IN	USHORT		usHandleType;
	OUT	struct _STATS {
		OUT	WAN_STATS	BundleStats;
		OUT	WAN_STATS	LinkStats;
	} Stats;
} NDISWAN_GET_STATS, *PNDISWAN_GET_STATS;

//
// Structure used in IOCTL_NDISWAN_GET_BANDWIDTH_UTILIZATION
//
typedef struct _NDISWAN_GET_BANDWIDTH_UTILIZATION {
	IN	NDIS_HANDLE	hBundleHandle;
	OUT	USHORT		usBandwidthUtilization;
} NDISWAN_GET_BANDWIDTH_UTILIZATION, *PNDISWAN_GET_BANDWIDTH_UTILIZATION;

//
// Structure used in IOCTL_NDISWAN_ENUM_PROTOCOL_UTILIZATION
//
typedef struct _NDISWAN_ENUM_PROTOCOL_UTILIZATION {
	IN	NDIS_HANDLE				hBundleHandle;
	OUT	PROTOCOL_UTILIZATION	ProtocolArray[1];
} NDISWAN_ENUM_PROTOCOL_UTILIZATION, *PNDISWAN_ENUM_PROTOCOL_UTILIZATION;

//
// Structure used in IOCTL_NDISWAN_ENUM_ACTIVE_BUNDLES
//
typedef struct _NDISWAN_ENUM_ACTIVE_BUNDLES {
	OUT	ULONG	ulNumberOfActiveBundles;
} NDISWAN_ENUM_ACTIVE_BUNDLES, *PNDISWAN_ENUM_ACTIVE_BUNDLES;

//
// Structure used in IOCTL_NDISWAN_SET_LINK_INFO
//
typedef struct _NDISWAN_SET_LINK_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	IN	WAN_LINK_INFO	LinkInfo;
} NDISWAN_SET_LINK_INFO, *PNDISWAN_SET_LINK_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_LINK_INFO
//
typedef struct _NDISWAN_GET_LINK_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	OUT	WAN_LINK_INFO	LinkInfo;
} NDISWAN_GET_LINK_INFO, *PNDISWAN_GET_LINK_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_WAN_INFO
//
typedef struct _NDISWAN_GET_WAN_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	OUT	WAN_INFO		WanInfo;
} NDISWAN_GET_WAN_INFO, *PNDISWAN_GET_WAN_INFO;

//
// Structure used in IOCTL_NDISWAN_SET_COMPRESSION_INFO
//
typedef struct _NDISWAN_SET_COMPRESSION_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	IN	COMPRESS_INFO	SendCapabilities;
	IN	COMPRESS_INFO	RecvCapabilities;
} NDISWAN_SET_COMPRESSION_INFO, *PNDISWAN_SET_COMPRESSION_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_COMPRESSION_INFO
//
typedef struct _NDISWAN_GET_COMPRESSION_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	OUT	COMPRESS_INFO	SendCapabilities;
	OUT	COMPRESS_INFO	RecvCapabilities;
} NDISWAN_GET_COMPRESSION_INFO, *PNDISWAN_GET_COMPRESSION_INFO;

//
// Structure used in IOCTL_NDISWAN_SET_VJ_INFO
//
typedef struct _NDISWAN_SET_VJ_INFO {
	IN	NDIS_HANDLE	hLinkHandle;
	IN	VJ_INFO		SendCapabilities;
	IN	VJ_INFO		RecvCapabilities;
} NDISWAN_SET_VJ_INFO, *PNDISWAN_SET_VJ_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_VJ_INFO
//
typedef struct _NDISWAN_GET_VJ_INFO {
	IN	NDIS_HANDLE	hLinkHandle;
	OUT	VJ_INFO		SendCapabilities;
	OUT	VJ_INFO		RecvCapabilities;
} NDISWAN_GET_VJ_INFO, *PNDISWAN_GET_VJ_INFO;

//
// Structure used in IOCTL_NDISWAN_SET_BRIDGE_INFO
//
typedef struct _NDISWAN_SET_BRIDGE_INFO {
	IN	NDIS_HANDLE	hLinkHandle;
	IN	USHORT		LanSegmentNumber;
	IN	UCHAR		BridgeNumber;
	IN	UCHAR		BridgingOptions;
	IN	ULONG		BridgingCapabilities;
	IN	UCHAR		BridgingType;
	IN	UCHAR		MacBytes[6];
} NDISWAN_SET_BRIDGE_INFO, *PNDISWAN_SET_BRIDGE_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_BRIDGE_INFO
//
typedef struct _NDISWAN_GET_BRIDGE_INFO {
	IN	NDIS_HANDLE	hLinkHandle;
	OUT	USHORT		LanSegmentNumber;
	OUT	UCHAR		BridgeNumber;
	OUT	UCHAR		BridgingOptions;
	OUT	ULONG		BridgingCapabilities;
	OUT	UCHAR		BridgingType;
	OUT	UCHAR		MacBytes[6];
} NDISWAN_GET_BRIDGE_INFO, *PNDISWAN_GET_BRIDGE_INFO;

//
// Structure used in IOCTL_NDISWAN_SET_CIPX_INFO
//
typedef struct _NDISWAN_SET_CIPX_INFO {
	IN	NDIS_HANDLE	hLinkHandle;
	IN	CIPX_INFO	SendCapabilities;
	IN	CIPX_INFO	RecvCapabilities;
} NDISWAN_SET_CIPX_INFO, *PNDISWAN_SET_CIPX_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_CIPX_INFO
//
typedef struct _NDISWAN_GET_CIPX_INFO {
	IN	NDIS_HANDLE	hLinkHandle;
	OUT	CIPX_INFO	SendCapabilities;
	OUT	CIPX_INFO	RecvCapabilities;
} NDISWAN_GET_CIPX_INFO, *PNDISWAN_GET_CIPX_INFO;

//
// Structure used in IOCTL_NDISWAN_SET_ENCRYPTION_INFO
//
typedef struct _NDISWAN_SET_ENCRYPTION_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	IN	ENCRYPT_INFO	SendCapabilities;
	IN	ENCRYPT_INFO	RecvCapabilities;
} NDISWAN_SET_ENCRYPTION_INFO, *PNDISWAN_SET_ENCRYPTION_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_ENCRYPTION_INFO
//
typedef struct _NDISWAN_GET_ENCRYPTION_INFO {
	IN	NDIS_HANDLE		hLinkHandle;
	IN	ENCRYPT_INFO	SendCapabilities;
	IN	ENCRYPT_INFO	RecvCapabilities;
} NDISWAN_GET_ENCRYPTION_INFO, *PNDISWAN_GET_ENCRYPTION_INFO;

//
// Structure used in IOCTL_NDISWAN_GET_IDLE_TIME
//
typedef struct _NDISWAN_GET_IDLE_TIME {
	IN	NDIS_HANDLE		hBundleHandle;
	IN	USHORT			usProtocolType;
	OUT	ULONG			ulSeconds;
} NDISWAN_GET_IDLE_TIME, *PNDISWAN_GET_IDLE_TIME;

//
// Structure used in IOCTL_NDISWAN_SET_DEBUG_INFO
//
typedef struct _NDISWAN_SET_DEBUG_INFO {
	IN	ULONG	ulTraceLevel;
	IN	ULONG	ulTraceMask;
}NDISWAN_SET_DEBUG_INFO, *PNDISWAN_SET_DEBUG_INFO;

//
// Structure used in IOCTL_NDISWAN_ENUM_ADAPTERCB, WAN_ADAPTERCB
//
typedef struct _NDISWAN_ENUMCB {
	OUT	ULONG	ulNumberOfCBs;
	OUT	PVOID	Address[1];
} NDISWAN_ENUMCB, *PNDISWAN_ENUMCB;

//
// Structure used in IOCTL_NDISWAN_GET_NDISWANCB, ADAPTERCB, WAN_ADAPTERCB
//
typedef struct _NDISWAN_DUMPCB {
	IN OUT	PVOID	Address;
	OUT		UCHAR	Buffer[1];
} NDISWAN_DUMPCB, *PNDISWAN_DUMPCB;

#endif			// WAN_PUB

