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

static void	InitDev()
{
	S32		status;

	BRD_displayMode(BRDdm_ERROR | BRDdm_FATAL);//|BRDerrd_CONSOLE);
	
	BRD_Error* pErrInfo = new BRD_Error;
//	status = BRD_error(&pErrInfo);
	S32	DevNum;
	status = BRD_initEx(BRDinit_FILE | BRDinit_AUTOINIT, "brd.ini", NULL, &DevNum);
	status = BRD_errext(status);
	BRD_displayMode(BRDdm_VISIBLE);//|BRDerrd_CONSOLE);
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
	pDevInfo->bBusType = BUS_TYPE_PCI;
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
	pDevInfo->nInstance = lidList.pLID[CurInst];//CurInst;

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
	pDevInfo->nBaseCfgMemSize = BASEMOD_CFGMEM_SIZE;

	pDevInfo->pAdmCfgMem[0] = new UCHAR[SUBMOD_CFGMEM_SIZE];
	pDevInfo->nAdmCfgMemSize[0] = SUBMOD_CFGMEM_SIZE;
	if(0x53B2 == pDevInfo->wType || 0x5515 == pDevInfo->wType)
	{
		pDevInfo->pAdmCfgMem[1] = new UCHAR[SUBMOD_CFGMEM_SIZE];
		pDevInfo->nAdmCfgMemSize[1] = SUBMOD_CFGMEM_SIZE;
	}
	else
	{
		pDevInfo->pAdmCfgMem[1] = 0;
		pDevInfo->nAdmCfgMemSize[1] = 0;
	}
	pDevInfo->pAdmCfgMem[2] = 0;
	pDevInfo->pAdmCfgMem[3] = 0;
	pDevInfo->nAdmCfgMemSize[2] = 0;
	pDevInfo->nAdmCfgMemSize[3] = 0;
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
	if(pDevInfo->pAdmCfgMem[1])
		delete[] pDevInfo->pAdmCfgMem[1];
//	MessageBox( NULL, "BRD_cleanup", "", MB_OK);
	int CurInst = pDevInfo->nInstance;
//	if(!CurInst)
//	int status = BRD_cleanup();
	BRD_cleanup();
}

