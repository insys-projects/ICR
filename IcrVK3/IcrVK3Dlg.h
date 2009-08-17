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
	U08 m_bDacBiasBits;
	U08 m_isDacBias;
	U08 m_bAdcChanNum;
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
	U32 m_nDacChanNum;
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
	CComboBox		m_ctrlDdrModuleNum;
	CComboBox		m_ctrlOutR;
	CComboBox		m_ctrlMaxfreqSampl;
	CComboBox		m_ctrlInpR;
	CComboBox		m_ctrlSpeedGrade;
	CButton			m_ctrlDacBiasSet;
	CButton			m_ctrlAdcInpAdd;
	CButton			m_ctrlTuner;
	CString			m_sPldType;
	CString			m_sType;
	CButton			m_ctrlSelectorSinch;
	CNumEdit		m_ctrlSysGen;
	CNumEdit		m_ctrlRefGen;
	CEdit			m_ctrlDacChanNum;
	CEdit			m_ctrlDacOutNum;
	CEdit			m_ctrlDacBits;
	CEdit			m_ctrlDacBiasBits;
	CEdit			m_ctrlAdcTypeF;
	CEdit			m_ctrlAdcInpNum;
	CEdit			m_ctrlAdcBits;
	CEdit			m_ctrlAdcChanNum;
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
	void CreatePldType(void);
	afx_msg void OnBnClickedDacset();
	afx_msg void OnEnChangeDacchannum();
	afx_msg void OnCbnSelchangeOutampl();
	afx_msg void OnEnChangeAdcchannum();
	afx_msg void OnBnClickedDacbias();
	afx_msg void OnCbnSelchangeType();
	afx_msg void OnCbnSelchangeSpeed();
	afx_msg void OnEnChangeVol();
	afx_msg void OnEnChangePin();
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeSysfreq();
	afx_msg void OnEnUpdateSysfreq();
};

#endif // _ICRVK3DLG_H
