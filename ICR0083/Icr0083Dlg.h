#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0083Dlg dialog

class CIcr0083Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0083Dlg)

public:
	CIcr0083Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0083Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CSpinButtonCtrl	m_ctrlSpinAdc;
	int		m_AdcBits;
	int		m_AdcEncoding;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;
	UINT	m_NumOfAdc;
	UINT	m_Gen1;
	UINT	m_Gen2;
	UINT	m_Gen3;

	SUBMOD_INFO subInfo;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
