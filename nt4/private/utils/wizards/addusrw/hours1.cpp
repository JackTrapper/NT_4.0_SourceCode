// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "hours1.h"

/////////////////////////////////////////////////////////////////////////////
// CHours

IMPLEMENT_DYNCREATE(CHours, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CHours properties

unsigned long CHours::GetCrPermitColor()
{
	unsigned long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CHours::SetCrPermitColor(unsigned long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

unsigned long CHours::GetCrDenyColor()
{
	unsigned long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CHours::SetCrDenyColor(unsigned long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

VARIANT CHours::GetDateData()
{
	VARIANT result;
	GetProperty(0x3, VT_VARIANT, (void*)&result);
	return result;
}

void CHours::SetDateData(const VARIANT& propVal)
{
	SetProperty(0x3, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CHours operations
