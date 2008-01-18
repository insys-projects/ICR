// Icr64Z2A.h : main header file for the Icr64Z2A DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr64Z2ADlg.h"

UINT const MAX_HOSTPLDCNT = 4;

// CIcr64Z2AApp
// See Icr64Z2A.cpp for the implementation of this class
//

class CIcr64Z2AApp : public CWinApp
{
public:
	CIcr64Z2AApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
