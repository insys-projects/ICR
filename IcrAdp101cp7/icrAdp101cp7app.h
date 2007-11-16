// IcrAdp101cP7app.h : main header file for the IcrAdp101cP7 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp101cP7Dlg.h"

// CIcrAdp101cP7App
// See IcrAdp101cP7.cpp for the implementation of this class
//

class CIcrAdp101cP7App : public CWinApp
{
public:
	CIcrAdp101cP7App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
