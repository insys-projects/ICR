// Icr6713.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr6713App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ ������, ���������� ��� ������������
// (������������ ������ ����, ���������������� �� ������)
#define BASEMOD_CFGMEM_SIZE 128+256

#include "icr.h"

#include "Icr6713.h"

// ������������� ���������������� ��������
ICR_Cfg6713		m_Adp6713Cfg = {ADP6713_CFG_TAG, 14, 1, 0, 0, 0, 1};
//ICR_CfgHostPld	m_HostPldCfg  = {HOSTPLD_CFG_TAG, 7, 0, 6, 300, 456, 7};

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


// CIcr6713App

BEGIN_MESSAGE_MAP(CIcr6713App, CWinApp)
END_MESSAGE_MAP()


// CIcr6713App construction

CIcr6713App::CIcr6713App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr6713App object

CIcr6713App theApp;


// CIcr6713App initialization

BOOL CIcr6713App::InitInstance()
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
		lstrcpy(pDevInfo->sName, "6713");
		pDevInfo->dType = ADP6713;
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
		//case HOSTPLD_CFG_TAG:
		//	{
		//		PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
		//		m_HostPldCfg.wTag = pPldCfg->wTag;
		//		m_HostPldCfg.wSize = pPldCfg->wSize;
		//		m_HostPldCfg.bNumber = pPldCfg->bNumber;
		//		m_HostPldCfg.bType = pPldCfg->bType;
		//		m_HostPldCfg.wVolume = pPldCfg->wVolume;
		//		m_HostPldCfg.wPins = pPldCfg->wPins;
		//		m_HostPldCfg.bSpeedGrade = pPldCfg->bSpeedGrade;
		//		size = sizeof(ICR_CfgHostPld);
		//		RealCfgSize += size;
		//		break;
		//	}
		case ADP6713_CFG_TAG:
			{
				PICR_Cfg6713 pAdpCfg = (PICR_Cfg6713)pCurCfgMem;
				m_Adp6713Cfg.wTag = pAdpCfg->wTag;
				m_Adp6713Cfg.wSize = pAdpCfg->wSize;
				m_Adp6713Cfg.bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				m_Adp6713Cfg.dSizeOfSDRAM = pAdpCfg->dSizeOfSDRAM;
				m_Adp6713Cfg.dSizeOfFlash = pAdpCfg->dSizeOfFlash;
				m_Adp6713Cfg.dSizeOfPLDSRAM = pAdpCfg->dSizeOfPLDSRAM;
				m_Adp6713Cfg.bHostPldCnt = pAdpCfg->bHostPldCnt;
				pDeviceInfo->bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				size = sizeof(ICR_Cfg6713);
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

	m_Adp6713Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_Cfg6713 pAdpCfg = (PICR_Cfg6713)pCurCfgMem;
	pAdpCfg->wTag = ADP6713_CFG_TAG;
	pAdpCfg->wSize = sizeof(ICR_Cfg6713) - 4;
	pAdpCfg->bAdmIfCnt = m_Adp6713Cfg.bAdmIfCnt;
	pAdpCfg->dSizeOfSDRAM = m_Adp6713Cfg.dSizeOfSDRAM;
	pAdpCfg->dSizeOfFlash = m_Adp6713Cfg.dSizeOfFlash;
	pAdpCfg->dSizeOfPLDSRAM = m_Adp6713Cfg.dSizeOfPLDSRAM;
	pAdpCfg->bHostPldCnt = m_Adp6713Cfg.bHostPldCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_Cfg6713));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	//if(pAdpCfg->bHostPldCnt)
	//{
	//	for(int i = 0; i < pAdpCfg->bHostPldCnt; i++)
	//	{
	//		PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
	//		pPldCfg->wTag = HOSTPLD_CFG_TAG;
	//		pPldCfg->wSize = sizeof(ICR_CfgHostPld) - 4;
	//		pPldCfg->bNumber = 0;
	//		pPldCfg->bType = m_HostPldCfg.bType;
	//		pPldCfg->wVolume = m_HostPldCfg.wVolume;
	//		pPldCfg->wPins = m_HostPldCfg.wPins;
	//		pPldCfg->bSpeedGrade = m_HostPldCfg.bSpeedGrade;

	//		pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgHostPld));
	//		if(pCurCfgMem >= pEndCfgMem)
	//			return 1;
	//	}
	//}
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

	Icr6713Dlg dlg;

	dlg.m_SdramSize = m_Adp6713Cfg.dSizeOfSDRAM;
	dlg.m_FlashSize = m_Adp6713Cfg.dSizeOfFlash;
	dlg.m_PldSramSize = m_Adp6713Cfg.dSizeOfPLDSRAM;
	dlg.m_HostPldCnt = m_Adp6713Cfg.bHostPldCnt;

	//dlg.m_PldNum = m_HostPldCfg.bNumber;
	//dlg.m_PldType = m_HostPldCfg.bType;
	//dlg.m_PldVolume = m_HostPldCfg.wVolume;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp6713Cfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Adp6713Cfg.dSizeOfFlash = dlg.m_FlashSize;
		m_Adp6713Cfg.dSizeOfPLDSRAM = dlg.m_PldSramSize;
		m_Adp6713Cfg.bHostPldCnt = dlg.m_HostPldCnt;

		//m_HostPldCfg.bNumber = dlg.m_PldNum;
		//m_HostPldCfg.bType = dlg.m_PldType;
		//m_HostPldCfg.wVolume = dlg.m_PldVolume;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}
