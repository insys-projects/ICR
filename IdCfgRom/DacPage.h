#pragma once

#include "icr.h"

//#include "AdmIfPage.h"
#include "Adm2IfPage.h"
#include "afxwin.h"

#include "NumEdit.h"

UINT const MAX_DACCFG = 4;

// CDacPage dialog

class CDacPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDacPage)

public:
	CDacPage();
//	virtual ~CDacPage();

	void SetDataIntoDlg(PICR_CfgDac pDacCfg);
	void GetDataFromDlg(PICR_CfgDac pDacCfg, UINT num, UINT AdmNum);
	void SetMaxDac(int maxDac);

// Dialog Data
	enum { IDD = IDD_PP_DAC };
	CSpinButtonCtrl	m_ctrlSpinDacNum;
	int		m_DacEncoding;
	UINT	m_DacNum;
	UINT	m_DacAFCoff;
	UINT	m_DacHPFCoff;
	UINT	m_DacLPFCoff;
	UINT	m_DacRangeAF;
	UINT	m_DacRangePF;
	UINT	m_DacRateMax;
	UINT	m_DacRateMin;
	int		m_DacBits;

	UINT	m_AdmIfNum;

protected:
	ICR_CfgDac m_DacCfg[MAX_ADMIFCFG][MAX_DACCFG];
	int m_DacMax;

	void ChangeDacNum();
    CToolTipCtrl m_ToolTip;                         // The tooltip

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
//	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKillfocusDacnum();
	afx_msg void OnDeltaposSpindacnum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeDacencoding();
	afx_msg void OnKillfocusDacafcoff();
	afx_msg void OnKillfocusDachpfcoff();
	afx_msg void OnKillfocusDaclpfcoff();
	afx_msg void OnKillfocusDacrangeaf();
	afx_msg void OnKillfocusDacrangepf();
	afx_msg void OnKillfocusDacratemax();
	afx_msg void OnKillfocusDacratemin();
	afx_msg void OnSelchangeDacbits();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_btnDacAFSet;
	afx_msg void OnBnClickedAfset();
	CNumEdit m_edtDacRangeAF;
	CEdit m_edtDacAFCoff;
	CEdit m_edtDisableDacRangeAF;
	CEdit m_edtDisableDacAFCoff;
	CButton m_btnDacPFSet;
	afx_msg void OnBnClickedPfset();
	CEdit m_edtDacHPFCoff;
	CEdit m_edtDacLPFCoff;
	CEdit m_edtDacRangePF;
	CEdit m_edtDisableDacHPFCoff;
	CEdit m_edtDisableDacLPFCoff;
	CEdit m_edtDisableDacRangePF;
};
