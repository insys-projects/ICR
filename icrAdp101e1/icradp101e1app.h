// IcrAdp101E1app.h : main header file for the IcrAdp101E1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp101E1Dlg.h"


// See IcrAdp101E1.cpp for the implementation of this class
//

class CIcrAdp101E1App : public CWinApp
{
public:
	CIcrAdp101E1App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
