#pragma once


// CIcrAdp101pciDlg dialog

class CIcrAdp101pciDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAdp101pciDlg)

public:
	CIcrAdp101pciDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAdp101pciDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CComboBox	m_ctrlSdramSize;
	CComboBox	m_ctrlMaxCpuClock;
	CComboBox	m_ctrlPldRate;
	CComboBox	m_ctrlPldType;
	CSpinButtonCtrl	m_ctrlSpinPldCnt;
	CSpinButtonCtrl	m_ctrlSpinPldNum;
	CString	m_strPldName;
	UINT	m_PldNum;
	UINT	m_PldPins;
	UINT	m_PldVolume;
	UINT	m_HostPldCnt;
	double	m_BusClock;

	int		m_SdramSize;
	int		m_MaxCpuClock;
	int		m_PldRate;
	int		m_PldType;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	void SetPldName();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnEnKillfocusPldpins();
	afx_msg void OnCbnSelchangePldtype();
	afx_msg void OnEnKillfocusPldvolume();
	afx_msg void OnCbnSelchangePldrate();
};
