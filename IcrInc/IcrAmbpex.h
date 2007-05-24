//****************** File icrAmbpex.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� AMBPEX1/AMBPEX8
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on AMBPEX1/AMBPEX8 base modules
//
//	Copyright (c) 2007, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  26-03-07 - builded
//
//*******************************************************************

#ifndef __ICRAMBPEX_H_
 #define __ICRAMBPEX_H_

#pragma pack(push, 1)    

const USHORT AMBPEX1_CFG_TAG = 0x5502; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBPEX1
const USHORT AMBPEX8_CFG_TAG = 0x5503; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBPEX8

// AMBPEX1/AMBPEX8 modules configuration
// ���������������� ��������� ������� ������� AMBPEX1/AMBPEX8
typedef struct _ICR_CfgAmbpex {
	USHORT	wTag;			// ��� ��������� (AMBPEX1_CFG_TAG ��� AMBPEX8_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfCnt;		// ���������� ����������� ADM
	ULONG	dSysGen;		// System generator in Hz (default 66 MHz)
	UCHAR	bDdsType;		// type of DDS (0-non, 1-PLL, 2-DDS)
	UCHAR	bSramCfgCnt;	// ���������� ���������������� �������� ����������� ������ SRAM
//	UCHAR	bSdramSlotCnt;	// ���������� ������������� ������ ������������ ������
//	UCHAR	bSdramCfgCnt;	// ���������� ���������������� �������� ������������ ������
//	UCHAR	bDspNodeCfgCnt;	// ���������� ���������������� �������� ���� �������� ��������� ��������
} ICR_CfgAmbpex, *PICR_CfgAmbpex, ICR_Cfg5502, *PICR_Cfg5502, ICR_Cfg5503, *PICR_Cfg5503;

#pragma pack(pop)    

#endif // __ICRAMBPEX_H_

// ****************** End of file icrAmbpex.h **********************
