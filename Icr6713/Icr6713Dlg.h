#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Icr6713Dlg dialog

class Icr6713Dlg : public CDialog
{
	DECLARE_DYNAMIC(Icr6713Dlg)

public:
	Icr6713Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr6713Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	int	m_SdramSize;
	int	m_FlashSize;
	int	m_PldSramSize;

	CComboBox m_ctrlSdramSize;
	CComboBox m_ctrlFlashSize;
	CSpinButtonCtrl m_ctrlHostPldCnt;
	CSpinButtonCtrl m_ctrlPldNum;
	CComboBox m_ctrlPldSramSize;
	UINT m_HostPldCnt;
	UINT m_PldNum;

protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnEnKillfocusHostpldcnt();
	afx_msg void OnEnKillfocusPldnum();
	afx_msg void OnDeltaposSpinpldcnt(NMHDR *pNMHDR, LRESULT *pResult);
};
