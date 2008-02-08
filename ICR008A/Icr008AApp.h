// Icr008A.h : main header file for the Icr008A DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr008ADlg.h"

// CIcr008AApp
// See Icr008A.cpp for the implementation of this class
//

class CIcr008AApp : public CWinApp
{
public:
	CIcr008AApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
