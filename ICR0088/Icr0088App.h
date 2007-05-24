// Icr0088.h : main header file for the Icr0088 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr0088Dlg.h"

// CIcr0088App
// See Icr0088.cpp for the implementation of this class
//

class CIcr0088App : public CWinApp
{
public:
	CIcr0088App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
