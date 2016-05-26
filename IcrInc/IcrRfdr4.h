//****************** File IcrRfdr4.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ������ RFDR4
//
//*********************************************************

#ifndef _ICRRFDR4_H
#define _ICRRFDR4_H

#include "utypes.h"
#include "icr.h"

#pragma pack(push, 1)    

const USHORT RFDR4_CFG_TAG = 0x53B4; // ��� ��� ��������� ���������������� ���������� ������ RFDR4

// ���������������� ��������� ������ RFDR4
typedef struct _ICR_Cfg53B4
{
	U16		wTag;				// tag of structure (0x53B4)
	U16		wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08		bAdmIfCnt;		// ���������� ����������� ADM
	U08		bAdcCnt;			// ���������� ���
	U08		bAttenuationMax;	// ������������ �������� ����������� (��)
	U08		bAttenuationStep;	// ��� ����������� ����������� (��)
	U08		bDdcCnt;			// ���������� ������� DDC �� ���� ����� ���
	U32		nIntGenFreq;		// ������� ����������� ���������� (��)
	U32		nDdcDecimation;		// ����������� ��������� DDC
	U32		nDdcBand;			// ������ ������ DDC (��)
	U16		wDdcGain;			// ����������� �������� DDC (���� ����)
	U16		wFifoSizeK			// ������ ���� ��� �� ���� ����� (����� ��������)
} ICR_Cfg53B4, *PICR_Cfg53B4, ICR_CfgRfdr4, *PICR_CfgRfdr4;

#pragma pack(pop) 

#endif // _ICRRFDR4_H

// ****************** End of file IcrRfdr4.h **********************
