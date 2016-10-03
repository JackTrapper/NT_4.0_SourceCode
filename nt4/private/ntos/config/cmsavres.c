/*++

Copyright (c) 1992  Microsoft Corporation

Module Name:

    cmsavres.c

Abstract:

    This file contains code for SaveKey and RestoreKey.

Author:

    Bryan M. Willman (bryanwi) 15-Jan-92

Revision History:

--*/

#include    "cmp.h"

//
// defines how big the buffer we use for doing a savekey by copying the
// hive file should be.
//
#define CM_SAVEKEYBUFSIZE 0x10000

extern PCMHIVE CmpMasterHive;

extern  BOOLEAN CmpProfileLoaded;

extern PUCHAR  CmpStashBuffer;

PCMHIVE
CmpCreateTemporaryHive(
    IN HANDLE FileHandle
    );

VOID
CmpDestroyTemporaryHive(
    PCMHIVE CmHive
    );

NTSTATUS
CmpLoadHiveVolatile(
    IN PCM_KEY_CONTROL_BLOCK KeyControlBlock,
    IN HANDLE FileHandle
    );

NTSTATUS
CmpRefreshHive(
    IN PCM_KEY_CONTROL_BLOCK KeyControlBlock
    );

NTSTATUS
CmpSaveKeyByFileCopy(
    PCMHIVE Hive,
    HANDLE  FileHandle
    );

ULONG
CmpRefreshWorkerRoutine(
    PCM_KEY_CONTROL_BLOCK Current,
    PVOID                 Context1,
    PVOID                 Context2
    );


#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE,CmRestoreKey)
#pragma alloc_text(PAGE,CmpLoadHiveVolatile)
#pragma alloc_text(PAGE,CmpRefreshHive)
#pragma alloc_text(PAGE,CmSaveKey)
#pragma alloc_text(PAGE,CmpCreateTemporaryHive)
#pragma alloc_text(PAGE,CmpDestroyTemporaryHive)
#pragma alloc_text(PAGE,CmpRefreshWorkerRoutine)
#pragma alloc_text(PAGE,CmpSaveKeyByFileCopy)
#endif


NTSTATUS
CmRestoreKey(
    IN PCM_KEY_CONTROL_BLOCK KeyControlBlock,
    IN HANDLE  FileHandle,
    IN ULONG Flags
    )
