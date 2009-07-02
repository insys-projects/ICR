//****************** File IcrVK3.h ***********************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  для модуля VK3
//
//*********************************************************

#ifndef _ICRVK3_H
#define _ICRVK3_H

#include "utypes.h"
#include "icr.h"

#pragma pack(push, 1)    

const USHORT VK3_CFG_TAG = 0x5506; // тэг для структуры конфигурационных параметров модуля VK3

// VK3 module configuration
// Конфигурационная структура модуля VK3
typedef struct _ICR_Cfg5506 
{
	U16		wTag;			// tag of structure (0x5506)
	U16		wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U32		nNum;			// Порядковый номер изделия
	U08		bDdrModuleNum;	// Количество слотов динамической памяти
	REAL32	fSysGen;		// Частота системного генератора (MHz) - 66.666
	U16		wRefGen;		// Частота опорного генератора (MHz) - 10
	U08		isDacBias;		// ЦАП смещения
	U08		bDacBiasBits;	// Разрядность ЦАП смещения
	U08		bAdcChanNum;	// Количество каналов АЦП 0, 1
	U08		bAdcInpNum;		// Число входов коммутатора АЦП - 0, 1, 2
	U08		isAdcInpAdd;	// Дополнительный вход АЦП, 1 - есть, 0 - нет
	U08		bAdcTypeF;		// Тип фильтра АЦП, 1 - PLP-15
	U16		wAdcBiasRange;	// Диапазон регулировки смещения АЦП (mV), 100
	U08		bAdcBits;		// Разрядность АЦП 16
	U16		wMaxfreqSampl;	// Максимальная частота дискретизации (MHz), 80, 100
	U16		wInpAmplRange;	// Входной амплитудный диапазон 1700 mV
	U32		nInpR;			// Входное сопротивление, 50 Ом, 75 Ом, 1МОм
	U08		isTuner;		// Тюнер, 1 - есть, 0 - нет
	U08		isSelectorSinch;// Селектор синхроимпульсов, 1 - есть, 0 - нет
	U08		bDacChanNum;	// Количество каналов ЦАП 0, 1
	U08		bDacOutNum;		// Число выходов ЦАП - 0, 1, 2
	U08		bDacTypeF;		// Тип фильтра ЦАП, 1 - PLP-15
	U16		wDacBiasRange;	// Диапазон регулировки смещения ЦАП (mV), 500
	U08		bDacBits;		// Разрядность ЦАП 14
	U16		wOutAmplRange;	// Выходной амплитудный диапазон 1100 mV
	U32		nOutR;			// Выходное сопротивление, 50 Ом, 75 Ом
	
	_ICR_Cfg0510	rPldType;	// Тип ПЛИС
} ICR_Cfg5506, *PICR_Cfg5506, ICR_CfgVK3, *PICR_CfgVK3;

#pragma pack(pop) 

#endif // _ICRVK3_H

// ****************** End of file IcrVK3.h **********************
