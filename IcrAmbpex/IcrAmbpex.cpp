// IcrAmbpex.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAmbpexApp.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAmbpex.h"

// ������������� ���������������� ��������
ICR_CfgAmbpex m_AmbpexCfg = { AMBPEX1_CFG_TAG, 7, 1, 66000000, 0, 0};
ICR_CfgSram m_SramCfg = { SRAM_CFG_TAG, 4, 0, 1, 1, 2};

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

// CIcrAmbpexApp

BEGIN_MESSAGE_MAP(CIcrAmbpexApp, CWinApp)
END_MESSAGE_MAP()


// CIcrAmbpexApp construction

CIcrAmbpexApp::CIcrAmbpexApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAmbpApp object

CIcrAmbpexApp theApp;


// CIcrAmbpexApp initialization

BOOL CIcrAmbpexApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//***************************************************************************************
//  BASEMOD_GetInfo - ������� ������ ��� ����������� �������������� ������� �������
//  Input:  pNumDev - ��������� �� ����� (������������ ���������������, ������� � 0)
//          pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: pNumDev - ���� -1, �� ������ �������������� ������� ������� ���
//  Notes:  ������ ������� ���������� ������, � ����� � ��������, ������ *pNumDev
//***************************************************************************************
BASEMOD_API void __stdcall BASEMOD_GetInfo(int* pNumDev, PBASEMOD_INFO pDevInfo)
{
	int curNum = *pNumDev;
	switch(curNum)
	{
	case 0:
		lstrcpy(pDevInfo->sName, _T("AMBPEX1"));
		pDevInfo->dType = AMBPEX1;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("AMBPEX8"));
		pDevInfo->dType = AMBPEX8;
		break;
	default:
		*pNumDev = -1;
	}
	pDevInfo->pCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];
	pDevInfo->nCfgMemSize = BASEMOD_CFGMEM_SIZE;
}

//***************************************************************************************
//  BASEMOD_Close - ������� ������ ��� ������������ ������� ������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: 
//  Notes:  ������ ������� ���������� ����� ����������� ������ �������� ���������
//***************************************************************************************
BASEMOD_API void __stdcall BASEMOD_Close(PBASEMOD_INFO pDevInfo)
{
	delete[] pDevInfo->pCfgMem;
}

