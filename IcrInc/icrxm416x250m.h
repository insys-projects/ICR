//****************** File icrxm416x250m.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� XM416x250M
//
//	Copyright (c) May 2014, Instrumental Systems,Corp.
//	Written by Ekkore
//
//*******************************************************************

#ifndef __XM416x250M_H_
 #define __XM416x250M_H_

#pragma pack(push, 1)    

const USHORT XM416x250M_CFG_TAG = 0x5516; // ��� ��� ��������� ���������������� ���������� ������� ����� ���������������� ������ XM416x250M

// XM416x250M module configuration
// ���������������� ��������� �������� ������ XM416x250M
typedef struct _ICR_CfgXm416x250m {
	U16	wTag;			// ��� ��������� (XM416x250M_CFG_TAG)
	U16	wSize;			// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;		// ���������� ����������� ADM
	U32	dSysGen;			// ��������� ��������� (��) (�� ��������� 250 ���)
	U08	isDDR3;			// ������� ������ DDR3
	U08	isVoltageMonitor;	// ������� �������� ����������
	U08	isCurrentMonitor;	// ������� �������� ����
} ICR_CfgXm416x250m, *PICR_CfgXm416x250m, ICR_Cfg5516, *PICR_Cfg5516;

#pragma pack(pop)    

#endif // __XM416x250M_H_

// ****************** End of file icrxm416x250m.h **********************
