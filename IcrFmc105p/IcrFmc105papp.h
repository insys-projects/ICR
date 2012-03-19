// IcrFmc105papp.h : main header file for the IcrFmc105p DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrFmc105pDlg.h"

UINT const MAX_DSPCNT = 16;

// CIcrFmc105pApp
// See IcrFmc105p.cpp for the implementation of this class
//

class CIcrFmc105pApp : public CWinApp
{
public:
	CIcrFmc105pApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
