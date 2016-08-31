//****************** File icrFmc127p.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� FMC127P
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on FMC105P base modules
//
//	Copyright (c) 2015, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  27-11-15 - builded
//
//*******************************************************************

#ifndef __ICRFMC127P_H_
 #define __ICRFMC127P_H_

#pragma pack(push, 1)    

const USHORT FMC127P_CFG_TAG = 0x551F; // ��� ��� ��������� ���������������� ���������� �������� ������ FMC127P

// FMC127P module configuration
// ���������������� ��������� �������� ������ FMC127P
typedef struct _ICR_CfgFmc127p {
	U16	wTag;			// ��� ��������� (FMC127P_CFG_TAG)
	U16	wSize;			// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;		// ���������� ����������� ADM
	U32	dSysGen;		// System generator in Hz (default 250 MHz)
	U08	bDdsType;		// ��� ����������� DDS (0-non) - ���� ������������ ��� �������������
	U08	bSwitchType;	// ��� ����������� (0-non, 1-type6(FMC127P))
	U08	bAdrSwitch;		// �������� ��� �����������: ����������� (���� ������������ ��� �������������)
	U08	bGen0Type;		// ��� ����������� ���������� 0 (0-�����������������, 1-Si570)
	U32	nRefGen0;		// ������� ���������� 0, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32	nRefMaxGen0;	// ������������ ������� �����. ���������� (��)
	U08	bAdrGen0;		// �������� ��� �����. ����������: 0x49 �� ���������
	U08 bIsFMC2;		// ���������� �� ���� FMC2
	U08	bIsSynx2;		// ���������� �� ��������� SYNX2	
	U08	bIsUserEEPROM;	// ����������� �� ���������������� ����
	U08	bIsPowerCtrl;	// ���������� �� ���������� �������
	U08	bAdrPower;		// �������� ��� ����������� �������: 0x48 �� ���������
	U08 bIsInternalDDR3;	// ����������� �� ���������� ������ DDR3 128x32 �����
} ICR_CfgFmc127p, *PICR_CfgFmc127p, ICR_Cfg551F, *PICR_Cfg551F;

#pragma pack(pop)    

#endif // __ICRFMC127P_H_

// ****************** End of file icrFmc127p.h **********************
