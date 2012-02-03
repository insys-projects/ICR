// Icr0095Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr0095App.h"
#include "Icr0095Dlg.h"
//#include "Icr0095Dlg.h"

// CIcr0095Dlg dialog

IMPLEMENT_DYNAMIC(CIcr0095Dlg, CDialog)

CIcr0095Dlg::CIcr0095Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcr0095Dlg::IDD, pParent)
{
	m_AdcBits = 12;
	m_NumOfAdc = 4;
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
	m_SyntType = 4;

	{
		int		iiAdc;
		for( iiAdc=0; iiAdc<4; iiAdc++ )
		{
			m_awRangeDeviation[iiAdc] = 10000;
			m_awBiasDeviation[iiAdc] = 0;
		}
	}
}

CIcr0095Dlg::~CIcr0095Dlg()
{
}

void CIcr0095Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
	DDX_CBIndex(pDX, IDC_ADCBITS, m_AdcBits);
	DDX_CBIndex(pDX, IDC_ADCENCODING, m_AdcEncoding);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDV_MinMaxUInt(pDX, m_NumOfAdc, 1, 4);

	DDX_CBIndex(pDX, IDC_ADCTYPE, m_AdcType);
	DDX_CBIndex(pDX, IDC_DACTYPE, m_DacType);
	DDX_Text(pDX, IDC_DACRANGE, m_DacRange);
	DDX_CBIndex(pDX, IDC_GENTYPE, m_GenType);
	DDX_Text(pDX, IDC_GENREF, m_GenRef);
	DDX_Text(pDX, IDC_GENREFMAX, m_GenRefMax);
	DDX_CBIndex(pDX, IDC_SYNTTYPE, m_SyntType);

	CHAR		strGenAdr[10];

	sprintf_s( strGenAdr, "%X", m_GenAdr );
	DDX_Text(pDX, IDC_GENADR, strGenAdr, sizeof(strGenAdr) );
	sscanf_s( strGenAdr, "%X", &m_GenAdr );

	DDX_Text(pDX, IDC_BIASDV_CH0, m_awBiasDeviation[0]);
	DDX_Text(pDX, IDC_BIASDV_CH1, m_awBiasDeviation[1]);
	DDX_Text(pDX, IDC_BIASDV_CH2, m_awBiasDeviation[2]);
	DDX_Text(pDX, IDC_BIASDV_CH3, m_awBiasDeviation[3]);

	DDX_Text(pDX, IDC_RANGEDIV_CH0, m_awRangeDeviation[0]);
	DDX_Text(pDX, IDC_RANGEDIV_CH1, m_awRangeDeviation[1]);
	DDX_Text(pDX, IDC_RANGEDIV_CH2, m_awRangeDeviation[2]);
	DDX_Text(pDX, IDC_RANGEDIV_CH3, m_awRangeDeviation[3]);
}


BEGIN_MESSAGE_MAP(CIcr0095Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLEARDEVIATION, &CIcr0095Dlg::OnBnClickedButtonCleardeviation)
	ON_BN_CLICKED(IDC_BUTTON_CLEARRANGE, &CIcr0095Dlg::OnBnClickedButtonClearRange)
END_MESSAGE_MAP()


// CIcr0095Dlg message handlers

BOOL CIcr0095Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcr0095Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinAdc.SetRange(1, 4);

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

void CIcr0095Dlg::OnBnClickedButtonCleardeviation()
{
	UpdateData(TRUE);
	{
		int		iiAdc;
		for( iiAdc=0; iiAdc<4; iiAdc++ )
		{
			m_awBiasDeviation[iiAdc] = 0;
		}
	}
	UpdateData(FALSE);
}

void CIcr0095Dlg::OnBnClickedButtonClearRange()
{
	UpdateData(TRUE);
	{
		int		iiAdc;
		for( iiAdc=0; iiAdc<4; iiAdc++ )
		{
			m_awRangeDeviation[iiAdc] = 10000;
		}
	}
	UpdateData(FALSE);
}
