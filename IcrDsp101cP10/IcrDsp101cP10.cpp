// IcrDsp101cP10.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrDsp101cP10App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// размер памяти, выделяемой под конфигурацию
// (максимальный размер ППЗУ, устанавливаемого на модуль)
#define BASEMOD_CFGMEM_SIZE 128+256

#include "icr.h"

#include "IcrDsp101cP10.h"

const U16 DIOPLD_CFG_TAG	= 0x0520; // tag of DIO PLD configuration structure

// инициализация конфигурационных структур
ICR_CfgDSP101cP10 m_Dsp101cP10Cfg = {
		DSP101cP10_CFG_TAG, 
		22, 
		0, 
		250, 
		100000000, 
		0, 
		1, 
		1, 
		0, 
		0, 
		0x3FF, 
		0x3FF, 
		0x0
};
ICR_CfgHostPld m_HostPldCfg = {HOSTPLD_CFG_TAG, 7, 1, 5, 100, 456, 5};
ICR_CfgHostPld m_DioPldCfg = {DIOPLD_CFG_TAG, 7, 1, 4, 1000, 456, 5};

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

// CIcrDsp101cP10App

BEGIN_MESSAGE_MAP(CIcrDsp101cP10App, CWinApp)
END_MESSAGE_MAP()


// CIcrDsp101cP10App construction

CIcrDsp101cP10App::CIcrDsp101cP10App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrDsp101cP10App object

CIcrDsp101cP10App theApp;


// CIcrDsp101cP10App initialization

BOOL CIcrDsp101cP10App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("DSP101cP10"));
		pDevInfo->dType = DSP101cP10;
		break;
	default:
		*pNumDev = -1;
		return;
	}
	pDevInfo->pCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];
	pDevInfo->dCfgMemSize = BASEMOD_CFGMEM_SIZE;
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
		case HOSTPLD_CFG_TAG:
			{
				PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
				m_HostPldCfg.wTag = pPldCfg->wTag;
				m_HostPldCfg.wSize = pPldCfg->wSize;
				m_HostPldCfg.bNumber = pPldCfg->bNumber;
				m_HostPldCfg.bType = pPldCfg->bType;
				m_HostPldCfg.wVolume = pPldCfg->wVolume;
				m_HostPldCfg.wPins = pPldCfg->wPins;
				m_HostPldCfg.bSpeedGrade = pPldCfg->bSpeedGrade;
				size = sizeof(ICR_CfgHostPld);
				RealCfgSize += size;
				break;
			}
		case DIOPLD_CFG_TAG:
			{
				PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
				m_DioPldCfg.wTag = pPldCfg->wTag;
				m_DioPldCfg.wSize = pPldCfg->wSize;
				m_DioPldCfg.bNumber = pPldCfg->bNumber;
				m_DioPldCfg.bType = pPldCfg->bType;
				m_DioPldCfg.wVolume = pPldCfg->wVolume;
				m_DioPldCfg.wPins = pPldCfg->wPins;
				m_DioPldCfg.bSpeedGrade = pPldCfg->bSpeedGrade;
				size = sizeof(ICR_CfgHostPld);
				RealCfgSize += size;
				break;
			}
		case DSP101cP10_CFG_TAG:
			{
				PICR_CfgDSP101cP10 pDspCfg = (PICR_CfgDSP101cP10)pCurCfgMem;
				m_Dsp101cP10Cfg.wTag = pDspCfg->wTag;
				m_Dsp101cP10Cfg.wSize = pDspCfg->wSize;
				m_Dsp101cP10Cfg.bAdmIfCnt = pDspCfg->bAdmIfCnt;
				m_Dsp101cP10Cfg.wMaxCpuClock = pDspCfg->wMaxCpuClock;
				m_Dsp101cP10Cfg.dBusClock = pDspCfg->dBusClock;
				m_Dsp101cP10Cfg.dSizeOfSDRAM = pDspCfg->dSizeOfSDRAM;
				m_Dsp101cP10Cfg.bHostPldCnt = pDspCfg->bHostPldCnt;
				m_Dsp101cP10Cfg.bDioPldCnt = pDspCfg->bDioPldCnt;
				m_Dsp101cP10Cfg.wSDRCON = pDspCfg->wSDRCON;
				m_Dsp101cP10Cfg.bTypeOfLinks = pDspCfg->bTypeOfLinks;
				m_Dsp101cP10Cfg.wCpuMask = pDspCfg->wCpuMask;
				m_Dsp101cP10Cfg.wSdramMask = pDspCfg->wSdramMask;
				m_Dsp101cP10Cfg.wLinksJ4Mask = pDspCfg->wLinksJ4Mask;
				pDeviceInfo->bAdmIfCnt = pDspCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgDSP101cP10);
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
	pDeviceInfo->dRealCfgSize = RealCfgSize;
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

	m_Dsp101cP10Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgDSP101cP10 pDspCfg = (PICR_CfgDSP101cP10)pCurCfgMem;
	pDspCfg->wTag = DSP101cP10_CFG_TAG;
	pDspCfg->wSize = sizeof(ICR_CfgDSP101cP10) - 4;
	pDspCfg->bAdmIfCnt = m_Dsp101cP10Cfg.bAdmIfCnt;
	pDspCfg->wMaxCpuClock = m_Dsp101cP10Cfg.wMaxCpuClock;
	pDspCfg->dBusClock = m_Dsp101cP10Cfg.dBusClock;
	pDspCfg->dSizeOfSDRAM = m_Dsp101cP10Cfg.dSizeOfSDRAM;
	pDspCfg->bHostPldCnt = m_Dsp101cP10Cfg.bHostPldCnt;
	pDspCfg->bDioPldCnt = m_Dsp101cP10Cfg.bDioPldCnt;
	pDspCfg->wSDRCON = m_Dsp101cP10Cfg.wSDRCON;
	pDspCfg->bTypeOfLinks = m_Dsp101cP10Cfg.bTypeOfLinks;
	pDspCfg->wCpuMask = m_Dsp101cP10Cfg.wCpuMask;
	pDspCfg->wSdramMask = m_Dsp101cP10Cfg.wSdramMask;
	pDspCfg->wLinksJ4Mask = m_Dsp101cP10Cfg.wLinksJ4Mask;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDSP101cP10));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pDspCfg->bHostPldCnt)
	{
		for(int i = 0; i < pDspCfg->bHostPldCnt; i++)
		{
			PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
			pPldCfg->wTag = HOSTPLD_CFG_TAG;
			pPldCfg->wSize = sizeof(ICR_CfgHostPld) - 4;
			pPldCfg->bNumber = 0;
			pPldCfg->bType = m_HostPldCfg.bType;
			pPldCfg->wVolume = m_HostPldCfg.wVolume;
			pPldCfg->wPins = m_HostPldCfg.wPins;
			pPldCfg->bSpeedGrade = m_HostPldCfg.bSpeedGrade;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgHostPld));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
	if(pDspCfg->bDioPldCnt)
	{
		for(int i = 0; i < pDspCfg->bDioPldCnt; i++)
		{
			PICR_CfgHostPld pPldCfg = (PICR_CfgHostPld)pCurCfgMem;
			pPldCfg->wTag = DIOPLD_CFG_TAG;
			pPldCfg->wSize = sizeof(ICR_CfgHostPld) - 4;
			pPldCfg->bNumber = 0;
			pPldCfg->bType = m_DioPldCfg.bType;
			pPldCfg->wVolume = m_DioPldCfg.wVolume;
			pPldCfg->wPins = m_DioPldCfg.wPins;
			pPldCfg->bSpeedGrade = m_DioPldCfg.bSpeedGrade;

			pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgHostPld));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
		}
	}
	// тэг окончания данных не нужен (его пишет основная программа)
