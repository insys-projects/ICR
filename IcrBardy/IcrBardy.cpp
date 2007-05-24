//****************** File icrbardy.cpp ********************************
//
//  Исходный файл
//	для плагина BRD драйверов устройств
//
//  Source file
//	for Plug-in of device BRD drivers
//
//	Copyright (c) 2002-2003, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  20-08-03 - builded
//
//*******************************************************************

#include "stdafx.h"

#include "brd.h"
#include "icr.h"

#define	DEVICE_API_EXPORTS
#include "device.h"

#define MAXDEVICES 32
// размер памяти, выделяемой под конфигурацию
// (максимальный размер ППЗУ, устанавливаемого на модуль)
#define BASEMOD_CFGMEM_SIZE 512
#define SUBMOD_CFGMEM_SIZE 256

static void	InitDev()
{
	S32		status;

	BRD_displayMode(BRDdm_VISIBLE);//|BRDerrd_CONSOLE);
	
	BRD_Error* pErrInfo = new BRD_Error;
//	status = BRD_error(&pErrInfo);
	S32	DevNum;
	status = BRD_initEx(BRDinit_FILE | BRDinit_AUTOINIT, "brd.ini", NULL, &DevNum);
	status = BRD_errext(status);
	if(status != BRDerr_OK)
		status = BRD_init("brd.ini", &DevNum);
//	status = BRD_error(&pErrInfo);
}

//***************************************************************************************
//  DEVICE_GetInfo - функция служит для определения поддерживаемых базовых модулей, установленных в ПК
//  Input:  pNumDev - указатель на номер экземпляра (перебираются последовательно, начиная с 0)
//          pDevInfo - указатель на структуру для обмена информацией
//  Output: pNumDev - если -1, то больше установленных базовых модулей нет
//  Notes:  данная функция вызывается первой, в цикле с индексом, равным *pNumDev
//***************************************************************************************
DEVICE_API void __stdcall DEVICE_GetInfo(int* pNumDev, PDEVICE_INFO pDevInfo)
{
	pDevInfo->bBusType = 1; //PCIBus;
	int CurInst = *pNumDev;
	if(!CurInst)
		InitDev();
	BRD_LidList lidList;
	lidList.item = MAXDEVICES;
	lidList.pLID = new U32[MAXDEVICES];
	BRD_shell(BRDshl_LID_LIST, &lidList);
//	status = BRD_shell(BRDshl_LID_LIST, &lidList);
//	status = BRD_error(&pErrInfo);
	if((UINT)CurInst >= lidList.itemReal)
	{
		*pNumDev = -1;
		return;
	}
	pDevInfo->dInstance = lidList.pLID[CurInst];//CurInst;

	BRD_Info info;
	info.size = sizeof(info);
	BRD_getInfo(lidList.pLID[CurInst], &info );
	lstrcpy(pDevInfo->sName, info.name);
	pDevInfo->wType = info.boardType >> 16;
	pDevInfo->bVersion = info.boardType & 0xff;
	pDevInfo->wBusNum = info.bus;
	pDevInfo->wDevNum = info.dev;
	pDevInfo->wSlotNum = info.slot;

	pDevInfo->pBaseCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];
	pDevInfo->pAdmCfgMem[0] = new UCHAR[SUBMOD_CFGMEM_SIZE];
	pDevInfo->pAdmCfgMem[1] = 0;
	pDevInfo->pAdmCfgMem[2] = 0;
	pDevInfo->pAdmCfgMem[3] = 0;
	pDevInfo->dBaseCfgMemSize = BASEMOD_CFGMEM_SIZE;
	pDevInfo->dAdmCfgMemSize[0] = SUBMOD_CFGMEM_SIZE;
	pDevInfo->dAdmCfgMemSize[1] = 0;
	pDevInfo->dAdmCfgMemSize[2] = 0;
	pDevInfo->dAdmCfgMemSize[3] = 0;
}

//***************************************************************************************
//  DEVICE_Close - функция служит для освобождения занятой памяти
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: 
//  Notes:  данная функция вызывается перед завершением работы основной программы
//***************************************************************************************
DEVICE_API void __stdcall DEVICE_Close(PDEVICE_INFO pDevInfo)
{
	delete[] pDevInfo->pBaseCfgMem;
	delete[] pDevInfo->pAdmCfgMem[0];
//	MessageBox( NULL, "BRD_cleanup", "", MB_OK);
	int CurInst = pDevInfo->dInstance;
//	if(!CurInst)
//	int status = BRD_cleanup();
		BRD_cleanup();
}

