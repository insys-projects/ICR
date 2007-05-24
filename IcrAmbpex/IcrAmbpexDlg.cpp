// IcrAmbpexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAmbpexApp.h"
#include "IcrAmbpexDlg.h"


// CIcrAmbpexDlg dialog

IMPLEMENT_DYNAMIC(CIcrAmbpexDlg, CDialog)

CIcrAmbpexDlg::CIcrAmbpexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAmbpexDlg::IDD, pParent)
	, m_SysGen(66000000)
	, m_isDds(FALSE)
	, m_DdsType(0)
	, m_isSRAM(FALSE)
	, m_SramChips(0)
	, m_SramSize(0)
	, m_SramBitsWidth(0)
{

}

CIcrAmbpexDlg::~CIcrAmbpexDlg()
{
}

void CIcrAmbpexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_Check(pDX, IDC_DDSBE, m_isDds);
	DDX_CBIndex(pDX, IDC_DDSTYPE, m_DdsType);
	DDX_Check(pDX, IDC_SRAMBE, m_isSRAM);
	DDX_CBIndex(pDX, IDC_SRAMCHIPS, m_SramChips);
	DDX_CBIndex(pDX, IDC_SRAMSIZE, m_SramSize);
	DDX_CBIndex(pDX, IDC_SRAMBITSWIDTH, m_SramBitsWidth);
}


BEGIN_MESSAGE_MAP(CIcrAmbpexDlg, CDialog)
	ON_BN_CLICKED(IDC_DDSBE, OnBnClickedDdsbe)
	ON_BN_CLICKED(IDC_SRAMBE, OnBnClickedSrambe)
END_MESSAGE_MAP()


// CIcrAmbpexDlg message handlers
BOOL CIcrAmbpexDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrAmbpexDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);


    m_ToolTip.AddTool(GetDlgItem(IDC_DDSBE), IDC_DDSBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_DDSTYPE), IDC_DDSTYPE);
	
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMBE), IDC_SRAMBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMCHIPS), IDC_SRAMCHIPS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMSIZE), IDC_SRAMSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMBITSWIDTH), IDC_SRAMBITSWIDTH);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);

	CWnd* pSramChips = (CWnd*)GetDlgItem(IDC_SRAMCHIPS);
	pSramChips->EnableWindow(m_isSRAM);
	CWnd* pSramSize = (CWnd*)GetDlgItem(IDC_SRAMSIZE);
	pSramSize->EnableWindow(m_isSRAM);
	CWnd* pSramWidth = (CWnd*)GetDlgItem(IDC_SRAMBITSWIDTH);
	pSramWidth->EnableWindow(m_isSRAM);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIcrAmbpexDlg::OnBnClickedDdsbe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);
}

void CIcrAmbpexDlg::OnBnClickedSrambe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pSramChips = (CWnd*)GetDlgItem(IDC_SRAMCHIPS);
	pSramChips->EnableWindow(m_isSRAM);
	CWnd* pSramSize = (CWnd*)GetDlgItem(IDC_SRAMSIZE);
	pSramSize->EnableWindow(m_isSRAM);
	CWnd* pSramWidth = (CWnd*)GetDlgItem(IDC_SRAMBITSWIDTH);
	pSramWidth->EnableWindow(m_isSRAM);
}
