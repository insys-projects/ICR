// IcrAdp201v5app.h : main header file for the IcrAdp201v5 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp201v5Dlg.h"

// CIcrAdp201v5App
// See IcrAdp201v5.cpp for the implementation of this class
//

class CIcrAdp201v5App : public CWinApp
{
public:
	CIcrAdp201v5App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
