//****************** File Icrfmc119e.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ FMC119E
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  FMC118E, FMC119E, FMC128E, FMC129E base modules
//
//	Copyright (c) 2011-2012, Instrumental Systems,Corp.
//	Written by Dorokhin Brothers

//*******************************************************************
#ifndef __ICRFMC119E_H
 #define __ICRFMC119E_H

#pragma pack(push, 1)    

const USHORT FMC118E_CFG_TAG = 0x3018; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC118E
const USHORT FMC119E_CFG_TAG = 0x3019; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC119E
const USHORT FMC128E_CFG_TAG = 0x3028; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC128E
const USHORT FMC129E_CFG_TAG = 0x3029; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC129E

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
	U08 bPldType;			// ��� ����:
						// 0 - XC7K410T-2FFG900 (FMC119E)
						// 1 - XC7K325T-2FFG900 (FMC119E)
						// 2 - XC7A200T-2FBG676 (FMC118E)
						// 3 - XC7A200T-2FFG1156 (FMC128E)
						// 4 � XCKU035-2FFVA1156 (FMC129E)
						// 5 � XCKU040-2FFVA1156 (FMC129E)
						// 6 � XCKU060-2FFVA1156 (FMC129E)
	U08 bIsSodimDDR3;		// ����������� �� ������ DDR3 SODIM
	U08 bIsInternalDDR3;	// ����������� �� ���������� ������ DDR3 128x32 �����
	U08	bIsSynx;			// ���������� �� ��������� SYNX	
	U08	bIsIpass;			// ���������� �� ��������� iPASS
	U08	bIsRs;			// ���������� �� ��������� RS-232 ��� SFP:
						// 0 � ���, 
						// 1 � RS-232 (FMC119E)
						// 2 � SFP (FMC128E, FMC129E)
	U08 bTempRange;			// �������� ����������: (0-��������������, 1-������������)	
} ICR_CfgFmc119e, *PICR_CfgFmc119e;

#pragma pack(pop)

#endif	// __ICRFMC119E_H

// ****************** End of file Icrfmc119e.h **********************
