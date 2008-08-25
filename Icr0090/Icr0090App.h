// Icr0090.h : main header file for the Icr0090 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0090Dlg.h"

// CIcr0090App
// See Icr0090.cpp for the implementation of this class
//

class CIcr0090App : public CWinApp
{
public:
	CIcr0090App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
