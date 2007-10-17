//****************** File Icr008F.h ***********************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  для субмодулей ADMDAC216x400M
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
	ULONG	dPllRefGen;	// опорный генератор для ФАПЧ in Hz (default 10 MHz)
	ULONG	dPllFreq;	// частота, выдаваемая ФАПЧ in Hz (default 400 MHz)
	UCHAR	bDacCnt;	// количество ЦАП
} ICR_Cfg008F, *PICR_Cfg008F, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008F_H

// ****************** End of file Icr008F.h **********************
