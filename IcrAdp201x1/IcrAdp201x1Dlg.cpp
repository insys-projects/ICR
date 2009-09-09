// IcrAdp201x1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAdp201x1App.h"
#include "IcrAdp201x1Dlg.h"


// CIcrAdp201x1Dlg dialog

IMPLEMENT_DYNAMIC(CIcrAdp201x1Dlg, CDialog)

CIcrAdp201x1Dlg::CIcrAdp201x1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAdp201x1Dlg::IDD, pParent)
	, m_SysGen(250000000)
	, m_isDds(FALSE)
	, m_DdsType(0)
	, m_isLLCU(FALSE)
	, m_PldSdramSize(0)
	, m_MGTGen(156.25)
	, m_isCPU(FALSE)
	, m_CpuClk(600)
	, m_CpuSdramSize(0)
	, m_CpuFlashSize(0)
	, m_RefCpuGen(100.00)
{

}

CIcrAdp201x1Dlg::~CIcrAdp201x1Dlg()
{
}

void CIcrAdp201x1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_Check(pDX, IDC_DDSBE, m_isDds);
	DDX_CBIndex(pDX, IDC_DDSTYPE, m_DdsType);
	DDX_Check(pDX, IDC_LLCU, m_isLLCU);
	DDX_Control(pDX, IDC_PLDSDRAM, m_ctrlPldSdramSize);
	//DDX_CBIndex(pDX, IDC_PLDSDRAM, m_PldSdramSize);
	DDX_Text(pDX, IDC_MGTGEN, m_MGTGen);
	DDX_Check(pDX, IDC_CPUBE, m_isCPU);
	DDX_Control(pDX, IDC_CPUCLK, m_ctrlCpuClock);
	DDX_Control(pDX, IDC_CPUSDRAM, m_ctrlCpuSdramSize);
	DDX_Control(pDX, IDC_CPUFLASH, m_ctrlCpuFlashSize);
	//DDX_CBIndex(pDX, IDC_CPUCLK, m_CpuClk);
	//DDX_CBIndex(pDX, IDC_CPUSDRAM, m_CpuSdramSize);
	//DDX_CBIndex(pDX, IDC_CPUFLASH, m_CpuFlashSize);
	DDX_Text(pDX, IDC_REFCPUGEN, m_RefCpuGen);
}

BEGIN_MESSAGE_MAP(CIcrAdp201x1Dlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DDSBE, OnBnClickedDdsbe)
	ON_BN_CLICKED(IDC_CPUBE, OnBnClickedCpube)
END_MESSAGE_MAP()


// CIcrAdp201x1Dlg message handlers
BOOL CIcrAdp201x1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrAdp201x1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);

    m_ToolTip.AddTool(GetDlgItem(IDC_DDSBE), IDC_DDSBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_DDSTYPE), IDC_DDSTYPE);
	
    m_ToolTip.AddTool(GetDlgItem(IDC_CPUBE), IDC_CPUBE);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);

	if(m_PldSdramSize == 2048) // 2 Ãבאיע
		m_ctrlPldSdramSize.SetCurSel(2);
	else
		if(m_PldSdramSize == 1024) // 1 Ãבאיע
			m_ctrlPldSdramSize.SetCurSel(1);
		else
			m_ctrlPldSdramSize.SetCurSel(0); // 0 Ãבאיע - םוע

	if(m_CpuClk < (500 + (600 - 500) / 2))
		m_ctrlCpuClock.SetCurSel(0); // 500 ÌÃצ
	else
		m_ctrlCpuClock.SetCurSel(1); // 600 ÌÃצ

	if(m_CpuSdramSize == 512) // 512 Ìבאיע
		m_ctrlCpuSdramSize.SetCurSel(3);
	else
		if(m_CpuSdramSize == 256) // 256 Ìבאיע
			m_ctrlCpuSdramSize.SetCurSel(2);
		else
			if(m_CpuSdramSize == 128) // 128 Ìבאיע
				m_ctrlCpuSdramSize.SetCurSel(1);
			else
				m_ctrlCpuSdramSize.SetCurSel(0); // 0 Ìבאיע - םוע

	if(m_CpuFlashSize == 4096) // 4 Ìבאיע
		m_ctrlCpuFlashSize.SetCurSel(2);
	else
		if(m_CpuFlashSize == 2048) // 2 Ìבאיע
			m_ctrlCpuFlashSize.SetCurSel(1);
		else
			m_ctrlCpuFlashSize.SetCurSel(0); // 0 Ãבאיע - םוע

	CWnd* pClk = (CWnd*)GetDlgItem(IDC_CPUCLK);
	pClk->EnableWindow(m_isCPU);
	CWnd* pSdram = (CWnd*)GetDlgItem(IDC_CPUSDRAM);
	pSdram->EnableWindow(m_isCPU);
	CWnd* pFlash = (CWnd*)GetDlgItem(IDC_CPUFLASH);
	pFlash->EnableWindow(m_isCPU);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIcrAdp201x1Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if(m_ctrlCpuClock.GetCurSel())
		m_CpuClk = 600;
	else
		m_CpuClk = 500;
	switch(m_ctrlPldSdramSize.GetCurSel())
	{
	case 0:
		m_PldSdramSize = 0;
		break;
	case 1:
		m_PldSdramSize = 1024;
		break;
	case 2:
		m_PldSdramSize = 2 * 1024;
		break;
	}
	switch(m_ctrlCpuSdramSize.GetCurSel())
	{
	case 0:
		m_CpuSdramSize = 0;
		break;
	case 1:
		m_CpuSdramSize = 128;
		break;
	case 2:
		m_CpuSdramSize = 256;
		break;
	case 3:
		m_CpuSdramSize = 512;
		break;
	}
	switch(m_ctrlCpuFlashSize.GetCurSel())
	{
	case 0:
		m_CpuFlashSize = 0;
		break;
	case 1:
		m_CpuFlashSize = 2048; // 2 ÌÁאיעא
		break;
	case 2:
		m_CpuFlashSize = 4096; // 4 ÌÁאיעא
		break;
	}
}

void CIcrAdp201x1Dlg::OnBnClickedDdsbe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);
}

void CIcrAdp201x1Dlg::OnBnClickedCpube()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pClk = (CWnd*)GetDlgItem(IDC_CPUCLK);
	pClk->EnableWindow(m_isCPU);
	CWnd* pSdram = (CWnd*)GetDlgItem(IDC_CPUSDRAM);
	pSdram->EnableWindow(m_isCPU);
	CWnd* pFlash = (CWnd*)GetDlgItem(IDC_CPUFLASH);
	pFlash->EnableWindow(m_isCPU);
}
