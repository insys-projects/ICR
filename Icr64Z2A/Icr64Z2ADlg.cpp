// Icr64Z2ADlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr64Z2AApp.h"
#include "Icr64Z2ADlg.h"


// Icr64Z2ADlg dialog

IMPLEMENT_DYNAMIC(Icr64Z2ADlg, CDialog)

Icr64Z2ADlg::Icr64Z2ADlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr64Z2ADlg::IDD, pParent)
	, m_PldNum(0)
{
	m_strPldName = _T("");
	m_PldPins = 0;
	m_PldVolume = 0;
	m_HostPldCnt = 0;
}

Icr64Z2ADlg::~Icr64Z2ADlg()
{
}

void Icr64Z2ADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Control(pDX, IDC_SDRAMSIZEA, m_ctrlSdramASize);
	DDX_Control(pDX, IDC_SDRAMSIZEB, m_ctrlSdramBSize);
	DDX_Control(pDX, IDC_FLASH, m_ctrlFlashSize);
	DDX_Control(pDX, IDC_SBSRAM, m_ctrlSbsramSize);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlPldType);
	DDX_Control(pDX, IDC_SPINPLDCNT, m_ctrlHostPldCnt);
	DDX_Control(pDX, IDC_SPINPLDNUM, m_ctrlPldNum);
	DDX_Text(pDX, IDC_PLDNAME, m_strPldName);
	DDX_Text(pDX, IDC_HOSTPLDCNT, m_HostPldCnt);
	DDX_Text(pDX, IDC_PLDNUM, m_PldNum);
	DDX_Text(pDX, IDC_PLDVOLUME, m_PldVolume);
}


BEGIN_MESSAGE_MAP(Icr64Z2ADlg, CDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_PLDTYPE, &Icr64Z2ADlg::OnCbnSelchangePldtype)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, &Icr64Z2ADlg::OnEnKillfocusPldvolume)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINPLDCNT, &Icr64Z2ADlg::OnDeltaposSpinpldcnt)
//	ON_EN_CHANGE(IDC_HOSTPLDCNT, &Icr64Z2ADlg::OnEnChangeHostpldcnt)
ON_EN_KILLFOCUS(IDC_HOSTPLDCNT, &Icr64Z2ADlg::OnEnKillfocusHostpldcnt)
ON_EN_KILLFOCUS(IDC_PLDNUM, &Icr64Z2ADlg::OnEnKillfocusPldnum)
END_MESSAGE_MAP()


// Icr64Z2ADlg message handlers

BOOL Icr64Z2ADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlHostPldCnt.SetRange(0, MAX_HOSTPLDCNT);
	m_ctrlPldNum.SetRange(0, m_HostPldCnt - 1);

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZEA), IDC_SDRAMSIZEA);
	m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZEB), IDC_SDRAMSIZEB);
	m_ToolTip.AddTool(GetDlgItem(IDC_FLASH), IDC_FLASH);
	m_ToolTip.AddTool(GetDlgItem(IDC_SBSRAM), IDC_SBSRAM);
    m_ToolTip.AddTool(GetDlgItem(IDC_HOSTPLDCNT), IDC_HOSTPLDCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDNUM), IDC_PLDNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDVOLUME), IDC_PLDVOLUME);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	if(m_MaxCpuClock < (720 + (1400 - 720) / 2))
		m_ctrlMaxCpuClock.SetCurSel(0);
	else
		m_ctrlMaxCpuClock.SetCurSel(1);

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

	if(m_SdramBSize <= 32 * 1024 * 1024 / 2)
		m_ctrlSdramBSize.SetCurSel(0);
	else
		m_ctrlSdramBSize.SetCurSel(1);

	if(m_FlashSize <= 4 * 1024 * 1024 / 2)
		m_ctrlFlashSize.SetCurSel(0);
	else
		m_ctrlFlashSize.SetCurSel(1);

	if(m_SbsramSize <= 4 * 1024 * 1024 / 2)
		m_ctrlSbsramSize.SetCurSel(0);
	else
		if(m_SbsramSize <= 8 * 1024 * 1024 / 2)
			m_ctrlSbsramSize.SetCurSel(1);
		else
			if(m_SbsramSize <= 16 * 1024 * 1024 / 2)
				m_ctrlSbsramSize.SetCurSel(2);
			else
				m_ctrlSbsramSize.SetCurSel(3);

	m_ctrlPldType.SetCurSel(m_PldType);
	SetPldName();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void Icr64Z2ADlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if(m_ctrlMaxCpuClock.GetCurSel())
		m_MaxCpuClock = 1400;
	else
		m_MaxCpuClock = 720;
	switch(m_ctrlSdramASize.GetCurSel())
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
	if(m_ctrlFlashSize.GetCurSel())
		m_FlashSize = 4 * 1024 * 1024;
	else
		m_FlashSize = 0;
	switch(m_ctrlSbsramSize.GetCurSel())
	{
	case 0:
		m_SbsramSize = 0;
		break;
	case 1:
		m_SbsramSize = 4 * 1024 * 1024;
		break;
	case 2:
		m_SbsramSize = 8 * 1024 * 1024;
		break;
	case 3:
		m_SbsramSize = 16 * 1024 * 1024;
		break;
	}
	m_PldType = m_ctrlPldType.GetCurSel();
}

