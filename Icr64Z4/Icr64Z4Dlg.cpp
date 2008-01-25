// Icr64Z4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr64Z4App.h"
#include "Icr64Z4Dlg.h"


// Icr64Z4Dlg dialog

IMPLEMENT_DYNAMIC(Icr64Z4Dlg, CDialog)

Icr64Z4Dlg::Icr64Z4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr64Z4Dlg::IDD, pParent)
{

}

Icr64Z4Dlg::~Icr64Z4Dlg()
{
}

void Icr64Z4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CPUCNT, m_ctrlCpuCnt);
	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Control(pDX, IDC_FLASHCNT, m_ctrlFlashCnt);
}


BEGIN_MESSAGE_MAP(Icr64Z4Dlg, CDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_CPUCNT, &Icr64Z4Dlg::OnCbnSelchangeCpucnt)
END_MESSAGE_MAP()


// Icr64Z4Dlg message handlers

BOOL Icr64Z4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_CPUCNT), IDC_CPUCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
	m_ToolTip.AddTool(GetDlgItem(IDC_FLASHCNT), IDC_FLASHCNT);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	m_ctrlCpuCnt.SetCurSel(m_CpuCnt);
	if( m_MaxCpuClock < (720 + (840 - 720) / 2) )
		m_ctrlMaxCpuClock.SetCurSel(0);
	else
		if( m_MaxCpuClock < (840 + (1000 - 840) / 2) )
			m_ctrlMaxCpuClock.SetCurSel(1);
		else
			m_ctrlMaxCpuClock.SetCurSel(2);
	m_ctrlFlashCnt.SetCurSel(m_FlashCnt);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr64Z4Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr64Z4Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	m_CpuCnt = m_ctrlCpuCnt.GetCurSel();
	switch( m_ctrlMaxCpuClock.GetCurSel() )
	{
	case 0:
		m_MaxCpuClock = 720;
		break;
	case 1:
		m_MaxCpuClock = 840;
		break;
	case 2:
		m_MaxCpuClock = 1000;
		break;
	}
	m_FlashCnt = m_ctrlFlashCnt.GetCurSel();
}

void Icr64Z4Dlg::OnCbnSelchangeCpucnt()
{
	// TODO: Add your control notification handler code here
}
