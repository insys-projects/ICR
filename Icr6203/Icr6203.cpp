// Icr6203.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr6203App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "Icr6203.h"

// инициализация конфигурационных структур
ICR_Cfg6203 m_Adp6203Cfg = { ADP6203_CFG_TAG, 16, 1, 240, 0, 0, 0, 1 };
ICR_CfgFifoHost m_FifoHostCfg = { FIFO_HOST_TAG, 3, 0, 5, 3 };

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


// CIcr6203App

BEGIN_MESSAGE_MAP(CIcr6203App, CWinApp)
END_MESSAGE_MAP()


// CIcr6203App construction

CIcr6203App::CIcr6203App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr6203App object

CIcr6203App theApp;


// CIcr6203App initialization

BOOL CIcr6203App::InitInstance()
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
		lstrcpy(pDevInfo->sName, "ADP6203PCI");
		pDevInfo->dType = ADP6203;
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
		case ADP6203_CFG_TAG:
			{
				PICR_Cfg6203 pAdpCfg = (PICR_Cfg6203)pCurCfgMem;
				m_Adp6203Cfg.wTag = pAdpCfg->wTag;
				m_Adp6203Cfg.wSize = pAdpCfg->wSize;
				m_Adp6203Cfg.bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				m_Adp6203Cfg.wMaxCpuClock = pAdpCfg->wMaxCpuClock;
				m_Adp6203Cfg.dSizeOfSDRAM = pAdpCfg->dSizeOfSDRAM;
				m_Adp6203Cfg.dSizeOfDPRAM = pAdpCfg->dSizeOfDPRAM;
				m_Adp6203Cfg.dSizeOfSSRAM = pAdpCfg->dSizeOfSSRAM;
				m_Adp6203Cfg.bFifoCnt = pAdpCfg->bFifoCnt;
				pDeviceInfo->bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				size = sizeof(ICR_Cfg6203);
				RealCfgSize += size;
				break;
			}
		case FIFO_HOST_TAG:
			{
				PICR_CfgFifoHost pFifoCfg = (PICR_CfgFifoHost)pCurCfgMem;
				m_FifoHostCfg.bNumber = pFifoCfg->bNumber;
				m_FifoHostCfg.bDepth = pFifoCfg->bDepth;
				m_FifoHostCfg.bBitsWidth = pFifoCfg->bBitsWidth;
				size = sizeof(ICR_CfgFifoHost);
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
//  BASEMOD_GetProperty - функция служит для передачи значений из плагина в основную программу
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 0 - нет ошибок, 1 - 
//  Notes:  данная функция вызывается перед записью данных в файл или устройство
//***************************************************************************************
BASEMOD_API int __stdcall BASEMOD_GetProperty(PBASEMOD_INFO pDeviceInfo)
{
	PUSHORT pCurCfgMem = (PUSHORT)pDeviceInfo->pCfgMem;
	PUSHORT pEndCfgMem = (PUSHORT)(pDeviceInfo->pCfgMem) + BASEMOD_CFGMEM_SIZE/2;

	m_Adp6203Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_Cfg6203 pAdpCfg = (PICR_Cfg6203)pCurCfgMem;
	pAdpCfg->wTag = ADP6203_CFG_TAG;
	pAdpCfg->wSize = sizeof(ICR_Cfg6203) - 4;
	pAdpCfg->bAdmIfCnt = m_Adp6203Cfg.bAdmIfCnt;
	pAdpCfg->wMaxCpuClock = m_Adp6203Cfg.wMaxCpuClock;
	pAdpCfg->dSizeOfSDRAM = m_Adp6203Cfg.dSizeOfSDRAM;
	pAdpCfg->dSizeOfDPRAM = m_Adp6203Cfg.dSizeOfDPRAM;
	pAdpCfg->dSizeOfSSRAM = m_Adp6203Cfg.dSizeOfSSRAM;
	pAdpCfg->bFifoCnt = m_Adp6203Cfg.bFifoCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_Cfg6203));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if( pAdpCfg->bFifoCnt )
	{
		PICR_CfgFifoHost pFifoCfg = (PICR_CfgFifoHost)pCurCfgMem;
		pFifoCfg->wTag = FIFO_HOST_TAG;
		pFifoCfg->wSize = sizeof(ICR_CfgFifoHost) - 4;
		pFifoCfg->bNumber = 0;
		pFifoCfg->bDepth = m_FifoHostCfg.bDepth;
		pFifoCfg->bBitsWidth = m_FifoHostCfg.bBitsWidth;

		pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgFifoHost));
		if(pCurCfgMem >= pEndCfgMem)
			return 1;
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

	Icr6203Dlg dlg;

	dlg.m_MaxCpuClock = m_Adp6203Cfg.wMaxCpuClock;
	dlg.m_SdramSize = m_Adp6203Cfg.dSizeOfSDRAM;
	dlg.m_DpramSize = m_Adp6203Cfg.dSizeOfDPRAM;
	dlg.m_SsramSize = m_Adp6203Cfg.dSizeOfSSRAM;
	dlg.m_FifoCnt = m_Adp6203Cfg.bFifoCnt;
	dlg.m_FifoNum = m_FifoHostCfg.bNumber;
	dlg.m_FifoSize = m_FifoHostCfg.bDepth;
	dlg.m_FifoWidth = m_FifoHostCfg.bBitsWidth;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_Adp6203Cfg.wMaxCpuClock != dlg.m_MaxCpuClock ||
			m_Adp6203Cfg.dSizeOfSDRAM != dlg.m_SdramSize ||
			m_Adp6203Cfg.dSizeOfDPRAM != dlg.m_DpramSize ||
			m_Adp6203Cfg.dSizeOfSSRAM != dlg.m_SsramSize ||
			m_Adp6203Cfg.bFifoCnt != dlg.m_FifoCnt ||
			m_FifoHostCfg.bNumber != dlg.m_FifoNum ||
			m_FifoHostCfg.bDepth != dlg.m_FifoSize ||
			m_FifoHostCfg.bBitsWidth != dlg.m_FifoWidth
		)
			nResponse |= 0x100;

		m_Adp6203Cfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp6203Cfg.dSizeOfSDRAM = dlg.m_SdramSize;
		m_Adp6203Cfg.dSizeOfDPRAM = dlg.m_DpramSize;
		m_Adp6203Cfg.dSizeOfSSRAM = dlg.m_SsramSize;
		m_Adp6203Cfg.bFifoCnt = dlg.m_FifoCnt;

		m_FifoHostCfg.bNumber = dlg.m_FifoNum;
		m_FifoHostCfg.bDepth = dlg.m_FifoSize;
		m_FifoHostCfg.bBitsWidth = dlg.m_FifoWidth;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}

