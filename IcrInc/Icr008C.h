//****************** File Icr008C.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� 
//
//	Copyright (c) 2002-2005, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  08-09-05 - builded
//
//*********************************************************

#ifndef _ICR008C_H
 #define _ICR008C_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008C

// ���������������� ��������� ���������
typedef struct _ICR_Cfg008C {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen;		// �������� �������� ����������
	UCHAR	bIsOxco;	// ������� OXCO
	UCHAR	bIsDblFreq;	// ������� ��������� ������� �������� ����������
	ULONG	dLPFCutoff;	// ������� ����� ������� ������ ������ (��)
	UCHAR	bIsExtClk;	// ������� ����� �������� ������������
	UCHAR	bIsStrobe;	// ������� ������������� ��������� �������
	USHORT	wMaxAmpl;	// ������������ ��������� ��������� �������
} ICR_Cfg008C, *PICR_Cfg008C, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008�_H

//****************** End of file Icr008�.h **********************
