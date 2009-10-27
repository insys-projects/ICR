// Icr0091Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0091App.h"
//#include "Icr0091Dlg.h"

// CIcr0091Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0091Dlg, CDialog)

CIcr0091Dlg::CIcr0091Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0091Dlg::IDD, pParent)
{
	m_AdcBits = 1;
	m_NumOfAdc = 1;
	m_AdcEncoding = 1;
	m_AdcRange = 500;
	m_AdcRateMax = 1000000000;
	m_AdcRateMin = 1000;
	m_SubType = 0;
	m_RefGen0 = 400000000;
	m_RefGen1 = 300000000;
	m_RefGen1Max = 1000000000;
	m_RefGen1Min = 10000000;
	m_RefGen1Type = 1;
	m_RefGen2Type = 0;
	m_LpfPassBand = 0;
	m_Range0 = 10000;
	m_Range1 = 2000;
	m_Range2 = 500;
	m_Range3 = 100;
}

CIcr0091Dlg::~CIcr0091Dlg()
{
}

void CIcr0091Dlg::DoDataExchange(CDataExchange* pDX)
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

	DDX_CBIndex(pDX, IDC_SUBTYPE, m_SubType);
	DDX_Text(pDX, IDC_REFGEN0, m_RefGen0);
	DDX_Text(pDX, IDC_REFGEN1, m_RefGen1);
	DDX_Text(pDX, IDC_REFGEN1MAX, m_RefGen1Max);
	DDX_Text(pDX, IDC_REFGEN1MIN, m_RefGen1Min);
	DDX_CBIndex(pDX, IDC_REFGEN1TYPE, m_RefGen1Type);
	DDX_CBIndex(pDX, IDC_REFGEN2TYPE, m_RefGen2Type);
	DDX_Text(pDX, IDC_LPFPASSBAND, m_LpfPassBand);
	DDX_Text(pDX, IDC_RANGE0, m_Range0);
	DDX_Text(pDX, IDC_RANGE1, m_Range1);
	DDX_Text(pDX, IDC_RANGE2, m_Range2);
	DDX_Text(pDX, IDC_RANGE3, m_Range3);
}


BEGIN_MESSAGE_MAP(CIcr0091Dlg, CDialog)
END_MESSAGE_MAP()


// CIcr0091Dlg message handlers

BOOL CIcr0091Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr0091Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinAdc.SetRange(0, 32);

	//CString Title = subInfo.Name;
	//Title += _T(" Configuration");
	//SetWindowText(Title);
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
