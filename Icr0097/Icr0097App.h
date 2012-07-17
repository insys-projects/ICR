// Icr0097.h : main header file for the Icr0097 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0097Dlg.h"

// CIcr0097App
// See Icr0097.cpp for the implementation of this class
//

class CIcr0097App : public CWinApp
{
public:
	CIcr0097App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
