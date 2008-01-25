// Icr64Z4.h : main header file for the Icr64Z4 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr64Z4Dlg.h"

UINT const MAX_HOSTPLDCNT = 4;

// CIcr64Z4App
// See Icr64Z4.cpp for the implementation of this class
//

class CIcr64Z4App : public CWinApp
{
public:
	CIcr64Z4App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
