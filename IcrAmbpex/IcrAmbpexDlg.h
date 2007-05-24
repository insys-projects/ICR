#pragma once


// CIcrAmbpexDlg dialog

class CIcrAmbpexDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAmbpexDlg)

public:
	CIcrAmbpexDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAmbpexDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	UINT m_SysGen;
	BOOL m_isDds;
	int m_DdsType;
	BOOL m_isSRAM;
	int m_SramChips;
	int m_SramSize;
	int m_SramBitsWidth;
	afx_msg void OnBnClickedDdsbe();
	afx_msg void OnBnClickedSrambe();
};
