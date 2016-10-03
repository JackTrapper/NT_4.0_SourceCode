/*++

Copyright (c) 1990  Microsoft Corporation

Copyright (c) 1994 MOTOROLA, INC.  All Rights Reserved.  This file
contains copyrighted material.  Use of this file is restricted
by the provisions of a Motorola Software License Agreement.

Module Name:

    pxsiosup.c

Abstract:

    The module provides the PCI ISA bridge support.

Author:

    Jim Wooldridge (jimw@vnet.ibm.com)


Revision History:


--*/


#include "halp.h"
#include "pxsystyp.h"
#include "eisa.h"
#include "pxsiosup.h"
#include "pxpcisup.h"
#include "pxmemctl.h"
#include "bugcodes.h"


#define  SioId              0x04848086	// UMC 8886

PVOID HalpPciIsaBridgeConfigBase;
extern USHORT Halp8259MaskTable[];
extern PADAPTER_OBJECT MasterAdapterObject;
VOID HalpUpdate8259(KIRQL Irql);



//
// Define the context structure for use by the interrupt routine.
//


typedef BOOLEAN  (*PSECONDARY_DISPATCH)(
  PVOID InterruptRoutine,
  PVOID ServiceContext,
  PVOID TrapFrame
  );

//
// Declare the interrupt structure for profile interrupt
//

KINTERRUPT HalpProfileInterrupt;

//
// The following is the interrupt object used for DMA controller interrupts.
// DMA controller interrupts occur when a memory parity error occurs or a
// programming error occurs to the DMA controller.
//

//
// Declare the interrupt structure for machine checks
//

KINTERRUPT HalpMachineCheckInterrupt;

//
// Declare the interrupt structure for the clock interrupt
//

KINTERRUPT HalpDecrementerInterrupt;

//
//  Map the interrupt controllers priority scheme to NT IRQL values.
//  The SIO prioritizes IRQs as follows:
//     IRQ0, IRQ1, IRQ8 ... IRQ15, IRQ3, IRQ4 ... IRQ7.
//
//  NOTE: The following table must be coordinated with the entries
//        in Halp8259MaskTable in PXIRQL.C
//
KIRQL VectorToIrql[16] = {
//     IRQL	 Vector
//     ----      ------
	26,	// 0	
	25,	// 1
	24,	// 2
	15,	// 3
	14,	// 4
	13,	// 5
	12,	// 6
	11,	// 7
	23,	// 8
	22,	// 9
	21,	// 10
	20,	// 11
	19,	// 12
	18,	// 13
	17,	// 14
	16 };	// 15

KIRQL HalpTranslateVectorToIrql(
   IN ULONG Vector
   )
{ // It is assumed that the caller has checked that Vector is valid (0..15)
  return VectorToIrql[Vector];
}

//
// Add spurious and bogus interrupt counts
//

#if DBG
ULONG HalpSpuriousInterruptCount = 0;
ULONG HalpBogusInterruptCount = 0;
#endif


//
// Define Isa bus interrupt affinity.
//

KAFFINITY HalpIsaBusAffinity;


//
// The following function is called when a machine check occurs.
//

BOOLEAN
HalpHandleMachineCheck(
  IN PKINTERRUPT Interrupt,
  IN PVOID ServiceContext
    );

//
// Define save area for ISA adapter objects.
//

PADAPTER_OBJECT HalpIsaAdapter[8];

//
// Define save area for ISA interrupt mask registers
// and level\edge control registers.
//

USHORT HalpSioInterruptLevel = 0x0000;	// Default to edge-sensitive



BOOLEAN
HalpInitializeInterrupts (
    VOID
    )

/*++

Routine Description:

    This routine is called from phase 0 initialization, it initializes the
    8259 interrupt controller ( currently it masks all 8259 interrupts).


Arguments:

    None.

Return Value:


--*/

{  UCHAR DataByte;
   ULONG Vector;


   //
   // Initialize the SIO interrupt controller.  There are two cascaded
   // interrupt controllers, each of which must initialized with 4 initialize
   // control words.
   //
   DataByte = 0;
   ((PINITIALIZATION_COMMAND_1) &DataByte)->Icw4Needed = 1;
   ((PINITIALIZATION_COMMAND_1) &DataByte)->InitializationFlag = 1;

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt1ControlPort0,
        DataByte
        );

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt2ControlPort0,
        DataByte
        );

   //
   // The second initialization control word sets the interrupt vector to
   // 0-15.
   //

   DataByte = 0;

   WRITE_REGISTER_UCHAR(
       &((PEISA_CONTROL) HalpIoControlBase)->Interrupt1ControlPort1,
       DataByte
       );

   DataByte = 0x08;

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt2ControlPort1,
        DataByte
        );

   //
   // The third initialization control word set the controls for slave mode.
   // The master ICW3 uses bit position and the slave ICW3 uses a numeric.
    //

   DataByte = 1 << SLAVE_IRQL_LEVEL;

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt1ControlPort1,
        DataByte
        );

   DataByte = SLAVE_IRQL_LEVEL;

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt2ControlPort1,
        DataByte
        );

   //
   // The fourth initialization control word is used to specify normal
   // end-of-interrupt mode and not special-fully-nested mode.
   //

   DataByte = 0;
   ((PINITIALIZATION_COMMAND_4) &DataByte)->I80x86Mode = 1;

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt1ControlPort1,
        DataByte
        );

   WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt2ControlPort1,
        DataByte
        );



   //
   // Mask all 8259 interrupts (except the Slave input)
   //

   for (Vector=0; Vector<= HIGHEST_8259_VECTOR; Vector++) {
     HalpDisableSioInterrupt(Vector + DEVICE_VECTORS);
   }
   HalpEnableSioInterrupt(SLAVE_IRQL_LEVEL + DEVICE_VECTORS, Latched);

   //
   // Reserve the external interrupt vector for exclusive use by the HAL.
   //

   PCR->ReservedVectors |= (1 << EXTERNAL_INTERRUPT_VECTOR);

   return TRUE;

}


