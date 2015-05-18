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
	U16	wTag;			// tag of structure (0x6610, 0x6612 ...)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	
	U08	bCpuCnt;		// ����� ����������� �� ������
	U08	bCpuType;		// ��� ���������� (0x71, 0x72, 0x74, 0x78)
	U08	bOrder;			// ����� ���������� (0, 1 � �.�.)
	U08	bFpgaCnt;		// ������� FPGA �� ������

	U32	dCpuClkIn;		// CPU clock base (Hz) 
	U32	dPcieClkIn;		// PCIExpress clock base (Hz) 
	U32	dPaClkIn;		// PA clock base (Hz) 
	U32	dDDR3ClkIn;		// DDR clock base (Hz) 
	U32	dSRIOClkIn;		// SRIO&SGMII clock base (Hz) 
	U32	dHyperClkIn;	// HyperLink clock base (Hz) 

	U08	bIsEth0;		// ���� Ethernet 0 (0 ��� 1)
	U08	bIsEth1;		// ���� Ethernet 1 (0 ��� 1)
	U08	bIsHyper;		// ���� HyperLink (0 ��� 1) 
	U08	bIsPcie;		// ���� PCIExpress (0 ��� 1)
	U08	bIsSpi;			// ���� SPI (0 ��� 1)
	U08	bIsI2c;			// ���� I2C (0 ��� 1)
	U08	bIsSrio;		// ���� SRIO (14 - 1x4, 22 - 2x2, 41 - 4x1)
	U08	bIsRS232;		// ���� RS-232 (32 - 232, 22 - 422, 85 - 485)

	U32	dGpioLed;		// ������� ����� GPIO, ������� ���������� � LED (��� 0x77777777 - smart led)

	U32	dNandSize;		// ������ FLASH ������ ���� NAND (EMIF16)
	U32	dNorSize;		// ������ FLASH ������ ���� NOR (SPI)
	U32	dSizeOfDDR3;	// ������ DDR3 (32-������ �����), ���� ������ �� ������

    // LEVELING ��� ������ DDR3
	U16 wWrLev0;
	U16 wWrLev1;
	U16 wWrLev2;
	U16 wWrLev3;
	U16 wWrLev4;
	U16 wWrLev5;
	U16 wWrLev6;
	U16 wWrLev7;
	U16 wWrLev8;

	U16 wGtLev0;
	U16 wGtLev1;
	U16 wGtLev2;
	U16 wGtLev3;
	U16 wGtLev4;
	U16 wGtLev5;
	U16 wGtLev6;
	U16 wGtLev7;
	U16 wGtLev8;

	// ��������� ��������� DDR3
	U08	bT_RP;
	U08	bT_RCD;
	U08	bT_WR;
	U08	bT_RAS;
	U08	bT_RC;
	U08	bT_RRD;
	U08	bT_WTR;
	U08	bT_RTP;
	U08	bT_RFC;

	// ������ ��������� DDR3
	U08	bCL;
	U08	bROWSIZE;
	U08	bRANK;
	U08	bPSIZE;

	// frequence multipliers and dividers
	U08 bMainPllMult;   
    U08 bMainPllDiv;	

	U08	bDdr3PllMul;
	U08	bDdr3PllDiv;

	U08 bNetPllMult;   
    U08 bNetPllDiv;	

	// Network parameters
    U16 wNet0AdviseAbility;
    U16 wNet0AuxConfig;
    U16 wNet1AdviseAbility;
    U16 wNet1AuxConfig;


} ICR_Cfg6678, *PICR_Cfg6678;

#pragma pack(pop)

#endif	// __ICR6678_H

// ****************** End of file icr6678.h **********************
