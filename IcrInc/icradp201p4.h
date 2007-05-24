//****************** File icrAdp201P4.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ ADP201P4
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on ADP201P4 base module
//
//	Copyright (c) 2003-2005, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers
//
//  History:
//  07-11-05 - builded
//
//*******************************************************************
#ifndef __ICRADP201P4_H
 #define __ICRADP201P4_H

#pragma pack(push, 1)    

const USHORT Adp201P4_CFG_TAG = 0x5086; // ��� ��� ��������� ���������������� ���������� �������� ������ ADP201P4

// ADP201P4 module configuration
// ���������������� ��������� �������� ������ ADP201P4
typedef struct _ICR_Cfg5086 {
	U16	wTag;			// tag of structure (0x5086)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ����� ����������� ADM = 1
	U16	wMaxCpuClock;	// CPU clock (MHz) - 500 or 600
	U32	dBusClock;		// Bus clock (edited - default 100000000 Hz)
	U32	dSizeOfSDRAM;	// ������ SDRAM � ������ 0, 64Mb, 128Mb, 256Mb
	U08	bHostPldCnt;	// Host PLD counter
	U16	wSDRCON;		// init value for SDRAM  (edited)
	U16	wCpuMask;		// ����� ������� ����������� (������� ���� ������� � P1 -
						// P4 P3 P2 P1, 0 - ���, 1 - ����)
	U16	wSdramMask;		// ����� ������� ������ � ����������� (������� ���� ������� � P1 - 
						// P4 P3 P2 P1, 0 - ���, 1 - ����)
	U08	wSDRAM_RAS;		// SDRAM parameter RAS
	U08	wSDRAM_CAS;		// SDRAM parameter CAS
	U08	wSDRAM_BANK;	// SDRAM parameter BANK
	U08	wSDRAM_CL;		// SDRAM parameter CL

} ICR_Cfg5086, *PICR_Cfg5086, ICR_CfgAdp201P4, *PICR_CfgAdp201P4;

#pragma pack(pop)

#endif	// __ICRADP201P4_H

// ****************** End of file icrAdp201P4.h **********************
