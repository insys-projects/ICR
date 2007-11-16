#pragma once


// CIcrAdp101cP7Dlg dialog

class CIcrAdp101cP7Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAdp101cP7Dlg)

public:
	CIcrAdp101cP7Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAdp101cP7Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CComboBox	m_ctrlLinksType;
	CComboBox	m_ctrlSdramSize;
	CSpinButtonCtrl	m_ctrlSpinPldCnt;
	CSpinButtonCtrl	m_ctrlSpinPldNum;
	CComboBox	m_ctrlPldType;
	CComboBox	m_ctrlPldRate;
	CComboBox	m_ctrlMaxCpuClock;
	CComboBox	m_ctrlX5;
	CComboBox	m_ctrlX6;

	double	m_BusClock;
	UINT	m_HostPldCnt;
	CString	m_strPldName;
	UINT	m_PldVolume;
	UINT	m_PldNum;
	UINT	m_PldPins;
	CString	m_strSDRCON;

	UINT	m_SdramSize;
	UINT	m_MaxCpuClock;
	UINT	m_SDRCON;
	UINT	m_TypeOfLinks;
	UINT	m_CpuMask;
	UINT	m_SdramMask;
	UINT	m_PldRate;
	UINT	m_PldType;

	UINT	m_X5;
	UINT	m_X6;

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
