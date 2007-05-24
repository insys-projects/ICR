// Icr0084.h : main header file for the Icr0084 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr0084Dlg.h"

// CIcr0084App
// See Icr0084.cpp for the implementation of this class
//

class CIcr0084App : public CWinApp
{
public:
	CIcr0084App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
