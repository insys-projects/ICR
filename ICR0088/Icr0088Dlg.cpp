// Icr0088Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0088App.h"
#include "Icr0088Dlg.h"

// CIcr0088Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0088Dlg, CDialog)
CIcr0088Dlg::CIcr0088Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0088Dlg::IDD, pParent)
{
	m_BufType = 0;
}

CIcr0088Dlg::~CIcr0088Dlg()
{
}

void CIcr0088Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_BUFTYPE, m_BufType);
}


BEGIN_MESSAGE_MAP(CIcr0088Dlg, CDialog)
END_MESSAGE_MAP()


// CIcr0088Dlg message handlers

BOOL CIcr0088Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString Title;
	GetWindowText(Title);
	CString Name = subInfo.Name;
	Title = Name + _T(" ") + Title;
	SetWindowText(Title);
	
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_BUFTYPE), IDC_BUFTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcr0088Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}
