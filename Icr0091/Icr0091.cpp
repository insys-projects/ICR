// Icr0091.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr0091App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr0091.h"

ICR_CfgAdc g_AdcCfg = { ADC_CFG_TAG, 14, 0, 0, 10, 1, 10000000, 1000000000, 500};

ICR_CfgAdm g_AdmCfg = { ADM_CFG_TAG, 70, 0, 2, 0, 
						400000000, 
						1000000000, 10000000, 1000000000, 1, 
						0, 0, 
						0, 0,
						{10000, 2000, 500, 100}, 
						{10000, 10000, 10000, 10000}, {10000, 10000, 10000, 10000},
						{0, 0, 0, 0}, {0, 0, 0, 0}
					};

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


// CIcr0091App

BEGIN_MESSAGE_MAP(CIcr0091App, CWinApp)
END_MESSAGE_MAP()


// CIcr0091App construction

CIcr0091App::CIcr0091App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr0091App object

CIcr0091App theApp;


// CIcr0091App initialization

BOOL CIcr0091App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADM210x1G"));
		pDevInfo->Type = ADM210x1G;
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
				g_AdcCfg.wTag = pAdcCfg->wTag;
				g_AdcCfg.wSize = pAdcCfg->wSize;
				g_AdcCfg.bNumber = pAdcCfg->bNumber;
				g_AdcCfg.bAdmNum = pAdcCfg->bAdmNum;
				g_AdcCfg.bBits = pAdcCfg->bBits;
				g_AdcCfg.bEncoding = pAdcCfg->bEncoding;
				g_AdcCfg.dMinRate = pAdcCfg->dMinRate;
				g_AdcCfg.dMaxRate = pAdcCfg->dMaxRate;
				g_AdcCfg.wRange = pAdcCfg->wRange;
				size = sizeof(ICR_CfgAdc);
				RealCfgSize += size;
				break;
			}
		case ADM_CFG_TAG:
			{
				PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pAdmCfgMem;
				g_AdmCfg.wTag = pAdmCfg->wTag;
				g_AdmCfg.wSize = pAdmCfg->wSize;
				g_AdmCfg.bAdmIfNum = pAdmCfg->bAdmIfNum;
				g_AdmCfg.bAdcCnt = pAdmCfg->bAdcCnt;

				g_AdmCfg.bSubType    = pAdmCfg->bSubType;
				g_AdmCfg.nRefGen0      = pAdmCfg->nRefGen0;
				g_AdmCfg.nRefGen1      = pAdmCfg->nRefGen1;
				g_AdmCfg.nRefGen1Min   = pAdmCfg->nRefGen1Min;
				g_AdmCfg.nRefGen1Max   = pAdmCfg->nRefGen1Max;
				g_AdmCfg.nRefGen1Type = pAdmCfg->nRefGen1Type;
				g_AdmCfg.nRefGen2     = pAdmCfg->nRefGen2;
				g_AdmCfg.nRefGen2Type = pAdmCfg->nRefGen2Type;
				g_AdmCfg.nLpfPassBand = pAdmCfg->nLpfPassBand;
				g_AdmCfg.awRange[0]  = pAdmCfg->awRange[0];
				g_AdmCfg.awRange[1]  = pAdmCfg->awRange[1];
				g_AdmCfg.awRange[2]  = pAdmCfg->awRange[2];
				g_AdmCfg.awRange[3]  = pAdmCfg->awRange[3];

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
	pAdmCfg->bAdmIfNum = 0;//g_AdcCfg.AdmNumber;
	pAdmCfg->bAdcCnt = g_AdmCfg.bAdcCnt;

	pAdmCfg->bSubType    = g_AdmCfg.bSubType;
	pAdmCfg->nRefGen0 = g_AdmCfg.nRefGen0;
	pAdmCfg->nRefGen1 = g_AdmCfg.nRefGen1;
	pAdmCfg->nRefGen1Min  = g_AdmCfg.nRefGen1Min;
	pAdmCfg->nRefGen1Max  = g_AdmCfg.nRefGen1Max;
	pAdmCfg->nRefGen1Type = g_AdmCfg.nRefGen1Type;
	pAdmCfg->nRefGen2     = g_AdmCfg.nRefGen2;
	pAdmCfg->nRefGen2Type = g_AdmCfg.nRefGen2Type;
	pAdmCfg->nLpfPassBand = g_AdmCfg.nLpfPassBand;
	pAdmCfg->awRange[0]  = g_AdmCfg.awRange[0];
	pAdmCfg->awRange[1]  = g_AdmCfg.awRange[1];
	pAdmCfg->awRange[2]  = g_AdmCfg.awRange[2];
	pAdmCfg->awRange[3]  = g_AdmCfg.awRange[3];

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdm));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pCurCfgMem;
	pAdcCfg->wTag = ADC_CFG_TAG;
	pAdcCfg->wSize = sizeof(ICR_CfgAdc) - 4;
	pAdcCfg->bNumber = 0;
	pAdcCfg->bAdmNum = 0;//g_AdcCfg.AdmNumber;
	pAdcCfg->bBits = g_AdcCfg.bBits;
	pAdcCfg->bEncoding = g_AdcCfg.bEncoding;
	pAdcCfg->dMinRate = g_AdcCfg.dMinRate;
	pAdcCfg->dMaxRate = g_AdcCfg.dMaxRate;
	pAdcCfg->wRange = g_AdcCfg.wRange;

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

	CIcr0091Dlg dlg;
	lstrcpy(dlg.subInfo.sName, pDeviceInfo->sName);
	dlg.subInfo.Type = pDeviceInfo->Type;

	switch(g_AdcCfg.bBits)
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
	dlg.m_AdcEncoding = g_AdcCfg.bEncoding;
	dlg.m_AdcRange    = g_AdcCfg.wRange;
	dlg.m_AdcRateMax  = g_AdcCfg.dMaxRate;
	dlg.m_AdcRateMin  = g_AdcCfg.dMinRate;
	dlg.m_NumOfAdc    = g_AdmCfg.bAdcCnt;

	dlg.m_SubType  = g_AdmCfg.bSubType;
	dlg.m_RefGen0  = g_AdmCfg.nRefGen0;
	dlg.m_RefGen1  = g_AdmCfg.nRefGen1;
	dlg.m_RefGen1Min  = g_AdmCfg.nRefGen1Min;
	dlg.m_RefGen1Max  = g_AdmCfg.nRefGen1Max;
	dlg.m_RefGen1Type  = g_AdmCfg.nRefGen1Type;
	dlg.m_RefGen2Type  = g_AdmCfg.nRefGen2Type;
	dlg.m_LpfPassBand  = g_AdmCfg.nLpfPassBand;
	dlg.m_Range0   = g_AdmCfg.awRange[0];
	dlg.m_Range1   = g_AdmCfg.awRange[1];
	dlg.m_Range2   = g_AdmCfg.awRange[2];
	dlg.m_Range3   = g_AdmCfg.awRange[3];

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		U08	tmpAdcBits;
		switch(dlg.m_AdcBits)
		{
			case 0:
				tmpAdcBits = 8;
				break;
			case 1:
				tmpAdcBits = 10;
				break;
			case 2:
				tmpAdcBits = 12;
				break;
			case 3:
				tmpAdcBits = 14;
				break;
			case 4:
				tmpAdcBits = 16;
				break;
		}
		if( 
			g_AdcCfg.bBits != tmpAdcBits ||
			g_AdcCfg.bEncoding != dlg.m_AdcEncoding ||
			g_AdcCfg.wRange != dlg.m_AdcRange ||
			g_AdcCfg.dMaxRate != dlg.m_AdcRateMax ||
			g_AdcCfg.dMinRate != dlg.m_AdcRateMin ||
			g_AdmCfg.bAdcCnt != dlg.m_NumOfAdc ||

			g_AdmCfg.bSubType    != dlg.m_SubType ||
			g_AdmCfg.nRefGen0 != dlg.m_RefGen0 ||
			g_AdmCfg.nRefGen1 != dlg.m_RefGen1 ||
			g_AdmCfg.nRefGen1Min != dlg.m_RefGen1Min ||
			g_AdmCfg.nRefGen1Max != dlg.m_RefGen1Max ||
			g_AdmCfg.nRefGen1Type != dlg.m_RefGen1Type ||
			g_AdmCfg.nRefGen2Type != dlg.m_RefGen2Type ||
			g_AdmCfg.nLpfPassBand != dlg.m_LpfPassBand ||
			g_AdmCfg.awRange[0]  != dlg.m_Range0 ||
			g_AdmCfg.awRange[1]  != dlg.m_Range1 ||
			g_AdmCfg.awRange[2]  != dlg.m_Range2 ||
			g_AdmCfg.awRange[3]  != dlg.m_Range3
		)
			nResponse |= 0x100;

		switch(dlg.m_AdcBits)
		{
			case 0:
				g_AdcCfg.bBits = 8;
				break;
			case 1:
				g_AdcCfg.bBits = 10;
				break;
			case 2:
				g_AdcCfg.bBits = 12;
				break;
			case 3:
				g_AdcCfg.bBits = 14;
				break;
			case 4:
				g_AdcCfg.bBits = 16;
				break;
		}
		g_AdcCfg.bEncoding = dlg.m_AdcEncoding;
		g_AdcCfg.wRange = dlg.m_AdcRange;
		g_AdcCfg.dMaxRate = dlg.m_AdcRateMax;
		g_AdcCfg.dMinRate = dlg.m_AdcRateMin;
//		g_AdcCfg.Number = ;
		g_AdmCfg.bAdcCnt = dlg.m_NumOfAdc;

		g_AdmCfg.bSubType    = dlg.m_SubType;
		g_AdmCfg.nRefGen0 = dlg.m_RefGen0;
		g_AdmCfg.nRefGen1 = dlg.m_RefGen1;
		g_AdmCfg.nRefGen1Min = dlg.m_RefGen1Min;
		g_AdmCfg.nRefGen1Max = dlg.m_RefGen1Max;
		g_AdmCfg.nRefGen1Type = dlg.m_RefGen1Type;
		g_AdmCfg.nRefGen2Type = dlg.m_RefGen2Type;
		g_AdmCfg.nLpfPassBand = dlg.m_LpfPassBand;
		g_AdmCfg.awRange[0]  = dlg.m_Range0;
		g_AdmCfg.awRange[1]  = dlg.m_Range1;
		g_AdmCfg.awRange[2]  = dlg.m_Range2;
		g_AdmCfg.awRange[3]  = dlg.m_Range3;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}
