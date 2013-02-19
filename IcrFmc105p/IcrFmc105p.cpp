// IcrAmbpex5.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icrfmc105pApp.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "Icrfmc105p.h"

// инициализация конфигурационных структур
ICR_CfgFmc105p m_Fmc105pCfg = { FMC105P_CFG_TAG, 26, 1, 250000000, 0, 1, 0x48, 0, 50000000, 280000000, 0x49, 156250000, 100000000, 0 };
ICR_CfgDspNode m_DspNodeCfg = {DSPNODE_CFG_TAG, 10, 0, 22, 240, 1156, 0, 0, 0, 0};


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

// CIcrFmc105pApp

BEGIN_MESSAGE_MAP(CIcrFmc105pApp, CWinApp)
END_MESSAGE_MAP()


// CIcrAmbpex5App construction

CIcrFmc105pApp::CIcrFmc105pApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrFmc105pApp object

CIcrFmc105pApp theApp;


// CIcrFmc105pApp initialization

BOOL CIcrFmc105pApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//***************************************************************************************
//  BASEMOD_GetInfo - функция служит для определения поддерживаемых базовых модулей
//  Input:  pNumDev - указатель на номер (перебираются последовательно, начиная с 0)
//          pDevInfo - указатель на структуру для обмена информацией
//  Output: pNumDev - если -1, то больше поддерживаемых базовых модулей нет
//  Notes:  данная функция вызывается первой, в цикле с индексом, равным *pNumDev
//***************************************************************************************
BASEMOD_API void __stdcall BASEMOD_GetInfo(int* pNumDev, PBASEMOD_INFO pDevInfo)
{
	int curNum = *pNumDev;
	switch(curNum)
	{
	case 0:
		lstrcpy(pDevInfo->sName, _T("FMC105P"));
		pDevInfo->dType = FMC105P;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("FMC106P"));
		pDevInfo->dType = FMC106P;
		break;
	case 2:
		lstrcpy(pDevInfo->sName, _T("FMC114V"));
		pDevInfo->dType = FMC114V;
		break;
	case 3:
		lstrcpy(pDevInfo->sName, _T("FMC115cP"));
		pDevInfo->dType = FMC115CP;
		break;
	case 4:
		lstrcpy(pDevInfo->sName, _T("FMC110P"));
		pDevInfo->dType = FMC110P;
		break;
	case 5:
		lstrcpy(pDevInfo->sName, _T("FMC113E"));
		pDevInfo->dType = FMC113E;
		break;
	case 6:
		lstrcpy(pDevInfo->sName, _T("FMC108V"));
		pDevInfo->dType = FMC108V;
		break;
	case 7:
		lstrcpy(pDevInfo->sName, _T("FMC103E2"));
		pDevInfo->dType = FMC103E2;
		break;
	case 8:
		lstrcpy(pDevInfo->sName, _T("FMC112cP"));
		pDevInfo->dType = FMC112CP;
		break;
	default:
		*pNumDev = -1;
	}
	pDevInfo->pCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];
	pDevInfo->nCfgMemSize = BASEMOD_CFGMEM_SIZE;
}

//***************************************************************************************
//  BASEMOD_Close - функция служит для освобождения занятой памяти
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: 
//  Notes:  данная функция вызывается перед завершением работы основной программы
//***************************************************************************************
BASEMOD_API void __stdcall BASEMOD_Close(PBASEMOD_INFO pDevInfo)
{
	delete[] pDevInfo->pCfgMem;
}

