//****************** File Icr0091.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� ADM210x1G
//
//*********************************************************

#ifndef _ICR0091_H
 #define _ICR0091_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x0091

// ���������������� ��������� ���������
typedef struct _ICR_Cfg0091 {
	U16	wTag;		// ��� ��������� (ADM_CFG_TAG)
	U16	wSize;		// ������ ���� ��������� ����� ���������
	U08	bAdmIfNum;	// ����� ���������� ADM
	U08	bAdcCnt;	// ���������� ���
	U08	bSubType;	// ��� ���������: 0-Standard, 1 -WB HF, 2-WB LF 
	U32	nRefGen0;             // ������� ��������� 0 (��)
	U32	nRefGen1;             // ������� ��������� 1 (��)
	U32	nRefGen1Min;          // ������� ��������� 1 (��)
	U32	nRefGen1Max;          // ������� ��������� 1 (��)
	U08	nRefGen1Type;         // ��� �������� ���������� 1
	U32	nRefGen2;             // ������� ��������� 2 (��)
	U08	nRefGen2Type;         // ��� �������� ���������� 2
	U08	nReserve0;            // ������
	U32	nLpfPassBand;         // ������� ����� ��� (��)
	U16 awRange[4];	          // ����� �������������� ��� Standard (��) (default 10000, 2000, 500, 100)
	U16	awRangeDeviation0[4]; // ���������� �� �� �������� ��� ���0 (����) (default 10000)
	U16	awRangeDeviation1[4]; // ���������� �� �� �������� ��� ���1 (����) (default 10000)
	U16 awRelativeBias0[4];   // ������������� �������� ���� ��� ���0 (����) (default 0)
	U16 awRelativeBias1[4];   // ������������� �������� ���� ��� ���1 (����) (default 0)
} ICR_Cfg0091, *PICR_Cfg0091, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR0091_H

// ****************** End of file Icr0091.h **********************
