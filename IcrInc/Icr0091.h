//****************** File Icr0091.h ***********************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  для субмодулей ADM210x1G
//
//*********************************************************

#ifndef _ICR0091_H
 #define _ICR0091_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0091

// Конфигурационные параметры субмодуля
typedef struct _ICR_Cfg0091 {
	U16	wTag;		// тэг структуры (ADM_CFG_TAG)
	U16	wSize;		// размер всех следующих полей структуры
	U08	bAdmIfNum;	// номер интерфейса ADM
	U08	bAdcCnt;	// количество АЦП
	U08	bSubType;	// тип субмодуля: 0-Standard, 1 -WB HF, 2-WB LF 
	U32	nRefGen0;             // опорный генератор 0 (Гц)
	U32	nRefGen1;             // опорный генератор 1 (Гц)
	U32	nRefGen1Min;          // опорный генератор 1 (Гц)
	U32	nRefGen1Max;          // опорный генератор 1 (Гц)
	U08	nRefGen1Type;         // тип опорного генератора 1
	U32	nRefGen2;             // опорный генератор 2 (Гц)
	U08	nRefGen2Type;         // тип опорного генератора 2
	U08	nReserve0;            // резерв
	U32	nLpfPassBand;         // частота среза ФНЧ (Гц)
	U16 awRange[4];	          // шкалы преобразования для Standard (мВ) (default 10000, 2000, 500, 100)
	U16	awRangeDeviation0[4]; // отклонение ШП от номинала для АЦП0 (разы) (default 10000)
	U16	awRangeDeviation1[4]; // отклонение ШП от номинала для АЦП1 (разы) (default 10000)
	U16 awRelativeBias0[4];   // относительное смещение нуля для АЦП0 (разы) (default 0)
	U16 awRelativeBias1[4];   // относительное смещение нуля для АЦП1 (разы) (default 0)
} ICR_Cfg0091, *PICR_Cfg0091, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0091_H

// ****************** End of file Icr0091.h **********************
