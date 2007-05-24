//****************** File icrDsp101cP10.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ DSP101cP10 
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on DSP101cP10 base module
//
//	Copyright (c) 2003, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers
//
//  History:
//  25-09-03 - builded
//  30-09-03 - modified
//
//*******************************************************************
#ifndef __ICRDSP101cP10_H
 #define __ICRDSP101cP10_H

#pragma pack(push, 1)    

const USHORT DSP101cP10_CFG_TAG = 0x5365; // ��� ��� ��������� ���������������� ���������� �������� ������ DSP101cP10

// DSP101cP10 module configuration
// ���������������� ��������� �������� ������ DSP101cP10
typedef struct _ICR_Cfg5365 {
	U16	wTag;			// tag of structure (0x5365)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ����� ����������� ADM = 0
	U16	wMaxCpuClock;	// CPU clock (MHz) - 250 or 300
	U32	dBusClock;		// Bus clock (edited - default 100000000 Hz)
	U32	dSizeOfSDRAM;	// ������ SDRAM � ������ 0, 64Mb, 128Mb
	U08	bHostPldCnt;	// Host PLD counter
	U08	bDioPldCnt;		// Dio PLD counter
	U16	wSDRCON;		// init value for SDRAM  (edited)
	U08	bTypeOfLinks;	// External Links type (0 - TTL, 1 - LVDS)
	U16	wCpuMask;		// ����� ������� ����������� (������� ���� ������� � �������� -
						// P0 A0 A1 A2 B0 B1 B2 C0 C1 C2, 0 - ���, 1 - ����)
	U16	wSdramMask;		// ����� ������� ������ � ����������� (������� ���� ������� � �������� - 
						// P0 A0 A1 A2 B0 B1 B2 C0 C1 C2, 0 - ���, 1 - ����)
	U16	wLinksJ4Mask;	// ����� ������� � ����������� ������ �� J4 (������� ���� ������� � ������� - 
						// A0 A1 A2 B0 B1 B2 C0 C1 C2, 0 - ���, 1 - ����)
} ICR_Cfg5365, *PICR_Cfg5365, ICR_CfgDSP101cP10, *PICR_CfgDSP101cP10;

#pragma pack(pop)

#endif	// __ICRDSP101cP10_H

// ****************** End of file icrDsp101cP10.h **********************
