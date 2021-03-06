// IcrDsp101cP10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrDsp101cP10App.h"
#include "IcrDsp101cP10Dlg.h"

#pragma warning (disable:4996)

// CIcrDsp101cP10Dlg dialog

IMPLEMENT_DYNAMIC(CIcrDsp101cP10Dlg, CDialog)
CIcrDsp101cP10Dlg::CIcrDsp101cP10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrDsp101cP10Dlg::IDD, pParent)
{
	m_BusClock = 100.0;
	m_strDioPldName = _T("");
	m_DioPldCnt = 0;
	m_DioPldNum = 0;
	m_DioPldPins = 0;
	m_DioPldVol = 0;
	m_HostPldCnt = 0;
	m_strPldName = _T("");
	m_PldVolume = 0;
	m_PldNum = 0;
	m_PldPins = 0;
	m_strSDRCON = _T("");
}

CIcrDsp101cP10Dlg::~CIcrDsp101cP10Dlg()
{
}

void CIcrDsp101cP10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINKSTYPE, m_ctrlLinksType);
	DDX_Control(pDX, IDC_SDRAMSIZE, m_ctrlSdramSize);
	DDX_Control(pDX, IDC_SPINDIOPLDCNT, m_ctrlSpinDioPldCnt);
	DDX_Control(pDX, IDC_SPINPLDCNT, m_ctrlSpinPldCnt);
	DDX_Control(pDX, IDC_SPINPLDNUM, m_ctrlSpinPldNum);
	DDX_Control(pDX, IDC_SPINDIOPLDNUM, m_ctrlSpinDioPldNum);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlPldType);
	DDX_Control(pDX, IDC_PLDRATE, m_ctrlPldRate);
	DDX_Control(pDX, IDC_DIOPLDTYPE, m_ctrlDioPldType);
	DDX_Control(pDX, IDC_DIOPLDRATE, m_ctrlDioPldRate);
	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Text(pDX, IDC_BUSCLOCK, m_BusClock);
	DDX_Text(pDX, IDC_DIOPLDNAME, m_strDioPldName);
	DDX_Text(pDX, IDC_DIOPLDCNT, m_DioPldCnt);
	DDX_Text(pDX, IDC_DIOPLDNUM, m_DioPldNum);
	DDX_Text(pDX, IDC_DIOPLDPINS, m_DioPldPins);
	DDX_Text(pDX, IDC_DIOPLDVOL, m_DioPldVol);
	DDX_Text(pDX, IDC_HOSTPLDCNT, m_HostPldCnt);
	DDX_Text(pDX, IDC_PLDNAME, m_strPldName);
	DDX_Text(pDX, IDC_PLDVOLUME, m_PldVolume);
	DDX_Text(pDX, IDC_PLDNUM, m_PldNum);
	DDX_Text(pDX, IDC_PLDPINS, m_PldPins);
	DDX_Text(pDX, IDC_SDRCON, m_strSDRCON);
}


BEGIN_MESSAGE_MAP(CIcrDsp101cP10Dlg, CDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_DIOPLDRATE, OnCbnSelchangeDiopldrate)
	ON_CBN_SELCHANGE(IDC_DIOPLDTYPE, OnCbnSelchangeDiopldtype)
	ON_CBN_SELCHANGE(IDC_PLDRATE, OnCbnSelchangePldrate)
	ON_CBN_SELCHANGE(IDC_PLDTYPE, OnCbnSelchangePldtype)
//	ON_EN_KILLFOCUS(IDC_PLDNUM, OnEnKillfocusPldnum)
	ON_EN_KILLFOCUS(IDC_PLDPINS, OnEnKillfocusPldpins)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, OnEnKillfocusPldvolume)
//	ON_EN_KILLFOCUS(IDC_DIOPLDNUM, OnEnKillfocusDiopldnum)
	ON_EN_KILLFOCUS(IDC_DIOPLDPINS, OnEnKillfocusDiopldpins)
	ON_EN_KILLFOCUS(IDC_DIOPLDVOL, OnEnKillfocusDiopldvol)
END_MESSAGE_MAP()


// CIcrDsp101cP10Dlg message handlers

