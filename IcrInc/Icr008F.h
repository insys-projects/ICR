//****************** File Icr008F.h ***********************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  для субмодулей ADMDAC216x400M
//
//	Copyright (c) 2008, Instrumental Systems,Corp.
//	Written by Tsikin Eugene
//
//  History:
//  29-01-08 - builded
//
//*********************************************************

#ifndef _ICR008F_H
 #define _ICR008F_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008F

// Конфигурационные параметры субмодуля
typedef struct _ICR_Cfg008F {
	USHORT	wTag;		// тэг структуры (ADM_CFG_TAG)
	USHORT	wSize;		// размер всех следующих полей структуры
	UCHAR	bAdmIfNum;	// номер интерфейса ADM
	UCHAR	bIsGen;		// наличие встроенного опорного генератора
	ULONG	dGen;		// значение опорного генератора
	UCHAR	bFreqTune;	// подстройка частоты встроенного опорного генератора
	//ULONG	dPllRefGen;	// опорный генератор для ФАПЧ in Hz (default 10 MHz)
	//ULONG	dPllFreq;	// частота, выдаваемая ФАПЧ in Hz (default 400 MHz)
	UCHAR	bDacCnt;	// количество ЦАП
	ULONG	dLPFCutoff;	// частота среза фильтра низких частот (Гц)
	UCHAR	bOutResist;	// выходное сопротивление (0 - 50 Ом, 1 - 75 Ом)
	ULONG	dOscFreq;	// частота ГУН (по умолч. 400 МГц)
	UCHAR	bOutCasMod;	// модификация выходного каскада 0 - LF, 1 - HF
	UCHAR	bIsQuadMod;	// наличие квадратурного модулятора
	UCHAR	bQuadModType;// тип квадратурного модулятора ( 0 – AD8345, 1 – AD8346, 2 – AD8349 )
	UCHAR	bIsExtClk;	// наличие входа внешнего тактирования
} ICR_Cfg008F, *PICR_Cfg008F, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008F_H

// ****************** End of file Icr008F.h **********************
