// Icr0090Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0090App.h"
#include "Icr0090Dlg.h"
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

	{
		int		iiP, iiR, iiAdc, iiRange;
		for( iiRange=0; iiRange<4; iiRange++ )
		for( iiAdc=0; iiAdc<2; iiAdc++ )
		for( iiR=0; iiR<2; iiR++ )
		for( iiP=0; iiP<2; iiP++ )
		{
			m_awRangeDeviation[iiP][iiR][iiAdc][iiRange] = 10000;
			m_awBiasDeviation[iiP][iiR][iiAdc][iiRange] = 0;
		}
	}
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

	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH0_RANGE0, m_awBiasDeviation[0][0][0][0]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH0_RANGE1, m_awBiasDeviation[0][0][0][1]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH0_RANGE2, m_awBiasDeviation[0][0][0][2]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH0_RANGE3, m_awBiasDeviation[0][0][0][3]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH1_RANGE0, m_awBiasDeviation[0][0][1][0]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH1_RANGE1, m_awBiasDeviation[0][0][1][1]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH1_RANGE2, m_awBiasDeviation[0][0][1][2]);
	DDX_Text(pDX, IDC_BIASDV_P0_R0_CH1_RANGE3, m_awBiasDeviation[0][0][1][3]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH0_RANGE0, m_awBiasDeviation[0][1][0][0]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH0_RANGE1, m_awBiasDeviation[0][1][0][1]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH0_RANGE2, m_awBiasDeviation[0][1][0][2]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH0_RANGE3, m_awBiasDeviation[0][1][0][3]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH1_RANGE0, m_awBiasDeviation[0][1][1][0]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH1_RANGE1, m_awBiasDeviation[0][1][1][1]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH1_RANGE2, m_awBiasDeviation[0][1][1][2]);
	DDX_Text(pDX, IDC_BIASDV_P0_R1_CH1_RANGE3, m_awBiasDeviation[0][1][1][3]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH0_RANGE0, m_awBiasDeviation[1][0][0][0]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH0_RANGE1, m_awBiasDeviation[1][0][0][1]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH0_RANGE2, m_awBiasDeviation[1][0][0][2]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH0_RANGE3, m_awBiasDeviation[1][0][0][3]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH1_RANGE0, m_awBiasDeviation[1][0][1][0]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH1_RANGE1, m_awBiasDeviation[1][0][1][1]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH1_RANGE2, m_awBiasDeviation[1][0][1][2]);
	DDX_Text(pDX, IDC_BIASDV_P1_R0_CH1_RANGE3, m_awBiasDeviation[1][0][1][3]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH0_RANGE0, m_awBiasDeviation[1][1][0][0]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH0_RANGE1, m_awBiasDeviation[1][1][0][1]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH0_RANGE2, m_awBiasDeviation[1][1][0][2]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH0_RANGE3, m_awBiasDeviation[1][1][0][3]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH1_RANGE0, m_awBiasDeviation[1][1][1][0]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH1_RANGE1, m_awBiasDeviation[1][1][1][1]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH1_RANGE2, m_awBiasDeviation[1][1][1][2]);
	DDX_Text(pDX, IDC_BIASDV_P1_R1_CH1_RANGE3, m_awBiasDeviation[1][1][1][3]);

}


BEGIN_MESSAGE_MAP(CIcr0090Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLEARDEVIATION, &CIcr0090Dlg::OnBnClickedButtonCleardeviation)
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

void CIcr0090Dlg::OnBnClickedButtonCleardeviation()
{
	{
		int		iiP, iiR, iiAdc, iiRange;
		for( iiRange=0; iiRange<4; iiRange++ )
		for( iiAdc=0; iiAdc<2; iiAdc++ )
		for( iiR=0; iiR<2; iiR++ )
		for( iiP=0; iiP<2; iiP++ )
		{
			m_awRangeDeviation[iiP][iiR][iiAdc][iiRange] = 10000;
			m_awBiasDeviation[iiP][iiR][iiAdc][iiRange] = 0;
		}
	}
	UpdateData(FALSE);
}
