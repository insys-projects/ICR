//****************** File icrAmbp.h *******************************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ������� ������� AMBPCD/AMBPCX
//
//  Constants & structures definitions
//	for identification & configuration EPROM
//  on AMBPCD/AMBPCX base modules
//
//	Copyright (c) 2004, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  05-10-04 - builded
//  14-10-04 - add AMBPCD
//  20-10-04 - add dSysGen
//
//*******************************************************************

#ifndef __ICRAMBP_H_
 #define __ICRAMBP_H_

#pragma pack(push, 1)    

const USHORT AMBPCD_CFG_TAG = 0x4D44; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBPCD
const USHORT AMBPCX_CFG_TAG = 0x4D58; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBPCX
const USHORT AMBPEX2_CFG_TAG = 0x5508; // ��� ��� ��������� ���������������� ���������� �������� ������ AMBPEX2

// AMBPCD/AMBPCX modules configuration
// ���������������� ��������� ������� ������� AMBPCD/AMBPCX
typedef struct _ICR_CfgAmbp {
	USHORT	wTag;			// ��� ��������� (AMBPCX_CFG_TAG ��� AMBPCD_CFG_TAG)
	USHORT	wSize;			// ������ ���� ��������� ����� ���������
	UCHAR	bAdmIfCnt;		// ���������� ����������� ADM
	ULONG	dSysGen;		// System generator in Hz (default 66 MHz)
	UCHAR	bSdramSlotCnt;	// ���������� ������������� ������ ������������ ������
	UCHAR	bSdramCfgCnt;	// ���������� ���������������� �������� ������������ ������
	UCHAR	bDspNodeCfgCnt;	// ���������� ���������������� �������� ���� �������� ��������� ��������
} ICR_CfgAmbp, *PICR_CfgAmbp, ICR_Cfg4d58, *PICR_Cfg4d58, ICR_CfgAmbpcx, *PICR_CfgAmbpcx, ICR_Cfg4d44, *PICR_Cfg4d44, ICR_CfgAmbpcd, *PICR_CfgAmbpcd;

#pragma pack(pop)    

#endif // __ICRAMBP_H_

// ****************** End of file IcrAmbp.h **********************
