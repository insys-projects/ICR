//****************** File icrFmc124p.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� FMC124P
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on FMC124P base modules
//
//	Copyright (c) 2015, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  28-07-15 - builded
//
//*******************************************************************

#ifndef __ICRFMC124P_H_
 #define __ICRFMC124P_H_

#pragma pack(push, 1)    

const USHORT FMC124P_CFG_TAG = 0x551E; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC124P

// FMC124P module configuration
// ���������������� ��������� �������� ������ FMC124P
typedef struct _ICR_CfgFmc124p {
	U16	wTag;				// ��� ��������� (FMC124P_CFG_TAG)
	U16	wSize;				// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;			// ���������� ����������� ADM
	U32	dSysGen;			// System generator in Hz (default 250 MHz)
	U08	bDdsType;			// ��� ����������� DDS (0-non, 1-above 50MHz, 2-below 50MHz)
	U08	bSwitchType;		// ��� ����������� (0-non, 1-type5(FMC124P))
	U08	bAdrSwitch;			// �������� ��� �����������: 0x48 �� ���������
	U32	dRefGenDDS;			// Reference generator for DDS (default 19.2 MHz)
	U08	bTermGenDDS;		// temperature-compensated generator for DDS (0 - non temperature-compensated)
	U32	dRefGen100M;		// Reference generator 6 in Hz (default 100 MHz)
	U08 bIsSodimDDR3;		// ����������� �� ������ DDR3 SODIM
	U08 bIsInternalDDR3;	// ����������� �� ���������� ������ DDR3 256x32 �����
} ICR_CfgFmc124p, *PICR_CfgFmc124p, ICR_Cfg551E, *PICR_Cfg551E;

#pragma pack(pop)    

#endif // __ICRFMC124P_H_

// ****************** End of file icrFmc124p.h **********************
