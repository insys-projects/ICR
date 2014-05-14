//****************** File Icr0097.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� FM816x250M, FM416x250M, FM416x100M, XM416x250M
//
//*********************************************************

#ifndef _ICR0097_H
 #define _ICR0097_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0097

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0097 {
	U16	wTag;		// ��� ��������� (ADM_CFG_TAG)
	U16	wSize;		// ������ ���� ��������� ����� ���������
	U08	bAdmIfNum;	// ����� ���������� ADM
	U08	bAdcCnt;	// ���������� ���: 4, 8
	U08	bAdcType;	// ��� ��������� ���: 0-�����������, 1-AD9467B
	U08	bDacType;	// ��� ��������� ���: 0-���, 1-AD5621
	U16	wDacRange;	// ����� �������������� ���: (��)
	U08	bGenType;	// ��� ��������� �����. ����������: 0-�� �������-��, 1-Si571
	U08	bGenAdr;	// �������� ��� �����. ����������: 0x49 �� ���������
	U32	nGenRef;    // ��������� ��������� ������� �����. ���������� (��)
	U32	nGenRefMax; // ������������ ������� �����. ���������� (��)
} ICR_Cfg0097, *PICR_Cfg0097, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0097_H

// ****************** End of file Icr0097.h **********************
