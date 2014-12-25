//****************** File Icrfmc119e.h *******************************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  базового модуля FMC119E
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  FMC119E base modules
//
//	Copyright (c) 2011-2012, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers

//*******************************************************************
#ifndef __ICRFMC119E_H
 #define __ICRFMC119E_H

#pragma pack(push, 1)    

const USHORT FMC119E_CFG_TAG = 0x3019; // тэг для структуры конфигурационных параметров базового модуля FMC119E

// FMC119E module configuration
// Конфигурационная структура базового модуля FMC119E
typedef struct _ICR_CfgFmc119e {
	U16	wTag;				// тэг структуры (FMC119E_CFG_TAG)
	U16	wSize;				// размер всех следующих полей структуры
	
	U08 bPldType;			// Тип ПЛИС(1-XC7K325T-2FFG900С, 0-XC7K410T-2FFG900С)
	U08 bIsInternalDDR3;	// Установлена ли встроенная память DDR3 128x32 Мслов
	U08 bIsSodimDDR3;		// Установлена ли память DDR3 SODIM
	U08	bIsSynx;			// Установлен ли интерфейс SYNX	
	U08	bIsIpass;			// Установлен ли интерфейс iPASS
	U08	bIsRs;				// Установлен ли интерфейс RS-232/485/422
	U08 bProgGen;			// Программируемый генератор(0-не установлен, 1-установлен Si570)
	U08	bGenAdr;			// адресный код програм. генератора: 0x49 по умолчанию
	U32	nGenRef;			// заводская установка частоты програм. генератора (Гц)
	U32	nGenRefMax;			// максимальная частота програм. генератора (Гц)
	U08 bTempRange;			// Диапазон температур(0-индустриальный, 1-коммерческий)	
} ICR_CfgFmc119e, *PICR_CfgFmc119e;

#pragma pack(pop)

#endif	// __ICRFMC119E_H

// ****************** End of file Icrfmc119e.h **********************