//***************************************************************************************
//  DEVICE_ReadIdCfgRom - функция служит для чтения ППЗУ
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 1 - успешное завершение, 0 - ошибка
//  Notes:  данная функция вызывается по нажатию на соответствующую кнопку
//***************************************************************************************
DEVICE_API int __stdcall DEVICE_ReadIdCfgRom(PDEVICE_INFO pDevInfo, UCHAR bDevs)
{
	int CurInst = pDevInfo->nInstance;
	BRD_Handle handle = BRD_open(CurInst, 0, NULL);
	if( !handle )
		return 0;

	BRD_PuList PuListTmp[1];
	U32 ItemReal;
	BRD_puList(handle, PuListTmp, 1, &ItemReal);
	BRD_PuList	*PuList = new BRD_PuList[ItemReal];
	U32	ItemsCnt = ItemReal;
	BRD_puList(handle, PuList, ItemsCnt, &ItemReal);
	if( ItemReal > ItemsCnt )
	{
		BRD_close(handle);
		delete [] PuList;
		pDevInfo->nRealBaseCfgSize = 0;
		pDevInfo->nRealAdmCfgSize[0] = 0;
		return 0;
	}

	ULONG status = BRDerr_OK;
	// считывание ICR базового модуля
	int nSuccess = 0;
	if( (bDevs == READ_WRITE_BASEMODULE) || (bDevs == READ_WRITE_ALL) )
	{
		ULONG puBaseIcrId = 0;
		for(ULONG ii = 0; ii < ItemReal; ii++)
		{
			if(PuList[ii].puCode == BASE_ID_TAG)
			{
				puBaseIcrId = PuList[ii].puId;
				break;
			}
		}
		if( puBaseIcrId == 0 )
		{
			for(ULONG ii = 0; ii < ItemReal; ii++)
			{
				if( PuList[ii].puId == 0x1 )
				{
					puBaseIcrId = PuList[ii].puId;
					break;
				}
			}
		}

		if( puBaseIcrId )
		{
			status = BRD_puRead(handle, puBaseIcrId, 0, pDevInfo->pBaseCfgMem, BASEMOD_CFGMEM_SIZE);
			if(!BRD_errcmp(status, BRDerr_OK))
				MessageBox(NULL, "ERROR by reading base module ICR", "IcrBardy", MB_OK);
			else
				if(*(PUSHORT)pDevInfo->pBaseCfgMem == BASE_ID_TAG)
				{
					pDevInfo->nRealBaseCfgSize = *((PUSHORT)pDevInfo->pBaseCfgMem + 2);
					nSuccess = 1;
					if(pDevInfo->nRealBaseCfgSize > BASEMOD_CFGMEM_SIZE)
						pDevInfo->nRealBaseCfgSize = 0;
				}
		}
	}
	if( !nSuccess )
		pDevInfo->nRealBaseCfgSize = 0;

	// считывание ICR субмодуля
	nSuccess = 0;
	if( (bDevs == READ_WRITE_SUBMODULE) || (bDevs == READ_WRITE_ALL) )
	{
		ULONG puAdmIcrId = 0;
		int iSub = 0;
		for(ULONG ii = 0; ii < ItemReal; ii++)
		{
			if(PuList[ii].puCode == ADM_ID_TAG)
			{
				puAdmIcrId = PuList[ii].puId;
				status = BRD_puRead(handle, puAdmIcrId, 0, pDevInfo->pAdmCfgMem[iSub], SUBMOD_CFGMEM_SIZE);
				//sprintf(msg, "Reading submodule ICR, status = 0X%08X", status);
				//MessageBox(NULL, msg, "IcrBardy", MB_OK);
				if(!BRD_errcmp(status, BRDerr_OK))
					MessageBox(NULL, "ERROR by reading submodule ICR", "IcrBardy", MB_OK);
				else
					if(*(PUSHORT)pDevInfo->pAdmCfgMem[iSub] == ADM_ID_TAG)
					{
						pDevInfo->nRealAdmCfgSize[iSub] = *((PUSHORT)pDevInfo->pAdmCfgMem[iSub] + 2);
						if(iSub) *((PUCHAR)pDevInfo->pAdmCfgMem[iSub] + 6) = iSub;
						nSuccess = 1;
					}
				iSub++;
			}
		}
	}
	//if( (bDevs == READ_WRITE_SUBMODULE) || (bDevs == READ_WRITE_ALL) )
	//{
	//	ULONG puAdmIcrId = 0;
	//	for(ULONG ii = 0; ii < ItemReal; ii++)
	//	{
	//		if(PuList[ii].puCode == ADM_ID_TAG)
	//		{
	//			puAdmIcrId = PuList[ii].puId;
	//			break;
	//		}
	//	}

	//	if( puAdmIcrId )
	//	{
	//		//char msg[128];
	//		status = BRD_puRead(handle, puAdmIcrId, 0, pDevInfo->pAdmCfgMem[0], SUBMOD_CFGMEM_SIZE);
	//		//sprintf(msg, "Reading submodule ICR, status = 0X%08X", status);
	//		//MessageBox(NULL, msg, "IcrBardy", MB_OK);
	//		if(!BRD_errcmp(status, BRDerr_OK))
	//			MessageBox(NULL, "ERROR by reading submodule ICR", "IcrBardy", MB_OK);
	//		else
	//			if(*(PUSHORT)pDevInfo->pAdmCfgMem[0] == ADM_ID_TAG)
	//			{
	//				pDevInfo->nRealAdmCfgSize[0] = *((PUSHORT)pDevInfo->pAdmCfgMem[0] + 2);
	//				nSuccess = 1;
	//			}
	//	}
	//}
	if( !nSuccess )
		pDevInfo->nRealAdmCfgSize[0] = 0;

	BRD_close(handle);
	delete [] PuList;

	return 1;
}

