// IcrAdp101pciDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAdp101pciApp.h"
#include "IcrAdp101pciDlg.h"


// CIcrAdp101pciDlg dialog

IMPLEMENT_DYNAMIC(CIcrAdp101pciDlg, CDialog)
CIcrAdp101pciDlg::CIcrAdp101pciDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAdp101pciDlg::IDD, pParent)
{
	m_strPldName = _T("");
	m_PldNum = 0;
	m_PldPins = 0;
	m_PldVolume = 0;
	m_HostPldCnt = 0;
	m_BusClock = 100.0;
}

CIcrAdp101pciDlg::~CIcrAdp101pciDlg()
{
}

void CIcrAdp101pciDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SDRAMSIZE, m_ctrlSdramSize);
	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Control(pDX, IDC_PLDRATE, m_ctrlPldRate);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlPldType);
	DDX_Control(pDX, IDC_SPINPLDCNT, m_ctrlSpinPldCnt);
	DDX_Control(pDX, IDC_SPINPLDNUM, m_ctrlSpinPldNum);
	DDX_Text(pDX, IDC_PLDNAME, m_strPldName);
	DDX_Text(pDX, IDC_PLDNUM, m_PldNum);
	DDX_Text(pDX, IDC_PLDPINS, m_PldPins);
	DDX_Text(pDX, IDC_PLDVOLUME, m_PldVolume);
	DDX_Text(pDX, IDC_HOSTPLDCNT, m_HostPldCnt);
	DDX_Text(pDX, IDC_BUSCLOCK, m_BusClock);
}


BEGIN_MESSAGE_MAP(CIcrAdp101pciDlg, CDialog)
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_PLDPINS, OnEnKillfocusPldpins)
	ON_CBN_SELCHANGE(IDC_PLDTYPE, OnCbnSelchangePldtype)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, OnEnKillfocusPldvolume)
	ON_CBN_SELCHANGE(IDC_PLDRATE, OnCbnSelchangePldrate)
END_MESSAGE_MAP()


// CIcrAdp101pciDlg message handlers

BOOL CIcrAdp101pciDlg::OnInitDialog()
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

	m_ctrlPldType.SetCurSel(m_PldType);
	m_ctrlPldRate.SetCurSel(m_PldRate);
	SetPldName();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIcrAdp101pciDlg::OnDestroy()
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
	m_PldType = m_ctrlPldType.GetCurSel();
	m_PldRate = m_ctrlPldRate.GetCurSel();
}

void CIcrAdp101pciDlg::SetPldName() 
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

BOOL CIcrAdp101pciDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CIcrAdp101pciDlg::OnEnKillfocusPldpins()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAdp101pciDlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAdp101pciDlg::OnEnKillfocusPldvolume()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAdp101pciDlg::OnCbnSelchangePldrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}
