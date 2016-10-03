

/*++

Copyright (c) 1990  Microsoft Corporation

Copyright (c) 1994 MOTOROLA, INC.  All Rights Reserved.  This file
contains copyrighted material.  Use of this file is restricted
by the provisions of a Motorola Software License Agreement.

Copyright (c) 1996  International Business Machines Corporation

Module Name:

    pxmemctl.c

Abstract:

    The module initializes any planar registers.
    This module also implements machince check parity error handling.

Author:

    Jim Wooldridge (jimw@austin.vnet.ibm.com)


Revision History:

    T. White  -- Added dword I/O to allow GXT150P to work correctly

Special Note:

    Please make sure that the dword I/O mechanisms are carried
    forward for any box which is to support the GXT150P graphics
    adapter. The GXT150P graphics adapter runs in any PowerPC
    machine with a standard PCI bus connector.


--*/

#include "halp.h"
#include "pci.h"
#include "pcip.h"

extern PVOID HalpPciConfigBase;
#define PCI_INTERRUPT_ROUTING_SCSI  13
#define PCI_INTERRUPT_ROUTING_OTHER 15

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE,HalpGetPCIIrq)
#endif

ULONG HalpPciConfigSlot[] = {  0x0800,
                               0x1000,
                               0x2000,
                               0x4000,
                               0x8000,
                              0x10000,
                              0x20000,
                              0x40000,
                            };
ULONG HalpPciMaxSlots = 7;

ULONG
HalpTranslatePciSlotNumber (
    ULONG BusNumber,
    ULONG SlotNumber
    )
/*++

Routine Description:

    This routine translate a PCI slot number to a PCI device number.
    This is a sandalfoot memory map implementation.

Arguments:

    None.

Return Value:

    Returns length of data written.

--*/

{
   //
   // Sandalfoot only has 1 PCI bus so bus number is unused
   //

   UNREFERENCED_PARAMETER(BusNumber);

   return ((ULONG) ((PUCHAR) HalpPciConfigBase + HalpPciConfigSlot[SlotNumber]));

}


ULONG
HalpPhase0SetPciDataByOffset (
    ULONG BusNumber,
    ULONG SlotNumber,
    PUCHAR Buffer,
    ULONG Offset,
    ULONG Length
    )

/*++

Routine Description:

    This routine writes to PCI configuration space prior to bus handler installation.

Arguments:

    None.

Return Value:

    Returns length of data written.

--*/

{
   PUCHAR to;
   PUCHAR from;
   ULONG tmpLength;
   PULONG ulong_to, ulong_from;

   if (SlotNumber < HalpPciMaxSlots) {

      to = (PUCHAR)HalpPciConfigBase + HalpPciConfigSlot[SlotNumber];
      to += Offset;
      from = Buffer;

      // The GXT150P graphics adapter requires the use of dword I/O
      // to some of its PCI configuration registers. Therefore, this
      // code uses dword I/O when possible.

      // If the bus address is not dword aligned or the length
      // is not a multiple of 4 (dword size) bytes, then use byte I/O
      if(((ULONG)to & 0x3)||(Length & 0x3)){
          tmpLength = Length;
          while (tmpLength > 0) {
              *to++ = *from++;
              tmpLength--;
          }
      // If the bus address is dword aligned and the length is
      // a multiple of 4 (dword size) bytes, then use dword I/O
      }else{
          ulong_to = (PULONG) to;
          ulong_from = (PULONG) from;
          tmpLength = Length >> 2;
          while (tmpLength > 0) {
              *ulong_to++ = *ulong_from++;
              tmpLength--;
          }
      }

      return(Length);
   }
   else {
      return (0);
   }
}

ULONG
HalpPhase0GetPciDataByOffset (
    ULONG BusNumber,
    ULONG SlotNumber,
    PUCHAR Buffer,
    ULONG Offset,
    ULONG Length
    )

/*++

Routine Description:

    This routine reads PCI config space prior to bus handlder installation.

Arguments:

    None.

Return Value:

    Amount of data read.

--*/

