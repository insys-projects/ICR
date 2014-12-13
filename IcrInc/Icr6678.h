//****************** File icr6678.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ �� ���������� TI6678
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

const USHORT FMC110_6678_CFG_TAG = 0x6610; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC110
const USHORT FMC112_6678_CFG_TAG = 0x6612; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC112
const USHORT FMC114_6678_CFG_TAG = 0x6614; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC114
const USHORT FMC117_6678_CFG_TAG = 0x6617; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC117
const USHORT PEX_SRIO_CFG_TAG	 = 0x6615; // ��� ��� ��������� ���������������� ���������� �������� ������ PEX-SRIO

// 6678 module configuration
// ���������������� ��������� �������� ������ 6678
typedef struct _ICR_Cfg6678 {
	U16	wTag;			// tag of structure (0x6610, 0x6613 or 0x6614)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	
	U16	wDevConf;		// Device virtual BOOT mode
	U16	wCpuType;		// ��� ���������� (0x6671, 0x6672, 0x6674,0x6678)

	U32	wCpuClkIn;		// CPU clock base (MHz) 
	U32	wPcieClkIn;		// PCIExpress clock base (MHz) 
	U32	wPaClkIn;		// PA clock base (MHz) 
	U32	wDDRClkIn;		// DDR clock base (MHz) 
	U32	wSRIOClkIn;		// SRIO&SGMII clock base (MHz) 
	U32	wHyperClkIn;	// HyperLink clock base (MHz) 

	U08	bIsEth0;		// ���� Ethernet 0
	U08	bIsEth1;		// ���� Ethernet 1
	U08	bIsSrio;		// ���� SRIO
	U08	bIsHyper;		// ���� HyperLink

	U08	bIsPcie;		// ���� PCIExpress
	U08	bIsRS232;		// ���� RS-232
	U08	bIsSpi;			// ���� SPI
	U08	bIsI2c;			// ���� I2C

	U32	dSizeOfDDR3;	// ������ DDR3 (MBytes), ���� ������ �� ������

	U08	bOrder;			// CHIP number on Board
	U08	bIsNand;		// is NAND FLASH CHIP
	U08	bIsSmartLed;	// is LED 7-segment Indicator
	U08	bRsv;			// reserved

} ICR_Cfg6678, *PICR_Cfg6678;

#pragma pack(pop)

#endif	// __ICR6678_H

// ****************** End of file icr6678.h **********************
