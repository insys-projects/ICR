// Icr0086.h : main header file for the Icr0086 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr0086Dlg.h"

// CIcr0086App
// See Icr0086.cpp for the implementation of this class
//

class CIcr0086App : public CWinApp
{
public:
	CIcr0086App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
