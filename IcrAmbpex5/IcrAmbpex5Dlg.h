#pragma once


// CIcrAmbpex5Dlg dialog

class CIcrAmbpex5Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAmbpex5Dlg)

public:
	CIcrAmbpex5Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAmbpex5Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void SetSramVol();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	//afx_msg void OnDestroy();

	UINT m_SysGen;
	BOOL m_isDds;
	int m_DdsType;
	BOOL m_isSRAM;
	int m_SramChips;
	int m_SramSize;
	int m_SramBitsWidth;
	afx_msg void OnBnClickedDdsbe();
	afx_msg void OnBnClickedSrambe();

	int m_SfpCnt;
	double m_Gen5;
	CString	m_strSramVol;

	afx_msg void OnCbnSelchangeSramchips();
	afx_msg void OnCbnSelchangeSramsize();
	afx_msg void OnCbnSelchangeSrambitswidth();
};
