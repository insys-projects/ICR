// IcrFmc105pDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrFmc105pApp.h"
#include "IcrFmc105pDlg.h"


// CIcrFmc105pDlg dialog

IMPLEMENT_DYNAMIC(CIcrFmc105pDlg, CDialog)

CIcrFmc105pDlg::CIcrFmc105pDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrFmc105pDlg::IDD, pParent)
	, m_SysGen(250000000)
	, m_isDds(FALSE)
	, m_DdsType(0)
	, m_isSwitch(TRUE)
	, m_SwitchType(1)
	, m_Gen5(156.25)
	, m_Gen6(100.00)
	, m_DspNodeCnt(0)
	, m_DspNodeNum(0)
	, m_DspPldType(0)
	, m_DspPldVolume(0)
	, m_DspPldPins(0)
	, m_DspPldRate(0)
	, m_strDspPldName(_T(""))
{
	m_AdrSwitch = 0x48;
	m_Gen0Type = 0;
	m_AdrGen0 = 0x49;
	m_RefGen0 = 0;
	m_RefMaxGen0 = 280000000;
}

CIcrFmc105pDlg::~CIcrFmc105pDlg()
{
}

void CIcrFmc105pDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SYSGEN, m_SysGen);
	DDX_Check(pDX, IDC_DDSBE, m_isDds);
	DDX_CBIndex(pDX, IDC_DDSTYPE, m_DdsType);
	DDX_Check(pDX, IDC_SWITCHBE, m_isSwitch);
	DDX_CBIndex(pDX, IDC_SWITCHTYPE, m_SwitchType);
	DDX_Text(pDX, IDC_DSPCNT, m_DspNodeCnt);
	DDX_Text(pDX, IDC_GEN5, m_Gen5);
	DDX_Text(pDX, IDC_GEN6, m_Gen6);
	DDX_Control(pDX, IDC_SPINDSPCNT, m_ctrlSpinDspNode);
	DDX_Text(pDX, IDC_DSPNUM, m_DspNodeNum);
	DDX_Control(pDX, IDC_SPINDSPNUM, m_ctrlSpinDspNodeNum);
	DDX_Text(pDX, IDC_PLDVOLUME, m_DspPldVolume);
	DDX_Text(pDX, IDC_PLDPINS, m_DspPldPins);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlDspPldType);
	DDX_Control(pDX, IDC_PLDRATE, m_ctrlDspPldRate);
	DDX_Text(pDX, IDC_PLDNAME, m_strDspPldName);
	//DDX_CBIndex(pDX, IDC_GENTYPE, m_Gen0Type);
	DDX_Control(pDX, IDC_GENTYPE, m_ctrlGen0Type);
	DDX_Text(pDX, IDC_GENREF, m_RefGen0);
	DDX_Text(pDX, IDC_GENREFMAX, m_RefMaxGen0);

	CHAR	strGenAdr[10];
	sprintf_s( strGenAdr, "%X", m_AdrGen0 );
	DDX_Text(pDX, IDC_GENADR, strGenAdr, sizeof(strGenAdr) );
	sscanf_s( strGenAdr, "%X", &m_AdrGen0 );

	CHAR	strSwitchAdr[10];
	sprintf_s(strSwitchAdr, "%X", m_AdrSwitch);
	DDX_Text(pDX, IDC_SWITCHADR, strSwitchAdr, sizeof(strSwitchAdr) );
	sscanf_s(strSwitchAdr, "%X", &m_AdrSwitch);
}


BEGIN_MESSAGE_MAP(CIcrFmc105pDlg, CDialog)
	ON_BN_CLICKED(IDC_DDSBE, OnBnClickedDdsbe)
	ON_BN_CLICKED(IDC_SWITCHBE, OnBnClickedSwitchbe)
	ON_EN_KILLFOCUS(IDC_PLDPINS, OnEnKillfocusPldpins)
	ON_CBN_SELCHANGE(IDC_PLDTYPE, OnCbnSelchangePldtype)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, OnEnKillfocusPldvolume)
	ON_CBN_SELCHANGE(IDC_PLDRATE, OnCbnSelchangePldrate)
	ON_EN_KILLFOCUS(IDC_DSPCNT, &OnEnKillfocusDspcnt)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINDSPCNT, &OnDeltaposSpindspcnt)
	ON_EN_KILLFOCUS(IDC_DSPNUM, &OnEnKillfocusDspnum)
	ON_CBN_SELCHANGE(IDC_GENTYPE, OnCbnSelchangeGentype)
