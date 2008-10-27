#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0081Dlg dialog

class CIcr0081Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0081Dlg)

public:
	CIcr0081Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0081Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	CSpinButtonCtrl	m_ctrlSpinAdc;
	int		m_AdcBits;
	int		m_AdcEncoding;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;
	UINT	m_NumOfAdc;
	UINT	m_PllRefGen;
	UINT	m_PllFreq;
	BOOL	m_IsRF;

	SUBMOD_INFO subInfo;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
