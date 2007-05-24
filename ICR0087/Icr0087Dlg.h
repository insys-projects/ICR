#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0087Dlg dialog

class CIcr0087Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0087Dlg)

public:
	CIcr0087Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0087Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CSpinButtonCtrl	m_ctrlSpinDac;
	int		m_DacBits;
	int		m_DacEncoding;
	UINT	m_DacRange;
	UINT	m_DacRateMax;
	UINT	m_Gen;
	UINT	m_NumOfDac;
	UINT	m_DacRateMin;
	int		m_FifoBitsWidth;
	int		m_FifoSize;

	SUBMOD_INFO subInfo;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeDacbits();
};
