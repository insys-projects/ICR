//****************** File Icr009F.h ***********************
//
//  ����������� �������� � �������� 
//	��� ������ � ���������������� ����
//  ��� ��������� FM405P � ��������� ���������
//
//*********************************************************

#ifndef _ICR009F_H
 #define _ICR009F_H

#pragma pack(push, 1)    

#define ADM_CFG_TAG 0x009F

// ���������������� ��������� ���������
typedef struct _ICR_Cfg009F {
	U16	wTag;		// ��� ��������� (ADM_CFG_TAG)
	U16	wSize;	// ������ ���� ��������� ����� ���������
	U08	bAdmIfNum;	// ����� ���������� ADM
	U08	isMatching;// ���� ������������ ������� ����; 0-���, 1-����
	U08 reserve[10];// ������
} ICR_Cfg009F, *PICR_Cfg009F, ICR_CfgAdm, *PICR_CfgAdm;

#pragma pack(pop)    

#endif // _ICR009F_H

// ****************** End of file Icr009F.h **********************
