#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0090Dlg dialog

class CIcr0090Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0090Dlg)

public:
	CIcr0090Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0090Dlg();

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
	UINT	m_Range0;
	UINT	m_Range1;
	UINT	m_Range2;
	UINT	m_Range3;
	int		m_ClrDeviations;
	int		m_awRangeDeviation[2][2][2][4];	// отклонение ШП от номинала (разы) (default 10000)
										// [тип входа][Rвх/ФНЧ][номер АЦП][номер ШП]
	int		m_awBiasDeviation[2][2][2][4];	// отклонения смещения нуля (разы) (default 0)
										// [тип входа][Rвх/ФНЧ][номер АЦП][номер ШП]

	SUBMOD_INFO subInfo;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCleardeviation();
};
