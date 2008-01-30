//****************** File Icr008A.h ***********************
//
//  ќпределени€ констант и структур 
//	дл€ работы с конфигурационным ѕѕ«”
//  дл€ субмодулей 
//
//	Copyright (c) 2002-2004, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  30-08-04 - builded
//
//*********************************************************

#ifndef _ICR008A_H
 #define _ICR008A_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008A

//  онфигурационные параметры субмодул€
typedef struct _ICR_Cfg008A {
	USHORT	wTag;			// тэг структуры (ADM_CFG_TAG)
	USHORT	wSize;			// размер всех следующих полей структуры
	UCHAR	bAdmIfNum;		// номер интерфейса ADM
	ULONG	dGen;			// значение опорного генератора
	UCHAR	bDacCnt;		// количество ÷јѕ
	ULONG	dLPFCutoff;		// частота среза фильтра низких частот (√ц)
	UCHAR	bOutResist;		// выходное сопротивление (0 - 50 ќм, 1 - 75 ќм)
	UCHAR	bIsQuadMod;		// наличие квадратурного модул€тора
	UCHAR	bIsExtClk;		// наличие входа внешнего тактировани€
	UCHAR	bQuadModType;	// тип квадратурного модул€тора ( 0 Ц AD8345, 1 Ц AD8346, 2 Ц AD8349 )
} ICR_Cfg008A, *PICR_Cfg008A, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008A_H

//****************** End of file Icr008A.h **********************
