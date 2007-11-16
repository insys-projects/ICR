// IcrAdp101pci.h : main header file for the IcrAdp101pci DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrAdp101pciDlg.h"

// CIcrAdp101pciApp
// See IcrAdp101pci.cpp for the implementation of this class
//

class CIcrAdp101pciApp : public CWinApp
{
public:
	CIcrAdp101pciApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
