// Icr0092.h : main header file for the Icr0092 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0092Dlg.h"

// CIcr0092App
// See Icr0092.cpp for the implementation of this class
//

class CIcr0092App : public CWinApp
{
public:
	CIcr0092App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
