// Icr0084.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr0084App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr0084.h"

ICR_CfgAdc m_aAdcCfg[10] = {{ ADC_CFG_TAG, 14, 0, 0, 12, 1, 1000, 1000000, 2500},	//ADM1612x1M:
						    { ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 1000000, 500},	//ADM214x1M:
							{ ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 3000000, 500},	//ADM214x3M:
							{ ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 10000000, 500},	//ADM214x10M:
							{ ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 10000000, 500},	//ADM214x10MX:
							{ ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 160000, 500},	//ADM1614x160:
							{ ADC_CFG_TAG, 14, 0, 0, 16, 1, 1000, 250000, 500},	//ADM216x250:
							{ ADC_CFG_TAG, 14, 0, 0, 16, 1, 1000, 2500000, 500},	//ADM216x2M5:
							{ ADC_CFG_TAG, 14, 0, 0, 16, 1, 1000, 200000, 500},	//ADM416x200:
							{ ADC_CFG_TAG, 14, 0, 0, 16, 1, 1000, 48000, 500}		//ADM816x48:
						   };

ICR_CfgAdm m_aAdmCfg[10] = {{ ADM_CFG_TAG, 2, 0, 16},	//ADM1612x1M
							{ ADM_CFG_TAG, 2, 0, 2},	//ADM214x1M:
							{ ADM_CFG_TAG, 2, 0, 2},	//ADM214x3M:
							{ ADM_CFG_TAG, 2, 0, 2},	//ADM214x10M
							{ ADM_CFG_TAG, 2, 0, 2},	//ADM214x10M
							{ ADM_CFG_TAG, 2, 0, 16},	//ADM1614x16
							{ ADM_CFG_TAG, 2, 0, 2},	//ADM216x250
							{ ADM_CFG_TAG, 2, 0, 2},	//ADM216x2M5
							{ ADM_CFG_TAG, 2, 0, 4},	//ADM416x200
							{ ADM_CFG_TAG, 2, 0, 8}		//ADM816x48:
						   };

S32 GetTypeAdm(ICR_ADMType type);

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

// CIcr0084App

BEGIN_MESSAGE_MAP(CIcr0084App, CWinApp)
END_MESSAGE_MAP()


// CIcr0084App construction

CIcr0084App::CIcr0084App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr0084App object

CIcr0084App theApp;


// CIcr0084App initialization

