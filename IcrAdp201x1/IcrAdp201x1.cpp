// IcrAdp201x1.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAdp201x1App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAdp201x1.h"

// инициализация конфигурационных структур
ICR_CfgAdp201x1 m_Adp201x1Cfg = { ADP201X1AMB_CFG_TAG, 24, 1, 250000000, 0, 0, 0, 156250000, 100000000, 0, 600, 0, 0};

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

// CIcrAdp201x1App

BEGIN_MESSAGE_MAP(CIcrAdp201x1App, CWinApp)
END_MESSAGE_MAP()


// CIcrAdp201x1App construction

CIcrAdp201x1App::CIcrAdp201x1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAmbpApp object

CIcrAdp201x1App theApp;


// CIcrAdp201x1App initialization

BOOL CIcrAdp201x1App::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADP201X1AMB"));
		pDevInfo->dType = ADP201X1AMB;
		break;
	case 1:
		lstrcpy(pDevInfo->sName, _T("ADP201X1DSP"));
		pDevInfo->dType = ADP201X1DSP;
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
		case ADP201X1AMB_CFG_TAG:
		case ADP201X1DSP_CFG_TAG:
			{
				PICR_CfgAdp201x1 pAdp201x1Cfg = (PICR_CfgAdp201x1)pCurCfgMem;
				m_Adp201x1Cfg.wTag = pAdp201x1Cfg->wTag;
				m_Adp201x1Cfg.wSize = pAdp201x1Cfg->wSize;
				m_Adp201x1Cfg.bAdmIfCnt = pAdp201x1Cfg->bAdmIfCnt;
				m_Adp201x1Cfg.dSysGen = pAdp201x1Cfg->dSysGen;
				m_Adp201x1Cfg.bDdsType = pAdp201x1Cfg->bDdsType;
				m_Adp201x1Cfg.wSizeOfPldSdram = pAdp201x1Cfg->wSizeOfPldSdram;
				m_Adp201x1Cfg.bLlcuConnector = pAdp201x1Cfg->bLlcuConnector;
				m_Adp201x1Cfg.dRefMgtGen = pAdp201x1Cfg->dRefMgtGen;
				m_Adp201x1Cfg.dRefCpuGen = pAdp201x1Cfg->dRefCpuGen;
				m_Adp201x1Cfg.bIsCpu = pAdp201x1Cfg->bIsCpu;
				m_Adp201x1Cfg.wCpuClock = pAdp201x1Cfg->wCpuClock;
				m_Adp201x1Cfg.wSizeOfCpuSdram = pAdp201x1Cfg->wSizeOfCpuSdram;
				m_Adp201x1Cfg.wSizeOfCpuFlash = pAdp201x1Cfg->wSizeOfCpuFlash;
				pDeviceInfo->bAdmIfCnt = pAdp201x1Cfg->bAdmIfCnt;
				size = sizeof(ICR_CfgAdp201x1);
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

	m_Adp201x1Cfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAdp201x1 pAdp201x1Cfg = (PICR_CfgAdp201x1)pCurCfgMem;
	pAdp201x1Cfg->wTag = pDeviceInfo->dType;//AMBVME_CFG_TAG;
	pAdp201x1Cfg->wSize = sizeof(ICR_CfgAdp201x1) - 4;
	pAdp201x1Cfg->bAdmIfCnt = m_Adp201x1Cfg.bAdmIfCnt;
	pAdp201x1Cfg->dSysGen = m_Adp201x1Cfg.dSysGen;
	pAdp201x1Cfg->bDdsType = m_Adp201x1Cfg.bDdsType;
	pAdp201x1Cfg->wSizeOfPldSdram = m_Adp201x1Cfg.wSizeOfPldSdram;
	pAdp201x1Cfg->bLlcuConnector = m_Adp201x1Cfg.bLlcuConnector;
	pAdp201x1Cfg->dRefMgtGen = m_Adp201x1Cfg.dRefMgtGen;
	pAdp201x1Cfg->dRefCpuGen = m_Adp201x1Cfg.dRefCpuGen;
	pAdp201x1Cfg->bIsCpu = m_Adp201x1Cfg.bIsCpu;
	pAdp201x1Cfg->wCpuClock = m_Adp201x1Cfg.wCpuClock;
	pAdp201x1Cfg->wSizeOfCpuSdram = m_Adp201x1Cfg.wSizeOfCpuSdram;
	pAdp201x1Cfg->wSizeOfCpuFlash = m_Adp201x1Cfg.wSizeOfCpuFlash;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdp201x1));
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

	CIcrAdp201x1Dlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_Adp201x1Cfg.dSysGen;
	dlg.m_isDds = m_Adp201x1Cfg.bDdsType ? 1 : 0;
	dlg.m_DdsType = dlg.m_isDds ? (m_Adp201x1Cfg.bDdsType - 1) : -1;
	dlg.m_isLLCU = m_Adp201x1Cfg.bLlcuConnector;
	dlg.m_PldSdramSize = m_Adp201x1Cfg.wSizeOfPldSdram;
	dlg.m_MGTGen = m_Adp201x1Cfg.dRefMgtGen ? (m_Adp201x1Cfg.dRefMgtGen / 1000000.) : 0;
	dlg.m_isCPU = m_Adp201x1Cfg.bIsCpu;
	dlg.m_CpuClk = m_Adp201x1Cfg.wCpuClock;
	dlg.m_CpuSdramSize = m_Adp201x1Cfg.wSizeOfCpuSdram;
	dlg.m_CpuFlashSize = m_Adp201x1Cfg.wSizeOfCpuFlash;
	dlg.m_RefCpuGen = m_Adp201x1Cfg.dRefCpuGen ? (m_Adp201x1Cfg.dRefCpuGen / 1000000.) : 0;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_Adp201x1Cfg.dSysGen != dlg.m_SysGen ||
			m_Adp201x1Cfg.bDdsType != (dlg.m_isDds ? (dlg.m_DdsType + 1) : 0) ||
			dlg.m_isLLCU != m_Adp201x1Cfg.bLlcuConnector ||
			dlg.m_PldSdramSize != m_Adp201x1Cfg.wSizeOfPldSdram ||
			dlg.m_MGTGen != m_Adp201x1Cfg.dRefMgtGen ||
			dlg.m_isCPU != m_Adp201x1Cfg.bIsCpu ||
			dlg.m_CpuClk != m_Adp201x1Cfg.wCpuClock ||
			dlg.m_CpuSdramSize != m_Adp201x1Cfg.wSizeOfCpuSdram ||
			dlg.m_CpuFlashSize != m_Adp201x1Cfg.wSizeOfCpuFlash ||
			dlg.m_RefCpuGen != m_Adp201x1Cfg.dRefCpuGen
		)
			nResponse |= 0x100;

		m_Adp201x1Cfg.dSysGen = dlg.m_SysGen;
		m_Adp201x1Cfg.bDdsType = dlg.m_isDds ? (dlg.m_DdsType + 1) : 0;
		m_Adp201x1Cfg.bLlcuConnector = dlg.m_isLLCU;
		m_Adp201x1Cfg.wSizeOfPldSdram = dlg.m_PldSdramSize;
		m_Adp201x1Cfg.dRefMgtGen = U32(dlg.m_MGTGen * 1000000.);
		m_Adp201x1Cfg.bIsCpu = dlg.m_isCPU;
		m_Adp201x1Cfg.wCpuClock = dlg.m_CpuClk;
		m_Adp201x1Cfg.wSizeOfCpuSdram = dlg.m_CpuSdramSize;
		m_Adp201x1Cfg.wSizeOfCpuFlash = dlg.m_CpuFlashSize;
		m_Adp201x1Cfg.dRefCpuGen = U32(dlg.m_RefCpuGen * 1000000.);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
