// IcrDR16.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrDR16App.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"
#include "IcrDR16.h"

ICR_CfgDR16 g_AdpDR16Cfg = {DR16_CFG_TAG, 52, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
							1, 0, 16, 14, 1, 20000000, 65000000, 0, 0, 500, 50,
							4, 12000000, 500, 0, 0, 1000000000};

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


// CIcrDR16App

BEGIN_MESSAGE_MAP(CIcrDR16App, CWinApp)
END_MESSAGE_MAP()


// CIcrDR16App construction

CIcrDR16App::CIcrDR16App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrDR16App object

CIcrDR16App theApp;

// CIcrDR16App initialization

BOOL CIcrDR16App::InitInstance()
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
		lstrcpy(pDevInfo->sName, "DR-16");
		pDevInfo->dType = DR16;
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

 			case DR16_CFG_TAG:
 			{
 				PICR_CfgDR16 pAdpCfg = (PICR_CfgDR16)pCurCfgMem;

				g_AdpDR16Cfg.wTag				= pAdpCfg->wTag;
				g_AdpDR16Cfg.wSize				= pAdpCfg->wSize;
				g_AdpDR16Cfg.isDuc				= pAdpCfg->isDuc;
				g_AdpDR16Cfg.isDucTransformator = pAdpCfg->isDucTransformator;
				g_AdpDR16Cfg.isGenerator        = pAdpCfg->isGenerator;
				g_AdpDR16Cfg.isSynthesizer      = pAdpCfg->isSynthesizer;
				g_AdpDR16Cfg.isExtTactInput     = pAdpCfg->isExtTactInput;
				g_AdpDR16Cfg.isExtStartInput    = pAdpCfg->isExtStartInput;
				g_AdpDR16Cfg.isExtStartOutput   = pAdpCfg->isExtStartOutput;
				g_AdpDR16Cfg.isLinks            = pAdpCfg->isLinks;
				g_AdpDR16Cfg.isPiox				= pAdpCfg->isPiox;
				g_AdpDR16Cfg.isSynx				= pAdpCfg->isSynx;
				g_AdpDR16Cfg.isLvdsPiox			= pAdpCfg->isLvdsPiox;
				g_AdpDR16Cfg.isPci64			= pAdpCfg->isPci64;
				g_AdpDR16Cfg.isIndustrial		= pAdpCfg->isIndustrial;
				g_AdpDR16Cfg.bAdcCnt			= pAdpCfg->bAdcCnt;
				g_AdpDR16Cfg.bAdcBits			= pAdpCfg->bAdcBits;
				g_AdpDR16Cfg.nAdcMinRate		= pAdpCfg->nAdcMinRate;
				g_AdpDR16Cfg.nAdcMaxRate		= pAdpCfg->nAdcMaxRate;
				g_AdpDR16Cfg.nAdcLowFreq		= pAdpCfg->nAdcLowFreq;
				g_AdpDR16Cfg.nAdcHighFreq		= pAdpCfg->nAdcHighFreq;
				g_AdpDR16Cfg.wAdcRange			= pAdpCfg->wAdcRange;
				g_AdpDR16Cfg.bAdcInpResist		= pAdpCfg->bAdcInpResist;
				g_AdpDR16Cfg.bDdcCnt			= pAdpCfg->bDdcCnt;
				g_AdpDR16Cfg.nDucHighFreq		= pAdpCfg->nDucHighFreq;
				g_AdpDR16Cfg.wDucRange			= pAdpCfg->wDucRange;
				g_AdpDR16Cfg.nGenFreq			= pAdpCfg->nGenFreq;
				g_AdpDR16Cfg.wGenPrec			= pAdpCfg->wGenPrec;
				g_AdpDR16Cfg.nSyntFreq			= pAdpCfg->nSyntFreq;
				
 				size = sizeof(ICR_CfgDR16);
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
 
 	PICR_CfgDR16 pAdpCfg = (PICR_CfgDR16)pCurCfgMem;

 	pAdpCfg->wTag				= DR16_CFG_TAG;
 	pAdpCfg->wSize				= sizeof(ICR_CfgDR16) - 4;
	pAdpCfg->isDuc				= g_AdpDR16Cfg.isDuc;
	pAdpCfg->isDucTransformator = g_AdpDR16Cfg.isDucTransformator;
	pAdpCfg->isGenerator		= g_AdpDR16Cfg.isGenerator;
	pAdpCfg->isSynthesizer		= g_AdpDR16Cfg.isSynthesizer;
	pAdpCfg->isExtTactInput		= g_AdpDR16Cfg.isExtTactInput;
	pAdpCfg->isExtStartInput	= g_AdpDR16Cfg.isExtStartInput;
	pAdpCfg->isExtStartOutput	= g_AdpDR16Cfg.isExtStartOutput;
	pAdpCfg->isLinks			= g_AdpDR16Cfg.isLinks;
	pAdpCfg->isPiox				= g_AdpDR16Cfg.isPiox;
	pAdpCfg->isSynx				= g_AdpDR16Cfg.isSynx;
	pAdpCfg->isLvdsPiox			= g_AdpDR16Cfg.isLvdsPiox;
	pAdpCfg->isPci64			= g_AdpDR16Cfg.isPci64;
	pAdpCfg->isIndustrial		= g_AdpDR16Cfg.isIndustrial;
	pAdpCfg->bAdcCnt			= g_AdpDR16Cfg.bAdcCnt;
	pAdpCfg->bAdcBits			= g_AdpDR16Cfg.bAdcBits;
	pAdpCfg->nAdcMinRate		= g_AdpDR16Cfg.nAdcMinRate;
	pAdpCfg->nAdcMaxRate		= g_AdpDR16Cfg.nAdcMaxRate;
	pAdpCfg->nAdcLowFreq		= g_AdpDR16Cfg.nAdcLowFreq;
	pAdpCfg->nAdcHighFreq		= g_AdpDR16Cfg.nAdcHighFreq;
	pAdpCfg->wAdcRange			= g_AdpDR16Cfg.wAdcRange;
	pAdpCfg->bAdcInpResist		= g_AdpDR16Cfg.bAdcInpResist;
	pAdpCfg->bDdcCnt			= g_AdpDR16Cfg.bDdcCnt;
	pAdpCfg->nDucHighFreq		= g_AdpDR16Cfg.nDucHighFreq;
	pAdpCfg->wDucRange			= g_AdpDR16Cfg.wDucRange;
	pAdpCfg->nGenFreq			= g_AdpDR16Cfg.nGenFreq;
	pAdpCfg->wGenPrec			= g_AdpDR16Cfg.wGenPrec;
	pAdpCfg->nSyntFreq			= g_AdpDR16Cfg.nSyntFreq;

 	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDR16));
 	
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

	IcrDR16Dlg dlg;

	dlg.m_isDuc              = g_AdpDR16Cfg.isDuc;
	dlg.m_isDucTransformator = g_AdpDR16Cfg.isDucTransformator;
	dlg.m_isGenerator        = g_AdpDR16Cfg.isGenerator;
	dlg.m_isSynthesizer      = g_AdpDR16Cfg.isSynthesizer;
	dlg.m_isExtTactInput     = g_AdpDR16Cfg.isExtTactInput;
	dlg.m_isExtStartInput    = g_AdpDR16Cfg.isExtStartInput;
	dlg.m_isExtStartOutput   = g_AdpDR16Cfg.isExtStartOutput;
	dlg.m_isLinks            = g_AdpDR16Cfg.isLinks;
	dlg.m_isPiox             = g_AdpDR16Cfg.isPiox;
	dlg.m_isSynx             = g_AdpDR16Cfg.isSynx;
	dlg.m_isLvdsPiox         = g_AdpDR16Cfg.isLvdsPiox;
	dlg.m_isPci64            = g_AdpDR16Cfg.isPci64;
	dlg.m_isIndustrial       = g_AdpDR16Cfg.isIndustrial;
	dlg.m_bAdcCnt    		 = g_AdpDR16Cfg.bAdcCnt;
	dlg.m_sAdcBits.Format("%d", g_AdpDR16Cfg.bAdcBits);
	dlg.m_nAdcMinRate		 = g_AdpDR16Cfg.nAdcMinRate / 1000000;
	dlg.m_sAdcMaxRate.Format("%d", g_AdpDR16Cfg.nAdcMaxRate / 1000000);
	dlg.m_sAdcLowFreq.Format("%.3f", (REAL32)g_AdpDR16Cfg.nAdcLowFreq / (REAL32)1000000);
	dlg.m_nAdcHighFreq       = g_AdpDR16Cfg.nAdcHighFreq / 1000000;
	dlg.m_sAdcInpResist.Format("%d", g_AdpDR16Cfg.bAdcInpResist);
	dlg.m_sAdcRange.Format("%f", (REAL32)g_AdpDR16Cfg.wAdcRange / (REAL32)1000);
	dlg.m_sDdcCnt.Format("%d", g_AdpDR16Cfg.bDdcCnt);
	dlg.m_nDucHighFreq       = g_AdpDR16Cfg.nDucHighFreq / 1000000;
	dlg.m_sDucRange.Format("%f", (REAL32)g_AdpDR16Cfg.wDucRange / (REAL32)1000);
	dlg.m_nGenFreq  		 = g_AdpDR16Cfg.nGenFreq / 1000000;
	dlg.m_sGenPrec.Format("%.2f", (REAL32)g_AdpDR16Cfg.wGenPrec / (REAL32)100);
	dlg.m_nSyntFreq    		 = g_AdpDR16Cfg.nSyntFreq / 1000000;

	int nResponse = (int)dlg.DoModal(); // Вызвать диалоговое окно

	if(nResponse == IDOK)
	{
// 		U08 bAdcBitsTmp;
// 		bAdcBitsTmp = ; 

		if( 
			g_AdpDR16Cfg.isDuc              != dlg.m_isDuc ||
			g_AdpDR16Cfg.isDucTransformator != dlg.m_isDucTransformator ||
			g_AdpDR16Cfg.isGenerator        != dlg.m_isGenerator ||
			g_AdpDR16Cfg.isSynthesizer      != dlg.m_isSynthesizer ||
			g_AdpDR16Cfg.isExtTactInput     != dlg.m_isExtTactInput ||
			g_AdpDR16Cfg.isExtStartInput    != dlg.m_isExtStartInput ||
			g_AdpDR16Cfg.isExtStartOutput   != dlg.m_isExtStartOutput ||
			g_AdpDR16Cfg.isLinks            != dlg.m_isLinks ||
			g_AdpDR16Cfg.isPiox             != dlg.m_isPiox ||
			g_AdpDR16Cfg.isSynx             != dlg.m_isSynx ||
			g_AdpDR16Cfg.isLvdsPiox         != dlg.m_isLvdsPiox ||
			g_AdpDR16Cfg.isPci64            != dlg.m_isPci64 ||
			g_AdpDR16Cfg.isIndustrial       != dlg.m_isIndustrial ||
			g_AdpDR16Cfg.bAdcCnt            != dlg.m_bAdcCnt ||
			g_AdpDR16Cfg.bAdcBits		    != atoi(dlg.m_sAdcBits.GetString()) ||
			(g_AdpDR16Cfg.nAdcMinRate       != (dlg.m_nAdcMinRate * 1000000)) ||
			(g_AdpDR16Cfg.nAdcMaxRate	    != (atoi(dlg.m_sAdcMaxRate.GetString()) * 1000000)) ||
			(g_AdpDR16Cfg.nAdcLowFreq   	!= (atof(dlg.m_sAdcLowFreq.GetString()) * 1000000)) ||
			(g_AdpDR16Cfg.nAdcHighFreq      != (dlg.m_nAdcHighFreq * 1000000)) ||
			g_AdpDR16Cfg.bAdcInpResist      != atoi(dlg.m_sAdcInpResist.GetString()) ||
			(g_AdpDR16Cfg.wAdcRange   	    != (atof(dlg.m_sAdcRange.GetString()) * 1000)) ||
			g_AdpDR16Cfg.bDdcCnt		    != atoi(dlg.m_sDdcCnt.GetString()) ||
			g_AdpDR16Cfg.nDucHighFreq	    != (dlg.m_nDucHighFreq * 1000000) ||
			(g_AdpDR16Cfg.wDucRange   	    != (atof(dlg.m_sDucRange.GetString()) * 1000)) ||
			(g_AdpDR16Cfg.nGenFreq          != (dlg.m_nGenFreq * 1000000)) ||
			(g_AdpDR16Cfg.wGenPrec   	    != (atof(dlg.m_sGenPrec.GetString()) * 100)) ||
			g_AdpDR16Cfg.nSyntFreq          != (dlg.m_nSyntFreq * 1000000) 
		  )
			nResponse |= 0x100;

			g_AdpDR16Cfg.isDuc              = dlg.m_isDuc;
			g_AdpDR16Cfg.isDucTransformator = dlg.m_isDucTransformator;
			g_AdpDR16Cfg.isGenerator        = dlg.m_isGenerator;
			g_AdpDR16Cfg.isSynthesizer      = dlg.m_isSynthesizer;
			g_AdpDR16Cfg.isExtTactInput     = dlg.m_isExtTactInput;
			g_AdpDR16Cfg.isExtStartInput    = dlg.m_isExtStartInput;
			g_AdpDR16Cfg.isExtStartOutput   = dlg.m_isExtStartOutput;
			g_AdpDR16Cfg.isLinks            = dlg.m_isLinks;
			g_AdpDR16Cfg.isPiox             = dlg.m_isPiox;
			g_AdpDR16Cfg.isSynx             = dlg.m_isSynx;
			g_AdpDR16Cfg.isLvdsPiox         = dlg.m_isLvdsPiox;
			g_AdpDR16Cfg.isPci64            = dlg.m_isPci64;
			g_AdpDR16Cfg.isIndustrial       = dlg.m_isIndustrial;
			g_AdpDR16Cfg.bAdcCnt            = dlg.m_bAdcCnt;
			g_AdpDR16Cfg.bAdcBits		    = atoi(dlg.m_sAdcBits.GetString());	
			g_AdpDR16Cfg.nAdcMinRate        = dlg.m_nAdcMinRate * 1000000;
			g_AdpDR16Cfg.nAdcMaxRate        = atoi(dlg.m_sAdcMaxRate.GetString()) * 1000000;
			g_AdpDR16Cfg.nAdcLowFreq   	    = (atof(dlg.m_sAdcLowFreq.GetString()) * 1000000);
			g_AdpDR16Cfg.nAdcHighFreq       = dlg.m_nAdcHighFreq * 1000000;
			g_AdpDR16Cfg.bAdcInpResist	    = atoi(dlg.m_sAdcInpResist.GetString());	
			g_AdpDR16Cfg.wAdcRange          = atof(dlg.m_sAdcRange.GetString()) * 1000;
			g_AdpDR16Cfg.bDdcCnt		    = atoi(dlg.m_sDdcCnt.GetString());
			g_AdpDR16Cfg.nDucHighFreq	    = dlg.m_nDucHighFreq * 1000000;
			g_AdpDR16Cfg.wDucRange          = atof(dlg.m_sDucRange.GetString()) * 1000;
			g_AdpDR16Cfg.nGenFreq           = dlg.m_nGenFreq * 1000000;
			g_AdpDR16Cfg.wGenPrec           = atof(dlg.m_sGenPrec.GetString()) * 100;
			g_AdpDR16Cfg.nSyntFreq          = dlg.m_nSyntFreq * 1000000;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	return nResponse;
}