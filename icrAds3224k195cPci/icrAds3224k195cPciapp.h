// IcrAds3224k195cPciapp.h : main header file for the IcrAds3224k195cPci DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAds3224k195cPciDlg.h"

// CIcrAds3224k195cPciApp
// See IcrAds3224k195cPci.cpp for the implementation of this class
//

class CIcrAds3224k195cPciApp : public CWinApp
{
public:
	CIcrAds3224k195cPciApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
