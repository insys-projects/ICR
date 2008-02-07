// IcrAdp101cP1.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAdp101cP1App.h"    

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ ������, ���������� ��� ������������
// (������������ ������ ����, ���������������� �� ������)
#define BASEMOD_CFGMEM_SIZE 128+256

#include "icr.h"

#include "IcrAdp101cP1.h"

// ������������� ���������������� ��������
ICR_CfgAdp101cP1 m_Adp101cP1Cfg = { 
	Adp101cP1_CFG_TAG, 
	12, 
	1, 
	300, 
	100000000, 
	0, 
	1, 
};
ICR_CfgHostPld m_HostPldCfg = {HOSTPLD_CFG_TAG, 7, 1, 5, 100, 456, 5};

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CIcrAdp101cP1App

BEGIN_MESSAGE_MAP(CIcrAdp101cP1App, CWinApp)
END_MESSAGE_MAP()


// CIcrAdp101cP1App construction

CIcrAdp101cP1App::CIcrAdp101cP1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAdp101cP1App object

CIcrAdp101cP1App theApp;


// CIcrAdp101cP1App initialization

BOOL CIcrAdp101cP1App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//***************************************************************************************
//  BASEMOD_GetInfo - ������� ������ ��� ����������� �������������� ������� �������
//  Input:  pNumDev - ��������� �� ����� (������������ ���������������, ������� � 0)
//          pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: pNumDev - ���� -1, �� ������ �������������� ������� ������� ���
//  Notes:  ������ ������� ���������� ������, � ����� � ��������, ������ *pNumDev
//***************************************************************************************
BASEMOD_API void __stdcall BASEMOD_GetInfo(int* pNumDev, PBASEMOD_INFO pDevInfo)
{
	int curNum = *pNumDev;
	switch(curNum)
	{
	case 0:
		lstrcpy(pDevInfo->sName, _T("ADP101CP1"));
		pDevInfo->dType = ADP101cP1;
		break;
	default:
		*pNumDev = -1;
		return;
	}
	pDevInfo->pCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];
	pDevInfo->dCfgMemSize = BASEMOD_CFGMEM_SIZE;
}

//***************************************************************************************
//  BASEMOD_Close - ������� ������ ��� ������������ ������� ������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: 
//  Notes:  ������ ������� ���������� ����� ����������� ������ �������� ���������
//***************************************************************************************
BASEMOD_API void __stdcall BASEMOD_Close(PBASEMOD_INFO pDevInfo)
{
	delete[] pDevInfo->pCfgMem;
}

