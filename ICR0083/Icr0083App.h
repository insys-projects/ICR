// Icr0083.h : main header file for the Icr0083 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr0083Dlg.h"

// CIcr0083App
// See Icr0083.cpp for the implementation of this class
//

class CIcr0083App : public CWinApp
{
public:
	CIcr0083App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
