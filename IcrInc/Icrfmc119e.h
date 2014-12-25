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
	
	U08 bPldType;			// ��� ����(1-XC7K325T-2FFG900�, 0-XC7K410T-2FFG900�)
	U08 bIsInternalDDR3;	// ����������� �� ���������� ������ DDR3 128x32 �����
	U08 bIsSodimDDR3;		// ����������� �� ������ DDR3 SODIM
	U08	bIsSynx;			// ���������� �� ��������� SYNX	
	U08	bIsIpass;			// ���������� �� ��������� iPASS
	U08	bIsRs;				// ���������� �� ��������� RS-232/485/422
	U08 bProgGen;			// ��������������� ���������(0-�� ����������, 1-���������� Si570)
	U08	bGenAdr;			// �������� ��� �������. ����������: 0x49 �� ���������
	U32	nGenRef;			// ��������� ��������� ������� �������. ���������� (��)
	U32	nGenRefMax;			// ������������ ������� �������. ���������� (��)
	U08 bTempRange;			// �������� ����������(0-��������������, 1-������������)	
} ICR_CfgFmc119e, *PICR_CfgFmc119e;

#pragma pack(pop)

#endif	// __ICRFMC119E_H

// ****************** End of file Icrfmc119e.h **********************
