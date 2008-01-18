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

#define MAXDEVICES 32
#define MAXBASEMODS 256
#define MAXSUBMODS 256

DEVICE_CTRL DeviceCtrl[MAXDEVICES];
BASEMOD_CTRL BaseModCtrl[MAXBASEMODS];
SUBMOD_CTRL SubmodCtrl[MAXSUBMODS];

int m_NumOfDevices;
int m_NumOfBaseModules;
int m_NumOfSubModules;

// задается путь к папке с плагинами
//CString strDevsPath="Submodules\\";
int GetSubmodules();
int GetBaseModules();
int GetDevices();

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
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	for(int i = 0; i < MAXDEVICES; i++)
		DeviceCtrl[i].hLib = 0;
	m_NumOfDevices = GetDevices();

	for(int i = 0; i < MAXBASEMODS; i++)
		BaseModCtrl[i].hLib = 0;
	m_NumOfBaseModules = GetBaseModules();

	for(int i = 0; i < MAXSUBMODS; i++)
		SubmodCtrl[i].hLib = 0;
	m_NumOfSubModules = GetSubmodules();

	CIdCfgRomDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int GetDevices()
{
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir)/sizeof(TCHAR), szCurDir);
	CString sCurFullPath = szCurDir;
	sCurFullPath += _T("\\");
//	sCurFullPath += strDevsPath;
	SetCurrentDirectory(sCurFullPath);
//	CString sCurFullPathDll = sCurFullPath;
	sCurFullPath += _T("*.dll");
	WIN32_FIND_DATA FindData;
	HANDLE hFindFiles = FindFirstFile(sCurFullPath,&FindData); 
	if(hFindFiles == INVALID_HANDLE_VALUE)
		return 0;
	int idx = 0;
	do {
//		CString sPath = sCurFullPath;
//		sPath += FindData.cFileName; 
//		HINSTANCE hLib = LoadLibrary(sPath);
		HINSTANCE hLib = LoadLibrary(FindData.cFileName);
		if(hLib)
		{
			DEVICE_GetInfo_Type* pDEVICE_GetInfo; 
			DEVICE_ReadICR_Type* pDEVICE_ReadICR; 
			DEVICE_WriteICR_Type* pDEVICE_WriteICR; 
			DEVICE_Close_Type*	pDEVICE_Close;

			pDEVICE_GetInfo = (DEVICE_GetInfo_Type*)GetProcAddress( hLib, _T("DEVICE_GetInfo"));
			pDEVICE_Close = (DEVICE_Close_Type*)GetProcAddress( hLib, _T("DEVICE_Close"));
			pDEVICE_ReadICR = (DEVICE_ReadICR_Type*)GetProcAddress( hLib, _T("DEVICE_ReadIdCfgRom"));
			pDEVICE_WriteICR = (DEVICE_WriteICR_Type*)GetProcAddress( hLib, _T("DEVICE_WriteIdCfgRom"));
			if(pDEVICE_GetInfo && pDEVICE_ReadICR && pDEVICE_WriteICR && pDEVICE_Close)
			{
				for(int i = 0; idx < MAXDEVICES; idx++, i++)
				{
//					int devNum = idx;
					int devNum = i;
					DEVICE_INFO DevInfo;
					DevInfo.wSize = sizeof(DEVICE_INFO);
					(pDEVICE_GetInfo)(&devNum, &DevInfo);
					if(devNum == -1)
						break;
					DeviceCtrl[idx].hLib	 = hLib;
					DeviceCtrl[idx].pGetInfo = pDEVICE_GetInfo;
					DeviceCtrl[idx].pClose = pDEVICE_Close;
					DeviceCtrl[idx].pReadIdCfgRom = pDEVICE_ReadICR;
					DeviceCtrl[idx].pWriteIdCfgRom = pDEVICE_WriteICR;

					DeviceCtrl[idx].devInfo.wSize = sizeof(DEVICE_INFO);
					DeviceCtrl[idx].devInfo.wType = DevInfo.wType;
					DeviceCtrl[idx].devInfo.bVersion = DevInfo.bVersion;
					lstrcpy(DeviceCtrl[idx].devInfo.sName, DevInfo.sName);
					DeviceCtrl[idx].devInfo.bBusType = DevInfo.bBusType;
					DeviceCtrl[idx].devInfo.wBusNum	= DevInfo.wBusNum;
					DeviceCtrl[idx].devInfo.wDevNum = DevInfo.wDevNum;
					DeviceCtrl[idx].devInfo.wSlotNum = DevInfo.wSlotNum;
					DeviceCtrl[idx].devInfo.dInstance = DevInfo.dInstance;
					DeviceCtrl[idx].devInfo.pBaseCfgMem = DevInfo.pBaseCfgMem;
					DeviceCtrl[idx].devInfo.dBaseCfgMemSize = DevInfo.dBaseCfgMemSize;
					DeviceCtrl[idx].devInfo.pAdmCfgMem[0] = DevInfo.pAdmCfgMem[0];
					DeviceCtrl[idx].devInfo.dAdmCfgMemSize[0] = DevInfo.dAdmCfgMemSize[0];
					DeviceCtrl[idx].devInfo.pAdmCfgMem[1] = DevInfo.pAdmCfgMem[1];
					DeviceCtrl[idx].devInfo.dAdmCfgMemSize[1] = DevInfo.dAdmCfgMemSize[1];
					DeviceCtrl[idx].devInfo.pAdmCfgMem[2] = DevInfo.pAdmCfgMem[2];
					DeviceCtrl[idx].devInfo.dAdmCfgMemSize[2] = DevInfo.dAdmCfgMemSize[2];
					DeviceCtrl[idx].devInfo.pAdmCfgMem[3] = DevInfo.pAdmCfgMem[3];
					DeviceCtrl[idx].devInfo.dAdmCfgMemSize[3] = DevInfo.dAdmCfgMemSize[3];
				}
			}
			else
				FreeLibrary(hLib);
		}
//		if(!FindNextFile(hFindFiles,&FindData))
//			break;
	} while(FindNextFile(hFindFiles,&FindData));
	FindClose(hFindFiles);
	SetCurrentDirectory(szCurDir);
	return idx;
}

