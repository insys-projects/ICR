// Icr0092Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0092App.h"
#include "Icr0092Dlg.h"


// Icr0092Dlg dialog

IMPLEMENT_DYNAMIC(Icr0092Dlg, CDialog)

Icr0092Dlg::Icr0092Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr0092Dlg::IDD, pParent)
	, m_bNumOfDac(0)
	, m_nDacRateMin(0)
	, m_nDacRateMax(400000000)
	, m_isPll(0)
	, m_nOscFreq(400000000)



	, m_isGen(0)
	, m_sGenPrec(_T(""))
	, m_nGen(0)
	, m_isFreqTune(0)
	, m_nDacRange(2500)
	, m_nLpfCutoff(0)
	, m_sOutResist(_T(""))

	, m_QuadMod(FALSE)
	, m_ExtClk(FALSE)
	, m_isClkOut(1)
	, m_isIndustrial(0)
{
	m_QuadModType = 0;
}

Icr0092Dlg::~Icr0092Dlg()
{
}

void Icr0092Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text (pDX, IDC_NUMOFDAC,   m_bNumOfDac);
	DDX_Text (pDX, IDC_DACRATEMIN, m_nDacRateMin);
	DDX_Text (pDX, IDC_DACRATEMAX, m_nDacRateMax);
	DDX_Check(pDX, IDC_ISPLL,      m_isPll);
	DDX_Text (pDX, IDC_OSCFREQ,    m_nOscFreq);

	DDX_Check(pDX, IDC_CLKOUT,     m_isClkOut);
	DDX_Check(pDX, IDC_INDUSTRIAL, m_isIndustrial);

	DDX_Check(pDX, IDC_ISGEN, m_isGen);
	DDX_Check(pDX, IDC_GENTUNE, m_isFreqTune);
	DDX_Control(pDX, IDC_SPINDAC, m_ctrlSpinDac);
	DDX_Control(pDX, IDC_DACOUTRESIST, m_ctrlDacOutResist);
	DDX_Control(pDX, IDC_QUADMODTYPE, m_ctrlQuadModType);
	DDX_Check(pDX, IDC_QUADMOD, m_QuadMod);
	DDX_Check(pDX, IDC_EXTCLK, m_ExtClk);
	DDX_CBString(pDX, IDC_DACOUTRESIST, m_sOutResist);

	DDX_Text(pDX, IDC_GEN, m_nGen);
	DDX_Text(pDX, IDC_DACRANGE, m_nDacRange);
	DDX_Text(pDX, IDC_DACLPFCOFF, m_nLpfCutoff);

	DDX_Control(pDX, IDC_GEN_PREC, m_ctrlGenPrec);
	DDX_Text(pDX, IDC_GEN_PREC, m_sGenPrec);
}


BEGIN_MESSAGE_MAP(Icr0092Dlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_QUADMOD, &Icr0092Dlg::OnBnClickedQuadmod)
	ON_BN_CLICKED(IDC_ISGEN, &Icr0092Dlg::OnBnClickedIsgen)
//	ON_BN_CLICKED(IDC_ISPLL, &Icr0092Dlg::OnBnClickedIspll)
//	ON_EN_KILLFOCUS(IDC_OSCFREQ, &Icr0092Dlg::OnEnKillfocusOscfreq)
	ON_EN_KILLFOCUS(IDC_GEN, &Icr0092Dlg::OnEnKillfocusGen)
	ON_BN_CLICKED(IDC_ISPLL, &Icr0092Dlg::OnBnClickedIspll)
END_MESSAGE_MAP()


// Icr0092Dlg message handlers

BOOL Icr0092Dlg::OnInitDialog()
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
    m_ToolTip.AddTool(GetDlgItem(IDC_QUADMOD), IDC_QUADMOD);
	m_ToolTip.AddTool(GetDlgItem(IDC_QUADMODTYPE), IDC_QUADMODTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_EXTCLK), IDC_EXTCLK);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACLPFCOFF), IDC_DACLPFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACOUTRESIST), IDC_DACOUTRESIST);
	m_ToolTip.AddTool(GetDlgItem(IDC_ISGEN), IDC_ISGEN);
	m_ToolTip.AddTool(GetDlgItem(IDC_GENTUNE), IDC_GENTUNE);
	m_ToolTip.AddTool(GetDlgItem(IDC_OSCFREQ), IDC_OSCFREQ1);
	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);
	m_ToolTip.AddTool(GetDlgItem(IDC_GEN_PREC), IDC_GEN_PREC);

 	if ( m_nOscFreq > 0 )
	{
 		m_isPll = 1;
		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
		pPll->EnableWindow(TRUE);
	}
	else
	{
		m_isPll = 0;	
		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
		pPll->EnableWindow(FALSE);
	}


		CWnd* pIsGen = (CWnd*)GetDlgItem(IDC_ISGEN);
		pIsGen->EnableWindow(TRUE);
		if( m_isGen == 1 )
		{
			CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
			pGen->EnableWindow(TRUE);
			CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
			pGenTune->EnableWindow(TRUE);
			CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
			pGenPrec->EnableWindow(TRUE);
		}
