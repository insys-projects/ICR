// IcrVK3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrVK3.h"
#include "IcrVK3Dlg.h"


// IcrVK3Dlg dialog

IMPLEMENT_DYNAMIC(IcrVK3Dlg, CDialog)

IcrVK3Dlg::IcrVK3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IcrVK3Dlg::IDD, pParent)
	, m_sPldType(_T(""))
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
	DDX_Text(pDX, IDC_DACCHANNUM, m_nDacChanNum);
	DDX_Text(pDX, IDC_OUTNUM, m_bDacOutNum);
	DDX_Text(pDX, IDC_DACBITS, m_bDacBits);
	DDX_Text(pDX, IDC_VOL, m_nVolume);
	DDX_Text(pDX, IDC_PIN, m_nPins);
	DDX_Text(pDX, IDC_ADCCHANNUM, m_bAdcChanNum);
	DDX_Text(pDX, IDC_INPNUM, m_bAdcInpNum);
	DDX_Text(pDX, IDC_ADCBITS, m_bAdcBits);
	DDX_Text(pDX, IDC_PLDTYPE, m_sPldType);
	DDX_Control(pDX, IDC_DDRNUM, m_ctrlDdrModuleNum);
	DDX_Control(pDX, IDC_SYSFREQ, m_ctrlSysGen);
	DDX_Control(pDX, IDC_REFFREQ, m_ctrlRefGen);
	DDX_Control(pDX, IDC_DACBIAS, m_ctrlDacBiasSet);
	DDX_Control(pDX, IDC_DACRANGEBIAS, m_ctrlDacBiasRange);
	DDX_Control(pDX, IDC_DACCHANNUM, m_ctrlDacChanNum);
	DDX_Control(pDX, IDC_OUTNUM, m_ctrlDacOutNum);
	DDX_Control(pDX, IDC_DACFTYPE, m_ctrlDacTypeF);
	DDX_Control(pDX, IDC_DACBITS, m_ctrlDacBits);
	DDX_Control(pDX, IDC_OUTAMPL, m_ctrlOutAmplRange);
	DDX_Control(pDX, IDC_OUTR, m_ctrlOutR);
	DDX_Control(pDX, IDC_BIASBITS, m_ctrlDacBiasBits);
	DDX_Control(pDX, IDC_ADCRANGEBIAS, m_ctrlAdcBiasRange);
	DDX_Control(pDX, IDC_ADCFTYPE, m_ctrlAdcTypeF);
	DDX_Control(pDX, IDC_SAMPLEFREQ, m_ctrlMaxfreqSampl);
	DDX_Control(pDX, IDC_INPAMPL, m_ctrlInpAmplRange);
	DDX_Control(pDX, IDC_INPR, m_ctrlInpR);
	DDX_Control(pDX, IDC_DACINPADD, m_ctrlAdcInpAdd);
	DDX_Control(pDX, IDC_TUNER, m_ctrlTuner);
	DDX_Control(pDX, IDC_SELECTOR, m_ctrlSelectorSinch);
	DDX_Control(pDX, IDC_INPNUM, m_ctrlAdcInpNum);
	DDX_Control(pDX, IDC_ADCBITS, m_ctrlAdcBits);
	DDX_Control(pDX, IDC_ADCCHANNUM, m_ctrlAdcChanNum);
	DDX_Control(pDX, IDC_TYPE, m_ctrlType);
	DDX_Control(pDX, IDC_SPEED, m_ctrlSpeedGrade);
}


