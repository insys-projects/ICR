//****************** File Icr0083.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� 
//
//*********************************************************

#ifndef _ICR0083_H
 #define _ICR0083_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0083

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0083 {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen[3];	// �������� ������� ����������� 1-3
	UCHAR	bAdcCnt;	// ���������� ���
} ICR_Cfg0083, *PICR_Cfg0083, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0083_H

// ****************** End of file Icr0083.h **********************
