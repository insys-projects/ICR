// Icr64Z5App.h : main header file for the Icr64Z5 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr64Z5Dlg.h"

// CIcr64Z5App
// See Icr64Z5.cpp for the implementation of this class
//

class CIcr64Z5App : public CWinApp
{
public:
	CIcr64Z5App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
