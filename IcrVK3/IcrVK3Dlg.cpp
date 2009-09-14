// IcrVK3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrVK3.h"
#include "IcrVK3Dlg.h"


// IcrVK3Dlg dialog

IMPLEMENT_DYNAMIC(IcrVK3Dlg, CDialog)

IcrVK3Dlg::IcrVK3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IcrVK3Dlg::IDD, pParent)
	, m_dSysGen(0)
{

}

IcrVK3Dlg::~IcrVK3Dlg()
{
}

void IcrVK3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM, m_nNum);
	DDX_Text(pDX, IDC_BIASBITS, m_bDacBiasBits);
	DDX_Text(pDX, IDC_OUTNUM, m_bDacOutNum);
	DDX_Text(pDX, IDC_DACBITS, m_bDacBits);
	DDX_Text(pDX, IDC_INPNUM, m_bAdcInpNum);
	DDX_Text(pDX, IDC_ADCBITS, m_bAdcBits);
	DDX_Text(pDX, IDC_SYSFREQ, m_dSysGen);
	DDX_Text(pDX, IDC_REFFREQ, m_dRefGen);
	DDX_Control(pDX, IDC_DACBIAS, m_ctrlDacBiasSet);
	DDX_Text(pDX, IDC_DACRANGEBIAS, m_nDacBiasRange);
	DDX_Control(pDX, IDC_OUTNUM, m_ctrlDacOutNum);
	DDX_Text(pDX, IDC_DACFTYPE, m_sDacTypeF);
	DDX_Control(pDX, IDC_DACBITS, m_ctrlDacBits);
	DDX_Text(pDX, IDC_OUTAMPL, m_nOutAmplRange);
	DDX_Control(pDX, IDC_OUTR, m_ctrlOutR);
	DDX_Control(pDX, IDC_BIASBITS, m_ctrlDacBiasBits);
	DDX_Text(pDX, IDC_ADCRANGEBIAS, m_nAdcBiasRange);
	DDX_Control(pDX, IDC_ADCFTYPE, m_ctrlAdcTypeF);
	DDX_Text(pDX, IDC_ADCFTYPE, m_sAdcTypeF);
	DDX_Text(pDX, IDC_INPAMPL, m_nInpAmplRange);
	DDX_Control(pDX, IDC_INPR, m_ctrlInpR);
	DDX_Control(pDX, IDC_DACINPADD, m_ctrlAdcInpAdd);
	DDX_Control(pDX, IDC_TUNER, m_ctrlTuner);
	DDX_Control(pDX, IDC_SELECTOR, m_ctrlSelectorSinch);
	DDX_Control(pDX, IDC_INPNUM, m_ctrlAdcInpNum);
	DDX_Control(pDX, IDC_ADCBITS, m_ctrlAdcBits);
	DDX_Control(pDX, IDC_SYSFREQ, m_ctrlSysGen);
	DDX_Control(pDX, IDC_REFFREQ, m_ctrlRefGen);
	DDX_Control(pDX, IDC_DACRANGEBIAS, m_ctrlDacBiasRange);
	DDX_Control(pDX, IDC_OUTAMPL, m_ctrlOutAmplRange);
	DDX_Control(pDX, IDC_ADCRANGEBIAS, m_ctrlAdcBiasRange);
	DDX_Control(pDX, IDC_INPAMPL, m_ctrlInpAmplRange);
	DDX_Control(pDX, IDC_DACFTYPE, m_ctrlDacTypeF);
	DDX_Control(pDX, IDC_ISADC, m_ctrlAdcChanNum);
	DDX_Control(pDX, IDC_ISDAC, m_ctrlDacChanNum);
	DDX_Control(pDX, IDC_DDRNUM, m_ctrlDdrModuleNum);
	DDX_Text(pDX, IDC_DACSAMPLEFREQ, m_nDacMaxfreqSampl);
	DDX_Text(pDX, IDC_ADCSAMPLEFREQ, m_nAdcMaxfreqSampl);
	DDX_Control(pDX, IDC_DACSAMPLEFREQ, m_ctrlDacMaxfreqSampl);
	DDX_Control(pDX, IDC_ADCSAMPLEFREQ, m_ctrlAdcMaxfreqSampl);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlPldType);
}


