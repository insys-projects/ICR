#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Icr6203Dlg dialog

class Icr6203Dlg : public CDialog
{
	DECLARE_DYNAMIC(Icr6203Dlg)

public:
	Icr6203Dlg(CWnd* pParent = NULL);
	virtual ~Icr6203Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	// Controls (переменные контроля объектами окна)
	CComboBox m_ctrlSdramSize;
	CComboBox m_ctrlDpramSize;
	CComboBox m_ctrlSsramSize;
	CComboBox m_ctrlFifoSize;
	CComboBox m_ctrlFifoWidth;
	CSpinButtonCtrl m_ctrlFifoCnt;
	CSpinButtonCtrl m_ctrlFifoNum;

	// Text-dialog exchanging variables (переменные обмена текстом с дилоговым окном)
	UINT m_MaxCpuClock;
	UINT m_FifoCnt;
	UINT m_FifoNum;

	// Controls associated variables (переменные, ассоциированные с переменными контроля)
	UINT	m_SdramSize;
	UINT	m_DpramSize;
	UINT	m_SsramSize;
	UINT	m_FifoSize;
	UINT	m_FifoWidth;

protected:
	CToolTipCtrl m_ToolTip;
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnDeltaposSpinfifocnt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusFifocnt();
	afx_msg void OnEnKillfocusFifonum();
};
