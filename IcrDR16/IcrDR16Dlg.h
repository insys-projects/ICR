#ifndef _ICRDR16DLG_H
#define _ICRDR16DLG_H

#include "utypes.h"
#include "resource.h"		// main symbols
#include "NumEdit.h"

#pragma once

// IcrDR16Dlg dialog

class CNumComboBox : public CComboBox
{
	public:

		CNumEdit	m_NumEdit;
		S08			m_isNumber;

		CNumComboBox(){m_isNumber = -1;}
		virtual ~CNumComboBox(){};

		void SetNumber(U08 isEnable);
		S08 GetNumber(){return m_isNumber;}
};

class IcrDR16Dlg : public CDialog
{
	DECLARE_DYNAMIC(IcrDR16Dlg)

public:
	IcrDR16Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~IcrDR16Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	S32 m_isDuc;
	S32 m_isDucTransformator;
	S32 m_isGenerator;
	S32 m_isSynthesizer;
	S32 m_isExtTactInput;
	S32 m_isExtStartInput;
	S32 m_isExtStartOutput;
	S32 m_isLinks;
	S32 m_isPiox;
	S32 m_isSynx;
	S32 m_isLvdsPiox;
	S32 m_isPci64;
	S32 m_isIndustrial;
	U08 m_bAdcCnt;
	U32 m_nAdcMinRate;
	U32 m_nAdcHighFreq;
	U32 m_nDucHighFreq;
	U32 m_nGenFreq;
	U32 m_nSyntFreq;

	CString m_sAdcBits;
	CString m_sAdcMaxRate;
	CString m_sAdcInpResist;
	CString m_sAdcRange;
	CString m_sDdcCnt;
	CString m_sDucRange;
	CString m_sGenPrec;
	CString m_sAdcLowFreq;

	CNumEdit m_ctrlGenPrec;
	CNumEdit m_ctrlAdcLowFreq;

	CNumComboBox m_ctrlAdcBits;
	CNumComboBox m_ctrlAdcMaxRate;
	CNumComboBox m_ctrlAdcInpResist;
	CNumComboBox m_ctrlAdcRange;
	CNumComboBox m_ctrlDdcCnt;
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

protected:
	CToolTipCtrl m_ToolTip;   
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CNumComboBox m_ctrlDucRange;
};

#endif // _ICRDR16DLG_H