/*++

Routine Description:

    This copies the data from an on-disk hive into the registry.  The file
    is not loaded into the registry, and the system will NOT be using
    the source file after the call returns.

    If the flag REG_WHOLE_HIVE_VOLATILE is not set, the given key is replaced
    by the root of the hive file.  The root's name is changed to the name
    of the given key.

    If the flag REG_WHOLE_HIVE_VOLATILE is set, a volatile hive is created,
    the hive file is copied into it, and the resulting hive is linked to
    the master hive.  The given key must be in the master hive.  (Usually
    will be \Registry\User)

    If the flag REG_REFRESH_HIVE is set (must be only flag) then the
    the Hive will be restored to its state as of the last flush.
    (The hive must be marked NOLAZY_FLUSH, and the caller must have
     TCB privilege, and the handle must point to the root of the hive.
     If the refresh fails, the hive will be corrupt, and the system
     will bugcheck.)

Arguments:

    Hive - supplies a pointer to the hive control structure for the hive

    Cell - supplies index of node at root of tree to restore into

    FileHandle - handle of the file to read from.

Return Value:

    NTSTATUS - Result code from call, among the following:

        <TBS>

--*/
{
    NTSTATUS    status;
    PCELL_DATA  ptar;
    PCELL_DATA  psrc;
    PCMHIVE     TmpCmHive;
    HCELL_INDEX newroot;
    HCELL_INDEX newcell;
    HCELL_INDEX parent;
    HCELL_INDEX list;
    ULONG       count;
    ULONG       i;
    ULONG       j;
    LONG        size;
    LONG        change; // must be signed
    PHHIVE      Hive;
    HCELL_INDEX Cell;
    HSTORAGE_TYPE Type;
    ULONG       NumberLeaves;
    PHCELL_INDEX LeafArray;
    PCM_KEY_INDEX Leaf;
    PCM_KEY_FAST_INDEX FastLeaf;

    PAGED_CODE();
    CMLOG(CML_MAJOR, CMS_SAVRES) {
        KdPrint(("CmRestoreKey:\n"));
        KdPrint(("\tKCB=%08lx\n",KeyControlBlock));
        KdPrint(("\tFileHandle=%08lx\n",FileHandle));
    }

    if (Flags & REG_REFRESH_HIVE) {
        if ((Flags & ~REG_REFRESH_HIVE) != 0) {
            //
            // Refresh must be alone
            //
            return STATUS_INVALID_PARAMETER;
        }
    }

    //
    // If they want to do WHOLE_HIVE_VOLATILE, it's a completely different API.
    //
    if (Flags & REG_WHOLE_HIVE_VOLATILE) {
        return(CmpLoadHiveVolatile(KeyControlBlock, FileHandle));
    }

    //
    // If they want to do REFRESH_HIVE, that's a completely different api too.
    //
    if (Flags & REG_REFRESH_HIVE) {
        CmpLockRegistryExclusive();
        status = CmpRefreshHive(KeyControlBlock);
        CmpUnlockRegistry();
        return status;
    }

    Hive = KeyControlBlock->KeyHive;
    Cell = KeyControlBlock->KeyCell;

    //
    // Disallow attempts to "restore" the master hive
    //
    if (Hive == &CmpMasterHive->Hive) {
        return STATUS_ACCESS_DENIED;
    }

    CmpLockRegistryExclusive();

    //
    // Make sure this is the only handle open for this key, AND
    // that key has not been deleted
    //
    if ((KeyControlBlock->RefCount != 1) || (KeyControlBlock->Delete)) {
        CmpUnlockRegistry();
        return(STATUS_CANNOT_DELETE);
    }

    DCmCheckRegistry(CONTAINING_RECORD(Hive, CMHIVE, Hive));

    //
    // Check for any open handles underneath the key we are restoring to.
    //
    if (CmpSearchForOpenSubKeys(KeyControlBlock)) {

        //
        // Cannot restore over a subtree with open handles in it.
        //

        CmpUnlockRegistry();
        return(STATUS_CANNOT_DELETE);
    }

    ptar = HvGetCell(Hive, Cell);

    //
    // The subtree the caller wants does not exactly match a
    // subtree.  Make a temporary hive, load the file into it,
    // tree copy the temporary to the active, and free the temporary.
    //

    //
    // Create the temporary hive
    //
    if (!CmpInitializeHive(&TmpCmHive,
                           HINIT_FILE,
                           0,
                           HFILE_TYPE_PRIMARY,
                           NULL,
                           FileHandle,
                           NULL,
                           NULL,
                           NULL,
                           NULL)) {

        status = STATUS_INSUFFICIENT_RESOURCES;
        goto ErrorExit1;
    }

    //
    // Create a new target root, under which we will copy the new tree
    //
    if (ptar->u.KeyNode.Flags & KEY_HIVE_ENTRY) {
        parent = HCELL_NIL;                         // root of hive, so parent is NIL
    } else {
        parent = ptar->u.KeyNode.Parent;
    }

    newroot = CmpCopyKeyPartial(
                &(TmpCmHive->Hive),
                TmpCmHive->Hive.BaseBlock->RootCell,
                Hive,
                parent,
                TRUE
                );
    if (newroot == HCELL_NIL) {
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto ErrorExit2;
    }

    //
    // newroot has all the correct stuff, except that it has the
    // source root's name, when it needs to have the target root's.
    // So edit its name.
    //
    psrc = HvGetCell(Hive, Cell);
    ptar = HvGetCell(Hive, newroot);
    size = HvGetCellSize(Hive, ptar);

    // psrc->old root
    // ptar->new root

    //
    // make sure that new root has correct amount of space
    // to hold name from old root
    //
    change = (LONG)psrc->u.KeyNode.NameLength -
                (LONG)ptar->u.KeyNode.NameLength;

    if (change != 0) {
        newcell = HvReallocateCell(Hive, newroot, size+change);
        if (newcell == HCELL_NIL) {
            status = STATUS_INSUFFICIENT_RESOURCES;
            goto ErrorExit2;
        }
        newroot = newcell;
        ptar = HvGetCell(Hive, newroot);
    }

    status = STATUS_SUCCESS;

    RtlMoveMemory(
        (PVOID)&(ptar->u.KeyNode.Name[0]),
        (PVOID)&(psrc->u.KeyNode.Name[0]),
        psrc->u.KeyNode.NameLength
        );

    ptar->u.KeyNode.NameLength = psrc->u.KeyNode.NameLength;
    if (psrc->u.KeyNode.Flags & KEY_COMP_NAME) {
        ptar->u.KeyNode.Flags |= KEY_COMP_NAME;
    } else {
        ptar->u.KeyNode.Flags &= ~KEY_COMP_NAME;
    }

    //
    // newroot is now ready to have subtree copied under it, do tree copy
    //
    if (CmpCopyTree(
            &(TmpCmHive->Hive),
            TmpCmHive->Hive.BaseBlock->RootCell,
            Hive,
            newroot
            ) == FALSE)
    {
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto ErrorExit2;
    }

    //
    // The new root and the tree under it now look the way we want.
    //

    //
    // Swap the new tree in for the old one.
    //
    ptar = HvGetCell(Hive, Cell);
    parent = ptar->u.KeyNode.Parent;

    if (ptar->u.KeyNode.Flags & KEY_HIVE_ENTRY) {

        //
        // root is actually the root of the hive.  parent doesn't
        // refer to it via a child list, but rather with an inter hive
        // pointer.  also, must update base block
        //
        ptar = HvGetCell( (&(CmpMasterHive->Hive)), parent);
        ptar->u.KeyNode.u1.ChildHiveReference.KeyCell = newroot;
        ptar = HvGetCell(Hive, newroot);
        ptar->u.KeyNode.Parent = parent;
        Hive->BaseBlock->RootCell = newroot;


    } else {

        //
        //  Notice that new root is *always* name of existing target,
        //      therefore, even in b-tree, old and new cell can share
        //      the same reference slot in the parent.  So simply edit
        //      the new cell_index on the top of the old.
        //
        ptar = HvGetCell(Hive, parent);
        Type = HvGetCellType(Cell);
        list = ptar->u.KeyNode.SubKeyLists[Type];
        count = ptar->u.KeyNode.SubKeyCounts[Type];

        ptar = HvGetCell(Hive, list);
        if (ptar->u.KeyIndex.Signature == CM_KEY_INDEX_ROOT) {
            NumberLeaves = ptar->u.KeyIndex.Count;
            LeafArray = &ptar->u.KeyIndex.List[0];
        } else {
            NumberLeaves = 1;
            LeafArray = &list;
        }

        //
        // Look in each leaf for the HCELL_INDEX we need to replace
        //
        for (i = 0; i < NumberLeaves; i++) {
            Leaf = (PCM_KEY_INDEX)HvGetCell(Hive, LeafArray[i]);
            if (Leaf->Signature == CM_KEY_FAST_LEAF) {
                FastLeaf = (PCM_KEY_FAST_INDEX)Leaf;
                for (j=0; j < FastLeaf->Count; j++) {
                    if (FastLeaf->List[j].Cell == Cell) {
                        FastLeaf->List[j].Cell = newroot;
                        goto FoundCell;
                    }
                }
            } else {
                for (j=0; j < Leaf->Count; j++) {
                    if (Leaf->List[j] == Cell) {

                        Leaf->List[j] = newroot;
                        goto FoundCell;
                    }
                }
            }
        }
        ASSERT(FALSE);      //  implies we didn't find it
                        //  we should never get here
    }

FoundCell:


    //
    // Fix up the key control block to point to the new root
    //
    KeyControlBlock->KeyCell = newroot;
    KeyControlBlock->KeyNode = (PCM_KEY_NODE)HvGetCell(Hive, newroot);
    CmpReinsertKeyControlBlock(KeyControlBlock);


    //
    // Delete the old subtree and it's root cell
    //
    CmpDeleteTree(Hive, Cell);
    CmpFreeKeyByCell(Hive, Cell, FALSE);

    //
    // Report the notify event
    //
    CmpReportNotify(KeyControlBlock->FullName,
                    KeyControlBlock->KeyHive,
                    KeyControlBlock->KeyCell,
                    REG_NOTIFY_CHANGE_NAME);

    //
    // Free the temporary hive
    //
    CmpDestroyTemporaryHive(TmpCmHive);

    //
    // We've given user chance to log on, so turn on quota
    //
    if (CmpProfileLoaded == FALSE) {
        CmpProfileLoaded = TRUE;
        CmpSetGlobalQuotaAllowed();
    }

    DCmCheckRegistry(CONTAINING_RECORD(Hive, CMHIVE, Hive));
    CmpUnlockRegistry();
    return status;


    //
    // Error exits
    //
ErrorExit2:
    CmpDestroyTemporaryHive(TmpCmHive);
ErrorExit1:
    DCmCheckRegistry(CONTAINING_RECORD(Hive, CMHIVE, Hive));
    CmpUnlockRegistry();

    return status;
}