BOOL CIcr0084App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADM1612x1M"));
		pDevInfo->Type = ADM1612x1M;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("ADM214x1M"));
		pDevInfo->Type = ADM214x1M;
		break;
	case 2:
		lstrcpy(pDevInfo->sName, _T("ADM214x3M"));
		pDevInfo->Type = ADM214x3M;
		break;
	case 3:
		lstrcpy(pDevInfo->sName, _T("ADM214x10M"));
		pDevInfo->Type = ADM214x10M;
		break;
	case 4:
		lstrcpy(pDevInfo->sName, _T("ADM214x10MX"));
		pDevInfo->Type = ADM214x10MX;
		break;
	case 5:
		lstrcpy(pDevInfo->sName, _T("ADM1614x160"));
		pDevInfo->Type = ADM1614x160;
		break;
	case 6:
		lstrcpy(pDevInfo->sName, _T("ADM216x250"));
		pDevInfo->Type = ADM216x250;
		break;
	case 7:
		lstrcpy(pDevInfo->sName, _T("ADM216x2.5M"));
		pDevInfo->Type = ADM216x2M5;
		break;
	case 8:
		lstrcpy(pDevInfo->sName, _T("ADM416x200"));
		pDevInfo->Type = ADM416x200;
		break;
	case 9:
		lstrcpy(pDevInfo->sName, _T("ADM816x48"));
		pDevInfo->Type = ADM816x48;
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
SUBMOD_API int __stdcall SUBMOD_SetProperty(PSUBMOD_INFO pDevInfo)
{
	S32   idx = GetTypeAdm(pDevInfo->Type);
	ULONG RealCfgSize = 0;
	PVOID pAdmCfgMem = (PVOID)pDevInfo->pCfgMem;
	PVOID pEndAdmCfgMem = (PVOID)((UCHAR*)pAdmCfgMem + SUBMOD_CFGMEM_SIZE);
	int end_flag = 0;

	if(idx<0)
		idx = 0;

	do
	{
		USHORT sign = *((USHORT*)pAdmCfgMem);
		USHORT size = 0;
		switch(sign)
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
				m_aAdcCfg[idx].wTag = pAdcCfg->wTag;
				m_aAdcCfg[idx].wSize = pAdcCfg->wSize;
				m_aAdcCfg[idx].bNumber = pAdcCfg->bNumber;
				m_aAdcCfg[idx].bAdmNum = pAdcCfg->bAdmNum;
				m_aAdcCfg[idx].bBits = pAdcCfg->bBits;
				m_aAdcCfg[idx].bEncoding = pAdcCfg->bEncoding;
				m_aAdcCfg[idx].dMinRate = pAdcCfg->dMinRate;
				m_aAdcCfg[idx].dMaxRate = pAdcCfg->dMaxRate;
				m_aAdcCfg[idx].wRange = pAdcCfg->wRange;
				size = sizeof(ICR_CfgAdc);
				RealCfgSize += size;
				break;
			}
		case ADM_CFG_TAG:
			{
				PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pAdmCfgMem;
				m_aAdmCfg[idx].wTag = pAdmCfg->wTag;
				m_aAdmCfg[idx].wSize = pAdmCfg->wSize;
				m_aAdmCfg[idx].bAdmIfNum = pAdmCfg->bAdmIfNum;
				m_aAdmCfg[idx].bAdcCnt = pAdmCfg->bAdcCnt;
				size = sizeof(ICR_CfgAdm);
				RealCfgSize += size;
				break;
			}
		}
		pAdmCfgMem = (UCHAR*)pAdmCfgMem + size;
	} while(!end_flag && pAdmCfgMem < pEndAdmCfgMem);
	pDevInfo->nRealCfgSize = RealCfgSize;
	return 0;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_GetProperty(PSUBMOD_INFO pDevInfo)
{
	S32 idx = GetTypeAdm(pDevInfo->Type);
	USHORT* pEndCfgMem = (USHORT*)(pDevInfo->pCfgMem) + SUBMOD_CFGMEM_SIZE/2;

	if(idx<0)
		idx = 0;

	USHORT* pCurCfgMem = (USHORT*)pDevInfo->pCfgMem;
	PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pCurCfgMem;
	pAdmCfg->wTag = ADM_CFG_TAG;
	pAdmCfg->wSize = sizeof(ICR_CfgAdm) - 4;
	pAdmCfg->bAdmIfNum = 0;//m_aAdcCfg.AdmNumber;
	pAdmCfg->bAdcCnt = m_aAdmCfg[idx].bAdcCnt;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdm));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pCurCfgMem;
	pAdcCfg->wTag = ADC_CFG_TAG;
	pAdcCfg->wSize = sizeof(ICR_CfgAdc) - 4;
	pAdcCfg->bNumber = 0;
	pAdcCfg->bAdmNum = 0;//m_aAdcCfg.AdmNumber;
	pAdcCfg->bBits = m_aAdcCfg[idx].bBits;
	pAdcCfg->bEncoding = m_aAdcCfg[idx].bEncoding;
	pAdcCfg->dMinRate = m_aAdcCfg[idx].dMinRate;
	pAdcCfg->dMaxRate = m_aAdcCfg[idx].dMaxRate;
	pAdcCfg->wRange = m_aAdcCfg[idx].wRange;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdc));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;
	*pCurCfgMem = END_TAG;
	pCurCfgMem++;
	pDevInfo->nRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDevInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_DialogProperty(PSUBMOD_INFO pDevInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	S32 idx = GetTypeAdm(pDevInfo->Type);

	if(idx<0)
		idx = 0;

//	int curNum = pDevInfo->Number;

	CIcr0084Dlg dlg;
	lstrcpy(dlg.subInfo.sName, pDevInfo->sName);
	dlg.subInfo.Type = pDevInfo->Type;

	switch(m_aAdcCfg[idx].bBits)
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

	dlg.m_AdcEncoding = m_aAdcCfg[idx].bEncoding;
	dlg.m_AdcRange = m_aAdcCfg[idx].wRange;
	dlg.m_AdcRateMax = m_aAdcCfg[idx].dMaxRate;
	dlg.m_AdcRateMin = m_aAdcCfg[idx].dMinRate;

	dlg.m_NumOfAdc = m_aAdmCfg[idx].bAdcCnt;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		switch(dlg.m_AdcBits)
		{
			case 0:
				m_aAdcCfg[idx].bBits = 12;
				break;
			case 1:
				m_aAdcCfg[idx].bBits = 14;
				break;
			case 2:
				m_aAdcCfg[idx].bBits = 16;
				break;
		}
		m_aAdcCfg[idx].bEncoding = dlg.m_AdcEncoding;
		m_aAdcCfg[idx].wRange = dlg.m_AdcRange;
		m_aAdcCfg[idx].dMaxRate = dlg.m_AdcRateMax;
		m_aAdcCfg[idx].dMinRate = dlg.m_AdcRateMin;
//		m_aAdcCfg.Number = ;
		m_aAdmCfg[idx].bAdcCnt = dlg.m_NumOfAdc;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}

//***************************************************************************************
S32 GetTypeAdm(ICR_ADMType type)
{
	switch(type)
	{
		case ADM1612x1M:
			return 0;
		case ADM214x1M:
			return 1;
		case ADM214x3M:
			return 2;
		case ADM214x10M:
			return 3;
		case ADM214x10MX:
			return 4;
		case ADM1614x160:
			return 5;
		case ADM216x250:
			return 6;
		case ADM216x2M5:
			return 7;
		case ADM416x200:
			return 8;
		case ADM816x48:
			return 9;
		default:
			return -1;
	}
}