//***************************************************************************************
//  BASEMOD_SetProperty - функция служит для передачи значений из основной программы в плагин
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 
//  Notes:  данная функция вызывается после получения данных из файла или устройства
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
		//case SRAM_CFG_TAG:
		//	{
		//		PICR_CfgSram pSramCfg = (PICR_CfgSram)pCurCfgMem;
		//		m_SramCfg.wTag = pSramCfg->wTag;
		//		m_SramCfg.wSize = pSramCfg->wSize;
		//		m_SramCfg.bNumber = pSramCfg->bNumber;
		//		m_SramCfg.bChipCnt = pSramCfg->bChipCnt;
		//		m_SramCfg.bChipDepth = pSramCfg->bChipDepth;
		//		m_SramCfg.bChipBitsWidth = pSramCfg->bChipBitsWidth;
		//		size = sizeof(ICR_CfgSram);
		//		RealCfgSize += size;
		//		break;
		//	}
		case DSPNODE_CFG_TAG:
			{
				PICR_CfgDspNode pDspNodeCfg = (PICR_CfgDspNode)pCurCfgMem;
				m_DspNodeCfg.wTag = pDspNodeCfg->wTag;
				m_DspNodeCfg.wSize = pDspNodeCfg->wSize;
				m_DspNodeCfg.bNumber = pDspNodeCfg->bNumber;
				m_DspNodeCfg.bPldType = pDspNodeCfg->bPldType;
				m_DspNodeCfg.wPldVolume = pDspNodeCfg->wPldVolume;
				m_DspNodeCfg.wPldPins = pDspNodeCfg->wPldPins;
				m_DspNodeCfg.bPldSpeedGrade = pDspNodeCfg->bPldSpeedGrade;
				m_DspNodeCfg.bPioType = 0;
				m_DspNodeCfg.bSramCfgCnt = 0;
				m_DspNodeCfg.bLoadRom = 0;
				size = sizeof(ICR_CfgDspNode);
				RealCfgSize += size;
				break;
			}
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
		case FMC105P_CFG_TAG:
		case FMC106P_CFG_TAG:
		case FMC103E2_CFG_TAG:
		case FMC114V_CFG_TAG:
		case FMC110P_CFG_TAG:
		case FMC113E_CFG_TAG:
		case FMC108V_CFG_TAG:
		case FMC115СP_CFG_TAG:
		case FMC112CP_CFG_TAG:
			{
				PICR_CfgFmc105p pFmc105pCfg = (PICR_CfgFmc105p)pCurCfgMem;
				m_Fmc105pCfg.wTag = pFmc105pCfg->wTag;
				m_Fmc105pCfg.wSize = pFmc105pCfg->wSize;
				m_Fmc105pCfg.bAdmIfCnt = pFmc105pCfg->bAdmIfCnt;
				m_Fmc105pCfg.dSysGen = pFmc105pCfg->dSysGen;
				m_Fmc105pCfg.bDdsType = pFmc105pCfg->bDdsType;
				m_Fmc105pCfg.bSwitchType = pFmc105pCfg->bSwitchType;
				m_Fmc105pCfg.bAdrSwitch = pFmc105pCfg->bAdrSwitch;
				m_Fmc105pCfg.bGen0Type = pFmc105pCfg->bGen0Type;
				m_Fmc105pCfg.nRefGen0 = pFmc105pCfg->nRefGen0;
				m_Fmc105pCfg.nRefMaxGen0 = pFmc105pCfg->nRefMaxGen0;
				m_Fmc105pCfg.bAdrGen0 = pFmc105pCfg->bAdrGen0;
				m_Fmc105pCfg.dRefGen5 = pFmc105pCfg->dRefGen5;
				m_Fmc105pCfg.dRefGen6 = pFmc105pCfg->dRefGen6;
				m_Fmc105pCfg.bDspNodeCfgCnt = pFmc105pCfg->bDspNodeCfgCnt;
				pDeviceInfo->bAdmIfCnt = pFmc105pCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgFmc105p);
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
//  BASEMOD_SetProperty - функция служит для передачи значений из плагина в основную программу
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 0 - нет ошибок, 1 - 
//  Notes:  данная функция вызывается перед записью данных в файл или устройство
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_GetProperty(PBASEMOD_INFO pDeviceInfo)
{
	PUSHORT pCurCfgMem = (PUSHORT)pDeviceInfo->pCfgMem;
	PUSHORT pEndCfgMem = (PUSHORT)(pDeviceInfo->pCfgMem) + BASEMOD_CFGMEM_SIZE/2;

	m_Fmc105pCfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgFmc105p pFmc105pCfg = (PICR_CfgFmc105p)pCurCfgMem;
	pFmc105pCfg->wTag = pDeviceInfo->dType;
	pFmc105pCfg->wSize = sizeof(ICR_CfgFmc105p) - 4;
	pFmc105pCfg->bAdmIfCnt = m_Fmc105pCfg.bAdmIfCnt;
	pFmc105pCfg->dSysGen = m_Fmc105pCfg.dSysGen;
	pFmc105pCfg->bDdsType = m_Fmc105pCfg.bDdsType;
	pFmc105pCfg->bSwitchType = m_Fmc105pCfg.bSwitchType;
	pFmc105pCfg->bAdrSwitch = m_Fmc105pCfg.bAdrSwitch;
	pFmc105pCfg->bGen0Type = m_Fmc105pCfg.bGen0Type;
	pFmc105pCfg->nRefGen0 = m_Fmc105pCfg.nRefGen0;
	pFmc105pCfg->nRefMaxGen0 = m_Fmc105pCfg.nRefMaxGen0;
	pFmc105pCfg->bAdrGen0 = m_Fmc105pCfg.bAdrGen0;
	pFmc105pCfg->dRefGen5 = m_Fmc105pCfg.dRefGen5;
	pFmc105pCfg->dRefGen6 = m_Fmc105pCfg.dRefGen6;
	pFmc105pCfg->bDspNodeCfgCnt = m_Fmc105pCfg.bDspNodeCfgCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgFmc105p));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pFmc105pCfg->bDspNodeCfgCnt)
	{
		for(int j = 0; j < pFmc105pCfg->bDspNodeCfgCnt; j++)
		{
			PICR_CfgDspNode pDspCfg = (PICR_CfgDspNode)pCurCfgMem;
			pDspCfg->wTag = DSPNODE_CFG_TAG;
			pDspCfg->wSize = sizeof(ICR_CfgDspNode) - 4;
			pDspCfg->bNumber = 0;
			pDspCfg->bPldType = m_DspNodeCfg.bPldType;
			pDspCfg->wPldVolume = m_DspNodeCfg.wPldVolume;
			pDspCfg->wPldPins = m_DspNodeCfg.wPldPins;
			pDspCfg->bPldSpeedGrade = m_DspNodeCfg.bPldSpeedGrade;
			pDspCfg->bPioType = 0;
			pDspCfg->bSramCfgCnt = 0;
			pDspCfg->bLoadRom = 0;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDspNode));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
	// тэг окончания данных не нужен (его пишет основная программа)
