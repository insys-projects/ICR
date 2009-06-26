#ifndef _ICRVK3DLG_H
#define _ICRVK3DLG_H

#pragma once

#include "utypes.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "NumEdit.h"

// IcrVK3Dlg dialog

class IcrVK3Dlg : public CDialog
{
	DECLARE_DYNAMIC(IcrVK3Dlg)

public:
	IcrVK3Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~IcrVK3Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	U32 m_nNum;
	U08 m_bDdrModuleNum;
	REAL32 m_fSysGen;
	U16 m_wRefGen;
	U08 m_bDacBiasBits;
	U08 m_isDacBias;
	U08 m_bAdcChanNum;
	U08 m_bAdcInpNum;
	U08 m_bAdcTypeF;
	U16 m_wAdcBiasRange;
	U08 m_bAdcBits;
	U32 m_nMaxfreqSampl;
	U16 m_wInpAmplRange;
	U32 m_nInpR;
	U08 m_isAdcInpAdd;
	U08 m_isTuner;
	U08 m_isSelectorSinch;
	U32 m_nDacChanNum;
	U08 m_bDacOutNum;
	U08 m_bDacTypeF;
	U16 m_wDacBiasRange;
	U08 m_bDacBits;
	U16 m_wOutAmplRange;
	U32 m_nOutR;
	U08 m_bType;
	U32 m_nVolume;
	U08 m_bSpeedGrade;
	U32 m_nPins;
public:
	virtual BOOL OnInitDialog();
public:
	CToolTipCtrl m_ToolTip;
public:
	CComboBox m_ctrlDdrModuleNum;
public:
	CComboBox m_ctrlSysGen;
public:
	CComboBox m_ctrlRefGen;
public:
	CButton m_ctrlDacBiasSet;
public:
	CComboBox m_ctrlDacBiasRange;
public:
	void DacParamEnable(U08 isSet = TRUE);
public:
	CEdit m_ctrlDacChanNum;
public:
	CEdit m_ctrlDacOutNum;
public:
	CComboBox m_ctrlDacTypeF;
public:
	CEdit m_ctrlDacBits;
public:
	CComboBox m_ctrlOutAmplRange;
public:
	CComboBox m_ctrlOutR;
public:
	afx_msg void OnBnClickedDacset();
public:
	CEdit m_ctrlDacBiasBits;
public:
	CComboBox m_ctrlAdcBiasRange;
public:
	void AdcParamEnable(U08 isSet);
public:
//	afx_msg void OnEnChangeDacchannum();
public:
//	afx_msg void OnEnUpdateDacchannum();
public:
	afx_msg void OnEnChangeDacchannum();
public:
	CComboBox m_ctrlAdcTypeF;
public:
	CComboBox m_ctrlMaxfreqSampl;
public:
	CComboBox m_ctrlInpAmplRange;
public:
	CComboBox m_ctrlInpR;
public:
	afx_msg void OnCbnSelchangeOutampl();
public:
	CButton m_ctrlAdcInpAdd;
public:
	CButton m_ctrlTuner;
public:
	CButton m_ctrlSelectorSinch;
public:
	CEdit m_ctrlAdcInpNum;
public:
	CEdit m_ctrlAdcBits;
public:
	afx_msg void OnEnChangeAdcchannum();
public:
	afx_msg void OnBnClickedDacbias();
public:
	CEdit m_ctrlAdcChanNum;
public:
	void BiasParamEnable(U08 isSet);
public:
	CString m_sPldType;
public:
	afx_msg void OnCbnSelchangeType();
public:
	CComboBox m_ctrlType;
public:
	CComboBox m_ctrlSpeedGrade;
public:
	void CreatePldType(void);
public:
	afx_msg void OnCbnSelchangeSpeed();
public:
	afx_msg void OnEnChangeVol();
public:
	afx_msg void OnEnChangePin();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnDestroy();
};

#endif // _ICRVK3DLG_H