BOOLEAN
HalpCreateSioStructures (
    VOID
    )

/*++

Routine Description:

    This routine initializes the structures necessary for SIO operations
    and connects the intermediate interrupt dispatcher.

Arguments:

    None.

Return Value:

    If the second level interrupt dispatcher is connected, then a value of
    TRUE is returned. Otherwise, a value of FALSE is returned.

--*/

{

    UCHAR DataByte;
    KIRQL oldIrql;


    //
    // Initialize the Machine Check interrupt handler
    //

    if (HalpEnableInterruptHandler(&HalpMachineCheckInterrupt,
                                   HalpHandleMachineCheck,
                                   NULL,
                                   NULL,
                                   MACHINE_CHECK_VECTOR,
                                   MACHINE_CHECK_LEVEL,
                                   MACHINE_CHECK_LEVEL,
                                   Latched,
                                   FALSE,
                                   0,
                                   FALSE,
                                   InternalUsage,
                                   MACHINE_CHECK_VECTOR
                                   ) == FALSE) {
        KeBugCheck(HAL_INITIALIZATION_FAILED);
    }

    //
    // Enable NMI IOCHK# and PCI SERR#
    //

    DataByte = READ_REGISTER_UCHAR(&((PEISA_CONTROL)HalpIoControlBase)->NmiStatus);
    WRITE_REGISTER_UCHAR(&((PEISA_CONTROL)HalpIoControlBase)->NmiStatus,
                        DataByte & ~DISABLE_IOCHK_NMI & ~DISABLE_PCI_SERR_NMI);

    //
    // Clear the SIO NMI disable bit.  This bit is the high order of the
    // NMI enable register.
    //

    DataByte = 0;


    WRITE_REGISTER_UCHAR(
      &((PEISA_CONTROL) HalpIoControlBase)->NmiEnable,
      DataByte
      );

    //
    // Connect the external interrupt handler
    //

    PCR->InterruptRoutine[EXTERNAL_INTERRUPT_VECTOR] = (PKINTERRUPT_ROUTINE) HalpHandleExternalInterrupt;

    //
    // register the interrupt vector
    //

    HalpRegisterVector(InternalUsage,
                       EXTERNAL_INTERRUPT_VECTOR,
                       EXTERNAL_INTERRUPT_VECTOR,
                       HIGH_LEVEL);




    // Connect directly to the decrementer handler.  This is done
    // directly rather than thru HalpEnableInterruptHandler due to
    // special handling required because the handler calls KdPollBreakIn().
    //

    PCR->InterruptRoutine[DECREMENT_VECTOR] = (PKINTERRUPT_ROUTINE) HalpHandleDecrementerInterrupt;


    //
    // Initialize and connect the Timer 1 interrupt (IRQ0)
    //

    if (HalpEnableInterruptHandler( &HalpProfileInterrupt,
                           (PKSERVICE_ROUTINE) HalpHandleProfileInterrupt,
                           (PVOID) NULL,
                           (PKSPIN_LOCK)NULL,
                           PROFILE_VECTOR,
                           PROFILE_LEVEL,
                           PROFILE_LEVEL,
                           Latched,
                           TRUE,
                           0,
                           FALSE,
                           DeviceUsage,
                           PROFILE_VECTOR
                           ) == FALSE) {
        KeBugCheck(HAL_INITIALIZATION_FAILED);
    }


    //
    // Disable Timer 1; only used by profiling
    //

    HalDisableSystemInterrupt(PROFILE_VECTOR, PROFILE_LEVEL);

    //
    // Set default profile rate
    //

    HalSetProfileInterval(5000);

    //
    // Raise the IRQL while the SIO interrupt controller is initialized.
    //

    KeRaiseIrql(CLOCK2_LEVEL, &oldIrql);

    //
    // Initialize any planar registers
    //

    HalpInitPlanar();

    
    //
    // Enable the clock interrupt
    //
    HalpUpdateDecrementer(1000);        // Get those decrementer ticks going


    //
    // Set ISA bus interrupt affinity.
    //

    HalpIsaBusAffinity = PCR->SetMember;


    //
    // Restore IRQL level.
    //

    KeLowerIrql(oldIrql);


    //
    // DMA command - set assert level
    //

    DataByte = READ_REGISTER_UCHAR(&((PEISA_CONTROL)HalpIoControlBase)->Dma1BasePort.DmaStatus);
    WRITE_REGISTER_UCHAR(&((PEISA_CONTROL)HalpIoControlBase)->Dma1BasePort.DmaStatus,
                        DataByte & ~DACK_ASSERT_HIGH & ~DREQ_ASSERT_LOW);

    //
    // Initialize the DMA mode registers to a default value.
    // Disable all of the DMA channels except channel 4 which is that
    // cascade of channels 0-3.
    //

    WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Dma1BasePort.AllMask,
        0x0F
        );

    WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Dma2BasePort.AllMask,
        0x0E
        );

    return(TRUE);
}

