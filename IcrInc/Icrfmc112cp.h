//****************** File icrFmc112cp.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� FMC112cP
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on FMC112cP base modules
//
//	Copyright (c) 2014, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  06-06-14 - builded
//
//*******************************************************************

#ifndef __ICRFMC112CP_H_
 #define __ICRFMC112CP_H_

#pragma pack(push, 1)    

const USHORT FMC112CP_CFG_TAG = 0x53B2; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC112cP

// FMC112cP modules configuration
// ���������������� ��������� ������� ������� FMC112cP
typedef struct _ICR_CfgFmc112cp {
	U16	wTag;			// ��� ��������� (FMC112CP_CFG_TAG)
	U16	wSize;			// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;		// ���������� ����������� ADM
	U32	dSysGen;		// System generator in Hz (default 250 MHz)
	U08	bDdsType;		// ��� ����������� DDS (0-non, 1-above 50MHz, 2-below 50MHz)
	U08	bSwitchType;	// ��� ����������� (0-non, 1-type3(FMC112cP))
	U08	bAdrSwitch;		// �������� ��� �����������: 0x48 �� ���������
	U08	bGen0Type;		// ��� ����������� ���������� 0 (0-�����������������, 1-Si571)
	U32	nRefGen0;		// ������� ���������� 0, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32	nRefMaxGen0;	// ������������ ������� �����. ���������� (��)
	U08	bAdrGen0;		// �������� ��� �����. ����������: 0x49 �� ���������
	U32	dRefGen5;		// MGT Reference generator 5 in Hz (default 156.25 MHz)
	U32	dRefGen6;		// Reference generator 6 in Hz (default 100 MHz)
	U08	bDspNodeCfgCnt;	// ���������� ���������������� �������� ���� �������� ��������� ��������
	U08	isDDR3;			// ������� ������ DDR3
} ICR_CfgFmc112cp, *PICR_CfgFmc112cp, ICR_Cfg53B2, *PICR_Cfg53B2;

#pragma pack(pop)    

#endif // __ICRFMC112CP_H_

// ****************** End of file icrFmc112cp.h **********************
