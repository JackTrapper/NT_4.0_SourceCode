/*++

Copyright (c) 1990 Microsoft Corporation

Module Name:

    drive.hxx

Abstract:

    The drive class hierarchy models the concept of a drive in various
    stages.  It looks like this:

        DRIVE
            DP_DRIVE
                IO_DP_DRIVE
                    LOG_IO_DP_DRIVE
                    PHYS_IO_DP_DRIVE

    DRIVE
    -----

    DRIVE implements a container for the drive path which is recognizable
    by the file system.  'Initialize' takes the path as an argument so
    that it can be later queried with 'GetNtDriveName'.


    DP_DRIVE
    --------

    DP_DRIVE (Drive Parameters) implements queries for the geometry of the
    drive.  'Initiliaze' queries the information from the drive.  What
    is returned is the default drive geometry for the drive.  The user
    may ask by means of 'IsSupported' if the physical device will support
    another MEDIA_TYPE.

    A protected member function called 'SetMediaType' allows the a derived
    class to set the MEDIA_TYPE to another media type which is supported
    by the device.  This method is protected because only a low-level
    format will actually change the media type.


    IO_DP_DRIVE
    -----------

    IO_DP_DRIVE implements the reading a writting of sectors as well
    as 'Lock', 'Unlock', and 'Dismount'.  The 'FormatVerifyFloppy' method
    does a low-level format.  A version of this method allows the user
    to specify a new MEDIA_TYPE for the media.


    LOG_IO_DP_DRIVE and PHYS_IO_DP_DRIVE
    ------------------------------------

    LOG_IO_DP_DRIVE models logical drive.  PHYS_IO_DP_DRIVE models a
    physical drive.  Currently both implementations just initialize
    an IO_DP_DRIVE.  The difference is in the drive path specified.
    Some drive paths are to logical drives and others are to physical
    drives.


Author:

        Mark Shavlik (marks) Jun-90
        Norbert P. Kusters (norbertk) 22-Feb-91

--*/


#if ! defined( DRIVE_DEFN )

#define DRIVE_DEFN


#include "wstring.hxx"
#include "bigint.hxx"

#if defined ( _AUTOCHECK_ )
#define IFSUTIL_EXPORT
#elif defined ( _IFSUTIL_MEMBER_ )
#define IFSUTIL_EXPORT    __declspec(dllexport)
#else
#define IFSUTIL_EXPORT    __declspec(dllimport)
#endif



//
//      Forward references
//

DECLARE_CLASS( DRIVE );
DECLARE_CLASS( DP_DRIVE );
DECLARE_CLASS( IO_DP_DRIVE );
DECLARE_CLASS( LOG_IO_DP_DRIVE );
DECLARE_CLASS( PHYS_IO_DP_DRIVE );
DECLARE_CLASS( NUMBER_SET );
DECLARE_CLASS( MESSAGE );
DECLARE_CLASS( DRIVE_CACHE );

#if !defined _PARTITION_SYSTEM_ID_DEFINED_
#define _PARTITION_SYSTEM_ID_DEFINED_
enum PARTITION_SYSTEM_ID {
     SYSID_NONE         = 0,
     SYSID_FAT12BIT     = 1,
     SYSID_FAT16BIT     = 4,
     SYSID_FAT32MEG     = 6,
     SYSID_IFS          = 7,
     SYSID_EXTENDED     = 5
};
#endif

DEFINE_TYPE( ULONG, SECTORCOUNT );      // count of sectors
DEFINE_TYPE( ULONG, LBN );              // Logical buffer number

DEFINE_POINTER_AND_REFERENCE_TYPES( MEDIA_TYPE );
DEFINE_POINTER_AND_REFERENCE_TYPES( DISK_GEOMETRY );

struct _DRTYPE {
        MEDIA_TYPE  MediaType;
        ULONG       SectorSize;
        BIG_INT     Sectors;            // w/o hidden sectors.
        BIG_INT     HiddenSectors;
        SECTORCOUNT SectorsPerTrack;
        ULONG       Heads;
};

// Hosted volumes always have certain values fixed.  Define
// those values here:
//
CONST MEDIA_TYPE HostedDriveMediaType = FixedMedia;
CONST ULONG HostedDriveSectorSize = 512;
CONST BIG_INT HostedDriveHiddenSectors = 0;
CONST SECTORCOUNT HostedDriveSectorsPerTrack = 0x11;
CONST SECTORCOUNT HostedDriveHeads = 6;

