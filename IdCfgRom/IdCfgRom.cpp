// IdCfgRom.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "IdCfgRomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIdCfgRomApp

BEGIN_MESSAGE_MAP(CIdCfgRomApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CIdCfgRomApp construction

CIdCfgRomApp::CIdCfgRomApp()
{
	EnableHtmlHelp();

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIdCfgRomApp object

CIdCfgRomApp theApp;

DEVICE_CTRL g_DeviceCtrl[MAXDEVICES];
BASEMOD_CTRL g_BaseModCtrl[MAXBASEMODS];
SUBMOD_CTRL g_SubmodCtrl[MAXSUBMODS];

int g_nNumOfDevices;
int g_nNumOfBaseModules;
int g_nNumOfSubModules;

// изъятие информации об устройствах, базовых модулях и субмодулях из dll'ей
void GetInfoFromDlls();

// CIdCfgRomApp initialization

BOOL CIdCfgRomApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization

	GetInfoFromDlls();

	CIdCfgRomDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void GetInfoFromDlls()
{
	CString sDllPath = GetCurDir() + "\\*.dll";
	WIN32_FIND_DATA FindData;
	HANDLE hFindFiles = FindFirstFile(sDllPath, &FindData);
	if(hFindFiles == INVALID_HANDLE_VALUE)
		return;
	do
	{
		HINSTANCE hLib = LoadLibrary(FindData.cFileName);
		if( !hLib )
			continue;

		DEVICE_GetInfo_Type* pDEVICE_GetInfo = (DEVICE_GetInfo_Type*)GetProcAddress( hLib, _T("DEVICE_GetInfo")); 
		DEVICE_Close_Type*	pDEVICE_Close = (DEVICE_Close_Type*)GetProcAddress( hLib, _T("DEVICE_Close"));
		DEVICE_ReadICR_Type* pDEVICE_ReadICR = (DEVICE_ReadICR_Type*)GetProcAddress( hLib, _T("DEVICE_ReadIdCfgRom")); 
		DEVICE_WriteICR_Type* pDEVICE_WriteICR = (DEVICE_WriteICR_Type*)GetProcAddress( hLib, _T("DEVICE_WriteIdCfgRom"));

		BASEMOD_GetInfo_Type* pBASEMOD_GetInfo = (BASEMOD_GetInfo_Type*)GetProcAddress( hLib, _T("BASEMOD_GetInfo"));
		BASEMOD_Close_Type* pBASEMOD_Close = (BASEMOD_Close_Type*)GetProcAddress( hLib, _T("BASEMOD_Close"));
		BASEMOD_SetProp_Type* pBASEMOD_SetProp = (BASEMOD_SetProp_Type*)GetProcAddress( hLib, _T("BASEMOD_SetProperty"));
		BASEMOD_GetProp_Type* pBASEMOD_GetProp = (BASEMOD_GetProp_Type*)GetProcAddress( hLib, _T("BASEMOD_GetProperty"));
		BASEMOD_DlgProp_Type* pBASEMOD_DlgProp = (BASEMOD_DlgProp_Type*)GetProcAddress( hLib, _T("BASEMOD_DialogProperty"));

		SUBMOD_GetInfo_Type* pSUBMOD_GetInfo = (SUBMOD_GetInfo_Type*)GetProcAddress( hLib, _T("SUBMOD_GetInfo"));
		SUBMOD_Close_Type*	pSUBMOD_Close = (SUBMOD_Close_Type*)GetProcAddress( hLib, _T("SUBMOD_Close"));
		SUBMOD_SetProp_Type* pSUBMOD_SetProp = (SUBMOD_SetProp_Type*)GetProcAddress( hLib, _T("SUBMOD_SetProperty"));
		SUBMOD_GetProp_Type* pSUBMOD_GetProp = (SUBMOD_GetProp_Type*)GetProcAddress( hLib, _T("SUBMOD_GetProperty"));
		SUBMOD_DlgProp_Type* pSUBMOD_DlgProp = (SUBMOD_DlgProp_Type*)GetProcAddress( hLib, _T("SUBMOD_DialogProperty"));

		// dll с информацией об устройствах
		if( pDEVICE_GetInfo && pDEVICE_Close && pDEVICE_ReadICR && pDEVICE_WriteICR )
		{
			for(int ii=0; g_nNumOfDevices<MAXDEVICES; ii++)
			{
				int devNum = ii;
				DEVICE_INFO DevInfo;
				DevInfo.wSize = sizeof(DEVICE_INFO);
				(pDEVICE_GetInfo)(&devNum, &DevInfo);
				if( devNum == -1 )
					break;
				g_DeviceCtrl[g_nNumOfDevices].hLib = hLib;
				g_DeviceCtrl[g_nNumOfDevices].pGetInfo = pDEVICE_GetInfo;
				g_DeviceCtrl[g_nNumOfDevices].pClose = pDEVICE_Close;
				g_DeviceCtrl[g_nNumOfDevices].pReadIdCfgRom = pDEVICE_ReadICR;
				g_DeviceCtrl[g_nNumOfDevices].pWriteIdCfgRom = pDEVICE_WriteICR;

				g_DeviceCtrl[g_nNumOfDevices].devInfo.wSize = sizeof(DEVICE_INFO);
				g_DeviceCtrl[g_nNumOfDevices].devInfo.wType = DevInfo.wType;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.bVersion = DevInfo.bVersion;
				lstrcpy(g_DeviceCtrl[g_nNumOfDevices].devInfo.sName, DevInfo.sName);
				g_DeviceCtrl[g_nNumOfDevices].devInfo.bBusType = DevInfo.bBusType;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.wBusNum	= DevInfo.wBusNum;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.wDevNum = DevInfo.wDevNum;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.wSlotNum = DevInfo.wSlotNum;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.nInstance = DevInfo.nInstance;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.pBaseCfgMem = DevInfo.pBaseCfgMem;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.nBaseCfgMemSize = DevInfo.nBaseCfgMemSize;
				g_DeviceCtrl[g_nNumOfDevices].devInfo.pAdmCfgMem[0] = DevInfo.pAdmCfgMem[0];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.nAdmCfgMemSize[0] = DevInfo.nAdmCfgMemSize[0];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.pAdmCfgMem[1] = DevInfo.pAdmCfgMem[1];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.nAdmCfgMemSize[1] = DevInfo.nAdmCfgMemSize[1];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.pAdmCfgMem[2] = DevInfo.pAdmCfgMem[2];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.nAdmCfgMemSize[2] = DevInfo.nAdmCfgMemSize[2];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.pAdmCfgMem[3] = DevInfo.pAdmCfgMem[3];
				g_DeviceCtrl[g_nNumOfDevices].devInfo.nAdmCfgMemSize[3] = DevInfo.nAdmCfgMemSize[3];
				g_nNumOfDevices++;
			}
		}
		// dll с информацией о базовых модулях
		else if(pBASEMOD_GetInfo && pBASEMOD_Close && pBASEMOD_SetProp && pBASEMOD_GetProp && pBASEMOD_DlgProp)
		{
			for(int ii=0; g_nNumOfBaseModules<MAXBASEMODS; ii++)
			{
				int devNum = ii;
				BASEMOD_INFO DevInfo;
				DevInfo.wSize = sizeof(BASEMOD_INFO);
				(pBASEMOD_GetInfo)(&devNum, &DevInfo);
				if(devNum == -1)
					break;
				g_BaseModCtrl[g_nNumOfBaseModules].hLib	 = hLib;
				g_BaseModCtrl[g_nNumOfBaseModules].pGetInfo = pBASEMOD_GetInfo;
				g_BaseModCtrl[g_nNumOfBaseModules].pClose = pBASEMOD_Close;
				g_BaseModCtrl[g_nNumOfBaseModules].pSetProperty = pBASEMOD_SetProp;
				g_BaseModCtrl[g_nNumOfBaseModules].pGetProperty = pBASEMOD_GetProp;
				g_BaseModCtrl[g_nNumOfBaseModules].pDlgProperty = pBASEMOD_DlgProp;

				g_BaseModCtrl[g_nNumOfBaseModules].devInfo.wSize = sizeof(BASEMOD_INFO);
				g_BaseModCtrl[g_nNumOfBaseModules].devInfo.pCfgMem = DevInfo.pCfgMem;
				g_BaseModCtrl[g_nNumOfBaseModules].devInfo.nCfgMemSize = DevInfo.nCfgMemSize;
				g_BaseModCtrl[g_nNumOfBaseModules].devInfo.dType = DevInfo.dType;
				lstrcpy(g_BaseModCtrl[g_nNumOfBaseModules].devInfo.sName, DevInfo.sName);
				g_nNumOfBaseModules++;
			}
		}
		// dll с информацией о субмодулях
		else if(pSUBMOD_GetInfo && pSUBMOD_Close && pSUBMOD_SetProp && pSUBMOD_GetProp && pSUBMOD_DlgProp)
		{
			for(int ii=0; g_nNumOfSubModules<MAXSUBMODS; ii++)
			{
				int devNum = ii;
				SUBMOD_INFO DevInfo;
				DevInfo.wSize = sizeof(SUBMOD_INFO);
				(pSUBMOD_GetInfo)(&devNum, &DevInfo);
				if(devNum == -1)
					break;
				g_SubmodCtrl[g_nNumOfSubModules].hLib	 = hLib;
				g_SubmodCtrl[g_nNumOfSubModules].pGetInfo = pSUBMOD_GetInfo;
				g_SubmodCtrl[g_nNumOfSubModules].pClose = pSUBMOD_Close;
				g_SubmodCtrl[g_nNumOfSubModules].pSetProperty = pSUBMOD_SetProp;
				g_SubmodCtrl[g_nNumOfSubModules].pGetProperty = pSUBMOD_GetProp;
				g_SubmodCtrl[g_nNumOfSubModules].pDlgProperty = pSUBMOD_DlgProp;

				g_SubmodCtrl[g_nNumOfSubModules].devInfo.wSize = sizeof(SUBMOD_INFO);
				g_SubmodCtrl[g_nNumOfSubModules].devInfo.pCfgMem = DevInfo.pCfgMem;
				g_SubmodCtrl[g_nNumOfSubModules].devInfo.nCfgMemSize = DevInfo.nCfgMemSize;
				g_SubmodCtrl[g_nNumOfSubModules].devInfo.Type = DevInfo.Type;
				lstrcpy(g_SubmodCtrl[g_nNumOfSubModules].devInfo.sName, DevInfo.sName);
				g_nNumOfSubModules++;
			}
		}
		else
		{
			FreeLibrary(hLib);
			continue;
		}

	} while(FindNextFile(hFindFiles,&FindData));
	FindClose(hFindFiles);
}
