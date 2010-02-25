// IcrSync_cP6.h : main header file for the IcrSync_cP6 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "IcrSync_cP6Dlg.h"
#include "resource.h"		// main symbols


// CIcrSync_cP6App
// See IcrSync_cP6.cpp for the implementation of this class
//

class CIcrSync_cP6App : public CWinApp
{
public:
	CIcrSync_cP6App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
