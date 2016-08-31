//****************** File icrAmbvme.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  �������� ������ AMBVME 
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on AMBVME base module
//
//	Copyright (c) 2002-2004, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  27-05-04 - builded
//
//*******************************************************************
#ifndef __ICRAMBVME_H
 #define __ICRAMBVME_H

#pragma pack(push, 1)    

const USHORT AMBVME_CFG_TAG = 0x4D56; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBVME
const USHORT FMC116V_CFG_TAG = 0x5515; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBVME


// AMBVME module configuration
// ���������������� ��������� �������� ������ AMBVME
typedef struct _ICR_Cfg4D56 {
	U16	wTag;			// tag of structure (0x4D56)
	U16	wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08	bAdmIfCnt;		// ADM counter ADM = 1
	U08	bSdramCfgCnt;	// SDRAM structure counter
	U08	bHostPldCnt;	// Host PLD counter
} ICR_Cfg4D56, *PICR_Cfg4D56, ICR_CfgAmbvme, *PICR_CfgAmbvme;

#pragma pack(pop)    

#endif	// __ICRAMBVME_H

// ****************** End of file icrAmbvme.h **********************
