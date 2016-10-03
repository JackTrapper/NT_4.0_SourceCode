//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1994.
//
//  File:       nt.cxx
//
//  Contents:   Functions that wrap fdisk partition engine functions,
//              including functions that manipulate fdisk engine structures
//              (REGIONs, for example).
//
//  History:    5-Dec-92    TedM    Created
//              22-Jan-94   BobRi   Misc cleanup
//
//----------------------------------------------------------------------------

#include "headers.hxx"
#pragma hdrstop

#include <string.h>
#include <stdio.h>

#include "nt.hxx"
#include "ntlow.hxx"

//////////////////////////////////////////////////////////////////////////////

// Pagefile support structures.

typedef struct _PAGEFILE_LOCATION
{
    struct _PAGEFILE_LOCATION* Next;
    WCHAR                      DriveLetter;
} PAGEFILE_LOCATION, *PPAGEFILE_LOCATION;

PPAGEFILE_LOCATION PagefileHead = NULL;

// For some reason the file systems don't like being accessed shortly after
// a format or lock event.

#define SLEEP_TIME (1000*2) // 2 seconds

//
// These partition ID's are for systems recognized by WINDISK,
// even though they don't appear in ntdddisk.h.
//
#define PARTITION_OS2_BOOT              0xa
#define PARTITION_EISA                  0x12


WCHAR SysIdName[100];

PWSTR
GetWideSysIDName(
    IN UCHAR SysID
    )
{
    DWORD stringId;

    switch (SysID)
    {
        case PARTITION_ENTRY_UNUSED:
            stringId = IDS_PARTITION_FREE;
            break;

        case PARTITION_XENIX_1:
            stringId = IDS_PARTITION_XENIX1;
            break;

        case PARTITION_XENIX_2:
            stringId = IDS_PARTITION_XENIX2;
            break;

        case PARTITION_OS2_BOOT:
            stringId = IDS_PARTITION_OS2_BOOT;
            break;

        case PARTITION_EISA:
            stringId = IDS_PARTITION_EISA;
            break;

        case PARTITION_UNIX:
            stringId = IDS_PARTITION_UNIX;
            break;

        case PARTITION_PREP:
#ifdef _PPC_
            stringId = IDS_PARTITION_POWERPC;
#else
            // If not on a PPC platform, assume this is Eisa related
            stringId = IDS_PARTITION_EISA;
#endif
            break;

        default:
            stringId = IDS_UNKNOWN;
            break;
    }

    LoadString(
            g_hInstance,
            stringId,
            SysIdName,
            ARRAYLEN(SysIdName));

    return SysIdName;
}


ULONG
MyDiskRegistryGet(
    OUT PDISK_REGISTRY *DiskRegistry
    )

/*++

Routine Description:

    Allocate memory for the size of the disk registry, obtain
    the registry contents (if any) and return the pointer to the
    allocated memory.

Arguments:

    A pointer to a disk registry pointer.

Return Value:

    status indicating success or failure.

--*/

{
    ULONG           length;
    PDISK_REGISTRY  diskRegistry;
    NTSTATUS        status;

    while (   ((status = DiskRegistryGet(NULL, &length)) == STATUS_NO_MEMORY)
           || (status == STATUS_INSUFFICIENT_RESOURCES))
    {
        ConfirmOutOfMemory();
    }

    if (!NT_SUCCESS(status))
    {
        return EC(status);
    }

    diskRegistry = (PDISK_REGISTRY)Malloc(length);

    while (   ((status = DiskRegistryGet(diskRegistry, &length)) == STATUS_NO_MEMORY)
           || (status == STATUS_INSUFFICIENT_RESOURCES))
    {
        ConfirmOutOfMemory();
    }

    if (NT_SUCCESS(status))
    {
        LOG_DISK_REGISTRY("MyDiskRegistryGet", diskRegistry);

        *DiskRegistry = diskRegistry;
    }

    return EC(status);
}


ULONG
FormDiskSignature(
    VOID
    )

/*++

Routine Description:

    Return a ULONG disk signature.  This is derived from the current
    system time.

Arguments:

    None

Return Value:

    A 32-bit signature

--*/

