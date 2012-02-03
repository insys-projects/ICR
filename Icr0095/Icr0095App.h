// Icr0095.h : main header file for the Icr0095 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr0095Dlg.h"

// CIcr0095App
// See Icr0095.cpp for the implementation of this class
//

class CIcr0095App : public CWinApp
{
public:
	CIcr0095App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
