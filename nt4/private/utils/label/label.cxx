#define _NTAPI_ULIB_

#include "ulib.hxx"
#include "arg.hxx"
#include "array.hxx"
#include "smsg.hxx"
#include "rtmsg.h"
#include "wstring.hxx"
#include "path.hxx"
#include "substrng.hxx"
#include "system.hxx"
#include "ifssys.hxx"
#include "ulibcl.hxx"

extern "C" {
    #include "ntioapi.h"
}

CONST   MaxLabelLength = 1024;

VOID
DisplayLabelUsage(
    IN OUT  PMESSAGE    Message
    )
/*++

Routine Description:

    This routine displays the usage for the dos 5 label program.

Arguments:

    Message - Supplies an outlet for the messages.

Return Value:

    None.

--*/
{
    Message->Set(MSG_LBL_INFO);
    Message->Display("");
    Message->Set(MSG_LBL_USAGE);
    Message->Display("");
}


BOOLEAN
OpenDrive(
    IN  PCWSTRING   Drive,
    OUT PHANDLE     Handle,
    OUT PNTSTATUS   Status
    )
/*++

Routine Description:

    This routine opens an NT handle to for the given dos drive name.

Arguments:

    Drive   - Supplies a dos drive name.
        Handle  - Returns an NT handle to the drive.
        Status  - Receives the status code if the function returns FALSE

Return Value:

    FALSE   - Failure.
    TRUE    - Success.

--*/
{
    DSTRING             ntdrive;
    UNICODE_STRING      string;
    OBJECT_ATTRIBUTES   oa;
    IO_STATUS_BLOCK     status_block;

    if (!IFS_SYSTEM::DosDriveNameToNtDriveName(Drive, &ntdrive)) {

        *Status = STATUS_NO_MEMORY;
        return FALSE;
    }

    if (!(string.Buffer = ntdrive.QueryWSTR())) {

        *Status = STATUS_NO_MEMORY;
        return FALSE;
    }

    string.Length = (USHORT) (ntdrive.QueryChCount()*sizeof(WCHAR));
    string.MaximumLength = string.Length;

    InitializeObjectAttributes( &oa,
                                &string,
                                OBJ_CASE_INSENSITIVE,
                                0,
                                0 );

    *Status = NtOpenFile(Handle,
                         SYNCHRONIZE | FILE_READ_DATA | FILE_WRITE_DATA,
                         &oa, &status_block,
                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                         FILE_SYNCHRONOUS_IO_ALERT | FILE_WRITE_THROUGH);

    return (BOOLEAN) NT_SUCCESS(*Status);
}


BOOLEAN
OpenReadOnlyDrive(
    IN  PCWSTRING   Drive,
    OUT PHANDLE     Handle
    )
/*++

Routine Description:

    This routine opens an NT handle to for the given dos drive name.

Arguments:

    Drive   - Supplies a dos drive name.
        Handle  - Returns an NT handle to the drive.

Return Value:

    FALSE   - Failure.
    TRUE    - Success.

--*/
{
    DSTRING             ntdrive;
    UNICODE_STRING      string;
    OBJECT_ATTRIBUTES   oa;
    IO_STATUS_BLOCK     status_block;
    DSTRING             backslash;
    NTSTATUS            Status;


    if (!IFS_SYSTEM::DosDriveNameToNtDriveName(Drive, &ntdrive) ||
        !backslash.Initialize("\\") ||
        !ntdrive.Strcat(&backslash)) {

        return FALSE;
    }

    if (!(string.Buffer = ntdrive.QueryWSTR())) {

        return FALSE;
    }

    string.Length = (USHORT) (ntdrive.QueryChCount()*sizeof(WCHAR));
    string.MaximumLength = string.Length;

    InitializeObjectAttributes( &oa,
                                &string,
                                OBJ_CASE_INSENSITIVE,
                                0,
                                0 );

    Status = NtOpenFile(Handle,
                        SYNCHRONIZE | FILE_READ_DATA,
                        &oa, &status_block,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        FILE_SYNCHRONOUS_IO_ALERT);

    return (BOOLEAN) NT_SUCCESS(Status);
}


BOOLEAN
GetLabelInput(
    IN      PCWSTRING   Drive,
    OUT     PBOOLEAN    LabelExists,
    OUT     PWSTRING    Label,
    IN OUT  PMESSAGE    Message
    )