{
    static ULONG baseSignature = 0;

    LARGE_INTEGER time;

    if (!baseSignature)
    {
        NtQuerySystemTime(&time);
        time.QuadPart = time.QuadPart >> 16;
        baseSignature = time.LowPart;
    }
    return baseSignature++;
}


BOOLEAN
GetVolumeSizeMB(
    IN  ULONG  Disk,
    IN  ULONG  Partition,
    OUT PULONG Size
    )

/*++

Routine Description:

    Given a disk and a partition, query the "volume" to get its size.
    By performing the query on the 1st partition of a potential FT set,
    the total size of the set will be returned.  If the partition isn't
    an FT set, it will work too.

Arguments:

    Disk - the disk number
    Partition - the partition number
    Size - the size of the "volume"

Return Value:

    TRUE - a size was returned.
    FALSE - something failed in getting the size.

--*/

{
    BOOLEAN                     retValue = FALSE;
    IO_STATUS_BLOCK             statusBlock;
    HANDLE                      handle;
    STATUS_CODE                 sc;
    PARTITION_INFORMATION       partitionInfo;
    LARGE_INTEGER               partitionLength;

    *Size = 0;
    sc = LowOpenPartition(GetDiskName(Disk), Partition, &handle);
    if (sc == OK_STATUS)
    {
        sc = NtDeviceIoControlFile(handle,
                                   0,
                                   NULL,
                                   NULL,
                                   &statusBlock,
                                   IOCTL_DISK_GET_PARTITION_INFO,
                                   NULL,
                                   0,
                                   &partitionInfo,
                                   sizeof(PARTITION_INFORMATION));

        if (sc == OK_STATUS)
        {
            // Convert to MB

            partitionLength.QuadPart = partitionInfo.PartitionLength.QuadPart >> 20;
            *Size = partitionLength.LowPart;
            retValue = TRUE;
        }
        LowCloseDisk(handle);
    }
    return retValue;
}


ULONG
GetVolumeTypeAndSize(
    IN  ULONG  Disk,
    IN  ULONG  Partition,
    OUT PWSTR *Label,
    OUT PWSTR *Type,
    OUT PULONG Size
    )

/*++

Routine Description:

    Given a disk and partition number, determine its size, label and file
    system type.  This routine will allocate the space for label and file
    system type.  It is the responsibility of the caller to free this memory.

Arguments:

    Disk - the disk number
    Partition - the partition number
    Label - a pointer to a pointer for a WCHAR string to contain the label
    Type - a pointer to a pointer for a WCHAR string to contain the file system
           type.
    Size - a pointer to a ULONG for the size of the disk in KB.

Return Value:

    OK_STATUS - everything was performed.
    !OK_STATUS - the error code that was returned in the process of performing
                 this work.

--*/

