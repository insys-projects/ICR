// IcrSync_cP6.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrSync_cP6App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "IcrSync_cP6.h"

ICR_CfgSync_cP6 g_Sync_cP6Cfg = {SYNCCP6_CFG_TAG, sizeof(ICR_CfgSync_cP6) - 4, 100000000, 1};

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


// CIcrSync_cP6App

BEGIN_MESSAGE_MAP(CIcrSync_cP6App, CWinApp)
END_MESSAGE_MAP()


// CIcrSync_cP6App construction

CIcrSync_cP6App::CIcrSync_cP6App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrSync_cP6App object

CIcrSync_cP6App theApp;


// CIcrSync_cP6App initialization

BOOL CIcrSync_cP6App::InitInstance()
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
 		lstrcpy(pDevInfo->sName, "Sync-cP6");
 		pDevInfo->dType = SYNCCP6;
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
 	PVOID pCurCfgMem  = (PVOID)pDeviceInfo->pCfgMem;
 	PVOID pEndCfgMem  = (PVOID)(pDeviceInfo->pCfgMem + BASEMOD_CFGMEM_SIZE);
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
 
 		case SYNCCP6_CFG_TAG:
 			{
 				PICR_CfgSync_cP6 pCfg = (PICR_CfgSync_cP6)pCurCfgMem;
 
 				g_Sync_cP6Cfg.wTag		    = pCfg->wTag;
 				g_Sync_cP6Cfg.wSize		    = pCfg->wSize;
 				g_Sync_cP6Cfg.nIntGenFreq   = pCfg->nIntGenFreq;
 				g_Sync_cP6Cfg.isInpTactSign = pCfg->isInpTactSign;
 	 
 				size = sizeof(ICR_CfgSync_cP6);
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
 
 	PICR_CfgSync_cP6 pCfg = (PICR_CfgSync_cP6)pCurCfgMem;
 
 	pCfg->wTag		    = SYNCCP6_CFG_TAG;
 	pCfg->wSize		    = sizeof(ICR_CfgSync_cP6) - 4;
 	pCfg->nIntGenFreq   = g_Sync_cP6Cfg.nIntGenFreq;
 	pCfg->isInpTactSign = g_Sync_cP6Cfg.isInpTactSign;
 
 	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgSync_cP6));
 
 	if(pCurCfgMem >= pEndCfgMem)
 		return 1;
 
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
 
	IcrSync_cP6Dlg dlg;

	CString str;
	U32 n;
 	

	str.Format("%f", (REAL32)g_Sync_cP6Cfg.nIntGenFreq / (REAL32)1000000);
	
	//--- Удаление нулей справа ---//
	n = str.ReverseFind('0');

	while(n == (str.GetLength() - 1))
	{
		str.Delete(n);
		n = str.ReverseFind('0');
	}

	n = str.ReverseFind('.');

	if(n == (str.GetLength() - 1))
		str.Delete(n);
	//-----------------------------//
	
	dlg.m_sIntGenFreq = str;
		
	dlg.m_isInpTactSign = g_Sync_cP6Cfg.isInpTactSign;
 	
  	int nResponse = (int)dlg.DoModal(); // Вызвать диалоговое окно
 
 	if(nResponse == IDOK)
 	{
 		if( 
  			(g_Sync_cP6Cfg.nIntGenFreq   != (atof(dlg.m_sIntGenFreq.GetString()) * 1000000)) ||
 			(g_Sync_cP6Cfg.isInpTactSign != dlg.m_isInpTactSign) 
 		  )
 			nResponse |= 0x100;
 
		g_Sync_cP6Cfg.nIntGenFreq   = (U32)(atof(dlg.m_sIntGenFreq.GetString()) * 1000000);
		g_Sync_cP6Cfg.isInpTactSign = dlg.m_isInpTactSign; 
 	}
 	else if (nResponse == IDCANCEL)
 	{
 		// TODO: Place code here to handle when the dialog is
 		//  dismissed with Cancel
 	}

	return nResponse;
}