END_MESSAGE_MAP()


// CIcrFmc105pDlg message handlers
BOOL CIcrFmc105pDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
   m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIcrFmc105pDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlSpinDspNode.SetRange(0, MAX_DSPCNT);
	m_ctrlSpinDspNodeNum.SetRange(0, (m_DspNodeCnt ? (m_DspNodeCnt - 1) : 0 ) );
	if( m_DspNodeCnt == 0 )
		LockUnlockDspWindows(LOCK);
	else if ( m_DspNodeCnt > 0 )
		LockUnlockDspWindows(UNLOCK);

	m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SYSGEN), IDC_SYSGEN);

    m_ToolTip.AddTool(GetDlgItem(IDC_DDSBE), IDC_DDSBE);
    m_ToolTip.AddTool(GetDlgItem(IDC_DDSTYPE), IDC_DDSTYPE);
	
    m_ToolTip.AddTool(GetDlgItem(IDC_DSPCNT), IDC_DSPCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_DSPNUM), IDC_DSPNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDRATE), IDC_PLDRATE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDVOLUME), IDC_PLDVOLUME);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDPINS), IDC_PLDPINS);
	
	m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	m_ctrlDspPldType.SetCurSel(m_DspPldType);
	m_ctrlDspPldRate.SetCurSel(m_DspPldRate);
	SetPldName();

	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);
	CWnd* pSwitchType = (CWnd*)GetDlgItem(IDC_SWITCHTYPE);
	pSwitchType->EnableWindow(m_isSwitch);
	CWnd* pSwitchAdr = (CWnd*)GetDlgItem(IDC_SWITCHADR);
	pSwitchAdr->EnableWindow(m_isSwitch);

	m_ctrlGen0Type.SetCurSel(m_Gen0Type);
	//CWnd* pGenRefLabel = (CWnd*)GetDlgItem(IDC_GEN0LB);
	//if(m_Gen0Type)
	//	pGenRefLabel->SetWindowText("Predefined:");
	//else
	//	pGenRefLabel->SetWindowText("Frequency:");
	CWnd* pGenRefMax = (CWnd*)GetDlgItem(IDC_GENREFMAX);
	CWnd* pGenAdr = (CWnd*)GetDlgItem(IDC_GENADR);
	pGenRefMax->EnableWindow(m_Gen0Type);
	pGenAdr->EnableWindow(m_Gen0Type);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIcrFmc105pDlg::SetPldName() 
{
	int nIndex = m_ctrlDspPldType.GetCurSel();
	CString strPldType;
	m_ctrlDspPldType.GetLBText(nIndex, strPldType);
	m_DspPldType = nIndex;

	CString strPldPins;
	strPldPins.Format(_T("%d"), m_DspPldPins);

	nIndex = m_ctrlDspPldRate.GetCurSel();
	CString strPldRate;
	m_ctrlDspPldRate.GetLBText(nIndex, strPldRate);
	m_DspPldRate = nIndex;

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

void CIcrFmc105pDlg::OnEnKillfocusPldpins()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrFmc105pDlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrFmc105pDlg::OnEnKillfocusPldvolume()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrFmc105pDlg::OnCbnSelchangePldrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrFmc105pDlg::OnBnClickedDdsbe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pDdsType = (CWnd*)GetDlgItem(IDC_DDSTYPE);
	pDdsType->EnableWindow(m_isDds);
}

void CIcrFmc105pDlg::OnCbnSelchangeGentype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	int nIndex = m_ctrlGen0Type.GetCurSel();
	m_Gen0Type = nIndex;
	//CWnd* pGenRefLabel = (CWnd*)GetDlgItem(IDC_GEN0LB);
	//if(nIndex)
	//	pGenRefLabel->SetWindowText("Predefined:");
	//else
	//	pGenRefLabel->SetWindowText("Frequency:");
	CWnd* pGenRefMax = (CWnd*)GetDlgItem(IDC_GENREFMAX);
	CWnd* pGenAdr = (CWnd*)GetDlgItem(IDC_GENADR);
	pGenRefMax->EnableWindow(nIndex);
	pGenAdr->EnableWindow(nIndex);
}

