// Icr008C.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr008CApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr008C.h"

ICR_CfgAdm m_AdmCfg = { ADM_CFG_TAG, 15, 0, 10000000, 1, 1, 90000000, 1, 0, 500};

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

// CIcr008CApp

BEGIN_MESSAGE_MAP(CIcr008CApp, CWinApp)
END_MESSAGE_MAP()


// CIcr008CApp construction

CIcr008CApp::CIcr008CApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr008CApp object

CIcr008CApp theApp;


// CIcr008CApp initialization

BOOL CIcr008CApp::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADMDDS9852A"));
		pDevInfo->Type = ADMDDS9852A;
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
		case ADM_CFG_TAG:
			{
				PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pAdmCfgMem;
				m_AdmCfg.wTag = pAdmCfg->wTag;
				m_AdmCfg.wSize = pAdmCfg->wSize;
				m_AdmCfg.bAdmIfNum = pAdmCfg->bAdmIfNum;
				m_AdmCfg.dGen = pAdmCfg->dGen;
				m_AdmCfg.bIsOxco = pAdmCfg->bIsOxco;
				m_AdmCfg.bIsDblFreq = pAdmCfg->bIsDblFreq;
				m_AdmCfg.dLPFCutoff = pAdmCfg->dLPFCutoff;
				m_AdmCfg.bIsExtClk = pAdmCfg->bIsExtClk;
				m_AdmCfg.bIsStrobe = pAdmCfg->bIsStrobe;
				m_AdmCfg.wMaxAmpl = pAdmCfg->wMaxAmpl;
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
	pAdmCfg->dGen = m_AdmCfg.dGen;
	pAdmCfg->bIsOxco = m_AdmCfg.bIsOxco;
	pAdmCfg->bIsDblFreq = m_AdmCfg.bIsDblFreq;
	pAdmCfg->dLPFCutoff = m_AdmCfg.dLPFCutoff;
	pAdmCfg->bIsExtClk = m_AdmCfg.bIsExtClk;
	pAdmCfg->bIsStrobe = m_AdmCfg.bIsStrobe;
	pAdmCfg->wMaxAmpl = m_AdmCfg.wMaxAmpl;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdm));
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

	CIcr008CDlg dlg;
	lstrcpy(dlg.subInfo.sName, pDeviceInfo->sName);
	dlg.subInfo.Type = pDeviceInfo->Type;

	dlg.m_Gen = m_AdmCfg.dGen;
	dlg.m_IsOxco = m_AdmCfg.bIsOxco;
	dlg.m_IsDblFreq = m_AdmCfg.bIsDblFreq;
	dlg.m_LpfCutoff = m_AdmCfg.dLPFCutoff;
	dlg.m_ExtClk = m_AdmCfg.bIsExtClk;
	dlg.m_IsStrobe = m_AdmCfg.bIsStrobe;
	dlg.m_MaxAmpl = m_AdmCfg.wMaxAmpl;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_AdmCfg.dGen != dlg.m_Gen ||
			m_AdmCfg.bIsOxco != dlg.m_IsOxco ||
			m_AdmCfg.bIsDblFreq != dlg.m_IsDblFreq ||
			m_AdmCfg.dLPFCutoff != dlg.m_LpfCutoff ||
			m_AdmCfg.bIsExtClk != dlg.m_ExtClk ||
			m_AdmCfg.bIsStrobe != dlg.m_IsStrobe ||
			m_AdmCfg.wMaxAmpl != dlg.m_MaxAmpl
		)
			nResponse |= 0x100;

		m_AdmCfg.dGen = dlg.m_Gen;
		m_AdmCfg.bIsOxco = dlg.m_IsOxco;
		m_AdmCfg.bIsDblFreq = dlg.m_IsDblFreq;
		m_AdmCfg.dLPFCutoff = dlg.m_LpfCutoff;
		m_AdmCfg.bIsExtClk = dlg.m_ExtClk;
		m_AdmCfg.bIsStrobe = dlg.m_IsStrobe;
		m_AdmCfg.wMaxAmpl = dlg.m_MaxAmpl;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
