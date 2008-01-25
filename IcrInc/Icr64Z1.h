//****************** File Icr64Z1.h *********************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ 64Z1
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on 64Z1 base module
//
//	Copyright (c) 2008, Instrumental Systems,Corp.
//	Written by Tsikin Eugene
//
//  History:
//  21-01-08 - builded
//
//*******************************************************************
#ifndef __ICR64Z1_H
 #define __ICR64Z1_H

#pragma pack(push, 1)    

const USHORT ADP64Z1_CFG_TAG = 0x6431; // ��� ��� ��������� ���������������� ���������� �������� ������ 64Z1

// 64Z1 module configuration
// ���������������� ��������� �������� ������ 64Z1
typedef struct _ICR_Cfg6431 {
	U16	wTag;			// tag of structure (0x6431)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ADM counter ADM = 1
	U16	wMaxCpuClock;	// ����. �������� ������� ���������� (MHz) - 600, 720, 1000
	U08 bCpuName;		// �������� ���������� 0 - TMS320C6415 1 - TMS320C6416
	U32	dSizeOfSDRAMA;	// ������ SDRAM �� EMIFA (Mb) - 0, 128, 256, 512
	U32	dSizeOfSDRAMB;	// ������ SDRAM �� EMIFB (Mb) - 0, 32
	U32	dSizeOfFlash;	// ������ Flash (Mb) - 0, 2, 4
	U08	bHostPldCnt;	// Host PLD counter
} ICR_Cfg6431, *PICR_Cfg6431, ICR_Cfg64Z1, *PICR_Cfg64Z1;

#pragma pack(pop)    

#endif	// __ICR64Z1_H

// ****************** End of file Icr64Z1.h *************************
