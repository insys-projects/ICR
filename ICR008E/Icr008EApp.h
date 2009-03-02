// Icr008E.h : main header file for the Icr008E DLL
//


#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr008EDlg.h"

// CIcr0083App
// See Icr0083.cpp for the implementation of this class
//

class CIcr008EApp : public CWinApp
{
public:
	CIcr008EApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
