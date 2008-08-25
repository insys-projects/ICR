// Icr0090Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0090App.h"
//#include "Icr0090Dlg.h"

// CIcr0090Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0090Dlg, CDialog)

CIcr0090Dlg::CIcr0090Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0090Dlg::IDD, pParent)
{
	m_AdcBits = 2;
	m_NumOfAdc = 1;
	m_AdcEncoding = 1;
	m_AdcRange = 500;
	m_AdcRateMax = 1000000000;
	m_AdcRateMin = 1000;
	m_SubType = 0;
	m_RefGen0 = 400000000;
	m_RefGen1 = 300000000;
	m_Range0 = 10000;
	m_Range1 = 2000;
	m_Range2 = 500;
	m_Range3 = 100;
}

CIcr0090Dlg::~CIcr0090Dlg()
{
}

void CIcr0090Dlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_RANGE0, m_Range0);
	DDX_Text(pDX, IDC_RANGE1, m_Range1);
	DDX_Text(pDX, IDC_RANGE2, m_Range2);
	DDX_Text(pDX, IDC_RANGE3, m_Range3);
}


BEGIN_MESSAGE_MAP(CIcr0090Dlg, CDialog)
END_MESSAGE_MAP()


// CIcr0090Dlg message handlers

BOOL CIcr0090Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr0090Dlg::OnInitDialog()
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
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADC), IDC_NUMOFADC);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
