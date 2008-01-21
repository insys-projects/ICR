#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Icr64Z2ADlg dialog

class Icr64Z2ADlg : public CDialog
{
	DECLARE_DYNAMIC(Icr64Z2ADlg)

public:
	Icr64Z2ADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr64Z2ADlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	int	m_MaxCpuClock;
	int	m_SdramASize;
	int	m_SdramBSize;
	int	m_FlashSize;
	int	m_SbsramSize;
	int	m_PldType;
	int	m_PldPins;
	int	m_PldRate;

	CComboBox m_ctrlMaxCpuClock;
	CComboBox m_ctrlSdramASize;
	CComboBox m_ctrlSdramBSize;
	CComboBox m_ctrlFlashSize;
	CComboBox m_ctrlSbsramSize;
	CComboBox m_ctrlPldType;
	CSpinButtonCtrl m_ctrlHostPldCnt;
	CSpinButtonCtrl m_ctrlPldNum;

	CString m_strPldName;
	UINT m_HostPldCnt;
	UINT m_PldNum;
	UINT m_PldVolume;

protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	void SetPldName();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangePldtype();
	afx_msg void OnEnKillfocusPldvolume();
	afx_msg void OnDeltaposSpinpldcnt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusHostpldcnt();
	afx_msg void OnEnKillfocusPldnum();
};
