// Icr0093Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0093App.h"
//#include "Icr0093Dlg.h"

// CIcr0093Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0093Dlg, CDialog)

CIcr0093Dlg::CIcr0093Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0093Dlg::IDD, pParent)
{
	m_AdcBits = 1;
	m_NumOfAdc = 4;
	m_AdcEncoding = 1;
	m_AdcRange = 500;
	m_AdcRateMax = 1000000000;
	m_AdcRateMin = 1000;

	m_AdcType = 0;
	m_DacType = 0;
	m_DacRange = 2500;
	m_GenType = 1;
	m_GenRef = 10000000;
	m_GenRefMax = 280000000;

	m_Range0 = 10000;
	m_Range1 = 2000;
	m_Range2 = 500;
	m_Range3 = 100;
	m_Range2 = 100;
	m_Range3 = 100;
}

CIcr0093Dlg::~CIcr0093Dlg()
{
}

void CIcr0093Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDV_MinMaxUInt(pDX, m_NumOfAdc, 1, 8);

	DDX_CBIndex(pDX, IDC_ADCTYPE, m_AdcType);
	DDX_CBIndex(pDX, IDC_DACTYPE, m_DacType);
	DDX_Text(pDX, IDC_DACRANGE, m_DacRange);
	DDX_Text(pDX, IDC_GENREF, m_GenRef);
	DDX_CBIndex(pDX, IDC_GENTYPE, m_GenType);
	DDX_Text(pDX, IDC_GENREF, m_GenRef);
	DDX_Text(pDX, IDC_GENREFMAX, m_GenRefMax);
	DDX_Text(pDX, IDC_RANGE0, m_Range0);
	DDX_Text(pDX, IDC_RANGE1, m_Range1);
	DDX_Text(pDX, IDC_RANGE2, m_Range2);
	DDX_Text(pDX, IDC_RANGE3, m_Range3);
	DDX_Text(pDX, IDC_RANGE4, m_Range4);
	DDX_Text(pDX, IDC_RANGE5, m_Range5);
}


//BEGIN_MESSAGE_MAP(CIcr0093Dlg, CDialog)
//	ON_BN_CLICKED(IDC_BUTTON_CLEARDEVIATION, &CIcr0093Dlg::OnBnClickedButtonCleardeviation)
//END_MESSAGE_MAP()


// CIcr0093Dlg message handlers

BOOL CIcr0093Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr0093Dlg::OnInitDialog()
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

//void CIcr0093Dlg::OnBnClickedButtonCleardeviation()
//{
//	{
//		int		iiP, iiR, iiAdc, iiRange;
//		for( iiRange=0; iiRange<4; iiRange++ )
//		for( iiAdc=0; iiAdc<2; iiAdc++ )
//		for( iiR=0; iiR<2; iiR++ )
//		for( iiP=0; iiP<2; iiP++ )
//		{
//			m_awRangeDeviation[iiP][iiR][iiAdc][iiRange] = 10000;
//			m_awBiasDeviation[iiP][iiR][iiAdc][iiRange] = 0;
//		}
//	}
//	UpdateData(FALSE);
//}
