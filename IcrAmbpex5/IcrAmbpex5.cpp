// IcrAmbpex5.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAmbpex5App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAmbpex5.h"

// инициализация конфигурационных структур
ICR_CfgAmbpex5 m_Ambpex5Cfg = { AMBPEX5_CFG_TAG, 14, 1, 250000000, 0, 0, 156250000, 0};
ICR_CfgSram m_SramCfg = { SRAM_CFG_TAG, 4, 0, 2, 1, 11};

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

// CIcrAmbpex5App

BEGIN_MESSAGE_MAP(CIcrAmbpex5App, CWinApp)
END_MESSAGE_MAP()


// CIcrAmbpex5App construction

CIcrAmbpex5App::CIcrAmbpex5App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAmbpApp object

CIcrAmbpex5App theApp;


// CIcrAmbpex5App initialization

BOOL CIcrAmbpex5App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("AMBPEX5"));
		pDevInfo->dType = AMBPEX5;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("FMC105P"));
		pDevInfo->dType = FMC105P;
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
		case AMBPEX5_CFG_TAG:
			{
				PICR_CfgAmbpex5 pAmbpex5Cfg = (PICR_CfgAmbpex5)pCurCfgMem;
				m_Ambpex5Cfg.wTag = pAmbpex5Cfg->wTag;
				m_Ambpex5Cfg.wSize = pAmbpex5Cfg->wSize;
				m_Ambpex5Cfg.bAdmIfCnt = pAmbpex5Cfg->bAdmIfCnt;
				m_Ambpex5Cfg.dSysGen = pAmbpex5Cfg->dSysGen;
				m_Ambpex5Cfg.bDdsType = pAmbpex5Cfg->bDdsType;
				m_Ambpex5Cfg.bSPFCnt = pAmbpex5Cfg->bSPFCnt;
				m_Ambpex5Cfg.dRefGen5 = pAmbpex5Cfg->dRefGen5;
				m_Ambpex5Cfg.bSramCfgCnt = pAmbpex5Cfg->bSramCfgCnt;
				pDeviceInfo->bAdmIfCnt = pAmbpex5Cfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAmbpex5);
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

	m_Ambpex5Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAmbpex5 pAmbpex5Cfg = (PICR_CfgAmbpex5)pCurCfgMem;
	pAmbpex5Cfg->wTag = pDeviceInfo->dType;
	pAmbpex5Cfg->wSize = sizeof(ICR_CfgAmbpex5) - 4;
	pAmbpex5Cfg->bAdmIfCnt = m_Ambpex5Cfg.bAdmIfCnt;
	pAmbpex5Cfg->dSysGen = m_Ambpex5Cfg.dSysGen;
	pAmbpex5Cfg->bDdsType = m_Ambpex5Cfg.bDdsType;
	pAmbpex5Cfg->bSPFCnt = m_Ambpex5Cfg.bSPFCnt;
	pAmbpex5Cfg->dRefGen5 = m_Ambpex5Cfg.dRefGen5;
	pAmbpex5Cfg->bSramCfgCnt = m_Ambpex5Cfg.bSramCfgCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAmbpex5));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pAmbpex5Cfg->bSramCfgCnt)
	{
		for(int j = 0; j < pAmbpex5Cfg->bSramCfgCnt; j++)
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

	CIcrAmbpex5Dlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_Ambpex5Cfg.dSysGen;
	dlg.m_isDds = m_Ambpex5Cfg.bDdsType ? 1 : 0;
	dlg.m_DdsType = dlg.m_isDds ? (m_Ambpex5Cfg.bDdsType - 1) : -1;

	dlg.m_SfpCnt = m_Ambpex5Cfg.bSPFCnt;
	dlg.m_Gen5 = m_Ambpex5Cfg.dRefGen5 ? (m_Ambpex5Cfg.dRefGen5 / 1000000.) : 0;

	dlg.m_isSRAM = m_Ambpex5Cfg.bSramCfgCnt;

	dlg.m_SramChips = dlg.m_isSRAM ? (m_SramCfg.bChipCnt - 1) : -1;
	dlg.m_SramSize = m_SramCfg.bChipDepth;
	dlg.m_SramBitsWidth = m_SramCfg.bChipBitsWidth;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_Ambpex5Cfg.dSysGen != dlg.m_SysGen ||
			m_Ambpex5Cfg.bDdsType != (dlg.m_isDds ? (dlg.m_DdsType + 1) : 0) ||
			m_Ambpex5Cfg.bSramCfgCnt != dlg.m_isSRAM ||
			m_SramCfg.bNumber != dlg.m_isSRAM ||
			m_SramCfg.bChipCnt != (dlg.m_isSRAM ? (dlg.m_SramChips + 1) : 0) ||
			m_SramCfg.bChipDepth != dlg.m_SramSize ||
			m_SramCfg.bChipBitsWidth != dlg.m_SramBitsWidth ||
			m_Ambpex5Cfg.bSPFCnt != dlg.m_SfpCnt ||
			m_Ambpex5Cfg.dRefGen5 != dlg.m_Gen5
		)
			nResponse |= 0x100;

		m_Ambpex5Cfg.dSysGen = dlg.m_SysGen;
		m_Ambpex5Cfg.bDdsType = dlg.m_isDds ? (dlg.m_DdsType + 1) : 0;
		m_Ambpex5Cfg.bSramCfgCnt = dlg.m_isSRAM;
		m_Ambpex5Cfg.dRefGen5 = (ULONG)(dlg.m_Gen5 * 1000000.);
		m_Ambpex5Cfg.bSPFCnt = dlg.m_SfpCnt;

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
