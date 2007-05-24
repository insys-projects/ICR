//****************** File Icr0084.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� 
//
//*********************************************************

#ifndef _ICR0084_H
 #define _ICR0084_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0084

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0084 {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	UCHAR	bAdcCnt;	// ���������� ���
} ICR_Cfg0084, *PICR_Cfg0084, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0084_H

// ****************** End of file Icr0084.h **********************
