// IcrDsp101cP10.h : main header file for the IcrDsp101cP10 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrDsp101cP10Dlg.h"

// CIcrDsp101cP10App
// See IcrDsp101cP10.cpp for the implementation of this class
//

class CIcrDsp101cP10App : public CWinApp
{
public:
	CIcrDsp101cP10App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
