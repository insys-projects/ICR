// Icr64Z1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr64Z1App.h"
#include "Icr64Z1Dlg.h"


// Icr64Z1Dlg dialog

IMPLEMENT_DYNAMIC(Icr64Z1Dlg, CDialog)

Icr64Z1Dlg::Icr64Z1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr64Z1Dlg::IDD, pParent)
{

}

Icr64Z1Dlg::~Icr64Z1Dlg()
{
}

void Icr64Z1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Control(pDX, IDC_SDRAMSIZEA, m_ctrlSdramASize);
	DDX_Control(pDX, IDC_SDRAMSIZEB, m_ctrlSdramBSize);
	DDX_Control(pDX, IDC_FLASH, m_ctrlFlashSize);
	DDX_Control(pDX, IDC_CPUNAME, m_ctrlCpuName);
}


BEGIN_MESSAGE_MAP(Icr64Z1Dlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Icr64Z1Dlg message handlers

BOOL Icr64Z1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
	m_ToolTip.AddTool(GetDlgItem(IDC_CPUNAME), IDC_CPUNAME);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZEA), IDC_SDRAMSIZEA);
	m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZEB), IDC_SDRAMSIZEB);
	m_ToolTip.AddTool(GetDlgItem(IDC_FLASH), IDC_FLASH);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	if( m_MaxCpuClock < (600 + (720 - 600) / 2) )
		m_ctrlMaxCpuClock.SetCurSel(0);
	else
		if( m_MaxCpuClock < (720 + (1000 - 720) / 2) )
			m_ctrlMaxCpuClock.SetCurSel(1);
		else
			m_ctrlMaxCpuClock.SetCurSel(2);

	if( m_CpuName )
		m_ctrlCpuName.SetCurSel(1);
	else
		m_ctrlCpuName.SetCurSel(0);

	if(m_SdramASize <= 128 * 1024 * 1024 / 2)
		m_ctrlSdramASize.SetCurSel(0);
	else
		if(m_SdramASize <= 256 * 1024 * 1024 / 2)
			m_ctrlSdramASize.SetCurSel(1);
		else
			if(m_SdramASize <= 512 * 1024 * 1024 / 2)
				m_ctrlSdramASize.SetCurSel(2);
			else
				m_ctrlSdramASize.SetCurSel(3);

	if( m_SdramBSize <= 32 * 1024 * 1024 / 2 )
		m_ctrlSdramBSize.SetCurSel(0);
	else
		m_ctrlSdramBSize.SetCurSel(1);

	if( m_FlashSize <= 2 * 1024 * 1024 / 2 )
		m_ctrlFlashSize.SetCurSel(0);
	else
		if( m_FlashSize <= 4 * 1024 * 1024 / 2 )
			m_ctrlFlashSize.SetCurSel(1);
		else
			m_ctrlFlashSize.SetCurSel(2);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr64Z1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr64Z1Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	switch( m_ctrlMaxCpuClock.GetCurSel() )
	{
		case 0:
			m_MaxCpuClock = 600;
			break;
		case 1:
			m_MaxCpuClock = 720;
			break;
		case 2:
			m_MaxCpuClock = 1000;
			break;
	}
	if( m_ctrlCpuName.GetCurSel() )
		m_CpuName = 1;
	else
		m_CpuName = 0;
	switch( m_ctrlSdramASize.GetCurSel() )
	{
	case 0:
		m_SdramASize = 0;
		break;
	case 1:
		m_SdramASize = 128 * 1024 * 1024;
		break;
	case 2:
		m_SdramASize = 256 * 1024 * 1024;
		break;
	case 3:
		m_SdramASize = 512 * 1024 * 1024;
		break;
	}
	if(m_ctrlSdramBSize.GetCurSel())
		m_SdramBSize = 32 * 1024 * 1024;
	else
		m_SdramBSize = 0;
	switch( m_ctrlFlashSize.GetCurSel())
	{
	case 0:
		m_FlashSize = 0;
		break;
	case 1:
		m_FlashSize = 2 * 1024 * 1024;
		break;
	case 2:
		m_FlashSize = 4 * 1024 * 1024;
		break;
	}
}
