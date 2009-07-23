//****************** File Icr0090.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� ADM212x500(WB), ADM214x400M(WB)
//
//*********************************************************

#ifndef _ICR0090_H
 #define _ICR0090_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0090

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0090 {
	U16	wTag;		// ��� ��������� (ADM_CFG_TAG)
	U16	wSize;		// ������ ���� ��������� ����� ���������
	U08	bAdmIfNum;	// ����� ���������� ADM
	U08	bAdcCnt;	// ���������� ���
	U08	bSubType;	// ��� ���������: 0-Standard, 1 -WB HF, 2-WB LF 
	U32	anRefGen[2];// ������� ���������� 0 � 1 (��)
	U16 awRange[4];	// ����� �������������� ��� Standard (��) (default 10000, 2000, 500, 100)
	U16	awRangeDeviation0[4]; // ���������� �� �� �������� ��� ���0 (����) (default 10000)
	U16	awRangeDeviation1[4]; // ���������� �� �� �������� ��� ���1 (����) (default 10000)
	U16 awRelativeBias0[4];// ������������� �������� ���� ��� ���0 (����) (default 0)
	U16 awRelativeBias1[4];// ������������� �������� ���� ��� ���1 (����) (default 0)
} ICR_Cfg0090, *PICR_Cfg0090, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0090_H

// ****************** End of file Icr0090.h **********************
