// Icr008CDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr008CApp.h"
//#include "Icr008CDlg.h"


// CIcr008CDlg dialog

IMPLEMENT_DYNAMIC(CIcr008CDlg, CPropertyPage)
CIcr008CDlg::CIcr008CDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr008CDlg::IDD, pParent)
	, m_Gen(10000000)
	, m_IsOxco(TRUE)
	, m_IsDblFreq(TRUE)
	, m_LpfCutoff(90000000)
	, m_ExtClk(TRUE)
	, m_IsStrobe(FALSE)
	, m_MaxAmpl(500)
{
}

CIcr008CDlg::~CIcr008CDlg()
{
}

void CIcr008CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GEN, m_Gen);
	DDX_Check(pDX, IDC_OXCO, m_IsOxco);
	DDX_Check(pDX, IDC_FREQDBL, m_IsDblFreq);
	DDX_Text(pDX, IDC_DACLPFCOFF, m_LpfCutoff);
	DDX_Check(pDX, IDC_EXTCLK, m_ExtClk);
	DDX_Check(pDX, IDC_STROBE, m_IsStrobe);
	DDX_Text(pDX, IDC_DACRANGE, m_MaxAmpl);
}


BEGIN_MESSAGE_MAP(CIcr008CDlg, CDialog)
END_MESSAGE_MAP()

// CIcr008CDlg message handlers

BOOL CIcr008CDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString Title;
	GetWindowText(Title);
	CString Name = subInfo.sName;
	Title = Name + _T(" ") + Title;
	SetWindowText(Title);

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_GEN), IDC_GEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_OXCO), IDC_OXCO);
    m_ToolTip.AddTool(GetDlgItem(IDC_FREQDBL), IDC_FREQDBL);
    m_ToolTip.AddTool(GetDlgItem(IDC_EXTCLK), IDC_EXTCLK);
    m_ToolTip.AddTool(GetDlgItem(IDC_STROBE), IDC_STROBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACLPFCOFF), IDC_DACLPFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGE), IDC_DACRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcr008CDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}
