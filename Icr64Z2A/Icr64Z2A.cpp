// Icr64Z2A.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Icr64Z2AApp.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "Icr64Z2A.h"

// инициализация конфигурационных структур
ICR_Cfg64Z2A m_Adp64Z2ACfg = { ADP64Z2A_CFG_TAG, 20, 1, 720, 0, 0, 0, 0, 1};
ICR_CfgHostPld m_HostPldCfg = {HOSTPLD_CFG_TAG, 7, 0, 7, 400, 456, 5};

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


// CIcr64Z2AApp

BEGIN_MESSAGE_MAP(CIcr64Z2AApp, CWinApp)
END_MESSAGE_MAP()


// CIcr64Z2AApp construction

CIcr64Z2AApp::CIcr64Z2AApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcr64Z2AApp object

CIcr64Z2AApp theApp;


// CIcr64Z2AApp initialization

BOOL CIcr64Z2AApp::InitInstance()
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
		lstrcpy(pDevInfo->sName, "ADP64Z2APCI");
		pDevInfo->dType = ADP64Z2A;
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
		case ADP64Z2A_CFG_TAG:
			{
				PICR_Cfg64Z2A pAdpCfg = (PICR_Cfg64Z2A)pCurCfgMem;
				m_Adp64Z2ACfg.wTag = pAdpCfg->wTag;
				m_Adp64Z2ACfg.wSize = pAdpCfg->wSize;
				m_Adp64Z2ACfg.bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				m_Adp64Z2ACfg.wMaxCpuClock = pAdpCfg->wMaxCpuClock;
				m_Adp64Z2ACfg.dSizeOfSDRAMA = pAdpCfg->dSizeOfSDRAMA;
				m_Adp64Z2ACfg.dSizeOfSDRAMB = pAdpCfg->dSizeOfSDRAMB;
				m_Adp64Z2ACfg.dSizeOfFlash = pAdpCfg->dSizeOfFlash;
				m_Adp64Z2ACfg.dSizeOfSBSRAM = pAdpCfg->dSizeOfSBSRAM;
				m_Adp64Z2ACfg.bHostPldCnt = pAdpCfg->bHostPldCnt;
				pDeviceInfo->bAdmIfCnt = pAdpCfg->bAdmIfCnt;
				size = sizeof(ICR_Cfg64Z2A);
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

	m_Adp64Z2ACfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_Cfg64Z2A pAdpCfg = (PICR_Cfg64Z2A)pCurCfgMem;
	pAdpCfg->wTag = ADP64Z2A_CFG_TAG;
	pAdpCfg->wSize = sizeof(ICR_Cfg64Z2A) - 4;
	pAdpCfg->bAdmIfCnt = m_Adp64Z2ACfg.bAdmIfCnt;
	pAdpCfg->wMaxCpuClock = m_Adp64Z2ACfg.wMaxCpuClock;
	pAdpCfg->dSizeOfSDRAMA = m_Adp64Z2ACfg.dSizeOfSDRAMA;
	pAdpCfg->dSizeOfSDRAMB = m_Adp64Z2ACfg.dSizeOfSDRAMB;
	pAdpCfg->dSizeOfFlash = m_Adp64Z2ACfg.dSizeOfFlash;
	pAdpCfg->dSizeOfSBSRAM = m_Adp64Z2ACfg.dSizeOfSBSRAM;
	pAdpCfg->bHostPldCnt = m_Adp64Z2ACfg.bHostPldCnt;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_Cfg64Z2A));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pAdpCfg->bHostPldCnt)
	{
		for(int i = 0; i < pAdpCfg->bHostPldCnt; i++)
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

	Icr64Z2ADlg dlg;

	dlg.m_MaxCpuClock = m_Adp64Z2ACfg.wMaxCpuClock;
	dlg.m_SdramASize = m_Adp64Z2ACfg.dSizeOfSDRAMA;
	dlg.m_SdramBSize = m_Adp64Z2ACfg.dSizeOfSDRAMB;
	dlg.m_FlashSize = m_Adp64Z2ACfg.dSizeOfFlash;
	dlg.m_SbsramSize = m_Adp64Z2ACfg.dSizeOfSBSRAM;
	dlg.m_HostPldCnt = m_Adp64Z2ACfg.bHostPldCnt;

	dlg.m_PldNum = m_HostPldCfg.bNumber;
	dlg.m_PldType = m_HostPldCfg.bType;
	dlg.m_PldVolume = m_HostPldCfg.wVolume;

	int nResponse = (int)dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_Adp64Z2ACfg.wMaxCpuClock = dlg.m_MaxCpuClock;
		m_Adp64Z2ACfg.dSizeOfSDRAMA = dlg.m_SdramASize;
		m_Adp64Z2ACfg.dSizeOfSDRAMB = dlg.m_SdramBSize;
		m_Adp64Z2ACfg.dSizeOfFlash = dlg.m_FlashSize;
		m_Adp64Z2ACfg.dSizeOfSBSRAM = dlg.m_SbsramSize;
		m_Adp64Z2ACfg.bHostPldCnt = dlg.m_HostPldCnt;

		m_HostPldCfg.bNumber = dlg.m_PldNum;
		m_HostPldCfg.bType = dlg.m_PldType;
		m_HostPldCfg.wVolume = dlg.m_PldVolume;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return nResponse;
}