// 	}
// 	else
// 	{
// 		m_isPll = 0;
// 		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
// 		pPll->EnableWindow(FALSE);
// 		CWnd* pIsGen = (CWnd*)GetDlgItem(IDC_ISGEN);
// 		pIsGen->EnableWindow(FALSE);
// 		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
// 		pGen->EnableWindow(FALSE);
// 		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
// 		pGenTune->EnableWindow(FALSE);
// 		CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
// 		pGenPrec->EnableWindow(FALSE);
// 	}

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
	if( m_nGen > 0 )
	{
		m_isGen = 1;
	}
	else
	{
		m_isGen = 0;
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(FALSE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(FALSE);
		CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
		pGenPrec->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr0092Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr0092Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	UpdateData(TRUE);
	if( m_QuadMod )
		m_QuadModType = m_ctrlQuadModType.GetCurSel() + 1;
	else
		m_QuadModType = 0;
	if( m_isPll == 0 )
		m_nOscFreq = 0;
	if( m_isGen == 0 )
		m_nGen = 0;
}

void Icr0092Dlg::OnBnClickedQuadmod()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_QuadMod == 0 )
		m_ctrlQuadModType.EnableWindow(FALSE);
	else if ( m_QuadMod == 1 )
		m_ctrlQuadModType.EnableWindow(TRUE);
}

void Icr0092Dlg::OnBnClickedIsgen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_isGen == 0 )
	{
		m_nGen = 0;
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(FALSE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(FALSE);
		CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
		pGenPrec->EnableWindow(FALSE);
	}
	else if ( m_isGen == 1 )
	{
		m_nGen = 1;
		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
		pGen->EnableWindow(TRUE);
		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
		pGenTune->EnableWindow(TRUE);
		CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
		pGenPrec->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

//void Icr0092Dlg::OnBnClickedIspll()
//{
//	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	if( m_isPll == 0 )
//	{
//		m_nOscFreq = 0;
//		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
//		pPll->EnableWindow(FALSE);
//		CWnd* pIsGen = (CWnd*)GetDlgItem(IDC_ISGEN);
//		pIsGen->EnableWindow(FALSE);
//		CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
//		pGen->EnableWindow(FALSE);
//		CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
//		pGenTune->EnableWindow(FALSE);
//		CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
//		pGenPrec->EnableWindow(FALSE);
//	}
//	else if ( m_isPll == 1 )
//	{
//		m_nOscFreq = 1;
//		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
//		pPll->EnableWindow(TRUE);
//		CWnd* pIsGen = (CWnd*)GetDlgItem(IDC_ISGEN);
//		pIsGen->EnableWindow(TRUE);
//		if( m_isGen == 1 )
//		{
//			m_nGen = 1;
//			CWnd* pGen = (CWnd*)GetDlgItem(IDC_GEN);
//			pGen->EnableWindow(TRUE);
//			CWnd* pGenTune = (CWnd*)GetDlgItem(IDC_GENTUNE);
//			pGenTune->EnableWindow(TRUE);
//			CWnd* pGenPrec = (CWnd*)GetDlgItem(IDC_GEN_PREC);
//			pGenPrec->EnableWindow(TRUE);
//		}
//	}
//	UpdateData(FALSE);
//}

//void Icr0092Dlg::OnEnKillfocusOscfreq()
//{
//	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	if( m_nOscFreq == 0 )
//		m_nOscFreq = 1;
//	UpdateData(FALSE);
//}

void Icr0092Dlg::OnEnKillfocusGen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_nGen == 0 )
		m_nGen = 1;
	UpdateData(FALSE);
}

void Icr0092Dlg::OnBnClickedIspll()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if(m_isPll == 0)
	{
		m_nOscFreq = 0;
		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
		pPll->EnableWindow(FALSE);
	}
	else
	{
		m_nOscFreq = 1;
		CWnd* pPll = (CWnd*)GetDlgItem(IDC_OSCFREQ);
		pPll->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
}
