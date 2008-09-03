// Icr0089Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0089App.h"
//#include "Icr0089Dlg.h"

// CIcr0089Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0089Dlg, CDialog)
CIcr0089Dlg::CIcr0089Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0089Dlg::IDD, pParent)
	, m_AdcBits(1)
	, m_AdcEncoding(1)
	, m_AdcRateMax(200000000)
	, m_AdcRateMin(25000000)
	, m_AdcRange(10000)
	, m_Gen(20000000)
	, m_NumOfAdc(0)
{
}

CIcr0089Dlg::~CIcr0089Dlg()
{
}

void CIcr0089Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_GEN1, m_Gen);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
}


BEGIN_MESSAGE_MAP(CIcr0089Dlg, CDialog)
END_MESSAGE_MAP()


// CIcr0089Dlg message handlers

BOOL CIcr0089Dlg::OnInitDialog()
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

BOOL CIcr0089Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}
