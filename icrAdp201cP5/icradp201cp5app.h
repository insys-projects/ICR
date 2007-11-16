// IcrAdp201cP5app.h : main header file for the IcrAdp201cP5 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp201cP5Dlg.h"

// CIcrAdp201cP5App
// See IcrAdp201cP5.cpp for the implementation of this class
//

class CIcrAdp201cP5App : public CWinApp
{
public:
	CIcrAdp201cP5App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
