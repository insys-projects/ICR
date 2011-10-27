//****************** File Icr0094.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� FM214x250M
//
//*********************************************************

#ifndef _ICR0094_H
 #define _ICR0094_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0094

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0094 {
	U16	wTag;		// ��� ��������� (ADM_CFG_TAG)
	U16	wSize;		// ������ ���� ��������� ����� ���������
	U08	bAdmIfNum;	// ����� ���������� ADM
	U08	bAdcCnt;	// ���������� ���: 1, 2
	U08	bAdcType;	// ��� ��������� ���: 0-������
	U08	bDacType;	// ��� ��������� ���: 0-������
	U16	wDacRange;	// ����� �������������� ���: (��)
	U08	bGenType;	// ��� ��������� �����. ����������: 0-�� �������-��, 1-Si571
	U08	bGenAdr;	// �������� ��� �����. ����������: 0x49 �� ���������
	U32	nGenRef;    // ��������� ��������� ������� �����. ���������� (��)
	U32	nGenRefMax; // ������������ ������� �����. ���������� (��)
	U08	bSyntType;	// ��� ��������� �����������: 0-�����������, 1-AD9518
	U08	bAttType;	// ��� ��������� �����������: 0-�����������, 1-DAT-31R5

	U08 reserve[22];// ������ ��� ������������

	S16	awRangeDeviation[2][2][2][4];	// ���������� �� �� �������� (����) (default 10000)
										// [��� �����][R��/���][����� ���][����� ��]
	S16 awBiasDeviation[2][2][2][4];	// ���������� �������� ���� (����) (default 0)
										// [��� �����][R��/���][����� ���][����� ��]
} ICR_Cfg0094, *PICR_Cfg0094, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0094_H

// ****************** End of file Icr0094.h **********************
