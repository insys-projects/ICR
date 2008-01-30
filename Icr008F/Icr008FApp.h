// Icr008F.h : main header file for the Icr008F DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Icr008FDlg.h"

// CIcr008FApp
// See Icr008F.cpp for the implementation of this class
//

class CIcr008FApp : public CWinApp
{
public:
	CIcr008FApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