NTSTATUS
CmpLoadHiveVolatile(
    IN PCM_KEY_CONTROL_BLOCK KeyControlBlock,
    IN HANDLE FileHandle
    )

/*++

Routine Description:

    Creates a VOLATILE hive and loads it underneath the given Hive and Cell.
    The data for the volatile hive is copied out of the given file.  The
    file is *NOT* in use by the registry when this returns.

Arguments:

    Hive - Supplies the hive that the new hive is to be created under.
           Currently this must be the Master Hive.

    Cell - Supplies the HCELL_INDEX of the new hive's parent.  (Usually
           will by \Registry\User)

    FileHandle - Supplies a handle to the hive file that will be copied
           into the volatile hive.

Return Value:

    NTSTATUS

--*/

{
    PHHIVE Hive;
    PCELL_DATA RootData;
    PCMHIVE NewHive;
    PCMHIVE TempHive;
    HCELL_INDEX Cell;
    HCELL_INDEX Root;
    REGISTRY_COMMAND Command;
    NTSTATUS Status;
    UNICODE_STRING RootName;
    UNICODE_STRING NewName;
    USHORT NewNameLength;


    PAGED_CODE();
    CmpLockRegistryExclusive();

    if (KeyControlBlock->Delete) {
        CmpUnlockRegistry();
        return(STATUS_KEY_DELETED);
    }
    Hive = KeyControlBlock->KeyHive;
    Cell = KeyControlBlock->KeyCell;

    //
    // New hives can be created only under the master hive.
    //

    if (Hive != &CmpMasterHive->Hive) {
        CmpUnlockRegistry();
        return(STATUS_INVALID_PARAMETER);
    }

    //
    // Create a temporary hive and load the file into it
    //
    if (!CmpInitializeHive(&TempHive,
                           HINIT_FILE,
                           0,
                           HFILE_TYPE_PRIMARY,
                           NULL,
                           FileHandle,
                           NULL,
                           NULL,
                           NULL,
                           NULL)) {
        CmpUnlockRegistry();
        return(STATUS_INSUFFICIENT_RESOURCES);
    }

    //
    // Create the volatile hive.
    //
    if (!CmpInitializeHive(&NewHive,
                           HINIT_CREATE,
                           HIVE_VOLATILE,
                           0,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL)) {
        CmpDestroyTemporaryHive(TempHive);
        CmpUnlockRegistry();
        return(STATUS_INSUFFICIENT_RESOURCES);
    }

    //
    // Create the target root
    //
    Root = CmpCopyKeyPartial(&TempHive->Hive,
                             TempHive->Hive.BaseBlock->RootCell,
                             &NewHive->Hive,
                             HCELL_NIL,
                             FALSE);
    if (Root == HCELL_NIL) {
        CmpDestroyTemporaryHive(TempHive);
        CmpDestroyTemporaryHive(NewHive);
        CmpUnlockRegistry();
        return(STATUS_INSUFFICIENT_RESOURCES);
    }
    NewHive->Hive.BaseBlock->RootCell = Root;

    //
    // Copy the temporary hive into the volatile hive
    //
    if (!CmpCopyTree(&TempHive->Hive,
                    TempHive->Hive.BaseBlock->RootCell,
                    &NewHive->Hive,
                    Root))
    {
        CmpDestroyTemporaryHive(TempHive);
        CmpDestroyTemporaryHive(NewHive);
        CmpUnlockRegistry();
        return(STATUS_INSUFFICIENT_RESOURCES);
    }

    //
    // The volatile hive now has all the right stuff in all the right places,
    // we just need to link it into the master hive.
    //
    RootData = HvGetCell(&NewHive->Hive,Root);
    NewNameLength = KeyControlBlock->FullName.Length +
                    CmpHKeyNameLen(&RootData->u.KeyNode) +
                    sizeof(WCHAR);
    NewName.Buffer = ExAllocatePool(PagedPool, NewNameLength);
    if (NewName.Buffer == NULL) {
        CmpDestroyTemporaryHive(TempHive);
        CmpDestroyTemporaryHive(NewHive);
        CmpUnlockRegistry();
        return(STATUS_INSUFFICIENT_RESOURCES);
    }
    NewName.Length = NewName.MaximumLength = NewNameLength;
    RtlCopyUnicodeString(&NewName, &KeyControlBlock->FullName);
    RtlAppendUnicodeToString(&NewName, L"\\");

    if (RootData->u.KeyNode.Flags & KEY_COMP_NAME) {
        CmpCopyCompressedName(NewName.Buffer + (NewName.Length / sizeof(WCHAR)),
                              NewName.MaximumLength - NewName.Length,
                              RootData->u.KeyNode.Name,
                              CmpHKeyNameLen(&RootData->u.KeyNode));
        NewName.Length += CmpHKeyNameLen(&RootData->u.KeyNode);
    } else {
        RootName.Buffer = RootData->u.KeyNode.Name;
        RootName.Length = RootName.MaximumLength = RootData->u.KeyNode.NameLength;

        RtlAppendUnicodeStringToString(&NewName,&RootName);
    }

    Status = CmpLinkHiveToMaster(&NewName,
                                 NULL,
                                 NewHive,
                                 FALSE,
                                 NULL);
    if (NT_SUCCESS(Status)) {
        Command.CmHive = NewHive;
        Command.Command = REG_CMD_ADD_HIVE_LIST;
        CmpWorkerCommand(&Command);
    } else {
        CmpDestroyTemporaryHive(NewHive);
    }
    CmpDestroyTemporaryHive(TempHive);

    ExFreePool(NewName.Buffer);

    if (NT_SUCCESS(Status)) {
        //
        // We've given user chance to log on, so turn on quota
        //
        if (CmpProfileLoaded == FALSE) {
            CmpProfileLoaded = TRUE;
            CmpSetGlobalQuotaAllowed();
        }
    }

    CmpUnlockRegistry();
    return(Status);
}



