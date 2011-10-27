// Icr0094Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0094App.h"
#include "Icr0094Dlg.h"
//#include "Icr0094Dlg.h"

// CIcr0094Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0094Dlg, CDialog)

CIcr0094Dlg::CIcr0094Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0094Dlg::IDD, pParent)
{
	m_AdcBits = 2;
	m_NumOfAdc = 2;
	m_AdcEncoding = 1;
	m_AdcRange = 500;
	m_AdcRateMax = 250000000;
	m_AdcRateMin = 1000;

	m_AdcType = 0;
	m_DacType = 0;
	m_DacRange = 500;
	m_GenType = 1;
	m_GenAdr = 0x49;
	m_GenRef = 0;
	m_GenRefMax = 280000000;
	m_SyntType = 1;
	m_AttType = 1;

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

CIcr0094Dlg::~CIcr0094Dlg()
{
}

void CIcr0094Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDV_MinMaxUInt(pDX, m_NumOfAdc, 1, 2);

	DDX_CBIndex(pDX, IDC_ADCTYPE, m_AdcType);
	DDX_CBIndex(pDX, IDC_DACTYPE, m_DacType);
	DDX_Text(pDX, IDC_DACRANGE, m_DacRange);
	DDX_CBIndex(pDX, IDC_GENTYPE, m_GenType);
	DDX_Text(pDX, IDC_GENREF, m_GenRef);
	DDX_Text(pDX, IDC_GENREFMAX, m_GenRefMax);
	DDX_CBIndex(pDX, IDC_SYNTTYPE, m_SyntType);
	DDX_CBIndex(pDX, IDC_ATTTYPE, m_AttType);

	CHAR		strGenAdr[10];

	sprintf_s( strGenAdr, "%X", m_GenAdr );
	DDX_Text(pDX, IDC_GENADR, strGenAdr, sizeof(strGenAdr) );
	sscanf_s( strGenAdr, "%X", &m_GenAdr );

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

	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH0_RANGE0, m_awRangeDeviation[0][0][0][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH0_RANGE1, m_awRangeDeviation[0][0][0][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH0_RANGE2, m_awRangeDeviation[0][0][0][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH0_RANGE3, m_awRangeDeviation[0][0][0][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH1_RANGE0, m_awRangeDeviation[0][0][1][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH1_RANGE1, m_awRangeDeviation[0][0][1][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH1_RANGE2, m_awRangeDeviation[0][0][1][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R0_CH1_RANGE3, m_awRangeDeviation[0][0][1][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH0_RANGE0, m_awRangeDeviation[0][1][0][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH0_RANGE1, m_awRangeDeviation[0][1][0][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH0_RANGE2, m_awRangeDeviation[0][1][0][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH0_RANGE3, m_awRangeDeviation[0][1][0][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH1_RANGE0, m_awRangeDeviation[0][1][1][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH1_RANGE1, m_awRangeDeviation[0][1][1][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH1_RANGE2, m_awRangeDeviation[0][1][1][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P0_R1_CH1_RANGE3, m_awRangeDeviation[0][1][1][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH0_RANGE0, m_awRangeDeviation[1][0][0][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH0_RANGE1, m_awRangeDeviation[1][0][0][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH0_RANGE2, m_awRangeDeviation[1][0][0][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH0_RANGE3, m_awRangeDeviation[1][0][0][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH1_RANGE0, m_awRangeDeviation[1][0][1][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH1_RANGE1, m_awRangeDeviation[1][0][1][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH1_RANGE2, m_awRangeDeviation[1][0][1][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R0_CH1_RANGE3, m_awRangeDeviation[1][0][1][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH0_RANGE0, m_awRangeDeviation[1][1][0][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH0_RANGE1, m_awRangeDeviation[1][1][0][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH0_RANGE2, m_awRangeDeviation[1][1][0][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH0_RANGE3, m_awRangeDeviation[1][1][0][3]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH1_RANGE0, m_awRangeDeviation[1][1][1][0]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH1_RANGE1, m_awRangeDeviation[1][1][1][1]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH1_RANGE2, m_awRangeDeviation[1][1][1][2]);
	DDX_Text(pDX, IDC_RANGEDIV_P1_R1_CH1_RANGE3, m_awRangeDeviation[1][1][1][3]);

}


BEGIN_MESSAGE_MAP(CIcr0094Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLEARDEVIATION, &CIcr0094Dlg::OnBnClickedButtonCleardeviation)
END_MESSAGE_MAP()


// CIcr0094Dlg message handlers

BOOL CIcr0094Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr0094Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinAdc.SetRange(1, 2);

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

void CIcr0094Dlg::OnBnClickedButtonCleardeviation()
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
