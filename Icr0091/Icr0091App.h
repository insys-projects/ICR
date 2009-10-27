// Icr0091.h : main header file for the Icr0091 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0091Dlg.h"

// CIcr0091App
// See Icr0091.cpp for the implementation of this class
//

class CIcr0091App : public CWinApp
{
public:
	CIcr0091App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
