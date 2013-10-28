// Icr0093.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr0093App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr0093.h"

ICR_CfgAdc g_AdcCfg = { ADC_CFG_TAG, 14, 0, 0, 10, 1, 10000000, 1000000000, 500};

ICR_CfgAdm g_AdmCfg = { ADM_CFG_TAG, 31, 0, 8, 0, 
						0, 2500, 1, 0x49, 10000000, 1400000000,
						{ 0, 4000, 2000, 1000, 500, 250, 0, 0 }
					  };


// CIcr0093App

BEGIN_MESSAGE_MAP(CIcr0093App, CWinApp)
END_MESSAGE_MAP()


// CIcr0093App construction

CIcr0093App::CIcr0093App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr0093App object

CIcr0093App theApp;


// CIcr0093App initialization

BOOL CIcr0093App::InitInstance()
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
			lstrcpy(pDevInfo->sName, _T("FM814x125M"));
			pDevInfo->Type = FM814x125M;
			break;
		case 1:
			lstrcpy(pDevInfo->sName, _T("FM814x250M"));
			pDevInfo->Type = FM814x250M;
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
	ULONG	RealCfgSize = 0;
	PVOID	pAdmCfgMem = (PVOID)pDeviceInfo->pCfgMem;
	PVOID	pEndAdmCfgMem = (PVOID)((UCHAR*)pAdmCfgMem + SUBMOD_CFGMEM_SIZE);
	int		end_flag = 0;
	int		ii;
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

				g_AdmCfg.bAdcType	    = pAdmCfg->bAdcType;	
				g_AdmCfg.bDacType	    = pAdmCfg->bDacType;	
				g_AdmCfg.wDacRange	    = pAdmCfg->wDacRange;	
				g_AdmCfg.bGenType	    = pAdmCfg->bGenType;	
				g_AdmCfg.bGenAdr	    = pAdmCfg->bGenAdr;	
				g_AdmCfg.nGenRef        = pAdmCfg->nGenRef;   
				g_AdmCfg.nGenRefMax     = pAdmCfg->nGenRefMax;
				for( ii=0; ii<8; ii++ )
					g_AdmCfg.awRange[ii]  = pAdmCfg->awRange[ii];

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
	int			ii;

	pAdmCfg->wTag = ADM_CFG_TAG;
	pAdmCfg->wSize = sizeof(ICR_CfgAdm) - 4;
	pAdmCfg->bAdmIfNum = 0;//g_AdcCfg.AdmNumber;
	pAdmCfg->bAdcCnt = g_AdmCfg.bAdcCnt;

	pAdmCfg->bAdcType	    = g_AdmCfg.bAdcType;	
	pAdmCfg->bDacType	    = g_AdmCfg.bDacType;	
	pAdmCfg->wDacRange	    = g_AdmCfg.wDacRange;	
	pAdmCfg->bGenType	    = g_AdmCfg.bGenType;	
	pAdmCfg->bGenAdr	    = g_AdmCfg.bGenAdr;	
	pAdmCfg->nGenRef        = g_AdmCfg.nGenRef;   
	pAdmCfg->nGenRefMax     = g_AdmCfg.nGenRefMax;
	for( ii=0; ii<8; ii++ )
		pAdmCfg->awRange[ii]  = g_AdmCfg.awRange[ii];


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

	CIcr0093Dlg dlg;
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

	dlg.m_AdcType   = g_AdmCfg.bAdcType;
	dlg.m_DacType   = g_AdmCfg.bDacType;
	dlg.m_DacRange  = g_AdmCfg.wDacRange;
	dlg.m_GenType   = g_AdmCfg.bGenType;
	dlg.m_GenAdr    = g_AdmCfg.bGenAdr;
	dlg.m_GenRef    = g_AdmCfg.nGenRef;
	dlg.m_GenRefMax = g_AdmCfg.nGenRefMax;
	dlg.m_Range0   = g_AdmCfg.awRange[0];
	dlg.m_Range1   = g_AdmCfg.awRange[1];
	dlg.m_Range2   = g_AdmCfg.awRange[2];
	dlg.m_Range3   = g_AdmCfg.awRange[3];
	dlg.m_Range4   = g_AdmCfg.awRange[4];
	dlg.m_Range5   = g_AdmCfg.awRange[5];

	//
	// Вызвать диалоговое окно
	//
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

			g_AdmCfg.bAdcType    != dlg.m_AdcType ||
			g_AdmCfg.bDacType    != dlg.m_DacType ||
			g_AdmCfg.wDacRange   != dlg.m_DacRange ||
			g_AdmCfg.bGenType    != dlg.m_GenType ||
			g_AdmCfg.bGenAdr     != dlg.m_GenAdr ||
			g_AdmCfg.nGenRef     != dlg.m_GenRef ||
			g_AdmCfg.nGenRefMax  != dlg.m_GenRefMax ||
			g_AdmCfg.awRange[0]  != dlg.m_Range0 ||
			g_AdmCfg.awRange[1]  != dlg.m_Range1 ||
			g_AdmCfg.awRange[2]  != dlg.m_Range2 ||
			g_AdmCfg.awRange[3]  != dlg.m_Range3 ||
			g_AdmCfg.awRange[4]  != dlg.m_Range4 ||
			g_AdmCfg.awRange[5]  != dlg.m_Range5
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

		g_AdmCfg.bAdcType   = dlg.m_AdcType;
		g_AdmCfg.bDacType   = dlg.m_DacType;
		g_AdmCfg.wDacRange  = dlg.m_DacRange;
		g_AdmCfg.bGenType   = dlg.m_GenType;
		g_AdmCfg.bGenAdr    = dlg.m_GenAdr;
		g_AdmCfg.nGenRef    = dlg.m_GenRef;
		g_AdmCfg.nGenRefMax = dlg.m_GenRefMax;
		g_AdmCfg.awRange[0]  = dlg.m_Range0;
		g_AdmCfg.awRange[1]  = dlg.m_Range1;
		g_AdmCfg.awRange[2]  = dlg.m_Range2;
		g_AdmCfg.awRange[3]  = dlg.m_Range3;
		g_AdmCfg.awRange[4]  = dlg.m_Range4;
		g_AdmCfg.awRange[5]  = dlg.m_Range5;

	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}
