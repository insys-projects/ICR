#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0094Dlg dialog

class CIcr0094Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0094Dlg)

public:
	CIcr0094Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0094Dlg();

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
	int		m_DacRange;
	int		m_GenType;
	UINT	m_GenAdr;
	UINT	m_GenRef;
	UINT	m_GenRefMax;
	int		m_SyntType;
	int		m_AttType;
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
	afx_msg void OnBnClickedButtonClearRange();
};