ULONG
CmpRefreshWorkerRoutine(
    PCM_KEY_CONTROL_BLOCK Current,
    PVOID                 Context1,
    PVOID                 Context2
    )
/*++

Routine Description:

    Helper used by CmpRefreshHive when calling
    CmpSearchKeyControlBlockTree.

    If a match is found, the KCB is deleted and restart is returned.
    Else, continue is returned.

Arguments:

    Current - the kcb to examine

    Context1 - the hive to match against

    Context2 - nothing

Return Value:

    if no match, return continue.

    if match, return restart.

--*/
{
    PAGED_CODE();
    if (Current->KeyHive == (PHHIVE)Context1) {

        //
        // match.  set deleted flag.  restart search.
        //
        Current->Delete = TRUE;
        CmpRemoveKeyControlBlock(Current);
        Current->KeyHive = NULL;
        Current->KeyCell = 0;
        return KCB_WORKER_RESTART;
    } else {
        return KCB_WORKER_CONTINUE;
    }
}


NTSTATUS
CmpRefreshHive(
    IN PCM_KEY_CONTROL_BLOCK KeyControlBlock
    )
/*++

Routine Description:

    Backs out all changes to a hives since it was last flushed.
    Used as a transaction abort by the security system.

    Caller must have SeTcbPrivilege.

    The target hive must have HIVE_NOLAZYFLUSH set.

    KeyControlBlock must refer to the root of the hive (HIVE_ENTRY must
    be set in the key.)

    Any kcbs that point into this hive (and thus any handles open
    against it) will be force to DELETED state.  (If we do any work.)

    All notifies pending against the hive will be flushed.

    When we're done, only the tombstone kcbs, handles, and attached
    notify blocks will be left.

    WARNNOTE:   Once reads have begun, if the operation fails, the hive
                will be corrupt, so we will bugcheck.

Arguments:

    KeyControlBlock - provides a reference to the root of the hive
                      we wish to refresh.

Return Value:

    NTSTATUS

--*/
{
    PHHIVE              Hive;
    HCELL_INDEX         Cell;
    PCELL_DATA          pcell;
    REGISTRY_COMMAND    CommandArea;
    PLIST_ENTRY         ptr;
    PCM_NOTIFY_BLOCK    node;

    PAGED_CODE();
    //
    // Check to see if the caller has the privilege to make this call.
    //
    if (!SeSinglePrivilegeCheck(SeTcbPrivilege, KeGetPreviousMode())) {
        return STATUS_PRIVILEGE_NOT_HELD;
    }

    if (KeyControlBlock->Delete) {
        return(STATUS_KEY_DELETED);
    }
    Hive = KeyControlBlock->KeyHive;
    Cell = KeyControlBlock->KeyCell;

    //
    // check to see if hive is of proper type
    //
    if ( ! (Hive->HiveFlags & HIVE_NOLAZYFLUSH)) {
        return STATUS_INVALID_PARAMETER;
    }

    //
    // punt if any volatile storage has been allocated
    //
    if (Hive->Storage[Volatile].Length != 0) {
        return STATUS_UNSUCCESSFUL;
    }

    //
    // check to see if call was applied to the root of the hive
    //
    pcell = HvGetCell(Hive, Cell);
    if ( ! (pcell->u.KeyNode.Flags & KEY_HIVE_ENTRY)) {
        return STATUS_INVALID_PARAMETER;
    }

    //
    // Flush all NotifyBlocks attached to this hive
    //
    while (TRUE) {

        //
        // flush below will edit list, so restart at beginning each time
        //
        ptr = &(((PCMHIVE)Hive)->NotifyList);
        if (ptr->Flink == NULL) {
            break;
        }

        ptr = ptr->Flink;
        node = CONTAINING_RECORD(ptr, CM_NOTIFY_BLOCK, HiveList);
        ASSERT((node->KeyBody)->NotifyBlock == node);
        CmpFlushNotify(node->KeyBody);
    }

    //
    // Force all kcbs that refer to this hive to the deleted state.
    //
    CmpSearchKeyControlBlockTree(
        CmpRefreshWorkerRoutine,
        (PVOID)Hive,
        NULL
        );

    //
    // We cannot do the relevent I/O from this context, so send a
    // command to the worker code.
    //
    CommandArea.Command = REG_CMD_REFRESH_HIVE;
    CommandArea.Hive = Hive;
    CmpWorkerCommand(&CommandArea);

    //
    // we're back (rather than bugchecked) so it worked
    //
    return STATUS_SUCCESS;
}



