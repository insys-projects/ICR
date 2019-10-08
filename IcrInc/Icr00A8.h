//****************** File Icr00A8.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� FM816x600M
//
//*********************************************************

#ifndef _ICR00A8_H
 #define _ICR00A8_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x00A8

// ���������������� ��������� ���������
typedef struct _ICR_Cfg00A8 {
	U16	wTag;		// ��� ��������� (ADM_CFG_TAG)
	U16	wSize;		// ������ ���� ��������� ����� ���������
	U08	bAdmIfNum;	// ����� ���������� ADM
	U08	bAdcCnt;	// ���������� ���: 4, 8
	U08	bAdcType;	// ��� ��������� ���: 1-������
	U08	bThdac16Type;	// ��� 16-���������� ��������� ���-���: 1-������
	U16	wThdac16Range;	// ����� �������������� 16-���������� ���-���: (��)
	U08	bGenType;	// ��� ��������� �����. ����������: 0-�� �������-��, 1-Si571
	U08	bGenAdr;	// �������� ��� �����. ����������: 0x49 �� ���������
	U32	nGenRef;    // ��������� ��������� ������� �����. ���������� (��)
	U32	nGenRefMax; // ������������ ������� �����. ���������� (��)
	U32	nAdcLoBand;	// ������ ������� ������ ��� (��)
	U32	nAdcHiBand;	// ������� ������� ������ ��� (��)
	U32	nAdcBitrateMin;	// ����������� ������� ��������� ��� (�������/���)
	U32	nAdcBitrateMax;	// ������������ ������� ��������� ��� (�������/���)
	U16	wThdac1Range;	// ����� �������������� 1-���������� ���-���: (��)
	U08	bInpType;		// ��� �����: 0-��������, 1-��������
	U08	bReserve;		// ������
	U16	awUcm[8];		// ���� ��� U��, ��������� � LTC2668: 0..65535
	U16	awBiasMax[8];	// �������� �������� ���� ��� ���� 0 � LTC2668 (��)
	S16	awBiasMin[8];	// �������� �������� ���� ��� ���� 0xFFFF � LTC2668 (��)
	U16	awDac0[8];		// ���� � LTC2668 ���  �������� ����, ������� 0 ������: 0..65535
} ICR_Cfg00A8, *PICR_Cfg00A8, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR00A8_H

// ****************** End of file Icr00A8.h **********************
