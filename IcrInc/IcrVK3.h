//****************** File IcrVK3.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ������ VK3
//
//*********************************************************

#ifndef _ICRVK3_H
#define _ICRVK3_H

#include "utypes.h"
#include "icr.h"

#pragma pack(push, 1)    

const USHORT VK3_CFG_TAG = 0x5506; // ��� ��� ��������� ���������������� ���������� ������ VK3

// VK3 module configuration
// ���������������� ��������� ������ VK3
typedef struct _ICR_Cfg5506 
{
	U16		wTag;			// tag of structure (0x5506)
	U16		wSize;			// size of all following fields of structure (without wTag + wSize) = sizeof(ICR_XXXX) - 4
	U32		nNum;			// ���������� ����� �������
	U08		bDdrModuleNum;	// ���������� ������ ������������ ������
	REAL32	fSysGen;		// ������� ���������� ���������� (MHz) - 66.666
	U16		wRefGen;		// ������� �������� ���������� (MHz) - 10
	U08		isDacBias;		// ��� ��������
	U08		bDacBiasBits;	// ����������� ��� ��������
	U08		bAdcChanNum;	// ���������� ������� ��� 0, 1
	U08		bAdcInpNum;		// ����� ������ ����������� ��� - 0, 1, 2
	U08		isAdcInpAdd;	// �������������� ���� ���, 1 - ����, 0 - ���
	U08		bAdcTypeF;		// ��� ������� ���, 1 - PLP-15
	U16		wAdcBiasRange;	// �������� ����������� �������� ��� (mV), 100
	U08		bAdcBits;		// ����������� ��� 16
	U16		wMaxfreqSampl;	// ������������ ������� ������������� (MHz), 80, 100
	U16		wInpAmplRange;	// ������� ����������� �������� 1700 mV
	U32		nInpR;			// ������� �������������, 50 ��, 75 ��, 1���
	U08		isTuner;		// �����, 1 - ����, 0 - ���
	U08		isSelectorSinch;// �������� ���������������, 1 - ����, 0 - ���
	U08		bDacChanNum;	// ���������� ������� ��� 0, 1
	U08		bDacOutNum;		// ����� ������� ��� - 0, 1, 2
	U08		bDacTypeF;		// ��� ������� ���, 1 - PLP-15
	U16		wDacBiasRange;	// �������� ����������� �������� ��� (mV), 500
	U08		bDacBits;		// ����������� ��� 14
	U16		wOutAmplRange;	// �������� ����������� �������� 1100 mV
	U32		nOutR;			// �������� �������������, 50 ��, 75 ��
	
	_ICR_Cfg0510	rPldType;	// ��� ����
} ICR_Cfg5506, *PICR_Cfg5506, ICR_CfgVK3, *PICR_CfgVK3;

#pragma pack(pop) 

#endif // _ICRVK3_H

// ****************** End of file IcrVK3.h **********************
