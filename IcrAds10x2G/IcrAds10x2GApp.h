// IcrAds10x2G.h : main header file for the IcrAds10x2G DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAds10x2GDlg.h"

// CIcrAds10x2GApp
// See IcrAds10x2G.cpp for the implementation of this class
//

class CIcrAds10x2GApp : public CWinApp
{
public:
	CIcrAds10x2GApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