BOOLEAN
HalpMapIoControlSpace (
    VOID
    )

/*++

Routine Description:

    This routine maps the HAL SIO control space for a PowerPC system.

Arguments:

    None.

Return Value:

    If the initialization is successfully completed, then a value of TRUE
    is returned. Otherwise, a value of FALSE is returned.

--*/

{


    PHYSICAL_ADDRESS physicalAddress;

    //
    // Map SIO control space.
    //

    physicalAddress.HighPart = 0;
    physicalAddress.LowPart = IO_CONTROL_PHYSICAL_BASE;
    HalpIoControlBase = MmMapIoSpace(physicalAddress,
                                       PAGE_SIZE * 16,
                                       FALSE);


    if (HalpIoControlBase == NULL)
       return FALSE;
    else
       return TRUE;

}

BOOLEAN
HalpHandleExternalInterrupt(
    IN PKINTERRUPT Interrupt,
    IN PVOID ServiceContext,
    IN PVOID TrapFrame
    )

/*++

Routine Description:

    This routine is entered as the result of an interrupt being generated
    via the vector that is connected to an interrupt object that describes
    the SIO device interrupts. Its function is to call the second
    level interrupt dispatch routine and acknowledge the interrupt at the SIO
    controller.

    N.B. This routine is entered and left with external interrupts disabled.


Arguments:

    Interrupt - Supplies a pointer to the interrupt object.

    ServiceContext - Supplies a pointer to the SIO interrupt acknowledge
        register.

      None.

Return Value:

    Returns the value returned from the second level routine.

--*/

{
    PSECONDARY_DISPATCH SioHandler;
    PKINTERRUPT SioInterrupt;
    USHORT interruptVector;
    BOOLEAN returnValue;
    UCHAR OldIrql;
    USHORT Isr;
    UCHAR Irql;


    //
    // Read the interrupt vector.
    //

    interruptVector = READ_REGISTER_UCHAR(HalpInterruptBase);

    //
    // check for nmi interrupt before we raise irql since we would raise to a
    // bogus level
    //

    if (interruptVector == 0xFF) {

       HalpHandleMachineCheck(NULL, NULL);
    }

    //
    // check for spurious interrupt
    //

    if (interruptVector == SPURIOUS_VECTOR) {

       WRITE_REGISTER_UCHAR(&((PEISA_CONTROL)HalpIoControlBase)->Interrupt1ControlPort0,
                            0x0B);
       Isr = READ_REGISTER_UCHAR(&((PEISA_CONTROL)HalpIoControlBase)->Interrupt1ControlPort0);
       if (!(Isr & 0x80)) {

       //
       // Spurious interrupt
       //

#if DBG
         //DbgPrint("A spurious interrupt occurred. \n");
         HalpSpuriousInterruptCount++;
#endif
         return(0);

       }
    }

    if (interruptVector > HIGHEST_8259_VECTOR) {
#if DBG
         DbgPrint("A bogus interrupt (0x%02x) occurred. \n", interruptVector);
         HalpBogusInterruptCount++;
#endif
      return (0);
    }

    //
    // Translate vector to IRQL and raise IRQL
    //

    Irql = HalpTranslateVectorToIrql(interruptVector);
    KeRaiseIrql( Irql, &OldIrql);

    //
    // Dispatch to the secondary interrupt service routine.
    //

    SioHandler = (PSECONDARY_DISPATCH)
                    PCR->InterruptRoutine[DEVICE_VECTORS + interruptVector];
    SioInterrupt = CONTAINING_RECORD(SioHandler,
                                      KINTERRUPT,
                                      DispatchCode[0]);

    returnValue = SioHandler(SioInterrupt,
                              SioInterrupt->ServiceContext,
                              TrapFrame
                              );

    //
    // Dismiss the interrupt in the SIO interrupt controllers.
    //

    //
    // If this is a cascaded interrupt then the interrupt must be dismissed in
    // both controllers.
    //

    if (interruptVector & 0x08) {

        WRITE_REGISTER_UCHAR(
            &((PEISA_CONTROL) HalpIoControlBase)->Interrupt2ControlPort0,
            NONSPECIFIC_END_OF_INTERRUPT
            );

    }

    WRITE_REGISTER_UCHAR(
        &((PEISA_CONTROL) HalpIoControlBase)->Interrupt1ControlPort0,
        NONSPECIFIC_END_OF_INTERRUPT
        );

    //
    // Lower IRQL but disable external interrupts.
    // Return to caller with interrupts disabled.
    //


    HalpResetIrqlAfterInterrupt(OldIrql);

    return(returnValue);

}

