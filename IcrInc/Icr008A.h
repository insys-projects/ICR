//****************** File Icr008A.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� 
//
//	Copyright (c) 2002-2004, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  30-08-04 - builded
//
//*********************************************************

#ifndef _ICR008A_H
 #define _ICR008A_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008A

// ���������������� ��������� ���������
typedef struct _ICR_Cfg008A {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen;		// �������� �������� ����������
	UCHAR	bDacCnt;	// ���������� ���
	ULONG	dLPFCutoff;	// ������� ����� ������� ������ ������ (��)
	UCHAR	bOutResist;	// �������� ������������� (0 - 50 ��, 1 - 75 ��)
	UCHAR	bIsQuadMod;	// ������� ������������� ����������
	UCHAR	bIsExtClk;	// ������� ����� �������� ������������
} ICR_Cfg008A, *PICR_Cfg008A, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008A_H

//****************** End of file Icr008A.h **********************
