/*++

Copyright (c) 1992  Microsoft Corporation

Module Name:

    tok162sw.h

Abstract:

    The hardware-related definitions for the IBM Token-Ring 16/4 II
    ISA driver.

Author:

    Kevin Martin (kevinma) 1-Feb-1994

Environment:

    Architecturally, there is an assumption in this driver that we are
    on a little endian machine.

Notes:

    optional-notes

Revision History:


--*/

#include <ndis.h>
#include <tok162hw.h>

//
// Debugging flags.
//
#if DBG

//
// Degrees of debugging output. Can be OR'd in any combination.
//
#define TOK162_DEBUG_LOUD       0x1
#define TOK162_DEBUG_VERY_LOUD  0x2
#define TOK162_DEBUG_EXTRA_LOUD 0x4
#define TOK162_DEBUG_CURRENT    0x8

//
// The degree of debugging output being displayed on the debugger currently.
// Defined in TOK162.C.
//
extern  UCHAR                   Tok162Debug;

//
// Macros that decide on the debugging based on Tok162Debug.
//
#define LOUD_DEBUG(A)       if (Tok162Debug & TOK162_DEBUG_LOUD) { A ; }
#define VERY_LOUD_DEBUG(A)  if (Tok162Debug & TOK162_DEBUG_VERY_LOUD) { A ; }
#define EXTRA_LOUD_DEBUG(A) if (Tok162Debug & TOK162_DEBUG_EXTRA_LOUD) { A ; }
#define CURRENT_DEBUG(A)    if (Tok162Debug & TOK162_DEBUG_CURRENT) { A ; }

//
// The size of the logging array
//
#define LOG_SIZE                256

//
// Pointer for the logging array. Allocated in TOK162.C
// (AllocateAdapterMemory)
//
extern  PUCHAR                  Tok162Log;

//
// The current index into the logging array.
//
extern  USHORT                  Tok162LogPlace;

//
// Logging macro.
//
#define IF_LOG(ch) { Tok162Log[Tok162LogPlace] = (ch); \
                     Tok162LogPlace = (Tok162LogPlace + 1) % LOG_SIZE; }

#else // if dbg

//
// Make sure all of the debugging and logging calls resolve to NULL
//
#define LOUD_DEBUG(A)
#define VERY_LOUD_DEBUG(A)
#define EXTRA_LOUD_DEBUG(A)
#define CURRENT_DEBUG(A)

#define IF_LOG(ch) { }

#endif // if dbg

//
// Version constants for this driver
//
#define TOK162_NDIS_MAJOR_VERSION   3
#define TOK162_NDIS_MINOR_VERSION   0

//
// Macro to allocate physical memory.
//
#define TOK162_ALLOC_PHYS(_Status, _pBuffer, _Length) \
{ \
    NDIS_PHYSICAL_ADDRESS MinusOne = NDIS_PHYSICAL_ADDRESS_CONST (-1, -1); \
    *(_Status) = NdisAllocateMemory( \
                     (PVOID*)(_pBuffer), \
                     (_Length), \
                     0, \
                     MinusOne); \
}

//
// Macro to free physical memory previously allocated.
//
#define TOK162_FREE_PHYS(_Buffer) NdisFreeMemory((_Buffer), 0, 0)

//
// Enumeration for the reset stages.
//
enum ResetStates{InitialInit,
                 CheckReset,
                 CheckResetRetry,
                 DoTheInit,
                 CheckInit,
                 CheckInitRetry,
                 DoOpen
                 };

//
// Adapter structure is defined further down.
//
struct _TOK162_ADAPTER;