VOID
HalpDisableSioInterrupt(
    IN ULONG Vector
    )

/*++

Routine Description:

    This function Disables the SIO interrupt.

Arguments:

    Vector - Supplies the vector of the ESIA interrupt that is Disabled.

Return Value:

     None.

--*/

{ USHORT MaskBit, i;

  //
  // Calculate the SIO interrupt vector.
  //
  Vector -= DEVICE_VECTORS;

  if (Vector <= HIGHEST_8259_VECTOR) {
    //
    // Generate 8259 mask
    //
    MaskBit = (USHORT) (1 << Vector);

    //
    // Set the mask bit in Halp8259MaskTable
    //
    for (i = 0;  i <= 31; i++) {
      Halp8259MaskTable[i] |= MaskBit;
    }

    // Write new mask values to 8259s
    HalpUpdate8259(PCR->CurrentIrql);
  }
}

VOID
HalpIsaMapTransfer(
    IN PADAPTER_OBJECT AdapterObject,
    IN ULONG Offset,
    IN ULONG Length,
    IN BOOLEAN WriteToDevice
    )
/*++

Routine Description:

    This function programs the SIO DMA controller for a transfer.

Arguments:

    Adapter - Supplies the DMA adapter object to be programed.

    Offset - Supplies the logical address to use for the transfer.

    Length - Supplies the length of the transfer in bytes.

    WriteToDevice - Indicates the direction of the transfer.

Return Value:

    None.

--*/

{

    PUCHAR BytePtr;
    UCHAR adapterMode;
    UCHAR dataByte;
    KIRQL   Irql;


    ASSERT(Offset >= IO_CONTROL_PHYSICAL_BASE);

    adapterMode = AdapterObject->AdapterMode;

    //
    // Check to see if this request is for a master I/O card.
    //

    if (((PDMA_EISA_MODE) &adapterMode)->RequestMode == CASCADE_REQUEST_MODE) {

        //
        // Set the mode, Disable the request and return.
        //

        if (AdapterObject->AdapterNumber == 1) {

            //
            // This request is for DMA controller 1
            //

            PDMA1_CONTROL dmaControl;

            dmaControl = AdapterObject->AdapterBaseVa;

            WRITE_REGISTER_UCHAR( &dmaControl->Mode, adapterMode );

            //
            // Unmask the DMA channel.
            //

            WRITE_REGISTER_UCHAR(
                &dmaControl->SingleMask,
                 (UCHAR) (DMA_CLEARMASK | AdapterObject->ChannelNumber)
                 );

        } else {

            //
            // This request is for DMA controller 1
            //

            PDMA2_CONTROL dmaControl;

            dmaControl = AdapterObject->AdapterBaseVa;

            WRITE_REGISTER_UCHAR( &dmaControl->Mode, adapterMode );

            //
            // Unmask the DMA channel.
            //

            WRITE_REGISTER_UCHAR(
                &dmaControl->SingleMask,
                 (UCHAR) (DMA_CLEARMASK | AdapterObject->ChannelNumber)
                 );

        }

        return;
    }
    //
    // Determine the mode based on the transfer direction.
    //

    ((PDMA_EISA_MODE) &adapterMode)->TransferType = (UCHAR) (WriteToDevice ?
        WRITE_TRANSFER :  READ_TRANSFER);

    BytePtr = (PUCHAR) &Offset;

    if (AdapterObject->Width16Bits) {

        //
        // If this is a 16 bit transfer then adjust the length and the address
        // for the 16 bit DMA mode.
        //

        Length >>= 1;

        //
        // In 16 bit DMA mode the low 16 bits are shifted right one and the
        // page register value is unchanged. So save the page register value
        // and shift the logical address then restore the page value.
        //

        dataByte = BytePtr[2];
        Offset >>= 1;
        BytePtr[2] = dataByte;

    }


    //
    // grab the spinlock for the system DMA controller
    //

    KeAcquireSpinLock( &AdapterObject->MasterAdapter->SpinLock, &Irql );

    //
    // Determine the controller number based on the Adapter number.
    //

    if (AdapterObject->AdapterNumber == 1) {

        //
        // This request is for DMA controller 1
        //

        PDMA1_CONTROL dmaControl;

        dmaControl = AdapterObject->AdapterBaseVa;

        WRITE_REGISTER_UCHAR( &dmaControl->ClearBytePointer, 0 );

        WRITE_REGISTER_UCHAR( &dmaControl->Mode, adapterMode );

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseAddress,
            BytePtr[0]
            );

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseAddress,
            BytePtr[1]
            );

        WRITE_REGISTER_UCHAR(
            ((PUCHAR) &((PEISA_CONTROL) HalpIoControlBase)->DmaPageLowPort) +
            (ULONG)AdapterObject->PagePort,
            BytePtr[2]
            );


        WRITE_REGISTER_UCHAR(
            ((PUCHAR) &((PEISA_CONTROL) HalpIoControlBase)->DmaPageHighPort) +
            (ULONG)AdapterObject->PagePort,
            BytePtr[3]
            );

        //
        // Notify DMA chip of the length to transfer.
        //

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseCount,
            (UCHAR) ((Length - 1) & 0xff)
            );

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseCount,
            (UCHAR) ((Length - 1) >> 8)
            );


        //
        // Set the DMA chip to read or write mode; and unmask it.
        //

        WRITE_REGISTER_UCHAR(
            &dmaControl->SingleMask,
             (UCHAR) (DMA_CLEARMASK | AdapterObject->ChannelNumber)
             );

    } else {

        //
        // This request is for DMA controller 2
        //

        PDMA2_CONTROL dmaControl;

        dmaControl = AdapterObject->AdapterBaseVa;

        WRITE_REGISTER_UCHAR( &dmaControl->ClearBytePointer, 0 );

        WRITE_REGISTER_UCHAR( &dmaControl->Mode, adapterMode );

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseAddress,
            BytePtr[0]
            );

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseAddress,
            BytePtr[1]
            );

        WRITE_REGISTER_UCHAR(
            ((PUCHAR) &((PEISA_CONTROL) HalpIoControlBase)->DmaPageLowPort) +
            (ULONG)AdapterObject->PagePort,
            BytePtr[2]
            );


        WRITE_REGISTER_UCHAR(
            ((PUCHAR) &((PEISA_CONTROL) HalpIoControlBase)->DmaPageHighPort) +
            (ULONG)AdapterObject->PagePort,
            BytePtr[3]
            );

        //
        // Notify DMA chip of the length to transfer.
        //

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseCount,
            (UCHAR) ((Length - 1) & 0xff)
            );

        WRITE_REGISTER_UCHAR(
            &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
            .DmaBaseCount,
            (UCHAR) ((Length - 1) >> 8)
            );


        //
        // Set the DMA chip to read or write mode; and unmask it.
        //

        WRITE_REGISTER_UCHAR(
            &dmaControl->SingleMask,
             (UCHAR) (DMA_CLEARMASK | AdapterObject->ChannelNumber)
             );

    }

    KeReleaseSpinLock (&AdapterObject->MasterAdapter->SpinLock, Irql);

}