//***************************************************************************************
//  DEVICE_WriteIdCfgRom - функция служит для записи ППЗУ
//  Input:  pDevInfo - указатель на структуру для обмена информацией
//  Output: return - 1 - успешное завершение, 0 - ошибка
//  Notes:  данная функция вызывается по нажатию на соответствующую кнопку
//***************************************************************************************
DEVICE_API int __stdcall DEVICE_WriteIdCfgRom(PDEVICE_INFO pDevInfo, UCHAR bDevs)
{
	int CurInst = pDevInfo->nInstance;
	BRD_Handle handle = BRD_open(CurInst, 0, NULL);
	if( !handle )
		return 0;

	BRD_PuList PuListTmp[50];
	U32 ItemReal;
	BRD_puList(handle, PuListTmp, 50, &ItemReal);
	BRD_PuList	*PuList = new BRD_PuList[ItemReal];
	U32	ItemsCnt = ItemReal;
	BRD_puList(handle, PuList, ItemsCnt, &ItemReal);
	if( ItemReal > ItemsCnt )
	{
		BRD_close(handle);
		delete [] PuList;
		return 0;
	}

	ULONG status = BRDerr_OK;
	// прописывание ICR базового модуля
	if( (bDevs == READ_WRITE_BASEMODULE) || (bDevs == READ_WRITE_ALL) )
	{
		ULONG puBaseIcrId = 0;
		for(ULONG ii = 0; ii < ItemReal; ii++)
		{
			if(PuList[ii].puCode == BASE_ID_TAG)
			{
				puBaseIcrId = PuList[ii].puId;
				break;
			}
		}
		if( puBaseIcrId == 0 )
		{
			for(ULONG ii = 0; ii < ItemReal; ii++)
			{
				if( PuList[ii].puId == 0x1 )
				{
					puBaseIcrId = PuList[ii].puId;
					break;
				}
			}
		}

		if( puBaseIcrId )
		{
			BRD_puEnable(handle, puBaseIcrId);
			status = BRD_puWrite(handle, puBaseIcrId, 0, pDevInfo->pBaseCfgMem, pDevInfo->nRealBaseCfgSize);
			if(!BRD_errcmp(status, BRDerr_OK))
				MessageBox(NULL, "ERROR by writing base module ICR", "IcrBardy", MB_OK);
		}
	}

	// прописывание ICR субмодуля
	if( (bDevs == READ_WRITE_SUBMODULE) || (bDevs == READ_WRITE_ALL) )
	{
		ULONG puAdmIcrId = 0;
		int iSub = 0;
		for(ULONG ii = 0; ii < ItemReal; ii++)
		{
			if(PuList[ii].puCode == ADM_ID_TAG)
			{
				puAdmIcrId = PuList[ii].puId;
				BRD_puEnable(handle, puAdmIcrId);
				status = BRD_puWrite(handle, puAdmIcrId, 0, pDevInfo->pAdmCfgMem[iSub], pDevInfo->nRealAdmCfgSize[iSub]);
				if(!BRD_errcmp(status, BRDerr_OK))
					MessageBox(NULL, "ERROR by writing submodule ICR", "IcrBardy", MB_OK);
				iSub++;
			}
		}
	}
	//if( (bDevs == READ_WRITE_SUBMODULE) || (bDevs == READ_WRITE_ALL) )
	//{
	//	ULONG puAdmIcrId = 0;
	//	for(ULONG ii = 0; ii < ItemReal; ii++)
	//	{
	//		if(PuList[ii].puCode == ADM_ID_TAG)
	//		{
	//			puAdmIcrId = PuList[ii].puId;
	//			break;
	//		}
	//	}

	//	if( puAdmIcrId )
	//	{
	//		BRD_puEnable(handle, puAdmIcrId);
	//		status = BRD_puWrite(handle, puAdmIcrId, 0, pDevInfo->pAdmCfgMem[0], pDevInfo->nRealAdmCfgSize[0]);
	//		if(!BRD_errcmp(status, BRDerr_OK))
	//			MessageBox(NULL, "ERROR by writing submodule ICR", "IcrBardy", MB_OK);
	//	}
	//}

	BRD_close(handle);
	delete [] PuList;

	return 1;
}

// ****************** End of file icrbardy.cpp ***************
