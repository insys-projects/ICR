#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CIcrSync8chPCIDlg dialog

class CIcrSync8chPCIDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrSync8chPCIDlg)

public:
	CIcrSync8chPCIDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrSync8chPCIDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	UINT m_SysGen;
	UINT m_Gen1;
	UINT m_Gen2;
	UINT m_OcxoGen;
	UINT m_PllFreq;

	int		m_ClkChanCnt;
	int		m_StrbChanCnt;
	BOOL	m_ClkE;
	BOOL	m_ClkF;
	BOOL	m_StrboA;
	BOOL	m_StrboB;
	BOOL	m_StrboD;
	BOOL	m_Sync;
	int		m_IsLF;
};