//***************************************************************************************
//  BASEMOD_SetProperty - ������� ������ ��� �������� �������� �� �������� ��������� � ������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - 
//  Notes:  ������ ������� ���������� ����� ��������� ������ �� ����� ��� ����������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_SetProperty(PBASEMOD_INFO pDeviceInfo)
{
	ULONG RealCfgSize = 0;
	PVOID pCurCfgMem = (PVOID)pDeviceInfo->pCfgMem;
	PVOID pEndCfgMem = (PVOID)(pDeviceInfo->pCfgMem + BASEMOD_CFGMEM_SIZE);
	int end_flag = 0;
	do
	{
		USHORT sign = *((PUSHORT)pCurCfgMem);
		USHORT size = 0;
		switch(sign)
		{
		case END_TAG:
		case ALT_END_TAG:
			end_flag = 1;
			RealCfgSize += 2;
			break;
		case HOSTPLD_CFG_TAG:
			{
				PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
				m_HostPldCfg.wTag = pPldCfg->wTag;
				m_HostPldCfg.wSize = pPldCfg->wSize;
				m_HostPldCfg.bNumber = pPldCfg->bNumber;
				m_HostPldCfg.bType = pPldCfg->bType;
				m_HostPldCfg.wVolume = pPldCfg->wVolume;
				m_HostPldCfg.wPins = pPldCfg->wPins;
				m_HostPldCfg.bSpeedGrade = pPldCfg->bSpeedGrade;
				size = sizeof(ICR_CfgHostPld);
				RealCfgSize += size;
				break;
			}
		case Adp101cP1_CFG_TAG:
			{
				PICR_CfgAdp101cP1 pDspCfg = (PICR_CfgAdp101cP1)pCurCfgMem;
				m_Adp101cP1Cfg.wTag = pDspCfg->wTag;
				m_Adp101cP1Cfg.wSize = pDspCfg->wSize;
				m_Adp101cP1Cfg.bAdmIfCnt = pDspCfg->bAdmIfCnt;
				m_Adp101cP1Cfg.wMaxCpuClock = pDspCfg->wMaxCpuClock;
				m_Adp101cP1Cfg.dBusClock = pDspCfg->dBusClock;
				m_Adp101cP1Cfg.dSizeOfSDRAM = pDspCfg->dSizeOfSDRAM;
				m_Adp101cP1Cfg.bHostPldCnt = pDspCfg->bHostPldCnt;
//				m_Adp101cP1Cfg.wSDRCON = pDspCfg->wSDRCON;
				pDeviceInfo->bAdmIfCnt = pDspCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAdp101cP1);
				RealCfgSize += size;
				break;
			}
		default: 
			end_flag = 1;
			break;
		}
		pCurCfgMem = (PUCHAR)pCurCfgMem + size;
		if(pCurCfgMem >= pEndCfgMem)
			return 1;
	} while(!end_flag && pCurCfgMem < pEndCfgMem);
	pDeviceInfo->dRealCfgSize = RealCfgSize;
	return 0;
}

