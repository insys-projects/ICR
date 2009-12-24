// IcrAmbp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAmbpApp.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAmbp.h"

// инициализация конфигурационных структур
ICR_CfgAmbp m_AmbpCfg = { AMBPCD_CFG_TAG, 8, 1, 66000000, 0, 0, 0};
//ICR_CfgAmbp m_AmbpcdCfg = { AMBPCD_CFG_TAG, 4, 1, 2, 0, 0};
//ICR_CfgAmbp m_AmbpcxCfg = { AMBPCX_CFG_TAG, 4, 1, 0, 0, 0};
ICR_CfgDdrSdram m_SdramCfg = { DDRSDRAM_CFG_TAG, 7, 0, 1, 13, 9, 1, 4, 4, 2};
ICR_CfgDspNode m_DspNodeCfg = {DSPNODE_CFG_TAG, 10, 0, 4, 1000, 896, 5, 0, 0, 0};
ICR_CfgSram m_SramCfg = { SRAM_CFG_TAG, 4, 0, 0, 1, 2};

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

// CIcrAmbpApp

BEGIN_MESSAGE_MAP(CIcrAmbpApp, CWinApp)
END_MESSAGE_MAP()


// CIcrAmbpApp construction

CIcrAmbpApp::CIcrAmbpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAmbpApp object

CIcrAmbpApp theApp;


// CIcrAmbpApp initialization

