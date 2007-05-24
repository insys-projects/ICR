#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr008EDlg dialog

class CIcr008EDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr008EDlg)

public:
	CIcr008EDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr008EDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	int		m_AdcBits;
	int		m_AdcEncoding;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;
	int		m_NumOfAdc;

	int		m_DacBits;
	int		m_DacEncoding;
	UINT	m_DacRange;
	UINT	m_DacRateMax;
	UINT	m_DacRateMin;
	int		m_NumOfDac;

	SUBMOD_INFO subInfo;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
