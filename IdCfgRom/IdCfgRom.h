// IdCfgRom.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "IdCfgRomMsg.h"

#include "Functions.h"

#define MAXDEVICES 32
#define MAXBASEMODS 256
#define MAXSUBMODS 256

#include "device.h"

enum
{
	CMDDEV_BASE,
	CMDDEV_SUB,
	CMDDEV_BASESUB
};

// Struct info about device DLL 
typedef struct {
	HINSTANCE			 hLib;				// Dll Handle 
	DEVICE_GetInfo_Type	 *pGetInfo;			// API function
	DEVICE_Close_Type	 *pClose;			// API function
	DEVICE_ReadICR_Type	 *pReadIdCfgRom;	// API function
	DEVICE_WriteICR_Type *pWriteIdCfgRom;	// API function
	DEVICE_INFO			 devInfo;			// Info structure
} DEVICE_CTRL, *PDEVICE_CTRL;

#include "basemod.h"

// Struct info about base module DLL 
typedef struct {
	HINSTANCE				hLib;			// Dll Handle 
	BASEMOD_GetInfo_Type	*pGetInfo;		// API function
	BASEMOD_Close_Type		*pClose;		// API function
	BASEMOD_GetProp_Type	*pGetProperty;	// API function
	BASEMOD_SetProp_Type	*pSetProperty;	// API function
	BASEMOD_DlgProp_Type	*pDlgProperty;	// API function
	BASEMOD_INFO			devInfo;		// Info structure
} BASEMOD_CTRL, *PBASEMOD_CTRL;

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

// дл€ работы с реестром
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

	CString m_sCmdFileName;
	int		m_nCmdDev;
	int		m_nCmdNoDev;

	// изъ€тие информации об устройствах, базовых модул€х и субмодул€х из dll'ей
	void GetInfoFromDlls();
	int ParseCommandLine();
};

extern CIdCfgRomApp theApp;

extern DEVICE_CTRL g_DeviceCtrl[];
extern BASEMOD_CTRL g_BaseModCtrl[MAXBASEMODS];
extern SUBMOD_CTRL g_SubmodCtrl[];
extern int g_nNumOfDevices;
extern int g_nNumOfBaseModules;
extern int g_nNumOfSubModules;
