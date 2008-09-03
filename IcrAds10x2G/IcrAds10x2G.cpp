// IcrAds10x2G.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "IcrAds10x2GApp.h"

#define	BASEMOD_API_EXPORTS
#include "basemod.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "icr.h"

#include "IcrAds10x2g.h"

// инициализация конфигурационных структур
ICR_CfgAds10x2g m_AdsCfg = { ADS10X2G_CFG_TAG, 7, 1, 66000000, 1, 0, 40000000, 2000000000};
ICR_CfgAdc m_AdcCfg = { ADC_CFG_TAG, 14, 0, 0, 10, 1, 200000000, 2000000000, 500};
ICR_CfgDdrSdram m_SdramCfg = { DDRSDRAM_CFG_TAG, 7, 0, 1, 13, 9, 1, 4, 4, 2};

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

// CIcrAds10x2GApp

BEGIN_MESSAGE_MAP(CIcrAds10x2GApp, CWinApp)
END_MESSAGE_MAP()


// CIcrAds10x2GApp construction

CIcrAds10x2GApp::CIcrAds10x2GApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIcrAds10x2GApp object

CIcrAds10x2GApp theApp;


// CIcrAds10x2GApp initialization

BOOL CIcrAds10x2GApp::InitInstance()
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
		lstrcpy(pDevInfo->sName, _T("ADS10x2G"));
		pDevInfo->dType = ADS10x2G;
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
		case ADC_CFG_TAG:
			{
				PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pCurCfgMem;
				m_AdcCfg.wTag = pAdcCfg->wTag;
				m_AdcCfg.wSize = pAdcCfg->wSize;
				m_AdcCfg.bNumber = pAdcCfg->bNumber;
				m_AdcCfg.bAdmNum = pAdcCfg->bAdmNum;
				m_AdcCfg.bBits = pAdcCfg->bBits;
				m_AdcCfg.bEncoding = pAdcCfg->bEncoding;
				m_AdcCfg.dMinRate = pAdcCfg->dMinRate;
				m_AdcCfg.dMaxRate = pAdcCfg->dMaxRate;
				m_AdcCfg.wRange = pAdcCfg->wRange;
				size = sizeof(ICR_CfgAdc);
				RealCfgSize += size;
				break;
			}
		case DDRSDRAM_CFG_TAG:
			{
				PICR_CfgDdrSdram pSdramCfg = (PICR_CfgDdrSdram)pCurCfgMem;
				m_SdramCfg.wTag = pSdramCfg->wTag;
				m_SdramCfg.wSize = pSdramCfg->wSize;
				m_SdramCfg.bNumber = pSdramCfg->bNumber;
				m_SdramCfg.bModuleCnt = pSdramCfg->bModuleCnt;
				m_SdramCfg.bColAddrBits = pSdramCfg->bColAddrBits;
				m_SdramCfg.bRowAddrBits = pSdramCfg->bRowAddrBits;
				m_SdramCfg.bModuleBanks = pSdramCfg->bModuleBanks;
				m_SdramCfg.bChipBanks = pSdramCfg->bChipBanks;
				m_SdramCfg.bPrimaryWidth = pSdramCfg->bPrimaryWidth;
				m_SdramCfg.bCasLatency = pSdramCfg->bCasLatency;
				size = sizeof(ICR_CfgDdrSdram);
				RealCfgSize += size;
				break;
			}
		case ADS10X2G_CFG_TAG:
			{
				PICR_CfgAds10x2g pAdsCfg = (PICR_CfgAds10x2g)pCurCfgMem;
				m_AdsCfg.wTag = pAdsCfg->wTag;
				m_AdsCfg.wSize = pAdsCfg->wSize;
				m_AdsCfg.bAdmIfCnt = pAdsCfg->bAdmIfCnt;
				m_AdsCfg.dSysGen = pAdsCfg->dSysGen;
				m_AdsCfg.bAdcCnt = pAdsCfg->bAdcCnt;
				m_AdsCfg.bSdramCfgCnt = pAdsCfg->bSdramCfgCnt;
				m_AdsCfg.dPllRefGen = pAdsCfg->dPllRefGen;
				m_AdsCfg.dPllFreq = pAdsCfg->dPllFreq;
				pDeviceInfo->bAdmIfCnt = pAdsCfg->bAdmIfCnt;
                size = sizeof(ICR_CfgAds10x2g);
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

	m_AdsCfg.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	PICR_CfgAds10x2g pAdsCfg = (PICR_CfgAds10x2g)pCurCfgMem;
	pAdsCfg->wTag = pDeviceInfo->dType;
	pAdsCfg->wSize = sizeof(ICR_CfgAds10x2g) - 4;
	pAdsCfg->bAdmIfCnt = m_AdsCfg.bAdmIfCnt;
	pAdsCfg->dSysGen = m_AdsCfg.dSysGen;
	pAdsCfg->bAdcCnt = m_AdsCfg.bAdcCnt;
	pAdsCfg->bSdramCfgCnt = m_AdsCfg.bSdramCfgCnt;
	pAdsCfg->dPllRefGen = m_AdsCfg.dPllRefGen;
	pAdsCfg->dPllFreq = m_AdsCfg.dPllFreq;

	pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAds10x2g));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	PICR_CfgAdc pAdcCfg = (PICR_CfgAdc)pCurCfgMem;
	pAdcCfg->wTag = ADC_CFG_TAG;
	pAdcCfg->wSize = sizeof(ICR_CfgAdc) - 4;
	pAdcCfg->bNumber = 0;
	pAdcCfg->bAdmNum = 0;//m_AdcCfg.AdmNumber;
	pAdcCfg->bBits = m_AdcCfg.bBits;
	pAdcCfg->bEncoding = m_AdcCfg.bEncoding;
	pAdcCfg->dMinRate = m_AdcCfg.dMinRate;
	pAdcCfg->dMaxRate = m_AdcCfg.dMaxRate;
	pAdcCfg->wRange = m_AdcCfg.wRange;

	pCurCfgMem = (USHORT*)((UCHAR*)pCurCfgMem + sizeof(ICR_CfgAdc));
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(pAdsCfg->bSdramCfgCnt)
	{
		PICR_CfgDdrSdram pSdramCfg = (PICR_CfgDdrSdram)pCurCfgMem;
		pSdramCfg->wTag = DDRSDRAM_CFG_TAG;
		pSdramCfg->wSize = sizeof(ICR_CfgSdram) - 4;
		pSdramCfg->bNumber = 0;
		pSdramCfg->bModuleCnt = m_SdramCfg.bModuleCnt;
		pSdramCfg->bColAddrBits = m_SdramCfg.bColAddrBits;
		pSdramCfg->bRowAddrBits = m_SdramCfg.bRowAddrBits;
		pSdramCfg->bModuleBanks = m_SdramCfg.bModuleBanks;
		pSdramCfg->bChipBanks = m_SdramCfg.bChipBanks;
		pSdramCfg->bPrimaryWidth = m_SdramCfg.bPrimaryWidth;
		pSdramCfg->bCasLatency = m_SdramCfg.bCasLatency;

		pCurCfgMem = (PUSHORT)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDdrSdram));
		if(pCurCfgMem >= pEndCfgMem)
			return 1;
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

	CIcrAds10x2GDlg dlg;
