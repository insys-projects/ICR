// IcrAds3224k195cPci.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAds3224k195cPciApp.h"    

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAds3224k195cPci.h"

const U16 DIOPLD_CFG_TAG	= 0x0520; // tag of DIO PLD configuration structure

// ������������� ���������������� ��������
ICR_CfgAds3224k195cPci m_Ads3224k195cPciCfg = { 
	Ads3224k195cPci_CFG_TAG, 
	20, 
	1, 
	300, 
	100000000, 
	0, 
	1, 
	1, 
	0, 
	0, 
};
ICR_CfgHostPld m_HostPldCfg = {HOSTPLD_CFG_TAG, 7, 1, 5, 100, 456, 5};
ICR_CfgHostPld m_DioPldCfg = {DIOPLD_CFG_TAG, 7, 1, 4, 1000, 456, 5};

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

// CIcrAds3224k195cPciApp

BEGIN_MESSAGE_MAP(CIcrAds3224k195cPciApp, CWinApp)
END_MESSAGE_MAP()


// CIcrAds3224k195cPciApp construction

CIcrAds3224k195cPciApp::CIcrAds3224k195cPciApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAds3224k195cPciApp object

CIcrAds3224k195cPciApp theApp;


// CIcrAds3224k195cPciApp initialization

BOOL CIcrAds3224k195cPciApp::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADS3224K195CPCI"));
		pDevInfo->dType = ADS3224K195CPCI;
		break;
	default:
		*pNumDev = -1;
		return;
	}
	pDevInfo->pCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];
	pDevInfo->nCfgMemSize = BASEMOD_CFGMEM_SIZE;
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
		case DIOPLD_CFG_TAG:
			{
				PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
				m_DioPldCfg.wTag = pPldCfg->wTag;
				m_DioPldCfg.wSize = pPldCfg->wSize;
				m_DioPldCfg.bNumber = pPldCfg->bNumber;
				m_DioPldCfg.bType = pPldCfg->bType;
				m_DioPldCfg.wVolume = pPldCfg->wVolume;
				m_DioPldCfg.wPins = pPldCfg->wPins;
				m_DioPldCfg.bSpeedGrade = pPldCfg->bSpeedGrade;
				size = sizeof(ICR_CfgHostPld);
				RealCfgSize += size;
				break;
			}
		case Ads3224k195cPci_CFG_TAG:
			{
				PICR_CfgAds3224k195cPci pDspCfg = (PICR_CfgAds3224k195cPci)pCurCfgMem;
				m_Ads3224k195cPciCfg.wTag = pDspCfg->wTag;
				m_Ads3224k195cPciCfg.wSize = pDspCfg->wSize;
				m_Ads3224k195cPciCfg.bAdmIfCnt = pDspCfg->bAdmIfCnt;
				m_Ads3224k195cPciCfg.wMaxCpuClock = pDspCfg->wMaxCpuClock;
				m_Ads3224k195cPciCfg.dBusClock = pDspCfg->dBusClock;
				m_Ads3224k195cPciCfg.dSizeOfSDRAM = pDspCfg->dSizeOfSDRAM;
				m_Ads3224k195cPciCfg.bHostPldCnt = pDspCfg->bHostPldCnt;
				m_Ads3224k195cPciCfg.bDioPldCnt = pDspCfg->bDioPldCnt;
				m_Ads3224k195cPciCfg.wSDRCON = pDspCfg->wSDRCON;
				m_Ads3224k195cPciCfg.bTypeOfLinks = pDspCfg->bTypeOfLinks;
				pDeviceInfo->bAdmIfCnt = pDspCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAds3224k195cPci);
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
	pDeviceInfo->nRealCfgSize = RealCfgSize;
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

	m_Ads3224k195cPciCfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAds3224k195cPci pDspCfg = (PICR_CfgAds3224k195cPci)pCurCfgMem;
	pDspCfg->wTag = Ads3224k195cPci_CFG_TAG;
	pDspCfg->wSize = sizeof(ICR_CfgAds3224k195cPci) - 4;
	pDspCfg->bAdmIfCnt = m_Ads3224k195cPciCfg.bAdmIfCnt;
	pDspCfg->wMaxCpuClock = m_Ads3224k195cPciCfg.wMaxCpuClock;
	pDspCfg->dBusClock = m_Ads3224k195cPciCfg.dBusClock;
	pDspCfg->dSizeOfSDRAM = m_Ads3224k195cPciCfg.dSizeOfSDRAM;
	pDspCfg->bHostPldCnt = m_Ads3224k195cPciCfg.bHostPldCnt;
	pDspCfg->bDioPldCnt = m_Ads3224k195cPciCfg.bDioPldCnt;
	pDspCfg->wSDRCON = m_Ads3224k195cPciCfg.wSDRCON;
	pDspCfg->bTypeOfLinks = m_Ads3224k195cPciCfg.bTypeOfLinks;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAds3224k195cPci));
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
	if(pDspCfg->bDioPldCnt)
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
	// ��� ��������� ������ �� ����� (��� ����� �������� ���������)