{
    IO_STATUS_BLOCK             statusBlock;
    HANDLE                      handle;
    UCHAR                       buffer[256];
    PWSTR                       label,
                                name;
    ULONG                       length;
    UINT                        oldErrorMode;
    DISK_GEOMETRY               diskGeometry;
    STATUS_CODE                 sc;
    BOOLEAN                     firstTime = TRUE;
    PFILE_FS_VOLUME_INFORMATION labelInfo = (PFILE_FS_VOLUME_INFORMATION)buffer;
    PFILE_FS_ATTRIBUTE_INFORMATION info = (PFILE_FS_ATTRIBUTE_INFORMATION)buffer;

    while (1)
    {
        oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
        sc = LowOpenPartition(GetDiskName(Disk), Partition, &handle);
        SetErrorMode(oldErrorMode);

        if (sc == OK_STATUS)
        {
            sc = NtQueryVolumeInformationFile(handle,
                                              &statusBlock,
                                              buffer,
                                              sizeof(buffer),
                                              FileFsVolumeInformation);
            if (sc == OK_STATUS)
            {
                length = labelInfo->VolumeLabelLength;
                labelInfo->VolumeLabel[length/sizeof(WCHAR)] = 0;
                length = (length+1) * sizeof(WCHAR);

                label = (PWSTR)Malloc(length);
                RtlMoveMemory(label, labelInfo->VolumeLabel, length);
            }
            else
            {
                label = (PWSTR)Malloc(sizeof(WCHAR));
                *label = 0;
            }
            *Label = label;

            if (sc == OK_STATUS)
            {
                sc = NtQueryVolumeInformationFile(handle,
                                                  &statusBlock,
                                                  buffer,
                                                  sizeof(buffer),
                                                  FileFsAttributeInformation);
                if (sc == OK_STATUS)
                {
                    length = info->FileSystemNameLength;
                    info->FileSystemName[length/sizeof(WCHAR)] = 0;
                    length = (length+1)*sizeof(WCHAR);
                    name = (PWSTR)Malloc(length);
                    RtlMoveMemory(name, info->FileSystemName, length);
                }
                else
                {
                    name = (PWSTR)Malloc(sizeof(WCHAR));
                    *name = 0;
                }
                *Type = name;
            }

            if (sc == OK_STATUS)
            {
                sc = NtDeviceIoControlFile(handle,
                                           0,
                                           NULL,
                                           NULL,
                                           &statusBlock,
                                           IOCTL_DISK_GET_DRIVE_GEOMETRY,
                                           NULL,
                                           0,
                                           (PVOID)&diskGeometry,
                                           sizeof(diskGeometry));
                if (NT_SUCCESS(sc))
                {
                    LARGE_INTEGER sizeInBytes;
                    ULONG         cylinderBytes;

                    cylinderBytes = diskGeometry.TracksPerCylinder *
                                    diskGeometry.SectorsPerTrack *
                                    diskGeometry.BytesPerSector;

                    sizeInBytes.QuadPart = diskGeometry.Cylinders.QuadPart * cylinderBytes;

                    // Now convert everything to KB

                    sizeInBytes.QuadPart = sizeInBytes.QuadPart >> 10;
                    *Size = (ULONG) sizeInBytes.LowPart;
                }
            }
            DmClose(handle);
            sc = OK_STATUS;
            break;
        }
        else
        {
            if (firstTime)
            {
                firstTime = FALSE;
            }
            else
            {
                *Label = (PWSTR)Malloc(sizeof(WCHAR));
                if (*Label) {

                    *((PWSTR)*Label) = 0;

                }
                *Type = (PWSTR)Malloc(sizeof(WCHAR));
                if (*Type) {

                    *((PWSTR)*Type) = 0;

                }
                *Size = 0;
                break;
            }

            Sleep(SLEEP_TIME);
        }
    }

    return EC(sc);
}



ULONG
GetVolumeLabel(
    IN  ULONG  Disk,
    IN  ULONG  Partition,
    OUT PWSTR *Label
    )

/*++

Routine Description:

    Given a disk number and a partition number return the volume label (if
    any).

Arguments:

    Disk - the disk number
    Partition - the partition number
    Label - a pointer to a pointer for a WCHAR string to contain the label

Return Value:

    OK_STATUS - everything was performed.
    !OK_STATUS - the error code that was returned in the process of performing
                 this work.
--*/

{
    IO_STATUS_BLOCK status_block;
    HANDLE          handle;
    STATUS_CODE     sc;
    BOOLEAN         firstTime = TRUE;
    unsigned char   buffer[256];
    PFILE_FS_VOLUME_INFORMATION LabelInfo = (PFILE_FS_VOLUME_INFORMATION)buffer;
    PWSTR           label;
    ULONG           length;

    while (1)
    {
        sc = LowOpenPartition(GetDiskName(Disk), Partition, &handle);
        if (sc == OK_STATUS)
        {
            sc = NtQueryVolumeInformationFile(handle,
                                              &status_block,
                                              buffer,
                                              sizeof(buffer),
                                              FileFsVolumeInformation);
            DmClose(handle);

            if (sc == OK_STATUS)
            {
                length = LabelInfo->VolumeLabelLength;

                LabelInfo->VolumeLabel[length/sizeof(WCHAR)] = L'\0';

                length = (length+1) * sizeof(WCHAR);

                label = (PWSTR)Malloc(length);
                RtlMoveMemory(label, LabelInfo->VolumeLabel, length);
            }
            else
            {
                label = (PWSTR)Malloc(sizeof(WCHAR));
                sc = OK_STATUS;
                *label = L'\0';
            }

            *Label = label;
            break;
        }
        else
        {
            if (firstTime)
            {
                firstTime = FALSE;
            }
            else
            {
                *Label = NULL;
                break;
            }

            Sleep(SLEEP_TIME);
        }
    }
    return EC(sc);
}