//
// This structure defines the global data needed by the driver.
//
typedef struct _TOK162_GLOBAL_DATA {

    //
    // Spinlock to protect fields in this structure.
    //
    NDIS_SPIN_LOCK              Lock;

    //
    // Chain of Adapters
    //
    LIST_ENTRY                  AdapterList;

    //
    // Handle to our Mac
    //
    NDIS_HANDLE                 TOK162MacHandle;

    //
    // Handle for NdisTerminateWrapper
    //
    NDIS_HANDLE                 TOK162NdisWrapperHandle;

    //
    // Driver object
    //
    PDRIVER_OBJECT              TOK162DriverObject;

} TOK162_GLOBAL_DATA, *PTOK162_GLOBAL_DATA;

//
// In addition to the Command Block fields which the TOK162HW.H
// defines, we need some additional fields for our own purposes.
// To ensure that these fields are properly aligned (and to
// ensure that the actual Command Block is properly aligned)
// we'll defined a Super Command Block.  This structure will
// contain a "normal" TOK162 Command Block plus some additional
// fields. This structure is used for both commands and transmits.
//
typedef struct _TOK162_SUPER_COMMAND_BLOCK {

    //
    // The actual TOK162 Command Block.
    //
    TOK162_COMMAND_BLOCK        Hardware;

    //
    // This contains the virtual address of the next pending command.
    //
    struct _TOK162_SUPER_COMMAND_BLOCK *NextCommand;

    //
    // Is this from a set
    //
    BOOLEAN                     Set;

    //
    // If this is a public (adapter-wide) command block, then
    // this will contain this block's index into the adapter's
    // command queue.
    //
    USHORT                      CommandBlockIndex;

    //
    // This field is used to timestamp the command blocks
    // as they are placed into the command queue.  If a
    // block fails to execute, the adapter will get a kick in the ass to
    // start it up again.
    //
    BOOLEAN                     Timeout;

    //
    // Count of the number of times we have retried a command.
    //
    UCHAR                       TimeoutCount;

} TOK162_SUPER_COMMAND_BLOCK, *PTOK162_SUPER_COMMAND_BLOCK;

//
// In addition to the Receive Entry fields which the TOK162HW.H
// defines, we need some additional fields for our own purposes.
// To ensure that these fields are properly aligned (and to
// ensure that the actual Receive Entry is properly aligned)
// we'll defined a Super Receive Entry.  This structure will
// contain a "normal" TOK162 Receive Entry plus some additional
// fields.
//
typedef struct _TOK162_SUPER_RECEIVE_LIST {

    //
    // The actual TOK162 Receive List.
    //
    TOK162_RECEIVE_LIST         Hardware;

    //
    // This contains the virtual address of this Receive List's
    // frame buffer.
    //
    PVOID                       ReceiveBuffer;
    NDIS_PHYSICAL_ADDRESS       ReceiveBufferPhysical;

    //
    // This contains the virtual address of the next
    // Receive List in the Receive Queue.
    //
    struct _TOK162_SUPER_RECEIVE_LIST *NextEntry;

    //
    // Points to an Mdl which points to this buffer
    //
    PNDIS_BUFFER                FlushBuffer;

    //
    // Offset in adapter for this receive list
    //
    USHORT                      AdapterOffset;

} TOK162_SUPER_RECEIVE_LIST, *PTOK162_SUPER_RECEIVE_LIST;

//
// The number of receive lists/buffers
//
#define RECEIVE_LIST_COUNT                3

