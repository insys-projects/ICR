// IcrDR16Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrDR16App.h"
#include "IcrDR16Dlg.h"

// IcrDR16Dlg dialog

IMPLEMENT_DYNAMIC(IcrDR16Dlg, CDialog)

IcrDR16Dlg::IcrDR16Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IcrDR16Dlg::IDD, pParent)
	, m_sAdcBits(_T(""))
	, m_sAdcMaxRate(_T(""))
	, m_sAdcInpResist(_T(""))
	, m_sAdcRange(_T(""))
	, m_sDdcCnt(_T(""))
	, m_sDucRange(_T(""))
	, m_isDuc(1)
	, m_isDucTransformator(1)
	, m_isGenerator(0)
	, m_isSynthesizer(0)
	, m_isExtTactInput(1)
	, m_isExtStartInput(1)
	, m_isExtStartOutput(0)
	, m_isLinks(0)
	, m_isPiox(0)
	, m_isSynx(0)
	, m_isLvdsPiox(0)
	, m_isPci64(1)
	, m_isIndustrial(0)
	, m_bAdcCnt(16)
{

}

IcrDR16Dlg::~IcrDR16Dlg()
{
}

void IcrDR16Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Check   (pDX, IDC_DUC,               m_isDuc);
	DDX_Check   (pDX, IDC_DUC_TRANSFORMATOR, m_isDucTransformator);
	DDX_Check   (pDX, IDC_GENERATOR,         m_isGenerator);
	DDX_Check   (pDX, IDC_SYNTHESIZER,       m_isSynthesizer);
	DDX_Check   (pDX, IDC_EXT_TACT_INPUT,    m_isExtTactInput);
	DDX_Check   (pDX, IDC_EXT_START_INPUT,   m_isExtStartInput);
	DDX_Check   (pDX, IDC_EXT_START_OUTPUT,  m_isExtStartOutput);
	DDX_Check   (pDX, IDC_LINKS,		     m_isLinks);
	DDX_Check   (pDX, IDC_PIOX,			     m_isPiox);
	DDX_Check   (pDX, IDC_SYNX,			     m_isSynx);
	DDX_Check   (pDX, IDC_LVDS_PIOX,         m_isLvdsPiox);
	DDX_Check   (pDX, IDC_PCI64,    		 m_isPci64);
	DDX_Check   (pDX, IDC_INDUSTRIAL,    	 m_isIndustrial);
	DDX_Text    (pDX, IDC_ADC_CNT,    	     m_bAdcCnt);
	DDX_Control (pDX, IDC_ADC_BITS,          m_ctrlAdcBits);
	DDX_CBString(pDX, IDC_ADC_BITS,          m_sAdcBits);
	DDX_Text    (pDX, IDC_ADC_MIN_RATE,    	 m_nAdcMinRate);
	DDX_Control (pDX, IDC_ADC_MAX_RATE,      m_ctrlAdcMaxRate);
	DDX_CBString(pDX, IDC_ADC_MAX_RATE,      m_sAdcMaxRate);
	DDX_Text    (pDX, IDC_ADC_LOW_FREQ,    	 m_nAdcLowFreq);
	DDX_Text    (pDX, IDC_ADC_HIGH_FREQ,   	 m_nAdcHighFreq);
	DDX_Control (pDX, IDC_ADC_INP_RESIST,    m_ctrlAdcInpResist);
	DDX_CBString(pDX, IDC_ADC_INP_RESIST,    m_sAdcInpResist);
	DDX_Control (pDX, IDC_ADC_RANGE,         m_ctrlAdcRange);
	DDX_CBString(pDX, IDC_ADC_RANGE,         m_sAdcRange);
	DDX_Control (pDX, IDC_DDC_CNT,           m_ctrlDdcCnt);
	DDX_CBString(pDX, IDC_DDC_CNT,           m_sDdcCnt);
	DDX_Text    (pDX, IDC_DUC_HIGH_FREQ,   	 m_nDucHighFreq);
	DDX_Control (pDX, IDC_DUC_RANGE,         m_ctrlDucRange);
	DDX_CBString(pDX, IDC_DUC_RANGE,         m_sDucRange);
	DDX_Text    (pDX, IDC_GEN_FREQ,   	     m_nGenFreq);
	DDX_Control (pDX, IDC_GEN_PREC,          m_ctrlGenPrec);
	DDX_Text    (pDX, IDC_GEN_PREC,   	     m_sGenPrec);
	DDX_Text    (pDX, IDC_SYNT_FREQ,   	     m_nSyntFreq);
}


