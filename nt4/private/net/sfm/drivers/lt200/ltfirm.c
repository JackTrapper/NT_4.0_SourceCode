/*++

Copyright (c) 1992  Microsoft Corporation

Module Name:

	ltfirm.c

Abstract:


Author:

	Stephen Hou			(stephh@microsoft.com)
	Nikhil 	Kamkolkar 	(nikhilk@microsoft.com)

Revision History:
	19 Jun 1992		Initial Version (dch@pacvax.pacersoft.com)

Notes:	Tab stop: 4
--*/

#define		LTFIRM_H_LOCALS
#include	"ltmain.h"
#include	"ltfirm.h"

//	Define file id for errorlogging
#define		FILENUM		LTFIRM

UCHAR	LtMicroCode[] =
{
#ifndef	OLD_FIRMWARE
	0x3A, 0x03, 0x00, 0x32, 0x93, 0x0A, 0x21, 0x8E, 0x0F, 0x3E,
	0x55, 0x77, 0xBE, 0x20, 0x09, 0x3E, 0xAA, 0x77, 0xBE, 0x20,
	0x03, 0x23, 0x18, 0xF1, 0x22, 0x91, 0x0A, 0xF9, 0x11, 0x95,
	0x0A, 0x21, 0x8E, 0x0F, 0xB7, 0xED, 0x52, 0x4D, 0x44, 0x0B,
	0x6B, 0x62, 0x13, 0x36, 0x00, 0xED, 0xB0, 0x3E, 0x10, 0xED,
	0x39, 0x33, 0x3E, 0x00, 0xED, 0x39, 0x32, 0xED, 0x39, 0x36,
	0x3E, 0x0C, 0xED, 0x39, 0x31, 0x3E, 0xC3, 0x21, 0x26, 0x02,
	0x32, 0x38, 0x00, 0x22, 0x39, 0x00, 0xED, 0x56, 0xCD, 0x1D,
	0x02, 0xFB, 0xCD, 0x3B, 0x0A, 0x18, 0xA9, 0x43, 0x6F, 0x70,
	0x79, 0x72, 0x69, 0x67, 0x68, 0x74, 0x20, 0x28, 0x63, 0x29,
	0x20, 0x31, 0x39, 0x38, 0x38, 0x20, 0x2D, 0x20, 0x31, 0x39,
	0x39, 0x31, 0x2C, 0x20, 0x50, 0x72, 0x69, 0x6E, 0x74, 0x69,
	0x6E, 0x67, 0x20, 0x43, 0x6F, 0x6D, 0x6D, 0x75, 0x6E, 0x69,
	0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x73, 0x20, 0x41, 0x73,
	0x73, 0x6F, 0x63, 0x69, 0x61, 0x74, 0x65, 0x73, 0x2E, 0x20,
	0x20, 0x41, 0x6C, 0x6C, 0x20, 0x72, 0x69, 0x67, 0x68, 0x74,
	0x73, 0x20, 0x72, 0x65, 0x73, 0x65, 0x72, 0x76, 0x65, 0x64,
	0x2E, 0x20, 0x20, 0x04, 0x04, 0x16, 0x28, 0xFF, 0x3C, 0x04,
	0x60, 0x0A, 0xE0, 0x06, 0x00, 0x07, 0x7E, 0x02, 0x40, 0x0B,
	0xF6, 0x0C, 0x06, 0x0D, 0x00, 0x0E, 0xC1, 0x0F, 0x00, 0x05,
	0x60, 0x03, 0xC0, 0x01, 0x00, 0x09, 0x08, 0x3E, 0x03, 0xD3,
	0x52, 0x3E, 0xC0, 0xD3, 0x52, 0xC9, 0x3E, 0x03, 0xD3, 0x52,
	0x3E, 0xD5, 0xD3, 0x52, 0xC9, 0x3E, 0x05, 0xD3, 0x52, 0x3E,
	0xE0, 0xD3, 0x52, 0xC9, 0x3E, 0x05, 0xD3, 0x52, 0x3E, 0xE0,
	0xD3, 0x52, 0xC9, 0x3E, 0x05, 0xD3, 0x52, 0x3E, 0x60, 0xD3,
	0x52, 0xC9, 0x06, 0x1C, 0x21, 0xB3, 0x01, 0x0E, 0x52, 0xED,
	0xA3, 0xC2, 0x03, 0x02, 0x21, 0x26, 0x02, 0x22, 0x40, 0x00,
	0x3A, 0x03, 0x00, 0xE6, 0x01, 0xC0, 0x3E, 0x0B, 0xED, 0x79,
	0x3E, 0x76, 0xED, 0x79, 0xC9, 0x21, 0xB5, 0x0A, 0x36, 0x84,
	0xCD, 0xFC, 0x01, 0xC9, 0xF5, 0xC5, 0xD5, 0xE5, 0x2A, 0x95,
	0x0A, 0x0E, 0x53, 0x11, 0x62, 0x02, 0x43, 0x14, 0xED, 0xA2,
	0x3A, 0xB2, 0x01, 0x5F, 0xDB, 0x52, 0xE6, 0x01, 0x20, 0x06,
	0x1D, 0x20, 0xF7, 0xC3, 0x10, 0x03, 0x3E, 0x01, 0xD3, 0x52,
	0xDB, 0x52, 0x5F, 0xE6, 0xA0, 0x20, 0x0A, 0xED, 0xA2, 0x20,
	0xE1, 0x15, 0x20, 0xDE, 0xC3, 0x0E, 0x03, 0xED, 0xA2, 0x7B,
	0xE6, 0x60, 0xC2, 0x14, 0x03, 0x3E, 0x30, 0xD3, 0x52, 0x3E,
	0x01, 0xD3, 0x52, 0xAF, 0xD3, 0x52, 0xED, 0x5B, 0x95, 0x0A,
	0x2B, 0x37, 0xED, 0x52, 0xDA, 0x12, 0x03, 0x22, 0x97, 0x0A,
	0x62, 0x6B, 0x3A, 0x99, 0x0A, 0xBE, 0x20, 0x51, 0x3E, 0x01,
	0x32, 0x9D, 0x0A, 0x23, 0x23, 0x3E, 0x84, 0xBE, 0x20, 0x2C,
	0x36, 0x85, 0x2B, 0x46, 0x3A, 0x99, 0x0A, 0x77, 0x2B, 0x70,
	0x11, 0x03, 0x00, 0xCD, 0x88, 0x03, 0x3E, 0x10, 0xD3, 0x52,
	0x3E, 0x38, 0xD3, 0x52, 0xCD, 0xD8, 0x01, 0x2A, 0x95, 0x0A,
	0x0E, 0x53, 0x11, 0x62, 0x02, 0x43, 0x14, 0x3A, 0xB1, 0x01,
	0x5F, 0xC3, 0x3A, 0x02, 0x3E, 0x81, 0xBE, 0xC2, 0xE2, 0x02,
	0x36, 0x82, 0x2B, 0x46, 0x3A, 0x99, 0x0A, 0x77, 0x2B, 0x70,
	0x11, 0x03, 0x00, 0xCD, 0x88, 0x03, 0xC3, 0xFD, 0x02, 0x23,
	0x23, 0x7E, 0xFE, 0x84, 0xC2, 0xE2, 0x02, 0xCD, 0x3C, 0x03,
	0x18, 0x14, 0x3E, 0x80, 0xA6, 0xC2, 0xDD, 0x02, 0xDD, 0xE5,
	0xDD, 0x21, 0xAE, 0x0A, 0xCD, 0x5C, 0x06, 0xCD, 0x8F, 0x07,
	0xDD, 0xE1, 0xE1, 0xD1, 0xC1, 0xF1, 0xFB, 0xED, 0x4D, 0xDD,
	0xE5, 0xDD, 0x21, 0x9E, 0x0A, 0xCD, 0x5C, 0x06, 0xDD, 0xE1,
	0xCD, 0x3C, 0x03, 0xC3, 0xF6, 0x02, 0x18, 0xED, 0x18, 0xEB,
	0x18, 0xE9, 0xE6, 0x40, 0x28, 0x02, 0x18, 0xE3, 0x18, 0xE1,
	0xAF, 0x32, 0xB2, 0x0A, 0xCD, 0xCF, 0x01, 0xC9, 0xC5, 0x21,
	0x04, 0x00, 0x39, 0x7E, 0x23, 0x66, 0x6F, 0xCD, 0x32, 0x03,
	0xC1, 0xC9, 0x3E, 0x01, 0x32, 0xB2, 0x0A, 0x22, 0x95, 0x0A,
	0x36, 0x00, 0x3A, 0xB2, 0x0A, 0xB7, 0xC8, 0x3E, 0x0E, 0xD3,
	0x52, 0x3E, 0xC1, 0xD3, 0x52, 0x3E, 0x0A, 0xD3, 0x52, 0x3E,
	0xE0, 0xD3, 0x52, 0x3E, 0x06, 0xD3, 0x52, 0x3A, 0x99, 0x0A,
	0xD3, 0x52, 0x3E, 0x10, 0xD3, 0x52, 0x3E, 0x38, 0xD3, 0x52,
	0x3E, 0x30, 0xD3, 0x52, 0xDB, 0x52, 0xE6, 0x01, 0x28, 0x04,
	0xDB, 0x53, 0x18, 0xF2, 0x3E, 0x0E, 0xD3, 0x52, 0x3E, 0x21,
	0xD3, 0x52, 0x3E, 0x01, 0xD3, 0x52, 0x3E, 0x09, 0xD3, 0x52,
	0x3E, 0x20, 0xD3, 0x52, 0xCD, 0xD8, 0x01, 0xC9, 0x0E, 0x53,
	0xCD, 0xCF, 0x01, 0x18, 0x17, 0x0E, 0x53, 0xCD, 0xCF, 0x01,
	0xCD, 0xE1, 0x01, 0x3A, 0xAD, 0x01, 0x3D, 0x20, 0xFD, 0xCD,
	0xF3, 0x01, 0x3A, 0xAD, 0x01, 0x3D, 0x20, 0xFD, 0xCD, 0xE1,
	0x01, 0x3A, 0xAE, 0x01, 0x3D, 0x20, 0xFD, 0x3E, 0x05, 0xD3,
	0x52, 0x3E, 0xE9, 0xD3, 0x52, 0x3E, 0x80, 0xD3, 0x52, 0x3A,
	0xAF, 0x01, 0x3D, 0x20, 0xFD, 0xED, 0xA3, 0x1B, 0x3E, 0xC0,
	0xD3, 0x52, 0xDB, 0x52, 0xE6, 0x04, 0x28, 0xFA, 0xED, 0xA3,
	0x1B, 0x7A, 0xB3, 0x20, 0xF3, 0xDB, 0x52, 0xE6, 0x04, 0x28,
	0xFA, 0x3A, 0xB1, 0x01, 0x47, 0xDB, 0x52, 0xE6, 0x04, 0x28,
	0x03, 0x05, 0x20, 0xF7, 0xDB, 0x52, 0xE6, 0x04, 0x28, 0xFA,
	0xCD, 0xEA, 0x01, 0x3A, 0xB0, 0x01, 0x3D, 0x20, 0xFD, 0xCD,
	0xF3, 0x01, 0xC9, 0xE5, 0xD5, 0x23, 0x23, 0x7E, 0xE6, 0x80,
	0xC2, 0x90, 0x04, 0x2B, 0x3A, 0x99, 0x0A, 0x77, 0x2B, 0x46,
	0x21, 0xB4, 0x0A, 0x77, 0x2B, 0x70, 0x11, 0x03, 0x00, 0xF3,
	0x3E, 0x0A, 0xD3, 0x52, 0xDB, 0x52, 0xE6, 0x80, 0xCA, 0x28,
	0x04, 0xD1, 0xE1, 0x3E, 0x01, 0x37, 0xFB, 0xC9, 0xCD, 0x8F,
	0x03, 0x3A, 0xB3, 0x0A, 0xFE, 0xFF, 0xCA, 0x7E, 0x04, 0xCD,
	0xD8, 0x01, 0x3A, 0xB1, 0x01, 0x47, 0xDB, 0x52, 0xE6, 0x01,
	0x20, 0x06, 0x05, 0x20, 0xF7, 0xC3, 0xAC, 0x04, 0xDB, 0x53,
	0x47, 0x3A, 0x99, 0x0A, 0xB8, 0xC2, 0xAC, 0x04, 0x3A, 0xB1,
	0x01, 0x47, 0xDB, 0x52, 0xE6, 0x01, 0x20, 0x06, 0x05, 0x20,
	0xF7, 0xC3, 0xAC, 0x04, 0xDB, 0x53, 0x3A, 0xB1, 0x01, 0x47,
	0xDB, 0x52, 0xE6, 0x01, 0x20, 0x06, 0x05, 0x20, 0xF7, 0xC3,
	0xAC, 0x04, 0xDB, 0x53, 0xFE, 0x85, 0xC2, 0xAC, 0x04, 0x3A,
	0xB2, 0x01, 0x18, 0x04, 0x3A, 0xB2, 0x01, 0x87, 0x3D, 0x20,
	0xFD, 0xD1, 0xE1, 0xCD, 0x88, 0x03, 0xCD, 0x3C, 0x03, 0xB7,
	0xFB, 0xC9, 0xD1, 0xE1, 0xF3, 0x3E, 0x0A, 0xD3, 0x52, 0xDB,
	0x52, 0xE6, 0x80, 0xCA, 0xA3, 0x04, 0x3E, 0x01, 0x37, 0xFB,
	0xC9, 0xCD, 0x8F, 0x03, 0xCD, 0x3C, 0x03, 0xB7, 0xFB, 0xC9,
	0xD1, 0xE1, 0x3E, 0x02, 0x37, 0xFB, 0xC9, 0xF3, 0x3E, 0x0E,
	0xD3, 0x52, 0x3E, 0x21, 0xD3, 0x52, 0xFB, 0xC9, 0x21, 0x04,
	0x00, 0x39, 0x5E, 0x23, 0x56, 0x21, 0x02, 0x00, 0x39, 0x7E,
	0x23, 0x66, 0x6F, 0xDD, 0xE5, 0x22, 0xC0, 0x0A, 0xED, 0x53,
	0xC2, 0x0A, 0xDD, 0x21, 0xAA, 0x0A, 0xCD, 0x5C, 0x06, 0x3A,
	0xB8, 0x0A, 0x32, 0xB9, 0x0A, 0x3A, 0xB7, 0x0A, 0x87, 0x32,
	0xB7, 0x0A, 0xCD, 0x6F, 0x06, 0xFE, 0x03, 0x38, 0x10, 0x3A,
	0xB8, 0x0A, 0x87, 0x3C, 0xE6, 0x0F, 0x32, 0xB8, 0x0A, 0xAF,
	0x32, 0xB7, 0x0A, 0x18, 0x17, 0x3A, 0xB6, 0x0A, 0xCD, 0x6F,
	0x06, 0xFE, 0x03, 0x30, 0x0D, 0x3A, 0xB8, 0x0A, 0xCB, 0x3F,
	0x32, 0xB8, 0x0A, 0x3E, 0xFF, 0x32, 0xB6, 0x0A, 0x3A, 0xB8,
	0x0A, 0x32, 0xB9, 0x0A, 0x3A, 0xB6, 0x0A, 0x87, 0x32, 0xB6,
	0x0A, 0x3E, 0x20, 0x32, 0xBA, 0x0A, 0x32, 0xBB, 0x0A, 0x06,
	0xFF, 0xDB, 0x52, 0xE6, 0x10, 0x20, 0x03, 0x05, 0x20, 0xF7,
	0xCD, 0xB3, 0x04, 0x06, 0x28, 0xDB, 0x52, 0xE6, 0x10, 0x28,
	0x03, 0x05, 0x20, 0xF7, 0x3E, 0x0A, 0xD3, 0x52, 0xDB, 0x52,
	0xE6, 0x80, 0xC2, 0x2D, 0x05, 0xDB, 0x52, 0xE6, 0x10, 0x28,
	0xD6, 0xED, 0x5F, 0x47, 0x3A, 0xB9, 0x0A, 0xA0, 0xE6, 0x0F,
	0x28, 0x20, 0x47, 0x0E, 0x0A, 0x3E, 0x0A, 0xD3, 0x52, 0xDB,
	0x52, 0xE6, 0x80, 0xCA, 0x76, 0x05, 0xCD, 0xB3, 0x04, 0xC3,
	0x9B, 0x05, 0xDB, 0x52, 0xE6, 0x10, 0xCA, 0x9B, 0x05, 0x0D,
	0x20, 0xE5, 0x10, 0xE1, 0x2A, 0xC0, 0x0A, 0xED, 0x5B, 0xC2,
	0x0A, 0xCD, 0xFB, 0x03, 0x30, 0x07, 0x3D, 0xCA, 0x9B, 0x05,
	0xC3, 0xC4, 0x05, 0xDD, 0xE1, 0x21, 0x00, 0x00, 0xC9, 0xDD,
	0x21, 0xA2, 0x0A, 0xCD, 0x5C, 0x06, 0x3A, 0xBB, 0x0A, 0x3D,
	0x32, 0xBB, 0x0A, 0x28, 0x13, 0x3A, 0xB9, 0x0A, 0xF6, 0x01,
	0x32, 0xB9, 0x0A, 0x3A, 0xB6, 0x0A, 0xF6, 0x01, 0x32, 0xB6,
	0x0A, 0xC3, 0x2D, 0x05, 0xDD, 0xE1, 0x21, 0x01, 0x00, 0xC9,
	0xDD, 0x21, 0xA6, 0x0A, 0xCD, 0x5C, 0x06, 0x3A, 0xB7, 0x0A,
	0xF6, 0x01, 0x32, 0xB7, 0x0A, 0x3A, 0xB9, 0x0A, 0x87, 0xF6,
	0x01, 0x32, 0xB9, 0x0A, 0x3A, 0xBA, 0x0A, 0x3D, 0x32, 0xBA,
	0x0A, 0xC2, 0x2D, 0x05, 0xDD, 0xE1, 0x21, 0x02, 0x00, 0xC9,
	0xDD, 0xE5, 0x21, 0x00, 0x00, 0x39, 0x11, 0x04, 0x00, 0x19,
	0x7E, 0x32, 0x99, 0x0A, 0xE6, 0x80, 0x32, 0xBC, 0x0A, 0x3A,
	0xBC, 0x0A, 0xB7, 0x28, 0x06, 0xDD, 0x21, 0x58, 0x02, 0x18,
	0x04, 0xDD, 0x21, 0x96, 0x00, 0x3A, 0x99, 0x0A, 0xB7, 0x28,
	0x31, 0x3C, 0x28, 0x2E, 0x3D, 0x21, 0xBD, 0x0A, 0x77, 0x23,
	0x77, 0x23, 0x36, 0x81, 0xAF, 0x32, 0x9D, 0x0A, 0xDD, 0x2B,
	0xDD, 0xE5, 0xE1, 0x7C, 0xB5, 0x28, 0x2A, 0x21, 0xBD, 0x0A,
	0x11, 0x03, 0x00, 0xCD, 0xCD, 0x04, 0x11, 0xE8, 0x03, 0x1B,
	0x7B, 0xB2, 0x20, 0xFB, 0x3A, 0x9D, 0x0A, 0xB7, 0x28, 0xE0,
	0x3A, 0x99, 0x0A, 0x47, 0x3E, 0x07, 0x80, 0xE6, 0x7F, 0x47,
	0x3A, 0xBC, 0x0A, 0xB0, 0x32, 0x99, 0x0A, 0x18, 0xA6, 0xDD,
	0xE1, 0xC9, 0xB7, 0xDD, 0x34, 0x00, 0xC0, 0xDD, 0x34, 0x01,
	0xC0, 0xDD, 0x34, 0x02, 0xC0, 0xDD, 0x34, 0x03, 0xC0, 0x37,
	0xC9, 0x06, 0x08, 0x0E, 0x00, 0x1F, 0x30, 0x01, 0x0C, 0x10,
	0xFA, 0x79, 0xC9, 0x21, 0x02, 0x00, 0x39, 0x5E, 0x23, 0x56,
	0x23, 0x4E, 0x23, 0x46, 0x23, 0x7E, 0x23, 0x66, 0x69, 0x4F,
	0x78, 0x44, 0x67, 0xED, 0xB0, 0xC9, 0x21, 0x02, 0x00, 0x39,
	0x7E, 0x23, 0x66, 0x6F, 0x3E, 0x11, 0xED, 0x39, 0x30, 0x7D,
	0xED, 0x39, 0x28, 0x7C, 0xED, 0x39, 0x29, 0x3E, 0x00, 0xED,
	0x39, 0x2A, 0x3E, 0x40, 0xED, 0x39, 0x2B, 0x3E, 0x00, 0xED,
	0x39, 0x2C, 0x21, 0x80, 0x02, 0x7D, 0xED, 0x39, 0x2E, 0x7C,
	0xED, 0x39, 0x2F, 0x3E, 0x91, 0xED, 0x39, 0x30, 0xD3, 0x44,
	0x3A, 0x94, 0x0A, 0xD3, 0x42, 0xC9, 0x21, 0x02, 0x00, 0x39,
	0x7E, 0x23, 0x66, 0x6F, 0x3E, 0x21, 0xED, 0x39, 0x30, 0x3E,
	0x40, 0xED, 0x39, 0x20, 0x3E, 0x00, 0xED, 0x39, 0x21, 0xED,
	0x39, 0x22, 0x7D, 0xED, 0x39, 0x23, 0x7C, 0xED, 0x39, 0x24,
	0x3E, 0x00, 0xED, 0x39, 0x25, 0x21, 0x80, 0x02, 0x7D, 0xED,
	0x39, 0x26, 0x7C, 0xED, 0x39, 0x27, 0x3E, 0x61, 0xED, 0x39,
	0x30, 0xD3, 0x43, 0x3A, 0x94, 0x0A, 0xD3, 0x42, 0xC9, 0xED,
	0x38, 0x2E, 0x5F, 0xED, 0x38, 0x2F, 0x57, 0xED, 0x38, 0x2E,
	0x6F, 0xED, 0x38, 0x2F, 0x67, 0xB7, 0xED, 0x52, 0x20, 0xEB,
	0x21, 0x80, 0x02, 0xB7, 0xED, 0x52, 0xC9, 0xED, 0x38, 0x26,
	0x5F, 0xED, 0x38, 0x27, 0x57, 0xED, 0x38, 0x26, 0x6F, 0xED,
	0x38, 0x27, 0x67, 0xB7, 0xED, 0x52, 0x20, 0xEB, 0x21, 0x80,
	0x02, 0xB7, 0xED, 0x52, 0xC9, 0xCD, 0x69, 0x0A, 0xDD, 0x6E,
	0x06, 0xDD, 0x66, 0x07, 0x7E, 0x23, 0x6E, 0x67, 0xC3, 0x75,
	0x0A, 0xCD, 0x69, 0x0A, 0x21, 0x00, 0x00, 0x22, 0xCC, 0x0A,
	0x22, 0xC5, 0x0A, 0x22, 0xC7, 0x0A, 0x21, 0x8E, 0x0F, 0x22,
	0xCE, 0x0A, 0xED, 0x5B, 0xCE, 0x0A, 0x2A, 0x91, 0x0A, 0xB7,
	0xED, 0x52, 0x11, 0x00, 0xFF, 0x19, 0x22, 0xCA, 0x0A, 0xCB,
	0x7C, 0x28, 0x06, 0x21, 0x00, 0x7D, 0x22, 0xCA, 0x0A, 0x2A,
	0xCE, 0x0A, 0xE5, 0xCD, 0x24, 0x03, 0xC3, 0x75, 0x0A, 0xCD,
	0x69, 0x0A, 0xE5, 0x2A, 0x95, 0x0A, 0x23, 0x23, 0x23, 0xE5,
	0xCD, 0x45, 0x07, 0xC1, 0x7C, 0xE6, 0x03, 0x67, 0xDD, 0x75,
	0xFE, 0xDD, 0x74, 0xFF, 0xED, 0x5B, 0x97, 0x0A, 0x23, 0x23,
	0x23, 0xB7, 0xED, 0x52, 0x20, 0x0C, 0x11, 0x05, 0x00, 0x2A,
	0x97, 0x0A, 0xCD, 0x5A, 0x0A, 0xF2, 0xCA, 0x07, 0x2A, 0x95,
	0x0A, 0xE5, 0xCD, 0x24, 0x03, 0xC3, 0x75, 0x0A, 0xED, 0x5B,
	0x97, 0x0A, 0x2A, 0xC7, 0x0A, 0x19, 0x22, 0xC7, 0x0A, 0x2A,
	0xCC, 0x0A, 0x19, 0x22, 0xCC, 0x0A, 0xED, 0x5B, 0xCA, 0x0A,
	0x21, 0x9E, 0xFD, 0x19, 0xED, 0x5B, 0xCC, 0x0A, 0xCD, 0x5A,
	0x0A, 0xF2, 0xF4, 0x07, 0x21, 0x00, 0x00, 0x22, 0xCC, 0x0A,
	0x3E, 0x01, 0x32, 0xC4, 0x0A, 0xCD, 0x04, 0x08, 0x21, 0x00,
	0x00, 0x39, 0xF9, 0xC3, 0x75, 0x0A, 0xCD, 0x69, 0x0A, 0x3A,
	0xC4, 0x0A, 0xB7, 0xCA, 0x75, 0x0A, 0xED, 0x5B, 0xC5, 0x0A,
	0x2A, 0xCC, 0x0A, 0xCD, 0x5A, 0x0A, 0xF2, 0x2D, 0x08, 0xED,
	0x5B, 0xCC, 0x0A, 0x21, 0x62, 0x02, 0x19, 0xED, 0x5B, 0xC5,
	0x0A, 0xCD, 0x5A, 0x0A, 0xFA, 0x4D, 0x08, 0xED, 0x5B, 0xC5,
	0x0A, 0x2A, 0xCC, 0x0A, 0xB7, 0xED, 0x52, 0x20, 0x07, 0x2A,
	0xC7, 0x0A, 0x7D, 0xB4, 0x28, 0x0D, 0xED, 0x5B, 0xCC, 0x0A,
	0x2A, 0xC5, 0x0A, 0xCD, 0x5A, 0x0A, 0xF2, 0x60, 0x08, 0xED,
	0x5B, 0xCE, 0x0A, 0x2A, 0xCC, 0x0A, 0x19, 0xE5, 0xCD, 0x24,
	0x03, 0xAF, 0x32, 0xC4, 0x0A, 0xC3, 0x75, 0x0A, 0xCD, 0x1C,
	0x03, 0x21, 0x00, 0x00, 0x39, 0xF9, 0xC3, 0x75, 0x0A, 0xCD,
	0x69, 0x0A, 0x3A, 0xC9, 0x0A, 0xB7, 0x28, 0x16, 0xCD, 0x0D,
	0x07, 0xED, 0x5B, 0xD0, 0x0A, 0x13, 0x13, 0x13, 0xCD, 0x5A,
	0x0A, 0xF2, 0x8A, 0x08, 0x21, 0x01, 0x00, 0xC3, 0x75, 0x0A,
	0x21, 0x00, 0x00, 0xC3, 0x75, 0x0A, 0xCD, 0x7D, 0x0A, 0xFC,
	0xFF, 0xCD, 0x6B, 0x08, 0x7D, 0xB4, 0xC2, 0x75, 0x0A, 0xED,
	0x5B, 0xC7, 0x0A, 0x21, 0x00, 0x00, 0xCD, 0x5A, 0x0A, 0xF2,
	0x75, 0x0A, 0xED, 0x5B, 0xCE, 0x0A, 0x2A, 0xC5, 0x0A, 0x19,
	0xDD, 0x75, 0xFE, 0xDD, 0x74, 0xFF, 0x23, 0x23, 0x23, 0xE5,
	0xCD, 0x45, 0x07, 0xC1, 0x7C, 0xE6, 0x03, 0x67, 0x23, 0x23,
	0x23, 0xDD, 0x75, 0xFC, 0xDD, 0x74, 0xFD, 0xE5, 0xDD, 0x6E,
	0xFE, 0xDD, 0x66, 0xFF, 0xE5, 0x21, 0xD3, 0x0A, 0xE5, 0xCD,
	0x7B, 0x06, 0xC1, 0xC1, 0xDD, 0x6E, 0xFC, 0xDD, 0x66, 0xFD,
	0x22, 0xD0, 0x0A, 0x21, 0xD2, 0x0A, 0x36, 0x04, 0x21, 0xD0,
	0x0A, 0xE3, 0xCD, 0x92, 0x06, 0xC1, 0x3E, 0x01, 0x32, 0xC9,
	0x0A, 0xF3, 0xDD, 0x5E, 0xFC, 0xDD, 0x56, 0xFD, 0x2A, 0xC7,
	0x0A, 0xB7, 0xED, 0x52, 0x22, 0xC7, 0x0A, 0xCB, 0x7C, 0x28,
	0x11, 0x21, 0x00, 0x00, 0x22, 0xC7, 0x0A, 0x22, 0xCC, 0x0A,
	0x22, 0xC5, 0x0A, 0x32, 0xC4, 0x0A, 0x18, 0x25, 0xDD, 0x5E,
	0xFC, 0xDD, 0x56, 0xFD, 0x2A, 0xC5, 0x0A, 0x19, 0x22, 0xC5,
	0x0A, 0xED, 0x5B, 0xCA, 0x0A, 0x21, 0x9E, 0xFD, 0x19, 0xED,
	0x5B, 0xC5, 0x0A, 0xCD, 0x5A, 0x0A, 0xF2, 0x43, 0x09, 0x21,
	0x00, 0x00, 0x22, 0xC5, 0x0A, 0xCD, 0x04, 0x08, 0x21, 0x00,
	0x00, 0x39, 0xF9, 0xFB, 0xC3, 0x75, 0x0A, 0xCD, 0x69, 0x0A,
	0x21, 0x30, 0x0D, 0x7E, 0xB7, 0x28, 0x10, 0xCD, 0x29, 0x07,
	0xED, 0x5B, 0x2E, 0x0D, 0x13, 0x13, 0x13, 0xCD, 0x5A, 0x0A,
	0xF2, 0x74, 0x09, 0x3A, 0x8D, 0x0F, 0xC6, 0x01, 0x32, 0x8D,
	0x0F, 0xC3, 0x75, 0x0A, 0x21, 0x30, 0x0D, 0x7E, 0xFE, 0x01,
	0x28, 0x19, 0xFE, 0x03, 0xCA, 0x06, 0x0A, 0xFE, 0x05, 0xCA,
	0x14, 0x0A, 0x21, 0x30, 0x0D, 0x36, 0x00, 0x21, 0x2E, 0x0D,
	0xE5, 0xCD, 0xCE, 0x06, 0xC3, 0x75, 0x0A, 0x3A, 0x8C, 0x0F,
	0xB7, 0x20, 0x48, 0x21, 0x32, 0x0D, 0x7E, 0x32, 0x94, 0x0A,
	0xCD, 0x55, 0x07, 0x21, 0x31, 0x0D, 0x7E, 0xE6, 0x7F, 0xB7,
	0x20, 0x28, 0x3A, 0x8D, 0x0F, 0xE6, 0x7F, 0x32, 0x8D, 0x0F,
	0xB7, 0x20, 0x05, 0xC6, 0x01, 0x32, 0x8D, 0x0F, 0x21, 0x31,
	0x0D, 0x7E, 0x6F, 0x17, 0x9F, 0x67, 0xCB, 0x7D, 0x3A, 0x8D,
	0x0F, 0x28, 0x05, 0xC6, 0x80, 0x32, 0x8D, 0x0F, 0x21, 0x31,
	0x0D, 0x77, 0x21, 0x31, 0x0D, 0x7E, 0x6F, 0x17, 0x9F, 0x67,
	0xE5, 0xCD, 0xEC, 0x05, 0xC1, 0x21, 0xD2, 0x0A, 0x36, 0x02,
	0x21, 0x02, 0x00, 0x22, 0xD0, 0x0A, 0x3A, 0x99, 0x0A, 0x21,
	0xD3, 0x0A, 0x77, 0x3A, 0x93, 0x0A, 0x21, 0xD4, 0x0A, 0x77,
	0x21, 0xD0, 0x0A, 0xE5, 0xCD, 0x92, 0x06, 0xC1, 0x18, 0x80,
	0x2A, 0x2E, 0x0D, 0xE5, 0x21, 0x31, 0x0D, 0xE5, 0xCD, 0xBE,
	0x04, 0xC1, 0x18, 0xEF, 0x21, 0xD2, 0x0A, 0x36, 0x06, 0x21,
	0x03, 0x00, 0x22, 0xD0, 0x0A, 0x3A, 0x99, 0x0A, 0x21, 0xD3,
	0x0A, 0x77, 0x3A, 0x93, 0x0A, 0x21, 0xD4, 0x0A, 0x77, 0x21,
	0xD5, 0x0A, 0x36, 0x05, 0x21, 0xD0, 0x0A, 0xE5, 0xCD, 0x92,
	0x06, 0x18, 0xC8, 0xCD, 0x69, 0x0A, 0x21, 0x30, 0x0D, 0x36,
	0x00, 0x21, 0x2E, 0x0D, 0xE5, 0xCD, 0xCE, 0x06, 0x21, 0xD0,
	0x0A, 0xE3, 0xCD, 0x92, 0x06, 0xC1, 0xCD, 0x4F, 0x09, 0xCD,
	0x90, 0x08, 0x18, 0xF8, 0x7C, 0xAA, 0xFA, 0x62, 0x0A, 0xED,
	0x52, 0xC9, 0x7C, 0xE6, 0x80, 0xED, 0x52, 0x3C, 0xC9, 0xE1,
	0xFD, 0xE5, 0xDD, 0xE5, 0xDD, 0x21, 0x00, 0x00, 0xDD, 0x39,
	0xE9, 0xDD, 0xF9, 0xDD, 0xE1, 0xFD, 0xE1, 0xC9, 0xE9, 0xE1,
	0xFD, 0xE5, 0xDD, 0xE5, 0xDD, 0x21, 0x00, 0x00, 0xDD, 0x39,
	0x5E, 0x23, 0x56, 0x23, 0xEB, 0x39, 0xF9, 0xEB, 0xE9, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#else
	0x3A, 0x03, 0x00, 0x32, 0xDE, 0x09, 0x21, 0xD8, 0x0E, 0x3E,
	0x55, 0x77, 0xBE, 0x20, 0x09, 0x3E, 0xAA, 0x77, 0xBE, 0x20,
	0x03, 0x23, 0x18, 0xF1, 0x22, 0xDC, 0x09, 0xF9, 0x11, 0xE0,
	0x09, 0x21, 0xD8, 0x0E, 0xB7, 0xED, 0x52, 0x4D, 0x44, 0x0B,
	0x6B, 0x62, 0x13, 0x36, 0x00, 0xED, 0xB0, 0x3E, 0x10, 0xED,
	0x39, 0x33, 0x3E, 0x00, 0xED, 0x39, 0x32, 0xED, 0x39, 0x36,
	0x3E, 0x0C, 0xED, 0x39, 0x31, 0x3E, 0xC3, 0x21, 0xE5, 0x01,
	0x32, 0x38, 0x00, 0x22, 0x39, 0x00, 0xED, 0x56, 0xCD, 0xDC,
	0x01, 0xFB, 0xCD, 0x00, 0x09, 0x18, 0xA9, 0x43, 0x6F, 0x70,
	0x79, 0x72, 0x69, 0x67, 0x68, 0x74, 0x20, 0x28, 0x43, 0x29,
	0x20, 0x31, 0x39, 0x38, 0x37, 0x20, 0x2D, 0x20, 0x54, 0x61,
	0x6E, 0x67, 0x65, 0x6E, 0x74, 0x20, 0x54, 0x65, 0x63, 0x68,
	0x6E, 0x6F, 0x6C, 0x6F, 0x67, 0x69, 0x65, 0x73, 0x20, 0x20,
	0x20, 0x41, 0x6C, 0x6C, 0x20, 0x72, 0x69, 0x67, 0x68, 0x74,
	0x73, 0x20, 0x72, 0x65, 0x73, 0x65, 0x72, 0x76, 0x65, 0x64,
	0x2E, 0x20, 0x20, 0x04, 0x04, 0x16, 0x28, 0xFF, 0x3C, 0x04,
	0x60, 0x0A, 0xE0, 0x06, 0x00, 0x07, 0x7E, 0x02, 0x40, 0x0B,
	0xF6, 0x0C, 0x06, 0x0D, 0x00, 0x0E, 0xC1, 0x0F, 0x00, 0x05,
	0x60, 0x03, 0xC0, 0x01, 0x00, 0x09, 0x08, 0x06, 0x1C, 0x21,
	0x9F, 0x01, 0x0E, 0x52, 0xED, 0xA3, 0xC2, 0xC2, 0x01, 0x21,
	0xE5, 0x01, 0x22, 0x40, 0x00, 0x3A, 0x03, 0x00, 0xE6, 0x01,
	0xC0, 0x3E, 0x0B, 0xED, 0x79, 0x3E, 0x76, 0xED, 0x79, 0xC9,
	0x21, 0x00, 0x0A, 0x36, 0x84, 0xCD, 0xBB, 0x01, 0xC9, 0xF5,
	0xC5, 0xD5, 0xE5, 0x2A, 0xE0, 0x09, 0x0E, 0x53, 0x11, 0x62,
	0x02, 0x43, 0x14, 0xED, 0xA2, 0x3A, 0x9E, 0x01, 0x5F, 0xDB,
	0x52, 0xE6, 0x01, 0x20, 0x06, 0x1D, 0x20, 0xF7, 0xC3, 0xD4,
	0x02, 0x3E, 0x01, 0xD3, 0x52, 0xDB, 0x52, 0x5F, 0xE6, 0xA0,
	0x20, 0x0A, 0xED, 0xA2, 0x20, 0xE1, 0x15, 0x20, 0xDE, 0xC3,
	0xD2, 0x02, 0xED, 0xA2, 0x7B, 0xE6, 0x60, 0xC2, 0xD8, 0x02,
	0x3E, 0x30, 0xD3, 0x52, 0x3E, 0x01, 0xD3, 0x52, 0xAF, 0xD3,
	0x52, 0xED, 0x5B, 0xE0, 0x09, 0x2B, 0x37, 0xED, 0x52, 0xDA,
	0xD6, 0x02, 0x22, 0xE2, 0x09, 0x62, 0x6B, 0x3A, 0xE4, 0x09,
	0xBE, 0x20, 0x56, 0x3E, 0x01, 0x32, 0xE8, 0x09, 0x23, 0x23,
	0x3E, 0x84, 0xBE, 0x20, 0x31, 0x36, 0x85, 0x2B, 0x46, 0x3A,
	0xE4, 0x09, 0x77, 0x2B, 0x70, 0x11, 0x03, 0x00, 0xCD, 0x56,
	0x03, 0x3E, 0x10, 0xD3, 0x52, 0x3E, 0x38, 0xD3, 0x52, 0x3E,
	0x03, 0xD3, 0x52, 0x3E, 0xD5, 0xD3, 0x52, 0x2A, 0xE0, 0x09,
	0x0E, 0x53, 0x11, 0x62, 0x02, 0x43, 0x14, 0x3A, 0x9D, 0x01,
	0x5F, 0xC3, 0xF9, 0x01, 0x3E, 0x81, 0xBE, 0xC2, 0xA6, 0x02,
	0x36, 0x82, 0x2B, 0x46, 0x3A, 0xE4, 0x09, 0x77, 0x2B, 0x70,
	0x11, 0x03, 0x00, 0xCD, 0x56, 0x03, 0xC3, 0xC1, 0x02, 0x23,
	0x23, 0x7E, 0xFE, 0x84, 0xC2, 0xA6, 0x02, 0xCD, 0x05, 0x03,
	0x18, 0x14, 0x3E, 0x80, 0xA6, 0xC2, 0xA1, 0x02, 0xDD, 0xE5,
	0xDD, 0x21, 0xF9, 0x09, 0xCD, 0x13, 0x06, 0xCD, 0x40, 0x07,
	0xDD, 0xE1, 0xE1, 0xD1, 0xC1, 0xF1, 0xFB, 0xED, 0x4D, 0xDD,
	0xE5, 0xDD, 0x21, 0xE9, 0x09, 0xCD, 0x13, 0x06, 0xDD, 0xE1,
	0xCD, 0x05, 0x03, 0xC3, 0xBA, 0x02, 0x18, 0xED, 0x18, 0xEB,
	0x18, 0xE9, 0xE6, 0x40, 0x28, 0x02, 0x18, 0xE3, 0x18, 0xE1,
	0xAF, 0x32, 0xFD, 0x09, 0x3E, 0x03, 0xD3, 0x52, 0x3E, 0xC0,
	0xD3, 0x52, 0xC9, 0xC5, 0x21, 0x04, 0x00, 0x39, 0x7E, 0x23,
	0x66, 0x6F, 0xCD, 0xFB, 0x02, 0xC1, 0xC9, 0x3E, 0x01, 0x32,
	0xFD, 0x09, 0x22, 0xE0, 0x09, 0x36, 0x00, 0x3A, 0xFD, 0x09,
	0xB7, 0xC8, 0x3E, 0x0E, 0xD3, 0x52, 0x3E, 0xC1, 0xD3, 0x52,
	0x3E, 0x0A, 0xD3, 0x52, 0x3E, 0xE0, 0xD3, 0x52, 0x3E, 0x06,
	0xD3, 0x52, 0x3A, 0xE4, 0x09, 0xD3, 0x52, 0x3E, 0x10, 0xD3,
	0x52, 0x3E, 0x38, 0xD3, 0x52, 0x3E, 0x30, 0xD3, 0x52, 0xDB,
	0x52, 0xE6, 0x01, 0x28, 0x04, 0xDB, 0x53, 0x18, 0xF2, 0x3E,
	0x0E, 0xD3, 0x52, 0x3E, 0x21, 0xD3, 0x52, 0x3E, 0x03, 0xD3,
	0x52, 0x3E, 0xD5, 0xD3, 0x52, 0x3E, 0x01, 0xD3, 0x52, 0x3E,
	0x09, 0xD3, 0x52, 0x3E, 0x20, 0xD3, 0x52, 0xC9, 0x0E, 0x53,
	0x3E, 0x03, 0xD3, 0x52, 0x3E, 0xC0, 0xD3, 0x52, 0x18, 0x20,
	0x0E, 0x53, 0x3E, 0x03, 0xD3, 0x52, 0x3E, 0xC0, 0xD3, 0x52,
	0x3E, 0x05, 0xD3, 0x52, 0x3E, 0xE0, 0xD3, 0x52, 0x3E, 0x05,
	0xD3, 0x52, 0x3E, 0x60, 0xD3, 0x52, 0x3A, 0x99, 0x01, 0x3D,
	0x20, 0xFD, 0x3E, 0x05, 0xD3, 0x52, 0x3E, 0xE0, 0xD3, 0x52,
	0x3A, 0x9A, 0x01, 0x3D, 0x20, 0xFD, 0x3E, 0x05, 0xD3, 0x52,
	0x3E, 0xE9, 0xD3, 0x52, 0x3E, 0x80, 0xD3, 0x52, 0x3A, 0x9B,
	0x01, 0x3D, 0x20, 0xFD, 0xED, 0xA3, 0x1B, 0x3E, 0xC0, 0xD3,
	0x52, 0xDB, 0x52, 0xE6, 0x04, 0x28, 0xFA, 0xED, 0xA3, 0x1B,
	0x7A, 0xB3, 0x20, 0xF3, 0xDB, 0x52, 0xE6, 0x04, 0x28, 0xFA,
	0x3A, 0x9D, 0x01, 0x47, 0xDB, 0x52, 0xE6, 0x04, 0x28, 0x03,
	0x05, 0x20, 0xF7, 0xDB, 0x52, 0xE6, 0x04, 0x28, 0xFA, 0x3E,
	0x05, 0xD3, 0x52, 0x3E, 0xE0, 0xD3, 0x52, 0x3A, 0x9C, 0x01,
	0x3D, 0x20, 0xFD, 0x3E, 0x05, 0xD3, 0x52, 0x3E, 0x60, 0xD3,
	0x52, 0xC9, 0xE5, 0xD5, 0x23, 0x23, 0x7E, 0xE6, 0x80, 0xC2,
	0x6C, 0x04, 0x2B, 0x3A, 0xE4, 0x09, 0x77, 0x2B, 0x46, 0x21,
	0xFF, 0x09, 0x77, 0x2B, 0x70, 0x11, 0x03, 0x00, 0xF3, 0x3E,
	0x0A, 0xD3, 0x52, 0xDB, 0x52, 0xE6, 0x00, 0xCA, 0x13, 0x04,
	0xD1, 0xE1, 0x3E, 0x01, 0x37, 0xFB, 0xC9, 0xCD, 0x62, 0x03,
	0x3A, 0xFE, 0x09, 0xFE, 0xFF, 0xCA, 0x5A, 0x04, 0x3E, 0x03,
	0xD3, 0x52, 0x3E, 0xC1, 0xD3, 0x52, 0x3A, 0x9D, 0x01, 0x47,
	0xDB, 0x52, 0xE6, 0x01, 0x20, 0x06, 0x05, 0x20, 0xF7, 0xC3,
	0x88, 0x04, 0xDB, 0x53, 0x47, 0x3A, 0xE4, 0x09, 0xB8, 0xC2,
	0x88, 0x04, 0xDB, 0x52, 0xE6, 0x01, 0x28, 0xFA, 0xDB, 0x53,
	0xDB, 0x52, 0xE6, 0x01, 0x28, 0xFA, 0xDB, 0x53, 0xFE, 0x85,
	0xC2, 0x88, 0x04, 0x3A, 0x9E, 0x01, 0x18, 0x04, 0x3A, 0x9E,
	0x01, 0x87, 0x3D, 0x20, 0xFD, 0xD1, 0xE1, 0xCD, 0x56, 0x03,
	0xCD, 0x05, 0x03, 0xB7, 0xFB, 0xC9, 0xD1, 0xE1, 0xF3, 0x3E,
	0x0A, 0xD3, 0x52, 0xDB, 0x52, 0xE6, 0xC0, 0xCA, 0x7F, 0x04,
	0x3E, 0x01, 0x37, 0xFB, 0xC9, 0xCD, 0x62, 0x03, 0xCD, 0x05,
	0x03, 0xB7, 0xFB, 0xC9, 0xD1, 0xE1, 0x3E, 0x02, 0x37, 0xFB,
	0xC9, 0x06, 0x08, 0x0E, 0x00, 0x1F, 0x30, 0x01, 0x0C, 0x10,
	0xFA, 0x79, 0xC9, 0x21, 0x04, 0x00, 0x39, 0x5E, 0x23, 0x56,
	0x21, 0x02, 0x00, 0x39, 0x7E, 0x23, 0x66, 0x6F, 0xDD, 0xE5,
	0x22, 0x0B, 0x0A, 0xED, 0x53, 0x0D, 0x0A, 0xDD, 0x21, 0xF5,
	0x09, 0xCD, 0x13, 0x06, 0x3A, 0x03, 0x0A, 0x32, 0x04, 0x0A,
	0x3A, 0x02, 0x0A, 0x87, 0x32, 0x02, 0x0A, 0xCD, 0x8F, 0x04,
	0xFE, 0x03, 0x38, 0x10, 0x3A, 0x03, 0x0A, 0x87, 0x3C, 0xE6,
	0x0F, 0x32, 0x03, 0x0A, 0xAF, 0x32, 0x02, 0x0A, 0x18, 0x17,
	0x3A, 0x01, 0x0A, 0xCD, 0x8F, 0x04, 0xFE, 0x03, 0x30, 0x0D,
	0x3A, 0x03, 0x0A, 0xCB, 0x3F, 0x32, 0x03, 0x0A, 0x3E, 0xFF,
	0x32, 0x01, 0x0A, 0x3A, 0x03, 0x0A, 0x32, 0x04, 0x0A, 0x3A,
	0x01, 0x0A, 0x87, 0x32, 0x01, 0x0A, 0x3E, 0x20, 0x32, 0x05,
	0x0A, 0x32, 0x06, 0x0A, 0x06, 0x28, 0xDB, 0x52, 0xE6, 0x10,
	0x28, 0xF8, 0x05, 0x20, 0xF7, 0xF3, 0x3E, 0x0E, 0xD3, 0x52,
	0x3E, 0x41, 0xD3, 0x52, 0xFB, 0xED, 0x5F, 0x47, 0x3A, 0x04,
	0x0A, 0xA0, 0xE6, 0x0F, 0x28, 0x0F, 0x47, 0x0E, 0x0A, 0xDB,
	0x52, 0xE6, 0x10, 0xCA, 0x52, 0x05, 0x0D, 0x20, 0xF6, 0x10,
	0xF2, 0x2A, 0x0B, 0x0A, 0xED, 0x5B, 0x0D, 0x0A, 0xCD, 0xE6,
	0x03, 0x30, 0x07, 0x3D, 0xCA, 0x52, 0x05, 0xC3, 0x7B, 0x05,
	0xDD, 0xE1, 0x21, 0x00, 0x00, 0xC9, 0xDD, 0x21, 0xED, 0x09,
	0xCD, 0x13, 0x06, 0x3A, 0x06, 0x0A, 0x3D, 0x32, 0x06, 0x0A,
	0x28, 0x13, 0x3A, 0x04, 0x0A, 0xF6, 0x01, 0x32, 0x04, 0x0A,
	0x3A, 0x01, 0x0A, 0xF6, 0x01, 0x32, 0x01, 0x0A, 0xC3, 0x0A,
	0x05, 0xDD, 0xE1, 0x21, 0x01, 0x00, 0xC9, 0xDD, 0x21, 0xF1,
	0x09, 0xCD, 0x13, 0x06, 0x3A, 0x02, 0x0A, 0xF6, 0x01, 0x32,
	0x02, 0x0A, 0x3A, 0x04, 0x0A, 0x87, 0xF6, 0x01, 0x32, 0x04,
	0x0A, 0x3A, 0x05, 0x0A, 0x3D, 0x32, 0x05, 0x0A, 0xC2, 0x0A,
	0x05, 0xDD, 0xE1, 0x21, 0x02, 0x00, 0xC9, 0xDD, 0xE5, 0x21,
	0x00, 0x00, 0x39, 0x11, 0x04, 0x00, 0x19, 0x7E, 0x32, 0xE4,
	0x09, 0xE6, 0x80, 0x32, 0x07, 0x0A, 0x3A, 0x07, 0x0A, 0xB7,
	0x28, 0x06, 0xDD, 0x21, 0x58, 0x02, 0x18, 0x04, 0xDD, 0x21,
	0x96, 0x00, 0x3A, 0xE4, 0x09, 0xB7, 0x28, 0x31, 0x3C, 0x28,
	0x2E, 0x3D, 0x21, 0x08, 0x0A, 0x77, 0x23, 0x77, 0x23, 0x36,
	0x81, 0xAF, 0x32, 0xE8, 0x09, 0xDD, 0x2B, 0xDD, 0xE5, 0xE1,
	0x7C, 0xB5, 0x28, 0x2A, 0x21, 0x08, 0x0A, 0x11, 0x03, 0x00,
	0xCD, 0xAA, 0x04, 0x11, 0xE8, 0x03, 0x1B, 0x7B, 0xB2, 0x20,
	0xFB, 0x3A, 0xE8, 0x09, 0xB7, 0x28, 0xE0, 0x3A, 0xE4, 0x09,
	0x47, 0x3E, 0x07, 0x80, 0xE6, 0x7F, 0x47, 0x3A, 0x07, 0x0A,
	0xB0, 0x32, 0xE4, 0x09, 0x18, 0xA6, 0xDD, 0xE1, 0xC9, 0xB7,
	0xDD, 0x34, 0x00, 0xC0, 0xDD, 0x34, 0x01, 0xC0, 0xDD, 0x34,
	0x02, 0xC0, 0xDD, 0x34, 0x03, 0xC0, 0x37, 0xC9, 0x21, 0x02,
	0x00, 0x39, 0x5E, 0x23, 0x56, 0x23, 0x4E, 0x23, 0x46, 0x23,
	0x7E, 0x23, 0x66, 0x69, 0x4F, 0x78, 0x44, 0x67, 0xED, 0xB0,
	0xC9, 0x21, 0x02, 0x00, 0x39, 0x7E, 0x23, 0x66, 0x6F, 0x3E,
	0x11, 0xED, 0x39, 0x30, 0x7D, 0xED, 0x39, 0x28, 0x7C, 0xED,
	0x39, 0x29, 0x3E, 0x00, 0xED, 0x39, 0x2A, 0x3E, 0x40, 0xED,
	0x39, 0x2B, 0x3E, 0x00, 0xED, 0x39, 0x2C, 0x21, 0x80, 0x02,
	0x7D, 0xED, 0x39, 0x2E, 0x7C, 0xED, 0x39, 0x2F, 0x3E, 0x91,
	0xED, 0x39, 0x30, 0xD3, 0x44, 0x3A, 0xDF, 0x09, 0xB7, 0x28,
	0x02, 0xD3, 0x42, 0xC9, 0x21, 0x02, 0x00, 0x39, 0x7E, 0x23,
	0x66, 0x6F, 0x3E, 0x21, 0xED, 0x39, 0x30, 0x3E, 0x40, 0xED,
	0x39, 0x20, 0x3E, 0x00, 0xED, 0x39, 0x21, 0xED, 0x39, 0x22,
	0x7D, 0xED, 0x39, 0x23, 0x7C, 0xED, 0x39, 0x24, 0x3E, 0x00,
	0xED, 0x39, 0x25, 0x21, 0x80, 0x02, 0x7D, 0xED, 0x39, 0x26,
	0x7C, 0xED, 0x39, 0x27, 0x3E, 0x61, 0xED, 0x39, 0x30, 0xD3,
	0x43, 0x3A, 0xDF, 0x09, 0xB7, 0x28, 0x02, 0xD3, 0x42, 0xC9,
	0xED, 0x38, 0x2E, 0x5F, 0xED, 0x38, 0x2F, 0x57, 0xED, 0x38,
	0x2E, 0x6F, 0xED, 0x38, 0x2F, 0x67, 0xB7, 0xED, 0x52, 0x20,
	0xEB, 0x21, 0x80, 0x02, 0xB7, 0xED, 0x52, 0xC9, 0xED, 0x38,
	0x26, 0x5F, 0xED, 0x38, 0x27, 0x57, 0xED, 0x38, 0x26, 0x6F,
	0xED, 0x38, 0x27, 0x67, 0xB7, 0xED, 0x52, 0x20, 0xEB, 0x21,
	0x80, 0x02, 0xB7, 0xED, 0x52, 0xC9, 0xCD, 0xB4, 0x09, 0xDD,
	0x6E, 0x06, 0xDD, 0x66, 0x07, 0x7E, 0x23, 0x6E, 0x67, 0xC3,
	0xC0, 0x09, 0xCD, 0xB4, 0x09, 0x21, 0x00, 0x00, 0x22, 0x17,
	0x0A, 0x22, 0x10, 0x0A, 0x22, 0x12, 0x0A, 0x21, 0xD8, 0x0E,
	0x22, 0x19, 0x0A, 0xED, 0x5B, 0x19, 0x0A, 0x2A, 0xDC, 0x09,
	0xB7, 0xED, 0x52, 0x11, 0x00, 0xFF, 0x19, 0x22, 0x15, 0x0A,
	0xCB, 0x7C, 0x28, 0x06, 0x21, 0x00, 0x7D, 0x22, 0x15, 0x0A,
	0x2A, 0x19, 0x0A, 0xE5, 0xCD, 0xED, 0x02, 0xC3, 0xC0, 0x09,
	0xCD, 0xB4, 0x09, 0xE5, 0x2A, 0xE0, 0x09, 0x23, 0x23, 0x23,
	0xE5, 0xCD, 0xF6, 0x06, 0xC1, 0x7C, 0xE6, 0x03, 0x67, 0xDD,
	0x75, 0xFE, 0xDD, 0x74, 0xFF, 0xED, 0x5B, 0xE2, 0x09, 0x23,
	0x23, 0x23, 0xB7, 0xED, 0x52, 0x20, 0x0C, 0x11, 0x05, 0x00,
	0x2A, 0xE2, 0x09, 0xCD, 0xA5, 0x09, 0xF2, 0x7B, 0x07, 0x2A,
	0xE0, 0x09, 0xE5, 0xCD, 0xED, 0x02, 0xC3, 0xC0, 0x09, 0xED,
	0x5B, 0xE2, 0x09, 0x2A, 0x12, 0x0A, 0x19, 0x22, 0x12, 0x0A,
	0x2A, 0x17, 0x0A, 0x19, 0x22, 0x17, 0x0A, 0xED, 0x5B, 0x15,
	0x0A, 0x21, 0x9E, 0xFD, 0x19, 0xED, 0x5B, 0x17, 0x0A, 0xCD,
	0xA5, 0x09, 0xF2, 0xA5, 0x07, 0x21, 0x00, 0x00, 0x22, 0x17,
	0x0A, 0x3E, 0x01, 0x32, 0x0F, 0x0A, 0xCD, 0xB5, 0x07, 0x21,
	0x00, 0x00, 0x39, 0xF9, 0xC3, 0xC0, 0x09, 0xCD, 0xB4, 0x09,
	0x3A, 0x0F, 0x0A, 0xB7, 0xCA, 0xC0, 0x09, 0xED, 0x5B, 0x10,
	0x0A, 0x2A, 0x17, 0x0A, 0xCD, 0xA5, 0x09, 0xF2, 0xDE, 0x07,
	0xED, 0x5B, 0x17, 0x0A, 0x21, 0x62, 0x02, 0x19, 0xED, 0x5B,
	0x10, 0x0A, 0xCD, 0xA5, 0x09, 0xFA, 0xFE, 0x07, 0xED, 0x5B,
	0x10, 0x0A, 0x2A, 0x17, 0x0A, 0xB7, 0xED, 0x52, 0x20, 0x07,
	0x2A, 0x12, 0x0A, 0x7D, 0xB4, 0x28, 0x0D, 0xED, 0x5B, 0x17,
	0x0A, 0x2A, 0x10, 0x0A, 0xCD, 0xA5, 0x09, 0xF2, 0x11, 0x08,
	0xED, 0x5B, 0x19, 0x0A, 0x2A, 0x17, 0x0A, 0x19, 0xE5, 0xCD,
	0xED, 0x02, 0xAF, 0x32, 0x0F, 0x0A, 0xC3, 0xC0, 0x09, 0xCD,
	0xE0, 0x02, 0x21, 0x00, 0x00, 0x39, 0xF9, 0xC3, 0xC0, 0x09,
	0xCD, 0xB4, 0x09, 0x3A, 0x14, 0x0A, 0xB7, 0x28, 0x16, 0xCD,
	0xBE, 0x06, 0xED, 0x5B, 0x1B, 0x0A, 0x13, 0x13, 0x13, 0xCD,
	0xA5, 0x09, 0xF2, 0x3B, 0x08, 0x21, 0x01, 0x00, 0xC3, 0xC0,
	0x09, 0x21, 0x00, 0x00, 0xC3, 0xC0, 0x09, 0xCD, 0xC8, 0x09,
	0xFC, 0xFF, 0xCD, 0x1C, 0x08, 0x7D, 0xB4, 0xC2, 0xC0, 0x09,
	0xED, 0x5B, 0x12, 0x0A, 0x21, 0x00, 0x00, 0xCD, 0xA5, 0x09,
	0xF2, 0xC0, 0x09, 0xED, 0x5B, 0x19, 0x0A, 0x2A, 0x10, 0x0A,
	0x19, 0xDD, 0x75, 0xFE, 0xDD, 0x74, 0xFF, 0x23, 0x23, 0x23,
	0xE5, 0xCD, 0xF6, 0x06, 0xC1, 0x7C, 0xE6, 0x03, 0x67, 0x23,
	0x23, 0x23, 0xDD, 0x75, 0xFC, 0xDD, 0x74, 0xFD, 0xE5, 0xDD,
	0x6E, 0xFE, 0xDD, 0x66, 0xFF, 0xE5, 0x21, 0x1E, 0x0A, 0xE5,
	0xCD, 0x26, 0x06, 0xC1, 0xC1, 0xDD, 0x6E, 0xFC, 0xDD, 0x66,
	0xFD, 0x22, 0x1B, 0x0A, 0x21, 0x1D, 0x0A, 0x36, 0x04, 0x21,
	0x1B, 0x0A, 0xE3, 0xCD, 0x3D, 0x06, 0xC1, 0x3E, 0x01, 0x32,
	0x14, 0x0A, 0xF3, 0xDD, 0x5E, 0xFC, 0xDD, 0x56, 0xFD, 0x2A,
	0x12, 0x0A, 0xB7, 0xED, 0x52, 0x22, 0x12, 0x0A, 0xCB, 0x7C,
	0x28, 0x11, 0x21, 0x00, 0x00, 0x22, 0x12, 0x0A, 0x22, 0x17,
	0x0A, 0x22, 0x10, 0x0A, 0x32, 0x0F, 0x0A, 0x18, 0x25, 0xDD,
	0x5E, 0xFC, 0xDD, 0x56, 0xFD, 0x2A, 0x10, 0x0A, 0x19, 0x22,
	0x10, 0x0A, 0xED, 0x5B, 0x15, 0x0A, 0x21, 0x9E, 0xFD, 0x19,
	0xED, 0x5B, 0x10, 0x0A, 0xCD, 0xA5, 0x09, 0xF2, 0xF4, 0x08,
	0x21, 0x00, 0x00, 0x22, 0x10, 0x0A, 0xCD, 0xB5, 0x07, 0x21,
	0x00, 0x00, 0x39, 0xF9, 0xFB, 0xC3, 0xC0, 0x09, 0xCD, 0xB4,
	0x09, 0x21, 0x7B, 0x0C, 0x36, 0x00, 0x21, 0x79, 0x0C, 0xE5,
	0xCD, 0x7C, 0x06, 0x21, 0x1B, 0x0A, 0xE3, 0xCD, 0x3D, 0x06,
	0xC1, 0xCD, 0x1F, 0x09, 0xCD, 0x41, 0x08, 0x18, 0xF8, 0xCD,
	0xB4, 0x09, 0x21, 0x7B, 0x0C, 0x7E, 0xB7, 0xCA, 0xC0, 0x09,
	0xCD, 0xDA, 0x06, 0xED, 0x5B, 0x79, 0x0C, 0x13, 0x13, 0x13,
	0xCD, 0xA5, 0x09, 0xFA, 0xC0, 0x09, 0x21, 0x7B, 0x0C, 0x7E,
	0xFE, 0x01, 0x28, 0x15, 0xFE, 0x03, 0x28, 0x51, 0xFE, 0x05,
	0x21, 0x7B, 0x0C, 0x36, 0x00, 0x21, 0x79, 0x0C, 0xE5, 0xCD,
	0x7C, 0x06, 0xC3, 0xC0, 0x09, 0x3A, 0xD7, 0x0E, 0xB7, 0x20,
	0x17, 0x21, 0x7D, 0x0C, 0x7E, 0x32, 0xDF, 0x09, 0xCD, 0x06,
	0x07, 0x21, 0x7C, 0x0C, 0x7E, 0x6F, 0x17, 0x9F, 0x67, 0xE5,
	0xCD, 0xA3, 0x05, 0xC1, 0x21, 0x1D, 0x0A, 0x36, 0x02, 0x21,
	0x02, 0x00, 0x22, 0x1B, 0x0A, 0x3A, 0xE4, 0x09, 0x21, 0x1E,
	0x0A, 0x77, 0x3A, 0xDE, 0x09, 0x21, 0x1F, 0x0A, 0x77, 0x21,
	0x1B, 0x0A, 0xE5, 0xCD, 0x3D, 0x06, 0xC1, 0x18, 0xB1, 0x2A,
	0x79, 0x0C, 0xE5, 0x21, 0x7C, 0x0C, 0xE5, 0xCD, 0x9B, 0x04,
	0xC1, 0x18, 0xEF, 0x7C, 0xAA, 0xFA, 0xAD, 0x09, 0xED, 0x52,
	0xC9, 0x7C, 0xE6, 0x80, 0xED, 0x52, 0x3C, 0xC9, 0xE1, 0xFD,
	0xE5, 0xDD, 0xE5, 0xDD, 0x21, 0x00, 0x00, 0xDD, 0x39, 0xE9,
	0xDD, 0xF9, 0xDD, 0xE1, 0xFD, 0xE1, 0xC9, 0xE9, 0xE1, 0xFD,
	0xE5, 0xDD, 0xE5, 0xDD, 0x21, 0x00, 0x00, 0xDD, 0x39, 0x5E,
	0x23, 0x56, 0x23, 0xEB, 0x39, 0xF9, 0xEB, 0xE9, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#endif
};