NTSTATUS
CmSaveKey(
    IN PCM_KEY_CONTROL_BLOCK    KeyControlBlock,
    IN HANDLE   FileHandle
    )
/*++

Routine Description:

Arguments:

    KeyControlBlock - pointer to the KCB that describes the key

    FileHandle - handle of the file to dump to.

Return Value:

    NTSTATUS - Result code from call, among the following:

        <TBS>

--*/
{
    NTSTATUS    status;
    PCELL_DATA  proot;
    USHORT      flags;
    PCMHIVE     TmpCmHive;
    PCMHIVE     CmHive;
    HCELL_INDEX newroot;
    PHHIVE Hive;
    HCELL_INDEX Cell;

    PAGED_CODE();
    CMLOG(CML_MAJOR, CMS_SAVRES) {
        KdPrint(("CmSaveKey:\n"));
        KdPrint(("\tKCB=%08lx",KeyControlBlock));
        KdPrint(("\tFileHandle=%08lx\n",FileHandle));
    }

    //
    // Disallow attempts to "save" the master hive
    //
    Hive = KeyControlBlock->KeyHive;
    Cell = KeyControlBlock->KeyCell;

    if (Hive == &CmpMasterHive->Hive) {
        return STATUS_ACCESS_DENIED;
    }

    CmpLockRegistryExclusive();

    if (KeyControlBlock->Delete) {
        CmpUnlockRegistry();
        return STATUS_KEY_DELETED;
    }

    DCmCheckRegistry(CONTAINING_RECORD(Hive, CMHIVE, Hive));

    if ( (Hive->HiveFlags & HIVE_NOLAZYFLUSH) &&
         (Hive->DirtyCount != 0))
    {
        //
        // It's a NOLAZY hive, and there's some dirty data, so writing
        // out a snapshot of what's in memory will not give the caller
        // consistent user data.  Therefore, copy the on disk image
        // instead of the memory image
        //

        //
        // Note that this will generate weird results if the key
        // being saved is not the root of the hive, since the
        // resulting file will always be a copy of the entire hive, not
        // just the subtree they asked for.
        //
        status = CmpSaveKeyByFileCopy((PCMHIVE)Hive, FileHandle);
        CmpUnlockRegistry();
        return status;
    }

    proot = HvGetCell(Hive, Cell);
    flags = proot->u.KeyNode.Flags;


    //
    // Always try to copy the hive and write it out.  This has the
    // effect of compressing out unused free storage.
    // If there isn't space, and the savekey is of the root of the
    // hive, then just write it out directly.  (i.e. don't fail on
    // a whole hive restore just because we're out of memory.)
    //
    CMLOG(CML_FLOW, CMS_SAVRES) KdPrint(("\tSave of partial hive\n"));

    //
    // The subtree the caller wants does not exactly match a
    // subtree.  Make a temporary hive, tree copy the source
    // to temp, write out the temporary, free the temporary.
    //

    //
    // Create the temporary hive
    //

    TmpCmHive = CmpCreateTemporaryHive(FileHandle);
    if (TmpCmHive == NULL) {
        status =  STATUS_INSUFFICIENT_RESOURCES;
        goto ErrorInsufficientResources;
    }

    //
    // Create a root cell, mark it as such
    //

    newroot = CmpCopyKeyPartial(
                Hive,
                Cell,
                &(TmpCmHive->Hive),
                HCELL_NIL,          // will force KEY_HIVE_ENTRY set
                TRUE);
    if (newroot == HCELL_NIL) {
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto ErrorInsufficientResources;
    }
    TmpCmHive->Hive.BaseBlock->RootCell = newroot;

    //
    // Do a tree copy
    //
    if (CmpCopyTree(Hive, Cell, &(TmpCmHive->Hive), newroot) == FALSE) {
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto ErrorInsufficientResources;
    }

    //
    // Write the file
    //
    TmpCmHive->FileHandles[HFILE_TYPE_EXTERNAL] = FileHandle;
    status = HvWriteHive(&(TmpCmHive->Hive));
    TmpCmHive->FileHandles[HFILE_TYPE_EXTERNAL] = NULL;

    //
    // Free the temporary hive
    //
    CmpDestroyTemporaryHive(TmpCmHive);
    DCmCheckRegistry(CONTAINING_RECORD(Hive, CMHIVE, Hive));
    CmpUnlockRegistry();
    return status;

    //
    // Error exits
    //
ErrorInsufficientResources:

    if (TmpCmHive != NULL) {
        CmpDestroyTemporaryHive(TmpCmHive);
    }
    if (flags & KEY_HIVE_ENTRY) {
        //
        // We failed, for want of space, trying to write out a
        // tree that exactly matches a hive.  Therefore,
        // write it out as a raw dump.
        //
        CMLOG(CML_FLOW, CMS_SAVRES) KdPrint(("\tSave of full hive\n"));

        CmHive = CONTAINING_RECORD(Hive, CMHIVE, Hive);

        ASSERT(CmHive->FileHandles[HFILE_TYPE_EXTERNAL] == NULL);

        CmHive->FileHandles[HFILE_TYPE_EXTERNAL] = FileHandle;
        status = HvWriteHive(Hive);
        CmHive->FileHandles[HFILE_TYPE_EXTERNAL] = NULL;

    } // else fall through to standard exit

    DCmCheckRegistry(CONTAINING_RECORD(Hive, CMHIVE, Hive));
    CmpUnlockRegistry();
    return status;
}


