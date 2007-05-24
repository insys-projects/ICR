#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr008ADlg dialog

class CIcr008ADlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr008ADlg)

public:
	CIcr008ADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr008ADlg();

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
	BOOL m_QuadMod;
	BOOL m_ExtClk;
	UINT m_LpfCutoff;
	int m_OutResist;
};
