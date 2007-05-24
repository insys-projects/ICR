#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"
//#include "afxcmn.h"

// CIcr0089Dlg dialog

class CIcr0089Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0089Dlg)

public:
	CIcr0089Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0089Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	CSpinButtonCtrl m_ctrlSpinAdc;
	int m_AdcBits;
	int m_AdcEncoding;
	UINT m_AdcRateMax;
	UINT m_AdcRateMin;
	UINT m_AdcRange;
	UINT m_Gen;
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
