// IcrAdp201P4.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAdp201P4App.h"    

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ ������, ���������� ��� ������������
// (������������ ������ ����, ���������������� �� ������)
#define BASEMOD_CFGMEM_SIZE 128+256

#include "icr.h"

#include "IcrAdp201P4.h"


// ������������� ���������������� ��������
ICR_CfgAdp201P4 m_Adp201P4Cfg = { 
	Adp201P4_CFG_TAG, 
	20, 
	1, 
	500, 
	100000000, 
	0, 
	1, 
	0xF, 
	0xF,
	13,
	9,
	1,
	6
};
ICR_CfgHostPld m_HostPldCfg = {HOSTPLD_CFG_TAG, 7, 1, 5, 300, 456, 5};

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

// CIcrAdp201P4App

BEGIN_MESSAGE_MAP(CIcrAdp201P4App, CWinApp)
END_MESSAGE_MAP()


// CIcrAdp201P4App construction

CIcrAdp201P4App::CIcrAdp201P4App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAdp201P4App object

CIcrAdp201P4App theApp;


// CIcrAdp201P4App initialization

BOOL CIcrAdp201P4App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("Adp201P4"));
		pDevInfo->dType = ADP201P4;
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
		case Adp201P4_CFG_TAG:
			{
				PICR_CfgAdp201P4 pDspCfg = (PICR_CfgAdp201P4)pCurCfgMem;
				m_Adp201P4Cfg.wTag = pDspCfg->wTag;
				m_Adp201P4Cfg.wSize = pDspCfg->wSize;
				m_Adp201P4Cfg.bAdmIfCnt = pDspCfg->bAdmIfCnt;
				m_Adp201P4Cfg.wMaxCpuClock = pDspCfg->wMaxCpuClock;
				m_Adp201P4Cfg.dBusClock = pDspCfg->dBusClock;
				m_Adp201P4Cfg.dSizeOfSDRAM = pDspCfg->dSizeOfSDRAM;
				m_Adp201P4Cfg.bHostPldCnt = pDspCfg->bHostPldCnt;
//				m_Adp201P4Cfg.wSDRCON = pDspCfg->wSDRCON;
				m_Adp201P4Cfg.wCpuMask = pDspCfg->wCpuMask;
				m_Adp201P4Cfg.wSdramMask = pDspCfg->wSdramMask;

				m_Adp201P4Cfg.wSDRAM_RAS = pDspCfg->wSDRAM_RAS;
				m_Adp201P4Cfg.wSDRAM_CAS = pDspCfg->wSDRAM_CAS;
				m_Adp201P4Cfg.wSDRAM_BANK = pDspCfg->wSDRAM_BANK;
				m_Adp201P4Cfg.wSDRAM_CL = pDspCfg->wSDRAM_CL;

				pDeviceInfo->bAdmIfCnt = pDspCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAdp201P4);
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

	m_Adp201P4Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAdp201P4 pDspCfg = (PICR_CfgAdp201P4)pCurCfgMem;
	pDspCfg->wTag = Adp201P4_CFG_TAG;
	pDspCfg->wSize = sizeof(ICR_CfgAdp201P4) - 4;
	pDspCfg->bAdmIfCnt = m_Adp201P4Cfg.bAdmIfCnt;
	pDspCfg->wMaxCpuClock = m_Adp201P4Cfg.wMaxCpuClock;
	pDspCfg->dBusClock = m_Adp201P4Cfg.dBusClock;
	pDspCfg->dSizeOfSDRAM = m_Adp201P4Cfg.dSizeOfSDRAM;
	pDspCfg->bHostPldCnt = m_Adp201P4Cfg.bHostPldCnt;
//	pDspCfg->wSDRCON = m_Adp201P4Cfg.wSDRCON;
	pDspCfg->wCpuMask = m_Adp201P4Cfg.wCpuMask;
	pDspCfg->wSdramMask = m_Adp201P4Cfg.wSdramMask;

	pDspCfg->wSDRAM_RAS = m_Adp201P4Cfg.wSDRAM_RAS;
	pDspCfg->wSDRAM_CAS = m_Adp201P4Cfg.wSDRAM_CAS;
	pDspCfg->wSDRAM_BANK = m_Adp201P4Cfg.wSDRAM_BANK;
	pDspCfg->wSDRAM_CL = m_Adp201P4Cfg.wSDRAM_CL;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdp201P4));
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


	CIcrAdp201P4Dlg dlg;

	dlg.m_MaxCpuClock = m_Adp201P4Cfg.wMaxCpuClock;
	dlg.m_BusClock = m_Adp201P4Cfg.dBusClock / 1000000.;
	dlg.m_SdramSize = m_Adp201P4Cfg.dSizeOfSDRAM;
	dlg.m_HostPldCnt = m_Adp201P4Cfg.bHostPldCnt;
//	dlg.m_SDRCON = m_Adp201P4Cfg.wSDRCON;
	dlg.m_CpuMask = m_Adp201P4Cfg.wCpuMask;
	dlg.m_SdramMask = m_Adp201P4Cfg.wSdramMask;

	dlg.m_sdramRAS = m_Adp201P4Cfg.wSDRAM_RAS;
	dlg.m_sdramCAS = m_Adp201P4Cfg.wSDRAM_CAS;
	dlg.m_sdramBANK = m_Adp201P4Cfg.wSDRAM_BANK;
	dlg.m_sdramCL = m_Adp201P4Cfg.wSDRAM_CL;

	dlg.m_PldNum = m_HostPldCfg.bNumber;
	dlg.m_PldType = m_HostPldCfg.bType;
	dlg.m_PldVolume = m_HostPldCfg.wVolume;
	dlg.m_PldPins = m_HostPldCfg.wPins;
	dlg.m_PldRate = m_HostPldCfg.bSpeedGrade;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp201P4Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp201P4Cfg.dBusClock = DWORD(dlg.m_BusClock * 1000000.);
		m_Adp201P4Cfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Adp201P4Cfg.bHostPldCnt = dlg.m_HostPldCnt;
//		m_Adp201P4Cfg.wSDRCON = dlg.m_SDRCON;
		m_Adp201P4Cfg.wCpuMask = dlg.m_CpuMask;
		m_Adp201P4Cfg.wSdramMask = dlg.m_SdramMask;

		m_Adp201P4Cfg.wSDRAM_RAS = dlg.m_sdramRAS;
		m_Adp201P4Cfg.wSDRAM_CAS = dlg.m_sdramCAS;
		m_Adp201P4Cfg.wSDRAM_BANK = dlg.m_sdramBANK;
		m_Adp201P4Cfg.wSDRAM_CL = dlg.m_sdramCL;

		m_HostPldCfg.bNumber = dlg.m_PldNum;
		m_HostPldCfg.bType = dlg.m_PldType;
		m_HostPldCfg.wVolume = dlg.m_PldVolume;
		m_HostPldCfg.wPins = dlg.m_PldPins;
		m_HostPldCfg.bSpeedGrade = dlg.m_PldRate;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}

