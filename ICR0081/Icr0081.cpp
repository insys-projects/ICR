// Icr0081.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr0081App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr0081.h"

ICR_CfgAdc m_aAdcCfg[2] = {{ ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 1000000000, 500},
						   { ADC_CFG_TAG, 14, 0, 0, 14, 1, 1000, 1000000000, 500}};

ICR_CfgAdm m_aAdmCfg[2] = {{ ADM_CFG_TAG, 11, 0, 40000000, 200000000, 2, 0},
						   { ADM_CFG_TAG, 11, 0, 40000000, 200000000, 2, 0}};

S32 GetTypeAdm(ICR_ADMType type);

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


// CIcr0081App

BEGIN_MESSAGE_MAP(CIcr0081App, CWinApp)
END_MESSAGE_MAP()


// CIcr0081App construction

CIcr0081App::CIcr0081App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr0081App object

CIcr0081App theApp;


// CIcr0081App initialization

BOOL CIcr0081App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADM214x200M"));
		pDevInfo->Type = ADM214x200M;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("ADM28x1G"));
		pDevInfo->Type = ADM28x1G;
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
	S32   idx = GetTypeAdm(pDeviceInfo->Type);
	ULONG RealCfgSize = 0;
	PVOID pAdmCfgMem = (PVOID)pDeviceInfo->pCfgMem;
	PVOID pEndAdmCfgMem = (PVOID)((UCHAR*)pAdmCfgMem + SUBMOD_CFGMEM_SIZE);
	int   end_flag = 0;

	if(idx<0)
		idx = 0;

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
				m_aAdmCfg[idx].dPllRefGen = pAdmCfg->dPllRefGen;
				m_aAdmCfg[idx].dPllFreq = pAdmCfg->dPllFreq;
				m_aAdmCfg[idx].bAdcCnt = pAdmCfg->bAdcCnt;
				m_aAdmCfg[idx].bIsRF = pAdmCfg->bIsRF;
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
	S32         idx = GetTypeAdm(pDeviceInfo->Type);
	USHORT*     pEndCfgMem = (USHORT*)(pDeviceInfo->pCfgMem) + SUBMOD_CFGMEM_SIZE/2;
	USHORT*     pCurCfgMem = (USHORT*)pDeviceInfo->pCfgMem;
	PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pCurCfgMem;

	if(idx<0)
		idx = 0;

	pAdmCfg->wTag = ADM_CFG_TAG;
	pAdmCfg->wSize = sizeof(ICR_CfgAdm) - 4;
	pAdmCfg->bAdmIfNum = 0;//m_AdcCfg.AdmNumber;
	pAdmCfg->dPllRefGen = m_aAdmCfg[idx].dPllRefGen;
	pAdmCfg->dPllFreq = m_aAdmCfg[idx].dPllFreq;
	pAdmCfg->bAdcCnt = m_aAdmCfg[idx].bAdcCnt;
	pAdmCfg->bIsRF = m_aAdmCfg[idx].bIsRF;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdm));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pCurCfgMem;
	pAdcCfg->wTag = ADC_CFG_TAG;
	pAdcCfg->wSize = sizeof(ICR_CfgAdc) - 4;
	pAdcCfg->bNumber = 0;
	pAdcCfg->bAdmNum = 0;//m_AdcCfg.AdmNumber;
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
	pDeviceInfo->nRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_DialogProperty(PSUBMOD_INFO pDeviceInfo)
{
	S32 idx = GetTypeAdm(pDeviceInfo->Type);

	if(idx<0)
		idx = 0;

	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

//	int curNum = pDeviceInfo->Number;

	CIcr0081Dlg dlg;
	lstrcpy(dlg.subInfo.sName, pDeviceInfo->sName);
	dlg.subInfo.Type = pDeviceInfo->Type;

	switch(m_aAdcCfg[idx].bBits)
	{
		case 8:
			dlg.m_AdcBits = 0;
			break;
		case 10:
			dlg.m_AdcBits = 1;
			break;
		case 12:
			dlg.m_AdcBits = 2;
			break;
		case 14:
			dlg.m_AdcBits = 3;
			break;
		case 16:
			dlg.m_AdcBits = 4;
			break;
	}
	int oldAdcBits = dlg.m_AdcBits;
	dlg.m_AdcEncoding = m_aAdcCfg[idx].bEncoding;
	dlg.m_AdcRange = m_aAdcCfg[idx].wRange;
	dlg.m_AdcRateMax = m_aAdcCfg[idx].dMaxRate;
	dlg.m_AdcRateMin = m_aAdcCfg[idx].dMinRate;
	dlg.m_NumOfAdc = m_aAdmCfg[idx].bAdcCnt;
	dlg.m_PllRefGen = m_aAdmCfg[idx].dPllRefGen;
	dlg.m_PllFreq = m_aAdmCfg[idx].dPllFreq;
	dlg.m_IsRF = m_aAdmCfg[idx].bIsRF;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			oldAdcBits != dlg.m_AdcBits ||
			m_aAdcCfg[idx].bEncoding != dlg.m_AdcEncoding ||
			m_aAdcCfg[idx].wRange != dlg.m_AdcRange ||
			m_aAdcCfg[idx].dMaxRate != dlg.m_AdcRateMax ||
			m_aAdcCfg[idx].dMinRate != dlg.m_AdcRateMin ||
			m_aAdmCfg[idx].bAdcCnt != dlg.m_NumOfAdc ||
			m_aAdmCfg[idx].dPllRefGen != dlg.m_PllRefGen ||
			m_aAdmCfg[idx].dPllFreq != dlg.m_PllFreq ||
			m_aAdmCfg[idx].bIsRF != dlg.m_IsRF
		)
			nResponse |= 0x100;

		switch(dlg.m_AdcBits)
		{
			case 0:
				m_aAdcCfg[idx].bBits = 8;
				break;
			case 1:
				m_aAdcCfg[idx].bBits = 10;
				break;
			case 2:
				m_aAdcCfg[idx].bBits = 12;
				break;
			case 3:
				m_aAdcCfg[idx].bBits = 14;
				break;
			case 4:
				m_aAdcCfg[idx].bBits = 16;
				break;
		}
		m_aAdcCfg[idx].bEncoding = dlg.m_AdcEncoding;
		m_aAdcCfg[idx].wRange = dlg.m_AdcRange;
		m_aAdcCfg[idx].dMaxRate = dlg.m_AdcRateMax;
		m_aAdcCfg[idx].dMinRate = dlg.m_AdcRateMin;
//		m_AdcCfg.Number = ;
		m_aAdmCfg[idx].bAdcCnt = dlg.m_NumOfAdc;
		m_aAdmCfg[idx].dPllRefGen = dlg.m_PllRefGen;
		m_aAdmCfg[idx].dPllFreq = dlg.m_PllFreq;
		m_aAdmCfg[idx].bIsRF = dlg.m_IsRF;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}

//***************************************************************************************
S32 GetTypeAdm(ICR_ADMType type)
{
	switch(type)
	{
	case ADM214x200M:
		return 0;
	case ADM28x1G:
		return 1;
	default:
		return -1;
	}
}
