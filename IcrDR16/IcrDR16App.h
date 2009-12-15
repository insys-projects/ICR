// IcrDR16.h : main header file for the IcrDR16 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IcrDR16Dlg.h"

// CIcrDR16App
// See IcrDR16.cpp for the implementation of this class
//

class CIcrDR16App : public CWinApp
{
public:
	CIcrDR16App();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