/*++

Routine Description:

    This routine prints the current label, if any, and the current serial
    number.  Then a new label is queried from the user.

Arguments:

    Drive       - The dos style drive name.
    LabelExists - Returns whether or not a label currently exists on
                    the volume.
    Label       - Returns the inputted label.
    Message     - Supplies an outlet for messages.

Return Value:

    FALSE   - Failure.
    TRUE    - Success.

--*/
{
    CONST   length = sizeof(FILE_FS_VOLUME_INFORMATION) + MaxLabelLength;
    CONST   max_fsname = 40;

    // The buffer for FileFsVolumeInformation must be quadword-aligned.

    LONGLONG                        info_buf[length/sizeof(LONGLONG) + 1];
    PFILE_FS_VOLUME_INFORMATION     info;

    IO_STATUS_BLOCK                 status_block;
    PUSHORT                         p;
    DSTRING                         driveletter;
    DSTRING                         current_label;
    HANDLE                          Handle;
    WCHAR                           file_system[max_fsname];
    MSGID                           label_prompt_msg;
    DSTRING                         root_dir;
    DSTRING                         slash;
    PWSTR                           proot_dir;
    DSTRING                         fsname;
    DSTRING                         ntfs;

    if (!OpenReadOnlyDrive(Drive, &Handle)) {

        Message->Set(MSG_INCOMPATIBLE_PARAMETERS);
        Message->Display();
        return FALSE;
    }


    info = (PFILE_FS_VOLUME_INFORMATION) info_buf;

    if (!NT_SUCCESS(NtQueryVolumeInformationFile(Handle, &status_block,
                    info, length, FileFsVolumeInformation))) {

        NtClose(Handle);
        return FALSE;
    }

    NtClose(Handle);

    info->VolumeLabel[info->VolumeLabelLength/sizeof(WCHAR)] = 0;

    if (!current_label.Initialize(info->VolumeLabel)) {
        return FALSE;
    }

    if (Drive->QueryChCount() == 2 && Drive->QueryChAt(1) == ':') {
        if (!driveletter.Initialize(Drive, 0, Drive->QueryChCount() - 1)) {
            return FALSE;
        }
    } else {
        if (!driveletter.Initialize(Drive)) {
            return FALSE;
        }
    }

    if (info->VolumeLabelLength) {
        Message->Set(MSG_LBL_THE_LABEL);
        Message->Display("%W%W", &driveletter, &current_label);
        *LabelExists = TRUE;
    } else {
        Message->Set(MSG_LBL_NO_LABEL);
        Message->Display("%W", &driveletter);
        *LabelExists = FALSE;
    }

    p = (PUSHORT) &info->VolumeSerialNumber;

    if (p[1] || p[0]) {
        Message->Set(MSG_VOLUME_SERIAL_NUMBER);
        Message->Display("%04X%04X", p[1], p[0]);
    }

    // Figure out which label prompt message to use.

    label_prompt_msg = MSG_VOLUME_LABEL_PROMPT;

    if (slash.Initialize("\\") &&
        root_dir.Initialize(Drive) &&
        root_dir.Strcat(&slash) &&
        ntfs.Initialize("NTFS") &&
        (proot_dir = root_dir.QueryWSTR())) {

        if (GetVolumeInformation(proot_dir, NULL, 0, NULL, NULL,
                                 NULL, file_system, max_fsname) &&
            fsname.Initialize(file_system) &&
            !fsname.Stricmp(&ntfs)) {

            label_prompt_msg = MSG_VOLUME_LABEL_NO_MAX;
        }

        DELETE(proot_dir);
    }

    Message->Set(label_prompt_msg, ERROR_MESSAGE);
    Message->Display();

    return Message->QueryStringInput(Label);
}


BOOLEAN
SetLabel(
    IN      PCWSTRING   Drive,
    IN      PCWSTRING   Label,
    IN OUT  PMESSAGE    Message
    )
/*++

Routine Description:

    This routine sets the supplied label on the supplied drive.

Arguments:

    Drive   - Supplies the dos drive name.
    Label   - Supplies a label.
    Message - Supplies an outlet for messages.

Return Value:

    FALSE   - Failure.
    TRUE    - Success.

--*/
{
    CONST   length  = sizeof(FILE_FS_LABEL_INFORMATION) + MaxLabelLength;

    PFILE_FS_LABEL_INFORMATION  info;
    STR                         info_buf[length];
    IO_STATUS_BLOCK             status_block;
    NTSTATUS                    nts;
    DSTRING                     uppercase_label;
    HANDLE                      Handle;
    NTSTATUS                    status;


    if (!OpenDrive(Drive, &Handle, &status)) {

        if( status == STATUS_ACCESS_DENIED ) {

            Message->Set(MSG_DASD_ACCESS_DENIED);
            Message->Display("");

        } else {

            Message->Set(MSG_INCOMPATIBLE_PARAMETERS);
            Message->Display("");
        }

        return 1;
    }


    if (!uppercase_label.Initialize(Label)) {
        return FALSE;
    }

    info = (PFILE_FS_LABEL_INFORMATION) info_buf;

    if (!uppercase_label.QueryWSTR(0, TO_END, info->VolumeLabel,
                                   (length - sizeof(ULONG))/sizeof(WCHAR))) {

        Message->Set(MSG_INCOMPATIBLE_PARAMETERS);
        Message->Display();
        return FALSE;
    }

    info->VolumeLabelLength = uppercase_label.QueryChCount()*sizeof(WCHAR);

    nts = NtSetVolumeInformationFile(Handle, &status_block, info,
                                     length, FileFsLabelInformation);

    if (!NT_SUCCESS(nts)) {

        if ( nts == STATUS_ACCESS_DENIED ) {

            Message->Set(MSG_DASD_ACCESS_DENIED);
            Message->Display();

        } else if ( nts == STATUS_INVALID_VOLUME_LABEL ) {

            Message->Set(MSG_INVALID_LABEL);
            Message->Display();

        } else if ( nts == STATUS_NOT_SUPPORTED ||
                    nts == STATUS_INVALID_DEVICE_REQUEST ) {

            Message->Set(MSG_LBL_NOT_SUPPORTED);
            Message->Display();

        } else if ( nts == STATUS_DISK_FULL ) {

            Message->Set(MSG_INSUFFICIENT_DISK_SPACE);
            Message->Display();

        } else {

            Message->Set(MSG_INCOMPATIBLE_PARAMETERS);
            Message->Display();
        }

        return FALSE;
    }

    return TRUE;
}


