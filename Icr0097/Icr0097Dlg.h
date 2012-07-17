#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0097Dlg dialog

class CIcr0097Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0097Dlg)

public:
	CIcr0097Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0097Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	CSpinButtonCtrl	m_ctrlSpinAdc;
	int		m_AdcBits;
	int		m_AdcEncoding;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;
	UINT	m_NumOfAdc;

	int		m_AdcType;
	int		m_DacType;
	UINT	m_DacRange;
	int		m_GenType;
	DWORD	m_GenAdr;
	UINT	m_GenRef;
	UINT	m_GenRefMax;

	SUBMOD_INFO subInfo;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnBnClickedButtonCleardeviation();
};
