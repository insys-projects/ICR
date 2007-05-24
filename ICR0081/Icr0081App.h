// Icr0081.h : main header file for the Icr0081 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0081Dlg.h"

// CIcr0081App
// See Icr0081.cpp for the implementation of this class
//

class CIcr0081App : public CWinApp
{
public:
	CIcr0081App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
