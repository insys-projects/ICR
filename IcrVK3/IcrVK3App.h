// IcrVK3.h : main header file for the IcrVK3 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IcrVK3Dlg.h"


// CIcrVK3App
// See IcrVK3.cpp for the implementation of this class
//

class CIcrVK3App : public CWinApp
{
public:
	CIcrVK3App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