ULONG
GetTypeName(
    IN  ULONG  Disk,
    IN  ULONG  Partition,
    OUT PWSTR* Name
    )

/*++

Routine Description:

    Given a disk number and partition number return the file system type
    string.

Arguments:

    Disk - the disk number
    Partition - the partition number
    Name - a pointer to a pointer for a WCHAR string to contain the file system
           type.

Return Value:

    OK_STATUS - everything was performed.
    !OK_STATUS - the error code that was returned in the process of performing
                 this work.
--*/

{
    PWSTR       name;
    STATUS_CODE sc;
    HANDLE      handle;
    UCHAR       buffer[256];
    BOOLEAN     firstTime = TRUE;
    PFILE_FS_ATTRIBUTE_INFORMATION info = (PFILE_FS_ATTRIBUTE_INFORMATION)buffer;
    IO_STATUS_BLOCK status_block;
    ULONG           length;

    // For some reason, the file systems believe they are locked or need
    // to be verified after formats and the like.  Therefore this is attempted
    // twice before it actually gives up.

    while (1)
    {
        sc = LowOpenPartition(GetDiskName(Disk), Partition, &handle);
        if (sc == OK_STATUS)
        {
            sc = NtQueryVolumeInformationFile(handle,
                                              &status_block,
                                              buffer,
                                              sizeof(buffer),
                                              FileFsAttributeInformation);
            DmClose(handle);

            if (sc == OK_STATUS)
            {
                length = info->FileSystemNameLength;
                info->FileSystemName[length/sizeof(WCHAR)] = L'\0';
                length = (length+1)*sizeof(WCHAR);
                name = (PWSTR)Malloc(length);
                RtlMoveMemory(name, info->FileSystemName, length);
            }
            else
            {
                name = (PWSTR)Malloc(sizeof(WCHAR));
                *name = L'\0';
                sc = OK_STATUS;
            }
            *Name = name;
            break;
        }
        else
        {
            if (firstTime)
            {
                firstTime = FALSE;
            }
            else
            {
                break;
            }

            Sleep(SLEEP_TIME);
        }
    }

    return EC(sc);
}


ULONG
GetSpaceInformation(
    IN  ULONG          Disk,
    IN  ULONG          Partition,
    OUT PLARGE_INTEGER FreeSpaceInBytes,
    OUT PLARGE_INTEGER TotalSpaceInBytes
    )
{
    STATUS_CODE              sc;
    HANDLE                   handle;
    FILE_FS_SIZE_INFORMATION info;
    IO_STATUS_BLOCK          status_block;

    TotalSpaceInBytes->QuadPart = FreeSpaceInBytes->QuadPart = 0;

    sc = LowOpenPartition(GetDiskName(Disk), Partition, &handle);
    if (sc == OK_STATUS)
    {
        sc = NtQueryVolumeInformationFile(handle,
                                          &status_block,
                                          &info,
                                          sizeof(info),
                                          FileFsSizeInformation);
        NtClose(handle);

        if (sc == OK_STATUS)
        {
            FreeSpaceInBytes->QuadPart =
                    info.AvailableAllocationUnits.QuadPart *
                    UInt32x32To64(info.SectorsPerAllocationUnit, info.BytesPerSector)
                    ;

            TotalSpaceInBytes->QuadPart =
                    info.TotalAllocationUnits.QuadPart *
                    UInt32x32To64(info.SectorsPerAllocationUnit, info.BytesPerSector)
                    ;
        }
    }

    return EC(sc);
}



BOOLEAN
IsRemovable(
    IN ULONG DiskNumber
    )
