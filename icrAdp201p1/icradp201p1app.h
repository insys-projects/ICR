// IcrAdp201p1.h : main header file for the IcrAdp201p1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp201p1Dlg.h"

// CIcrAdp201p1App
// See IcrAdp201p1.cpp for the implementation of this class
//

class CIcrAdp201p1App : public CWinApp
{
public:
	CIcrAdp201p1App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
