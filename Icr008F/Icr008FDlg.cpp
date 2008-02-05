// Icr008FDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr008FApp.h"
#include "Icr008FDlg.h"


// Icr008FDlg dialog

IMPLEMENT_DYNAMIC(Icr008FDlg, CDialog)

Icr008FDlg::Icr008FDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr008FDlg::IDD, pParent)
	, m_OscFreq(0)
	, m_IsGen(FALSE)
	, m_GenTune(FALSE)
	, m_QuadMod(FALSE)
	, m_ExtClk(FALSE)
	, m_OutResist(0)
	, m_OutCasMod(0)
	, m_IsPll(FALSE)
{
	m_DacRateMax = 1000000;
	m_DacRateMin = 0;
	m_Gen = 120000000;
	m_NumOfDac = 0;
	m_DacRange = 2500;
	m_LpfCutoff = 0;
	m_OscFreq = 400;
	m_OutCasMod = 0;
	m_QuadModType = 0;
}

Icr008FDlg::~Icr008FDlg()
{
}

void Icr008FDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTCASMOD, m_ctrlOutCasMod);
	DDX_Check(pDX, IDC_ISPLL, m_IsPll);
	DDX_Check(pDX, IDC_ISGEN, m_IsGen);
	DDX_Check(pDX, IDC_GENTUNE, m_GenTune);
	DDX_Control(pDX, IDC_SPINDAC, m_ctrlSpinDac);
	DDX_Control(pDX, IDC_DACOUTRESIST, m_ctrlDacOutResist);
	DDX_Control(pDX, IDC_QUADMODTYPE, m_ctrlQuadModType);
	DDX_Check(pDX, IDC_QUADMOD, m_QuadMod);
	DDX_Check(pDX, IDC_EXTCLK, m_ExtClk);
	DDX_CBIndex(pDX, IDC_DACOUTRESIST, m_OutResist);
	DDX_CBIndex(pDX, IDC_OUTCASMOD, m_OutCasMod);
	DDX_Text(pDX, IDC_DACRATEMIN, m_DacRateMin);
	DDX_Text(pDX, IDC_DACRATEMAX, m_DacRateMax);
	DDX_Text(pDX, IDC_GEN, m_Gen);
	DDX_Text(pDX, IDC_NUMOFDAC, m_NumOfDac);
	DDX_Text(pDX, IDC_DACRANGE, m_DacRange);
	DDX_Text(pDX, IDC_DACLPFCOFF, m_LpfCutoff);
	DDX_Text(pDX, IDC_OSCFREQ, m_OscFreq);
}


BEGIN_MESSAGE_MAP(Icr008FDlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_QUADMOD, &Icr008FDlg::OnBnClickedQuadmod)
	ON_BN_CLICKED(IDC_ISGEN, &Icr008FDlg::OnBnClickedIsgen)
	ON_BN_CLICKED(IDC_ISPLL, &Icr008FDlg::OnBnClickedIspll)
END_MESSAGE_MAP()


// Icr008FDlg message handlers

BOOL Icr008FDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinDac.SetRange(0, 32);

//	CString Title = subInfo.Name;
//	Title += _T(" Configuration");
//	SetWindowText(Title);
	CString Title;
	GetWindowText(Title);
	CString Name = subInfo.Name;
	Title = Name + _T(" ") + Title;
	SetWindowText(Title);
	
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMAX), IDC_DACRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMIN), IDC_DACRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGE), IDC_DACRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_GEN), IDC_GEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFDAC), IDC_NUMOFDAC);
    m_ToolTip.AddTool(GetDlgItem(IDC_QUADMOD), IDC_QUADMOD);
	m_ToolTip.AddTool(GetDlgItem(IDC_QUADMODTYPE), IDC_QUADMODTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_EXTCLK), IDC_EXTCLK);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACLPFCOFF), IDC_DACLPFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACOUTRESIST), IDC_DACOUTRESIST);
	m_ToolTip.AddTool(GetDlgItem(IDC_ISGEN), IDC_ISGEN);
	m_ToolTip.AddTool(GetDlgItem(IDC_GENTUNE), IDC_GENTUNE);
	m_ToolTip.AddTool(GetDlgItem(IDC_OSCFREQ), IDC_OSCFREQ1);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTCASMOD), IDC_OUTCASMOD);
	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	m_ctrlQuadModType.SetCurSel(m_QuadModType);
	
	if( m_IsGen == 0 )
	{
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(FALSE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(FALSE);
	}
	else if ( m_IsGen == 1 )
	{
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(TRUE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(TRUE);
	}
	if( m_QuadMod == 0 )
		m_ctrlQuadModType.EnableWindow(FALSE);
	else if ( m_QuadMod == 1 )
		m_ctrlQuadModType.EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr008FDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr008FDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	m_QuadModType = m_ctrlQuadModType.GetCurSel();
}

void Icr008FDlg::OnBnClickedQuadmod()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_QuadMod == 0 )
		m_ctrlQuadModType.EnableWindow(FALSE);
	else if ( m_QuadMod == 1 )
		m_ctrlQuadModType.EnableWindow(TRUE);
}

void Icr008FDlg::OnBnClickedIsgen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_IsGen == 0 )
	{
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(FALSE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(FALSE);
	}
	else if ( m_IsGen == 1 )
	{
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(TRUE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(TRUE);
	}
}

void Icr008FDlg::OnBnClickedIspll()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_IsGen == 0 )
	{
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(FALSE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(FALSE);
	}
	else if ( m_IsGen == 1 )
	{
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(TRUE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(TRUE);
	}
}