//	*pSignSize = END_TAG;
//	pSignSize++;
	pDeviceInfo->nRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

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


	CIcrAds3224k195cPciDlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_MaxCpuClock = m_Ads3224k195cPciCfg.wMaxCpuClock;
	dlg.m_BusClock = m_Ads3224k195cPciCfg.dBusClock / 1000000.;
	dlg.m_SdramSize = m_Ads3224k195cPciCfg.dSizeOfSDRAM;
	dlg.m_HostPldCnt = m_Ads3224k195cPciCfg.bHostPldCnt;
	dlg.m_DioPldCnt = m_Ads3224k195cPciCfg.bDioPldCnt;
	dlg.m_SDRCON = m_Ads3224k195cPciCfg.wSDRCON;
	dlg.m_TypeOfLinks = m_Ads3224k195cPciCfg.bTypeOfLinks;

	dlg.m_PldNum = m_HostPldCfg.bNumber;
	dlg.m_PldType = m_HostPldCfg.bType;
	dlg.m_PldVolume = m_HostPldCfg.wVolume;
	dlg.m_PldPins = m_HostPldCfg.wPins;
	dlg.m_PldRate = m_HostPldCfg.bSpeedGrade;

	dlg.m_DioPldNum = m_DioPldCfg.bNumber;
	dlg.m_DioPldType = m_DioPldCfg.bType;
	dlg.m_DioPldVol = m_DioPldCfg.wVolume;
	dlg.m_DioPldPins = m_DioPldCfg.wPins;
	dlg.m_DioPldRate = m_DioPldCfg.bSpeedGrade;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Ads3224k195cPciCfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Ads3224k195cPciCfg.dBusClock = DWORD(dlg.m_BusClock * 1000000.);
		m_Ads3224k195cPciCfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Ads3224k195cPciCfg.bHostPldCnt = dlg.m_HostPldCnt;
		m_Ads3224k195cPciCfg.bDioPldCnt = dlg.m_DioPldCnt;
		m_Ads3224k195cPciCfg.wSDRCON = dlg.m_SDRCON;
		m_Ads3224k195cPciCfg.bTypeOfLinks = dlg.m_TypeOfLinks;

		m_HostPldCfg.bNumber = dlg.m_PldNum;
		m_HostPldCfg.bType = dlg.m_PldType;
		m_HostPldCfg.wVolume = dlg.m_PldVolume;
		m_HostPldCfg.wPins = dlg.m_PldPins;
		m_HostPldCfg.bSpeedGrade = dlg.m_PldRate;

		m_DioPldCfg.bNumber = dlg.m_DioPldNum;
		m_DioPldCfg.bType = dlg.m_DioPldType;
		m_DioPldCfg.wVolume = dlg.m_DioPldVol;
		m_DioPldCfg.wPins = dlg.m_DioPldPins;
		m_DioPldCfg.bSpeedGrade = dlg.m_DioPldRate;

	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