int GetBaseModules()
{
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir)/sizeof(TCHAR), szCurDir);
	CString sCurFullPath = szCurDir;
	sCurFullPath += _T("\\");
//	sCurFullPath += strDevsPath;
	SetCurrentDirectory(sCurFullPath);
//	CString sCurFullPathDll = sCurFullPath;
	sCurFullPath += _T("*.dll");
	WIN32_FIND_DATA FindData;
	HANDLE hFindFiles = FindFirstFile(sCurFullPath,&FindData); 
	if(hFindFiles == INVALID_HANDLE_VALUE)
		return 0;
	int idx = 0;
	do {
//		CString sPath = sCurFullPath;
//		sPath += FindData.cFileName; 
//		HINSTANCE hLib = LoadLibrary(sPath);
		HINSTANCE hLib = LoadLibrary(FindData.cFileName);
		if(hLib)
		{
			BASEMOD_GetInfo_Type* pBASEMOD_GetInfo; 
			BASEMOD_SetProp_Type* pBASEMOD_SetProp; 
			BASEMOD_GetProp_Type* pBASEMOD_GetProp; 
			BASEMOD_DlgProp_Type* pBASEMOD_DlgProp; 
			BASEMOD_Close_Type*	pBASEMOD_Close;

			pBASEMOD_GetInfo = (BASEMOD_GetInfo_Type*)GetProcAddress( hLib, _T("BASEMOD_GetInfo"));
			pBASEMOD_Close = (BASEMOD_Close_Type*)GetProcAddress( hLib, _T("BASEMOD_Close"));
			pBASEMOD_SetProp = (BASEMOD_SetProp_Type*)GetProcAddress( hLib, _T("BASEMOD_SetProperty"));
			pBASEMOD_GetProp = (BASEMOD_GetProp_Type*)GetProcAddress( hLib, _T("BASEMOD_GetProperty"));
			pBASEMOD_DlgProp = (BASEMOD_DlgProp_Type*)GetProcAddress( hLib, _T("BASEMOD_DialogProperty"));
/*			pBASEMOD_GetInfo = (BASEMOD_GetInfo_Type*)GetProcAddress( hLib, "BASEMOD_GetInfo");
			if(pBASEMOD_GetInfo == 0)
				AfxMessageBox( "BASEMOD_GetInfo = 0", MB_OK|MB_ICONINFORMATION, 0);
			pBASEMOD_Close = (BASEMOD_Close_Type*)GetProcAddress( hLib, "BASEMOD_Close");
			if(pBASEMOD_Close == 0)
				AfxMessageBox( "BASEMOD_Close = 0", MB_OK|MB_ICONINFORMATION, 0);
			pBASEMOD_SetProp = (BASEMOD_SetProp_Type*)GetProcAddress( hLib, "BASEMOD_SetProperty");
			if(pBASEMOD_SetProp == 0)
				AfxMessageBox( "BASEMOD_SetProperty = 0", MB_OK|MB_ICONINFORMATION, 0);
			pBASEMOD_GetProp = (BASEMOD_GetProp_Type*)GetProcAddress( hLib, "BASEMOD_GetProperty");
			if(pBASEMOD_GetProp == 0)
				AfxMessageBox( "BASEMOD_GetProperty = 0", MB_OK|MB_ICONINFORMATION, 0);
			pBASEMOD_DlgProp = (BASEMOD_DlgProp_Type*)GetProcAddress( hLib, "BASEMOD_DialogProperty");
			if(pBASEMOD_DlgProp == 0)
				AfxMessageBox( "BASEMOD_DialogProperty = 0", MB_OK|MB_ICONINFORMATION, 0);*/
			if(pBASEMOD_GetInfo && pBASEMOD_SetProp && pBASEMOD_GetProp && pBASEMOD_DlgProp && pBASEMOD_Close)
			{
//				AfxMessageBox( FindData.cFileName, MB_OK|MB_ICONINFORMATION, 0);
				for(int i = 0; idx < MAXBASEMODS; idx++, i++)
				{
//					int devNum = idx;
					int devNum = i;
					BASEMOD_INFO DevInfo;
					DevInfo.wSize = sizeof(BASEMOD_INFO);
					(pBASEMOD_GetInfo)(&devNum, &DevInfo);
					if(devNum == -1)
						break;
					BaseModCtrl[idx].hLib	 = hLib;
					BaseModCtrl[idx].pGetInfo = pBASEMOD_GetInfo;
					BaseModCtrl[idx].pClose = pBASEMOD_Close;
					BaseModCtrl[idx].pSetProperty = pBASEMOD_SetProp;
					BaseModCtrl[idx].pGetProperty = pBASEMOD_GetProp;
					BaseModCtrl[idx].pDlgProperty = pBASEMOD_DlgProp;

					BaseModCtrl[idx].devInfo.wSize = sizeof(BASEMOD_INFO);
					BaseModCtrl[idx].devInfo.pCfgMem = DevInfo.pCfgMem;
					BaseModCtrl[idx].devInfo.dCfgMemSize = DevInfo.dCfgMemSize;
					BaseModCtrl[idx].devInfo.dType = DevInfo.dType;
					lstrcpy(BaseModCtrl[idx].devInfo.sName, DevInfo.sName);
				}
			}
			else
				FreeLibrary(hLib);
		}
//		if(!FindNextFile(hFindFiles,&FindData))
//			break;
	} while(FindNextFile(hFindFiles,&FindData));
	FindClose(hFindFiles);
	SetCurrentDirectory(szCurDir);
	return idx;
}

