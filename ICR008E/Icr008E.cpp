// Icr008E.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr008EApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "Icr008E.h"

ICR_CfgAdc		m_AdcCfg = { ADC_CFG_TAG, 14, 0, 0, 24, 1, 2000, 192000, 500};
ICR_CfgAdmDac	m_DacCfg = { ADMDAC_CFG_TAG, 14, 0, 0, 24, 1, 2000, 192000, 500};  

ICR_CfgAdm		m_AdmCfg = { ADM_CFG_TAG, 14, 0, 16, 4};

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

// CIcr008EApp

BEGIN_MESSAGE_MAP(CIcr008EApp, CWinApp)
END_MESSAGE_MAP()


// CIcr008EApp construction

CIcr008EApp::CIcr008EApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr008EApp object

CIcr008EApp theApp;


// CIcr008EApp initialization

BOOL CIcr008EApp::InitInstance()
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
		lstrcpy(pDevInfo->Name, _T("ADM1624x192"));
		pDevInfo->Type = ADM1624x192;
		break;
	//case 1:
	//	lstrcpy(pDevInfo->Name, _T("AA_212x25M"));
	//	pDevInfo->Type = ADM212x25M;
	//	break;
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
				m_AdmCfg.bAdcCnt = pAdmCfg->bAdcCnt;
				m_AdmCfg.bDacCnt = pAdmCfg->bDacCnt;
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
	pAdmCfg->bAdmIfNum = 0;//m_AdcCfg.AdmNumber;
	pAdmCfg->bAdcCnt = m_AdmCfg.bAdcCnt;
	pAdmCfg->bDacCnt = m_AdmCfg.bDacCnt;

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

	PICR_CfgAdmDac	pDacCfg = (PICR_CfgAdmDac)pCurCfgMem;
	pDacCfg->wTag = ADMDAC_CFG_TAG;
	pDacCfg->wSize = sizeof(ICR_CfgAdmDac) - 4;
	pDacCfg->bNumber = 0;
	pDacCfg->bAdmNum = 0;
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
	U08		abAdcBits[] = { 12, 16, 24 };
	U08		abDacBits[] = { 12, 16, 24 };
	U08		abAdcCnt[]  = { 0, 2, 4, 6, 8, 10, 12, 14, 16 };
	U08		abDacCnt[]  = { 0, 2, 4 };
	int		ii;

//	int curNum = pDeviceInfo->Number;

	CIcr008EDlg dlg;
	lstrcpy(dlg.subInfo.Name, pDeviceInfo->Name);
	dlg.subInfo.Type = pDeviceInfo->Type;

	dlg.m_AdcBits = 0;
	for( ii=0; ii<sizeof(abAdcBits)/sizeof(abAdcBits[0]); ii++ )
		if( m_AdcCfg.bBits == abAdcBits[ii] )
			dlg.m_AdcBits = ii;
	dlg.m_AdcEncoding = m_AdcCfg.bEncoding;
	dlg.m_AdcRange = m_AdcCfg.wRange;
	dlg.m_AdcRateMax = m_AdcCfg.dMaxRate;
	dlg.m_AdcRateMin = m_AdcCfg.dMinRate;
	dlg.m_NumOfAdc = 0;
	for( ii=0; ii<sizeof(abAdcCnt)/sizeof(abAdcCnt[0]); ii++ )
		if( m_AdmCfg.bAdcCnt == abAdcCnt[ii] )
			dlg.m_NumOfAdc = ii;

	dlg.m_DacBits = 0;
	for( ii=0; ii<sizeof(abDacBits)/sizeof(abDacBits[0]); ii++ )
		if( m_DacCfg.bBits == abDacBits[ii] )
			dlg.m_DacBits = ii;
	dlg.m_DacEncoding = m_DacCfg.bEncoding;
	dlg.m_DacRange = m_DacCfg.wRange;
	dlg.m_DacRateMax = m_DacCfg.dMaxRate;
	dlg.m_DacRateMin = m_DacCfg.dMinRate;
	dlg.m_NumOfDac = 0;
	for( ii=0; ii<sizeof(abDacCnt)/sizeof(abDacCnt[0]); ii++ )
		if( m_AdmCfg.bDacCnt == abDacCnt[ii] )
			dlg.m_NumOfDac = ii;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_AdcCfg.bBits != abAdcBits[dlg.m_AdcBits] ||
			m_AdcCfg.bEncoding != dlg.m_AdcEncoding ||
			m_AdcCfg.wRange != dlg.m_AdcRange ||
			m_AdcCfg.dMaxRate != dlg.m_AdcRateMax ||
			m_AdcCfg.dMinRate != dlg.m_AdcRateMin ||
			m_AdmCfg.bAdcCnt != abAdcCnt[dlg.m_NumOfAdc] ||
			m_DacCfg.bBits != abDacBits[dlg.m_DacBits] ||
			m_DacCfg.bEncoding != dlg.m_DacEncoding ||
			m_DacCfg.wRange != dlg.m_DacRange ||
			m_DacCfg.dMaxRate != dlg.m_DacRateMax ||
			m_DacCfg.dMinRate != dlg.m_DacRateMin ||
			m_AdmCfg.bDacCnt != abDacCnt[dlg.m_NumOfDac]
		)
			nResponse |= 0x100;

		m_AdcCfg.bBits = abAdcBits[dlg.m_AdcBits];
		m_AdcCfg.bEncoding = dlg.m_AdcEncoding;
		m_AdcCfg.wRange = dlg.m_AdcRange;
		m_AdcCfg.dMaxRate = dlg.m_AdcRateMax;
		m_AdcCfg.dMinRate = dlg.m_AdcRateMin;
		m_AdmCfg.bAdcCnt = abAdcCnt[dlg.m_NumOfAdc];

		m_DacCfg.bBits = abDacBits[dlg.m_DacBits];
		m_DacCfg.bEncoding = dlg.m_DacEncoding;
		m_DacCfg.wRange = dlg.m_DacRange;
		m_DacCfg.dMaxRate = dlg.m_DacRateMax;
		m_DacCfg.dMinRate = dlg.m_DacRateMin;
		m_AdmCfg.bDacCnt = abDacCnt[dlg.m_NumOfDac];
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}
