// IcrSync8chPCIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrSync8chPCIApp.h"
#include "IcrSync8chPCIDlg.h"


// CIcrSync8chPCIDlg dialog

IMPLEMENT_DYNAMIC(CIcrSync8chPCIDlg, CDialog)
CIcrSync8chPCIDlg::CIcrSync8chPCIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrSync8chPCIDlg::IDD, pParent)
	, m_SysGen(66000000)
	, m_Gen1(200000000)
	, m_Gen2(0)
	, m_OcxoGen(0)
	, m_PllFreq(0)
	, m_ClkChanCnt(2)
	, m_StrbChanCnt(2)
	, m_ClkE(0)
	, m_ClkF(0)
	, m_StrboA(0)
	, m_StrboB(0)
	, m_StrboD(0)
	, m_Sync(0)
	, m_IsLF(0)
{
}

CIcrSync8chPCIDlg::~CIcrSync8chPCIDlg()
{
}

void CIcrSync8chPCIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_Text(pDX, IDC_GEN1, m_Gen1);
	DDX_Text(pDX, IDC_GEN2, m_Gen2);
	DDX_Text(pDX, IDC_OCXOGEN, m_OcxoGen);
	DDX_Text(pDX, IDC_PLLFREQ, m_PllFreq);
	
	DDX_CBIndex(pDX, IDC_CLKCHANS, m_ClkChanCnt);
	DDX_CBIndex(pDX, IDC_STRBCHANS, m_StrbChanCnt);
	DDX_Check(pDX, IDC_CLKE, m_ClkE);
	DDX_Check(pDX, IDC_CLKF, m_ClkF);
	DDX_Check(pDX, IDC_STROA, m_StrboA);
	DDX_Check(pDX, IDC_STROB, m_StrboB);
	DDX_Check(pDX, IDC_STROD, m_StrboD);
	DDX_Check(pDX, IDC_SYNC, m_Sync);
	DDX_CBIndex(pDX, IDC_FREQRANGE, m_IsLF);
}


BEGIN_MESSAGE_MAP(CIcrSync8chPCIDlg, CDialog)
END_MESSAGE_MAP()


// CIcrSync8chPCIDlg message handlers

BOOL CIcrSync8chPCIDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrSync8chPCIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);
    //m_ToolTip.AddTool(GetDlgItem(IDC_PLLREFGEN), IDC_PLLREFGEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLLFREQ), IDC_PLLFREQ);

 //   m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADC), IDC_NUMOFADC);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGE), IDC_ADCRANGE);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMAX), IDC_ADCRATEMAX);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMIN), IDC_ADCRATEMIN);

	//m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCNT), IDC_SDRAMCNT);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMNUM), IDC_SDRAMNUM);

 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMDIMMS), IDC_SDRAMDIMMS);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMROWBITS), IDC_SDRAMROWBITS);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCOLBITS), IDC_SDRAMCOLBITS);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMDIMMBANKS), IDC_SDRAMDIMMBANKS);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCHIPBANKS), IDC_SDRAMCHIPBANKS);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMPRIMWIDTH), IDC_SDRAMPRIMWIDTH);
 //   m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCASLAT), IDC_SDRAMCASLAT);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

