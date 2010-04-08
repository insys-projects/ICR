// IcrAmbpexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAmbpex5App.h"
#include "IcrAmbpex5Dlg.h"


// CIcrAmbpex5Dlg dialog

IMPLEMENT_DYNAMIC(CIcrAmbpex5Dlg, CDialog)

CIcrAmbpex5Dlg::CIcrAmbpex5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAmbpex5Dlg::IDD, pParent)
	, m_SysGen(66000000)
	, m_isDds(FALSE)
	, m_DdsType(0)
	, m_isSRAM(FALSE)
	, m_SramChips(0)
	, m_SramSize(0)
	, m_SramBitsWidth(0)
	, m_Gen5(156.25)
	, m_SfpCnt(0)
{
	m_strSramVol = _T("");
}

CIcrAmbpex5Dlg::~CIcrAmbpex5Dlg()
{
}

void CIcrAmbpex5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_Check(pDX, IDC_DDSBE, m_isDds);
	DDX_CBIndex(pDX, IDC_DDSTYPE, m_DdsType);
	DDX_Check(pDX, IDC_SRAMBE, m_isSRAM);
	DDX_CBIndex(pDX, IDC_SRAMCHIPS, m_SramChips);
	DDX_CBIndex(pDX, IDC_SRAMSIZE, m_SramSize);
	DDX_CBIndex(pDX, IDC_SRAMBITSWIDTH, m_SramBitsWidth);
	DDX_Text(pDX, IDC_SRAMVOL, m_strSramVol);
	DDX_Text(pDX, IDC_GEN5, m_Gen5);
	DDX_CBIndex(pDX, IDC_SFP, m_SfpCnt);
}


BEGIN_MESSAGE_MAP(CIcrAmbpex5Dlg, CDialog)
	ON_BN_CLICKED(IDC_DDSBE, OnBnClickedDdsbe)
	ON_BN_CLICKED(IDC_SRAMBE, OnBnClickedSrambe)
	ON_CBN_SELCHANGE(IDC_SRAMCHIPS, &CIcrAmbpex5Dlg::OnCbnSelchangeSramchips)
	ON_CBN_SELCHANGE(IDC_SRAMSIZE, &CIcrAmbpex5Dlg::OnCbnSelchangeSramsize)
	ON_CBN_SELCHANGE(IDC_SRAMBITSWIDTH, &CIcrAmbpex5Dlg::OnCbnSelchangeSrambitswidth)
END_MESSAGE_MAP()


// CIcrAmbpex5Dlg message handlers
BOOL CIcrAmbpex5Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrAmbpex5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);


    m_ToolTip.AddTool(GetDlgItem(IDC_DDSBE), IDC_DDSBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_DDSTYPE), IDC_DDSTYPE);
	
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMBE), IDC_SRAMBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMCHIPS), IDC_SRAMCHIPS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMSIZE), IDC_SRAMSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMBITSWIDTH), IDC_SRAMBITSWIDTH);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);

	CWnd* pSramChips = (CWnd*)GetDlgItem(IDC_SRAMCHIPS);
	pSramChips->EnableWindow(m_isSRAM);
	CWnd* pSramSize = (CWnd*)GetDlgItem(IDC_SRAMSIZE);
	pSramSize->EnableWindow(m_isSRAM);
	CWnd* pSramWidth = (CWnd*)GetDlgItem(IDC_SRAMBITSWIDTH);
	pSramWidth->EnableWindow(m_isSRAM);

	//if(m_SdramSize == 2048) // 2 Ãבאיע
	//	m_ctrlSdramSize.SetCurSel(3);
	//else
	//	if(m_SdramSize == 1024) // 1 Ãבאיע
	//		m_ctrlSdramSize.SetCurSel(2);
	//	else
	//		if(m_SdramSize == 512) // 512 Ìבאיע
	//			m_ctrlSdramSize.SetCurSel(1);
	//		else
	//			m_ctrlSdramSize.SetCurSel(0); // 0 Ãבאיע - םוע

	SetSramVol();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//void CIcrAmbpex5Dlg::OnDestroy()
//{
//	CDialog::OnDestroy();
//
//	// TODO: Add your message handler code here
//	switch(m_ctrlSdramSize.GetCurSel())
//	{
//	case 0:
//		m_SdramSize = 0;
//		break;
//	case 1:
//		m_SdramSize = 512;
//		break;
//	case 2:
//		m_SdramSize = 1024;
//		break;
//	case 3:
//		m_SdramSize = 2 * 1024;
//		break;
//	}
//}

void CIcrAmbpex5Dlg::OnBnClickedDdsbe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);
}

void CIcrAmbpex5Dlg::OnBnClickedSrambe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pSramChips = (CWnd*)GetDlgItem(IDC_SRAMCHIPS);
	pSramChips->EnableWindow(m_isSRAM);
	CWnd* pSramSize = (CWnd*)GetDlgItem(IDC_SRAMSIZE);
	pSramSize->EnableWindow(m_isSRAM);
	CWnd* pSramWidth = (CWnd*)GetDlgItem(IDC_SRAMBITSWIDTH);
	pSramWidth->EnableWindow(m_isSRAM);
}

void CIcrAmbpex5Dlg::SetSramVol()
{
	double size = 0;
	if(m_isSRAM)
	{
		int chips = m_SramChips + 1;
		int deepM = (m_SramSize == 3) ? m_SramSize+1 : m_SramSize;
		int width;
		if(m_SramBitsWidth < 9)
			width = 8 << (m_SramBitsWidth-1);
		else
			width = 9 << (m_SramBitsWidth-9);
		size = (chips * deepM * width) / 8.;
	}
	m_strSramVol.Format("%.2f Mbytes", size);
	UpdateData(FALSE); // from variable to window
}

void CIcrAmbpex5Dlg::OnCbnSelchangeSramchips()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetSramVol();
}

void CIcrAmbpex5Dlg::OnCbnSelchangeSramsize()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetSramVol();
}

void CIcrAmbpex5Dlg::OnCbnSelchangeSrambitswidth()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetSramVol();
}
