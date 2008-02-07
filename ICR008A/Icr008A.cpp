// Icr0087.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr008AApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr008A.h"

ICR_CfgAdmDac m_DacCfg = { ADMDAC_CFG_TAG, 14, 0, 0, 14, 1, 0, 200000000, 2500};

ICR_CfgDacFifo m_FifoCfg = { DAC_FIFO_TAG, 5, 0, 0, 14, 2, 1};

ICR_CfgAdm m_AdmCfg = { ADM_CFG_TAG, 14, 0, 120000000, 2, 0, 0, 0};

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

// CIcr008AApp

BEGIN_MESSAGE_MAP(CIcr008AApp, CWinApp)
END_MESSAGE_MAP()


// CIcr008AApp construction

CIcr008AApp::CIcr008AApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr008AApp object

CIcr008AApp theApp;


// CIcr008AApp initialization

BOOL CIcr008AApp::InitInstance()
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
		lstrcpy(pDevInfo->Name, _T("ADMDAC214x125M"));
		pDevInfo->Type = ADMDAC214x125M;
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
		case DAC_FIFO_TAG:
			{
				PICR_CfgDacFifo pFifoCfg = (PICR_CfgDacFifo)pAdmCfgMem;
				m_FifoCfg.wTag = pFifoCfg->wTag;
				m_FifoCfg.wSize = pFifoCfg->wSize;
				m_FifoCfg.bNumber = pFifoCfg->bNumber;
				m_FifoCfg.bAdmNum = pFifoCfg->bAdmNum;
				m_FifoCfg.bDepth = pFifoCfg->bDepth;
				m_FifoCfg.bBitsWidth = pFifoCfg->bBitsWidth;
				size = sizeof(ICR_CfgDacFifo);
				RealCfgSize += size;
				break;
			}
		case ADM_CFG_TAG:
			{
				PICR_CfgAdm pAdmCfg = (PICR_CfgAdm)pAdmCfgMem;
				m_AdmCfg.wTag = pAdmCfg->wTag;
				m_AdmCfg.wSize = pAdmCfg->wSize;
				m_AdmCfg.bAdmIfNum = pAdmCfg->bAdmIfNum;
				m_AdmCfg.dGen = pAdmCfg->dGen;
				m_AdmCfg.bDacCnt = pAdmCfg->bDacCnt;
				m_AdmCfg.dLPFCutoff = pAdmCfg->dLPFCutoff;
				m_AdmCfg.bOutResist = pAdmCfg->bOutResist;
				m_AdmCfg.bIsExtClk = pAdmCfg->bIsExtClk;
				m_AdmCfg.bQuadModType = pAdmCfg->bQuadModType;
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
	pAdmCfg->dGen = m_AdmCfg.dGen;
	pAdmCfg->bDacCnt = m_AdmCfg.bDacCnt;
	pAdmCfg->dLPFCutoff = m_AdmCfg.dLPFCutoff;
	pAdmCfg->bOutResist = m_AdmCfg.bOutResist;
	pAdmCfg->bIsExtClk = m_AdmCfg.bIsExtClk;
	pAdmCfg->bQuadModType = m_AdmCfg.bQuadModType;

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

	PICR_CfgDacFifo pFifoCfg = (PICR_CfgDacFifo)pCurCfgMem;
	pFifoCfg->wTag = DAC_FIFO_TAG;
	pFifoCfg->wSize = sizeof(ICR_CfgDacFifo) - 4;
	pFifoCfg->bNumber = 0;
	pFifoCfg->bAdmNum = 0;//m_DacCfg.AdmNumber;
	pFifoCfg->bDepth = m_FifoCfg.bDepth;
	pFifoCfg->bBitsWidth = m_FifoCfg.bBitsWidth;
	pFifoCfg->bIsCycle = m_FifoCfg.bIsCycle;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgDacFifo));
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

	CIcr008ADlg dlg;
	lstrcpy(dlg.subInfo.Name, pDeviceInfo->Name);
	dlg.subInfo.Type = pDeviceInfo->Type;

	switch(m_DacCfg.bBits)
	{
		case 12:
			dlg.m_DacBits = 0;
			break;
		case 14:
			dlg.m_DacBits = 1;
			break;
		case 16:
			dlg.m_DacBits = 2;
			break;
	}
	dlg.m_DacEncoding = m_DacCfg.bEncoding;
	dlg.m_DacRange = m_DacCfg.wRange;
	dlg.m_DacRateMax = m_DacCfg.dMaxRate;
	dlg.m_DacRateMin = m_DacCfg.dMinRate;

	if(m_FifoCfg.bDepth)
	{
		if(m_FifoCfg.bDepth < 5)
			m_FifoCfg.bDepth = 5;
		if(m_FifoCfg.bDepth > 20)
			m_FifoCfg.bDepth = 20;
		dlg.m_FifoSize = m_FifoCfg.bDepth - 4;
	}
	else
		dlg.m_FifoSize = 0;
