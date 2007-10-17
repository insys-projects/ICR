//****************** File Icr008F.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ���������� ADMDAC216x400M
//
//*********************************************************

#ifndef _ICR008F_H
 #define _ICR008F_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008F

// ���������������� ��������� ���������
typedef struct _ICR_Cfg008F {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dPllRefGen;	// ������� ��������� ��� ���� in Hz (default 10 MHz)
	ULONG	dPllFreq;	// �������, ���������� ���� in Hz (default 400 MHz)
	UCHAR	bDacCnt;	// ���������� ���
} ICR_Cfg008F, *PICR_Cfg008F, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008F_H

// ****************** End of file Icr008F.h **********************
