#pragma once

#include "utypes.h"
#include "afxcmn.h"
#include "afxwin.h"

// Icr64Z5Dlg dialog

class Icr64Z5Dlg : public CDialog
{
	DECLARE_DYNAMIC(Icr64Z5Dlg)

public:
	Icr64Z5Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr64Z5Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CToolTipCtrl m_ToolTip;

	DECLARE_MESSAGE_MAP()
public:
	U08 m_bCpuName;
	U16 m_wMaxCpuClock;
	U16 m_wSizeOfDDR2;
	U32 m_wSizeOfFlash;
	U08 m_isSetEMAC;
	U08 m_bTypeSRIO;
	virtual BOOL OnInitDialog();
	CComboBox m_ctrlCpuName;
	CComboBox m_ctrlMaxCpuClock;
	CComboBox m_ctrlSizeOfDDR2;
	CComboBox m_ctrlSizeOfFlash;
	CButton m_ctrlSetEMAC;
	CComboBox m_ctrlTypeSRIO;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
