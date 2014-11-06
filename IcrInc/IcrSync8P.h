//****************** File IcrSync8P.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� Sync8P
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on Sync8P modules
//
//	Copyright (c) 2014, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  31-10-14 - builded
//
//*******************************************************************

#ifndef __ICRSYNC8P_H_
 #define __ICRSYNC8P_H_

#pragma pack(push, 1)

const USHORT SYNC8P_CFG_TAG = 0x551B; // ��� ��� ��������� ���������������� ���������� ������ SYNC8P

// SYNC8P modules configuration
// ���������������� ��������� ������� SYNC8P
typedef struct _ICR_CfgSync8P {
	U16		wTag;			// ��� ��������� (SYNC8P_CFG_TAG)
	U16		wSize;			// ������ ���� ��������� ����� ���������
	U08		bAdmIfCnt;		// ���������� ����������� ADM
	U32		dSysGen;		// System generator in Hz (default 66 MHz)
	U32		dGen1;			// ������� ���������� 1, ���� �� �����������������, ��� ��������� ������� Si571 (default 50 MHz)
	U32		dGen2;			// generator 2 in Hz (default 0 MHz)
	U32		dOcxoGen;		// OCXO generator in Hz (default 0 MHz)
	U32		dPllFreq;		// �������, ���������� ���� in Hz (default 0 GHz)
	U08		bClkChanCnt;	// ���������� �������� ������� ������������ (default 4)
	U08		bStrbChanCnt;	// ���������� �������� ������� c������������ (default 4)
	U08		bIsClkE;		// ������� ��������������� ������ CLKE
	U08		bIsClkF;		// ������� ��������������� ������ CLKF
	U08		bIsStrbA;		// ������� ��������������� ������ STROA
	U08		bIsStrbB;		// ������� ��������������� ������ STROB
	U08		bIsStrbD;		// ������� ��������������� ������ STROD
	U08		bIsSync;		// ������� �������������� �������� ������������ �������������
	U08		bIsLF;			// �������� ������ �������� �������� ������������: 1 - LF (0.1-400 ���), 0 - HF(5-2500 ���)
	U08		bGen1Type;		// ��� ����������� ���������� 1 (0-�����������������, 1-Si571)
	//U32		nRefGen1;		// ������� ���������� 1, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32		nRefMaxGen1;	// ������������ ������� ���������� 1 (��)
	U08		bAdrGen1;		// �������� ���  ���������� 1: 0x49 �� ���������
	U08		bGenPllType;	// ��� ����������� ���������� ��� (0-�����������������, 1-Si571)
	U32		nRefGenPll;		// ������� ���������� ���, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32		nRefMinGenPll;	// ����������� ������� ���������� ��� (��)
	U32		nRefMaxGenPll;	// ������������ ������� ���������� ��� (��)
	U08		bAdrGenPll;		// �������� ��� ��� ����������: 0x49 �� ���������
} ICR_CfgSync8P, *PICR_CfgSync8P, ICR_Cfg551B, *PICR_Cfg551B;

#pragma pack(pop)    

#endif // __ICRSYNC8P_H_

// ****************** End of file IcrSync8P.h **********************