//
// In addition to the Transmit Entry fields which the TOK162HW.H
// defines, we need some additional fields for our own purposes.
// To ensure that these fields are properly aligned (and to
// ensure that the actual Transmit Entry is properly aligned)
// we'll defined a Super Transmit Entry.  This structure will
// contain a "normal" TOK162 Transmit Entry plus some additional
// fields.
//
typedef struct _TOK162_SUPER_TRANSMIT_LIST {

    //
    // The actual TOK162 Receive List.
    //
    TOK162_TRANSMIT_LIST         Hardware;

    //
    // This contains the virtual address of this Transmit List's
    // frame buffer.
    //
    PVOID                       TransmitBuffer;
    NDIS_PHYSICAL_ADDRESS       TransmitBufferPhysical;

    //
    // This contains the virtual address of the next
    // Transmit List in the Transmit Queue.
    //
    struct _TOK162_SUPER_TRANSMIT_LIST *NextEntry;

    //
    // This contains the virtual address of the next
    // active Transmit List in the active Transmit Queue.
    //
    struct _TOK162_SUPER_TRANSMIT_LIST *NextActive;

    //
    // Packet associated with this list
    //
    PNDIS_PACKET                Packet;

    //
    // Timeout watch
    //
    BOOLEAN                     Timeout;

    //
    // Count of the number of times we have retried a command.
    //
    UCHAR                       TimeoutCount;

    //
    // First adapter entry on board.
    //
    USHORT                      FirstEntry;

    //
    // Number of NDIS Buffers.
    //
    UINT                        NumberOfBuffers;

    //
    // Number of Map Registers Used
    //
    UINT                        NumberOfMapRegisters;

    //
    // Boolean indicating whether the above buffer was used
    //
    BOOLEAN                     UsedBuffer;

    //
    // flush buffer
    //
    PNDIS_BUFFER                FlushBuffer;

} TOK162_SUPER_TRANSMIT_LIST, *PTOK162_SUPER_TRANSMIT_LIST;

//
// The number of transmit lists and the number of adapter entries we
// reserve for transmits. The product of these numbers must be equal
// to TRANSMIT_ENTRIES as defined in tok162hw.h.
//
#define TRANSMIT_LIST_COUNT               3
#define MAX_BUFFERS_PER_TRANSMIT          5

