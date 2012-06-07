// Icr0096.h : main header file for the Icr0096 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0096Dlg.h"

// CIcr0096App
// See Icr0096.cpp for the implementation of this class
//

class CIcr0096App : public CWinApp
{
public:
	CIcr0096App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
