//****************** File Icr0081.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� ADM28x1G, ADM214x200M
//
//*********************************************************

#ifndef _ICR0081_H
 #define _ICR0081_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0081

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0081 {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dPllRefGen;	// ������� ��������� ��� ���� in Hz (default 40 MHz)
	ULONG	dPllFreq;	// �������, ���������� ���� in Hz (default 2 GHz)
	UCHAR	bAdcCnt;	// ���������� ���
	UCHAR	bIsRF;		// ������� �����: 1 - ��������������, 0 - ��� (ADM214x200M ver 1.1)
} ICR_Cfg0081, *PICR_Cfg0081, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0081_H

// ****************** End of file Icr0081.h **********************
