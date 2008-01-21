// Icr6713.h : main header file for the Icr6713 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr6713Dlg.h"

UINT const MAX_HOSTPLDCNT = 4;

// CIcr6713App
// See Icr6713.cpp for the implementation of this class
//

class CIcr6713App : public CWinApp
{
public:
	CIcr6713App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
