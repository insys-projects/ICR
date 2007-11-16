//****************** File icrAds3224k195cPci.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ Adp101cPci 
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on Adp101cPci base module
//
//	Copyright (c) 2004, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers
//
//  History:
//  3-12-04 - builded
//
//*******************************************************************
#ifndef __ICRAdp101cPci_H
 #define __ICRAdp101cPci_H

#pragma pack(push, 1)    

const USHORT Adp101cPci_CFG_TAG = 0x5367; // ��� ��� ��������� ���������������� ���������� �������� ������ Adp101cPci

// Adp101cPci module configuration
// ���������������� ��������� �������� ������ Adp101cPci
typedef struct _ICR_Cfg5367 {
	U16	wTag;			// tag of structure (0x5367)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ����� ����������� ADM = 1
	U16	wMaxCpuClock;		// CPU clock (MHz) - 250 or 300
	U32	dBusClock;		// Bus clock (edited - default 100000000 Hz)
	U32	dSizeOfSDRAM;		// ������ SDRAM � ������ 0, 64Mb, 128Mb
	U08	bHostPldCnt;		// Host PLD counter
	U16	wSDRCON;		// init value for SDRAM  (edited)
} ICR_Cfg5367, *PICR_Cfg5367, ICR_CfgAdp101cPci, *PICR_CfgAdp101cPci;

#pragma pack(pop)

#endif	// __ICRAdp101cPci_H

// ****************** End of file icrAdp101cPci.h **********************
