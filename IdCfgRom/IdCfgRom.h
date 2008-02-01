// IdCfgRom.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IdCfgRomMsg.h"

#include "submod.h"

// Struct info about submodule DLL 
typedef struct {
	HINSTANCE			hLib;			// Dll Handle 
	SUBMOD_GetInfo_Type	*pGetInfo;		// API function
	SUBMOD_Close_Type	*pClose;		// API function
	SUBMOD_SetProp_Type	*pSetProperty;	// API function
	SUBMOD_GetProp_Type	*pGetProperty;	// API function
	SUBMOD_DlgProp_Type	*pDlgProperty;	// API function
	SUBMOD_INFO			devInfo;		// Info structure
} SUBMOD_CTRL, *PSUBMOD_CTRL;

#include "basemod.h"

// Struct info about base module DLL 
typedef struct {
	HINSTANCE			hLib;				// Dll Handle 
	BASEMOD_GetInfo_Type	*pGetInfo;		// API function
	BASEMOD_Close_Type		*pClose;		// API function
	BASEMOD_GetProp_Type	*pGetProperty;	// API function
	BASEMOD_SetProp_Type	*pSetProperty;	// API function
	BASEMOD_DlgProp_Type	*pDlgProperty;	// API function
	BASEMOD_INFO			devInfo;		// Info structure
} BASEMOD_CTRL, *PBASEMOD_CTRL;

#include "device.h"

// Struct info about device DLL 
typedef struct {
	HINSTANCE			 hLib;				// Dll Handle 
	DEVICE_GetInfo_Type	 *pGetInfo;			// API function
	DEVICE_Close_Type	 *pClose;			// API function
	DEVICE_ReadICR_Type	 *pReadIdCfgRom;	// API function
	DEVICE_WriteICR_Type *pWriteIdCfgRom;	// API function
	DEVICE_INFO			 devInfo;			// Info structure
} DEVICE_CTRL, *PDEVICE_CTRL;

// для работы с реестром
#include "atlbase.h"

// CIdCfgRomApp:
// See IdCfgRom.cpp for the implementation of this class
//

class CIdCfgRomApp : public CWinApp
{
public:
	CIdCfgRomApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CIdCfgRomApp theApp;