//
// Adapter Structure
//
typedef struct _TOK162_ADAPTER {

    //
    // Handle given by NDIS when the miniport was initialized.
    //
    NDIS_HANDLE                 MiniportAdapterHandle;

    //
    // Interrupt pointers and variables for the adapter
    //
    NDIS_MINIPORT_INTERRUPT     Interrupt;
    USHORT                      InterruptLevel;

    //
    // Are we running at 16Mbps?
    //
    BOOLEAN                     Running16Mbps;

    //
    // Pointers for the System Command Block for the adapter
    //
    PSCB                        Scb;
    NDIS_PHYSICAL_ADDRESS       ScbPhysical;

    //
    // Pointers for the System Status Block for the adapter
    //
    PSSB                        Ssb;
    NDIS_PHYSICAL_ADDRESS       SsbPhysical;

    //
    // Offset in adapter memory of the communication block
    //
    USHORT                      CommunicationOffset;

    //
    // Command queue and related variables
    //
    PTOK162_SUPER_COMMAND_BLOCK CommandQueue;
    NDIS_PHYSICAL_ADDRESS       CommandQueuePhysical;

    //
    // Index to next command block
    //
    UINT                        NextCommandBlock;

    //
    // Number of command blocks available for use
    //
    UINT                        NumberOfAvailableCommandBlocks;

    //
    // Active command.
    //
    PTOK162_SUPER_COMMAND_BLOCK CommandOnCard;

    //
    // First pending command.
    //
    PTOK162_SUPER_COMMAND_BLOCK WaitingCommandHead;

    //
    // Last pending command.
    //
    PTOK162_SUPER_COMMAND_BLOCK WaitingCommandTail;

    //
    // Current packet filter on adapter
    //
    UINT                        CurrentPacketFilter;

    //
    // Is there an outstanding request
    //
    BOOLEAN                     RequestInProgress;

    //
    // Number of bytes needed and written.
    //
    PUINT                       BytesWritten;
    PUINT                       BytesNeeded;

    //
    // Current Oid processing.
    //
    NDIS_OID                    Oid;

    //
    // Buffer and length of buffer used for doing query/set info calls.
    //
    PVOID                       InformationBuffer;
    UINT                        InformationBufferLength;

    //
    // Current interrupt value
    //
    USHORT                      InterruptMask;

    //
    // Command that caused the interrupt
    //
    USHORT                      SsbCommand;

    //
    // The status variables that are saved as the result of an interrupt
    //
    USHORT                      SsbStatus1;
    USHORT                      SsbStatus2;
    USHORT                      SsbStatus3;

    //
    // The I/O Base address of the adapter.
    //
    ULONG                       PortIOBase;
    PVOID                       PortIOAddress;

    //
    // Pointers and variables for the Open block for the adapter
    //
    POPEN_COMMAND               Open;
    NDIS_PHYSICAL_ADDRESS       OpenPhysical;

    //
    // The network address for the adapter and the current one being used.
    //
    CHAR                        NetworkAddress[TOK162_LENGTH_OF_ADDRESS];
    CHAR                        CurrentAddress[TOK162_LENGTH_OF_ADDRESS];

    //
    // Functional and Group Addresses for the adapter
    //
    ULONG                       FunctionalAddress;
    ULONG                       GroupAddress;

    //
    // Pointer to the Receive Queue.
    //
    PTOK162_SUPER_RECEIVE_LIST  ReceiveQueue;
    NDIS_PHYSICAL_ADDRESS       ReceiveQueuePhysical;

    //
    // Pointer to the current receive list
    //
    PTOK162_SUPER_RECEIVE_LIST  ReceiveQueueCurrent;

    //
    // Number of frame header bytes in the buffer.
    //
    USHORT                      SizeOfReceivedHeader;

    //
    // Count of the receive buffers
    //
    UINT                        NumberOfReceiveBuffers;

    //
    // Size of the receive buffer, based on the ring speed.
    //
    USHORT                      ReceiveBufferSize;

    //
    // The receive flush buffer pool handle
    //
    PNDIS_HANDLE                FlushBufferPoolHandle;

    //
    // Indicator for receive complete
    //
    BOOLEAN                     DoReceiveComplete;

    //
    // Pointer to the Transmit Queue.
    //
    PTOK162_SUPER_TRANSMIT_LIST TransmitQueue;
    NDIS_PHYSICAL_ADDRESS       TransmitQueuePhysical;

    //
    // Spinlock for transmits
    //
    NDIS_SPIN_LOCK              TransmitLock;

    //
    // Pointer to the head of the waiting transmit queue.
    //
    PTOK162_SUPER_TRANSMIT_LIST AvailableTransmit;

    //
    // Pointers for the active transmit queue.
    //
    PTOK162_SUPER_TRANSMIT_LIST ActiveTransmitHead;
    PTOK162_SUPER_TRANSMIT_LIST ActiveTransmitTail;

    //
    // Array of transmit entries
    //
    TOK162_TRANSMIT_LIST        DownLoadArray[MAX_BUFFERS_PER_TRANSMIT];

    //
    // Next available adapter transmit slot
    //
    USHORT                      AdapterTransmitIndex;
    USHORT                      TransmitCount;

    //
    // Count of the transmit blocks
    //
    UINT                        NumberOfAvailableTransmitBlocks;

    //
    // Flag that when enabled lets routines know that a reset
    // is in progress.
    //
    BOOLEAN                     ResetInProgress;

    //
    // Are we doing the initial initialization?
    //
    BOOLEAN                     InitialInit;

    //
    // Has the initial open completed?
    //
    BOOLEAN                     InitialOpenComplete;

    //
    // Has the initial receive command been sent
    //
    BOOLEAN                     InitialReceiveSent;

    //
    // Reset State
    //
    USHORT                      ResetState;

    //
    // Variables to keep track of the number of retries attempted during
    // a reset
    //
    USHORT                      ResetRetries;
    USHORT                      InitRetries;

    //
    // Result of Reset command
    //
    NDIS_STATUS                 ResetResult;

    //
    // Offsets into adapter memory for different structures.
    // These are obtained at initialization time and the values
    // are read using the READ.ADAPTER DMA command.
    //
    USHORT                      UniversalAddress;
    USHORT                      MicrocodeLevel;
    USHORT                      AdapterAddresses;
    USHORT                      AdapterParms;
    USHORT                      MacBuffer;

    //
    // Buffer for READ.ERROR.LOG
    //
    PTOK162_ERRORLOG            ErrorLog;
    NDIS_PHYSICAL_ADDRESS       ErrorLogPhysical;

    //
    // Buffer for READ.ADAPTER for node addresses. If more info is needed
    // in the future, this will have to be changed as the current addresses
    // are being stored here (func,node,group)
    //
    PTOK162_READADAPTERBUF      AdapterBuf;
    NDIS_PHYSICAL_ADDRESS       AdapterBufPhysical;

    //
    // Counters to hold the various number of errors/statistics for both
    // reception and transmission.
    //
    UINT                        ReceiveCongestionError;
    UINT                        LineError;
    UINT                        LostFrameError;
    UINT                        BurstError;
    UINT                        FrameCopiedError;
    UINT                        TokenError;
    UINT                        InternalError;
    UINT                        ARIFCIError;
    UINT                        AbortDelimeter;
    UINT                        DMABusError;
    ULONG                       TotalSends;
    ULONG                       RegularPackets;
    ULONG                       ConstrainPackets;

    //
    // Packet counts
    //
    UINT                        GoodTransmits;
    UINT                        GoodReceives;
    UINT                        TransmitsQueued;
    UINT                        BadTransmits;
    UINT                        BadReceives;

    //
    // Timer objects for TOK162InterruptHandler and TOK162ResetHandler
    //
    NDIS_MINIPORT_TIMER         DeferredTimer;
    NDIS_MINIPORT_TIMER         ResetTimer;

    //
    // Holds number of different types of RING.STATUS.CHANGE
    // indications.
    //
    UINT                        SignalLoss;
    UINT                        HardError;
    UINT                        SoftError;
    UINT                        TransmitBeacon;
    UINT                        LobeWireFault;
    UINT                        AutoRemovalError;
    UINT                        RemoveReceived;
    UINT                        CounterOverflow;
    UINT                        SingleStation;
    UINT                        RingRecovery;

    //
    // Current state of the ring.
    //
    NDIS_802_5_RING_STATE       CurrentRingState;

    //
    // Pointer to the initialization block
    //
    PADAPTER_INITIALIZATION     InitializationBlock;
    NDIS_PHYSICAL_ADDRESS       InitializationBlockPhysical;

    //
    // Pointer to the initialization Dma Test block
    //
    PADAPTER_INITIALIZATION     DmaTest;
    NDIS_PHYSICAL_ADDRESS       DmaTestPhysical;

    //
    // This points to the next adapter registered for the same Miniport
    //
    LIST_ENTRY                  AdapterList;

} TOK162_ADAPTER,*PTOK162_ADAPTER;

//
// Given a MiniportContextHandle return the PTOK162_ADAPTER
// it represents.
//
#define PTOK162_ADAPTER_FROM_CONTEXT_HANDLE(Handle) \
    ((PTOK162_ADAPTER)(Handle))

//
// Define our block of global data.  The actual data resides in TOK162.C.
//
extern TOK162_GLOBAL_DATA        TOK162Globals;

//
// This record type is inserted into the MiniportReserved portion
// of the packet header when the packet is going through the
// staged allocation of buffer space prior to the actual send.
//
typedef struct _TOK162_RESERVED {

    //
    // Pointer to next packet. We use this as our queueing mechanism.
    //
    PNDIS_PACKET                NextEntry;

    //
    // Reserved section of this structure.
    //
    UCHAR                       BufferIndex;
    UCHAR                       FirstEntry;
    UCHAR                       NumberBuffers;
    UCHAR                       Reserved;


} TOK162_RESERVED,*PTOK162_RESERVED;

//
// This macro will return a pointer to the TOK162 reserved portion
// of a packet given a pointer to a packet.
//
#define PTOK162_RESERVED_FROM_PACKET(Packet) \
    ((PTOK162_RESERVED)((Packet)->MiniportReserved))

#include <tok162pr.h>
