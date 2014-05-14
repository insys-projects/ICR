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

// FMC105P/FMC106P modules configuration
// ���������������� ��������� ������� ������� FMC105P/FMC106P
typedef struct _ICR_CfgFmc105p {
	U16	wTag;			// ��� ��������� (FMC105P_CFG_TAG ��� FMC106P_CFG_TAG)
	U16	wSize;			// ������ ���� ��������� ����� ���������
	U08	bAdmIfCnt;		// ���������� ����������� ADM
	U32	dSysGen;			// ��������� ��������� (��) (�� ��������� 250 ���)
	U08	isDDR3;			// ������� ������ DDR3
	U08	isVoltageMonitor;	// ������� �������� ����������
	U08	isCurrentMonitor;	// ������� �������� ����
} ICR_CfgFmc105p, *PICR_CfgFmc105p, ICR_Cfg5509, *PICR_Cfg5509;

#pragma pack(pop)    

#endif // __XM416x250M_H_

// ****************** End of file icrxm416x250m.h **********************