NTSTATUS
CmpSaveKeyByFileCopy(
    PCMHIVE  CmHive,
    HANDLE  FileHandle
    )
/*++

Routine Description:

    Do special case of SaveKey by copying the hive file

Arguments:

    CmHive - supplies a pointer to an HHive

    FileHandle - open handle to target file

Return Value:

    NTSTATUS - Result code from call, among the following:

--*/
{
    PHBASE_BLOCK    BaseBlock;
    NTSTATUS        status;
    ULONG           Offset;
    ULONG           Length;
    ULONG           Position;
    REGISTRY_COMMAND   CommandArea;
    PUCHAR          CopyBuffer;
    ULONG           BufferLength;
    ULONG           BytesToCopy;

    PAGED_CODE();

    //
    // Attempt to allocate large buffer for copying stuff around.  If
    // we can't get one, just use the stash buffer.
    //
    BufferLength = CM_SAVEKEYBUFSIZE;
    try {
        CopyBuffer = ExAllocatePoolWithQuota(PagedPoolCacheAligned,
                                             BufferLength);
    } except(EXCEPTION_EXECUTE_HANDLER) {
        CopyBuffer = NULL;
    }
    if (CopyBuffer == NULL) {
        CopyBuffer = CmpStashBuffer;
        BufferLength = HBLOCK_SIZE;
    }
    //
    // Read the base block, step the sequence number, and write it out
    //
    status = STATUS_REGISTRY_IO_FAILED;

    CmHive->FileHandles[HFILE_TYPE_EXTERNAL] = FileHandle;

    Offset = 0;
    CommandArea.Command = REG_CMD_HIVE_READ;
    CommandArea.CmHive = CmHive;
    CommandArea.FileType = HFILE_TYPE_PRIMARY;
    CommandArea.Offset = &Offset;
    CommandArea.Buffer = CopyBuffer;
    CommandArea.FileSize = HBLOCK_SIZE;
    CmpWorkerCommand(&CommandArea);
    if (! NT_SUCCESS(CommandArea.Status)) {
        goto ErrorExit;
    }

    BaseBlock = (PHBASE_BLOCK)CopyBuffer;
    Length = BaseBlock->Length;

    BaseBlock->Sequence1++;

    Offset = 0;
    if ( ! CmpFileWrite((PHHIVE)CmHive, HFILE_TYPE_EXTERNAL, &Offset,
                        CopyBuffer, HBLOCK_SIZE))
    {
        goto ErrorExit;
    }

    //
    // Flush the external, so header will show corrupt until we're done
    //
    if (CmpFileFlush((PHHIVE)CmHive, HFILE_TYPE_EXTERNAL)) {
        status = STATUS_SUCCESS;
    }

    //
    // For span of data, read from master and write to external
    //
    for (Position = 0; Position < Length; Position += BytesToCopy) {

        Offset = Position + HBLOCK_SIZE;
        BytesToCopy = Length-Position;
        if (BytesToCopy > BufferLength) {
            BytesToCopy = BufferLength;
        }

        CommandArea.Command = REG_CMD_HIVE_READ;
        CommandArea.CmHive = CmHive;
        CommandArea.FileType = HFILE_TYPE_PRIMARY;
        CommandArea.Offset = &Offset;
        CommandArea.Buffer = CopyBuffer;
        CommandArea.FileSize = BytesToCopy;
        CmpWorkerCommand(&CommandArea);
        if (! NT_SUCCESS(CommandArea.Status)) {
            goto ErrorExit;
        }

        Offset = Position + HBLOCK_SIZE;
        if ( ! CmpFileWrite((PHHIVE)CmHive, HFILE_TYPE_EXTERNAL, &Offset,
                            CopyBuffer, BytesToCopy))
        {
            goto ErrorExit;
        }
    }

    //
    // Flush the external, so data is there before we update the header
    //
    if (CmpFileFlush((PHHIVE)CmHive, HFILE_TYPE_EXTERNAL)) {
        status = STATUS_SUCCESS;
    }

    //
    // Reread the base block, sync the seq #, rewrite it.
    // (Brute force, but means no memory alloc - always works)
    //
    Offset = 0;
    CommandArea.Command = REG_CMD_HIVE_READ;
    CommandArea.CmHive = CmHive;
    CommandArea.FileType = HFILE_TYPE_PRIMARY;
    CommandArea.Offset = &Offset;
    CommandArea.Buffer = CopyBuffer;
    CommandArea.FileSize = HBLOCK_SIZE;
    CmpWorkerCommand(&CommandArea);
    if (! NT_SUCCESS(CommandArea.Status)) {
        goto ErrorExit;
    }
    BaseBlock->Sequence1++;     // it got trampled when we reread it
    BaseBlock->Sequence2++;

    Offset = 0;
    if ( ! CmpFileWrite((PHHIVE)CmHive, HFILE_TYPE_EXTERNAL, &Offset,
                        CopyBuffer, HBLOCK_SIZE))
    {
        goto ErrorExit;
    }

    //
    // Flush the external, and we are done
    //
    if (CmpFileFlush((PHHIVE)CmHive, HFILE_TYPE_EXTERNAL)) {
        status = STATUS_SUCCESS;
    }

ErrorExit:
    if (CopyBuffer != CmpStashBuffer) {
        ExFreePool(CopyBuffer);
    }
    CmHive->FileHandles[HFILE_TYPE_EXTERNAL] = NULL;
    return status;
}


