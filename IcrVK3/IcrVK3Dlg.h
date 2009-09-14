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
	double m_dSysGen;
	double m_dRefGen;
	U08 m_bAdcChanNum;
	U08 m_bDacBiasBits;
	U08 m_isDacBias;
	U08 m_bAdcInpNum;
	CString m_sAdcTypeF;
	U32 m_nAdcBiasRange;
	U08 m_bAdcBits;
	U32 m_nMaxfreqSampl;
	U32 m_nInpAmplRange;
	U32 m_nInpR;
	U08 m_isAdcInpAdd;
	U08 m_isTuner;
	U08 m_isSelectorSinch;
	U08 m_bDacChanNum;
	U08 m_bDacOutNum;
	CString m_sDacTypeF;
	U32 m_nDacBiasRange;
	U08 m_bDacBits;
	U32 m_nOutAmplRange;
	U32 m_nOutR;
	U08 m_bType;
	U32 m_nVolume;
	U08 m_bSpeedGrade;
	U32 m_nPins;

	CToolTipCtrl	m_ToolTip;
	CComboBox		m_ctrlOutR;
	CComboBox		m_ctrlInpR;
	CButton			m_ctrlDacBiasSet;
	CButton			m_ctrlAdcInpAdd;
	CButton			m_ctrlTuner;
	CButton			m_ctrlSelectorSinch;
	CNumEdit		m_ctrlSysGen;
	CNumEdit		m_ctrlRefGen;
	CEdit			m_ctrlDacOutNum;
	CEdit			m_ctrlDacBits;
	CEdit			m_ctrlDacBiasBits;
	CEdit			m_ctrlAdcTypeF;
	CEdit			m_ctrlAdcInpNum;
	CEdit			m_ctrlAdcBits;
	CEdit			m_ctrlDacBiasRange;
	CEdit			m_ctrlOutAmplRange;
	CEdit			m_ctrlAdcBiasRange;
	CEdit			m_ctrlInpAmplRange;
	CEdit			m_ctrlDacTypeF;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DacParamEnable(U08 isSet = TRUE);
	void AdcParamEnable(U08 isSet);
	void BiasParamEnable(U08 isSet);
	afx_msg void OnBnClickedDacset();
	afx_msg void OnEnChangeDacchannum();
	afx_msg void OnCbnSelchangeOutampl();
	afx_msg void OnBnClickedDacbias();
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeSysfreq();
	afx_msg void OnEnUpdateSysfreq();
	afx_msg void OnBnClickedIsadc();
public:
	CButton m_ctrlAdcChanNum;
public:
	CButton m_ctrlDacChanNum;
public:
	afx_msg void OnBnClickedIsdac();
public:
	CButton m_ctrlDdrModuleNum;
public:
	afx_msg void OnBnClickedDdrnum();
public:
	U32 m_nDacMaxfreqSampl;
public:
	CEdit m_ctrlDacMaxfreqSampl;
public:
	CEdit m_ctrlAdcMaxfreqSampl;
public:
	U32 m_nAdcMaxfreqSampl;
public:
	CComboBox m_ctrlPldType;
public:
	afx_msg void OnCbnSelchangePldtype();
};

#endif // _ICRVK3DLG_H
