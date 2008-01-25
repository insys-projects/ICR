// Icr64Z1.h : main header file for the Icr64Z1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr64Z1Dlg.h"

UINT const MAX_HOSTPLDCNT = 4;

// CIcr64Z1App
// See Icr64Z1.cpp for the implementation of this class
//

class CIcr64Z1App : public CWinApp
{
public:
	CIcr64Z1App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
