//****************** File Icrfmc119e.h *******************************
//
//  ќпределени€ констант и структур 
//	дл€ работы с конфигурационным ѕѕ«”
//  базового модул€ FMC119E
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  FMC118E, FMC119E, FMC128E, FMC129E base modules
//
//	Copyright (c) 2011-2012, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers

//*******************************************************************
#ifndef __ICRFMC119E_H
 #define __ICRFMC119E_H

#pragma pack(push, 1)    

const USHORT FMC118E_CFG_TAG = 0x3018; // тэг дл€ структуры конфигурационных параметров базового модул€ FMC118E
const USHORT FMC119E_CFG_TAG = 0x3019; // тэг дл€ структуры конфигурационных параметров базового модул€ FMC119E
const USHORT FMC128E_CFG_TAG = 0x3028; // тэг дл€ структуры конфигурационных параметров базового модул€ FMC128E
const USHORT FMC129E_CFG_TAG = 0x3029; // тэг дл€ структуры конфигурационных параметров базового модул€ FMC129E

// FMC119E module configuration
//  онфигурационна€ структура базового модул€ FMC119E
typedef struct _ICR_CfgFmc119e {
	U16	wTag;				// тэг структуры (FMC119E_CFG_TAG)
	U16	wSize;				// размер всех следующих полей структуры
	U08	bAdmIfCnt;			// количество интерфейсов ADM
	U32	dSysGen;			// System generator in Hz (default 100 MHz)
	U08	bDdsType;			// тип синтезатора DDS (0-non, 1-above 50MHz, 2-below 50MHz)
	U08	bSwitchType;		// тип коммутатора (0-non, 1-type4(FMC119E))
	U08	bAdrSwitch;			// адресный код коммутатора: 0x48 по умолчанию
	U08	bGen0Type;			// тип внутреннего генератора 0 (0-непрограммируемый, 1-Si571)
	U32	nRefGen0;			// частота генератора 0, если он непрограммируемый, или заводска€ частота (default 50 MHz)
	U32	nRefMaxGen0;		// максимальна€ частота внутр. генератора (√ц)
	U08	bAdrGen0;			// адресный код внутр. генератора: 0x49 по умолчанию
	U32	dMgtRefGen;			// MGT Reference generator in Hz (default 156.25 MHz)
	U08 bPldType;			// “ип ѕЋ»—:
						// 0 - XC7K410T-2FFG900 (FMC119E)
						// 1 - XC7K325T-2FFG900 (FMC119E)
						// 2 - XC7A200T-2FBG676 (FMC118E)
						// 3 - XC7A200T-2FFG1156 (FMC128E)
						// 4 Ц XCKU035-2FFVA1156 (FMC129E)
						// 5 Ц XCKU040-2FFVA1156 (FMC129E)
						// 6 Ц XCKU060-2FFVA1156 (FMC129E)
	U08 bIsSodimDDR3;		// ”становлена ли пам€ть DDR3 SODIM
	U08 bIsInternalDDR3;	// ”становлена ли встроенна€ пам€ть DDR3 128x32 ћслов
	U08	bIsSynx;			// ”становлен ли интерфейс SYNX	
	U08	bIsIpass;			// ”становлен ли интерфейс iPASS
	U08	bIsRs;			// ”становлен ли интерфейс RS-232 или SFP:
						// 0 Ц нет, 
						// 1 Ц RS-232 (FMC119E)
						// 2 Ц SFP (FMC128E, FMC129E)
	U08 bTempRange;			// ƒиапазон температур: (0-индустриальный, 1-коммерческий)	
} ICR_CfgFmc119e, *PICR_CfgFmc119e;

#pragma pack(pop)

#endif	// __ICRFMC119E_H

// ****************** End of file Icrfmc119e.h **********************
