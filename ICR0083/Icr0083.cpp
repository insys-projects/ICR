// Icr0083.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr0083App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr0083.h"

ICR_CfgAdc m_AdcCfg = { ADC_CFG_TAG, 14, 0, 0, 12, 1, 1000, 1000000, 500};

ICR_CfgAdm m_AdmCfg = { ADM_CFG_TAG, 14, 0, 60000000, 50000000, 40000000, 2};

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

// CIcr0083App

BEGIN_MESSAGE_MAP(CIcr0083App, CWinApp)
END_MESSAGE_MAP()


// CIcr0083App construction

CIcr0083App::CIcr0083App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr0083App object

CIcr0083App theApp;


// CIcr0083App initialization

BOOL CIcr0083App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//***************************************************************************************
SUBMOD_API void __stdcall SUBMOD_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo)
{
	int curNum = *pNumDev;
	switch(curNum)
	{
	case 0:
		lstrcpy(pDevInfo->sName, _T("ADM212x10M"));
		pDevInfo->Type = ADM212x10M;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("ADM212x25M"));
		pDevInfo->Type = ADM212x25M;
		break;
	case 2:
		lstrcpy(pDevInfo->sName, _T("ADM212x40M"));
		pDevInfo->Type = ADM212x40M;
		break;
	case 3:
		lstrcpy(pDevInfo->sName, _T("ADM212x50M"));
		pDevInfo->Type = ADM212x50M;
		break;
	case 4:
		lstrcpy(pDevInfo->sName, _T("ADM212x60M"));
		pDevInfo->Type = ADM212x60M;
		break;
	case 5:
		lstrcpy(pDevInfo->sName, _T("ADM212x100M"));
		pDevInfo->Type = ADM212x100M;
		break;
	case 6:
		lstrcpy(pDevInfo->sName, _T("ADM214x60M"));
		pDevInfo->Type = ADM214x60M;
		break;
	case 7:
		lstrcpy(pDevInfo->sName, _T("ADM214x100M"));
		pDevInfo->Type = ADM214x100M;
		break;
	case 8:
		lstrcpy(pDevInfo->sName, _T("ADM414x65M"));
		pDevInfo->Type = ADM414x65M;
		break;
	case 9:
		lstrcpy(pDevInfo->sName, _T("ADM216x100M"));
		pDevInfo->Type = ADM216x100M;
		break;
	default:
		*pNumDev = -1;
		return;
	}
	pDevInfo->pCfgMem = new UCHAR[SUBMOD_CFGMEM_SIZE];
	pDevInfo->nCfgMemSize = SUBMOD_CFGMEM_SIZE;
}

