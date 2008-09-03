// Icr64Z1.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr64Z1App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "Icr64Z1.h"

// инициализация конфигурационных структур
ICR_Cfg64Z1 m_Adp64Z1Cfg = { ADP64Z1_CFG_TAG, 17, 1, 600, 0, 0, 0, 0, 1};

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


// CIcr64Z1App

BEGIN_MESSAGE_MAP(CIcr64Z1App, CWinApp)
END_MESSAGE_MAP()


// CIcr64Z1App construction

CIcr64Z1App::CIcr64Z1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr64Z1App object

CIcr64Z1App theApp;


// CIcr64Z1App initialization

BOOL CIcr64Z1App::InitInstance()
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
		lstrcpy(pDevInfo->sName, "ADP64Z1PCI");
		pDevInfo->dType = ADP64Z1;
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
		case ADP64Z1_CFG_TAG:
			{
				PICR_Cfg64Z1 pAdpCfg = (PICR_Cfg64Z1)pCurCfgMem;
				m_Adp64Z1Cfg.wTag = pAdpCfg->wTag;
				m_Adp64Z1Cfg.wSize = pAdpCfg->wSize;
				m_Adp64Z1Cfg.bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				m_Adp64Z1Cfg.wMaxCpuClock = pAdpCfg->wMaxCpuClock;
				m_Adp64Z1Cfg.bCpuName = pAdpCfg->bCpuName;
				m_Adp64Z1Cfg.dSizeOfSDRAMA = pAdpCfg->dSizeOfSDRAMA;
				m_Adp64Z1Cfg.dSizeOfSDRAMB = pAdpCfg->dSizeOfSDRAMB;
				m_Adp64Z1Cfg.dSizeOfFlash = pAdpCfg->dSizeOfFlash;
				pDeviceInfo->bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				size = sizeof(ICR_Cfg64Z1);
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

	m_Adp64Z1Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_Cfg64Z1 pAdpCfg = (PICR_Cfg64Z1)pCurCfgMem;
	pAdpCfg->wTag = ADP64Z1_CFG_TAG;
	pAdpCfg->wSize = sizeof(ICR_Cfg64Z1) - 4;
	pAdpCfg->bAdmIfCnt = m_Adp64Z1Cfg.bAdmIfCnt;
	pAdpCfg->wMaxCpuClock = m_Adp64Z1Cfg.wMaxCpuClock;
	pAdpCfg->bCpuName = m_Adp64Z1Cfg.bCpuName;
	pAdpCfg->dSizeOfSDRAMA = m_Adp64Z1Cfg.dSizeOfSDRAMA;
	pAdpCfg->dSizeOfSDRAMB = m_Adp64Z1Cfg.dSizeOfSDRAMB;
	pAdpCfg->dSizeOfFlash = m_Adp64Z1Cfg.dSizeOfFlash;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_Cfg64Z1));
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

	Icr64Z1Dlg dlg;

	dlg.m_MaxCpuClock = m_Adp64Z1Cfg.wMaxCpuClock;
	dlg.m_CpuName = m_Adp64Z1Cfg.bCpuName;
	dlg.m_SdramASize = m_Adp64Z1Cfg.dSizeOfSDRAMA;
	dlg.m_SdramBSize = m_Adp64Z1Cfg.dSizeOfSDRAMB;
	dlg.m_FlashSize = m_Adp64Z1Cfg.dSizeOfFlash;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp64Z1Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp64Z1Cfg.bCpuName = dlg.m_CpuName;
		m_Adp64Z1Cfg.dSizeOfSDRAMA = dlg.m_SdramASize;
		m_Adp64Z1Cfg.dSizeOfSDRAMB = dlg.m_SdramBSize;
		m_Adp64Z1Cfg.dSizeOfFlash = dlg.m_FlashSize;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}

