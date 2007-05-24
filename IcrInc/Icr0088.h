//****************** File Icr0088.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� 
//
//	Copyright (c) 2002-2003, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  09-10-03 - builded
//
//*********************************************************

#ifndef _ICR0088_H
 #define _ICR0088_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0088

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0088 {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	UCHAR	bBufType;	// ��� ������
} ICR_Cfg0088, *PICR_Cfg0088, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0087_H

//****************** End of file Icr0087.h **********************
