//****************** File icrc520f1.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� �520�1-��� (C520F1)
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on FMC112cP base modules
//
//	Copyright (c) 2015, Instrumental Systems,Corp.
//	Written by Ekkore
//
//  History:
//  25-02-15 - builded
//
//*******************************************************************

#ifndef __ICRC520F1_H_
 #define __ICRC520F1_H_

#pragma pack(push, 1)    

const USHORT C520F1_CFG_TAG = 0x53A3; // ��� ��� ��������� ���������������� ���������� �������� ������ �520�1-���

// C520F1 modules configuration
// ���������������� ��������� ������� ������� �520�1-���
typedef struct _ICR_CfgC520F1 {
	U16	wTag;			// ��� ��������� (C520F1_CFG_TAG)
	U16	wSize;			// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;		// ���������� ����������� ADM
	U08	reserve;			// ������
	U08	bGen0Type;		// ��� ����������� ���������� 0 (0-�����������������, 1-Si571)
	U08	bAdrGen0;		// �������� ��� �����. ����������: 0x49 �� ���������
	U32	nRefGen0;		// ������� ���������� 0, ���� �� �����������������, ��� ��������� ������� (default 50 MHz)
	U32	nRefMaxGen0;	// ������������ ������� �����. ���������� (��)
} ICR_CfgC520F1, *PICR_CfgC520F1, ICR_Cfg53A3, *PICR_Cfg53A3;

#pragma pack(pop)    

#endif // __ICRC520F1_H_

// ****************** End of file icrc520f1.h **********************
