//****************** File Icr008F.h ***********************
//
//  ќпределени€ констант и структур 
//	дл€ работы с конфигурационным ѕѕ«”
//  дл€ субмодулей ADMDAC216x400M
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

//  онфигурационные параметры субмодул€
typedef struct _ICR_Cfg008F {
	USHORT	wTag;		// тэг структуры (ADM_CFG_TAG)
	USHORT	wSize;		// размер всех следующих полей структуры
	UCHAR	bAdmIfNum;	// номер интерфейса ADM
	ULONG	dGen;		// значение опорного генератора
	UCHAR	bFreqTune;	// подстройка частоты встроенного опорного генератора
	UCHAR	bDacCnt;	// количество ÷јѕ
	ULONG	dLPFCutoff;	// частота среза фильтра низких частот (√ц)
	UCHAR	bOutResist;	// выходное сопротивление (0 - 50 ќм, 1 - 75 ќм)
	ULONG	dOscFreq;	// частота √”Ќ (√ц) (по умолч. 400 ћ√ц)
	UCHAR	bOutCasMod;	// модификаци€ выходного каскада 0 - LF, 1 - HF
	UCHAR	bQuadModType;// тип квадратурного модул€тора ( 0 - нет, 1 Ц AD8345, 2 Ц AD8346, 3 Ц AD8349 )
	UCHAR	bIsExtClk;	// наличие входа внешнего тактировани€
} ICR_Cfg008F, *PICR_Cfg008F, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008F_H

// ****************** End of file Icr008F.h **********************
