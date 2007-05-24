//****************** File icrAdp101cp1.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ ADP101cP1 
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on ADP101cP1 base module
//
//	Copyright (c) 2002-2003, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers
//
//  History:
//  28-08-03 - builded
//  10-09-03 - modified
//
//*******************************************************************
#ifndef __ICRADP101cP1_H
 #define __ICRADP101cP1_H

#pragma pack(push, 1)    

const USHORT Adp101cP1_CFG_TAG = 0x5367; // ��� ��� ��������� ���������������� ���������� �������� ������ ADP101cP1

// ADP101cP1 module configuration
// ���������������� ��������� �������� ������ ADP101cP1
typedef struct _ICR_Cfg5367 {
	U16	wTag;		// tag of structure (0x5367)
	U16	wSize;		// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;	// ADM counter ADM = 1
	U16	wMaxCpuClock;	// CPU clock (MHz) - 250 or 300
	U32	dBusClock;	// Bus clock (edited - default 100000000 Hz)
	U32	dSizeOfSDRAM;// ������ SDRAM � ������ 0, 64Mb, 128Mb, 256Mb
	U08	bHostPldCnt;// Host PLD counter
} ICR_Cfg5367, *PICR_Cfg5367, ICR_CfgAdp101cP1, *PICR_CfgAdp101cP1;

#pragma pack(pop)    

#endif	// __ICRADP101cP1_H

// ****************** End of file icrAdp101cp1.h **********************
