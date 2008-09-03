// Icr0084Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0084App.h"
//#include "Icr0084Dlg.h"

// CIcr0084Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0084Dlg, CDialog)
CIcr0084Dlg::CIcr0084Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0084Dlg::IDD, pParent)
{
	m_AdcBits = 2;
	m_NumOfAdc = 0;
	m_AdcEncoding = 1;
	m_AdcRange = 1000;
	m_AdcRateMax = 1000000;
	m_AdcRateMin = 0;
}

CIcr0084Dlg::~CIcr0084Dlg()
{
}

void CIcr0084Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDV_MinMaxUInt(pDX, m_NumOfAdc, 1, 32);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
}


BEGIN_MESSAGE_MAP(CIcr0084Dlg, CDialog)
END_MESSAGE_MAP()


// CIcr0084Dlg message handlers

BOOL CIcr0084Dlg::OnInitDialog()
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
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCBITS), IDC_ADCBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCENCODING), IDC_ADCENCODING);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMAX), IDC_ADCRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMIN), IDC_ADCRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGE), IDC_ADCRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADC), IDC_NUMOFADC);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcr0084Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

