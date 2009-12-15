//****************** File IcrVK3.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ������ DR-16
//
//*********************************************************

#ifndef _ICRDR16_H
#define _ICRDR16_H

#include "utypes.h"
#include "icr.h"

#pragma pack(push, 1)    

const USHORT DR16_CFG_TAG = 0x53B0; // ��� ��� ��������� ���������������� ���������� ������ DR16

// DR-16 module configuration
// ���������������� ��������� ������ DR-16
typedef struct _ICR_Cfg53B0
{
	U16		wTag;				// tag of structure (0x5506)
	U16		wSize;				// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U08		isDuc;				// ������� DUC (Digital Up Converter): 0, 1
	U08		isDucTransformator;	// ������� ����������������� ������ DUC�: 0, 1
	U08		isGenerator;		// ������� : 0, 1
	U08		isSynthesizer;		// ������� : 0, 1
	U08		isExtTactInput;		// ������� : 0, 1
	U08		isExtStartInput;	// ������� : 0, 1
	U08		isExtStartOutput;	// ������� : 0, 1
	U08		isLinks;			// ������� : 0, 1
	U08		isPiox;				// ������� : 0, 1
	U08		isSynx;				// ������� : 0, 1
	U08		isLvdsPiox;			// ������� : 0, 1
	U08		isPci64;			// ������� : 0, 1
	U08		isIndustrial;		// ������� : 0, 1

	U08		bAdcCnt;			// ���������� ���: 1..16
	U08		bAdcBits;			// ����������� ��� (����� ���): 12, 14, 16
	U08		bAdcEncoding;		// ��� ���������: 0 - ������ ���, 1 - �������-��������.
	U32		nAdcMinRate;		// ����������� ������� ������������� (��)
	U32		nAdcMaxRate;		// ������������ ������� ������������� (��)
	U32		nAdcLowFreq;		// ������ ������� ����� ��� (��)
	U32		nAdcHighFreq;		// ������� ������� ����� ��� (��)
	U16		wAdcRange;			// ������� �������� ��� (������)
	U08		bAdcInpResist;		// ������� ������������� ���: 0 - 50 ��, 1 - 75 ��

	U08		bDdcCnt;			// ���������� ���������  DDC: 1-4
	U32		nDucHighFreq;		// ������� ������� ����� DUC (��)
	U16		wDucRange;			// ����� �������������� DUC (��)
	U32		nGenFreq;			// ������� �������� ���������� (��)
	U16		wGenPrec;			// �������� ������� �������� ���������� (0.01 ppm)
	U32		nSyntFreq;			// ������� �����������
} ICR_Cfg53B0, *PICR_Cfg53B0, ICR_CfgDR16, *PICR_CfgDR16;

#pragma pack(pop) 

#endif // _ICRDR16_H

// ****************** End of file IcrDR16.h **********************
