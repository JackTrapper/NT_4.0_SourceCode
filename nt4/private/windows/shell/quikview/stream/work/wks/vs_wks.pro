/* VS_WKS.C 25/01/95 09.25.50 */
VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamOpenFunc (SOFILE fp, SHORT FileId, BYTE
	 VWPTR *FileName, SOFILTERINFO VWPTR *FilterInfo, HPROC hProc);
VW_LOCALSC SHORT VW_LOCALMOD xbfilbuf (HPROC hProc);
VW_LOCALSC SHORT VW_LOCALMOD xbseek (LONG logical_offset, SHORT origin, HPROC
	 hProc);
VW_LOCALSC WORD VW_LOCALMOD AllocateMemory (HANDLE VWPTR *h, LPBYTE VWPTR *lp,
	 WORD Size, WORD *Ok, HPROC hProc);
VW_LOCALSC VOID VW_LOCALMOD GetQuattroColLoc (HPROC hProc);
VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamSeekFunc (SOFILE hFile, HPROC hProc);
VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamTellFunc (SOFILE fp, HPROC hProc);
VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamSectionFunc (SOFILE fp, HPROC hProc);
VW_LOCALSC WORD VW_LOCALMOD get_int (HPROC hProc);
VW_LOCALSC SHORT VW_LOCALMOD get_8_byte_double (CHAR VWPTR *dbl_ch, HPROC hProc
	);
VW_LOCALSC VOID VW_LOCALMOD format_wk3_num (PSODATACELL data_cell, BYTE nfmt,
	 BYTE cdgs, BOOL multi_flag, HPROC hProc);
VW_LOCALSC VOID VW_LOCALMOD format_num (PSODATACELL data_cell, HPROC hProc);
VW_LOCALSC SHORT VW_LOCALMOD convert_alignment (CHAR ch, HPROC hProc);
VW_LOCALSC SHORT VW_LOCALMOD process_cell (HPROC hProc);
VW_LOCALSC SHORT VW_LOCALMOD goto_next_cell (SHORT StartCol, SHORT EndCol,
	 HPROC hProc);
VW_ENTRYSC VOID VW_ENTRYMOD VwStreamCloseFunc (SOFILE hFile, HPROC hProc);
VW_ENTRYSC SHORT VW_ENTRYMOD VwStreamReadFunc (SOFILE fp, HPROC hProc);