//***************************************************************************************
//  BASEMOD_SetProperty - ������� ������ ��� �������� �������� �� �������� ��������� � ������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - 
//  Notes:  ������ ������� ���������� ����� ��������� ������ �� ����� ��� ����������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_SetProperty(PBASEMOD_INFO pDeviceInfo)
{
	ULONG RealCfgSize = 0;
	PVOID pCurCfgMem = (PVOID)pDeviceInfo->pCfgMem;
	PVOID pEndCfgMem = (PVOID)(pDeviceInfo->pCfgMem + BASEMOD_CFGMEM_SIZE);
	int end_flag = 0;
	do
	{
		USHORT sign = *((PUSHORT)pCurCfgMem);
		USHORT size = 0;
		switch(sign)
		{
		case END_TAG:
		case ALT_END_TAG:
			end_flag = 1;
			RealCfgSize += 2;
			break;
		case SRAM_CFG_TAG:
			{
				PICR_CfgSram pSramCfg = (PICR_CfgSram)pCurCfgMem;
				m_SramCfg.wTag = pSramCfg->wTag;
				m_SramCfg.wSize = pSramCfg->wSize;
				m_SramCfg.bNumber = pSramCfg->bNumber;
				m_SramCfg.bChipCnt = pSramCfg->bChipCnt;
				m_SramCfg.bChipDepth = pSramCfg->bChipDepth;
				m_SramCfg.bChipBitsWidth = pSramCfg->bChipBitsWidth;
				size = sizeof(ICR_CfgSram);
				RealCfgSize += size;
				break;
			}
		//case DSPNODE_CFG_TAG:
		//	{
		//		PICR_CfgDspNode pDspNodeCfg = (PICR_CfgDspNode)pCurCfgMem;
		//		m_DspNodeCfg.wTag = pDspNodeCfg->wTag;
		//		m_DspNodeCfg.wSize = pDspNodeCfg->wSize;
		//		m_DspNodeCfg.bNumber = pDspNodeCfg->bNumber;
		//		m_DspNodeCfg.bPldType = pDspNodeCfg->bPldType;
		//		m_DspNodeCfg.wPldVolume = pDspNodeCfg->wPldVolume;
		//		m_DspNodeCfg.wPldPins = pDspNodeCfg->wPldPins;
		//		m_DspNodeCfg.bPldSpeedGrade = pDspNodeCfg->bPldSpeedGrade;
		//		m_DspNodeCfg.bSramCfgCnt = pDspNodeCfg->bSramCfgCnt;
		//		m_DspNodeCfg.bPioType = pDspNodeCfg->bPioType;
		//		m_DspNodeCfg.bLoadRom = pDspNodeCfg->bLoadRom;
		//		size = sizeof(ICR_CfgDspNode);
		//		RealCfgSize += size;
		//		break;
		//	}
		//case DDRSDRAM_CFG_TAG:
		//	{
		//		PICR_CfgDdrSdram pSdramCfg = (PICR_CfgDdrSdram)pCurCfgMem;
		//		m_SdramCfg.wTag = pSdramCfg->wTag;
		//		m_SdramCfg.wSize = pSdramCfg->wSize;
		//		m_SdramCfg.bNumber = pSdramCfg->bNumber;
		//		m_SdramCfg.bModuleCnt = pSdramCfg->bModuleCnt;
		//		m_SdramCfg.bColAddrBits = pSdramCfg->bColAddrBits;
		//		m_SdramCfg.bRowAddrBits = pSdramCfg->bRowAddrBits;
		//		m_SdramCfg.bModuleBanks = pSdramCfg->bModuleBanks;
		//		m_SdramCfg.bChipBanks = pSdramCfg->bChipBanks;
		//		m_SdramCfg.bPrimaryWidth = pSdramCfg->bPrimaryWidth;
		//		m_SdramCfg.bCasLatency = pSdramCfg->bCasLatency;
		//		size = sizeof(ICR_CfgDdrSdram);
		//		RealCfgSize += size;
		//		break;
		//	}
		case AMBPEX1_CFG_TAG:
		case AMBPEX8_CFG_TAG:
			{
				PICR_CfgAmbpex pAmbpexCfg = (PICR_CfgAmbpex)pCurCfgMem;
				m_AmbpexCfg.wTag = pAmbpexCfg->wTag;
				m_AmbpexCfg.wSize = pAmbpexCfg->wSize;
				m_AmbpexCfg.bAdmIfCnt = pAmbpexCfg->bAdmIfCnt;
				m_AmbpexCfg.dSysGen = pAmbpexCfg->dSysGen;
				m_AmbpexCfg.bDdsType = pAmbpexCfg->bDdsType;
				m_AmbpexCfg.bSramCfgCnt = pAmbpexCfg->bSramCfgCnt;
				pDeviceInfo->bAdmIfCnt = pAmbpexCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAmbpex);
				RealCfgSize += size;
				break;
			}
		default: 
			end_flag = 1;
			break;
		}
		pCurCfgMem = (PUCHAR)pCurCfgMem + size;
		if(pCurCfgMem >= pEndCfgMem)
			return 1;
	} while(!end_flag && pCurCfgMem < pEndCfgMem);
	pDeviceInfo->nRealCfgSize = RealCfgSize;
	return 0;
}

