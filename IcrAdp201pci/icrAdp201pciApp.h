// IcrAdp201pci.h : main header file for the IcrAdp201pci DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp201pciDlg.h"

// CIcrAdp201pciApp
// See IcrAdp201pci.cpp for the implementation of this class
//

class CIcrAdp201pciApp : public CWinApp
{
public:
	CIcrAdp201pciApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