BOOL CIcrDsp101cP10Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
    m_ToolTip.AddTool(GetDlgItem(IDC_BUSCLOCK), IDC_BUSCLOCK);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZE), IDC_SDRAMSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_HOSTPLDCNT), IDC_HOSTPLDCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDNUM), IDC_PLDNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDRATE), IDC_PLDRATE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDVOLUME), IDC_PLDVOLUME);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDPINS), IDC_PLDPINS);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	if(m_MaxCpuClock < (250 + (300 - 250) / 2))
		m_ctrlMaxCpuClock.SetCurSel(0);
	else
		m_ctrlMaxCpuClock.SetCurSel(1);

	if(m_SdramSize <= 64 * 1024 * 1024 / 2)
		m_ctrlSdramSize.SetCurSel(0);
	else
		if(m_SdramSize <= 128 * 1024 * 1024 / 2)
			m_ctrlSdramSize.SetCurSel(1);
		else
			if(m_SdramSize <= 256 * 1024 * 1024 / 2)
				m_ctrlSdramSize.SetCurSel(2);
			else
				m_ctrlSdramSize.SetCurSel(3);

	TCHAR buf[40];
	sprintf(buf, _T("%X"), m_SDRCON);
	m_strSDRCON = buf;

	m_ctrlLinksType.SetCurSel(m_TypeOfLinks);
			
	m_ctrlPldType.SetCurSel(m_PldType);
	m_ctrlPldRate.SetCurSel(m_PldRate);
	SetPldName();

	m_ctrlDioPldType.SetCurSel(m_DioPldType);
	m_ctrlDioPldRate.SetCurSel(m_DioPldRate);
	SetDioPldName();

	SetMaskOnCheckBoxes(m_CpuMask, IDC_P0);
	SetMaskOnCheckBoxes(m_SdramMask, IDC_M0);
	SetMaskOnCheckBoxes(m_LinksJ4Mask, IDC_L0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcrDsp101cP10Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CIcrDsp101cP10Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if(m_ctrlMaxCpuClock.GetCurSel())
		m_MaxCpuClock = 300;
	else
		m_MaxCpuClock = 250;
	switch(m_ctrlSdramSize.GetCurSel())
	{
	case 0:
		m_SdramSize = 0;
		break;
	case 1:
		m_SdramSize = 64 * 1024 * 1024;
		break;
	case 2:
		m_SdramSize = 128 * 1024 * 1024;
		break;
	case 3:
		m_SdramSize = 256 * 1024 * 1024;
		break;
	}
	
	LPTSTR stopstring;
	m_SDRCON = (USHORT)strtol(m_strSDRCON.GetBuffer(10), &stopstring, 16 );

	m_TypeOfLinks = m_ctrlLinksType.GetCurSel();
	m_PldType = m_ctrlPldType.GetCurSel();
	m_PldRate = m_ctrlPldRate.GetCurSel();
	m_DioPldType = m_ctrlDioPldType.GetCurSel();
	m_DioPldRate = m_ctrlDioPldRate.GetCurSel();

	GetMaskOnCheckBoxes(m_CpuMask, IDC_P0);
	GetMaskOnCheckBoxes(m_SdramMask, IDC_M0);
	GetMaskOnCheckBoxes(m_LinksJ4Mask, IDC_L0);
}

void CIcrDsp101cP10Dlg::OnCbnSelchangeDiopldrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrDsp101cP10Dlg::OnCbnSelchangeDiopldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrDsp101cP10Dlg::OnCbnSelchangePldrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrDsp101cP10Dlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

//void CIcrDsp101cP10Dlg::OnEnKillfocusPldnum()
//{
//	// TODO: Add your control notification handler code here
//}

void CIcrDsp101cP10Dlg::OnEnKillfocusPldpins()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrDsp101cP10Dlg::OnEnKillfocusPldvolume()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

//void CIcrDsp101cP10Dlg::OnEnKillfocusDiopldnum()
//{
//	// TODO: Add your control notification handler code here
//}

void CIcrDsp101cP10Dlg::OnEnKillfocusDiopldpins()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrDsp101cP10Dlg::OnEnKillfocusDiopldvol()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrDsp101cP10Dlg::SetMaskOnCheckBoxes(UINT mask, int idx)
{
	for(int i = 0; i < 10; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		int stat = (mask >> i) & 0x1;
		pProc->SetCheck(stat);
	}
}

void CIcrDsp101cP10Dlg::GetMaskOnCheckBoxes(UINT& mask, int idx)
{
	mask = 0;
	for(int i = 0; i < 10; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		UINT stat = pProc->GetCheck();
		mask |= (stat << i);
	}
}

void CIcrDsp101cP10Dlg::SetPldName() 
{
	int nIndex = m_ctrlPldType.GetCurSel();
	CString strPldType;
	m_ctrlPldType.GetLBText(nIndex, strPldType);

	CString strPldPins;
	strPldPins.Format(_T("%d"), m_PldPins);

	nIndex = m_ctrlPldRate.GetCurSel();
	CString strPldRate;
	m_ctrlPldRate.GetLBText(nIndex, strPldRate);

	CString strPldVolume;
	strPldVolume.Format(_T("%d"), m_PldVolume);

	CString strPldTypeVolume;

	if(strPldType.Find("...") != -1)
		strPldTypeVolume = strPldType.SpanExcluding("...") + strPldVolume + strPldType.Right(1);
	else
		strPldTypeVolume = strPldType + strPldVolume;

	if(strPldType.GetAt(0) == 'E')
		m_strPldName = strPldTypeVolume + ".." + strPldPins + "-" + strPldRate;
	if(strPldType.GetAt(0) == 'X')
		m_strPldName = strPldTypeVolume + "-" + strPldRate + ".." + strPldPins;

	UpdateData(FALSE); // from variable to window
}

void CIcrDsp101cP10Dlg::SetDioPldName() 
{
	int nIndex = m_ctrlDioPldType.GetCurSel();
	CString strPldType;
	m_ctrlDioPldType.GetLBText(nIndex, strPldType);

	CString strPldPins;
	strPldPins.Format(_T("%d"), m_DioPldPins);

	nIndex = m_ctrlDioPldRate.GetCurSel();
	CString strPldRate;
	m_ctrlDioPldRate.GetLBText(nIndex, strPldRate);

	CString strPldVolume;
	strPldVolume.Format(_T("%d"), m_DioPldVol);

	CString strPldTypeVolume;

	if(strPldType.Find("...") != -1)
		strPldTypeVolume = strPldType.SpanExcluding("...") + strPldVolume + strPldType.Right(1);
	else
		strPldTypeVolume = strPldType + strPldVolume;

	if(strPldType.GetAt(0) == 'E')
		m_strDioPldName = strPldTypeVolume + ".." + strPldPins + "-" + strPldRate;
	if(strPldType.GetAt(0) == 'X')
		m_strDioPldName = strPldTypeVolume + "-" + strPldRate + ".." + strPldPins;

	UpdateData(FALSE); // from variable to window
}