DEFINE_TYPE( struct _DRTYPE, DRTYPE );


class DRIVE : public OBJECT {

    public:

        DECLARE_CONSTRUCTOR(DRIVE);

        VIRTUAL
        ~DRIVE(
            );

        NONVIRTUAL
        BOOLEAN
        Initialize(
            IN      PCWSTRING    NtDriveName,
            IN OUT  PMESSAGE     Message DEFAULT NULL
            );

        NONVIRTUAL
        PCWSTRING
        GetNtDriveName(
            ) CONST;

    private:

        NONVIRTUAL
        VOID
        Construct(
                );

        NONVIRTUAL
        VOID
        Destroy(
            );

        DSTRING _name;

};


INLINE
PCWSTRING
DRIVE::GetNtDriveName(
    ) CONST
/*++

Routine Description:

    This routine returns a pointer string containing the NT drive name.

Arguments:

    None.

Return Value:

    A pointer to a string containing the NT drive name.

--*/
{
    return &_name;
}


class DP_DRIVE : public DRIVE {

    public:

        IFSUTIL_EXPORT
        DECLARE_CONSTRUCTOR(DP_DRIVE);

        VIRTUAL
        IFSUTIL_EXPORT
        ~DP_DRIVE(
                );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        Initialize(
            IN      PCWSTRING    NtDriveName,
            IN OUT  PMESSAGE     Message         DEFAULT NULL,
            IN      BOOLEAN      IsTransient     DEFAULT FALSE,
            IN      BOOLEAN      ExclusiveWrite  DEFAULT FALSE
            );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        Initialize(
            IN      PCWSTRING   NtDriveName,
            IN      PCWSTRING   HostFileName,
            IN OUT  PMESSAGE    Message         DEFAULT NULL,
            IN      BOOLEAN     IsTransient     DEFAULT FALSE,
            IN      BOOLEAN     ExclusiveWrite  DEFAULT FALSE
            );

        NONVIRTUAL
        MEDIA_TYPE
        QueryMediaType(
            ) CONST;

        NONVIRTUAL
        IFSUTIL_EXPORT
        UCHAR
        QueryMediaByte(
            ) CONST;

        VIRTUAL
        IFSUTIL_EXPORT
        ULONG
        QuerySectorSize(
            ) CONST;

        VIRTUAL
        IFSUTIL_EXPORT
        BIG_INT
        QuerySectors(
            ) CONST;

        NONVIRTUAL
        BIG_INT
        QueryHiddenSectors(
            ) CONST;

        NONVIRTUAL
        SECTORCOUNT
        QuerySectorsPerTrack(
            ) CONST;

        NONVIRTUAL
        ULONG
        QueryHeads(
            ) CONST;

        NONVIRTUAL
        BIG_INT
        QueryTracks(
            ) CONST;

        NONVIRTUAL
        BIG_INT
        QueryCylinders(
            ) CONST;

        NONVIRTUAL
        BOOLEAN
        IsRemovable(
            ) CONST;

        NONVIRTUAL
        BOOLEAN
        IsFloppy(
            ) CONST;

        NONVIRTUAL
        BOOLEAN
        IsSuperFloppy(
            ) CONST;

        NONVIRTUAL
        BOOLEAN
        IsFixed(
            ) CONST;

        NONVIRTUAL
        BOOLEAN
        IsSupported(
            IN  MEDIA_TYPE  MediaType
            ) CONST;

        NONVIRTUAL
        PCDRTYPE
        GetSupportedList(
            OUT PINT    NumSupported
            ) CONST;

        NONVIRTUAL
        IFSUTIL_EXPORT
        MEDIA_TYPE
        QueryRecommendedMediaType(
            ) CONST;

        NONVIRTUAL
        ULONG
        QueryAlignmentMask(
            ) CONST;

        NONVIRTUAL
        NTSTATUS
        QueryLastNtStatus(
            ) CONST;

        NONVIRTUAL
        HANDLE
        GetVolumeFileHandle(
            ) CONST;

#if defined ( DBLSPACE_ENABLED )
        NONVIRTUAL
        BOOLEAN
        QueryMountedFileSystemName(
            OUT PWSTRING FileSystemName,
            OUT PBOOLEAN IsCompressed
            );

        NONVIRTUAL
        BOOLEAN
        MountCvf(
            IN  PCWSTRING   CvfName,
            IN  PMESSAGE    Message
            );