BOOL CIcrAmbpApp::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("AMBPCD"));
		pDevInfo->dType = AMBPCD;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("AMBPCX"));
		pDevInfo->dType = AMBPCX;
		break;
	case 2:
		lstrcpy(pDevInfo->sName, _T("AMBPEX2"));
		pDevInfo->dType = AMBPEX2;
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
				m_DspNodeCfg.bSramCfgCnt = pDspNodeCfg->bSramCfgCnt;
				m_DspNodeCfg.bPioType = pDspNodeCfg->bPioType;
				m_DspNodeCfg.bLoadRom = pDspNodeCfg->bLoadRom;
				size = sizeof(ICR_CfgDspNode);
				RealCfgSize += size;
				break;
			}
		case DDRSDRAM_CFG_TAG:
			{
				PICR_CfgDdrSdram pSdramCfg = (PICR_CfgDdrSdram)pCurCfgMem;
				m_SdramCfg.wTag = pSdramCfg->wTag;
				m_SdramCfg.wSize = pSdramCfg->wSize;
				m_SdramCfg.bNumber = pSdramCfg->bNumber;
				m_SdramCfg.bModuleCnt = pSdramCfg->bModuleCnt;
				m_SdramCfg.bColAddrBits = pSdramCfg->bColAddrBits;
				m_SdramCfg.bRowAddrBits = pSdramCfg->bRowAddrBits;
				m_SdramCfg.bModuleBanks = pSdramCfg->bModuleBanks;
				m_SdramCfg.bChipBanks = pSdramCfg->bChipBanks;
				m_SdramCfg.bPrimaryWidth = pSdramCfg->bPrimaryWidth;
				m_SdramCfg.bCasLatency = pSdramCfg->bCasLatency;
				size = sizeof(ICR_CfgDdrSdram);
				RealCfgSize += size;
				break;
			}
		case AMBPCD_CFG_TAG:
		case AMBPCX_CFG_TAG:
		case AMBPEX2_CFG_TAG:
			{
				PICR_CfgAmbp pAmbpCfg = (PICR_CfgAmbp)pCurCfgMem;
				m_AmbpCfg.wTag = pAmbpCfg->wTag;
				m_AmbpCfg.wSize = pAmbpCfg->wSize;
				m_AmbpCfg.bAdmIfCnt = pAmbpCfg->bAdmIfCnt;
				m_AmbpCfg.dSysGen = pAmbpCfg->dSysGen;
				m_AmbpCfg.bSdramSlotCnt = pAmbpCfg->bSdramSlotCnt;
				m_AmbpCfg.bSdramCfgCnt = pAmbpCfg->bSdramCfgCnt;
				m_AmbpCfg.bDspNodeCfgCnt = pAmbpCfg->bDspNodeCfgCnt;
				pDeviceInfo->bAdmIfCnt = pAmbpCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAmbp);
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

	m_AmbpCfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAmbp pAmbpCfg = (PICR_CfgAmbp)pCurCfgMem;
	pAmbpCfg->wTag = pDeviceInfo->dType;//AMBVME_CFG_TAG;
	pAmbpCfg->wSize = sizeof(ICR_CfgAmbp) - 4;
	pAmbpCfg->bAdmIfCnt = m_AmbpCfg.bAdmIfCnt;
	pAmbpCfg->dSysGen = m_AmbpCfg.dSysGen;
	pAmbpCfg->bSdramSlotCnt = m_AmbpCfg.bSdramSlotCnt;
	pAmbpCfg->bSdramCfgCnt = m_AmbpCfg.bSdramCfgCnt;
	pAmbpCfg->bDspNodeCfgCnt = m_AmbpCfg.bDspNodeCfgCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAmbp));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pAmbpCfg->bSdramCfgCnt)
	{
		for(int i = 0; i < pAmbpCfg->bSdramCfgCnt; i++)
		{
			PICR_CfgDdrSdram pSdramCfg = (PICR_CfgDdrSdram)pCurCfgMem;
			pSdramCfg->wTag = DDRSDRAM_CFG_TAG;
			pSdramCfg->wSize = sizeof(ICR_CfgSdram) - 4;
			pSdramCfg->bNumber = 0;
			pSdramCfg->bModuleCnt = m_SdramCfg.bModuleCnt;
			pSdramCfg->bColAddrBits = m_SdramCfg.bColAddrBits;
			pSdramCfg->bRowAddrBits = m_SdramCfg.bRowAddrBits;
			pSdramCfg->bModuleBanks = m_SdramCfg.bModuleBanks;
			pSdramCfg->bChipBanks = m_SdramCfg.bChipBanks;
			pSdramCfg->bPrimaryWidth = m_SdramCfg.bPrimaryWidth;
			pSdramCfg->bCasLatency = m_SdramCfg.bCasLatency;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDdrSdram));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
	if(pAmbpCfg->bDspNodeCfgCnt)
	{
		for(int i = 0; i < pAmbpCfg->bDspNodeCfgCnt; i++)
		{
			PICR_CfgDspNode pDspCfg = (PICR_CfgDspNode)pCurCfgMem;
			pDspCfg->wTag = DSPNODE_CFG_TAG;
			pDspCfg->wSize = sizeof(ICR_CfgDspNode) - 4;
			pDspCfg->bNumber = 0;
			pDspCfg->bPldType = m_DspNodeCfg.bPldType;
			pDspCfg->wPldVolume = m_DspNodeCfg.wPldVolume;
			pDspCfg->wPldPins = m_DspNodeCfg.wPldPins;
			pDspCfg->bPldSpeedGrade = m_DspNodeCfg.bPldSpeedGrade;
			pDspCfg->bSramCfgCnt = m_DspNodeCfg.bSramCfgCnt;
			pDspCfg->bPioType = m_DspNodeCfg.bPioType;
			pDspCfg->bLoadRom = m_DspNodeCfg.bLoadRom;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDspNode));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
			
			if(pDspCfg->bSramCfgCnt)
			{
				for(int j = 0; j < pDspCfg->bSramCfgCnt; j++)
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

	CIcrAmbpDlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_AmbpCfg.dSysGen;
	dlg.m_SlotCnt = m_AmbpCfg.bSdramSlotCnt;
	dlg.m_SdramCnt = m_AmbpCfg.bSdramCfgCnt;
	dlg.m_DspNodeCnt = m_AmbpCfg.bDspNodeCfgCnt;

	dlg.m_SdramNum = m_SdramCfg.bNumber;
	dlg.m_SdramModules = m_SdramCfg.bModuleCnt >> 1;
	dlg.m_SdramColAddrBits = m_SdramCfg.bColAddrBits - 8;
	dlg.m_SdramRowAddrBits = m_SdramCfg.bRowAddrBits - 11;
	dlg.m_SdramModuleBanks = m_SdramCfg.bModuleBanks >> 1;
	dlg.m_SdramChipBanks = m_SdramCfg.bChipBanks >> 2;
	dlg.m_SdramPrimWidth = m_SdramCfg.bPrimaryWidth >> 3;
	dlg.m_SdramCasLat = m_SdramCfg.bCasLatency - 2;

	dlg.m_DspNodeNum = m_DspNodeCfg.bNumber;
	dlg.m_DspPldType = m_DspNodeCfg.bPldType;
	dlg.m_DspPldVolume = m_DspNodeCfg.wPldVolume;
	dlg.m_DspPldPins = m_DspNodeCfg.wPldPins;
	dlg.m_DspPldRate = m_DspNodeCfg.bPldSpeedGrade;
	dlg.m_LoadRom = m_DspNodeCfg.bLoadRom;
	dlg.m_isPio = m_DspNodeCfg.bPioType ? 1 : 0;
	dlg.m_PioType = dlg.m_isPio ? (m_DspNodeCfg.bPioType - 1) : -1;

	dlg.m_isSRAM = m_DspNodeCfg.bSramCfgCnt;
//	dlg.m_isSram = m_SramCfg.bNumber;
	dlg.m_SramChips = dlg.m_isSRAM ? (m_SramCfg.bChipCnt - 1) : -1;
	dlg.m_SramSize = m_SramCfg.bChipDepth;
	dlg.m_SramBitsWidth = m_SramCfg.bChipBitsWidth;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_AmbpCfg.dSysGen != dlg.m_SysGen ||
			m_AmbpCfg.bSdramSlotCnt != dlg.m_SlotCnt ||
			m_AmbpCfg.bSdramCfgCnt != dlg.m_SdramCnt ||
			m_AmbpCfg.bDspNodeCfgCnt != dlg.m_DspNodeCnt ||
			m_SdramCfg.bNumber != dlg.m_SdramNum ||
			m_SdramCfg.bModuleCnt != 1 << dlg.m_SdramModules ||
			m_SdramCfg.bColAddrBits != dlg.m_SdramColAddrBits + 8 ||
			m_SdramCfg.bRowAddrBits != dlg.m_SdramRowAddrBits + 11 ||
			m_SdramCfg.bModuleBanks != 1 << dlg.m_SdramModuleBanks ||
			m_SdramCfg.bChipBanks != 2 << dlg.m_SdramChipBanks ||
			m_SdramCfg.bPrimaryWidth != 1 << (dlg.m_SdramPrimWidth + 2) ||
			m_SdramCfg.bCasLatency != dlg.m_SdramCasLat + 2 ||
			m_DspNodeCfg.bNumber != dlg.m_DspNodeNum ||
			m_DspNodeCfg.bPldType != dlg.m_DspPldType ||
			m_DspNodeCfg.wPldVolume != dlg.m_DspPldVolume ||
			m_DspNodeCfg.wPldPins != dlg.m_DspPldPins ||
			m_DspNodeCfg.bPldSpeedGrade != dlg.m_DspPldRate ||
			m_DspNodeCfg.bLoadRom != dlg.m_LoadRom ||
			m_DspNodeCfg.bPioType != (dlg.m_isPio ? (dlg.m_PioType + 1) : 0) ||
			m_DspNodeCfg.bSramCfgCnt != dlg.m_isSRAM ||
			m_SramCfg.bNumber != m_DspNodeCfg.bNumber ||
			m_SramCfg.bChipCnt != (dlg.m_isSRAM ? (dlg.m_SramChips + 1) : 0) ||
			m_SramCfg.bChipDepth != dlg.m_SramSize ||
			m_SramCfg.bChipBitsWidth != dlg.m_SramBitsWidth
		)
			nResponse |= 0x100;

		m_AmbpCfg.dSysGen = dlg.m_SysGen;
		m_AmbpCfg.bSdramSlotCnt = dlg.m_SlotCnt;
		m_AmbpCfg.bSdramCfgCnt = dlg.m_SdramCnt;
		m_AmbpCfg.bDspNodeCfgCnt = dlg.m_DspNodeCnt;

		m_SdramCfg.bNumber = dlg.m_SdramNum;
