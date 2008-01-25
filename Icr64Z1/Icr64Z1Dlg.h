#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Icr64Z1Dlg dialog

class Icr64Z1Dlg : public CDialog
{
	DECLARE_DYNAMIC(Icr64Z1Dlg)

public:
	Icr64Z1Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr64Z1Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	int	m_MaxCpuClock;
	int	m_SdramASize;
	int	m_SdramBSize;
	int	m_FlashSize;
	int m_CpuName;

	CComboBox m_ctrlMaxCpuClock;
	CComboBox m_ctrlSdramASize;
	CComboBox m_ctrlSdramBSize;
	CComboBox m_ctrlFlashSize;
	CComboBox m_ctrlCpuName;

protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
