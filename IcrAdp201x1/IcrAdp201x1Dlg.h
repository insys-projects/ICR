#pragma once


// CIcrAdp201x1Dlg dialog

class CIcrAdp201x1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAdp201x1Dlg)

public:
	CIcrAdp201x1Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAdp201x1Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

	CComboBox	m_ctrlPldSdramSize;
	CComboBox	m_ctrlCpuClock;
	CComboBox	m_ctrlCpuSdramSize;
	CComboBox	m_ctrlCpuFlashSize;

	UINT m_SysGen;
	BOOL m_isDds;
	int m_DdsType;
	BOOL m_isLLCU;
	int m_PldSdramSize;
	double m_MGTGen;
	BOOL m_isCPU;
	int m_CpuClk;
	int m_CpuSdramSize;
	int m_CpuFlashSize;
	double m_RefCpuGen;

	afx_msg void OnBnClickedDdsbe();
	afx_msg void OnBnClickedCpube();
};