BEGIN_MESSAGE_MAP(IcrVK3Dlg, CDialog)
//	ON_EN_CHANGE(IDC_DACCHANNUM, &IcrVK3Dlg::OnEnChangeDacchannum)
//	ON_EN_UPDATE(IDC_DACCHANNUM, &IcrVK3Dlg::OnEnUpdateDacchannum)
ON_EN_CHANGE(IDC_DACCHANNUM, &IcrVK3Dlg::OnEnChangeDacchannum)
ON_CBN_SELCHANGE(IDC_OUTAMPL, &IcrVK3Dlg::OnCbnSelchangeOutampl)
ON_EN_CHANGE(IDC_ADCCHANNUM, &IcrVK3Dlg::OnEnChangeAdcchannum)
ON_BN_CLICKED(IDC_DACBIAS, &IcrVK3Dlg::OnBnClickedDacbias)
ON_CBN_SELCHANGE(IDC_TYPE, &IcrVK3Dlg::OnCbnSelchangeType)
ON_CBN_SELCHANGE(IDC_SPEED, &IcrVK3Dlg::OnCbnSelchangeSpeed)
ON_EN_CHANGE(IDC_VOL, &IcrVK3Dlg::OnEnChangeVol)
ON_EN_CHANGE(IDC_PIN, &IcrVK3Dlg::OnEnChangePin)
ON_WM_DESTROY()
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
	m_ToolTip.AddTool(GetDlgItem(IDC_DACCHANNUM), IDC_DACCHANNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTNUM), IDC_OUTNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACFTYPE), IDC_DACFTYPE);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGEBIAS), IDC_DACRANGEBIAS);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACBITS), IDC_DACBITS);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTAMPL), IDC_OUTAMPL);
	m_ToolTip.AddTool(GetDlgItem(IDC_OUTR), IDC_OUTR);
	m_ToolTip.AddTool(GetDlgItem(IDC_TYPE), IDC_TYPE);
	m_ToolTip.AddTool(GetDlgItem(IDC_VOL), IDC_VOL);
	m_ToolTip.AddTool(GetDlgItem(IDC_SPEED), IDC_SPEED);
	m_ToolTip.AddTool(GetDlgItem(IDC_PIN), IDC_PIN);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCCHANNUM), IDC_ADCCHANNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_INPNUM), IDC_INPNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCFTYPE), IDC_ADCFTYPE);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGEBIAS), IDC_ADCRANGEBIAS);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCBITS), IDC_ADCBITS);
	m_ToolTip.AddTool(GetDlgItem(IDC_SAMPLEFREQ), IDC_SAMPLEFREQ);
	m_ToolTip.AddTool(GetDlgItem(IDC_INPAMPL), IDC_INPAMPL);
	m_ToolTip.AddTool(GetDlgItem(IDC_INPR), IDC_INPR);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACINPADD), IDC_DACINPADD);
	m_ToolTip.AddTool(GetDlgItem(IDC_TUNER), IDC_TUNER);
	m_ToolTip.AddTool(GetDlgItem(IDC_SELECTOR), IDC_SELECTOR);

	m_ctrlDdrModuleNum.SetCurSel(m_bDdrModuleNum); 

	switch((int)m_fSysGen)
	{
		case 66: m_ctrlSysGen.SetCurSel(0); break;
	}

	switch(m_wRefGen)
	{
		case 10: m_ctrlRefGen.SetCurSel(0); break;
	}

	switch(m_bDacTypeF)
	{
		case 1: m_ctrlDacTypeF.SetCurSel(0); break;
	}

	switch(m_wDacBiasRange)
	{
		case 500: m_ctrlDacBiasRange.SetCurSel(0); break;
	}

	switch(m_wOutAmplRange)
	{
		case 1100: m_ctrlOutAmplRange.SetCurSel(0);
	}

	switch(m_nOutR)
	{
		case 50: m_ctrlOutR.SetCurSel(0); break;
		case 75: m_ctrlOutR.SetCurSel(1); break;
	}

	switch(m_bAdcTypeF)
	{
		case 1: m_ctrlAdcTypeF.SetCurSel(0); break;
	}

	switch(m_wAdcBiasRange)
	{
		case 100: m_ctrlAdcBiasRange.SetCurSel(0); break;
	}

	switch(m_nMaxfreqSampl)
	{
		case 80: m_ctrlMaxfreqSampl.SetCurSel(0); break;
		case 100: m_ctrlMaxfreqSampl.SetCurSel(1); break;
	}

	switch(m_wInpAmplRange)
	{
		case 1700: m_ctrlInpAmplRange.SetCurSel(0); break;
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

	AdcParamEnable(m_bAdcChanNum);
	DacParamEnable(m_nDacChanNum);
	m_ctrlDacBiasSet.SetCheck(m_isDacBias);
	BiasParamEnable(m_isDacBias);

	m_ctrlType.SetCurSel(m_bType);

	switch(m_bSpeedGrade)
	{
		case 4: m_ctrlSpeedGrade.SetCurSel(0); break;
		case 5: m_ctrlSpeedGrade.SetCurSel(1); break;
	}
	
	CreatePldType();

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
	m_ctrlMaxfreqSampl.EnableWindow(isSet);
	m_ctrlInpAmplRange.EnableWindow(isSet);
	m_ctrlInpR.EnableWindow(isSet);
	m_ctrlAdcInpAdd.EnableWindow(isSet);
	m_ctrlTuner.EnableWindow(isSet);
	m_ctrlSelectorSinch.EnableWindow(isSet);

	if(isSet)
	{
		if(m_ctrlDacBiasSet.GetCheck())
		{
			if(m_nDacChanNum)
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

void IcrVK3Dlg::OnEnChangeDacchannum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	CString str;
	U32 k;

	k = GetDlgItemText(IDC_DACCHANNUM, str);

	if(k)
		UpdateData();
	else
		return;

	if(m_nDacChanNum == 0)
		DacParamEnable(FALSE);
	else
		DacParamEnable(TRUE);
}

void IcrVK3Dlg::OnCbnSelchangeOutampl()
{
	// TODO: Add your control notification handler code here
}

void IcrVK3Dlg::OnEnChangeAdcchannum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString str;
	U32 k;

	k = GetDlgItemText(IDC_ADCCHANNUM, str);

	if(k)
		UpdateData();
	else
		return;

	if(m_bAdcChanNum == 0)
		AdcParamEnable(FALSE);
	else
		AdcParamEnable(TRUE);
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

void IcrVK3Dlg::OnCbnSelchangeType()
{
	// TODO: Add your control notification handler code here
UpdateData();
	CreatePldType();

	
}

void IcrVK3Dlg::CreatePldType(void)
{
	CString str;
	U32		idx;

	m_sPldType.Delete(0, m_sPldType.GetLength());
	m_ctrlType.GetLBText(m_ctrlType.GetCurSel(), str);
	m_sPldType.Append(str);
	idx = m_sPldType.Find("...");
	m_sPldType.Delete(idx, 3);
	str.Format("%d", m_nVolume);
	m_sPldType.Insert(idx, str);
	m_sPldType.Append("-");
	m_ctrlSpeedGrade.GetLBText(m_ctrlSpeedGrade.GetCurSel(), str);
	m_sPldType.Append(str);
	m_sPldType.Append("FGG");
	str.Format("%d", m_nPins);
	m_sPldType.Append(str);

	UpdateData(FALSE);
}

void IcrVK3Dlg::OnCbnSelchangeSpeed()
{
	// TODO: Add your control notification handler code here
UpdateData();
	CreatePldType();

	
}

void IcrVK3Dlg::OnEnChangeVol()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString str;
	U32 k;

	k = GetDlgItemText(IDC_VOL, str);

	if(!k)
		return;

	UpdateData();
	CreatePldType();

	
}

void IcrVK3Dlg::OnEnChangePin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString str;
	U32 k;

	k = GetDlgItemText(IDC_PIN, str);

	if(!k)
		return;

	UpdateData();
	CreatePldType();

	
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

	// TODO: Add your message handler code here

	m_bDdrModuleNum = m_ctrlDdrModuleNum.GetCurSel(); 

	switch(m_ctrlSysGen.GetCurSel())
	{
		case 0: m_fSysGen = 66.666; break;
	}

	switch(m_ctrlRefGen.GetCurSel())
	{
		case 0: m_wRefGen = 10; break;
	}

	switch(m_ctrlDacTypeF.GetCurSel())
	{
		case 0: m_bDacTypeF = 1; break;
	}

	switch(m_ctrlDacBiasRange.GetCurSel())
	{
		case 0: m_wDacBiasRange = 500; break;
	}

	switch(m_ctrlOutAmplRange.SetCurSel(0))
	{
		case 0: m_wOutAmplRange = 1100; break;
	}

	switch(m_ctrlOutR.GetCurSel())
	{
		case 0: m_nOutR = 50; break;
		case 1: m_nOutR = 75; break;
	}

	switch(m_ctrlAdcTypeF.GetCurSel())
	{
		case 0: m_bAdcTypeF = 1; break;
	}

	switch(m_ctrlAdcBiasRange.GetCurSel())
	{
		case 0: m_wAdcBiasRange = 100; break;
	}

	switch(m_ctrlMaxfreqSampl.GetCurSel())
	{
		case 0: m_nMaxfreqSampl = 80; break;
		case 1: m_nMaxfreqSampl = 100; break;
	}

	switch(m_ctrlInpAmplRange.GetCurSel())
	{
		case 0: m_wInpAmplRange = 1700; break;
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
	m_bType = m_ctrlType.GetCurSel();

	switch(m_ctrlSpeedGrade.GetCurSel())
	{
		case 0: m_bSpeedGrade = 4; break;
		case 1: m_bSpeedGrade = 5; break;
	}
}