//	*pSignSize = END_TAG;
//	pSignSize++;
	pDeviceInfo->dRealCfgSize = ULONG((PUCHAR)pCurCfgMem - pDeviceInfo->pCfgMem);

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


	CIcrDsp101cP10Dlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_MaxCpuClock = m_Dsp101cP10Cfg.wMaxCpuClock;
	dlg.m_BusClock = m_Dsp101cP10Cfg.dBusClock / 1000000.;
	dlg.m_SdramSize = m_Dsp101cP10Cfg.dSizeOfSDRAM;
	dlg.m_HostPldCnt = m_Dsp101cP10Cfg.bHostPldCnt;
	dlg.m_DioPldCnt = m_Dsp101cP10Cfg.bDioPldCnt;
	dlg.m_SDRCON = m_Dsp101cP10Cfg.wSDRCON;
	dlg.m_TypeOfLinks = m_Dsp101cP10Cfg.bTypeOfLinks;
	dlg.m_CpuMask = m_Dsp101cP10Cfg.wCpuMask;
	dlg.m_SdramMask = m_Dsp101cP10Cfg.wSdramMask;
	dlg.m_LinksJ4Mask = m_Dsp101cP10Cfg.wLinksJ4Mask;

	dlg.m_PldNum = m_HostPldCfg.bNumber;
	dlg.m_PldType = m_HostPldCfg.bType;
	dlg.m_PldVolume = m_HostPldCfg.wVolume;
	dlg.m_PldPins = m_HostPldCfg.wPins;
	dlg.m_PldRate = m_HostPldCfg.bSpeedGrade;

	dlg.m_DioPldNum = m_DioPldCfg.bNumber;
	dlg.m_DioPldType = m_DioPldCfg.bType;
	dlg.m_DioPldVol = m_DioPldCfg.wVolume;
	dlg.m_DioPldPins = m_DioPldCfg.wPins;
	dlg.m_DioPldRate = m_DioPldCfg.bSpeedGrade;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Dsp101cP10Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Dsp101cP10Cfg.dBusClock = DWORD(dlg.m_BusClock * 1000000.);
		m_Dsp101cP10Cfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Dsp101cP10Cfg.bHostPldCnt = dlg.m_HostPldCnt;
		m_Dsp101cP10Cfg.bDioPldCnt = dlg.m_DioPldCnt;
		m_Dsp101cP10Cfg.wSDRCON = dlg.m_SDRCON;
		m_Dsp101cP10Cfg.bTypeOfLinks = dlg.m_TypeOfLinks;
		m_Dsp101cP10Cfg.wCpuMask = dlg.m_CpuMask;
		m_Dsp101cP10Cfg.wSdramMask = dlg.m_SdramMask;
		m_Dsp101cP10Cfg.wLinksJ4Mask = dlg.m_LinksJ4Mask;

		m_HostPldCfg.bNumber = dlg.m_PldNum;
		m_HostPldCfg.bType = dlg.m_PldType;
		m_HostPldCfg.wVolume = dlg.m_PldVolume;
		m_HostPldCfg.wPins = dlg.m_PldPins;
		m_HostPldCfg.bSpeedGrade = dlg.m_PldRate;

		m_DioPldCfg.bNumber = dlg.m_DioPldNum;
		m_DioPldCfg.bType = dlg.m_DioPldType;
		m_DioPldCfg.wVolume = dlg.m_DioPldVol;
		m_DioPldCfg.wPins = dlg.m_DioPldPins;
		m_DioPldCfg.bSpeedGrade = dlg.m_DioPldRate;

	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