BEGIN_MESSAGE_MAP(IcrVK3Dlg, CDialog)
ON_CBN_SELCHANGE(IDC_OUTAMPL, &IcrVK3Dlg::OnCbnSelchangeOutampl)
ON_BN_CLICKED(IDC_DACBIAS, &IcrVK3Dlg::OnBnClickedDacbias)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_ISADC, &IcrVK3Dlg::OnBnClickedIsadc)
ON_BN_CLICKED(IDC_ISDAC, &IcrVK3Dlg::OnBnClickedIsdac)
ON_BN_CLICKED(IDC_DDRNUM, &IcrVK3Dlg::OnBnClickedDdrnum)
ON_CBN_SELCHANGE(IDC_PLDTYPE, &IcrVK3Dlg::OnCbnSelchangePldtype)
END_MESSAGE_MAP()


// IcrVK3Dlg message handlers

BOOL IcrVK3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_NUM), IDC_NUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_DDRNUM), IDC_DDRNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_SYSFREQ), IDC_SYSFREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_REFFREQ), IDC_REFFREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_BIASBITS), IDC_BIASBITS);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACBIAS), IDC_DACBIAS);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTNUM), IDC_OUTNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACFTYPE), IDC_DACFTYPE);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGEBIAS), IDC_DACRANGEBIAS);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACBITS), IDC_DACBITS);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTAMPL), IDC_OUTAMPL);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTR), IDC_OUTR);
	m_ToolTip.AddTool(GetDlgItem(IDC_ISADC), IDC_ISADC);
	m_ToolTip.AddTool(GetDlgItem(IDC_ISDAC), IDC_ISDAC);
	m_ToolTip.AddTool(GetDlgItem(IDC_INPNUM), IDC_INPNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCFTYPE), IDC_ADCFTYPE);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGEBIAS), IDC_ADCRANGEBIAS);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCBITS), IDC_ADCBITS);
	m_ToolTip.AddTool(GetDlgItem(IDC_INPAMPL), IDC_INPAMPL);
	m_ToolTip.AddTool(GetDlgItem(IDC_INPR), IDC_INPR);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACINPADD), IDC_DACINPADD);
	m_ToolTip.AddTool(GetDlgItem(IDC_TUNER), IDC_TUNER);
	m_ToolTip.AddTool(GetDlgItem(IDC_SELECTOR), IDC_SELECTOR);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACSAMPLEFREQ), IDC_DACSAMPLEFREQ); 
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCSAMPLEFREQ), IDC_ADCSAMPLEFREQ); 
	m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE); 

	m_ctrlDdrModuleNum.SetCheck(m_bDdrModuleNum); 

	switch(m_nOutR)
	{
		case 50: m_ctrlOutR.SetCurSel(0); break;
		case 75: m_ctrlOutR.SetCurSel(1); break;
	}

	switch(m_nInpR)
	{
		case 50: m_ctrlInpR.SetCurSel(0); break;
		case 75: m_ctrlInpR.SetCurSel(1); break;
		case 1000000: m_ctrlInpR.SetCurSel(2); break;
	}

	m_ctrlAdcInpAdd.SetCheck(m_isAdcInpAdd);
	m_ctrlTuner.SetCheck(m_isTuner);
	m_ctrlSelectorSinch.SetCheck(m_isSelectorSinch);

	m_ctrlAdcChanNum.SetCheck(m_bAdcChanNum);
	m_ctrlDacChanNum.SetCheck(m_bDacChanNum);
	AdcParamEnable(m_bAdcChanNum);
	DacParamEnable(m_bDacChanNum);
	m_ctrlDacBiasSet.SetCheck(m_isDacBias);
	BiasParamEnable(m_isDacBias);

	switch(m_bSpeedGrade)
	{
		case 4: m_ctrlPldType.SetCurSel(0); break;
		case 5: m_ctrlPldType.SetCurSel(1); break;
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void IcrVK3Dlg::OnBnClickedDacset()
{
	
}

void IcrVK3Dlg::DacParamEnable(U08 isSet)
{
	m_ctrlDacOutNum.EnableWindow(isSet);
	m_ctrlDacTypeF.EnableWindow(isSet);
	m_ctrlDacBits.EnableWindow(isSet);
	m_ctrlOutAmplRange.EnableWindow(isSet);
	m_ctrlOutR.EnableWindow(isSet);
	m_ctrlDacBiasSet.EnableWindow(isSet);

	if(isSet)
	{
		if(m_ctrlDacBiasSet.GetCheck())
			isSet = TRUE;
		else
			isSet = FALSE;

		m_ctrlDacBiasBits.EnableWindow(isSet);
		m_ctrlDacBiasRange.EnableWindow(isSet);

		if(isSet && (m_bAdcChanNum != 0))
			m_ctrlAdcBiasRange.EnableWindow(isSet);
		else
			m_ctrlAdcBiasRange.EnableWindow(FALSE);
	}
	else
	{
		m_ctrlDacBiasBits.EnableWindow(isSet);
		m_ctrlDacBiasRange.EnableWindow(isSet);
		m_ctrlAdcBiasRange.EnableWindow(isSet);
	}
}

void IcrVK3Dlg::AdcParamEnable(U08 isSet)
{
	m_ctrlAdcInpNum.EnableWindow(isSet);
	m_ctrlAdcTypeF.EnableWindow(isSet);
	m_ctrlAdcBits.EnableWindow(isSet);
	m_ctrlAdcMaxfreqSampl.EnableWindow(isSet);
	m_ctrlInpAmplRange.EnableWindow(isSet);
	m_ctrlInpR.EnableWindow(isSet);
	m_ctrlAdcInpAdd.EnableWindow(isSet);
	m_ctrlTuner.EnableWindow(isSet);
	m_ctrlSelectorSinch.EnableWindow(isSet);

	if(isSet)
	{
		if(m_ctrlDacBiasSet.GetCheck())
		{
			if(m_bDacChanNum)
				m_ctrlAdcBiasRange.EnableWindow(TRUE);
			else
				m_ctrlAdcBiasRange.EnableWindow(FALSE);
		}
		else
			m_ctrlAdcBiasRange.EnableWindow(FALSE);
	}
	else
		m_ctrlAdcBiasRange.EnableWindow(isSet);
}

void IcrVK3Dlg::OnCbnSelchangeOutampl()
{
	// TODO: Add your control notification handler code here
}

void IcrVK3Dlg::OnBnClickedDacbias()
{
	// TODO: Add your control notification handler code here
	BiasParamEnable(m_ctrlDacBiasSet.GetCheck());
}

void IcrVK3Dlg::BiasParamEnable(U08 isSet)
{
	m_ctrlDacBiasBits.EnableWindow(isSet);
	m_ctrlDacBiasRange.EnableWindow(isSet);

	if(isSet && (m_bAdcChanNum != 0))
		m_ctrlAdcBiasRange.EnableWindow(isSet);
	else
		m_ctrlAdcBiasRange.EnableWindow(FALSE);
}

BOOL IcrVK3Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void IcrVK3Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	//UpdateData(FALSE);

	// TODO: Add your message handler code here

	m_bDdrModuleNum = m_ctrlDdrModuleNum.GetCheck(); 

	switch(m_ctrlOutR.GetCurSel())
	{
		case 0: m_nOutR = 50; break;
		case 1: m_nOutR = 75; break;
	}

	switch(m_ctrlInpR.GetCurSel())
	{
		case 0: m_nInpR = 50; break;
		case 1: m_nInpR = 75; break;
		case 2: m_nInpR = 1000000; break;
	}

	m_isAdcInpAdd = m_ctrlAdcInpAdd.GetCheck();
	m_isTuner = m_ctrlTuner.GetCheck();
	m_isSelectorSinch = m_ctrlSelectorSinch.GetCheck();
	m_isDacBias = m_ctrlDacBiasSet.GetCheck();

	switch(m_ctrlPldType.GetCurSel())
	{
		case 0: m_bSpeedGrade = 4; break;
		case 1: m_bSpeedGrade = 5; break;
	}
}

void IcrVK3Dlg::OnBnClickedIsadc()
{
	// TODO: Add your control notification handler code here

	m_bAdcChanNum = m_ctrlAdcChanNum.GetCheck();
	AdcParamEnable(m_bAdcChanNum);
}

void IcrVK3Dlg::OnBnClickedIsdac()
{
	// TODO: Add your control notification handler code here

	m_bDacChanNum = m_ctrlDacChanNum.GetCheck();
	DacParamEnable(m_bDacChanNum);
}

void IcrVK3Dlg::OnBnClickedDdrnum()
{
	// TODO: Add your control notification handler code here

	m_bDacChanNum = m_ctrlDdrModuleNum.GetCheck();
}

void IcrVK3Dlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here

	if(m_ctrlPldType.GetCurSel())
		m_bSpeedGrade = 5;
	else
		m_bSpeedGrade = 4;
}
