// IcrSync8chPCI.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrSync8chPCIApp.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrSync8chPCI.h"

// инициализация конфигурационных структур
ICR_CfgSync8chPCI m_SyncCfg = { SYNC8CHPCI_CFG_TAG, 30, 1, 66000000, 200000000, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0};

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

// CIcrSync8chPCIApp

BEGIN_MESSAGE_MAP(CIcrSync8chPCIApp, CWinApp)
END_MESSAGE_MAP()


// CIcrSync8chPCIApp construction

CIcrSync8chPCIApp::CIcrSync8chPCIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrSync8chPCIApp object

CIcrSync8chPCIApp theApp;


// CIcrSync8chPCIApp initialization

BOOL CIcrSync8chPCIApp::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("Sync8chPCI"));
		pDevInfo->dType = SYNC8CHPCI;
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
		case SYNC8CHPCI_CFG_TAG:
			{
				PICR_CfgSync8chPCI pSyncCfg = (PICR_CfgSync8chPCI)pCurCfgMem;
				m_SyncCfg.wTag = pSyncCfg->wTag;
				m_SyncCfg.wSize = pSyncCfg->wSize;
				m_SyncCfg.bAdmIfCnt = pSyncCfg->bAdmIfCnt;
				m_SyncCfg.dSysGen = pSyncCfg->dSysGen;
				m_SyncCfg.dGen1 = pSyncCfg->dGen1;
				m_SyncCfg.dGen2 = pSyncCfg->dGen2;
				m_SyncCfg.dOcxoGen = pSyncCfg->dOcxoGen;
				m_SyncCfg.dPllFreq = pSyncCfg->dPllFreq;

				m_SyncCfg.bClkChanCnt = pSyncCfg->bClkChanCnt;
				m_SyncCfg.bStrbChanCnt = pSyncCfg->bStrbChanCnt;
				m_SyncCfg.bIsClkE = pSyncCfg->bIsClkE;
				m_SyncCfg.bIsClkF = pSyncCfg->bIsClkF;
				m_SyncCfg.bIsStrbA = pSyncCfg->bIsStrbA;
				m_SyncCfg.bIsStrbB = pSyncCfg->bIsStrbB;
				m_SyncCfg.bIsStrbD = pSyncCfg->bIsStrbD;
				m_SyncCfg.bIsSync = pSyncCfg->bIsSync;
				m_SyncCfg.bIsLF = pSyncCfg->bIsLF;

				pDeviceInfo->bAdmIfCnt = pSyncCfg->bAdmIfCnt;
                size = sizeof(ICR_CfgSync8chPCI);
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

	m_SyncCfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgSync8chPCI pSyncCfg = (PICR_CfgSync8chPCI)pCurCfgMem;
	pSyncCfg->wTag = pDeviceInfo->dType;
	pSyncCfg->wSize = sizeof(ICR_CfgSync8chPCI) - 4;
	pSyncCfg->bAdmIfCnt = m_SyncCfg.bAdmIfCnt;
	pSyncCfg->dSysGen = m_SyncCfg.dSysGen;
	pSyncCfg->dGen1 = m_SyncCfg.dGen1;
	pSyncCfg->dGen2 = m_SyncCfg.dGen2;
	pSyncCfg->dOcxoGen = m_SyncCfg.dOcxoGen;
	pSyncCfg->dPllFreq = m_SyncCfg.dPllFreq;

	pSyncCfg->bClkChanCnt = m_SyncCfg.bClkChanCnt;
	pSyncCfg->bStrbChanCnt = m_SyncCfg.bStrbChanCnt;
	pSyncCfg->bIsClkE = m_SyncCfg.bIsClkE;
	pSyncCfg->bIsClkF = m_SyncCfg.bIsClkF;
	pSyncCfg->bIsStrbA = m_SyncCfg.bIsStrbA;
	pSyncCfg->bIsStrbB = m_SyncCfg.bIsStrbB;
	pSyncCfg->bIsStrbD = m_SyncCfg.bIsStrbD;
	pSyncCfg->bIsSync = m_SyncCfg.bIsSync;
	pSyncCfg->bIsLF = m_SyncCfg.bIsLF;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgSync8chPCI));
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

	CIcrSync8chPCIDlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_SyncCfg.dSysGen;
	dlg.m_Gen1 = m_SyncCfg.dGen1;
	dlg.m_Gen2 = m_SyncCfg.dGen2;
	dlg.m_OcxoGen = m_SyncCfg.dOcxoGen;
	dlg.m_PllFreq = m_SyncCfg.dPllFreq;

	dlg.m_ClkChanCnt = m_SyncCfg.bClkChanCnt;
	dlg.m_StrbChanCnt = m_SyncCfg.bStrbChanCnt;
	dlg.m_ClkE = m_SyncCfg.bIsClkE;
	dlg.m_ClkF = m_SyncCfg.bIsClkF;
	dlg.m_StrboA = m_SyncCfg.bIsStrbA;
	dlg.m_StrboB = m_SyncCfg.bIsStrbB;
	dlg.m_StrboD = m_SyncCfg.bIsStrbD;
	dlg.m_Sync = m_SyncCfg.bIsSync;
	dlg.m_IsLF = m_SyncCfg.bIsLF;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_SyncCfg.dSysGen != dlg.m_SysGen ||
			m_SyncCfg.dGen1 != dlg.m_Gen1 ||
			m_SyncCfg.dGen2 != dlg.m_Gen2 ||
			m_SyncCfg.dOcxoGen != dlg.m_OcxoGen ||
			m_SyncCfg.dPllFreq != dlg.m_PllFreq ||
			m_SyncCfg.bClkChanCnt != dlg.m_ClkChanCnt ||
			m_SyncCfg.bStrbChanCnt != dlg.m_StrbChanCnt ||
			m_SyncCfg.bIsClkE != dlg.m_ClkE ||
			m_SyncCfg.bIsClkF != dlg.m_ClkF ||
			m_SyncCfg.bIsStrbA != dlg.m_StrboA ||
			m_SyncCfg.bIsStrbB != dlg.m_StrboB ||
			m_SyncCfg.bIsStrbD != dlg.m_StrboD ||
			m_SyncCfg.bIsSync != dlg.m_Sync ||
			m_SyncCfg.bIsLF != dlg.m_IsLF
		)
			nResponse |= 0x100;

		m_SyncCfg.dSysGen = dlg.m_SysGen;
		m_SyncCfg.dGen1 = dlg.m_Gen1;
		m_SyncCfg.dGen2 = dlg.m_Gen2;
		m_SyncCfg.dOcxoGen = dlg.m_OcxoGen;
		m_SyncCfg.dPllFreq = dlg.m_PllFreq;
		m_SyncCfg.bClkChanCnt = dlg.m_ClkChanCnt;
		m_SyncCfg.bStrbChanCnt = dlg.m_StrbChanCnt;
		m_SyncCfg.bIsClkE = dlg.m_ClkE;
		m_SyncCfg.bIsClkF = dlg.m_ClkF;
		m_SyncCfg.bIsStrbA = dlg.m_StrboA;
		m_SyncCfg.bIsStrbB = dlg.m_StrboB;
		m_SyncCfg.bIsStrbD = dlg.m_StrboD;
		m_SyncCfg.bIsSync = dlg.m_Sync;
		m_SyncCfg.bIsLF = dlg.m_IsLF;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
