//****************** File Icr008D.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ��������� ADM-FOTR
//
//*********************************************************

#ifndef _ICR008D_H
 #define _ICR008D_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x008D

// ���������������� ��������� ���������
typedef struct _ICR_Cfg008D {
	USHORT	wTag;		// ��� ��������� (ADM_CFG_TAG)
	USHORT	wSize;		// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfNum;	// ����� ���������� ADM
	ULONG	dGen;		// �������� �������� ����������
	UCHAR	bChanCnt;	// ���������� �������
	UCHAR	bTranciever; // ��� ������-�����������
} ICR_Cfg008D, *PICR_Cfg008D, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR008D_H

// ****************** End of file Icr008D.h **********************
