/* SCCLS.C 06/04/94 15.29.56 */
UT_ENTRYSC LSERR UT_ENTRYMOD LSCreateList (DWORD dwId, DWORD dwFlags, DWORD
	 dwElementSize, HANDLE FAR *phList);
UT_ENTRYSC LSERR UT_ENTRYMOD LSOpenList (DWORD dwId, DWORD dwFlags, HANDLE FAR
	 *phList);
UT_ENTRYSC LSERR UT_ENTRYMOD LSWriteList (HANDLE hList);
UT_ENTRYSC LSERR UT_ENTRYMOD LSCloseList (HANDLE hList, BOOL bSave);
UT_ENTRYSC LSERR UT_ENTRYMOD LSAddElement (HANDLE hList, VOID FAR *pElement);
UT_ENTRYSC LSERR UT_ENTRYMOD LSClearList (HANDLE hList);
UT_ENTRYSC LSERR UT_ENTRYMOD LSGetListCount (HANDLE hList, DWORD FAR *pCount);
LSERR LSGetListId (HANDLE hList, DWORD FAR *pId);
LSERR LSGetListDirty (HANDLE hList, BOOL FAR *pDirty);
LSERR LSSetListDirty (HANDLE hList, BOOL bDirty);
UT_ENTRYSC LSERR UT_ENTRYMOD LSGetListElementSize (HANDLE hList, DWORD FAR *
	pSize);
UT_ENTRYSC LSERR UT_ENTRYMOD LSGetElementByIndex (HANDLE hList, DWORD dwIndex,
	 VOID FAR *pElement);
UT_ENTRYSC LSERR UT_ENTRYMOD LSLockElementByIndex (HANDLE hList, DWORD dwIndex
	, VOID FAR *FAR *ppElement);
UT_ENTRYSC LSERR UT_ENTRYMOD LSUnlockElementByIndex (HANDLE hList, DWORD
	 dwIndex);
