// Icr0093.h : main header file for the Icr0093 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0093Dlg.h"

// CIcr0093App
// See Icr0093.cpp for the implementation of this class
//

class CIcr0093App : public CWinApp
{
public:
	CIcr0093App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
