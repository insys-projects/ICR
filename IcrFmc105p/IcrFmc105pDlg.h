#pragma once


// CIcrFmc105pDlg dialog

class CIcrFmc105pDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrFmc105pDlg)

public:
	CIcrFmc105pDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrFmc105pDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void SetPldName();
	
#define LOCK	0
#define UNLOCK	1
	void LockUnlockDspWindows(USHORT wLock);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusPldpins();
	afx_msg void OnCbnSelchangePldtype();
	afx_msg void OnEnKillfocusPldvolume();
	afx_msg void OnCbnSelchangePldrate();

	afx_msg void OnEnKillfocusDspcnt();
	afx_msg void OnDeltaposSpindspcnt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusDspnum();

	UINT m_SysGen;
	BOOL m_isDds;
	int m_DdsType;
	afx_msg void OnBnClickedDdsbe();

	BOOL m_isSwitch;
	int m_SwitchType;
	UINT	m_AdrSwitch;
	afx_msg void OnBnClickedSwitchbe();

	int		m_Gen0Type;
	CComboBox m_ctrlGen0Type;
	UINT	m_AdrGen0;
	UINT	m_RefGen0;
	UINT	m_RefMaxGen0;
	afx_msg void OnCbnSelchangeGentype();

	UINT m_DspNodeCnt;
	CSpinButtonCtrl m_ctrlSpinDspNode;
	UINT m_DspNodeNum;
	CSpinButtonCtrl m_ctrlSpinDspNodeNum;
	UINT m_DspPldVolume;
	UINT m_DspPldPins;
	CComboBox m_ctrlDspPldType;
	CComboBox m_ctrlDspPldRate;
	int m_DspPldType;
	int m_DspPldRate;

	CString m_strDspPldName;
	BOOL m_isPio;
	int m_PioType;
	afx_msg void OnBnClickedPiobe();

	double m_Gen5;
	double m_Gen6;

};
