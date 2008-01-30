// Icr6203.h : main header file for the Icr6203 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr6203Dlg.h"

UINT const MAX_FIFOHOSTCNT = 1;

// CIcr6203App
// See Icr6203.cpp for the implementation of this class
//

class CIcr6203App : public CWinApp
{
public:
	CIcr6203App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
