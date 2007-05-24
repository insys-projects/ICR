// Icr008C.h : main header file for the Icr008C DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr008CDlg.h"

// CIcr008CApp
// See Icr008C.cpp for the implementation of this class
//

class CIcr008CApp : public CWinApp
{
public:
	CIcr008CApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
