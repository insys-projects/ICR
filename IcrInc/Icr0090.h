//****************** File Icr0090.h ***********************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  для субмодулей ADM212x500(WB), ADM214x400M(WB)
//
//*********************************************************

#ifndef _ICR0090_H
 #define _ICR0090_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0090

// Конфигурационные параметры субмодуля
typedef struct _ICR_Cfg0090 {
	U16	wTag;		// тэг структуры (ADM_CFG_TAG)
	U16	wSize;		// размер всех следующих полей структуры
	U08	bAdmIfNum;	// номер интерфейса ADM
	U08	bAdcCnt;	// количество АЦП
	U08	bSubType;	// тип субмодуля: 0-Standard, 1 -WB HF, 2-WB LF 
	U32	anRefGen[2];// опорные генераторы 0 и 1 (Гц)
	U16 awRange[4];	// шкалы преобразования для Standard (мВ) (default 10000, 2000, 500, 100)
	U16	awRangeDeviation0[4]; // отклонение ШП от номинала для АЦП0 (разы) (default 10000)
	U16	awRangeDeviation1[4]; // отклонение ШП от номинала для АЦП1 (разы) (default 10000)
	U16 awRelativeBias0[4];// относительное смещение нуля для АЦП0 (разы) (default 0)
	U16 awRelativeBias1[4];// относительное смещение нуля для АЦП1 (разы) (default 0)
} ICR_Cfg0090, *PICR_Cfg0090, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0090_H

// ****************** End of file Icr0090.h **********************