//	*pSignSize = END_TAG;
//	pSignSize++;
	pDeviceInfo->nRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

//***************************************************************************************
//  BASEMOD_DialogProperty - функция служит для отображения диалога, позволяющего изменить значения параметров
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - IDOK или IDCANCEL
//  Notes:  данная функция вызывается по нажатию на соответствующую кнопку
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_DialogProperty(PBASEMOD_INFO pDeviceInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CIcrFmc105pDlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_Fmc105pCfg.dSysGen;
	dlg.m_isDds = m_Fmc105pCfg.bDdsType ? 1 : 0;
	dlg.m_DdsType = dlg.m_isDds ? (m_Fmc105pCfg.bDdsType - 1) : -1;
	dlg.m_isSwitch = m_Fmc105pCfg.bSwitchType ? 1 : 0;
	dlg.m_SwitchType = dlg.m_isSwitch ? (m_Fmc105pCfg.bSwitchType - 1) : -1;
	dlg.m_AdrSwitch = m_Fmc105pCfg.bAdrSwitch;

	dlg.m_Gen0Type = m_Fmc105pCfg.bGen0Type;
	dlg.m_RefGen0 = m_Fmc105pCfg.nRefGen0;
	dlg.m_RefMaxGen0 = m_Fmc105pCfg.nRefMaxGen0;
	dlg.m_AdrGen0 = m_Fmc105pCfg.bAdrGen0;

	dlg.m_DspNodeCnt = m_Fmc105pCfg.bDspNodeCfgCnt;

	dlg.m_Gen5 = m_Fmc105pCfg.dRefGen5 ? (m_Fmc105pCfg.dRefGen5 / 1000000.) : 0;
	dlg.m_Gen6 = m_Fmc105pCfg.dRefGen6 ? (m_Fmc105pCfg.dRefGen6 / 1000000.) : 0;

	dlg.m_DspNodeNum = m_DspNodeCfg.bNumber;
	dlg.m_DspPldType = m_DspNodeCfg.bPldType - 21;
	dlg.m_DspPldVolume = m_DspNodeCfg.wPldVolume;
	dlg.m_DspPldPins = m_DspNodeCfg.wPldPins;
	dlg.m_DspPldRate = m_DspNodeCfg.bPldSpeedGrade;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_Fmc105pCfg.dSysGen != dlg.m_SysGen ||
			m_Fmc105pCfg.bDdsType != (dlg.m_isDds ? (dlg.m_DdsType + 1) : 0) ||
			m_Fmc105pCfg.bSwitchType != (dlg.m_isSwitch ? (dlg.m_SwitchType + 1) : 0) ||
			m_Fmc105pCfg.bAdrSwitch != dlg.m_AdrSwitch ||
			m_Fmc105pCfg.bDspNodeCfgCnt != dlg.m_DspNodeCnt ||
			m_DspNodeCfg.bNumber != dlg.m_DspNodeNum ||
			m_DspNodeCfg.bPldType != dlg.m_DspPldType ||
			m_DspNodeCfg.wPldVolume != dlg.m_DspPldVolume ||
			m_DspNodeCfg.wPldPins != dlg.m_DspPldPins ||
			m_DspNodeCfg.bPldSpeedGrade != dlg.m_DspPldRate ||
			m_Fmc105pCfg.bGen0Type != dlg.m_Gen0Type ||
			m_Fmc105pCfg.nRefGen0 != dlg.m_RefGen0 ||
			m_Fmc105pCfg.nRefMaxGen0 != dlg.m_RefMaxGen0 ||
			m_Fmc105pCfg.bAdrGen0 != dlg.m_AdrGen0 ||
			m_Fmc105pCfg.dRefGen5 != dlg.m_Gen5 ||
			m_Fmc105pCfg.dRefGen6 != dlg.m_Gen6
		)
			nResponse |= 0x100;

		m_Fmc105pCfg.dSysGen = dlg.m_SysGen;
		m_Fmc105pCfg.bDdsType = dlg.m_isDds ? (dlg.m_DdsType + 1) : 0;
		m_Fmc105pCfg.bSwitchType = dlg.m_isSwitch ? (dlg.m_SwitchType + 1) : 0;
		m_Fmc105pCfg.bAdrSwitch = dlg.m_AdrSwitch;
		m_Fmc105pCfg.bGen0Type = dlg.m_Gen0Type;
		m_Fmc105pCfg.nRefGen0 = dlg.m_RefGen0;
		m_Fmc105pCfg.nRefMaxGen0 = dlg.m_RefMaxGen0;
		m_Fmc105pCfg.bAdrGen0 = dlg.m_AdrGen0;
		m_Fmc105pCfg.dRefGen5 = (ULONG)(dlg.m_Gen5 * 1000000.);
		m_Fmc105pCfg.dRefGen6 = (ULONG)(dlg.m_Gen6 * 1000000.);
		m_Fmc105pCfg.bDspNodeCfgCnt = dlg.m_DspNodeCnt;

		m_DspNodeCfg.bNumber = dlg.m_DspNodeNum;
		m_DspNodeCfg.bPldType = dlg.m_DspPldType + 21;
		m_DspNodeCfg.wPldVolume = dlg.m_DspPldVolume;
		m_DspNodeCfg.wPldPins = dlg.m_DspPldPins;
		m_DspNodeCfg.bPldSpeedGrade = dlg.m_DspPldRate;
		m_DspNodeCfg.bPioType = 0;
		m_DspNodeCfg.bSramCfgCnt = 0;
		m_DspNodeCfg.bLoadRom = 0;

	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
