// IcrAdp201x1.h : main header file for the IcrAdp201x1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp201x1Dlg.h"

// CIcrAdp201x1App
// See IcrAdp201x1.cpp for the implementation of this class
//

class CIcrAdp201x1App : public CWinApp
{
public:
	CIcrAdp201x1App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
