// IcrVK3.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrVK3App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "IcrVK3.h"

// ������������� ���������������� ��������
ICR_CfgVK3 m_AdpVK3Cfg = {VK3_CFG_TAG, 57, 0, 1, 66666000, 10000000, 1, 8, 1, 1, 1, 
"PLP-15", 64, 16, 80, 80, 1700, 75, 1, 1, 1, 1, "PLP-15", 512, 14, 1100, 75};

_ICR_Cfg0510	m_PldType = {PLD_CFG_TAG, 0, 0, 0, 1400, 676, 5};	// ��� ����

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


// CIcrVK3App

BEGIN_MESSAGE_MAP(CIcrVK3App, CWinApp)
END_MESSAGE_MAP()


// CIcrVK3App construction

CIcrVK3App::CIcrVK3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrVK3App object

CIcrVK3App theApp;


// CIcrVK3App initialization

BOOL CIcrVK3App::InitInstance()
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
		lstrcpy(pDevInfo->sName, "VK3");
		pDevInfo->dType = VK3;
		break;
	default:
		*pNumDev = -1;
		return;
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

		case PLD_CFG_TAG:
		{
			PICR_Cfg0510 pPldType = (PICR_Cfg0510)pCurCfgMem;
			m_PldType.bType = pPldType->bType;
			m_PldType.wVolume = pPldType->wVolume;
			m_PldType.bSpeedGrade = pPldType->bSpeedGrade;
			m_PldType.wPins = pPldType->wPins;
			size = sizeof(ICR_Cfg0510);
			RealCfgSize += size;
			break;
		}

		case VK3_CFG_TAG:
		{
			PICR_CfgVK3 pAdpCfg = (PICR_CfgVK3)pCurCfgMem;
			m_AdpVK3Cfg.wTag = pAdpCfg->wTag;
			m_AdpVK3Cfg.wSize = pAdpCfg->wSize;
			m_AdpVK3Cfg.nNum = pAdpCfg->nNum;
			m_AdpVK3Cfg.bDdrModuleNum = pAdpCfg->bDdrModuleNum;
			m_AdpVK3Cfg.nSysGen = pAdpCfg->nSysGen;
			m_AdpVK3Cfg.nRefGen = pAdpCfg->nRefGen;
			m_AdpVK3Cfg.bDacBiasBits = pAdpCfg->bDacBiasBits;
			m_AdpVK3Cfg.isDacBias = pAdpCfg->isDacBias;
			m_AdpVK3Cfg.bAdcChanNum = pAdpCfg->bAdcChanNum;
			m_AdpVK3Cfg.bAdcInpNum = pAdpCfg->bAdcInpNum;
			strcpy((char*)m_AdpVK3Cfg.abAdcTypeF, (char*)pAdpCfg->abAdcTypeF);
			m_AdpVK3Cfg.nAdcBiasRange = pAdpCfg->nAdcBiasRange;
			m_AdpVK3Cfg.bAdcBits = pAdpCfg->bAdcBits;
			m_AdpVK3Cfg.wAdcMaxfreqSampl = pAdpCfg->wAdcMaxfreqSampl;
			m_AdpVK3Cfg.wDacMaxfreqSampl = pAdpCfg->wDacMaxfreqSampl;
			m_AdpVK3Cfg.wInpAmplRange = pAdpCfg->wInpAmplRange;
			m_AdpVK3Cfg.nInpR = pAdpCfg->nInpR;
			m_AdpVK3Cfg.isAdcInpAdd = pAdpCfg->isAdcInpAdd;
			m_AdpVK3Cfg.isTuner = pAdpCfg->isTuner;
			m_AdpVK3Cfg.isSelectorSinch = pAdpCfg->isSelectorSinch;
			m_AdpVK3Cfg.bDacChanNum = pAdpCfg->bDacChanNum;
			m_AdpVK3Cfg.bDacOutNum = pAdpCfg->bDacOutNum;
			strcpy((char*)m_AdpVK3Cfg.abDacTypeF, (char*)pAdpCfg->abDacTypeF);
			m_AdpVK3Cfg.nDacBiasRange = pAdpCfg->nDacBiasRange;
			m_AdpVK3Cfg.bDacBits = pAdpCfg->bDacBits;
			m_AdpVK3Cfg.nOutAmplRange = pAdpCfg->nOutAmplRange;
			m_AdpVK3Cfg.nOutR = pAdpCfg->nOutR;
			size = sizeof(ICR_CfgVK3);
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
//  BASEMOD_GetProperty - ������� ������ ��� �������� �������� �� ������� � �������� ���������
//  Input:  pDevInfo - ��������� �� ��������� ��� ������ �����������
//  Output: return - 0 - ��� ������, 1 - 
//  Notes:  ������ ������� ���������� ����� ������� ������ � ���� ��� ����������
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_GetProperty(PBASEMOD_INFO pDeviceInfo)
{
	PUSHORT pCurCfgMem = (PUSHORT)pDeviceInfo->pCfgMem;
	PUSHORT pEndCfgMem = (PUSHORT)(pDeviceInfo->pCfgMem) + BASEMOD_CFGMEM_SIZE/2;

	PICR_CfgVK3 pAdpCfg = (PICR_CfgVK3)pCurCfgMem;
	pAdpCfg->wTag = VK3_CFG_TAG;
	pAdpCfg->wSize = sizeof(ICR_CfgVK3) - 4;
	pAdpCfg->nNum = m_AdpVK3Cfg.nNum;
	pAdpCfg->bDdrModuleNum = m_AdpVK3Cfg.bDdrModuleNum;
	pAdpCfg->nSysGen = m_AdpVK3Cfg.nSysGen;
	pAdpCfg->nRefGen = m_AdpVK3Cfg.nRefGen;
	pAdpCfg->bDacBiasBits = m_AdpVK3Cfg.bDacBiasBits;
	pAdpCfg->isDacBias = m_AdpVK3Cfg.isDacBias;
	pAdpCfg->bAdcChanNum = m_AdpVK3Cfg.bAdcChanNum;
	pAdpCfg->bAdcInpNum = m_AdpVK3Cfg.bAdcInpNum;
	strcpy((char*)pAdpCfg->abAdcTypeF, (char*)m_AdpVK3Cfg.abAdcTypeF);
	pAdpCfg->nAdcBiasRange = m_AdpVK3Cfg.nAdcBiasRange;
	pAdpCfg->bAdcBits = m_AdpVK3Cfg.bAdcBits;
	pAdpCfg->wAdcMaxfreqSampl = m_AdpVK3Cfg.wAdcMaxfreqSampl;
	pAdpCfg->wDacMaxfreqSampl = m_AdpVK3Cfg.wDacMaxfreqSampl;
	pAdpCfg->wInpAmplRange = m_AdpVK3Cfg.wInpAmplRange;
	pAdpCfg->nInpR = m_AdpVK3Cfg.nInpR;
	pAdpCfg->isAdcInpAdd = m_AdpVK3Cfg.isAdcInpAdd;
	pAdpCfg->isTuner = m_AdpVK3Cfg.isTuner;
	pAdpCfg->isSelectorSinch = m_AdpVK3Cfg.isSelectorSinch;
	pAdpCfg->bDacChanNum = m_AdpVK3Cfg.bDacChanNum;
	pAdpCfg->bDacOutNum = m_AdpVK3Cfg.bDacOutNum;
	strcpy((char*)pAdpCfg->abDacTypeF, (char*)m_AdpVK3Cfg.abDacTypeF);
	pAdpCfg->nDacBiasRange = m_AdpVK3Cfg.nDacBiasRange;
	pAdpCfg->bDacBits = m_AdpVK3Cfg.bDacBits;
	pAdpCfg->nOutAmplRange = m_AdpVK3Cfg.nOutAmplRange;
	pAdpCfg->nOutR = m_AdpVK3Cfg.nOutR;
	
	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgVK3));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_Cfg0510 pPldType = (PICR_Cfg0510)pCurCfgMem;
	pPldType->wTag = PLD_CFG_TAG; 
	pPldType->bType = m_PldType.bType;
	pPldType->wVolume = m_PldType.wVolume;
	pPldType->bSpeedGrade = m_PldType.bSpeedGrade;
	pPldType->wPins = m_PldType.wPins;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_Cfg0510));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

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

	IcrVK3Dlg dlg;

	dlg.m_nNum = m_AdpVK3Cfg.nNum;
	dlg.m_bDdrModuleNum = m_AdpVK3Cfg.bDdrModuleNum;
	dlg.m_dSysGen = (double)m_AdpVK3Cfg.nSysGen / (double)1000000;
	dlg.m_dRefGen = (double)m_AdpVK3Cfg.nRefGen / (double)1000000;
	dlg.m_bDacBiasBits = m_AdpVK3Cfg.bDacBiasBits;
	dlg.m_isDacBias = m_AdpVK3Cfg.isDacBias;
	dlg.m_bAdcChanNum = m_AdpVK3Cfg.bAdcChanNum;
	dlg.m_bAdcInpNum = m_AdpVK3Cfg.bAdcInpNum;
	dlg.m_sAdcTypeF.SetString((char*)m_AdpVK3Cfg.abAdcTypeF);
	dlg.m_nAdcBiasRange = m_AdpVK3Cfg.nAdcBiasRange;
	dlg.m_bAdcBits = m_AdpVK3Cfg.bAdcBits;
	dlg.m_nAdcMaxfreqSampl = m_AdpVK3Cfg.wAdcMaxfreqSampl;
	dlg.m_nDacMaxfreqSampl = m_AdpVK3Cfg.wDacMaxfreqSampl;
	dlg.m_nInpAmplRange = m_AdpVK3Cfg.wInpAmplRange;
	dlg.m_nInpR = m_AdpVK3Cfg.nInpR;
	dlg.m_isAdcInpAdd = m_AdpVK3Cfg.isAdcInpAdd;
	dlg.m_isTuner = m_AdpVK3Cfg.isTuner;
	dlg.m_isSelectorSinch = m_AdpVK3Cfg.isSelectorSinch;
	dlg.m_bDacChanNum = m_AdpVK3Cfg.bDacChanNum;
	dlg.m_bDacOutNum = m_AdpVK3Cfg.bDacOutNum;
	dlg.m_sDacTypeF.SetString((char*)m_AdpVK3Cfg.abDacTypeF);
	dlg.m_nDacBiasRange = m_AdpVK3Cfg.nDacBiasRange;
	dlg.m_bDacBits = m_AdpVK3Cfg.bDacBits;
	dlg.m_nOutAmplRange = m_AdpVK3Cfg.nOutAmplRange;
	dlg.m_nOutR = m_AdpVK3Cfg.nOutR;
	
	dlg.m_bType = m_PldType.bType;
	dlg.m_nVolume = m_PldType.wVolume;
	dlg.m_bSpeedGrade = m_PldType.bSpeedGrade;
	dlg.m_nPins = m_PldType.wPins;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_AdpVK3Cfg.nNum = dlg.m_nNum;
		m_AdpVK3Cfg.bDdrModuleNum = dlg.m_bDdrModuleNum;
		m_AdpVK3Cfg.nSysGen = dlg.m_dSysGen * 1000000;
		m_AdpVK3Cfg.nRefGen = dlg.m_dRefGen * 1000000;
		m_AdpVK3Cfg.bDacBiasBits = dlg.m_bDacBiasBits;
		m_AdpVK3Cfg.isDacBias = dlg.m_isDacBias;
		m_AdpVK3Cfg.bAdcChanNum = dlg.m_bAdcChanNum;
		m_AdpVK3Cfg.bAdcInpNum = dlg.m_bAdcInpNum;
		strcpy((char*)m_AdpVK3Cfg.abAdcTypeF, dlg.m_sAdcTypeF.GetString());
		m_AdpVK3Cfg.nAdcBiasRange = dlg.m_nAdcBiasRange;
		m_AdpVK3Cfg.bAdcBits = dlg.m_bAdcBits;
		m_AdpVK3Cfg.wAdcMaxfreqSampl = dlg.m_nAdcMaxfreqSampl;
		m_AdpVK3Cfg.wDacMaxfreqSampl = dlg.m_nDacMaxfreqSampl;
		m_AdpVK3Cfg.wInpAmplRange = dlg.m_nInpAmplRange;
		m_AdpVK3Cfg.nInpR = dlg.m_nInpR;
		m_AdpVK3Cfg.isAdcInpAdd = dlg.m_isAdcInpAdd;
		m_AdpVK3Cfg.isTuner = dlg.m_isTuner;
		m_AdpVK3Cfg.isSelectorSinch = dlg.m_isSelectorSinch;
		m_AdpVK3Cfg.bDacChanNum = dlg.m_bDacChanNum;
		m_AdpVK3Cfg.bDacOutNum = dlg.m_bDacOutNum;
		strcpy((char*)m_AdpVK3Cfg.abDacTypeF, dlg.m_sDacTypeF.GetString());
		m_AdpVK3Cfg.nDacBiasRange = dlg.m_nDacBiasRange;
		m_AdpVK3Cfg.bDacBits = dlg.m_bDacBits;
		m_AdpVK3Cfg.nOutAmplRange = dlg.m_nOutAmplRange;
		m_AdpVK3Cfg.nOutR = dlg.m_nOutR;
		
		m_PldType.bType = dlg.m_bType;
		m_PldType.wVolume = dlg.m_nVolume;
		m_PldType.bSpeedGrade = dlg.m_bSpeedGrade;
		m_PldType.wPins = dlg.m_nPins;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}