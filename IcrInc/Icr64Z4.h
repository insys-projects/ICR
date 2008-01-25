//****************** File Icr64Z4.h *********************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ 64Z4
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on 64Z4 base module
//
//	Copyright (c) 2008, Instrumental Systems,Corp.
//	Written by Tsikin Eugene
//
//  History:
//  21-01-08 - builded
//
//*******************************************************************
#ifndef __ICR64Z4_H
 #define __ICR64Z4_H

#pragma pack(push, 1)    

const USHORT ADP64Z4_CFG_TAG = 0x6434; // ��� ��� ��������� ���������������� ���������� �������� ������ 64Z4

// 64Z4 module configuration
// ���������������� ��������� �������� ������ 64Z4
typedef struct _ICR_Cfg6434 {
	U16	wTag;			// tag of structure (0x6434)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ADM counter ADM = 1
	U08	bCpuCnt;		// ���������� �����������
	U16	wMaxCpuClock;	// ����. �������� ������� ����������(-��) (MHz) - 720, 800, 1000
	U08	bFlashCnt;		// ���������� ���� Flash ������� 4 ����� ��� ����������(-��)
	U08	bHostPldCnt;	// Host PLD counter
} ICR_Cfg6434, *PICR_Cfg6434, ICR_Cfg64Z4, *PICR_Cfg64Z4;

#pragma pack(pop)    

#endif	// __ICR64Z4_H

// ****************** End of file Icr64Z4.h *************************