{
   PUCHAR to;
   PUCHAR from;
   ULONG tmpLength;
   PULONG ulong_to, ulong_from;

   if (SlotNumber < HalpPciMaxSlots) {

      from = (PUCHAR)HalpPciConfigBase + HalpPciConfigSlot[SlotNumber];
      from += Offset;
      to = Buffer;

      // The GXT150P graphics adapter requires the use of dword I/O
      // to some of its PCI configuration registers. Therefore, this
      // code uses dword I/O when possible.

      // If the bus address is not dword aligned or the length
      // is not a multiple of 4 (dword size) bytes, then use byte I/O
      if(((ULONG)from & 0x3)||(Length & 0x3)){
          tmpLength = Length;
          while (tmpLength > 0) {
              *to++ = *from++;
              tmpLength--;
          }
      // If the bus address is dword aligned and the length is
      // a multiple of 4 (dword size) bytes, then use dword I/O
      }else{
          ulong_to = (PULONG) to;
          ulong_from = (PULONG) from;
          tmpLength = Length >> 2;
          while (tmpLength > 0) {
              *ulong_to++ = *ulong_from++;
              tmpLength--;
          }
      }

      return(Length);
   }
   else {
      return (0);
   }
}

NTSTATUS
HalpGetPCIIrq (
    IN PBUS_HANDLER     BusHandler,
    IN PBUS_HANDLER     RootHandler,
    IN PCI_SLOT_NUMBER  PciSlot,
    OUT PSUPPORTED_RANGE    *Interrupt
    )
{
    ULONG                   buffer[PCI_COMMON_HDR_LENGTH/sizeof(ULONG)];
    PPCI_COMMON_CONFIG      PciData;

#define PCI_VENDOR_NCR 0x1000

    PciData = (PPCI_COMMON_CONFIG) buffer;
    HalGetBusData (
        PCIConfiguration,
        BusHandler->BusNumber,
        PciSlot.u.AsULONG,
        PciData,
        PCI_COMMON_HDR_LENGTH
        );

    if (PciData->VendorID == PCI_INVALID_VENDORID  ||
        PCI_CONFIG_TYPE (PciData) != 0) {
        return STATUS_UNSUCCESSFUL;
    }

    *Interrupt = ExAllocatePool (PagedPool, sizeof (SUPPORTED_RANGE));
    if (!*Interrupt) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory (*Interrupt, sizeof (SUPPORTED_RANGE));

    if (PciSlot.u.bits.DeviceNumber == 1) {
       (*Interrupt)->Base  = PCI_INTERRUPT_ROUTING_SCSI;
       (*Interrupt)->Limit = PCI_INTERRUPT_ROUTING_SCSI;
    } else {
       (*Interrupt)->Base  = PCI_INTERRUPT_ROUTING_OTHER;
       (*Interrupt)->Limit = PCI_INTERRUPT_ROUTING_OTHER;
    }

#if defined(SOFT_HDD_LAMP)

    if ( (PciData->BaseClass == 1) ||
       ( (PciData->VendorID == PCI_VENDOR_NCR) && (PciData->DeviceID == 1) ) ) {
        //
        // This device is a Mass Storage Controller, set flag to
        // turn on the HDD Lamp when interrupts come in on this
        // vector.
        //
        // N.B. We recognize NCR 810 controllers as they were implemented
        // before class codes.
        //

        extern ULONG HalpMassStorageControllerVectors;

        HalpMassStorageControllerVectors |= 1 << (*Interrupt)->Base;
    }

#endif

    return STATUS_SUCCESS;
}

VOID
HalpMapPlugInPciBridges(
   UCHAR NoBuses
   )

/*++

Routine Description:

   Looks for any unexpected (plug-in) PCI-PCI bridges so
   that interrupts can be mapped from these buses back
   into the interrupt controller.

Arguments:

   NoBuses -- This is the number of buses that HalpGetPciBridgeConfig found

Return Value:

    none

--*/
{
    // Sandalfoot doesn't support plug-in PCI busses!!!

    return;
}