PCMHIVE
CmpCreateTemporaryHive(
    IN HANDLE FileHandle
    )
/*++

Routine Description:

    Allocates and inits a temporary hive.

Arguments:

    FileHandle - Supplies the handle of the file to back the hive.

Return Value:

    Pointer to CmHive.

    If NULL the operation failed.

--*/
{
    PCMHIVE TempHive;

    PAGED_CODE();

    //
    // NOTE: Hive will get put on CmpHiveListHead list.
    //       Make sure CmpDestroyTemporaryHive gets called to remove it.
    //

    if (CmpInitializeHive(&TempHive,
                          HINIT_CREATE,
                          HIVE_VOLATILE,
                          0,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          NULL)) {
        return(TempHive);
    } else {
        return(NULL);
    }

}


VOID
CmpDestroyTemporaryHive(
    PCMHIVE CmHive
    )
/*++

Routine Description:

    Frees all the pieces of a hive.

Arguments:

    CmHive - CM level hive structure to free

Return Value:

    None.

--*/
{
    PAGED_CODE();
    CMLOG(CML_MINOR, CMS_SAVRES) {
        KdPrint(("CmpDestroyTemporaryHive:\n"));
        KdPrint(("\tCmHive=%08lx\n", CmHive));
    }

    if (CmHive == NULL) {
        return;
    }

    //
    // NOTE: Hive is on CmpHiveListHead list.
    //       Remove it.
    //
    RemoveEntryList(&CmHive->HiveList);

    HvFreeHive(&(CmHive->Hive));
    CmpFree(CmHive, sizeof(CMHIVE));

    return;
}
