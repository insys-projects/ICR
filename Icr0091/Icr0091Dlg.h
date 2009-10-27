#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0091Dlg dialog

class CIcr0091Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0091Dlg)

public:
	CIcr0091Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0091Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	CSpinButtonCtrl	m_ctrlSpinAdc;
	int		m_AdcBits;
	int		m_AdcEncoding;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;
	UINT	m_NumOfAdc;
	int		m_SubType;
	UINT	m_RefGen0;
	UINT	m_RefGen1;
	UINT	m_RefGen1Min;
	UINT	m_RefGen1Max;
	int		m_RefGen1Type;
	int		m_RefGen2Type;
	UINT	m_LpfPassBand;
	UINT	m_Range0;
	UINT	m_Range1;
	UINT	m_Range2;
	UINT	m_Range3;

	SUBMOD_INFO subInfo;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
