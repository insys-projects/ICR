// Icr0089.h : main header file for the Icr0089 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr0089Dlg.h"

// CIcr0089App
// See Icr0089.cpp for the implementation of this class
//

class CIcr0089App : public CWinApp
{
public:
	CIcr0089App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
