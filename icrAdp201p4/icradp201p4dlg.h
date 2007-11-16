#pragma once
#include "afxwin.h"


// CIcrAdp201P4Dlg dialog

class CIcrAdp201P4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAdp201P4Dlg)

public:
	CIcrAdp201P4Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAdp201P4Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CComboBox	m_ctrlSdramSize;
	CComboBox	m_ctrlPldType;
	CComboBox	m_ctrlPldRate;
	CComboBox	m_ctrlMaxCpuClock;

	double	m_BusClock;
	UINT	m_HostPldCnt;
	CString	m_strPldName;
	UINT	m_PldVolume;
	UINT	m_PldNum;
	UINT	m_PldPins;
//	CString	m_strSDRCON;
	
	CString	m_strSdramRAS;
	CString	m_strSdramCAS;
	CString	m_strSdramBANK;
	CString	m_strSdramCL;

	UINT	m_SdramSize;
	UINT	m_MaxCpuClock;
//	UINT	m_SDRCON;
	UINT	m_TypeOfLinks;
	UINT	m_CpuMask;
	UINT	m_SdramMask;
	UINT	m_PldRate;
	UINT	m_PldType;

	UINT	m_sdramRAS;
	UINT	m_sdramCAS;
	UINT	m_sdramBANK;
	UINT	m_sdramCL;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip

	void SetMaskOnCheckBoxes(UINT mask, int idx);
	void GetMaskOnCheckBoxes(UINT& mask, int idx);
	void SetPldName();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangePldrate();
	afx_msg void OnCbnSelchangePldtype();
	afx_msg void OnEnKillfocusPldpins();
	afx_msg void OnEnKillfocusPldvolume();
	afx_msg void OnBnClickedP1();
};