//***************************************************************************************
SUBMOD_API void __stdcall SUBMOD_Close(PSUBMOD_INFO pDevInfo)
{
	delete[] pDevInfo->pCfgMem;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_SetProperty(PSUBMOD_INFO pDeviceInfo)
{
	ULONG RealCfgSize = 0;
	PVOID pAdmCfgMem = (PVOID)pDeviceInfo->pCfgMem;
	PVOID pEndAdmCfgMem = (PVOID)((UCHAR*)pAdmCfgMem + SUBMOD_CFGMEM_SIZE);
	int end_flag = 0;
	do
	{
		USHORT tag = *((USHORT*)pAdmCfgMem);
		USHORT size = 0;
		switch(tag)
		{
		case END_TAG:
		case ALT_END_TAG:
		default: 
			end_flag = 1;
			RealCfgSize += 2;
			break;
		case ADC_CFG_TAG:
			{
				PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pAdmCfgMem;
				m_AdcCfg.wTag = pAdcCfg->wTag;
				m_AdcCfg.wSize = pAdcCfg->wSize;
				m_AdcCfg.bNumber = pAdcCfg->bNumber;
				m_AdcCfg.bAdmNum = pAdcCfg->bAdmNum;
				m_AdcCfg.bBits = pAdcCfg->bBits;
				m_AdcCfg.bEncoding = pAdcCfg->bEncoding;
				m_AdcCfg.dMinRate = pAdcCfg->dMinRate;
				m_AdcCfg.dMaxRate = pAdcCfg->dMaxRate;
				m_AdcCfg.wRange = pAdcCfg->wRange;
				size = sizeof(ICR_CfgAdc);
				RealCfgSize += size;
				break;
			}
		case ADM_CFG_TAG:
			{
				PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pAdmCfgMem;
				m_AdmCfg.wTag = pAdmCfg->wTag;
				m_AdmCfg.wSize = pAdmCfg->wSize;
				m_AdmCfg.bAdmIfNum = pAdmCfg->bAdmIfNum;
				m_AdmCfg.dGen[0] = pAdmCfg->dGen[0];
				m_AdmCfg.dGen[1] = pAdmCfg->dGen[1];
				m_AdmCfg.dGen[2] = pAdmCfg->dGen[2];
				m_AdmCfg.bAdcCnt = pAdmCfg->bAdcCnt;
				size = sizeof(ICR_CfgAdm);
				RealCfgSize += size;
				break;
			}
		}
		pAdmCfgMem = (UCHAR*)pAdmCfgMem + size;
	} while(!end_flag && pAdmCfgMem < pEndAdmCfgMem);
	pDeviceInfo->nRealCfgSize = RealCfgSize;
	return 0;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_GetProperty(PSUBMOD_INFO pDeviceInfo)
{
	USHORT* pEndCfgMem = (USHORT*)(pDeviceInfo->pCfgMem) + SUBMOD_CFGMEM_SIZE/2;

	USHORT* pCurCfgMem = (USHORT*)pDeviceInfo->pCfgMem;
	PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pCurCfgMem;
	pAdmCfg->wTag = ADM_CFG_TAG;
	pAdmCfg->wSize = sizeof(ICR_CfgAdm) - 4;
	pAdmCfg->bAdmIfNum = 0;//m_AdcCfg.AdmNumber;
	pAdmCfg->dGen[0] = m_AdmCfg.dGen[0];
	pAdmCfg->dGen[1] = m_AdmCfg.dGen[1];
	pAdmCfg->dGen[2] = m_AdmCfg.dGen[2];
	pAdmCfg->bAdcCnt = m_AdmCfg.bAdcCnt;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdm));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pCurCfgMem;
	pAdcCfg->wTag = ADC_CFG_TAG;
	pAdcCfg->wSize = sizeof(ICR_CfgAdc) - 4;
	pAdcCfg->bNumber = 0;
	pAdcCfg->bAdmNum = 0;//m_AdcCfg.AdmNumber;
	pAdcCfg->bBits = m_AdcCfg.bBits;
	pAdcCfg->bEncoding = m_AdcCfg.bEncoding;
	pAdcCfg->dMinRate = m_AdcCfg.dMinRate;
	pAdcCfg->dMaxRate = m_AdcCfg.dMaxRate;
	pAdcCfg->wRange = m_AdcCfg.wRange;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdc));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;
	*pCurCfgMem = END_TAG;
	pCurCfgMem++;
	pDeviceInfo->nRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_DialogProperty(PSUBMOD_INFO pDeviceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

//	int curNum = pDeviceInfo->Number;

	CIcr0083Dlg dlg;
	lstrcpy(dlg.subInfo.sName, pDeviceInfo->sName);
	dlg.subInfo.Type = pDeviceInfo->Type;

	switch(m_AdcCfg.bBits)
	{
		case 12:
			dlg.m_AdcBits = 0;
			break;
		case 14:
			dlg.m_AdcBits = 1;
			break;
		case 16:
			dlg.m_AdcBits = 2;
			break;
	}
	dlg.m_AdcEncoding = m_AdcCfg.bEncoding;
	dlg.m_AdcRange = m_AdcCfg.wRange;
	dlg.m_AdcRateMax = m_AdcCfg.dMaxRate;
	dlg.m_AdcRateMin = m_AdcCfg.dMinRate;
	dlg.m_NumOfAdc = m_AdmCfg.bAdcCnt;
	dlg.m_Gen1 = m_AdmCfg.dGen[0];
	dlg.m_Gen2 = m_AdmCfg.dGen[1];
	dlg.m_Gen3 = m_AdmCfg.dGen[2];

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		switch(dlg.m_AdcBits)
		{
			case 0:
				m_AdcCfg.bBits = 12;
				break;
			case 1:
				m_AdcCfg.bBits = 14;
				break;
			case 2:
				m_AdcCfg.bBits = 16;
				break;
		}
		m_AdcCfg.bEncoding = dlg.m_AdcEncoding;
		m_AdcCfg.wRange = dlg.m_AdcRange;
		m_AdcCfg.dMaxRate = dlg.m_AdcRateMax;
		m_AdcCfg.dMinRate = dlg.m_AdcRateMin;
//		m_AdcCfg.Number = ;
		m_AdmCfg.bAdcCnt = dlg.m_NumOfAdc;
		m_AdmCfg.dGen[0] = dlg.m_Gen1;
		m_AdmCfg.dGen[1] = dlg.m_Gen2;
		m_AdmCfg.dGen[2] = dlg.m_Gen3;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}
