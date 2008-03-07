//****************** File icrAmb3us.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ AMB3UV
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on AMB3UV base module
//
//	Copyright (c) 2007, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//
//*******************************************************************
#ifndef __ICRAMB3UV_H
 #define __ICRAMB3UV_H

#pragma pack(push, 1)    

const USHORT AMB3UV_CFG_TAG = 0x5467; // ��� ��� ��������� ���������������� ���������� �������� ������ AMB3UV

// AMB3UV module configuration
// ���������������� ��������� �������� ������ AMB3UV
typedef struct _ICR_Cfg5467 {
	USHORT	wTag;			// ��� ��������� (AMB3UV_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfCnt;		// ���������� ����������� ADM = 1
	ULONG	dSysGen;		// System generator in Hz (default 100 MHz)
	UCHAR	bDdsType;		// type of DDS (0-non, 1-PLL, 2-DDS)
	UCHAR	bDspNodeCfgCnt;	// ���������� ���������������� �������� ���� �������� ��������� ��������
} ICR_Cfg5467, *PICR_Cfg5467, ICR_CfgAmb3uv, *PICR_CfgAmb3uv;

#pragma pack(pop)    

#endif	// __ICRAMB3UV_H

// ****************** End of file icrAmb3uv.h **********************
