// IcrAds10x2GDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAds10x2GApp.h"
#include "IcrAds10x2GDlg.h"


// CIcrAds10x2GDlg dialog

IMPLEMENT_DYNAMIC(CIcrAds10x2GDlg, CDialog)
CIcrAds10x2GDlg::CIcrAds10x2GDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAds10x2GDlg::IDD, pParent)
	, m_SysGen(66000000)
	, m_PllRefGen(40000000)
	, m_PllFreq(2000000000)
	, m_SdramCnt(0)
	, m_SdramNum(0)
	, m_SdramModules(0)
	, m_SdramRowAddrBits(0)
	, m_SdramColAddrBits(0)
	, m_SdramModuleBanks(0)
	, m_SdramChipBanks(0)
	, m_SdramCasLat(0)
	, m_SdramPrimWidth(0)
{
	m_NumOfAdc = 1;
	m_AdcRateMax = 2000000000;
	m_AdcRateMin = 200000000;
	m_AdcRange = 500;
}

CIcrAds10x2GDlg::~CIcrAds10x2GDlg()
{
}

void CIcrAds10x2GDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_Text(pDX, IDC_PLLREFGEN, m_PllRefGen);
	DDX_Text(pDX, IDC_PLLFREQ, m_PllFreq);
	
	DDX_Text(pDX, IDC_NUMOFADC, m_NumOfAdc);
	DDX_Control(pDX, IDC_SPINADC, m_ctrlSpinAdc);
	DDV_MinMaxUInt(pDX, m_NumOfAdc, 1, 32);
	DDX_Text(pDX, IDC_ADCRATEMAX, m_AdcRateMax);
	DDX_Text(pDX, IDC_ADCRATEMIN, m_AdcRateMin);
	DDX_Text(pDX, IDC_ADCRANGE, m_AdcRange);

	DDX_Text(pDX, IDC_SDRAMCNT, m_SdramCnt);
	DDX_Text(pDX, IDC_SDRAMNUM, m_SdramNum);
	DDX_CBIndex(pDX, IDC_SDRAMDIMMS, m_SdramModules);
	DDX_CBIndex(pDX, IDC_SDRAMROWBITS, m_SdramRowAddrBits);
	DDX_CBIndex(pDX, IDC_SDRAMCOLBITS, m_SdramColAddrBits);
	DDX_CBIndex(pDX, IDC_SDRAMDIMMBANKS, m_SdramModuleBanks);
	DDX_CBIndex(pDX, IDC_SDRAMCHIPBANKS, m_SdramChipBanks);
	DDX_CBIndex(pDX, IDC_SDRAMCASLAT, m_SdramCasLat);
	DDX_Control(pDX, IDC_SPINSDRAM, m_ctrlSpinSdram);
	DDX_Control(pDX, IDC_SPINSDRAMNUM, m_ctrlSpinSdramNum);
	DDX_CBIndex(pDX, IDC_SDRAMPRIMWIDTH, m_SdramPrimWidth);
}


BEGIN_MESSAGE_MAP(CIcrAds10x2GDlg, CDialog)
END_MESSAGE_MAP()


// CIcrAds10x2GDlg message handlers

BOOL CIcrAds10x2GDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrAds10x2GDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinAdc.SetRange(0, 32);

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLLREFGEN), IDC_PLLREFGEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLLFREQ), IDC_PLLFREQ);

    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADC), IDC_NUMOFADC);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRANGE), IDC_ADCRANGE);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMAX), IDC_ADCRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADCRATEMIN), IDC_ADCRATEMIN);

	m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCNT), IDC_SDRAMCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMNUM), IDC_SDRAMNUM);

    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMDIMMS), IDC_SDRAMDIMMS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMROWBITS), IDC_SDRAMROWBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCOLBITS), IDC_SDRAMCOLBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMDIMMBANKS), IDC_SDRAMDIMMBANKS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCHIPBANKS), IDC_SDRAMCHIPBANKS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMPRIMWIDTH), IDC_SDRAMPRIMWIDTH);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCASLAT), IDC_SDRAMCASLAT);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	ULONG bBrdMemSize = (1 << (m_SdramRowAddrBits + 11)) *
						 (1 << (m_SdramColAddrBits + 8)) * 
						 (1 << m_SdramModuleBanks) * 
						 (2 << m_SdramChipBanks) *
						 (1 << m_SdramModules) * 8; // in bytes
	ULONG mBrdMemSize = bBrdMemSize / 1024 / 1024; // in MBytes

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

