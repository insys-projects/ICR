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

// инициализация конфигурационных структур
ICR_CfgVK3 m_AdpVK3Cfg = {VK3_CFG_TAG, 57, 0, 1, 66.666, 10, 1, 8, 1, 1, 1, 
1, 100, 16, 80, 1700, 75, 1, 1, 1, 1, 1, 500, 14, 1100, 75, {0, 0, 0, 0, 1400, 676, 5}};

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
		case VK3_CFG_TAG:
			{
				PICR_CfgVK3 pAdpCfg = (PICR_CfgVK3)pCurCfgMem;
				m_AdpVK3Cfg.wTag = pAdpCfg->wTag;
				m_AdpVK3Cfg.wSize = pAdpCfg->wSize;
				m_AdpVK3Cfg.nNum = pAdpCfg->nNum;
				m_AdpVK3Cfg.bDdrModuleNum = pAdpCfg->bDdrModuleNum;
				m_AdpVK3Cfg.fSysGen = pAdpCfg->fSysGen;
				m_AdpVK3Cfg.wRefGen = pAdpCfg->wRefGen;
				m_AdpVK3Cfg.bDacBiasBits = pAdpCfg->bDacBiasBits;
				m_AdpVK3Cfg.isDacBias = pAdpCfg->isDacBias;
				m_AdpVK3Cfg.bAdcChanNum = pAdpCfg->bAdcChanNum;
				m_AdpVK3Cfg.bAdcInpNum = pAdpCfg->bAdcInpNum;
				m_AdpVK3Cfg.bAdcTypeF = pAdpCfg->bAdcTypeF;
				m_AdpVK3Cfg.wAdcBiasRange = pAdpCfg->wAdcBiasRange;
				m_AdpVK3Cfg.bAdcBits = pAdpCfg->bAdcBits;
				m_AdpVK3Cfg.wMaxfreqSampl = pAdpCfg->wMaxfreqSampl;
				m_AdpVK3Cfg.wInpAmplRange = pAdpCfg->wInpAmplRange;
				m_AdpVK3Cfg.nInpR = pAdpCfg->nInpR;
				m_AdpVK3Cfg.isAdcInpAdd = pAdpCfg->isAdcInpAdd;
				m_AdpVK3Cfg.isTuner = pAdpCfg->isTuner;
				m_AdpVK3Cfg.isSelectorSinch = pAdpCfg->isSelectorSinch;
				m_AdpVK3Cfg.bDacChanNum = pAdpCfg->bDacChanNum;
				m_AdpVK3Cfg.bDacOutNum = pAdpCfg->bDacOutNum;
				m_AdpVK3Cfg.bDacTypeF = pAdpCfg->bDacTypeF;
				m_AdpVK3Cfg.wDacBiasRange = pAdpCfg->wDacBiasRange;
				m_AdpVK3Cfg.bDacBits = pAdpCfg->bDacBits;
				m_AdpVK3Cfg.wOutAmplRange = pAdpCfg->wOutAmplRange;
				m_AdpVK3Cfg.nOutR = pAdpCfg->nOutR;
				m_AdpVK3Cfg.rPldType.bType = pAdpCfg->rPldType.bType;
				m_AdpVK3Cfg.rPldType.wVolume = pAdpCfg->rPldType.wVolume;
				m_AdpVK3Cfg.rPldType.bSpeedGrade = pAdpCfg->rPldType.bSpeedGrade;
				m_AdpVK3Cfg.rPldType.wPins = pAdpCfg->rPldType.wPins;
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
//  BASEMOD_GetProperty - функция служит для передачи значений из плагина в основную программу
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 0 - нет ошибок, 1 - 
//  Notes:  данная функция вызывается перед записью данных в файл или устройство
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
	pAdpCfg->fSysGen = m_AdpVK3Cfg.fSysGen;
	pAdpCfg->wRefGen = m_AdpVK3Cfg.wRefGen;
	pAdpCfg->bDacBiasBits = m_AdpVK3Cfg.bDacBiasBits;
	pAdpCfg->isDacBias = m_AdpVK3Cfg.isDacBias;
	pAdpCfg->bAdcChanNum = m_AdpVK3Cfg.bAdcChanNum;
	pAdpCfg->bAdcInpNum = m_AdpVK3Cfg.bAdcInpNum;
	pAdpCfg->bAdcTypeF = m_AdpVK3Cfg.bAdcTypeF;
	pAdpCfg->wAdcBiasRange = m_AdpVK3Cfg.wAdcBiasRange;
	pAdpCfg->bAdcBits = m_AdpVK3Cfg.bAdcBits;
	pAdpCfg->wMaxfreqSampl = m_AdpVK3Cfg.wMaxfreqSampl;
	pAdpCfg->wInpAmplRange = m_AdpVK3Cfg.wInpAmplRange;
	pAdpCfg->nInpR = m_AdpVK3Cfg.nInpR;
	pAdpCfg->isAdcInpAdd = m_AdpVK3Cfg.isAdcInpAdd;
	pAdpCfg->isTuner = m_AdpVK3Cfg.isTuner;
	pAdpCfg->isSelectorSinch = m_AdpVK3Cfg.isSelectorSinch;
	pAdpCfg->bDacChanNum = m_AdpVK3Cfg.bDacChanNum;
	pAdpCfg->bDacOutNum = m_AdpVK3Cfg.bDacOutNum;
	pAdpCfg->bDacTypeF = m_AdpVK3Cfg.bDacTypeF;
	pAdpCfg->wDacBiasRange = m_AdpVK3Cfg.wDacBiasRange;
	pAdpCfg->bDacBits = m_AdpVK3Cfg.bDacBits;
	pAdpCfg->wOutAmplRange = m_AdpVK3Cfg.wOutAmplRange;
	pAdpCfg->nOutR = m_AdpVK3Cfg.nOutR;
	pAdpCfg->rPldType.bType = m_AdpVK3Cfg.rPldType.bType;
	pAdpCfg->rPldType.wVolume = m_AdpVK3Cfg.rPldType.wVolume;
	pAdpCfg->rPldType.bSpeedGrade = m_AdpVK3Cfg.rPldType.bSpeedGrade;
	pAdpCfg->rPldType.wPins = m_AdpVK3Cfg.rPldType.wPins;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgVK3));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

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

	IcrVK3Dlg dlg;

	dlg.m_nNum = m_AdpVK3Cfg.nNum;
	dlg.m_bDdrModuleNum = m_AdpVK3Cfg.bDdrModuleNum;
	dlg.m_fSysGen = m_AdpVK3Cfg.fSysGen;
	dlg.m_wRefGen = m_AdpVK3Cfg.wRefGen;
	dlg.m_bDacBiasBits = m_AdpVK3Cfg.bDacBiasBits;
	dlg.m_isDacBias = m_AdpVK3Cfg.isDacBias;
	dlg.m_bAdcChanNum = m_AdpVK3Cfg.bAdcChanNum;
	dlg.m_bAdcInpNum = m_AdpVK3Cfg.bAdcInpNum;
	dlg.m_bAdcTypeF = m_AdpVK3Cfg.bAdcTypeF;
	dlg.m_wAdcBiasRange = m_AdpVK3Cfg.wAdcBiasRange;
	dlg.m_bAdcBits = m_AdpVK3Cfg.bAdcBits;
	dlg.m_nMaxfreqSampl = m_AdpVK3Cfg.wMaxfreqSampl;
	dlg.m_wInpAmplRange = m_AdpVK3Cfg.wInpAmplRange;
	dlg.m_nInpR = m_AdpVK3Cfg.nInpR;
	dlg.m_isAdcInpAdd = m_AdpVK3Cfg.isAdcInpAdd;
	dlg.m_isTuner = m_AdpVK3Cfg.isTuner;
	dlg.m_isSelectorSinch = m_AdpVK3Cfg.isSelectorSinch;
	dlg.m_nDacChanNum = m_AdpVK3Cfg.bDacChanNum;
	dlg.m_bDacOutNum = m_AdpVK3Cfg.bDacOutNum;
	dlg.m_bDacTypeF = m_AdpVK3Cfg.bDacTypeF;
	dlg.m_wDacBiasRange = m_AdpVK3Cfg.wDacBiasRange;
	dlg.m_bDacBits = m_AdpVK3Cfg.bDacBits;
	dlg.m_wOutAmplRange = m_AdpVK3Cfg.wOutAmplRange;
	dlg.m_nOutR = m_AdpVK3Cfg.nOutR;
	dlg.m_bType = m_AdpVK3Cfg.rPldType.bType;
	dlg.m_nVolume = m_AdpVK3Cfg.rPldType.wVolume;
	dlg.m_bSpeedGrade = m_AdpVK3Cfg.rPldType.bSpeedGrade;
	dlg.m_nPins = m_AdpVK3Cfg.rPldType.wPins;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_AdpVK3Cfg.nNum = dlg.m_nNum;
		m_AdpVK3Cfg.bDdrModuleNum = dlg.m_bDdrModuleNum;
		m_AdpVK3Cfg.fSysGen = dlg.m_fSysGen;
		m_AdpVK3Cfg.wRefGen = dlg.m_wRefGen;
		m_AdpVK3Cfg.bDacBiasBits = dlg.m_bDacBiasBits;
		m_AdpVK3Cfg.isDacBias = dlg.m_isDacBias;
		m_AdpVK3Cfg.bAdcChanNum = dlg.m_bAdcChanNum;
		m_AdpVK3Cfg.bAdcInpNum = dlg.m_bAdcInpNum;
		m_AdpVK3Cfg.bAdcTypeF = dlg.m_bAdcTypeF;
		m_AdpVK3Cfg.wAdcBiasRange = dlg.m_wAdcBiasRange;
		m_AdpVK3Cfg.bAdcBits = dlg.m_bAdcBits;
		m_AdpVK3Cfg.wMaxfreqSampl = dlg.m_nMaxfreqSampl;
		m_AdpVK3Cfg.wInpAmplRange = dlg.m_wInpAmplRange;
		m_AdpVK3Cfg.nInpR = dlg.m_nInpR;
		m_AdpVK3Cfg.isAdcInpAdd = dlg.m_isAdcInpAdd;
		m_AdpVK3Cfg.isTuner = dlg.m_isTuner;
		m_AdpVK3Cfg.isSelectorSinch = dlg.m_isSelectorSinch;
		m_AdpVK3Cfg.bDacChanNum = dlg.m_nDacChanNum;
		m_AdpVK3Cfg.bDacOutNum = dlg.m_bDacOutNum;
		m_AdpVK3Cfg.bDacTypeF = dlg.m_bDacTypeF;
		m_AdpVK3Cfg.wDacBiasRange = dlg.m_wDacBiasRange;
		m_AdpVK3Cfg.bDacBits = dlg.m_bDacBits;
		m_AdpVK3Cfg.wOutAmplRange = dlg.m_wOutAmplRange;
		m_AdpVK3Cfg.nOutR = dlg.m_nOutR;
		m_AdpVK3Cfg.rPldType.bType = dlg.m_bType;
		m_AdpVK3Cfg.rPldType.wVolume = dlg.m_nVolume;
		m_AdpVK3Cfg.rPldType.bSpeedGrade = dlg.m_bSpeedGrade;
		m_AdpVK3Cfg.rPldType.wPins = dlg.m_nPins;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}