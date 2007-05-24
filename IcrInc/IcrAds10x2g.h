//****************** File icrAds10x2g.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ADS10X2G
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on ADS10X2G modules
//
//	Copyright (c) 2005, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  17-06-05 - builded
//  15-03-06 - add PllRefGen - by ver. 2.0
//  16-03-06 - add PllFreq - by ver. 2.0
//
//*******************************************************************

#ifndef __ICRADS10X2G_H_
 #define __ICRADS10X2G_H_

#pragma pack(push, 1)    

const USHORT ADS10X2G_CFG_TAG = 0x1020; // ��� ��� ��������� ���������������� ���������� �������� ������ ADS10X2G

// ADS10X2G modules configuration
// ���������������� ��������� ������� ������� ADS10X2G
typedef struct _ICR_CfgAds10x2g {
	USHORT	wTag;			// ��� ��������� (ADS10X2G_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfCnt;		// ���������� ����������� ADM
	ULONG	dSysGen;		// System generator in Hz (default 66 MHz)
	UCHAR	bAdcCnt;		// ���������� ���������������� �������� ���
	UCHAR	bSdramCfgCnt;	// ���������� ���������������� �������� ������������ ������
	ULONG	dPllRefGen;		// PLL reference generator in Hz (default 40 MHz) - ver. 2.0 only !!!
	ULONG	dPllFreq;		// �������, ���������� ���� in Hz (default 2 GHz) - ver. 2.0 only !!!
} ICR_CfgAds10x2g, *PICR_CfgAds10x2g, ICR_Cfg1020, *PICR_Cfg1020;

#pragma pack(pop)    

#endif // __ICRADS10X2G_H_

// ****************** End of file icrAds10x2g.h **********************
