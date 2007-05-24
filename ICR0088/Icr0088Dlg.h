#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"

// CIcr0088Dlg dialog

class CIcr0088Dlg : public CDialog
{
	DECLARE_DYNAMIC(CIcr0088Dlg)

public:
	CIcr0088Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcr0088Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };
	int		m_BufType;

	SUBMOD_INFO subInfo;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
