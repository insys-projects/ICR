// Icr008EDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr008Eapp.h"
#include "Icr008EDlg.h"


// CIcr008EDlg dialog

IMPLEMENT_DYNAMIC(CIcr008EDlg, CDialog)
CIcr008EDlg::CIcr008EDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr008EDlg::IDD, pParent)
{
	m_AdcBits = 2;
	m_AdcEncoding = 1;
	m_AdcRange = 1000;
	m_AdcRateMax = 1000000;
	m_AdcRateMin = 0;
	m_NumOfAdc = 0;

	m_DacBits = 2;
	m_DacEncoding = 1;
	m_DacRange = 1000;
	m_DacRateMax = 1000000;
	m_DacRateMin = 0;
	m_NumOfDac = 0;
}

CIcr008EDlg::~CIcr008EDlg()
{
}

void CIcr008EDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_CBIndex(pDX, IDC_NUMOFADC, m_NumOfAdc);

	DDX_CBIndex(pDX, IDC_DACBITS, m_DacBits);
	DDX_CBIndex(pDX, IDC_DACENCODING, m_DacEncoding);
	DDX_Text(pDX, IDC_DACRANGE, m_DacRange);
	DDX_Text(pDX, IDC_DACRATEMAX, m_DacRateMax);
	DDX_Text(pDX, IDC_DACRATEMIN, m_DacRateMin);
	DDX_CBIndex(pDX, IDC_NUMOFDAC, m_NumOfDac);
}


BEGIN_MESSAGE_MAP(CIcr008EDlg, CDialog)
END_MESSAGE_MAP()


// Icr008EDlg message handlers

BOOL CIcr008EDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr008EDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

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

	m_ToolTip.AddTool(GetDlgItem(IDC_DACBITS), IDC_DACBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACENCODING), IDC_DACENCODING);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMAX), IDC_DACRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMIN), IDC_DACRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGE), IDC_DACRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFDAC), IDC_NUMOFDAC);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
