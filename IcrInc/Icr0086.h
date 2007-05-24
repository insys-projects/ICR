//****************** File Icr0086.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� 
//
//	Copyright (c) 2002-2006, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  25-01-06 - builded
//
//*********************************************************

#ifndef _ICR0086_H
 #define _ICR0086_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0086

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0086 {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen;		// �������� �������� ����������
	UCHAR	bAdcCnt;	// ���������� ���
	UCHAR	bDdcCnt;	// ���������� DDC
	UCHAR	bRes;		// ���� �� ������������ (������� ������� ��� ?)
} ICR_Cfg0086, *PICR_Cfg0086, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0086_H

//****************** End of file Icr0086.h **********************
