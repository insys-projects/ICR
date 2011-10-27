// Icr0094.h : main header file for the Icr0094 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0094Dlg.h"

// CIcr0094App
// See Icr0094.cpp for the implementation of this class
//

class CIcr0094App : public CWinApp
{
public:
	CIcr0094App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
