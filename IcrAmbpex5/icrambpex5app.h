// IcrAmbpex5app.h : main header file for the IcrAmbpex5 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAmbpex5Dlg.h"

// CIcrAmbpex5App
// See IcrAmbpex5.cpp for the implementation of this class
//

class CIcrAmbpex5App : public CWinApp
{
public:
	CIcrAmbpex5App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
