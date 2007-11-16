// IcrAdp201P4app.h : main header file for the IcrAdp201P4 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp201P4Dlg.h"

// CIcrAdp201P4App
// See IcrAdp201P4.cpp for the implementation of this class
//

class CIcrAdp201P4App : public CWinApp
{
public:
	CIcrAdp201P4App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
