// Icr64Z4.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr64Z4App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ ������, ���������� ��� ������������
// (������������ ������ ����, ���������������� �� ������)
#define BASEMOD_CFGMEM_SIZE 128+256

#include "icr.h"

#include "Icr64Z4.h"

// ������������� ���������������� ��������
ICR_Cfg64Z4 m_Adp64Z4Cfg = { ADP64Z4_CFG_TAG, 6, 1, 1, 720, 0, 1};

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
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


// CIcr64Z4App

BEGIN_MESSAGE_MAP(CIcr64Z4App, CWinApp)
END_MESSAGE_MAP()


// CIcr64Z4App construction

CIcr64Z4App::CIcr64Z4App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr64Z4App object

CIcr64Z4App theApp;


// CIcr64Z4App initialization

BOOL CIcr64Z4App::InitInstance()
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
		lstrcpy(pDevInfo->sName, "64Z4");
		pDevInfo->dType = ADP64Z4;
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
		case ADP64Z4_CFG_TAG:
			{
				PICR_Cfg64Z4 pAdpCfg = (PICR_Cfg64Z4)pCurCfgMem;
				m_Adp64Z4Cfg.wTag = pAdpCfg->wTag;
				m_Adp64Z4Cfg.wSize = pAdpCfg->wSize;
				m_Adp64Z4Cfg.bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				m_Adp64Z4Cfg.bCpuCnt = pAdpCfg->bCpuCnt;
				m_Adp64Z4Cfg.wMaxCpuClock = pAdpCfg->wMaxCpuClock;
				m_Adp64Z4Cfg.bFlashCnt = pAdpCfg->bFlashCnt;
				pDeviceInfo->bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				size = sizeof(ICR_Cfg64Z4);
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
//  BASEMOD_GetProperty - ������� ������ ��� �������� �������� �� ������� � �������� ���������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - 0 - ��� ������, 1 - 
//  Notes:  ������ ������� ���������� ����� ������� ������ � ���� ��� ����������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_GetProperty(PBASEMOD_INFO pDeviceInfo)
{
	PUSHORT pCurCfgMem = (PUSHORT)pDeviceInfo->pCfgMem;
	PUSHORT pEndCfgMem = (PUSHORT)(pDeviceInfo->pCfgMem) + BASEMOD_CFGMEM_SIZE/2;

	m_Adp64Z4Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_Cfg64Z4 pAdpCfg = (PICR_Cfg64Z4)pCurCfgMem;
	pAdpCfg->wTag = ADP64Z4_CFG_TAG;
	pAdpCfg->wSize = sizeof(ICR_Cfg64Z4) - 4;
	pAdpCfg->bAdmIfCnt = m_Adp64Z4Cfg.bAdmIfCnt;
	pAdpCfg->bCpuCnt = m_Adp64Z4Cfg.bCpuCnt;
	pAdpCfg->wMaxCpuClock = m_Adp64Z4Cfg.wMaxCpuClock;
	pAdpCfg->bFlashCnt = m_Adp64Z4Cfg.bFlashCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_Cfg64Z4));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

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

	Icr64Z4Dlg dlg;

	dlg.m_CpuCnt = m_Adp64Z4Cfg.bCpuCnt;
	dlg.m_MaxCpuClock = m_Adp64Z4Cfg.wMaxCpuClock;
	dlg.m_FlashCnt = m_Adp64Z4Cfg.bFlashCnt;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp64Z4Cfg.bCpuCnt = dlg.m_CpuCnt;
		m_Adp64Z4Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp64Z4Cfg.bFlashCnt = dlg.m_FlashCnt;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}