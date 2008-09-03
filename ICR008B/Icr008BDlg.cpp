// Icr008BDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr008BApp.h"
//#include "Icr008BDlg.h"


// CIcr008BDlg dialog

IMPLEMENT_DYNAMIC(CIcr008BDlg, CDialog)
CIcr008BDlg::CIcr008BDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr008BDlg::IDD, pParent)
	, m_AdcRateMax(800000000)
	, m_AdcRateMin(50000000)
	, m_MaxFreqVco(800000000)
	, m_MinFreqVco(400000000)
	, m_AdcRange(500)
	, m_MainGen(80000000)
	, m_NumOfAdc(0)
{
}

CIcr008BDlg::~CIcr008BDlg()
{
}

void CIcr008BDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_VCOMAX, m_MaxFreqVco);
	DDX_Text(pDX, IDC_VCOMIN, m_MinFreqVco);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_GEN1, m_MainGen);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
}


BEGIN_MESSAGE_MAP(CIcr008BDlg, CDialog)
END_MESSAGE_MAP()


// CIcr008BDlg message handlers

BOOL CIcr008BDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinAdc.SetRange(0, 32);

//	CString Title = subInfo.Name;
//	Title += _T(" Configuration");
//	SetWindowText(Title);
	CString Title;
	GetWindowText(Title);
	CString Name = subInfo.sName;
	Title = Name + _T(" ") + Title;
	SetWindowText(Title);

    m_ToolTip.Create(this);
//    m_ToolTip.AddTool(GetDlgItem(IDC_ADCBITS), IDC_ADCBITS);
//    m_ToolTip.AddTool(GetDlgItem(IDC_ADCENCODING), IDC_ADCENCODING);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMAX), IDC_ADCRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMIN), IDC_ADCRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_VCOMAX), IDC_VCOMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_VCOMIN), IDC_VCOMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGE), IDC_ADCRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADC), IDC_NUMOFADC);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcr008BDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}
