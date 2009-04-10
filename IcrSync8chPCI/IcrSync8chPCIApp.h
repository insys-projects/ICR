// IcrSync8chPCI.h : main header file for the IcrSync8chPCI DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IcrSync8chPCIDlg.h"

// CIcrSync8chPCIApp
// See IcrSync8chPCI.cpp for the implementation of this class
//

class CIcrSync8chPCIApp : public CWinApp
{
public:
	CIcrSync8chPCIApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
