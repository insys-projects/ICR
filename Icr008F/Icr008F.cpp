// Icr008F.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr008FApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr008F.h"

ICR_CfgAdmDac m_DacCfg = { ADMDAC_CFG_TAG, 14, 0, 0, 14, 1, 0, 200000000, 2500};

ICR_CfgAdm m_AdmCfg = { ADM_CFG_TAG, 21, 0, 1, 120000000, 0, 2, 0, 0, 400, 0, 0, 0, 0};

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


// CIcr008FApp

BEGIN_MESSAGE_MAP(CIcr008FApp, CWinApp)
END_MESSAGE_MAP()


// CIcr008FApp construction

CIcr008FApp::CIcr008FApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr008FApp object

CIcr008FApp theApp;


// CIcr008FApp initialization

BOOL CIcr008FApp::InitInstance()
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
		lstrcpy(pDevInfo->Name, _T("ADMDAC216x400M"));
		pDevInfo->Type = ADMDAC216x400M;
		break;
	default:
		*pNumDev = -1;
		return;
	}
	pDevInfo->pCfgMem = new UCHAR[SUBMOD_CFGMEM_SIZE];
	pDevInfo->CfgMemSize = SUBMOD_CFGMEM_SIZE;
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
				m_AdmCfg.wTag = pAdmCfg->wTag;
				m_AdmCfg.wSize = pAdmCfg->wSize;
				m_AdmCfg.bAdmIfNum = pAdmCfg->bAdmIfNum;
				m_AdmCfg.bIsGen = pAdmCfg->bIsGen;
				m_AdmCfg.dGen = pAdmCfg->dGen;
				m_AdmCfg.bFreqTune = pAdmCfg->bFreqTune;
				m_AdmCfg.bDacCnt = pAdmCfg->bDacCnt;
				m_AdmCfg.dLPFCutoff = pAdmCfg->dLPFCutoff;
				m_AdmCfg.bOutResist = pAdmCfg->bOutResist;
				m_AdmCfg.dOscFreq = pAdmCfg->dOscFreq;
				m_AdmCfg.bOutCasMod = pAdmCfg->bOutCasMod;
				m_AdmCfg.bIsQuadMod = pAdmCfg->bIsQuadMod;
				m_AdmCfg.bQuadModType = pAdmCfg->bQuadModType;
				m_AdmCfg.bIsExtClk = pAdmCfg->bIsExtClk;
				size = sizeof(ICR_CfgAdm);
				RealCfgSize += size;
				break;
			}
		}
		pAdmCfgMem = (UCHAR*)pAdmCfgMem + size;
	} while(!end_flag && pAdmCfgMem < pEndAdmCfgMem);
	pDeviceInfo->RealCfgSize = RealCfgSize;
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
	pAdmCfg->bIsGen = m_AdmCfg.bIsGen;
	pAdmCfg->dGen = m_AdmCfg.dGen;
	pAdmCfg->bFreqTune = m_AdmCfg.bFreqTune;
	pAdmCfg->bDacCnt = m_AdmCfg.bDacCnt;
	pAdmCfg->dLPFCutoff = m_AdmCfg.dLPFCutoff;
	pAdmCfg->bOutResist = m_AdmCfg.bOutResist;
	pAdmCfg->dOscFreq = m_AdmCfg.dOscFreq;
	pAdmCfg->bOutCasMod = m_AdmCfg.bOutCasMod;
	pAdmCfg->bIsQuadMod = m_AdmCfg.bIsQuadMod;
	pAdmCfg->bQuadModType = m_AdmCfg.bQuadModType;
	pAdmCfg->bIsExtClk = m_AdmCfg.bIsExtClk;

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
	pDeviceInfo->RealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_DialogProperty(PSUBMOD_INFO pDeviceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

//	int curNum = pDeviceInfo->Number;

	Icr008FDlg dlg;
	lstrcpy(dlg.subInfo.Name, pDeviceInfo->Name);
	dlg.subInfo.Type = pDeviceInfo->Type;

	dlg.m_DacRange = m_DacCfg.wRange;
	dlg.m_DacRateMax = m_DacCfg.dMaxRate;
	dlg.m_DacRateMin = m_DacCfg.dMinRate;

	dlg.m_IsGen = m_AdmCfg.bIsGen;
	dlg.m_Gen = m_AdmCfg.dGen;
	dlg.m_GenTune = m_AdmCfg.bFreqTune;
	dlg.m_NumOfDac = m_AdmCfg.bDacCnt;
	dlg.m_LpfCutoff = m_AdmCfg.dLPFCutoff;
	dlg.m_OutResist = m_AdmCfg.bOutResist;
	dlg.m_OscFreq = m_AdmCfg.dOscFreq;
	dlg.m_OutCasMod = m_AdmCfg.bOutCasMod;
	dlg.m_QuadMod = m_AdmCfg.bIsQuadMod;
	dlg.m_QuadModType = m_AdmCfg.bQuadModType;
	dlg.m_ExtClk = m_AdmCfg.bIsExtClk;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK

		m_DacCfg.wRange = dlg.m_DacRange;
		m_DacCfg.dMaxRate = dlg.m_DacRateMax;
		m_DacCfg.dMinRate = dlg.m_DacRateMin;
//		m_DacCfg.Number = ;

		
		m_AdmCfg.bIsGen = dlg.m_IsGen;
		m_AdmCfg.dGen = dlg.m_Gen;
		m_AdmCfg.bFreqTune = dlg.m_GenTune;
		m_AdmCfg.bDacCnt = dlg.m_NumOfDac;
		m_AdmCfg.dLPFCutoff = dlg.m_LpfCutoff;
		m_AdmCfg.bOutResist = dlg.m_OutResist;
		m_AdmCfg.dOscFreq = dlg.m_OscFreq;
		m_AdmCfg.bOutCasMod = dlg.m_OutCasMod;
		m_AdmCfg.bIsQuadMod = dlg.m_QuadMod;
		m_AdmCfg.bQuadModType = dlg.m_QuadModType;
		m_AdmCfg.bIsExtClk = dlg.m_ExtClk;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