VOID
HalpEnableSioInterrupt(
    IN ULONG Vector,
    IN KINTERRUPT_MODE InterruptMode
    )

/*++

Routine Description:

    This function enables the SIO interrupt and sets
    the level/edge register to the requested value.

Arguments:

    Vector - Supplies the vector of the  interrupt that is enabled.

    InterruptMode - Supplies the mode of the interrupt; LevelSensitive or
        Latched.

Return Value:

     None.

--*/

{   USHORT MaskBit, Irql, i;

  //
  // Calculate the SIO interrupt vector.
  //
  Vector -= DEVICE_VECTORS;

  if (Vector <= HIGHEST_8259_VECTOR) {
    //
    // Generate 8259 mask
    //
    MaskBit = (USHORT) ~(1 << Vector);


    //
    // Force interrupts to be latched (edge-triggered) if Big Bend
    //
    if(HalpSystemType == MOTOROLA_BIG_BEND)
      InterruptMode = Latched;

    //
    // Set the level/edge control register.
    //
    if (InterruptMode == LevelSensitive) {
       HalpSioInterruptLevel |= ~MaskBit;
    } else {
       HalpSioInterruptLevel &= MaskBit;
    }

    if (Vector & 0x08) {

        //
        // The interrupt is in controller 2.
        //

        WRITE_REGISTER_UCHAR(
            &((PEISA_CONTROL) HalpIoControlBase)->Interrupt2EdgeLevel,
            (UCHAR) (HalpSioInterruptLevel >> 8)
            );

    } else {

        //
        // The interrupt is in controller 1.
        //

       WRITE_REGISTER_UCHAR(
            &((PEISA_CONTROL) HalpIoControlBase)->Interrupt1EdgeLevel,
            (UCHAR) HalpSioInterruptLevel
            );
    }


    //
    // Clear mask bit in Halp8259MaskTable
    //
    Irql = VectorToIrql[Vector];
    for (i = 0;  i < Irql; i++) {
      Halp8259MaskTable[i] &= MaskBit;
    }

    // Write new mask values to 8259s
    HalpUpdate8259(PCR->CurrentIrql);
  }
}

