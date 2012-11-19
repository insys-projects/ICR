//****************** File icr6678.h *******************************
//
//  Определения констант и структур 
//	для работы с конфигурационным ППЗУ
//  базового модуля на процессоре TI6678
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on TI6678 base modules
//
//	Copyright (c) 2011-2012, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers
//
//  History:
//  19-10-12 - builded
//
//*******************************************************************
#ifndef __ICR6678_H
 #define __ICR6678_H

#pragma pack(push, 1)    

const USHORT FMC110_6678_CFG_TAG = 0x6610; // тэг для структуры конфигурационных параметров базового модуля FMC110
const USHORT FMC113_6678_CFG_TAG = 0x6613; // тэг для структуры конфигурационных параметров базового модуля FMC113
const USHORT FMC114_6678_CFG_TAG = 0x6614; // тэг для структуры конфигурационных параметров базового модуля FMC114

// 6678 module configuration
// Конфигурационная структура базового модуля 6678
typedef struct _ICR_Cfg6678 {
	U16	wTag;			// tag of structure (0x6610, 0x6613 or 0x6614)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	
	U16	wDevConf;		// Device virtual BOOT mode
	U16	wCpuType;		// Тип процессора (0x6671, 0x6672, 0x6674,0x6678)

	U16	wCpuClkIn;		// CPU clock base (MHz) 
	U16	wPcieClkIn;		// PCIExpress clock base (MHz) 
	U16	wPaClkIn;		// PA clock base (MHz) 
	U16	wDDRClkIn;		// DDR clock base (MHz) 
	U16	wSRIOClkIn;		// SRIO&SGMII clock base (MHz) 
	U16	wHyperClkIn;	// HyperLink clock base (MHz) 

	U08	bIsEth0;		// есть Ethernet 0
	U08	bIsEth1;		// есть Ethernet 1
	U08	bIsSrio;		// есть SRIO
	U08	bIsHyper;		// есть HyperLink

	U08	bIsPcie;		// есть PCIExpress
	U08	bIsRS232;		// есть RS-232
	U08	bIsSpi;			// есть SPI
	U08	bIsI2c;			// есть I2C

	U32	dSizeOfDDR3;	// Размер DDR3 (MBytes), если запаян на модуле

} ICR_Cfg6678, *PICR_Cfg6678;

#pragma pack(pop)

#endif	// __ICR6678_H

// ****************** End of file icr6678.h **********************
