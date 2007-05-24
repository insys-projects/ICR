//****************** File Icr008B.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ��������� ADM28x800M
//
//*********************************************************

#ifndef _ICR008B_H
 #define _ICR008B_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008B

// ���������������� ��������� ���������
typedef struct _ICR_Cfg008B {
	USHORT	wTag;			// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;		// ����� ���������� ADM
	ULONG	dMainGen;		// �������� ��������� �������� ����������
	ULONG	dMaxFreqVco;	// ������������ ������� ��������������� ���
	ULONG	dMinFreqVco;	// ����������� ������� ��������������� ���
	UCHAR	bIsClbrValue;	// ������� ������������� �������������
	UCHAR	bAdcCnt;		// ���������� ���
} ICR_Cfg008B, *PICR_Cfg008B, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008B_H

// ****************** End of file Icr008B.h **********************