//	lstrcpy(dlg.baseInfo.sName, pDeviceInfo->sName);
//	dlg.baseInfo.bAdmIfCnt = pDeviceInfo->bAdmIfCnt;

	dlg.m_SysGen = m_AdsCfg.dSysGen;
//	dlg.m_AdcCnt = m_AdsCfg.bAdcCnt;
	dlg.m_SdramCnt = m_AdsCfg.bSdramCfgCnt;
	dlg.m_PllRefGen = m_AdsCfg.dPllRefGen;
	dlg.m_PllFreq = m_AdsCfg.dPllFreq;

	dlg.m_AdcRange = m_AdcCfg.wRange;
	dlg.m_AdcRateMax = m_AdcCfg.dMaxRate;
	dlg.m_AdcRateMin = m_AdcCfg.dMinRate;
//	dlg.m_NumOfAdc = m_AdmCfg.bAdcCnt;

	dlg.m_SdramNum = m_SdramCfg.bNumber;
	dlg.m_SdramModules = m_SdramCfg.bModuleCnt >> 1;
	dlg.m_SdramColAddrBits = m_SdramCfg.bColAddrBits - 8;
	dlg.m_SdramRowAddrBits = m_SdramCfg.bRowAddrBits - 11;
	dlg.m_SdramModuleBanks = m_SdramCfg.bModuleBanks >> 1;
	dlg.m_SdramChipBanks = m_SdramCfg.bChipBanks >> 2;
	dlg.m_SdramPrimWidth = m_SdramCfg.bPrimaryWidth >> 3;
	dlg.m_SdramCasLat = m_SdramCfg.bCasLatency - 2;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		if( 
			m_AdsCfg.dSysGen != dlg.m_SysGen ||
			m_AdsCfg.bSdramCfgCnt != dlg.m_SdramCnt ||
			m_AdsCfg.dPllRefGen != dlg.m_PllRefGen ||
			m_AdsCfg.dPllFreq != dlg.m_PllFreq ||
			m_AdcCfg.bBits != 10 ||
			m_AdcCfg.bEncoding != 1 ||
			m_AdcCfg.wRange != dlg.m_AdcRange ||
			m_AdcCfg.dMaxRate != dlg.m_AdcRateMax ||
			m_AdcCfg.dMinRate != dlg.m_AdcRateMin ||
			m_SdramCfg.bNumber != dlg.m_SdramNum ||
			m_SdramCfg.bModuleCnt != 1 << dlg.m_SdramModules ||
			m_SdramCfg.bColAddrBits != dlg.m_SdramColAddrBits + 8 ||
			m_SdramCfg.bRowAddrBits != dlg.m_SdramRowAddrBits + 11 ||
			m_SdramCfg.bModuleBanks != 1 << dlg.m_SdramModuleBanks ||
			m_SdramCfg.bChipBanks != 2 << dlg.m_SdramChipBanks ||
			m_SdramCfg.bPrimaryWidth != 1 << (dlg.m_SdramPrimWidth + 2) ||
			m_SdramCfg.bCasLatency != dlg.m_SdramCasLat + 2
		)
			nResponse |= 0x100;

		m_AdsCfg.dSysGen = dlg.m_SysGen;
