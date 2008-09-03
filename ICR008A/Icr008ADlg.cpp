// Icr0087Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr008AApp.h"
#include "Icr008ADlg.h"


// CIcr008ADlg dialog

IMPLEMENT_DYNAMIC(CIcr008ADlg, CDialog)
CIcr008ADlg::CIcr008ADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr008ADlg::IDD, pParent)
	, m_QuadMod(FALSE)
	, m_ExtClk(FALSE)
	, m_LpfCutoff(0)
	, m_OutResist(0)
{
	m_DacBits = 2;
	m_DacEncoding = 1;
	m_DacRange = 2500;
	m_DacRateMax = 1000000;
	m_Gen = 120000000;
	m_NumOfDac = 0;
	m_DacRateMin = 0;
	m_FifoBitsWidth = -1;
	m_FifoSize = -1;
	m_QuadModType = 0;
}

CIcr008ADlg::~CIcr008ADlg()
{
}

void CIcr008ADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINDAC, m_ctrlSpinDac);
	DDX_Text(pDX, IDC_DACRANGE, m_DacRange);
	DDX_Text(pDX, IDC_DACRATEMAX, m_DacRateMax);
	DDX_Text(pDX, IDC_GEN, m_Gen);
	DDX_Text(pDX, IDC_NUMOFDAC, m_NumOfDac);
	DDV_MinMaxUInt(pDX, m_NumOfDac, 1, 32);
	DDX_Text(pDX, IDC_DACRATEMIN, m_DacRateMin);
	DDX_CBIndex(pDX, IDC_DACFIFOSIZE, m_FifoSize);
	DDX_Check(pDX, IDC_QUADMOD, m_QuadMod);
	DDX_Check(pDX, IDC_EXTCLK, m_ExtClk);
	DDX_Text(pDX, IDC_DACLPFCOFF, m_LpfCutoff);
	DDX_CBIndex(pDX, IDC_DACOUTRESIST, m_OutResist);
	DDX_Control(pDX, IDC_QUADMODTYPE, m_ctrlQuadModType);
}


BEGIN_MESSAGE_MAP(CIcr008ADlg, CDialog)
	ON_BN_CLICKED(IDC_QUADMOD, &CIcr008ADlg::OnBnClickedQuadmod)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CIcr008ADlg message handlers

BOOL CIcr008ADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinDac.SetRange(0, 32);

//	CString Title = subInfo.Name;
//	Title += _T(" Configuration");
//	SetWindowText(Title);
	CString Title;
	GetWindowText(Title);
	CString Name = subInfo.sName;
	Title = Name + _T(" ") + Title;
	SetWindowText(Title);
	
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMAX), IDC_DACRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMIN), IDC_DACRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGE), IDC_DACRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_GEN), IDC_GEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFDAC), IDC_NUMOFDAC);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACFIFOSIZE), IDC_DACFIFOSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_QUADMOD), IDC_QUADMOD);
	m_ToolTip.AddTool(GetDlgItem(IDC_QUADMODTYPE), IDC_QUADMODTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_EXTCLK), IDC_EXTCLK);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACLPFCOFF), IDC_DACLPFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACOUTRESIST), IDC_DACOUTRESIST);
	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	m_ctrlQuadModType.SetCurSel(0);
	
	if( m_QuadModType > 0 )
	{
		m_QuadMod = 1;
		m_ctrlQuadModType.EnableWindow(TRUE);
		m_ctrlQuadModType.SetCurSel(m_QuadModType-1);
	}
	else 
	{
		m_QuadMod = 0;
		m_ctrlQuadModType.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcr008ADlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CIcr008ADlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	UpdateData(TRUE);
	if( m_QuadMod )
		m_QuadModType = m_ctrlQuadModType.GetCurSel() + 1;
	else
		m_QuadModType = 0;
}

void CIcr008ADlg::OnBnClickedQuadmod()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_QuadMod == 0 )
		m_ctrlQuadModType.EnableWindow(FALSE);
	else if ( m_QuadMod == 1 )
		m_ctrlQuadModType.EnableWindow(TRUE);
}
