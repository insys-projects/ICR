// IcrAmbpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAmbpApp.h"
#include "IcrAmbpDlg.h"
#include ".\icrambpdlg.h"


// CIcrAmbpDlg dialog

IMPLEMENT_DYNAMIC(CIcrAmbpDlg, CDialog)
CIcrAmbpDlg::CIcrAmbpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAmbpDlg::IDD, pParent)
	, m_SlotCnt(0)
	, m_SdramCnt(0)
	, m_DspNodeCnt(0)
	, m_SdramNum(0)
	, m_SdramModules(0)
	, m_SdramRowAddrBits(0)
	, m_SdramColAddrBits(0)
	, m_SdramModuleBanks(0)
	, m_SdramChipBanks(0)
	, m_SdramCasLat(0)
	, m_DspNodeNum(0)
	, m_DspPldType(0)
	, m_DspPldVolume(0)
	, m_DspPldPins(0)
	, m_DspPldRate(0)
	, m_LoadRom(0)
	, m_strDspPldName(_T(""))
	, m_isPio(FALSE)
	, m_PioType(0)
	, m_isSRAM(FALSE)
	, m_SramChips(0)
	, m_SramSize(0)
	, m_SramBitsWidth(0)
	, m_SysGen(66000000)
	, m_SdramPrimWidth(0)
{
}

CIcrAmbpDlg::~CIcrAmbpDlg()
{
}

void CIcrAmbpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_SDRAMSLOTS, m_SlotCnt);
	DDX_Text(pDX, IDC_SDRAMCNT, m_SdramCnt);
	DDX_Text(pDX, IDC_DSPCNT, m_DspNodeCnt);
	DDX_Text(pDX, IDC_SDRAMNUM, m_SdramNum);
	DDX_CBIndex(pDX, IDC_SDRAMDIMMS, m_SdramModules);
	DDX_CBIndex(pDX, IDC_SDRAMROWBITS, m_SdramRowAddrBits);
	DDX_CBIndex(pDX, IDC_SDRAMCOLBITS, m_SdramColAddrBits);
	DDX_CBIndex(pDX, IDC_SDRAMDIMMBANKS, m_SdramModuleBanks);
	DDX_CBIndex(pDX, IDC_SDRAMCHIPBANKS, m_SdramChipBanks);
	DDX_CBIndex(pDX, IDC_SDRAMCASLAT, m_SdramCasLat);
	DDX_Control(pDX, IDC_SPINSDRAM, m_ctrlSpinSdram);
	DDX_Control(pDX, IDC_SPINSDRAMNUM, m_ctrlSpinSdramNum);
	DDX_Control(pDX, IDC_SPINDSPCNT, m_ctrlSpinDspNode);
	DDX_Text(pDX, IDC_DSPNUM, m_DspNodeNum);
	DDX_Control(pDX, IDC_SPINDSPNUM, m_ctrlSpinDspNodeNum);
	//	DDX_CBIndex(pDX, IDC_PLDTYPE, m_DspPldType);
	DDX_Text(pDX, IDC_PLDVOLUME, m_DspPldVolume);
	DDX_Text(pDX, IDC_PLDPINS, m_DspPldPins);
	//	DDX_CBIndex(pDX, IDC_PLDRATE, m_DspPldRate);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlDspPldType);
	DDX_Control(pDX, IDC_PLDRATE, m_ctrlDspPldRate);
	DDX_CBIndex(pDX, IDC_LOADROM, m_LoadRom);
	DDX_Text(pDX, IDC_PLDNAME, m_strDspPldName);
	DDX_Check(pDX, IDC_PIOBE, m_isPio);
	DDX_CBIndex(pDX, IDC_PIOTYPE, m_PioType);
	DDX_Check(pDX, IDC_SRAMBE, m_isSRAM);
	DDX_CBIndex(pDX, IDC_SRAMCHIPS, m_SramChips);
	DDX_CBIndex(pDX, IDC_SRAMSIZE, m_SramSize);
	DDX_CBIndex(pDX, IDC_SRAMBITSWIDTH, m_SramBitsWidth);
	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_CBIndex(pDX, IDC_SDRAMPRIMWIDTH, m_SdramPrimWidth);
}


BEGIN_MESSAGE_MAP(CIcrAmbpDlg, CDialog)
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_PLDPINS, OnEnKillfocusPldpins)
	ON_CBN_SELCHANGE(IDC_PLDTYPE, OnCbnSelchangePldtype)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, OnEnKillfocusPldvolume)
	ON_CBN_SELCHANGE(IDC_PLDRATE, OnCbnSelchangePldrate)
	ON_BN_CLICKED(IDC_PIOBE, OnBnClickedPiobe)
	ON_BN_CLICKED(IDC_SRAMBE, OnBnClickedSrambe)