//		m_AmbpCfg.bSdramSlotCnt = dlg.m_SlotCnt;
		m_AdsCfg.bSdramCfgCnt = dlg.m_SdramCnt;
		m_AdsCfg.dPllRefGen = dlg.m_PllRefGen;
		m_AdsCfg.dPllFreq = dlg.m_PllFreq;

		m_AdcCfg.bBits = 10;
		m_AdcCfg.bEncoding = 1;
		m_AdcCfg.wRange = dlg.m_AdcRange;
		m_AdcCfg.dMaxRate = dlg.m_AdcRateMax;
		m_AdcCfg.dMinRate = dlg.m_AdcRateMin;

		m_SdramCfg.bNumber = dlg.m_SdramNum;
//		m_SdramCfg.bSlotCnt = 1 << dlg.m_SdramSlots;
		m_SdramCfg.bModuleCnt = 1 << dlg.m_SdramModules;
		m_SdramCfg.bColAddrBits = dlg.m_SdramColAddrBits + 8;
		m_SdramCfg.bRowAddrBits = dlg.m_SdramRowAddrBits + 11;
		m_SdramCfg.bModuleBanks = 1 << dlg.m_SdramModuleBanks;
		m_SdramCfg.bChipBanks = 2 << dlg.m_SdramChipBanks;
		m_SdramCfg.bPrimaryWidth = 1 << (dlg.m_SdramPrimWidth + 2);
		m_SdramCfg.bCasLatency = dlg.m_SdramCasLat + 2;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	return (int)nResponse;
}