//		m_SdramCfg.bSlotCnt = 1 << dlg.m_SdramSlots;
		m_SdramCfg.bModuleCnt = 1 << dlg.m_SdramModules;
		m_SdramCfg.bColAddrBits = dlg.m_SdramColAddrBits + 8;
		m_SdramCfg.bRowAddrBits = dlg.m_SdramRowAddrBits + 11;
		m_SdramCfg.bModuleBanks = 1 << dlg.m_SdramModuleBanks;
		m_SdramCfg.bChipBanks = 2 << dlg.m_SdramChipBanks;
		m_SdramCfg.bPrimaryWidth = 1 << (dlg.m_SdramPrimWidth + 2);
		m_SdramCfg.bCasLatency = dlg.m_SdramCasLat + 2;

		m_DspNodeCfg.bNumber = dlg.m_DspNodeNum;
		m_DspNodeCfg.bPldType = dlg.m_DspPldType;
		m_DspNodeCfg.wPldVolume = dlg.m_DspPldVolume;
		m_DspNodeCfg.wPldPins = dlg.m_DspPldPins;
		m_DspNodeCfg.bPldSpeedGrade = dlg.m_DspPldRate;
		m_DspNodeCfg.bLoadRom = dlg.m_LoadRom;
		m_DspNodeCfg.bPioType = dlg.m_isPio ? (dlg.m_PioType + 1) : 0;

		m_DspNodeCfg.bSramCfgCnt = dlg.m_isSRAM;
		m_SramCfg.bNumber = m_DspNodeCfg.bNumber;
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
