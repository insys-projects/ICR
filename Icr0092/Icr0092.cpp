// Icr0092.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr0092App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr0092.h"

ICR_CfgAdmDac m_DacCfg = { ADMDAC_CFG_TAG, 14, 0, 0, 14, 1, 0, 400000000, 2500};

ICR_CfgAdm g_AdmCfg = { ADM_CFG_TAG, 23, 0, 0, 0, 2, 0, 50, 400000000, 0, 0, 1, 1, 1, 0};

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


// CIcr0092App

BEGIN_MESSAGE_MAP(CIcr0092App, CWinApp)
END_MESSAGE_MAP()


// CIcr0092App construction

CIcr0092App::CIcr0092App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr0092App object

CIcr0092App theApp;


// CIcr0092App initialization

BOOL CIcr0092App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADMDAC216x400M v2.0"));
		pDevInfo->Type = ADMDAC216x400MV2;
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
		case ADMDAC_CFG_TAG:
			{
				PICR_CfgAdmDac pDacCfg = (PICR_CfgAdmDac)pAdmCfgMem;
				m_DacCfg.wTag = pDacCfg->wTag;
				m_DacCfg.wSize = pDacCfg->wSize;
				m_DacCfg.bNumber = pDacCfg->bNumber;
				m_DacCfg.bAdmNum = pDacCfg->bAdmNum;
				m_DacCfg.bBits = pDacCfg->bBits;
				m_DacCfg.bEncoding = pDacCfg->bEncoding;
				m_DacCfg.dMinRate = pDacCfg->dMinRate;
				m_DacCfg.dMaxRate = pDacCfg->dMaxRate;
				m_DacCfg.wRange = pDacCfg->wRange;
				size = sizeof(ICR_CfgAdmDac);
				RealCfgSize += size;
				break;
			}
		case ADM_CFG_TAG:
			{
				PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pAdmCfgMem;
				g_AdmCfg.wTag = pAdmCfg->wTag;
				g_AdmCfg.wSize = pAdmCfg->wSize;
				g_AdmCfg.bAdmIfNum = pAdmCfg->bAdmIfNum;
				g_AdmCfg.dGen = pAdmCfg->dGen;
				g_AdmCfg.bFreqTune = pAdmCfg->bFreqTune;
				g_AdmCfg.bDacCnt = pAdmCfg->bDacCnt;
				g_AdmCfg.dLPFCutoff = pAdmCfg->dLPFCutoff;
				g_AdmCfg.bOutResist = pAdmCfg->bOutResist;
				g_AdmCfg.dOscFreq = pAdmCfg->dOscFreq;
				g_AdmCfg.bOutCasMod = pAdmCfg->bOutCasMod;
				g_AdmCfg.bQuadModType = pAdmCfg->bQuadModType;
				g_AdmCfg.bIsExtClk = pAdmCfg->bIsExtClk;
				g_AdmCfg.wGenPrec = pAdmCfg->wGenPrec;
				g_AdmCfg.bIsClkout = pAdmCfg->bIsClkout;
				g_AdmCfg.bIsIndustrial = pAdmCfg->bIsIndustrial;
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
	pAdmCfg->bAdmIfNum = 0;//m_DacCfg.AdmNumber;
	pAdmCfg->dGen = g_AdmCfg.dGen;
	pAdmCfg->bFreqTune = g_AdmCfg.bFreqTune;
	pAdmCfg->bDacCnt = g_AdmCfg.bDacCnt;
	pAdmCfg->dLPFCutoff = g_AdmCfg.dLPFCutoff;
	pAdmCfg->bOutResist = g_AdmCfg.bOutResist;
	pAdmCfg->dOscFreq = g_AdmCfg.dOscFreq;
	pAdmCfg->bOutCasMod = g_AdmCfg.bOutCasMod;
	pAdmCfg->bQuadModType = g_AdmCfg.bQuadModType;
	pAdmCfg->bIsExtClk = g_AdmCfg.bIsExtClk;
	pAdmCfg->wGenPrec = g_AdmCfg.wGenPrec;

	pAdmCfg->bIsClkout     = g_AdmCfg.bIsClkout; 
	pAdmCfg->bIsIndustrial = g_AdmCfg.bIsIndustrial;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdm));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_CfgAdmDac pDacCfg = (PICR_CfgAdmDac)pCurCfgMem;
	pDacCfg->wTag = ADMDAC_CFG_TAG;
	pDacCfg->wSize = sizeof(ICR_CfgAdmDac) - 4;
	pDacCfg->bNumber = 0;
	pDacCfg->bAdmNum = 0;//m_DacCfg.AdmNumber;
	pDacCfg->bBits = m_DacCfg.bBits;
	pDacCfg->bEncoding = m_DacCfg.bEncoding;
	pDacCfg->dMinRate = m_DacCfg.dMinRate;
	pDacCfg->dMaxRate = m_DacCfg.dMaxRate;
	pDacCfg->wRange = m_DacCfg.wRange;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdmDac));
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

	Icr0092Dlg dlg;
	lstrcpy(dlg.subInfo.sName, pDeviceInfo->sName);
	dlg.subInfo.Type = pDeviceInfo->Type;

	dlg.m_nDacRange = m_DacCfg.wRange;
	dlg.m_nDacRateMax = m_DacCfg.dMaxRate/1000000;
	dlg.m_nDacRateMin = m_DacCfg.dMinRate/1000000;

	dlg.m_nGen = g_AdmCfg.dGen;
	dlg.m_isFreqTune = g_AdmCfg.bFreqTune;
	dlg.m_bNumOfDac = g_AdmCfg.bDacCnt;
	dlg.m_nLpfCutoff = g_AdmCfg.dLPFCutoff;
	dlg.m_sOutResist.Format("%d", g_AdmCfg.bOutResist);
	dlg.m_nOscFreq = g_AdmCfg.dOscFreq/1000000;
	dlg.m_QuadModType = g_AdmCfg.bQuadModType;
	dlg.m_ExtClk = g_AdmCfg.bIsExtClk;

	dlg.m_isClkOut = g_AdmCfg.bIsClkout;
	dlg.m_isIndustrial = g_AdmCfg.bIsIndustrial;

	dlg.m_sGenPrec.Format("%.2f", (REAL32)g_AdmCfg.wGenPrec / (REAL32)100); 

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_DacCfg.wRange != dlg.m_nDacRange ||
			m_DacCfg.dMaxRate != (dlg.m_nDacRateMax*1000000) ||
			m_DacCfg.dMinRate != (dlg.m_nDacRateMin*1000000) ||
			g_AdmCfg.dGen != dlg.m_nGen ||
			g_AdmCfg.bFreqTune != dlg.m_isFreqTune ||
			g_AdmCfg.bDacCnt != dlg.m_bNumOfDac ||
			g_AdmCfg.dLPFCutoff != dlg.m_nLpfCutoff ||
			(g_AdmCfg.bOutResist != (atoi(dlg.m_sOutResist.GetString()))) ||
			g_AdmCfg.dOscFreq != (dlg.m_nOscFreq*1000000) ||
			(g_AdmCfg.wGenPrec != (atof(dlg.m_sGenPrec.GetString()) * 100)) ||
			g_AdmCfg.bQuadModType != dlg.m_QuadModType ||
			g_AdmCfg.bIsExtClk != dlg.m_ExtClk ||
			g_AdmCfg.bIsClkout != dlg.m_isClkOut ||
			g_AdmCfg.bIsIndustrial != dlg.m_isIndustrial
		)
			nResponse |= 0x100;

		m_DacCfg.wRange = dlg.m_nDacRange;
		m_DacCfg.dMaxRate = dlg.m_nDacRateMax*1000000;
		m_DacCfg.dMinRate = dlg.m_nDacRateMin*1000000;
		
		g_AdmCfg.dGen = dlg.m_nGen;
		g_AdmCfg.bFreqTune = dlg.m_isFreqTune;
		g_AdmCfg.bDacCnt = dlg.m_bNumOfDac;
		g_AdmCfg.dLPFCutoff = dlg.m_nLpfCutoff;
		g_AdmCfg.bOutResist = atoi(dlg.m_sOutResist.GetString());
		g_AdmCfg.dOscFreq = dlg.m_nOscFreq * 1000000;
		g_AdmCfg.bQuadModType = dlg.m_QuadModType;
		g_AdmCfg.bIsExtClk = dlg.m_ExtClk;
		g_AdmCfg.wGenPrec = atof(dlg.m_sGenPrec.GetString()) * 100;

		g_AdmCfg.bIsClkout = dlg.m_isClkOut;
		g_AdmCfg.bIsIndustrial = dlg.m_isIndustrial;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