//***************************************************************************************
//  DEVICE_ReadIdCfgRom - функция служит для чтения ППЗУ
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 
//  Notes:  данная функция вызывается по нажатию на соответствующую кнопку
//***************************************************************************************
DEVICE_API int __stdcall DEVICE_ReadIdCfgRom(PDEVICE_INFO pDevInfo)
{
	int Status = 0;
	int CurInst = pDevInfo->dInstance;
	BRD_Handle handle = BRD_open(CurInst, 0, NULL);
//	int hDAQ = DeviceOpen(CurInst);
//	if(hDAQ) {
	if(handle) {
		ULONG puBaseIcrId = 0, puAdmIcrId = 0;
		BRD_PuList PuList[5];
		U32 ItemReal;
		BRD_puList(handle, PuList, 5, &ItemReal);
		if(ItemReal <= 5)
		{
			for(ULONG j = 0; j < ItemReal; j++)
			{
				if(PuList[j].puCode == BASE_ID_TAG)
				{
					puBaseIcrId = PuList[j].puId;
					break;
				}
			}
			if(puBaseIcrId)
			{
				BRD_puRead(handle, puBaseIcrId, 0, pDevInfo->pBaseCfgMem, BASEMOD_CFGMEM_SIZE);
				if(*(PUSHORT)pDevInfo->pBaseCfgMem == BASE_ID_TAG)
					pDevInfo->dRealBaseCfgSize = *((PUSHORT)pDevInfo->pBaseCfgMem + 2);
				else
					pDevInfo->dRealBaseCfgSize = 0;
				for(ULONG j = 0; j < ItemReal; j++)
					if(PuList[j].puCode == ADM_ID_TAG)
					{
						puAdmIcrId = PuList[j].puId;
						break;
					}
				if(puAdmIcrId)
				{
					BRD_puRead(handle, puAdmIcrId, 0, pDevInfo->pAdmCfgMem[0], SUBMOD_CFGMEM_SIZE);
					if(*(PUSHORT)pDevInfo->pAdmCfgMem[0] == ADM_ID_TAG)
						pDevInfo->dRealAdmCfgSize[0] = *((PUSHORT)pDevInfo->pAdmCfgMem[0] + 2);
					else
						pDevInfo->dRealAdmCfgSize[0] = 0;
				}
				else
					pDevInfo->dRealAdmCfgSize[0] = 0;
			}
			else
				pDevInfo->dRealBaseCfgSize = 0;
		}
		else
		{
			pDevInfo->dRealBaseCfgSize = 0;
			pDevInfo->dRealAdmCfgSize[0] = 0;
		}
		BRD_close(handle);
		Status = 1;
	}
	return Status;
}

//***************************************************************************************
//  DEVICE_WriteIdCfgRom - функция служит для записи ППЗУ
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 
//  Notes:  данная функция вызывается по нажатию на соответствующую кнопку
//***************************************************************************************
DEVICE_API int __stdcall DEVICE_WriteIdCfgRom(PDEVICE_INFO pDevInfo)
{
	int Status = 0;
	int CurInst = pDevInfo->dInstance;
	BRD_Handle handle = BRD_open(CurInst, 0, NULL);
	if(handle) {
		ULONG puBaseIcrId = 0, puAdmIcrId = 0;
		BRD_PuList PuList[5];
		U32 ItemReal;
		Status = BRD_puList(handle, PuList, 5, &ItemReal);
		if(ItemReal <= 5)
		{
			for(ULONG j = 0; j < ItemReal; j++)
				if(PuList[j].puCode == BASE_ID_TAG)
				{
					puBaseIcrId = PuList[j].puId;
					break;
				}
			if(puBaseIcrId)
			{
				BRD_puEnable(handle, puBaseIcrId);
				BRD_puWrite(handle, puBaseIcrId, 0, pDevInfo->pBaseCfgMem, pDevInfo->dRealBaseCfgSize);
				for(ULONG j = 0; j < ItemReal; j++)
					if(PuList[j].puCode == ADM_ID_TAG)
					{
						puAdmIcrId = PuList[j].puId;
						break;
					}
				if(puAdmIcrId)
				{
					BRD_puEnable(handle, puAdmIcrId);
					BRD_puWrite(handle, puAdmIcrId, 0, pDevInfo->pAdmCfgMem[0], pDevInfo->dRealAdmCfgSize[0]);
				}
			}
		}
		BRD_close(handle);
		Status = 1;
	}
	return Status;
}

// ****************** End of file icrbardy.cpp ***************
