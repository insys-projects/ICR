// Icr0086Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0086App.h"
//#include "Icr0086Dlg.h"


// CIcr0086Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0086Dlg, CDialog)
CIcr0086Dlg::CIcr0086Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0086Dlg::IDD, pParent)
	, m_AdcBits(1)
	, m_AdcEncoding(1)
	, m_AdcRateMax(100000000)
	, m_AdcRateMin(10000000)
	, m_AdcRange(500)
	, m_Gen(100000000)
	, m_NumOfAdc(4)
	, m_NumOfDdc(4)
{
}

CIcr0086Dlg::~CIcr0086Dlg()
{
}

void CIcr0086Dlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_NUMOFDDC, m_NumOfDdc);
	DDX_Control(pDX, IDC_SPINDDC, m_ctrlSpinDdc);
}


BEGIN_MESSAGE_MAP(CIcr0086Dlg, CDialog)
END_MESSAGE_MAP()


// ÑIcr0086Dlg message handlers

BOOL CIcr0086Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinDdc.SetRange(0, 32);
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
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFDDC), IDC_NUMOFDDC);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcr0086Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}
