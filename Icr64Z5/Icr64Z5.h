//****************** File Icr64Z5.h *********************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ 64Z5
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on 64Z5 base module
//
//	Copyright (c) 2009, Instrumental Systems,Corp.
//	Written by Kozlov Andrej
//
//  History:
//  08-06-09 - builded
//
//*******************************************************************
#ifndef __ICR64Z5_H
#define __ICR64Z5_H

#pragma pack(push, 1)    

const USHORT ADP64Z5_CFG_TAG = 0x6435; // ��� ��� ��������� ���������������� ���������� �������� ������ 64Z5

// 64Z5 module configuration
// ���������������� ��������� �������� ������ 64Z5
typedef struct _ICR_Cfg6435 {
	U16	wTag;			// tag of structure (0x6435)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ADM counter ADM = 1
	U08 bCpuName;		// �������� ���������� 0 - TMS320C6455
	U16	wMaxCpuClock;	// ����. �������� ������� ����������(-��) (MHz) - 1200
	U16	wSizeOfDDR2;	// ������ DDR2 (Mb) - 256, 512
	U32	wSizeOfFlash;	// ������ Flash (Mb) - 4
	U08	isSetEMAC;		// ������� EMAC 1Gb, 0 - �����������, 1 - ������������
	U08 bTypeSRIO;		// ��� ������� Serial Rapid IO, 0 - �����������, 1 - SRIO4xCU, 2 - SRIO4xFO, 3 - SRIO1(x4) 
} ICR_Cfg6435, *PICR_Cfg6435, ICR_Cfg64Z5, *PICR_Cfg64Z5;

#pragma pack(pop)    

#endif	// __ICR64Z5_H

// ****************** End of file Icr64Z4.h *************************
