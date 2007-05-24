// Icr0081Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0081App.h"
//#include "Icr0081Dlg.h"

// CIcr0081Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0081Dlg, CDialog)

CIcr0081Dlg::CIcr0081Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0081Dlg::IDD, pParent)
	, m_PllRefGen(40000000)
	, m_PllFreq(1000000000)
{
	m_AdcBits = 2;
	m_NumOfAdc = 1;
	m_AdcEncoding = 1;
	m_AdcRange = 500;
	m_AdcRateMax = 1000000000;
	m_AdcRateMin = 1000;

}

CIcr0081Dlg::~CIcr0081Dlg()
{
}

void CIcr0081Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDV_MinMaxUInt(pDX, m_NumOfAdc, 1, 32);
	DDX_Text(pDX, IDC_PLLREFGEN, m_PllRefGen);
	DDX_Text(pDX, IDC_PLLFREQ, m_PllFreq);
}


BEGIN_MESSAGE_MAP(CIcr0081Dlg, CDialog)
END_MESSAGE_MAP()


// CIcr0081Dlg message handlers

BOOL CIcr0081Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr0081Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinAdc.SetRange(0, 32);

	//CString Title = subInfo.Name;
	//Title += _T(" Configuration");
	//SetWindowText(Title);
	CString Title;
	GetWindowText(Title);
	CString Name = subInfo.Name;
	Title = Name + _T(" ") + Title;
	SetWindowText(Title);
	
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCBITS), IDC_ADCBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCENCODING), IDC_ADCENCODING);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMAX), IDC_ADCRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMIN), IDC_ADCRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGE), IDC_ADCRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLLREFGEN), IDC_PLLREFGEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLLFREQ), IDC_PLLFREQ);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADC), IDC_NUMOFADC);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
