
/*++

    zwingdi.h : header file for win32 api profiling dll for the GDI32
                 system dll

        Provides index by API name into profiling data structures.
         Creates array of API names for use in dumping data.

         NOTE:  This file is generated by WRAPPER code generator.

--*/


#define MODULE_NAME	"gdi32"
#define API_COUNT       283
#define	DATA_SEM_NAME	"\\BaseNamedObjects\\Gdi32DataSem"
#define	DATA_SEC_NAME	"\\BaseNamedObjects\\Gdi32DataSection"

#define I_AbortDoc        (1-1)
#define I_AbortPath        (2-1)
#define I_AddFontResourceA        (3-1)
#define I_AddFontResourceW        (4-1)
#define I_AngleArc        (5-1)
#define I_AnimatePalette        (6-1)
#define I_Arc        (7-1)
#define I_ArcTo        (8-1)
#define I_BeginPath        (9-1)
#define I_BitBlt        (10-1)
#define I_CancelDC        (11-1)
#define I_Chord        (12-1)
#define I_CloseEnhMetaFile        (13-1)
#define I_CloseFigure        (14-1)
#define I_CloseMetaFile        (15-1)
#define I_CombineRgn        (16-1)
#define I_CombineTransform        (17-1)
#define I_CopyEnhMetaFileA        (18-1)
#define I_CopyEnhMetaFileW        (19-1)
#define I_CopyMetaFileA        (20-1)
#define I_CopyMetaFileW        (21-1)
#define I_CreateBitmap        (22-1)
#define I_CreateBitmapIndirect        (23-1)
#define I_CreateBrushIndirect        (24-1)
#define I_CreateCompatibleBitmap        (25-1)
#define I_CreateCompatibleDC        (26-1)
#define I_CreateDCA        (27-1)
#define I_CreateDCW        (28-1)
#define I_CreateDIBPatternBrush        (29-1)
#define I_CreateDIBPatternBrushPt        (30-1)
#define I_CreateDIBitmap        (31-1)
#define I_CreateDiscardableBitmap        (32-1)
#define I_CreateEllipticRgn        (33-1)
#define I_CreateEllipticRgnIndirect        (34-1)
#define I_CreateEnhMetaFileA        (35-1)
#define I_CreateEnhMetaFileW        (36-1)
#define I_CreateFontA        (37-1)
#define I_CreateFontIndirectA        (38-1)
#define I_CreateFontIndirectW        (39-1)
#define I_CreateFontW        (40-1)
#define I_CreateHalftonePalette        (41-1)
#define I_CreateHatchBrush        (42-1)
#define I_CreateICA        (43-1)
#define I_CreateICW        (44-1)
#define I_CreateMetaFileA        (45-1)
#define I_CreateMetaFileW        (46-1)
#define I_CreatePalette        (47-1)
#define I_CreatePatternBrush        (48-1)
#define I_CreatePen        (49-1)
#define I_CreatePenIndirect        (50-1)
#define I_CreatePolyPolygonRgn        (51-1)
#define I_CreatePolygonRgn        (52-1)
#define I_CreateRectRgn        (53-1)
#define I_CreateRectRgnIndirect        (54-1)
#define I_CreateRoundRectRgn        (55-1)
#define I_CreateScalableFontResourceA        (56-1)
#define I_CreateScalableFontResourceW        (57-1)
#define I_CreateSolidBrush        (58-1)
#define I_DPtoLP        (59-1)
#define I_DeleteDC        (60-1)
#define I_DeleteEnhMetaFile        (61-1)
#define I_DeleteMetaFile        (62-1)
#define I_DeleteObject        (63-1)
#define I_DrawEscape        (64-1)
#define I_Ellipse        (65-1)
#define I_EndDoc        (66-1)
#define I_EndPage        (67-1)
#define I_EndPath        (68-1)
#define I_EnumEnhMetaFile        (69-1)
#define I_EnumFontFamiliesA        (70-1)
#define I_EnumFontFamiliesW        (71-1)
#define I_EnumFontsA        (72-1)
#define I_EnumFontsW        (73-1)
#define I_EnumMetaFile        (74-1)
#define I_EnumObjects        (75-1)
#define I_EqualRgn        (76-1)
#define I_Escape        (77-1)
#define I_ExcludeClipRect        (78-1)
#define I_ExtCreatePen        (79-1)
#define I_ExtCreateRegion        (80-1)
#define I_ExtEscape        (81-1)
#define I_ExtFloodFill        (82-1)
#define I_ExtSelectClipRgn        (83-1)
#define I_ExtTextOutA        (84-1)
#define I_ExtTextOutW        (85-1)
#define I_FillPath        (86-1)
#define I_FillRgn        (87-1)
#define I_FixBrushOrgEx        (88-1)
#define I_FlattenPath        (89-1)
#define I_FloodFill        (90-1)
#define I_FrameRgn        (91-1)
#define I_GdiComment        (92-1)
#define I_GdiFlush        (93-1)
#define I_GdiGetBatchLimit        (94-1)
#define I_GdiSetBatchLimit        (95-1)
#define I_GetArcDirection        (96-1)
#define I_GetAspectRatioFilterEx        (97-1)
#define I_GetBitmapBits        (98-1)
#define I_GetBitmapDimensionEx        (99-1)
#define I_GetBkColor        (100-1)
#define I_GetBkMode        (101-1)
#define I_GetBoundsRect        (102-1)
#define I_GetBrushOrgEx        (103-1)
#define I_GetCharABCWidthsA        (104-1)
#define I_GetCharABCWidthsFloatA        (105-1)
#define I_GetCharABCWidthsFloatW        (106-1)
#define I_GetCharABCWidthsW        (107-1)
#define I_GetCharWidth32A        (108-1)
#define I_GetCharWidth32W        (109-1)
#define I_GetCharWidthA        (110-1)
#define I_GetCharWidthFloatA        (111-1)
#define I_GetCharWidthFloatW        (112-1)
#define I_GetCharWidthW        (113-1)
#define I_GetClipBox        (114-1)
#define I_GetClipRgn        (115-1)
#define I_GetColorAdjustment        (116-1)
#define I_GetCurrentObject        (117-1)
#define I_GetCurrentPositionEx        (118-1)
#define I_GetDCOrgEx        (119-1)
#define I_GetDIBits        (120-1)
#define I_GetDeviceCaps        (121-1)
#define I_GetEnhMetaFileA        (122-1)
#define I_GetEnhMetaFileBits        (123-1)
#define I_GetEnhMetaFileDescriptionA        (124-1)
#define I_GetEnhMetaFileDescriptionW        (125-1)
#define I_GetEnhMetaFileHeader        (126-1)
#define I_GetEnhMetaFilePaletteEntries        (127-1)
#define I_GetEnhMetaFileW        (128-1)
#define I_GetFontData        (129-1)
#define I_GetGlyphOutlineA        (130-1)
#define I_GetGlyphOutlineW        (131-1)
#define I_GetGraphicsMode        (132-1)
#define I_GetKerningPairsA        (133-1)
#define I_GetKerningPairsW        (134-1)
#define I_GetMapMode        (135-1)
#define I_GetMetaFileA        (136-1)
#define I_GetMetaFileBitsEx        (137-1)
#define I_GetMetaFileW        (138-1)
#define I_GetMetaRgn        (139-1)
#define I_GetMiterLimit        (140-1)
#define I_GetNearestColor        (141-1)
#define I_GetNearestPaletteIndex        (142-1)
#define I_GetObjectA        (143-1)
#define I_GetObjectType        (144-1)
#define I_GetObjectW        (145-1)
#define I_GetOutlineTextMetricsA        (146-1)
#define I_GetOutlineTextMetricsW        (147-1)
#define I_GetPaletteEntries        (148-1)
#define I_GetPath        (149-1)
#define I_GetPixel        (150-1)
#define I_GetPolyFillMode        (151-1)
#define I_GetROP2        (152-1)
#define I_GetRasterizerCaps        (153-1)
#define I_GetRegionData        (154-1)
#define I_GetRgnBox        (155-1)
#define I_GetStockObject        (156-1)
#define I_GetStretchBltMode        (157-1)
#define I_GetSystemPaletteEntries        (158-1)
#define I_GetSystemPaletteUse        (159-1)
#define I_GetTextAlign        (160-1)
#define I_GetTextCharacterExtra        (161-1)
#define I_GetTextColor        (162-1)
#define I_GetTextExtentExPointA        (163-1)
#define I_GetTextExtentExPointW        (164-1)
#define I_GetTextExtentPoint32A        (165-1)
#define I_GetTextExtentPoint32W        (166-1)
#define I_GetTextExtentPointA        (167-1)
#define I_GetTextExtentPointW        (168-1)
#define I_GetTextFaceA        (169-1)
#define I_GetTextFaceW        (170-1)
#define I_GetTextMetricsA        (171-1)
#define I_GetTextMetricsW        (172-1)
#define I_GetViewportExtEx        (173-1)
#define I_GetViewportOrgEx        (174-1)
#define I_GetWinMetaFileBits        (175-1)
#define I_GetWindowExtEx        (176-1)
#define I_GetWindowOrgEx        (177-1)
#define I_GetWorldTransform        (178-1)
#define I_IntersectClipRect        (179-1)
#define I_InvertRgn        (180-1)
#define I_LPtoDP        (181-1)
#define I_LineDDA        (182-1)
#define I_LineTo        (183-1)
#define I_MaskBlt        (184-1)
#define I_ModifyWorldTransform        (185-1)
#define I_MoveToEx        (186-1)
#define I_OffsetClipRgn        (187-1)
#define I_OffsetRgn        (188-1)
#define I_OffsetViewportOrgEx        (189-1)
#define I_OffsetWindowOrgEx        (190-1)
#define I_PaintRgn        (191-1)
#define I_PatBlt        (192-1)
#define I_PathToRegion        (193-1)
#define I_Pie        (194-1)
#define I_PlayEnhMetaFile        (195-1)
#define I_PlayEnhMetaFileRecord        (196-1)
#define I_PlayMetaFile        (197-1)
#define I_PlayMetaFileRecord        (198-1)
#define I_PlgBlt        (199-1)
#define I_PolyBezier        (200-1)
#define I_PolyBezierTo        (201-1)
#define I_PolyDraw        (202-1)
#define I_PolyPolygon        (203-1)
#define I_PolyPolyline        (204-1)
#define I_PolyTextOutA        (205-1)
#define I_PolyTextOutW        (206-1)
#define I_Polygon        (207-1)
#define I_Polyline        (208-1)
#define I_PolylineTo        (209-1)
#define I_PtInRegion        (210-1)
#define I_PtVisible        (211-1)
#define I_RealizePalette        (212-1)
#define I_RectInRegion        (213-1)
#define I_RectVisible        (214-1)
#define I_Rectangle        (215-1)
#define I_RemoveFontResourceA        (216-1)
#define I_RemoveFontResourceW        (217-1)
#define I_ResetDCA        (218-1)
#define I_ResetDCW        (219-1)
#define I_ResizePalette        (220-1)
#define I_RestoreDC        (221-1)
#define I_RoundRect        (222-1)
#define I_SaveDC        (223-1)
#define I_ScaleViewportExtEx        (224-1)
#define I_ScaleWindowExtEx        (225-1)
#define I_SelectClipPath        (226-1)
#define I_SelectClipRgn        (227-1)
#define I_SelectObject        (228-1)
#define I_SelectPalette        (229-1)
#define I_SetAbortProc        (230-1)
#define I_SetArcDirection        (231-1)
#define I_SetBitmapBits        (232-1)
#define I_SetBitmapDimensionEx        (233-1)
#define I_SetBkColor        (234-1)
#define I_SetBkMode        (235-1)
#define I_SetBoundsRect        (236-1)
#define I_SetBrushOrgEx        (237-1)
#define I_SetColorAdjustment        (238-1)
#define I_SetDIBits        (239-1)
#define I_SetDIBitsToDevice        (240-1)
#define I_SetEnhMetaFileBits        (241-1)
#define I_SetGraphicsMode        (242-1)
#define I_SetMapMode        (243-1)
#define I_SetMapperFlags        (244-1)
#define I_SetMetaFileBitsEx        (245-1)
#define I_SetMetaRgn        (246-1)
#define I_SetMiterLimit        (247-1)
#define I_SetPaletteEntries        (248-1)
#define I_SetPixel        (249-1)
#define I_SetPixelV        (250-1)
#define I_SetPolyFillMode        (251-1)
#define I_SetROP2        (252-1)
#define I_SetRectRgn        (253-1)
#define I_SetStretchBltMode        (254-1)
#define I_SetSystemPaletteUse        (255-1)
#define I_SetTextAlign        (256-1)
#define I_SetTextCharacterExtra        (257-1)
#define I_SetTextColor        (258-1)
#define I_SetTextJustification        (259-1)
#define I_SetViewportExtEx        (260-1)
#define I_SetViewportOrgEx        (261-1)
#define I_SetWinMetaFileBits        (262-1)
#define I_SetWindowExtEx        (263-1)
#define I_SetWindowOrgEx        (264-1)
#define I_SetWorldTransform        (265-1)
#define I_StartDocA        (266-1)
#define I_StartDocW        (267-1)
#define I_StartPage        (268-1)
#define I_StretchBlt        (269-1)
#define I_StretchDIBits        (270-1)
#define I_StrokeAndFillPath        (271-1)
#define I_StrokePath        (272-1)
#define I_TextOutA        (273-1)
#define I_TextOutW        (274-1)
#define I_UnrealizeObject        (275-1)
#define I_UpdateColors        (276-1)
#define I_WidenPath        (277-1)
#define I_ChoosePixelFormat (278-1)
#define I_CreateDIBSection (279-1)
#define I_GetDIBColorTable (280-1)
#define I_SetDIBColorTable (281-1)
#define I_GetPixelFormat (282-1)
#define I_SetPixelFormat (283-1)