        NONVIRTUAL
        BOOLEAN
        SetCvfSize(
            IN  ULONG       Size
            );
#endif  // DBLSPACE_ENABLED


    protected:

        NONVIRTUAL
        BOOLEAN
        SetMediaType(
            IN  MEDIA_TYPE  MediaType   DEFAULT Unknown
            );


        // On a normal drive, _handle is a handle to the drive
        // and _alternate_drive is zero.  On a hosted drive,
        // however, _handle is a handle to the file which
        // contains the volume and _alternate_handle is a handle
        // to the volume itself.
        //
        // When the drive object opens a hosted volume, it must
        // first make the host file non-readonly.  It caches the
        // old attributes of the file so that it can reset them.
        //
        HANDLE      _handle;
        HANDLE      _alternate_handle;
        BOOLEAN     _hosted_drive;
        ULONG       _old_attributes;
        NTSTATUS    _last_status;

    private:

        NONVIRTUAL
        VOID
        Construct(
            );

        NONVIRTUAL
        VOID
        Destroy(
            );

        STATIC
        NTSTATUS
        OpenDrive(
            IN      PCWSTRING   NtDriveName,
            IN      ACCESS_MASK DesiredAccess,
            IN      BOOLEAN     ExclusiveWrite,
            OUT     PHANDLE     Handle,
            OUT     PULONG      Alignment,
            IN OUT  PMESSAGE    Message
            );

        STATIC
        VOID
        DiskGeometryToDriveType(
            IN  PCDISK_GEOMETRY DiskGeometry,
            OUT PDRTYPE         DriveType
            );

        STATIC
        VOID
        DiskGeometryToDriveType(
            IN  PCDISK_GEOMETRY DiskGeometry,
            IN  BIG_INT         NumSectors,
            IN  BIG_INT         NumHiddenSectors,
            OUT PDRTYPE         DriveType
            );

        DRTYPE      _actual;
        PDRTYPE     _supported_list;
        INT         _num_supported;
        ULONG       _alignment_mask;
        BOOLEAN     _super_floppy;

};


INLINE
MEDIA_TYPE
DP_DRIVE::QueryMediaType(
        ) CONST
/*++

Routine Description:

        This routine computes the media type.

Arguments:

    None.

Return Value:

        The media type.

--*/
{
        return _actual.MediaType;
}


INLINE
BIG_INT
DP_DRIVE::QueryHiddenSectors(
    ) CONST
/*++

Routine Description:

    This routine computes the number of hidden sectors.

Arguments:

    None.

Return Value:

    The number of hidden sectors.

--*/
{
    return _actual.HiddenSectors;
}


INLINE
SECTORCOUNT
DP_DRIVE::QuerySectorsPerTrack(
    ) CONST
/*++

Routine Description:

    This routine computes the number of sectors per track.

Arguments:

    None.

Return Value:

    The number of sectors per track.

--*/
{
    return _actual.SectorsPerTrack;
}


INLINE
ULONG
DP_DRIVE::QueryHeads(
    ) CONST
/*++

Routine Description:

    This routine computes the number of heads.

Arguments:

    None.

Return Value:

    The number of heads.

--*/
{
    return _actual.Heads;
}


INLINE
BIG_INT
DP_DRIVE::QueryTracks(
    ) CONST
/*++

Routine Description:

    This routine computes the number of tracks on the disk.

Arguments:

    None.

Return Value:

    The number of tracks on the disk.

--*/
{
    return (_actual.Sectors + _actual.HiddenSectors)/_actual.SectorsPerTrack;
}


INLINE
BIG_INT
DP_DRIVE::QueryCylinders(
    ) CONST
/*++

Routine Description:

    This routine computes the number of cylinders on the disk.

Arguments:

    None.

Return Value:

    The number of cylinders on the disk.

--*/
{
    return QueryTracks()/_actual.Heads;
}


INLINE
BOOLEAN
DP_DRIVE::IsRemovable(
    ) CONST
/*++

Routine Description:

    This routine computes whether or not the disk is removable.

Arguments:

    None.

Return Value:

    FALSE   - The disk is not removable.
    TRUE    - The disk is removable.

--*/
{
        return _actual.MediaType != FixedMedia;
}


INLINE
BOOLEAN
DP_DRIVE::IsFloppy(
    ) CONST