//***************************************************************************************
//  BASEMOD_SetProperty - ������� ������ ��� �������� �������� �� ������� � �������� ���������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - 0 - ��� ������, 1 - 
//  Notes:  ������ ������� ���������� ����� ������� ������ � ���� ��� ����������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_GetProperty(PBASEMOD_INFO pDeviceInfo)
{
	PUSHORT pCurCfgMem = (PUSHORT)pDeviceInfo->pCfgMem;
	PUSHORT pEndCfgMem = (PUSHORT)(pDeviceInfo->pCfgMem) + BASEMOD_CFGMEM_SIZE/2;

	m_Adp101cP1Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAdp101cP1 pDspCfg = (PICR_CfgAdp101cP1)pCurCfgMem;
	pDspCfg->wTag = Adp101cP1_CFG_TAG;
	pDspCfg->wSize = sizeof(ICR_CfgAdp101cP1) - 4;
	pDspCfg->bAdmIfCnt = m_Adp101cP1Cfg.bAdmIfCnt;
	pDspCfg->wMaxCpuClock = m_Adp101cP1Cfg.wMaxCpuClock;
	pDspCfg->dBusClock = m_Adp101cP1Cfg.dBusClock;
	pDspCfg->dSizeOfSDRAM = m_Adp101cP1Cfg.dSizeOfSDRAM;
	pDspCfg->bHostPldCnt = m_Adp101cP1Cfg.bHostPldCnt;
	//pDspCfg->wSDRCON = m_Adp101cP1Cfg.wSDRCON;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdp101cP1));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pDspCfg->bHostPldCnt)
	{
		for(int i = 0; i < pDspCfg->bHostPldCnt; i++)
		{
			PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
			pPldCfg->wTag = HOSTPLD_CFG_TAG;
			pPldCfg->wSize = sizeof(ICR_CfgHostPld) - 4;
			pPldCfg->bNumber = 0;
			pPldCfg->bType = m_HostPldCfg.bType;
			pPldCfg->wVolume = m_HostPldCfg.wVolume;
			pPldCfg->wPins = m_HostPldCfg.wPins;
			pPldCfg->bSpeedGrade = m_HostPldCfg.bSpeedGrade;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgHostPld));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
/*	if(pDspCfg->bDioPldCnt)
	{
		for(int i = 0; i < pDspCfg->bDioPldCnt; i++)
		{
			PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
			pPldCfg->wTag = DIOPLD_CFG_TAG;
			pPldCfg->wSize = sizeof(ICR_CfgHostPld) - 4;
			pPldCfg->bNumber = 0;
			pPldCfg->bType = m_DioPldCfg.bType;
			pPldCfg->wVolume = m_DioPldCfg.wVolume;
			pPldCfg->wPins = m_DioPldCfg.wPins;
			pPldCfg->bSpeedGrade = m_DioPldCfg.bSpeedGrade;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgHostPld));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
*/
    // ��� ��������� ������ �� ����� (��� ����� �������� ���������)
//	*pSignSize = END_TAG;
//	pSignSize++;
	pDeviceInfo->dRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
//  BASEMOD_DialogProperty - ������� ������ ��� ����������� �������, ������������ �������� �������� ����������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - IDOK ��� IDCANCEL
//  Notes:  ������ ������� ���������� �� ������� �� ��������������� ������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_DialogProperty(PBASEMOD_INFO pDeviceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));


	CIcrAdp101cP1Dlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_MaxCpuClock = m_Adp101cP1Cfg.wMaxCpuClock;
	dlg.m_BusClock = m_Adp101cP1Cfg.dBusClock / 1000000.;
	dlg.m_SdramSize = m_Adp101cP1Cfg.dSizeOfSDRAM;
	dlg.m_HostPldCnt = m_Adp101cP1Cfg.bHostPldCnt;
//	dlg.m_DioPldCnt = m_Adp101cP1Cfg.bDioPldCnt;
//	dlg.m_SDRCON = m_Adp101cP1Cfg.wSDRCON;
//	dlg.m_TypeOfLinks = m_Adp101cP1Cfg.bTypeOfLinks;

	dlg.m_PldNum = m_HostPldCfg.bNumber;
	dlg.m_PldType = m_HostPldCfg.bType;
	dlg.m_PldVolume = m_HostPldCfg.wVolume;
	dlg.m_PldPins = m_HostPldCfg.wPins;
	dlg.m_PldRate = m_HostPldCfg.bSpeedGrade;
/*
	dlg.m_DioPldNum = m_DioPldCfg.bNumber;
	dlg.m_DioPldType = m_DioPldCfg.bType;
	dlg.m_DioPldVol = m_DioPldCfg.wVolume;
	dlg.m_DioPldPins = m_DioPldCfg.wPins;
	dlg.m_DioPldRate = m_DioPldCfg.bSpeedGrade;
*/
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp101cP1Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp101cP1Cfg.dBusClock = DWORD(dlg.m_BusClock * 1000000.);
		m_Adp101cP1Cfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Adp101cP1Cfg.bHostPldCnt = dlg.m_HostPldCnt;
//		m_Adp101cP1Cfg.bDioPldCnt = dlg.m_DioPldCnt;
		//m_Adp101cP1Cfg.wSDRCON = dlg.m_SDRCON;
//		m_Adp101cP1Cfg.bTypeOfLinks = dlg.m_TypeOfLinks;

		m_HostPldCfg.bNumber = dlg.m_PldNum;
		m_HostPldCfg.bType = dlg.m_PldType;
		m_HostPldCfg.wVolume = dlg.m_PldVolume;
		m_HostPldCfg.wPins = dlg.m_PldPins;
		m_HostPldCfg.bSpeedGrade = dlg.m_PldRate;
/*
		m_DioPldCfg.bNumber = dlg.m_DioPldNum;
		m_DioPldCfg.bType = dlg.m_DioPldType;
		m_DioPldCfg.wVolume = dlg.m_DioPldVol;
		m_DioPldCfg.wPins = dlg.m_DioPldPins;
		m_DioPldCfg.bSpeedGrade = dlg.m_DioPldRate;
*/
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
