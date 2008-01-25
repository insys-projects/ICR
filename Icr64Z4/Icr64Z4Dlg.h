#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Icr64Z4Dlg dialog

class Icr64Z4Dlg : public CDialog
{
	DECLARE_DYNAMIC(Icr64Z4Dlg)

public:
	Icr64Z4Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr64Z4Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	int	m_CpuCnt;
	int	m_MaxCpuClock;
	int	m_FlashCnt;

	CComboBox m_ctrlCpuCnt;
	CComboBox m_ctrlMaxCpuClock;
	CComboBox m_ctrlFlashCnt;

protected:
	CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeCpucnt();
};
