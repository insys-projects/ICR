#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr008CDlg dialog

class CIcr008CDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr008CDlg)

public:
	CIcr008CDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr008CDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	UINT m_Gen;
	BOOL m_IsOxco;
	BOOL m_IsDblFreq;
	UINT m_LpfCutoff;
	BOOL m_ExtClk;
	BOOL m_IsStrobe;
	UINT m_MaxAmpl;

	SUBMOD_INFO subInfo;


protected:
    CToolTipCtrl m_ToolTip;								// The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
