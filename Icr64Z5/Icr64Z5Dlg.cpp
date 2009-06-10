// Icr64Z5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr64Z5App.h"
#include "Icr64Z5Dlg.h"


// Icr64Z5Dlg dialog

IMPLEMENT_DYNAMIC(Icr64Z5Dlg, CDialog)

Icr64Z5Dlg::Icr64Z5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr64Z5Dlg::IDD, pParent)
{

}

Icr64Z5Dlg::~Icr64Z5Dlg()
{
}

void Icr64Z5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CPUNAME, m_ctrlCpuName);
	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Control(pDX, IDC_DDR2SIZE, m_ctrlSizeOfDDR2);
	DDX_Control(pDX, IDC_FLASHSIZE, m_ctrlSizeOfFlash);
	DDX_Control(pDX, IDC_EMACSET, m_ctrlSetEMAC);
	DDX_Control(pDX, IDC_SRIOTYPE, m_ctrlTypeSRIO);
}


BEGIN_MESSAGE_MAP(Icr64Z5Dlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Icr64Z5Dlg message handlers

BOOL Icr64Z5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_CPUNAME), IDC_CPUNAME);
	m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
	m_ToolTip.AddTool(GetDlgItem(IDC_DDR2SIZE), IDC_DDR2SIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_FLASHSIZE), IDC_FLASHSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_EMACSET), IDC_EMACSET);
	m_ToolTip.AddTool(GetDlgItem(IDC_SRIOTYPE), IDC_SRIOTYPE);

	m_ctrlCpuName.SetCurSel(m_bCpuName);

	switch(m_wMaxCpuClock)
	{
		case 1200: m_ctrlMaxCpuClock.SetCurSel(0); break;
	}

	switch(m_wSizeOfDDR2)
	{
		case   0: m_ctrlSizeOfDDR2.SetCurSel(0); break;
		case 256: m_ctrlSizeOfDDR2.SetCurSel(1); break;
		case 512: m_ctrlSizeOfDDR2.SetCurSel(2); break;
	}

	switch(m_wSizeOfFlash)
	{
		case 0: m_ctrlSizeOfFlash.SetCurSel(0); break;
		case 4: m_ctrlSizeOfFlash.SetCurSel(1); break;
	}
		
	if(m_isSetEMAC)
		m_ctrlSetEMAC.SetCheck(TRUE);
	else
		m_ctrlSetEMAC.SetCheck(FALSE);

	switch(m_bTypeSRIO)
	{
		case 0: m_ctrlTypeSRIO.SetCurSel(0); break;
		case 1: m_ctrlTypeSRIO.SetCurSel(1); break;
		case 2: m_ctrlTypeSRIO.SetCurSel(2); break;
		case 3: m_ctrlTypeSRIO.SetCurSel(3); break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr64Z5Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr64Z5Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	m_bCpuName = m_ctrlCpuName.GetCurSel();

	switch(m_ctrlMaxCpuClock.GetCurSel())
	{
		case 0: m_wMaxCpuClock = 1200; break;
	}

	switch(m_ctrlSizeOfDDR2.GetCurSel())
	{
		case 0: m_wSizeOfDDR2 = 0;   break;
		case 1: m_wSizeOfDDR2 = 256; break;
		case 2: m_wSizeOfDDR2 = 512; break;
	}

	switch(m_ctrlSizeOfFlash.GetCurSel())
	{
		case 0: m_wSizeOfFlash = 0; break;
		case 1: m_wSizeOfFlash = 4; break;
	}

	if(m_ctrlSetEMAC.GetCheck())
		m_isSetEMAC = 1;
	else
		m_isSetEMAC = 0;

	switch(m_ctrlTypeSRIO.GetCurSel())
	{
		case 0: m_bTypeSRIO = 0; break;
		case 1: m_bTypeSRIO = 1; break;
		case 2: m_bTypeSRIO = 2; break;
		case 3: m_bTypeSRIO = 3; break;
	}
}
