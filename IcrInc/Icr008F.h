//****************** File Icr008F.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� ADMDAC216x400M
//
//	Copyright (c) 2008, Instrumental Systems,Corp.
//	Written by Tsikin Eugene
//
//  History:
//  29-01-08 - builded
//
//*********************************************************

#ifndef _ICR008F_H
 #define _ICR008F_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008F

// ���������������� ��������� ���������
typedef struct _ICR_Cfg008F {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen;		// �������� �������� ����������
	UCHAR	bFreqTune;	// ���������� ������� ����������� �������� ����������
	UCHAR	bDacCnt;	// ���������� ���
	ULONG	dLPFCutoff;	// ������� ����� ������� ������ ������ (��)
	UCHAR	bOutResist;	// �������� ������������� (0 - 50 ��, 1 - 75 ��)
	ULONG	dOscFreq;	// ������� ��� (��) (�� �����. 400 ���)
	UCHAR	bOutCasMod;	// ����������� ��������� ������� 0 - LF, 1 - HF
	UCHAR	bQuadModType;// ��� ������������� ���������� ( 0 - ���, 1 � AD8345, 2 � AD8346, 3 � AD8349 )
	UCHAR	bIsExtClk;	// ������� ����� �������� ������������
} ICR_Cfg008F, *PICR_Cfg008F, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008F_H

// ****************** End of file Icr008F.h **********************
