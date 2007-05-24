// Icr008B.h : main header file for the Icr008B DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr008BDlg.h"

// CIcr008BApp
// See Icr008B.cpp for the implementation of this class
//

class CIcr008BApp : public CWinApp
{
public:
	CIcr008BApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
