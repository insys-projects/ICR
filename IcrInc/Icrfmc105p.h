//****************** File icrFmc105p.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� FMC105P
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on FMC105P base modules
//
//	Copyright (c) 2012, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  15-03-12 - builded
//
//*******************************************************************

#ifndef __ICRFMC105P_H_
 #define __ICRFMC105P_H_

#pragma pack(push, 1)    

const USHORT FMC105P_CFG_TAG = 0x5509; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC105P
const USHORT FMC106P_CFG_TAG = 0x550A; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC106P
const USHORT FMC114V_CFG_TAG = 0x550C; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC114V
const USHORT FMC115�P_CFG_TAG = 0x53B1; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC115cP

// FMC105P/FMC106P modules configuration
// ���������������� ��������� ������� ������� FMC105P/FMC106P
typedef struct _ICR_CfgFmc105p {
	U16	wTag;			// ��� ��������� (FMC105P_CFG_TAG ��� FMC106P_CFG_TAG)
	U16	wSize;			// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;		// ���������� ����������� ADM
	U32	dSysGen;		// System generator in Hz (default 250 MHz)
	U08	bDdsType;		// ��� ����������� DDS (0-non, 1-above 50MHz, 2-below 50MHz)
	U08	bSwitchType;	// ��� ����������� (0-non, 1-type1(FMC105P), 2-type2(FMC106P))
	U08	bAdrSwitch;		// �������� ��� �����������: 0x48 �� ���������
	U08	bGen0Type;		// ��� ����������� ���������� 0 (0-�����������������, 1-Si571)
	U32	nRefGen0;		// ������� ���������� 0, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32	nRefMaxGen0;	// ������������ ������� �����. ���������� (��)
	U08	bAdrGen0;		// �������� ��� �����. ����������: 0x49 �� ���������
	U32	dRefGen5;		// Reference generator 5 in Hz (default 156.25 MHz)
	U32	dRefGen6;		// Reference generator 6 in Hz (default 100 MHz)
	U08	bDspNodeCfgCnt;	// ���������� ���������������� �������� ���� �������� ��������� ��������
} ICR_CfgFmc105p, *PICR_CfgFmc105p, ICR_Cfg5509, *PICR_Cfg5509;

#pragma pack(pop)    

#endif // __ICRFMC105P_H_

// ****************** End of file icrFmc105p.h **********************
