// Icr0087.h : main header file for the Icr0087 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Icr0087Dlg.h"

// CIcr0087App
// See Icr0087.cpp for the implementation of this class
//

class CIcr0087App : public CWinApp
{
public:
	CIcr0087App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
