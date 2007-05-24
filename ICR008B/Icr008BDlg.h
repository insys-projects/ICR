#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr008BDlg dialog

class CIcr008BDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr008BDlg)

public:
	CIcr008BDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr008BDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CSpinButtonCtrl m_ctrlSpinAdc;
	UINT m_AdcRateMax;
	UINT m_AdcRateMin;
	UINT m_AdcRange;
	UINT m_MainGen;
	UINT m_MaxFreqVco;
	UINT m_MinFreqVco;
	UINT m_NumOfAdc;

	SUBMOD_INFO subInfo;


protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
