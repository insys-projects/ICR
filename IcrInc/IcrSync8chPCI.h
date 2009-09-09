//****************** File IcrSync8chPCI.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� Sync8chPCI
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on Sync8chPCI modules
//
//	Copyright (c) 2009, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  02-04-09 - builded
//
//*******************************************************************

#ifndef __ICRSYNC8CHPCI_H_
 #define __ICRSYNC8CHPCI_H_

#pragma pack(push, 1)    

const USHORT SYNC8CHPCI_CFG_TAG = 0x50A2; // ��� ��� ��������� ���������������� ���������� ������ SYNC8CHPCI

// SYNC8CHPCI modules configuration
// ���������������� ��������� ������� SYNC8CHPCI
typedef struct _ICR_CfgSync8chPCI {
	USHORT	wTag;			// ��� ��������� (SYNC8CHPCI_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfCnt;		// ���������� ����������� ADM
	ULONG	dSysGen;		// System generator in Hz (default 66 MHz)
	ULONG	dGen1;			// generator 1 in Hz (default 200 MHz)
	ULONG	dGen2;			// generator 2 in Hz (default 0 MHz)
	ULONG	dOcxoGen;		// OCXO generator in Hz (default 0 MHz)
	ULONG	dPllFreq;		// �������, ���������� ���� in Hz (default 0 GHz)
	UCHAR	bClkChanCnt;	// ���������� �������� ������� ������������ (default 2)
	UCHAR	bStrbChanCnt;	// ���������� �������� ������� c������������ (default 2)
	UCHAR	bIsClkE;		// ������� ��������������� ������ CLKE
	UCHAR	bIsClkF;		// ������� ��������������� ������ CLKF
	UCHAR	bIsStrbA;		// ������� ��������������� ������ STROA
	UCHAR	bIsStrbB;		// ������� ��������������� ������ STROB
	UCHAR	bIsStrbD;		// ������� ��������������� ������ STROD
	UCHAR	bIsSync;		// ������� �������������� �������� ������������ �������������
	UCHAR	bIsLF;			// �������� ������ �������� �������� ������������: 1 - LF (0.1-400 ���), 0 - HF(5-2500 ���)
} ICR_CfgSync8chPCI, *PICR_CfgSync8chPCI, ICR_Cfg50A2, *PICR_Cfg50A2;

#pragma pack(pop)    

#endif // __ICRSYNC8CHPCI_H_

// ****************** End of file IcrSync8chPCI.h **********************