PADAPTER_OBJECT
HalpAllocateIsaAdapter(
    IN PDEVICE_DESCRIPTION DeviceDescriptor,
    OUT PULONG NumberOfMapRegisters
    )
/*++

Routine Description:

    This function allocates an ISA adapter object according to the
    specification supplied in the device description.  The necessary device
    descriptor information is saved. If there is
    no existing adapter object for this channel then a new one is allocated.
    The saved information in the adapter object is used to set the various DMA
    modes when the channel is allocated or a map transfer is done.

Arguments:

    DeviceDescription - Supplies the description of the device which want to
        use the DMA adapter.

    NumberofMapRegisters - number of map registers required for the adapter
                           object created


Return Value:

    Returns a pointer to the newly created adapter object or NULL if one
    cannot be created.

--*/

{

    PADAPTER_OBJECT adapterObject;
    PVOID adapterBaseVa;
    ULONG channelNumber;
    ULONG numberOfMapRegisters;
    ULONG controllerNumber;
    DMA_EXTENDED_MODE extendedMode;
    UCHAR adapterMode;
    BOOLEAN useChannel;
    ULONG maximumLength;

    //
    // Determine if the the channel number is important.  Master cards
    // do not use a channel number.
    //


    if ((DeviceDescriptor->Master)  && (DeviceDescriptor->InterfaceType != Isa)) {

      useChannel = FALSE;

    } else {

      useChannel = TRUE;
    }

    //
    // Channel 4 cannot be used since it is used for chaining. Return null if
    // it is requested.
    //

    if ((DeviceDescriptor->DmaChannel == 4 ||
        DeviceDescriptor->DmaChannel > 7) && useChannel) {

        return(NULL);
    }

    //
    // Limit the maximum length to 2 GB this is done so that the BYTES_TO_PAGES
    // macro works correctly.
    //

    maximumLength = DeviceDescriptor->MaximumLength & 0x7fffffff;

    //
    // Determine the number of map registers for this device.
    //

    if (DeviceDescriptor->ScatterGather &&
        !(DeviceDescriptor->InterfaceType == Isa &&
        DeviceDescriptor->Master))                   {


        //
        // Scatter gather not supported in SIO
        //

        if (!DeviceDescriptor->Master)

        //
        // one map register will be required when the the SIO supports this
        //
        // numberOfMapRegisters = 1;

           return NULL;


        //
        // Since the device support scatter/Gather then map registers are not
        // required.
        //

        numberOfMapRegisters = 0;

    } else {

        //
        // Determine the number of map registers required based on the maximum
        // transfer length, up to a maximum number.
        //

        numberOfMapRegisters = BYTES_TO_PAGES(maximumLength)
            + 1;
        numberOfMapRegisters = numberOfMapRegisters > MAXIMUM_ISA_MAP_REGISTER ?
            MAXIMUM_ISA_MAP_REGISTER : numberOfMapRegisters;

        //
        // If the device is not a master then it only needs one map register
        // and does scatter/Gather.
        //

        if (DeviceDescriptor->ScatterGather && !DeviceDescriptor->Master) {

            numberOfMapRegisters = 1;
        }
    }

    //
    // Set the channel number number.
    //

    channelNumber = DeviceDescriptor->DmaChannel & 0x03;

    //
    // Set the adapter base address to the Base address register and controller
    // number.
    //

    if (!(DeviceDescriptor->DmaChannel & 0x04)) {

        controllerNumber = 1;
        adapterBaseVa = (PVOID) &((PEISA_CONTROL) HalpIoControlBase)->Dma1BasePort;

    } else {

        controllerNumber = 2;
        adapterBaseVa = &((PEISA_CONTROL) HalpIoControlBase)->Dma2BasePort;

    }

    //
    // Determine if a new adapter object is necessary.  If so then allocate it.
    //

    if (useChannel && HalpIsaAdapter[DeviceDescriptor->DmaChannel] != NULL) {

        adapterObject = HalpIsaAdapter[DeviceDescriptor->DmaChannel];

        if (adapterObject->NeedsMapRegisters) {

            if (numberOfMapRegisters > adapterObject->MapRegistersPerChannel) {

                adapterObject->MapRegistersPerChannel = numberOfMapRegisters;
            }
        }

    } else {

        //
        // Allocate an adapter object.
        //

        adapterObject = (PADAPTER_OBJECT) HalpAllocateAdapter(
            numberOfMapRegisters,
            adapterBaseVa,
            NULL
            );

        if (adapterObject == NULL) {

            return(NULL);

        }

        if (useChannel) {

            HalpIsaAdapter[DeviceDescriptor->DmaChannel] = adapterObject;

        }

        //
        // Set the maximum number of map registers for this channel bus on
        // the number requested and the type of device.
        //

        if (numberOfMapRegisters) {

            //
            // The specified number of registers are actually allowed to be
            // allocated.
            //

            adapterObject->MapRegistersPerChannel = numberOfMapRegisters;

            //
            // Increase the commitment for the map registers.
            //

            if (DeviceDescriptor->Master) {

                //
                // Master I/O devices use several sets of map registers double
                // their commitment.
                //

                MasterAdapterObject->CommittedMapRegisters +=
                    numberOfMapRegisters * 2;

            } else {

                MasterAdapterObject->CommittedMapRegisters +=
                    numberOfMapRegisters;

            }

            //
            // If the committed map registers is significantly greater than the
            // number allocated then grow the map buffer.
            //

            if (MasterAdapterObject->CommittedMapRegisters >
                MasterAdapterObject->NumberOfMapRegisters &&
                MasterAdapterObject->CommittedMapRegisters -
                MasterAdapterObject->NumberOfMapRegisters >
                MAXIMUM_ISA_MAP_REGISTER ) {

                HalpGrowMapBuffers(
                    MasterAdapterObject,
                    INCREMENT_MAP_BUFFER_SIZE
                    );
            }

            adapterObject->NeedsMapRegisters = TRUE;

        } else {

            //
            // No real map registers were allocated.  If this is a master
            // device, then the device can have as may registers as it wants.
            //

            adapterObject->NeedsMapRegisters = FALSE;

            if (DeviceDescriptor->Master) {

                adapterObject->MapRegistersPerChannel = BYTES_TO_PAGES(
                    maximumLength
                    )
                    + 1;

            } else {

                //
                // The device only gets one register.  It must call
                // IoMapTransfer repeatedly to do a large transfer.
                //

                adapterObject->MapRegistersPerChannel = 1;
            }
        }
    }

    adapterObject->ScatterGather = DeviceDescriptor->ScatterGather;

    if (DeviceDescriptor->Master) {

        adapterObject->MasterDevice = TRUE;

    } else {

        adapterObject->MasterDevice = FALSE;

    }

    if (DeviceDescriptor->Master && (DeviceDescriptor->InterfaceType == Isa)) {

        adapterObject->IsaBusMaster = TRUE;

    } else {

        adapterObject->IsaBusMaster = FALSE;

    }

    //
    // If the channel number is not used then we are finished.  The rest of
    // the work deals with channels.
    //

    *NumberOfMapRegisters = adapterObject->MapRegistersPerChannel;

    if (!useChannel) {
        adapterObject->PagePort = (PVOID) (~0x0);
        ((PDMA_EISA_MODE) &adapterMode)->RequestMode = CASCADE_REQUEST_MODE;
        return(adapterObject);
    }

    //
    // Setup the pointers to all the random registers.
    //

    adapterObject->ChannelNumber = (UCHAR) channelNumber;

    if (controllerNumber == 1) {

        switch ((UCHAR)channelNumber) {

        case 0:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel0;
            break;

        case 1:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel1;
            break;

        case 2:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel2;
            break;

        case 3:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel3;
            break;
        }

        //
        // Set the adapter number.
        //

        adapterObject->AdapterNumber = 1;

        //
        // Save the extended mode register address.
        //

        adapterBaseVa =
            &((PEISA_CONTROL) HalpIoControlBase)->Dma1ExtendedModePort;

    } else {

        switch (channelNumber) {
        case 1:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel5;
            break;

        case 2:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel6;
            break;

        case 3:
            adapterObject->PagePort = (PUCHAR) &((PDMA_PAGE) 0)->Channel7;
            break;
        }

        //
        // Set the adapter number.
        //

        adapterObject->AdapterNumber = 2;

        //
        // Save the extended mode register address.
        //
        adapterBaseVa =
            &((PEISA_CONTROL) HalpIoControlBase)->Dma2ExtendedModePort;

    }


    adapterObject->Width16Bits = FALSE;


    //
    // Initialize the extended mode port.
    //

    *((PUCHAR) &extendedMode) = 0;
    extendedMode.ChannelNumber = (UCHAR) channelNumber;

    switch (DeviceDescriptor->DmaSpeed) {
    case Compatible:
        extendedMode.TimingMode = COMPATIBLITY_TIMING;
        break;

    case TypeA:
        extendedMode.TimingMode = TYPE_A_TIMING;
        break;

    case TypeB:
        extendedMode.TimingMode = TYPE_B_TIMING;
        break;

    case TypeC:
        extendedMode.TimingMode = BURST_TIMING;
        break;

    default:
        ObDereferenceObject( adapterObject );
        return(NULL);

    }

    switch (DeviceDescriptor->DmaWidth) {
    case Width8Bits:
        extendedMode.TransferSize = BY_BYTE_8_BITS;
        break;

    case Width16Bits:
        extendedMode.TransferSize = BY_BYTE_16_BITS;

        //
        // Note Width16bits should not be set here because there is no need
        // to shift the address and the transfer count.
        //

        break;

    default:
        ObDereferenceObject( adapterObject );
        return(NULL);

    }

    WRITE_REGISTER_UCHAR( adapterBaseVa, *((PUCHAR) &extendedMode));


    //
    // Initialize the adapter mode register value to the correct parameters,
    // and save them in the adapter object.
    //

    adapterMode = 0;
    ((PDMA_EISA_MODE) &adapterMode)->Channel = adapterObject->ChannelNumber;

    if (DeviceDescriptor->Master) {

        ((PDMA_EISA_MODE) &adapterMode)->RequestMode = CASCADE_REQUEST_MODE;

        //
        // Set the mode, and enable the request.
        //

        if (adapterObject->AdapterNumber == 1) {

            //
            // This request is for DMA controller 1
            //

            PDMA1_CONTROL dmaControl;

            dmaControl = adapterObject->AdapterBaseVa;

            WRITE_REGISTER_UCHAR( &dmaControl->Mode, adapterMode );

            //
            // Unmask the DMA channel.
            //

            WRITE_REGISTER_UCHAR(
                &dmaControl->SingleMask,
                 (UCHAR) (DMA_CLEARMASK | adapterObject->ChannelNumber)
                 );

        } else {

            //
            // This request is for DMA controller 2
            //

            PDMA2_CONTROL dmaControl;

            dmaControl = adapterObject->AdapterBaseVa;

            WRITE_REGISTER_UCHAR( &dmaControl->Mode, adapterMode );

            //
            // Unmask the DMA channel.
            //

            WRITE_REGISTER_UCHAR(
                &dmaControl->SingleMask,
                 (UCHAR) (DMA_CLEARMASK | adapterObject->ChannelNumber)
                 );

       }

    } else if (DeviceDescriptor->DemandMode) {

        ((PDMA_EISA_MODE) &adapterMode)->RequestMode = DEMAND_REQUEST_MODE;

    } else {

        ((PDMA_EISA_MODE) &adapterMode)->RequestMode = SINGLE_REQUEST_MODE;

    }

    if (DeviceDescriptor->AutoInitialize) {

        ((PDMA_EISA_MODE) &adapterMode)->AutoInitialize = 1;

    }

    adapterObject->AdapterMode = adapterMode;

    return(adapterObject);
}

