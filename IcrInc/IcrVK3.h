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
	U32		nSysGen;		// ������� ���������� ���������� (MHz) - 66.666
	U32		nRefGen;		// ������� �������� ���������� (MHz) - 10
	U08		isDacBias;		// ��� ��������
	U08		bDacBiasBits;	// ����������� ��� ��������
	U08		bAdcChanNum;	// ���������� ������� ��� 0, 1
	U08		bAdcInpNum;		// ����� ������ ����������� ��� - 0, 1, 2
	U08		isAdcInpAdd;	// �������������� ���� ���, 1 - ����, 0 - ���
	U08		abAdcTypeF[16];		// ��� ������� ���, 1 - PLP-15
	U32		nAdcBiasRange;	// �������� ����������� �������� ��� (mV), 100
	U08		bAdcBits;		// ����������� ��� 16
	U16		wMaxfreqSampl;	// ������������ ������� ������������� (MHz), 80, 100
	U16		wInpAmplRange;	// ������� ����������� �������� 1700 mV
	U32		nInpR;			// ������� �������������, 50 ��, 75 ��, 1���
	U08		isTuner;		// �����, 1 - ����, 0 - ���
	U08		isSelectorSinch;// �������� ���������������, 1 - ����, 0 - ���
	U08		bDacChanNum;	// ���������� ������� ��� 0, 1
	U08		bDacOutNum;		// ����� ������� ��� - 0, 1, 2
	U08	    abDacTypeF[16];	// ��� ������� ���, 1 - PLP-15
	U32		nDacBiasRange;	// �������� ����������� �������� ��� (mV), 500
	U08		bDacBits;		// ����������� ��� 14
	U32		nOutAmplRange;	// �������� ����������� �������� 1100 mV
	U32		nOutR;			// �������� �������������, 50 ��, 75 ��
} ICR_Cfg5506, *PICR_Cfg5506, ICR_CfgVK3, *PICR_CfgVK3;

#pragma pack(pop) 

#endif // _ICRVK3_H

// ****************** End of file IcrVK3.h **********************
