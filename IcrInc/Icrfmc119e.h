//****************** File Icrfmc119e.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ FMC119E
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  FMC119E base modules
//
//	Copyright (c) 2011-2012, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers

//*******************************************************************
#ifndef __ICRFMC119E_H
 #define __ICRFMC119E_H

#pragma pack(push, 1)    

const USHORT FMC119E_CFG_TAG = 0x3019; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC119E

// FMC119E module configuration
// ���������������� ��������� �������� ������ FMC119E
typedef struct _ICR_CfgFmc119e {
	U16	wTag;				// ��� ��������� (FMC119E_CFG_TAG)
	U16	wSize;				// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;			// ���������� ����������� ADM
	U32	dSysGen;			// System generator in Hz (default 100 MHz)
	U08	bDdsType;			// ��� ����������� DDS (0-non, 1-above 50MHz, 2-below 50MHz)
	U08	bSwitchType;		// ��� ����������� (0-non, 1-type4(FMC119E))
	U08	bAdrSwitch;			// �������� ��� �����������: 0x48 �� ���������
	U08	bGen0Type;			// ��� ����������� ���������� 0 (0-�����������������, 1-Si571)
	U32	nRefGen0;			// ������� ���������� 0, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32	nRefMaxGen0;		// ������������ ������� �����. ���������� (��)
	U08	bAdrGen0;			// �������� ��� �����. ����������: 0x49 �� ���������
	U32	dMgtRefGen;			// MGT Reference generator in Hz (default 156.25 MHz)
	U08 bPldType;			// ��� ����(1-XC7K325T-2FFG900�, 0-XC7K410T-2FFG900�)
	U08 bIsSodimDDR3;		// ����������� �� ������ DDR3 SODIM
	U08 bIsInternalDDR3;	// ����������� �� ���������� ������ DDR3 128x32 �����
	U08	bIsSynx;			// ���������� �� ��������� SYNX	
	U08	bIsIpass;			// ���������� �� ��������� iPASS
	U08	bIsRs;				// ���������� �� ��������� RS-232/485/422
	U08 bTempRange;			// �������� ����������(0-��������������, 1-������������)	
} ICR_CfgFmc119e, *PICR_CfgFmc119e;

#pragma pack(pop)

#endif	// __ICRFMC119E_H

// ****************** End of file Icrfmc119e.h **********************
