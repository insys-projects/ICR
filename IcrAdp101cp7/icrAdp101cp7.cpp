// IcrAdp101cP7.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAdp101cP7App.h"    

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAdp101cP7.h"


// инициализация конфигурационных структур
ICR_CfgAdp101cP7 m_Adp101cP7Cfg = { 
	Adp101cP7_CFG_TAG, 
	22, 
	2, 
	250, 
	100000000, 
	0, 
	1, 
	0, 
	0, 
	0x7F, 
	0x7F,
	0,
	0
};
ICR_CfgHostPld m_HostPldCfg = {HOSTPLD_CFG_TAG, 7, 1, 5, 300, 456, 5};

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

// CIcrAdp101cP7App

BEGIN_MESSAGE_MAP(CIcrAdp101cP7App, CWinApp)
END_MESSAGE_MAP()


// CIcrAdp101cP7App construction

CIcrAdp101cP7App::CIcrAdp101cP7App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAdp101cP7App object

CIcrAdp101cP7App theApp;


// CIcrAdp101cP7App initialization

BOOL CIcrAdp101cP7App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADP101CP7"));
		pDevInfo->dType = ADP101CP7;
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
		case Adp101cP7_CFG_TAG:
			{
				PICR_CfgAdp101cP7 pDspCfg = (PICR_CfgAdp101cP7)pCurCfgMem;
				m_Adp101cP7Cfg.wTag = pDspCfg->wTag;
				m_Adp101cP7Cfg.wSize = pDspCfg->wSize;
				m_Adp101cP7Cfg.bAdmIfCnt = pDspCfg->bAdmIfCnt;
				m_Adp101cP7Cfg.wMaxCpuClock = pDspCfg->wMaxCpuClock;
				m_Adp101cP7Cfg.dBusClock = pDspCfg->dBusClock;
				m_Adp101cP7Cfg.dSizeOfSDRAM = pDspCfg->dSizeOfSDRAM;
				m_Adp101cP7Cfg.bHostPldCnt = pDspCfg->bHostPldCnt;
				m_Adp101cP7Cfg.wSDRCON = pDspCfg->wSDRCON;
				m_Adp101cP7Cfg.bTypeOfLinks = pDspCfg->bTypeOfLinks;
				m_Adp101cP7Cfg.wCpuMask = pDspCfg->wCpuMask;
				m_Adp101cP7Cfg.wSdramMask = pDspCfg->wSdramMask;
				m_Adp101cP7Cfg.bX5 = pDspCfg->bX5;
				m_Adp101cP7Cfg.bX6 = pDspCfg->bX6;
				pDeviceInfo->bAdmIfCnt = pDspCfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAdp101cP7);
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

	m_Adp101cP7Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAdp101cP7 pDspCfg = (PICR_CfgAdp101cP7)pCurCfgMem;
	pDspCfg->wTag = Adp101cP7_CFG_TAG;
	pDspCfg->wSize = sizeof(ICR_CfgAdp101cP7) - 4;
	pDspCfg->bAdmIfCnt = m_Adp101cP7Cfg.bAdmIfCnt;
	pDspCfg->wMaxCpuClock = m_Adp101cP7Cfg.wMaxCpuClock;
	pDspCfg->dBusClock = m_Adp101cP7Cfg.dBusClock;
	pDspCfg->dSizeOfSDRAM = m_Adp101cP7Cfg.dSizeOfSDRAM;
	pDspCfg->bHostPldCnt = m_Adp101cP7Cfg.bHostPldCnt;
	pDspCfg->wSDRCON = m_Adp101cP7Cfg.wSDRCON;
	pDspCfg->bTypeOfLinks = m_Adp101cP7Cfg.bTypeOfLinks;
	pDspCfg->wCpuMask = m_Adp101cP7Cfg.wCpuMask;
	pDspCfg->wSdramMask = m_Adp101cP7Cfg.wSdramMask;
	pDspCfg->bX5 = m_Adp101cP7Cfg.bX5;
	pDspCfg->bX6 = m_Adp101cP7Cfg.bX6;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdp101cP7));
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


	CIcrAdp101cP7Dlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_MaxCpuClock = m_Adp101cP7Cfg.wMaxCpuClock;
	dlg.m_BusClock = m_Adp101cP7Cfg.dBusClock / 1000000.;
	dlg.m_SdramSize = m_Adp101cP7Cfg.dSizeOfSDRAM;
	dlg.m_HostPldCnt = m_Adp101cP7Cfg.bHostPldCnt;
	dlg.m_SDRCON = m_Adp101cP7Cfg.wSDRCON;
	dlg.m_TypeOfLinks = m_Adp101cP7Cfg.bTypeOfLinks;
	dlg.m_CpuMask = m_Adp101cP7Cfg.wCpuMask;
	dlg.m_SdramMask = m_Adp101cP7Cfg.wSdramMask;
	dlg.m_X5 = m_Adp101cP7Cfg.bX5;
	dlg.m_X6 = m_Adp101cP7Cfg.bX6;

	dlg.m_PldNum = m_HostPldCfg.bNumber;
	dlg.m_PldType = m_HostPldCfg.bType;
	dlg.m_PldVolume = m_HostPldCfg.wVolume;
	dlg.m_PldPins = m_HostPldCfg.wPins;
	dlg.m_PldRate = m_HostPldCfg.bSpeedGrade;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp101cP7Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp101cP7Cfg.dBusClock = DWORD(dlg.m_BusClock * 1000000.);
		m_Adp101cP7Cfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Adp101cP7Cfg.bHostPldCnt = dlg.m_HostPldCnt;
		m_Adp101cP7Cfg.wSDRCON = dlg.m_SDRCON;
		m_Adp101cP7Cfg.bTypeOfLinks = dlg.m_TypeOfLinks;
		m_Adp101cP7Cfg.wCpuMask = dlg.m_CpuMask;
		m_Adp101cP7Cfg.wSdramMask = dlg.m_SdramMask;
		m_Adp101cP7Cfg.bX5 = dlg.m_X5;
		m_Adp101cP7Cfg.bX6 = dlg.m_X6;

		m_HostPldCfg.bNumber = dlg.m_PldNum;
		m_HostPldCfg.bType = dlg.m_PldType;
		m_HostPldCfg.wVolume = dlg.m_PldVolume;
		m_HostPldCfg.wPins = dlg.m_PldPins;
		m_HostPldCfg.bSpeedGrade = dlg.m_PldRate;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}