void Icr64Z2ADlg::SetPldName() 
{
	int nIndex = m_ctrlPldType.GetCurSel();
	CString strPldType;
	m_ctrlPldType.GetLBText(nIndex, strPldType);

	CString strPldVolume;
	strPldVolume.Format(_T("%d"), m_PldVolume);

	CString strPldTypeVolume;

	if(strPldType.Find("...") != -1)
		strPldTypeVolume = strPldType.SpanExcluding("...") + strPldVolume + strPldType.Right(1);
	else
		strPldTypeVolume = strPldType + strPldVolume;

	if(strPldType.GetAt(0) == 'E')
		m_strPldName = strPldTypeVolume + "..456-4";
	if(strPldType.GetAt(0) == 'X')
		m_strPldName = strPldTypeVolume + "-4..456";

	UpdateData(FALSE); // from variable to window
}

BOOL Icr64Z2ADlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr64Z2ADlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void Icr64Z2ADlg::OnEnKillfocusPldvolume()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}


void Icr64Z2ADlg::OnDeltaposSpinpldcnt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	spinPos	= pNMUpDown->iPos;
	int	spinDelta = pNMUpDown->iDelta;
	if( (spinPos <= 0 && spinDelta == -1) || (spinPos >=4 && spinDelta == 1) )
		spinDelta = 0;
	int	spinPosAfterSpinClick = spinPos + spinDelta;
	if( (m_PldNum >= (UINT)spinPosAfterSpinClick) && (m_PldNum > 0) )
	{
		m_PldNum = spinPosAfterSpinClick - 1;
		UpdateData(FALSE);
	}

	int cboxStyle = m_ctrlPldType.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;

	if( spinPosAfterSpinClick>0 )
	{
		if( pldWindowsDisabled )
		{
			m_ctrlPldNum.EnableWindow(TRUE);
			m_ctrlPldType.EnableWindow(TRUE);
			CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
			pPldNum->EnableWindow(TRUE);
			CWnd* pPldVolume = (CWnd*)GetDlgItem(IDC_PLDVOLUME);
			pPldVolume->EnableWindow(TRUE);		
		}
		m_ctrlPldNum.SetRange(0, spinPosAfterSpinClick - 1);
	}
	else if( !pldWindowsDisabled )
	{
		m_ctrlPldNum.EnableWindow(FALSE);
		m_ctrlPldType.EnableWindow(FALSE);
		CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
		pPldNum->EnableWindow(FALSE);
		CWnd* pPldVolume = (CWnd*)GetDlgItem(IDC_PLDVOLUME);
		pPldVolume->EnableWindow(FALSE);
	}
	*pResult = 0;
}

void Icr64Z2ADlg::OnEnKillfocusHostpldcnt()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int cboxStyle = m_ctrlPldType.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	if( m_HostPldCnt > 4 )
		m_HostPldCnt = 4;
	if( pldWindowsDisabled && m_HostPldCnt>0 )
	{
		m_ctrlPldNum.EnableWindow(TRUE);
		m_ctrlPldType.EnableWindow(TRUE);
		CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
		pPldNum->EnableWindow(TRUE);
		CWnd* pPldVolume = (CWnd*)GetDlgItem(IDC_PLDVOLUME);
		pPldVolume->EnableWindow(TRUE);
	}
	if( !pldWindowsDisabled && m_HostPldCnt==0 )
	{
		m_ctrlPldNum.EnableWindow(FALSE);
		m_ctrlPldType.EnableWindow(FALSE);
		CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
		pPldNum->EnableWindow(FALSE);
		CWnd* pPldVolume = (CWnd*)GetDlgItem(IDC_PLDVOLUME);
		pPldVolume->EnableWindow(FALSE);
	}
	if( (m_PldNum >= m_HostPldCnt) && (m_HostPldCnt!=0) )
		m_PldNum = m_HostPldCnt - 1;
	else if( m_HostPldCnt==0 )
		m_PldNum = 0;
	m_ctrlPldNum.SetRange(0, m_HostPldCnt - 1);
	UpdateData(FALSE);
}

void Icr64Z2ADlg::OnEnKillfocusPldnum()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if( m_PldNum > m_HostPldCnt - 1 && (m_PldNum > 0) )
		m_PldNum = m_HostPldCnt - 1;
	UpdateData(FALSE);
}