/*++

Routine Description:

    This routine computes whether or not the disk is a floppy disk.

Arguments:

    None.

Return Value:

        FALSE   - The disk is not a floppy disk.
        TRUE    - The disk is a floppy disk.

--*/
{
        return IsRemovable() && _actual.MediaType != RemovableMedia;
}

INLINE
BOOLEAN
DP_DRIVE::IsSuperFloppy(
    ) CONST
/*++

Routine Description:

    This routine tells whether the media is non-floppy unpartitioned
    removable media.

Arguments:

    None.

Return Value:

    FALSE   - The disk is not a floppy disk.
    TRUE    - The disk is a floppy disk.

--*/
{
    return _super_floppy;
}


INLINE
BOOLEAN
DP_DRIVE::IsFixed(
    ) CONST
/*++

Routine Description:

    This routine computes whether or not the disk is a fixed disk.

Arguments:

    None.

Return Value:

    FALSE   - The disk is not a fixed disk.
    TRUE    - The disk is a fixed disk.

--*/
{
    return _actual.MediaType == FixedMedia;
}


INLINE
PCDRTYPE
DP_DRIVE::GetSupportedList(
    OUT PINT    NumSupported
    ) CONST
/*++

Routine Description:

    This routine returns a list of the supported media types by the device.

Arguments:

    NumSupported    - Returns the number of elements in the list.

Return Value:

    A list of the supported media types by the device.

--*/
{
    *NumSupported = _num_supported;
    return _supported_list;
}


INLINE
ULONG
DP_DRIVE::QueryAlignmentMask(
    ) CONST
/*++

Routine Description:

    This routine returns the memory alignment requirement for the drive.

Arguments:

    None.

Return Value:

    The memory alignment requirement for the drive in the form of a mask.

--*/
{
    return _alignment_mask;
}


INLINE
NTSTATUS
DP_DRIVE::QueryLastNtStatus(
    ) CONST
/*++

Routine Description:

    This routine returns the last NT status value.

Arguments:

    None.

Return Value:

    The last NT status value.

--*/
{
    return _last_status;
}


class IO_DP_DRIVE : public DP_DRIVE {

    FRIEND class DRIVE_CACHE;

        public:

                VIRTUAL
                ~IO_DP_DRIVE(
                        );

                NONVIRTUAL
                IFSUTIL_EXPORT
                BOOLEAN
                Read(
                        IN  BIG_INT     StartingSector,
                        IN  SECTORCOUNT NumberOfSectors,
                        OUT PVOID       Buffer
                        );

                NONVIRTUAL
                IFSUTIL_EXPORT
                BOOLEAN
                Write(
                        IN  BIG_INT     StartingSector,
                        IN  SECTORCOUNT NumberOfSectors,
                        IN  PVOID       Buffer
                        );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        Verify(
            IN  BIG_INT StartingSector,
            IN  BIG_INT NumberOfSectors
            );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        Verify(
            IN      BIG_INT     StartingSector,
            IN      BIG_INT     NumberOfSectors,
            IN OUT  PNUMBER_SET BadSectors
            );

                NONVIRTUAL
                IFSUTIL_EXPORT
                BOOLEAN
                Lock(
            );

        NONVIRTUAL
        BOOLEAN
        Unlock(
            );

        NONVIRTUAL
        BOOLEAN
        ForceDirty(
            );

                NONVIRTUAL
                BOOLEAN
                FormatVerifyFloppy(
                        IN      MEDIA_TYPE  MediaType   DEFAULT Unknown,
            IN OUT  PNUMBER_SET BadSectors  DEFAULT NULL,
            IN OUT  PMESSAGE    Message     DEFAULT NULL,
            IN      BOOLEAN     IsDmfFormat DEFAULT FALSE
                        );

        NONVIRTUAL
        IFSUTIL_EXPORT
        VOID
        SetCache(
            IN OUT  PDRIVE_CACHE    Cache
            );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        FlushCache(
            );

                //      Note that the following three methods, provided to
                //      support SimBad, are _not_ in ifsutil.dll.

        NONVIRTUAL
        BOOLEAN
        EnableBadSectorSimulation(
            IN  BOOLEAN Enable
            );

        NONVIRTUAL
        BOOLEAN
        SimulateBadSectors(
            IN BOOLEAN     Add,
            IN ULONG       Count,
            IN PLBN        SectorArray,
            IN NTSTATUS    Status,
            IN ULONG       AccessType
            );