ULONG
HalReadDmaCounter(
    IN PADAPTER_OBJECT AdapterObject
    )
/*++

Routine Description:

    This function reads the DMA counter and returns the number of bytes left
    to be transferred.

Arguments:

    AdapterObject - Supplies a pointer to the adapter object to be read.

Return Value:

    Returns the number of bytes still to be transferred.

--*/

{
    ULONG count=0;
    ULONG high;

    if (AdapterObject->PagePort) {

        //
        // Determine the controller number based on the Adapter number.
        //

        if (AdapterObject->AdapterNumber == 1) {

            //
            // This request is for DMA controller 1
            //

            PDMA1_CONTROL dmaControl;

            dmaControl = AdapterObject->AdapterBaseVa;

            //
            // Initialize count to a value which will not match.
            //

            count = 0xFFFF00;

            //
            // Loop until the same high byte is read twice.
            //

            do {

                high = count;

                WRITE_REGISTER_UCHAR( &dmaControl->ClearBytePointer, 0 );

                //
                // Read the current DMA count.
                //

                count = READ_REGISTER_UCHAR(
                    &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
                    .DmaBaseCount
                    );

                count |= READ_REGISTER_UCHAR(
                    &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
                    .DmaBaseCount
                    ) << 8;

            } while ((count & 0xFFFF00) != (high & 0xFFFF00));

        } else {

            //
            // This request is for DMA controller 2
            //

            PDMA2_CONTROL dmaControl;

            dmaControl = AdapterObject->AdapterBaseVa;

            //
            // Initialize count to a value which will not match.
            //

            count = 0xFFFF00;

            //
            // Loop until the same high byte is read twice.
            //

            do {

                high = count;

                WRITE_REGISTER_UCHAR( &dmaControl->ClearBytePointer, 0 );

                //
                // Read the current DMA count.
                //

                count = READ_REGISTER_UCHAR(
                    &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
                    .DmaBaseCount
                    );

                count |= READ_REGISTER_UCHAR(
                    &dmaControl->DmaAddressCount[AdapterObject->ChannelNumber]
                    .DmaBaseCount
                    ) << 8;

            } while ((count & 0xFFFF00) != (high & 0xFFFF00));

        }

        //
        // The DMA counter has a bias of one and can only be 16 bit long.
        //

        count = (count + 1) & 0xFFFF;

    }

    return(count);
}


VOID
HalpHandleIoError (
    VOID
    )

{

    UCHAR   StatusByte;


    //
    // Read NMI status
    //

    StatusByte = READ_REGISTER_UCHAR(&((PEISA_CONTROL) HalpIoControlBase)->NmiStatus);

    //
    // Test for PCI bus error
    //

    if (StatusByte & 0x40) {
        HalDisplayString ("NMI: IOCHK\n");
    }

    //
    // Test for ISA IOCHK
    //

    if (StatusByte & 0x80) {
        HalDisplayString ("NMI: PCI System Error\n");
    }

}


