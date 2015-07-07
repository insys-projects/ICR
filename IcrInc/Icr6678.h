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
//  06-07-15 - modify (minimize)
//
//*******************************************************************
#ifndef __ICR6678_H
 #define __ICR6678_H

#pragma pack(push, 1)    

const USHORT FM408C_CFG_TAG      = 0x6608; // ��� ��� ��������� ���������������� ���������� �������� ������ FM408C
const USHORT FMC110_6678_CFG_TAG = 0x6610; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC110
const USHORT FMC112_6678_CFG_TAG = 0x6612; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC112
const USHORT FMC114_6678_CFG_TAG = 0x6614; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC114
const USHORT FMC117_6678_CFG_TAG = 0x6617; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC117
const USHORT PEX_SRIO_CFG_TAG	 = 0x6615; // ��� ��� ��������� ���������������� ���������� �������� ������ PEX-SRIO
const USHORT DSP6678PEX_CFG_TAG	 = 0x6620; // ��� ��� ��������� ���������������� ���������� �������� ������ DSP6678PEX

// 6678 module configuration
typedef struct _ICR_Cfg6678 {
	U16	wTag;			// tag of structure 0x6678
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

} ICR_Cfg6678, *PICR_Cfg6678;

#pragma pack(pop)

#endif	// __ICR6678_H

// ****************** End of file icr6678.h **********************
