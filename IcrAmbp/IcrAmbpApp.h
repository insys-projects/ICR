// IcrAmbp.h : main header file for the IcrAmbp DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAmbpDlg.h"

UINT const MAX_SDRAMCNT = 16;
UINT const MAX_DSPCNT = 16;


// CIcrAmbpApp
// See IcrAmbp.cpp for the implementation of this class
//

class CIcrAmbpApp : public CWinApp
{
public:
	CIcrAmbpApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