END_MESSAGE_MAP()


// CIcrAmbpDlg message handlers

void CIcrAmbpDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CIcrAmbpDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrAmbpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSLOTS), IDC_SDRAMSLOTS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCNT), IDC_SDRAMCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMNUM), IDC_SDRAMNUM);

    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMDIMMS), IDC_SDRAMDIMMS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMROWBITS), IDC_SDRAMROWBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCOLBITS), IDC_SDRAMCOLBITS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMDIMMBANKS), IDC_SDRAMDIMMBANKS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCHIPBANKS), IDC_SDRAMCHIPBANKS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMPRIMWIDTH), IDC_SDRAMPRIMWIDTH);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMCASLAT), IDC_SDRAMCASLAT);

    m_ToolTip.AddTool(GetDlgItem(IDC_DSPCNT), IDC_DSPCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_DSPNUM), IDC_DSPNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDRATE), IDC_PLDRATE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDVOLUME), IDC_PLDVOLUME);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDPINS), IDC_PLDPINS);
    m_ToolTip.AddTool(GetDlgItem(IDC_LOADROM), IDC_LOADROM);
	
    m_ToolTip.AddTool(GetDlgItem(IDC_PIOBE), IDC_PIOBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PIOTYPE), IDC_PIOTYPE);
	
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMBE), IDC_SRAMBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMCHIPS), IDC_SRAMCHIPS);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMSIZE), IDC_SRAMSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_SRAMBITSWIDTH), IDC_SRAMBITSWIDTH);

	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	m_ctrlDspPldType.SetCurSel(m_DspPldType);
	m_ctrlDspPldRate.SetCurSel(m_DspPldRate);
	SetPldName();

	ULONG bBrdMemSize = (1 << (m_SdramRowAddrBits + 11)) *
						 (1 << (m_SdramColAddrBits + 8)) * 
						 (1 << m_SdramModuleBanks) * 
						 (2 << m_SdramChipBanks) *
						 (1 << m_SdramModules) * 8; // in bytes
	ULONG mBrdMemSize = bBrdMemSize / 1024 / 1024; // in MBytes

	CWnd* pPioType = (CWnd*)GetDlgItem(IDC_PIOTYPE);
	pPioType->EnableWindow(m_isPio);

	CWnd* pSramChips = (CWnd*)GetDlgItem(IDC_SRAMCHIPS);
	pSramChips->EnableWindow(m_isSRAM);
	CWnd* pSramSize = (CWnd*)GetDlgItem(IDC_SRAMSIZE);
	pSramSize->EnableWindow(m_isSRAM);
	CWnd* pSramWidth = (CWnd*)GetDlgItem(IDC_SRAMBITSWIDTH);
	pSramWidth->EnableWindow(m_isSRAM);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIcrAmbpDlg::SetPldName() 
{
	int nIndex = m_ctrlDspPldType.GetCurSel();
	CString strPldType;
	m_ctrlDspPldType.GetLBText(nIndex, strPldType);

	CString strPldPins;
	strPldPins.Format(_T("%d"), m_DspPldPins);

	nIndex = m_ctrlDspPldRate.GetCurSel();
	CString strPldRate;
	m_ctrlDspPldRate.GetLBText(nIndex, strPldRate);

	CString strPldVolume;
	strPldVolume.Format(_T("%d"), m_DspPldVolume);

	CString strPldTypeVolume;

	if(strPldType.Find("...") != -1)
		strPldTypeVolume = strPldType.SpanExcluding("...") + strPldVolume + strPldType.Right(1);
	else
		strPldTypeVolume = strPldType + strPldVolume;

	if(strPldType.GetAt(0) == 'E')
		m_strDspPldName = strPldTypeVolume + ".." + strPldPins + "-" + strPldRate;
	if(strPldType.GetAt(0) == 'X')
		m_strDspPldName = strPldTypeVolume + "-" + strPldRate + ".." + strPldPins;

	UpdateData(FALSE); // from variable to window
}

void CIcrAmbpDlg::OnEnKillfocusPldpins()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAmbpDlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAmbpDlg::OnEnKillfocusPldvolume()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAmbpDlg::OnCbnSelchangePldrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAmbpDlg::OnBnClickedPiobe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pPioType = (CWnd*)GetDlgItem(IDC_PIOTYPE);
	pPioType->EnableWindow(m_isPio);
}

void CIcrAmbpDlg::OnBnClickedSrambe()
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
