#pragma once


// CIcrDsp101cP10Dlg dialog

class CIcrDsp101cP10Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrDsp101cP10Dlg)

public:
	CIcrDsp101cP10Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrDsp101cP10Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CComboBox	m_ctrlLinksType;
	CComboBox	m_ctrlSdramSize;
	CSpinButtonCtrl	m_ctrlSpinDioPldCnt;
	CSpinButtonCtrl	m_ctrlSpinPldCnt;
	CSpinButtonCtrl	m_ctrlSpinPldNum;
	CSpinButtonCtrl	m_ctrlSpinDioPldNum;
	CComboBox	m_ctrlPldType;
	CComboBox	m_ctrlPldRate;
	CComboBox	m_ctrlDioPldType;
	CComboBox	m_ctrlDioPldRate;
	CComboBox	m_ctrlMaxCpuClock;
	double	m_BusClock;
	CString	m_strDioPldName;
	UINT	m_DioPldCnt;
	UINT	m_DioPldNum;
	UINT	m_DioPldPins;
	UINT	m_DioPldVol;
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
	UINT	m_LinksJ4Mask;
	UINT	m_PldRate;
	UINT	m_PldType;
	UINT	m_DioPldRate;
	UINT	m_DioPldType;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip

	void SetMaskOnCheckBoxes(UINT mask, int idx);
	void GetMaskOnCheckBoxes(UINT& mask, int idx);
	void SetPldName();
	void SetDioPldName();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeDiopldrate();
	afx_msg void OnCbnSelchangeDiopldtype();
	afx_msg void OnCbnSelchangePldrate();
	afx_msg void OnCbnSelchangePldtype();
//	afx_msg void OnEnKillfocusPldnum();
	afx_msg void OnEnKillfocusPldpins();
	afx_msg void OnEnKillfocusPldvolume();
//	afx_msg void OnEnKillfocusDiopldnum();
	afx_msg void OnEnKillfocusDiopldpins();
	afx_msg void OnEnKillfocusDiopldvol();
};