INT _CRTAPI1
main(
    )
/*++

Routine Description:

    This routine emulates the dos 5 label command for NT.

Arguments:

    None.

Return Value:

    1   - An error occured.
    0   - Success.

--*/
{
    STREAM_MESSAGE          msg;
    ARGUMENT_LEXEMIZER      arglex;
    ARRAY                   lex_array;
    ARRAY                   arg_array;
    STRING_ARGUMENT         progname;
    STRING_ARGUMENT         drive_arg;
    REST_OF_LINE_ARGUMENT   label_arg;
    FLAG_ARGUMENT           help_arg;
    DSTRING                 label_string;
    DSTRING                 drive_string;
    BOOLEAN                 label_exists;
    PATH                    label_path;
    PWSTRING                p;
    FSTRING                 colon;

    if (!msg.Initialize(Get_Standard_Output_Stream(),
                        Get_Standard_Input_Stream(),
                        Get_Standard_Error_Stream())) {
        return 1;
    }

    if (!lex_array.Initialize() || !arg_array.Initialize()) {
        return 1;
    }

    if (!arglex.Initialize(&lex_array)) {
        return 1;
    }

    arglex.SetCaseSensitive(FALSE);

    if (!arglex.PrepareToParse()) {
        return 1;
    }

    if (!progname.Initialize("*") ||
        !help_arg.Initialize("/?") ||
        !drive_arg.Initialize("*:") ||
        !label_arg.Initialize()) {
        return 1;
    }

    if (!arg_array.Put(&progname) ||
        !arg_array.Put(&drive_arg) ||
        !arg_array.Put(&help_arg) ||
        !arg_array.Put(&label_arg)) {
        return 1;
    }

    if (!arglex.DoParsing(&arg_array)) {
        msg.Set(MSG_INVALID_PARAMETER);
        msg.Display("%W", p = arglex.QueryInvalidArgument());
        return 1;
    }

    if (help_arg.QueryFlag()) {
        DisplayLabelUsage(&msg);
        return 0;
    }


    if (drive_arg.IsValueSet()) {
        if (!drive_string.Initialize(drive_arg.GetString()) ||
            !drive_string.Strcat(colon.Initialize((PWSTR) L":"))) {

            return 1;
        }
    } else {

        if (!SYSTEM::QueryCurrentDosDriveName(&drive_string)) {
            return 1;
        }
    }


    if (label_arg.IsValueSet()) {

        if (!label_path.Initialize(label_arg.GetRestOfLine())) {
            return 1;
        }

        if (p = label_path.QueryDevice()) {
            if (drive_arg.IsValueSet()) {
                msg.Set(MSG_INVALID_PARAMETER);
                msg.Display("%W", label_arg.GetRestOfLine());
                return 1;
            }

            if (!drive_string.Initialize(p)) {
                return 1;
            }

            DELETE(p);
        }

        if (p = label_path.QueryDirsAndName()) {
            if (!label_string.Initialize(p)) {
                return 1;
            }
            DELETE(p);
        } else {
            if (!label_string.Initialize("")) {
                return 1;
            }
        }
    }


    if (!label_string.QueryChCount()) {

        if (!GetLabelInput(&drive_string, &label_exists,
                           &label_string, &msg)) {
            return 1;
        }
    }

    if (!label_string.QueryChCount()) {
        if (label_exists) {
            msg.Set(MSG_LBL_DELETE_LABEL);
            msg.Display("");
            if (!msg.IsYesResponse(FALSE)) {
                return 0;
            }
        } else {
            return 0;
        }
    }

    return SetLabel(&drive_string, &label_string, &msg) ? 0 : 1;
}
