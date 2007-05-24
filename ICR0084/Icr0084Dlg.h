#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0084Dlg dialog

class CIcr0084Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0084Dlg)

public:
	CIcr0084Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0084Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CSpinButtonCtrl	m_ctrlSpinAdc;
	int		m_AdcBits;
	UINT	m_NumOfAdc;
	int		m_AdcEncoding;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;

	SUBMOD_INFO subInfo;

protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
