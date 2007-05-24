//****************** File Icr0089.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ��������� ADM212x200M 
//
//*********************************************************

#ifndef _ICR0089_H
 #define _ICR0089_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0089

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0089 {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen;		// �������� �������� ����������
	UCHAR	bAdcCnt;	// ���������� ���
} ICR_Cfg0089, *PICR_Cfg0089, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0083_H

// ****************** End of file Icr0089.h **********************