//	dlg.m_FifoSize = m_FifoCfg.bDepth;
	dlg.m_FifoBitsWidth = m_FifoCfg.bBitsWidth;

	dlg.m_NumOfDac = m_AdmCfg.bDacCnt;
	dlg.m_Gen = m_AdmCfg.dGen;
	dlg.m_LpfCutoff = m_AdmCfg.dLPFCutoff;
	dlg.m_OutResist = m_AdmCfg.bOutResist;
	dlg.m_ExtClk = m_AdmCfg.bIsExtClk;
	dlg.m_QuadModType = m_AdmCfg.bQuadModType;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		U08	tmpDacBits;
		U08	tmpFifoSize;
		switch( dlg.m_DacBits )
		{
			case 0:
				tmpDacBits = 12;
				break;
			case 1:
				tmpDacBits = 14;
				break;
			case 2:
				tmpDacBits = 16;
				break;
		}
		if( dlg.m_FifoSize )
			tmpFifoSize = dlg.m_FifoSize + 4;
		else
			tmpFifoSize = 0;
		if( 
			m_DacCfg.bBits != tmpDacBits ||
			m_DacCfg.bEncoding != dlg.m_DacEncoding ||
			m_DacCfg.wRange != dlg.m_DacRange ||
			m_DacCfg.dMaxRate != dlg.m_DacRateMax ||
			m_DacCfg.dMinRate != dlg.m_DacRateMin ||
			m_FifoCfg.bDepth != tmpFifoSize ||
			m_FifoCfg.bBitsWidth != dlg.m_FifoBitsWidth ||
			m_AdmCfg.bDacCnt != dlg.m_NumOfDac ||
			m_AdmCfg.dGen != dlg.m_Gen ||
			m_AdmCfg.dLPFCutoff != dlg.m_LpfCutoff ||
			m_AdmCfg.bOutResist != dlg.m_OutResist ||
			m_AdmCfg.bIsExtClk != dlg.m_ExtClk ||
			m_AdmCfg.bQuadModType != dlg.m_QuadModType
		)
			nResponse |= 0x100;

		switch(dlg.m_DacBits)
		{
			case 0:
				m_DacCfg.bBits = 12;
				break;
			case 1:
				m_DacCfg.bBits = 14;
				break;
			case 2:
				m_DacCfg.bBits = 16;
				break;
		}
		m_DacCfg.bEncoding = dlg.m_DacEncoding;
		m_DacCfg.wRange = dlg.m_DacRange;
		m_DacCfg.dMaxRate = dlg.m_DacRateMax;
		m_DacCfg.dMinRate = dlg.m_DacRateMin;
//		m_DacCfg.Number = ;

		if(dlg.m_FifoSize)
			m_FifoCfg.bDepth = dlg.m_FifoSize + 4;
		else
			m_FifoCfg.bDepth = 0;
//		m_FifoCfg.bDepth = dlg.m_FifoSize;
		m_FifoCfg.bBitsWidth = dlg.m_FifoBitsWidth;

		m_AdmCfg.bDacCnt = dlg.m_NumOfDac;
		m_AdmCfg.dGen = dlg.m_Gen;
		m_AdmCfg.dLPFCutoff = dlg.m_LpfCutoff;
		m_AdmCfg.bOutResist = dlg.m_OutResist;
		m_AdmCfg.bIsExtClk = dlg.m_ExtClk;
		m_AdmCfg.bQuadModType = dlg.m_QuadModType;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