int GetSubmodules()
{
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir)/sizeof(TCHAR), szCurDir);
	CString sCurFullPath = szCurDir;
	sCurFullPath += _T("\\");
//	sCurFullPath += strDevsPath;
	SetCurrentDirectory(sCurFullPath);
//	CString sCurFullPathDll = sCurFullPath;
	sCurFullPath += _T("*.dll");
	WIN32_FIND_DATA FindData;
	HANDLE hFindFiles = FindFirstFile(sCurFullPath,&FindData); 
	if(hFindFiles == INVALID_HANDLE_VALUE)
		return 0;
	int idx = 0;
	do {
//		CString sPath = sCurFullPath;
//		sPath += FindData.cFileName; 
//		HINSTANCE hLib = LoadLibrary(sPath);
		HINSTANCE hLib = LoadLibrary(FindData.cFileName);
		if(hLib)
		{
			SUBMOD_GetInfo_Type* pSUBMOD_GetInfo; 
			SUBMOD_SetProp_Type* pSUBMOD_SetProp; 
			SUBMOD_GetProp_Type* pSUBMOD_GetProp; 
			SUBMOD_DlgProp_Type* pSUBMOD_DlgProp; 
			SUBMOD_Close_Type*	pSUBMOD_Close;

			pSUBMOD_GetInfo = (SUBMOD_GetInfo_Type*)GetProcAddress( hLib, _T("SUBMOD_GetInfo"));
			pSUBMOD_Close = (SUBMOD_Close_Type*)GetProcAddress( hLib, _T("SUBMOD_Close"));
			pSUBMOD_SetProp = (SUBMOD_SetProp_Type*)GetProcAddress( hLib, _T("SUBMOD_SetProperty"));
			pSUBMOD_GetProp = (SUBMOD_GetProp_Type*)GetProcAddress( hLib, _T("SUBMOD_GetProperty"));
			pSUBMOD_DlgProp = (SUBMOD_DlgProp_Type*)GetProcAddress( hLib, _T("SUBMOD_DialogProperty"));
			if(pSUBMOD_GetInfo && pSUBMOD_SetProp && pSUBMOD_GetProp && pSUBMOD_DlgProp && pSUBMOD_Close)
			{
				for(int i = 0; idx < MAXSUBMODS; idx++, i++)
				{
//					int devNum = idx;
					int devNum = i;
					SUBMOD_INFO DevInfo;
					DevInfo.Size = sizeof(SUBMOD_INFO);
					(pSUBMOD_GetInfo)(&devNum, &DevInfo);
					if(devNum == -1)
						break;
					SubmodCtrl[idx].hLib	 = hLib;
					SubmodCtrl[idx].pGetInfo = pSUBMOD_GetInfo;
					SubmodCtrl[idx].pClose = pSUBMOD_Close;
					SubmodCtrl[idx].pSetProperty = pSUBMOD_SetProp;
					SubmodCtrl[idx].pGetProperty = pSUBMOD_GetProp;
					SubmodCtrl[idx].pDlgProperty = pSUBMOD_DlgProp;

					SubmodCtrl[idx].devInfo.Size = sizeof(SUBMOD_INFO);
					SubmodCtrl[idx].devInfo.pCfgMem = DevInfo.pCfgMem;
					SubmodCtrl[idx].devInfo.CfgMemSize = DevInfo.CfgMemSize;
					SubmodCtrl[idx].devInfo.Type = DevInfo.Type;
					lstrcpy(SubmodCtrl[idx].devInfo.Name, DevInfo.Name);
				}
			}
			else
				FreeLibrary(hLib);
		}
//		if(!FindNextFile(hFindFiles,&FindData))
//			break;
	} while(FindNextFile(hFindFiles,&FindData));
	FindClose(hFindFiles);
	SetCurrentDirectory(szCurDir);
	return idx;
}