        NONVIRTUAL
        BOOLEAN
        QuerySimulatedBadSectors(
            OUT PULONG  Count,
            IN  ULONG   MaximumLbnsInBuffer,
            OUT PLBN    SectorArray,
            OUT PULONG  AccessTypeArray
            );


        protected:

                DECLARE_CONSTRUCTOR(IO_DP_DRIVE);

                NONVIRTUAL
                BOOLEAN
                Initialize(
            IN      PCWSTRING    NtDriveName,
            IN OUT  PMESSAGE            Message        DEFAULT NULL,
            IN      BOOLEAN             ExclusiveWrite DEFAULT FALSE
            );

        NONVIRTUAL
                BOOLEAN
                Initialize(
            IN      PCWSTRING   NtDriveName,
            IN      PCWSTRING   HostFileName,
            IN OUT  PMESSAGE    Message         DEFAULT NULL,
            IN      BOOLEAN     ExclusiveWrite  DEFAULT FALSE
                        );

    private:

        BOOLEAN         _is_locked;
        BOOLEAN         _is_exclusive_write;
        PDRIVE_CACHE    _cache;

                NONVIRTUAL
                VOID
                Construct(
                        );

        NONVIRTUAL
        VOID
        Destroy(
            );

        NONVIRTUAL
        BOOLEAN
        VerifyWithRead(
            IN  BIG_INT StartingSector,
            IN  BIG_INT NumberOfSectors
            );

        NONVIRTUAL
        BOOLEAN
        HardRead(
                        IN  BIG_INT     StartingSector,
                        IN  SECTORCOUNT NumberOfSectors,
                        OUT PVOID       Buffer
            );

        NONVIRTUAL
        BOOLEAN
        HardWrite(
                        IN  BIG_INT     StartingSector,
                        IN  SECTORCOUNT NumberOfSectors,
            IN  PVOID       Buffer
            );

        NONVIRTUAL
                BOOLEAN
                Dismount(
                        );

};


class LOG_IO_DP_DRIVE : public IO_DP_DRIVE {

    public:

        IFSUTIL_EXPORT
        DECLARE_CONSTRUCTOR(LOG_IO_DP_DRIVE);

        VIRTUAL
        IFSUTIL_EXPORT
        ~LOG_IO_DP_DRIVE(
                );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        Initialize(
            IN      PCWSTRING    NtDriveName,
            IN OUT  PMESSAGE     Message        DEFAULT NULL,
            IN      BOOLEAN      ExclusiveWrite DEFAULT FALSE
            );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        SetSystemId(
            IN  PARTITION_SYSTEM_ID   SystemId
            );

        NONVIRTUAL
        IFSUTIL_EXPORT
        BOOLEAN
        Initialize(
            IN      PCWSTRING   NtDriveName,
            IN      PCWSTRING   HostFileName,
            IN OUT  PMESSAGE    Message         DEFAULT NULL,
            IN      BOOLEAN     ExclusiveWrite  DEFAULT FALSE
        );

    private:

        NONVIRTUAL
        VOID
        Construct(
            );

};


INLINE
VOID
LOG_IO_DP_DRIVE::Construct(
    )
/*++

Routine Description:

    Constructor for LOG_IO_DP_DRIVE.

Arguments:

    None.

Return Value:

    None.

--*/
{
}


class PHYS_IO_DP_DRIVE : public IO_DP_DRIVE {

        public:

                DECLARE_CONSTRUCTOR(PHYS_IO_DP_DRIVE);

                VIRTUAL
                ~PHYS_IO_DP_DRIVE(
                        );

                NONVIRTUAL
                BOOLEAN
                Initialize(
            IN      PCWSTRING    NtDriveName,
            IN OUT  PMESSAGE            Message        DEFAULT NULL,
            IN      BOOLEAN             ExclusiveWrite DEFAULT FALSE
                        );

    private:

        NONVIRTUAL
        VOID
        Construct(
            );

};


INLINE
VOID
PHYS_IO_DP_DRIVE::Construct(
    )
/*++

Routine Description:

    Constructor for PHYS_IO_DP_DRIVE.

Arguments:

    None.

Return Value:

    None.

--*/
{
}

INLINE
HANDLE
DP_DRIVE::GetVolumeFileHandle(
    ) CONST
/*++

Routine Description:

    This routine is a hack for NTFS->OFS convert...  it returns the
    handle open on the ntfs volume-file.

Arguments:

    None.

Return Value:

    The handle.

--*/
{
    return _handle;
}

#endif // DRIVE_DEFN