/*++

Routine Description:

    This function determines whether the specified physical
    disk is removable.

Arguments:

    DiskNumber  --  The Physical Disk Number of the disk in question.

Return Value:

    TRUE if the disk is removable.

--*/
{
    STATUS_CODE     sc;
    NTSTATUS        status;
    HANDLE          handle;
    DISK_GEOMETRY   diskGeometry;
    IO_STATUS_BLOCK statusBlock;
    BOOLEAN         result = FALSE;
    PCHAR           name;

    name = GetDiskName(DiskNumber);
    sc = LowOpenDisk(name, &handle);

    if (sc == OK_STATUS)
    {
        status = NtDeviceIoControlFile( handle,
                                        0,
                                        NULL,
                                        NULL,
                                        &statusBlock,
                                        IOCTL_DISK_GET_DRIVE_GEOMETRY,
                                        NULL,
                                        0,
                                        (PVOID)&diskGeometry,
                                        sizeof(diskGeometry));
        LowCloseDisk(handle);

        if (NT_SUCCESS(status))
        {
            if (diskGeometry.MediaType == RemovableMedia)
            {
                char  ntDeviceName[100];

                // Do a dismount/force mount sequence to make sure
                // the media hasn't changed since last mount.
                // Dismount partition 1 by lock/unlock/close.

                sprintf(ntDeviceName, "%s\\Partition1", name);
                status= LowOpenNtName(ntDeviceName, &handle);
                if (NT_SUCCESS(status))
                {
                    status = LowLockDrive(handle);
                    if (NT_SUCCESS(status)) {
                        LowUnlockDrive(handle);
                        LowCloseDisk(handle);

                        // Now force the mount by opening the device with a '\'
                        // This is done on partition 1 of the device.

                        sprintf(ntDeviceName, "%s\\Partition1\\", name);
                        status= LowOpenNtName(ntDeviceName, &handle);
                        if (NT_SUCCESS(status))
                        {
                            LowCloseDisk(handle);
                        }
                    }
                }
                result = TRUE;
            }
        } else if (status == STATUS_NO_MEDIA_IN_DEVICE) {

            //
            // This is a pretty good indication that this is a removable.
            //

            result = TRUE;

        }
    }

    return result;
}