BEGIN_MESSAGE_MAP(IcrDR16Dlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// IcrDR16Dlg message handlers


BOOL IcrDR16Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL IcrDR16Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_DUC), IDC_DUC);
	m_ToolTip.AddTool(GetDlgItem(IDC_DUC_TRANSFORMATOR), IDC_DUC_TRANSFORMATOR);
	m_ToolTip.AddTool(GetDlgItem(IDC_GENERATOR), IDC_GENERATOR);
	m_ToolTip.AddTool(GetDlgItem(IDC_SYNTHESIZER), IDC_SYNTHESIZER);
	m_ToolTip.AddTool(GetDlgItem(IDC_EXT_TACT_INPUT), IDC_EXT_TACT_INPUT);
	m_ToolTip.AddTool(GetDlgItem(IDC_EXT_START_INPUT), IDC_EXT_START_INPUT);
	m_ToolTip.AddTool(GetDlgItem(IDC_EXT_START_OUTPUT), IDC_EXT_START_OUTPUT);
	m_ToolTip.AddTool(GetDlgItem(IDC_LINKS), IDC_LINKS);
	m_ToolTip.AddTool(GetDlgItem(IDC_PIOX), IDC_PIOX);
	m_ToolTip.AddTool(GetDlgItem(IDC_SYNX), IDC_SYNX);
	m_ToolTip.AddTool(GetDlgItem(IDC_LVDS_PIOX), IDC_LVDS_PIOX);
	m_ToolTip.AddTool(GetDlgItem(IDC_PCI64), IDC_PCI64);
	m_ToolTip.AddTool(GetDlgItem(IDC_INDUSTRIAL), IDC_INDUSTRIAL);
	m_ToolTip.AddTool(GetDlgItem(IDC_DDC_CNT), IDC_DDC_CNT);
	m_ToolTip.AddTool(GetDlgItem(IDC_DUC_HIGH_FREQ), IDC_DUC_HIGH_FREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_DUC_RANGE), IDC_DUC_RANGE);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_CNT), IDC_ADC_CNT);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_BITS), IDC_ADC_BITS);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_MIN_RATE), IDC_ADC_MIN_RATE);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_MAX_RATE), IDC_ADC_MAX_RATE);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_LOW_FREQ), IDC_ADC_LOW_FREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_HIGH_FREQ), IDC_ADC_HIGH_FREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_INP_RESIST), IDC_ADC_INP_RESIST);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADC_RANGE), IDC_ADC_RANGE);
	m_ToolTip.AddTool(GetDlgItem(IDC_GEN_FREQ), IDC_GEN_FREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_GEN_PREC), IDC_GEN_PREC);
	m_ToolTip.AddTool(GetDlgItem(IDC_SYNT_FREQ), IDC_SYNT_FREQ);
	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
	m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	m_ctrlAdcBits.SetNumber(1);
	m_ctrlAdcMaxRate.SetNumber(1);
	m_ctrlAdcInpResist.SetNumber(1);
	m_ctrlAdcRange.SetNumber(1);
	m_ctrlDdcCnt.SetNumber(1);
	m_ctrlDucRange.SetNumber(1);

  	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CNumComboBox::SetNumber(U08 isEnable)
{
	if(isEnable)
	{
		COMBOBOXINFO cbinfo;
		cbinfo.cbSize = sizeof(COMBOBOXINFO);

		GetComboBoxInfo(&cbinfo);

		m_NumEdit.SubclassWindow(cbinfo.hwndItem);

		m_isNumber = 1;
	}
	else
	{
		m_NumEdit.UnsubclassWindow();
		m_isNumber = 0;
	}
}