void CIcrFmc105pDlg::OnBnClickedSwitchbe()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CWnd* pSwitchType = (CWnd*)GetDlgItem(IDC_SWITCHTYPE);
	pSwitchType->EnableWindow(m_isSwitch);
	CWnd* pSwitchAdr = (CWnd*)GetDlgItem(IDC_SWITCHADR);
	pSwitchAdr->EnableWindow(m_isSwitch);
}

void CIcrFmc105pDlg::OnDeltaposSpindspcnt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	spinPos	= pNMUpDown->iPos;
	int	spinDelta = pNMUpDown->iDelta;
	if( (spinPos <= 0 && spinDelta == -1) || (spinPos >=MAX_DSPCNT && spinDelta == 1) )
		spinDelta = 0;
	int	spinPosAfterSpinClick = spinPos + spinDelta;
	// если после уменьшения количества DSP номер DSP превышает количество, уменьшаем номер
	if( (m_DspNodeNum >= (UINT)spinPosAfterSpinClick) && (m_DspNodeNum > 0) )
	{
		m_DspNodeNum = spinPosAfterSpinClick - 1;
		UpdateData(FALSE);
	}

	int cboxStyle = m_ctrlDspPldType.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	// если изменённое количество DSP больше нуля
	if( spinPosAfterSpinClick>0 )
	{
		// если окна DSP выключены, они включаются
		if( pldWindowsDisabled )
			LockUnlockDspWindows(UNLOCK);
		m_ctrlSpinDspNodeNum.SetRange(0, spinPosAfterSpinClick - 1);
	}
	// если изменённое количество DSP равно нулю и окна DSP включены, они выключаются
	else if( !pldWindowsDisabled )
		LockUnlockDspWindows(LOCK);
	*pResult = 0;
}

void CIcrFmc105pDlg::OnEnKillfocusDspcnt()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int cboxStyle = m_ctrlDspPldType.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	if( m_DspNodeCnt > MAX_DSPCNT )
		m_DspNodeCnt = MAX_DSPCNT;
	// если окна DSP выключены, а количество DSP становится не нулём, окна DSP включаются
	if( pldWindowsDisabled && m_DspNodeCnt>0 )
		LockUnlockDspWindows(UNLOCK);
	// если окна DSP включены, а количество DSP становится равным нулю, окна DSP выключаются
	else if( !pldWindowsDisabled && m_DspNodeCnt==0 )
		LockUnlockDspWindows(LOCK);
	if( (m_DspNodeNum >= m_DspNodeCnt) && (m_DspNodeCnt!=0) )
		m_DspNodeNum = m_DspNodeCnt - 1;
	else if( m_DspNodeCnt==0 )
		m_DspNodeNum = 0;
	m_ctrlSpinDspNodeNum.SetRange(0, m_DspNodeCnt - 1);
	UpdateData(FALSE);
}

void CIcrFmc105pDlg::OnEnKillfocusDspnum()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// если вручную введённый номер DSP больше количества DSP, устанавливается максимально возможный номер
	if( m_DspNodeNum > m_DspNodeCnt - 1 && (m_DspNodeNum > 0) )
		m_DspNodeNum = m_DspNodeCnt - 1;
	UpdateData(FALSE);
}

void CIcrFmc105pDlg::LockUnlockDspWindows(USHORT wLock)
{
	CWnd* pDspNum = (CWnd*)GetDlgItem(IDC_DSPNUM);
	CWnd* pPldVolume = (CWnd*)GetDlgItem(IDC_PLDVOLUME);
	CWnd* pPldPins = (CWnd*)GetDlgItem(IDC_PLDPINS);
	if( wLock == LOCK )
	{
		pDspNum->EnableWindow(FALSE);
		m_ctrlSpinDspNodeNum.EnableWindow(FALSE);
		m_ctrlDspPldType.EnableWindow(FALSE);
		m_ctrlDspPldRate.EnableWindow(FALSE);
		pPldVolume->EnableWindow(FALSE);
		pPldPins->EnableWindow(FALSE);
	}
	else if ( wLock == UNLOCK )
	{
		pDspNum->EnableWindow(TRUE);
		m_ctrlSpinDspNodeNum.EnableWindow(TRUE);
		m_ctrlDspPldType.EnableWindow(TRUE);
		m_ctrlDspPldRate.EnableWindow(TRUE);
		pPldVolume->EnableWindow(TRUE);
		pPldPins->EnableWindow(TRUE);
	}
}

