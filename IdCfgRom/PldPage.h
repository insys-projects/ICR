#pragma once

#include "icr.h"

//#include "AdmIfPage.h"
#include "Adm2IfPage.h"

UINT const MAX_PLDCFG = 4;

// CPldPage dialog

class CPldPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPldPage)

public:
	CPldPage();
//	virtual ~CPldPage();

	void SetDataIntoDlg(PICR_CfgAdmPld pPldCfg);
	void GetDataFromDlg(PICR_CfgAdmPld pPldCfg, UINT num, UINT AdmNum);
	void SetMaxPld(int maxPld);

	void PageEnable(U08 isEnable);

// Dialog Data
	enum { IDD = IDD_PP_PLD };
	CSpinButtonCtrl	m_ctrlSpinPldNum;
	CComboBox	m_ctrlPldType;
	CComboBox	m_ctrlPldRate;
	CString	m_strPldName;
	UINT	m_PldNum;
	UINT	m_PldPins;
	UINT	m_PldVolume;

	UINT	m_AdmIfNum;

protected:
	ICR_CfgAdmPld m_PldCfg[MAX_ADMIFCFG][MAX_PLDCFG];
	int m_PldMax;

	void SetPldName();
	void ChangePldNum();

    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
//	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePldrate();
	afx_msg void OnSelchangePldtype();
	afx_msg void OnDeltaposSpinpldnum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusPldnum();
	afx_msg void OnKillfocusPldpins();
	afx_msg void OnKillfocusPldvolume();
//	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
