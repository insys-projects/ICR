//****************** File icrAmbpex5.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� AMBPEX5
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on AMBPEX5 base modules
//
//	Copyright (c) 2010, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  07-04-10 - builded
//
//*******************************************************************

#ifndef __ICRAMBPEX5_H_
 #define __ICRAMBPEX5_H_

#pragma pack(push, 1)    

const USHORT AMBPEX5_CFG_TAG = 0x5507; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBPEX8

// AMBPEX5/FMC105P modules configuration
// ���������������� ��������� ������� ������� AMBPEX5/FMC105P
typedef struct _ICR_CfgAmbpex5 {
	USHORT	wTag;			// ��� ��������� (AMBPEX5_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfCnt;		// ���������� ����������� ADM
	ULONG	dSysGen;		// System generator in Hz (default 250 MHz)
	UCHAR	bDdsType;		// type of DDS (0-non, 1-PLL, 2-DDS)
	UCHAR	bSramCfgCnt;	// ���������� ���������������� �������� ����������� ������ SRAM
	ULONG	dRefGen5;		// Reference generator 5 in Hz (default 156.25 MHz)
	UCHAR	bSPFCnt;		// ���������� ������������� SPF �������
} ICR_CfgAmbpex5, *PICR_CfgAmbpex5, ICR_Cfg5507, *PICR_Cfg5507;

#pragma pack(pop)    

#endif // __ICRAMBPEX5_H_

// ****************** End of file icrAmbpex5.h **********************
