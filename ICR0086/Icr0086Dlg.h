#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0086Dlg dialog

class CIcr0086Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0086Dlg)

public:
	CIcr0086Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0086Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CSpinButtonCtrl m_ctrlSpinAdc;
	CSpinButtonCtrl m_ctrlSpinDdc;
	int m_AdcBits;
	int m_AdcEncoding;
	UINT m_AdcRateMax;
	UINT m_AdcRateMin;
	UINT m_AdcRange;
	UINT m_Gen;
	UINT m_NumOfAdc;
	UINT m_NumOfDdc;

	SUBMOD_INFO subInfo;

protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
