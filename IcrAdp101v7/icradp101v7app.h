// IcrAdp101v7app.h : main header file for the IcrAdp101v7 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp101v7Dlg.h"

// CIcrAdp101v7App
// See IcrAdp101v7.cpp for the implementation of this class
//

class CIcrAdp101v7App : public CWinApp
{
public:
	CIcrAdp101v7App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