//***************************************************************************************
//  BASEMOD_SetProperty - ������� ������ ��� �������� �������� �� ������� � �������� ���������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - 0 - ��� ������, 1 - 
//  Notes:  ������ ������� ���������� ����� ������� ������ � ���� ��� ����������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_GetProperty(PBASEMOD_INFO pDeviceInfo)
{
	PUSHORT pCurCfgMem = (PUSHORT)pDeviceInfo->pCfgMem;
	PUSHORT pEndCfgMem = (PUSHORT)(pDeviceInfo->pCfgMem) + BASEMOD_CFGMEM_SIZE/2;

	m_AmbpexCfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAmbpex pAmbpexCfg = (PICR_CfgAmbpex)pCurCfgMem;
	pAmbpexCfg->wTag = pDeviceInfo->dType;//AMBVME_CFG_TAG;
	pAmbpexCfg->wSize = sizeof(ICR_CfgAmbpex) - 4;
	pAmbpexCfg->bAdmIfCnt = m_AmbpexCfg.bAdmIfCnt;
	pAmbpexCfg->dSysGen = m_AmbpexCfg.dSysGen;
	pAmbpexCfg->bDdsType = m_AmbpexCfg.bDdsType;
	pAmbpexCfg->bSramCfgCnt = m_AmbpexCfg.bSramCfgCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAmbpex));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pAmbpexCfg->bSramCfgCnt)
	{
		for(int j = 0; j < pAmbpexCfg->bSramCfgCnt; j++)
		{
			PICR_CfgSram pSramCfg = (PICR_CfgSram)pCurCfgMem;
			pSramCfg->wTag = SRAM_CFG_TAG;
			pSramCfg->wSize = sizeof(ICR_CfgSram) - 4;
			pSramCfg->bNumber = 0;
			pSramCfg->bChipCnt = m_SramCfg.bChipCnt;
			pSramCfg->bChipDepth = m_SramCfg.bChipDepth;
			pSramCfg->bChipBitsWidth = m_SramCfg.bChipBitsWidth;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgSram));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
	// ��� ��������� ������ �� ����� (��� ����� �������� ���������)
//	*pSignSize = END_TAG;
//	pSignSize++;
	pDeviceInfo->nRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
//  BASEMOD_DialogProperty - ������� ������ ��� ����������� �������, ������������ �������� �������� ����������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - IDOK ��� IDCANCEL
//  Notes:  ������ ������� ���������� �� ������� �� ��������������� ������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_DialogProperty(PBASEMOD_INFO pDeviceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CIcrAmbpexDlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_AmbpexCfg.dSysGen;
	dlg.m_isDds = m_AmbpexCfg.bDdsType ? 1 : 0;
	dlg.m_DdsType = dlg.m_isDds ? (m_AmbpexCfg.bDdsType - 1) : -1;
	
	dlg.m_isSRAM = m_AmbpexCfg.bSramCfgCnt;

	dlg.m_SramChips = dlg.m_isSRAM ? (m_SramCfg.bChipCnt - 1) : -1;
	dlg.m_SramSize = m_SramCfg.bChipDepth;
	dlg.m_SramBitsWidth = m_SramCfg.bChipBitsWidth;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_AmbpexCfg.dSysGen != dlg.m_SysGen ||
			m_AmbpexCfg.bDdsType != (dlg.m_isDds ? (dlg.m_DdsType + 1) : 0) ||
			m_AmbpexCfg.bSramCfgCnt != dlg.m_isSRAM ||
			m_SramCfg.bNumber != dlg.m_isSRAM ||
			m_SramCfg.bChipCnt != (dlg.m_isSRAM ? (dlg.m_SramChips + 1) : 0) ||
			m_SramCfg.bChipDepth != dlg.m_SramSize ||
			m_SramCfg.bChipBitsWidth != dlg.m_SramBitsWidth
		)
			nResponse |= 0x100;

		m_AmbpexCfg.dSysGen = dlg.m_SysGen;
		m_AmbpexCfg.bDdsType = dlg.m_isDds ? (dlg.m_DdsType + 1) : 0;
		m_AmbpexCfg.bSramCfgCnt = dlg.m_isSRAM;

		m_SramCfg.bNumber = dlg.m_isSRAM;
		m_SramCfg.bChipCnt = dlg.m_isSRAM ? (dlg.m_SramChips + 1) : 0;
		m_SramCfg.bChipDepth = dlg.m_SramSize;
		m_SramCfg.bChipBitsWidth = dlg.m_SramBitsWidth;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