ULONG
GetDriveLetterLinkTarget(
    IN PWSTR SourceNameStr,
    OUT PWSTR *LinkTarget
    )
{
    static WCHAR        targetNameBuffer[50];

    NTSTATUS            status;
    UNICODE_STRING      sourceName;
    UNICODE_STRING      targetName;
    OBJECT_ATTRIBUTES   oa;
    HANDLE              handle;


    RtlInitUnicodeString(&sourceName, SourceNameStr);

    InitializeObjectAttributes(&oa, &sourceName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    status = NtOpenSymbolicLinkObject(&handle, READ_CONTROL | SYMBOLIC_LINK_QUERY, &oa);

    if (NT_SUCCESS(status))
    {
        RtlZeroMemory(targetNameBuffer, sizeof(targetNameBuffer));
        targetName.Buffer = targetNameBuffer;
        targetName.MaximumLength = sizeof(targetNameBuffer);

        status = NtQuerySymbolicLinkObject(handle, &targetName, NULL);
        NtClose(handle);
    }

    if (NT_SUCCESS(status))
    {
        *LinkTarget = targetName.Buffer;
    }
    else
    {
        *LinkTarget = NULL;
    }

    return EC(status);
}


#include "bootmbr.h"

#if X86BOOTCODE_SIZE < MBOOT_CODE_SIZE
#error Something is wrong with the boot code (it's too small)!
#endif

ULONG
MasterBootCode(
    IN ULONG   Disk,
    IN ULONG   Signature,
    IN BOOLEAN SetBootCode,
    IN BOOLEAN SetSignature
    )

/*++

Routine Description:

    If the zero sector of the disk does not have a valid MBR
    signature (i.e. AA55), update it such that it has a valid
    MBR and fill in the disk signature and bootcode in the
    process.

Arguments:

    Disk - the disk ordinal to be affected
    SetSignature - if TRUE update the disk signature
    Signature    - the disk signature for the update

Return Value:

    status

--*/

{
    HANDLE      handle;
    STATUS_CODE status;
    PCHAR       diskName = GetDiskName(Disk);
    PUCHAR      unalignedSectorBuffer;
    PUCHAR      sectorBuffer;
    ULONG       bps;
    ULONG       dummy;
    ULONG       i;
    BOOLEAN     writeIt;

    #ifndef     max
    #define     max(a, b) (((a) > (b)) ? (a) : (b))
    #endif

    if (SetBootCode)
    {
        writeIt = FALSE;

        // allocate sector buffer

        status = LowGetDriveGeometry(diskName, &dummy, &bps, &dummy, &dummy);
        if (status != OK_STATUS)
        {
            return EC(status);
        }
        if (bps < 512)
        {
            bps = 512;
        }
        unalignedSectorBuffer = (PUCHAR)Malloc(2*bps);
        sectorBuffer = (PUCHAR)(((ULONG)unalignedSectorBuffer+bps) & ~(bps-1));

        // open entire disk (partition 0)

        if ((status = LowOpenDisk(diskName, &handle)) != OK_STATUS)
        {
            return EC(status);
        }

        // read (at least) first 512 bytes

        status = LowReadSectors(handle, bps, 0, 1, sectorBuffer);
        if (status == OK_STATUS)
        {
            if (   (sectorBuffer[MBOOT_SIG_OFFSET+0] != MBOOT_SIG1)
                || (sectorBuffer[MBOOT_SIG_OFFSET+1] != MBOOT_SIG2))
            {
                // xfer boot code into sectorBuffer

                for (i=0; i<MBOOT_CODE_SIZE; i++)
                {
                    sectorBuffer[i] = x86BootCode[i];
                }

                // wipe partition table

                for (i=MBOOT_CODE_SIZE; i<MBOOT_SIG_OFFSET; i++)
                {
                    sectorBuffer[i] = 0;
                }

                // set the signature

                sectorBuffer[MBOOT_SIG_OFFSET+0] = MBOOT_SIG1;
                sectorBuffer[MBOOT_SIG_OFFSET+1] = MBOOT_SIG2;

                writeIt = TRUE;
            }

            if (writeIt)
            {
                status = LowWriteSectors(handle, bps, 0, 1, sectorBuffer);
            }
        }

        LowCloseDisk(handle);

        Free(unalignedSectorBuffer);
    }

    if (SetSignature)
    {
        PDRIVE_LAYOUT_INFORMATION layout;

        // Use the IOCTL to set the signature.  This code really does
        // not know where the MBR exists.  (ezDrive extensions).

        status = LowGetDiskLayout(diskName, &layout);

        if (status == OK_STATUS)
        {
            layout->Signature = Signature;
            LowSetDiskLayout(diskName, layout);
        }
    }

    return EC(status);
}


ULONG
UpdateMasterBootCode(
    IN ULONG   Disk
    )

/*++

Routine Description:

    This routine updates the zero sector of the disk to insure that boot
    code is present.

Arguments:

    Disk - the disk number onto which to put the boot code.

Return Value:

    status

--*/

{
    HANDLE      handle;
    STATUS_CODE status;
    PUCHAR      unalignedSectorBuffer,
                sectorBuffer;
    ULONG       bps,
                dummy,
                i;
    PCHAR       diskName = GetDiskName(Disk);

#ifndef     max
#define     max(a,b) ((a > b) ? a : b)
#endif

    // allocate sector buffer

    status = LowGetDriveGeometry(diskName, &dummy, &bps, &dummy, &dummy);
    if (status != OK_STATUS)
    {
        return EC(status);
    }
    if (bps < 512)
    {
        bps = 512;
    }
    unalignedSectorBuffer = (PUCHAR)Malloc(2*bps);
    sectorBuffer = (PUCHAR)(((ULONG)unalignedSectorBuffer+bps) & ~(bps-1));

    // open entire disk (partition 0)

    if ((status = LowOpenDisk(diskName, &handle)) != OK_STATUS)
    {
        return EC(status);
    }

    // read (at least) first 512 bytes

    status = LowReadSectors(handle, bps, 0, 1, sectorBuffer);
    if (status == OK_STATUS)
    {
        // xfer boot code into sectorBuffer.  This avoids changing the
        // disk signature and the partition table information.

        for (i=0; i<MBOOT_CODE_SIZE; i++)
        {
            sectorBuffer[i] = x86BootCode[i];
        }

        status = LowWriteSectors(handle, bps, 0, 1, sectorBuffer);
    }

    LowCloseDisk(handle);

    // free the sector buffer

    Free(unalignedSectorBuffer);
    return EC(status);
}



VOID
MakePartitionActive(
    IN PREGION_DESCRIPTOR DiskRegionArray,
    IN ULONG              RegionCount,
    IN ULONG              RegionIndex
    )

/*++

Routine Description:

    Update the information in the internal structures to indicate
    that the specified partition is active.

Arguments:

    DiskRegionArray
    RegionCount
    RegionIndex

Return Value:

    None

--*/

{
    unsigned i;

    for (i=0; i<RegionCount; i++)
    {
        if (DiskRegionArray[i].RegionType == REGION_PRIMARY)
        {
            DiskRegionArray[i].Active = FALSE;
            SetPartitionActiveFlag(&DiskRegionArray[i], FALSE);
        }
    }
    DiskRegionArray[RegionIndex].Active = (BOOLEAN)0x80;
    SetPartitionActiveFlag(&DiskRegionArray[RegionIndex], 0x80);
}


VOID
LoadExistingPageFileInfo(
    IN VOID
    )

/*++

Routine Description:

    This routine finds all pagefiles in the system and updates the internal
    structures.

Arguments:

    None

Return Values:

    None

--*/

{
    NTSTATUS                     status;
    SYSTEM_INFO                  sysInfo;
    UCHAR                        genericBuffer[0x10000];
    PSYSTEM_PAGEFILE_INFORMATION pageFileInfo;
    ANSI_STRING                  ansiPageFileName;
    PPAGEFILE_LOCATION           pageFileListEntry;
    PCHAR                        p;

    GetSystemInfo(&sysInfo);

    status = NtQuerySystemInformation(SystemPageFileInformation,
                                      genericBuffer,
                                      sizeof(genericBuffer),
                                      NULL);
    if (!NT_SUCCESS(status))
    {
        // It's possible that this call will fail if the
        // the system is running without ANY paging files.

        return;
    }

    pageFileInfo = (PSYSTEM_PAGEFILE_INFORMATION) genericBuffer;

    for (;;)
    {
        RtlUnicodeStringToAnsiString(&ansiPageFileName,
                                     &pageFileInfo->PageFileName,
                                     TRUE);

        // Since the format of the pagefile name generally
        // looks something like "\DosDevices\h:\pagefile.sys",
        // just use the first character before the colon
        // and assume that's the drive letter.

        p = strchr(_strlwr(ansiPageFileName.Buffer), ':');

        if ((p-- != NULL) && (*p >= 'a') && (*p <= 'z'))
        {
            pageFileListEntry = (PPAGEFILE_LOCATION)Malloc(sizeof(PAGEFILE_LOCATION));
            if (NULL != pageFileListEntry)
            {
                if (NULL != PagefileHead)
                {
                    pageFileListEntry->Next = PagefileHead;
                }
                else
                {
                    PagefileHead = pageFileListEntry;
                    pageFileListEntry->Next = NULL;
                }
                pageFileListEntry->DriveLetter = (WCHAR)(*p);
            }
        }

        RtlFreeAnsiString(&ansiPageFileName);

        if (pageFileInfo->NextEntryOffset == 0)
        {
            break;
        }

        pageFileInfo = (PSYSTEM_PAGEFILE_INFORMATION)((PCHAR) pageFileInfo
                      + pageFileInfo->NextEntryOffset);
    }
}

BOOLEAN
IsPagefileOnDrive(
    WCHAR DriveLetter
    )

/*++

Routine Description:

    Walk the page file list and determine if the drive letter given has
    a paging file.  NOTE:  The assumption is that drive letters that
    contain paging files can never get changed during the execution of
    Disk Administrator.  Therefore this list is never updated, but
    can be used during the execution of Disk Administrator.

Arguments:

    DriveLetter - the drive in question.

Return Value:

    TRUE if this drive contains a page file.

--*/

{
    PPAGEFILE_LOCATION pageFileListEntry = PagefileHead;

    while (NULL != pageFileListEntry)
    {
        if (pageFileListEntry->DriveLetter == DriveLetter)
        {
            return TRUE;
        }
        pageFileListEntry = pageFileListEntry->Next;
    }
    return FALSE;
}