BOOLEAN
LtFirmInitialize(
	IN	PLT_ADAPTER Adapter,
	IN	UCHAR		SuggestedNodeId
	)
/*++

Routine Description:

	This routine initializes the card, downloads the firmware to it.

Arguments:

	Adapter		:	Pointer to the adapter structure.

Return Value:

	TRUE		:	If successful, false otherwise

--*/
{
	PUCHAR 	Firmware;
	UINT 	FirmwareLen;
	UINT 	RetryCount;
	UCHAR 	Data;
	BOOLEAN	Result = FALSE;

	// Clear the request Latch
	NdisRawReadPortUchar(XFER_PORT, &Data);

	// Clear the TX_READY FLOP
	NdisRawWritePortUchar(XFER_PORT, (UCHAR)0);

	// Reset the card.
	NdisRawWritePortUchar(RESET_PORT, (UCHAR)0);

	NdisStallExecution(LT_FIRM_INIT_STALL_TIME*5);

	for (RetryCount = 0; RetryCount < MAX_READ_RETRY_COUNT; RetryCount++)
	{
		// Get Card Status.
		NdisRawReadPortUchar(SC_PORT, &Data);

		if (Data & TX_READY)
		{
			break;
		}
		else DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_WARN,
					("LtFirmInitialize: Waiting for card ready SC_PORT %x\n", Data));

		NdisStallExecution(LT_FIRM_INIT_STALL_TIME);
	}

	//	BUGBUG:
	//	!!!!!!
	//	For DAYNA, it will not be ready at this point. DCH is going to
	//	send information to fix this.

	do
	{
		if (RetryCount == MAX_READ_RETRY_COUNT)
		{
			LOGERROR(
				Adapter->NdisAdapterHandle,
				NDIS_ERROR_CODE_HARDWARE_FAILURE);

			DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_FATAL,
					("LtFirmInitialize: Card Not Ready after Reset\n"));
			break;
		}

		//	Copy the firmware to the card.
		Firmware 	= LtMicroCode;
		FirmwareLen = sizeof(LtMicroCode);

		DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_INFO,
				("LtFirmInitialize: DownLoad %d bytes of firmware\n", FirmwareLen));

		// Well... the card is alive and well and in a reset state.
		// Next we need to output the first byte of the firmware and
		// check for TX_READY.
		NdisRawWritePortUchar(XFER_PORT, *Firmware);

		DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_INFO,
				("LtFirmInitialize: First byte of Firmware on card\n"));

		NdisRawReadPortUchar(SC_PORT, &Data);

		if (Data & TX_READY)
		{
			DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_FATAL,
					("LtFirmInitialize: Card Not Ready During Download\n"));

			LOGERROR(
				Adapter->NdisAdapterHandle,
				NDIS_ERROR_CODE_HARDWARE_FAILURE);
			break;
		}

		// Skip over the first byte because it already out there.
		Firmware ++;
		FirmwareLen --;

		NdisRawWritePortBufferUchar(XFER_PORT,
									Firmware,
									FirmwareLen);

		// Tell the card to start
		NdisRawReadPortUchar(XFER_PORT, &Data);

		// Wait for the card to start
		for (RetryCount = 0; RetryCount < MAX_START_RETRY_COUNT; RetryCount++)
		{
			NdisStallExecution(LT_FIRM_INIT_STALL_TIME);

			// Get Status
			NdisRawReadPortUchar(SC_PORT, &Data);

			DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_WARN,
					("LtFirmInitialize: Waiting for start - SC_PORT Data %x\n",
					(UCHAR)Data));

			if (Data & RX_READY)
			{
				break;
			}
		}

		//	!!!	This seems to be the only way the MCA card works according to
		//	!!!	Dave Hornbaker. It seems that the MCA card doesnt get ready at
		//	!!! this point, but works later on.
		if (RetryCount == MAX_START_RETRY_COUNT)
		{
			ASSERT(Adapter->BusType !=  NdisInterfaceMca);

			DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_FATAL,
					("LtFirmInitialize: Card Not Ready, could not get status\n"));

			LOGERROR(
				Adapter->NdisAdapterHandle,
				NDIS_ERROR_CODE_INVALID_VALUE_FROM_ADAPTER);
			break;
		}

		// Clear the initial ready signal.
		NdisRawReadPortUchar(XFER_PORT, &Data);

		// Now loop here for a finite time till the card acquires a node id.
		// If it fails to do so in the specified time, fail the load.
		if (!LtInitGetAddressSetPoll(Adapter, SuggestedNodeId))
		{
			break;
		}

		// We need to catch the card fast after it acquire the node id and before it
		// receives any packets. If it does receive any packets, then ask it acquire
		// the node id again. The stall happens ONLY IF A PACKET IS RECVD.
		for (RetryCount = 0; RetryCount < MAX_START_RETRY_COUNT*200; RetryCount++)
		{
			USHORT 				ResponseLength;
			UCHAR 				ResponseType;
			LT_INIT_RESPONSE 	InitPacket;

			//	Check for receive data
			NdisRawReadPortUchar(SC_PORT, &Data);

			if (Data & RX_READY)
			{
				// Get the length of the response on the card
				NdisRawReadPortUchar(XFER_PORT, &Data);

				ResponseLength = (USHORT)(Data & 0xFF);

				NdisRawReadPortUchar(XFER_PORT, &Data);

				ResponseLength |= (Data << 8);

				// Now get the IO code.
				NdisRawReadPortUchar(XFER_PORT, &ResponseType);

				DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_INFO,
						("LtFirmInitialize: RespType = %x, RespLength = %d\n",
							ResponseType, ResponseLength));

				if ((ResponseType == LT_RSP_LAP_INIT) &&
					(ResponseLength == sizeof(LT_INIT_RESPONSE)))
				{
					NdisRawReadPortBufferUchar(XFER_PORT,
												(PUCHAR)&InitPacket,
												ResponseLength);

					Adapter->NodeId = InitPacket.NodeId;
					Adapter->Flags |= ADAPTER_NODE_ID_VALID;

					//	This should start off a worker thread to write the
					//	node id into the pram.
					//	BUGBUG: Implement using worker threads.
					//	LtRegWritePramNodeId(Adapter);

					DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_INFO,
							("LtFirmInitailize: Node id acquired %x\n", InitPacket.NodeId));
					break;
				}
				DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_WARN,
						("LtFirmInitailize: Node id not valid yet !!\n"));

				// Suck in the packet and throw it away
				while (ResponseLength-- > 0)
				{
					NdisRawReadPortUchar(XFER_PORT, &Data);
				}

				// The response was probably over-written by incoming packet.
				// Try again.
				NdisStallExecution(LT_FIRM_INIT_STALL_TIME);
				DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_WARN,
						("LtFirmInitailize: Re-acquire node after packet recv\n"));
				if (!LtInitGetAddressSetPoll(Adapter, SuggestedNodeId))
				{
					break;
				}
			}
			else
			{
				DBGPRINT(DBG_COMP_INIT, DBG_LEVEL_WARN,
						("LtFirmInitialize: Waiting for node - SC_PORT Data %x\n",
						(UCHAR)Data)); 
			}
			NdisStallExecution(500);	// 500us
		}
		Result = ((Adapter->Flags & ADAPTER_NODE_ID_VALID) != 0);
	} while (FALSE);

	return(Result);
}

