// Icr6713Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr6713App.h"
#include "Icr6713Dlg.h"


// Icr6713Dlg dialog

IMPLEMENT_DYNAMIC(Icr6713Dlg, CDialog)

Icr6713Dlg::Icr6713Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr6713Dlg::IDD, pParent)
	, m_HostPldCnt(0)
	, m_PldNum(0)
{

}

Icr6713Dlg::~Icr6713Dlg()
{
}

void Icr6713Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SDRAMSIZE, m_ctrlSdramSize);
	DDX_Control(pDX, IDC_FLASH, m_ctrlFlashSize);
	DDX_Control(pDX, IDC_SPINPLDCNT, m_ctrlHostPldCnt);
	DDX_Control(pDX, IDC_SPINPLDNUM, m_ctrlPldNum);
	DDX_Control(pDX, IDC_PDLSRAM, m_ctrlPldSramSize);
	DDX_Text(pDX, IDC_HOSTPLDCNT, m_HostPldCnt);
	DDX_Text(pDX, IDC_PLDNUM, m_PldNum);
}


BEGIN_MESSAGE_MAP(Icr6713Dlg, CDialog)
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_HOSTPLDCNT, &Icr6713Dlg::OnEnKillfocusHostpldcnt)
	ON_EN_KILLFOCUS(IDC_PLDNUM, &Icr6713Dlg::OnEnKillfocusPldnum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINPLDCNT, &Icr6713Dlg::OnDeltaposSpinpldcnt)
END_MESSAGE_MAP()


// Icr6713Dlg message handlers

BOOL Icr6713Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlHostPldCnt.SetRange(0, MAX_HOSTPLDCNT);
	m_ctrlPldNum.SetRange(0, m_HostPldCnt - 1);

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZE), IDC_SDRAMSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_FLASH), IDC_FLASH);
    m_ToolTip.AddTool(GetDlgItem(IDC_HOSTPLDCNT), IDC_HOSTPLDCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDNUM), IDC_PLDNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDSRAM), IDC_PLDSRAM);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	if(m_SdramSize <= 64 * 1024 * 1024 / 2)
		m_ctrlSdramSize.SetCurSel(0);
	else
		if(m_SdramSize <= 128 * 1024 * 1024 / 2)
			m_ctrlSdramSize.SetCurSel(1);
		else
			m_ctrlSdramSize.SetCurSel(2);

	if(m_FlashSize <= 4 * 1024 * 1024 / 2)
		m_ctrlFlashSize.SetCurSel(0);
	else
		m_ctrlFlashSize.SetCurSel(1);

	if(m_PldSramSize <= 512 * 1024 / 2)
		m_ctrlPldSramSize.SetCurSel(0);
	else
		m_ctrlPldSramSize.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr6713Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr6713Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	switch( m_ctrlSdramSize.GetCurSel() )
	{
	case 0:
		m_SdramSize = 0;
		break;
	case 1:
		m_SdramSize = 64 * 1024 * 1024;
		break;
	case 2:
		m_SdramSize = 128 * 1024 * 1024;
		break;
	}
	if( m_ctrlFlashSize.GetCurSel() )
		m_FlashSize = 4 * 1024 * 1024;
	else
		m_FlashSize = 0;
	if( m_ctrlPldSramSize.GetCurSel() )
		m_PldSramSize = 512 * 1024;
	else
		m_PldSramSize = 0;
}

// установка количества ПЛИС с помощью стрелочек
void Icr6713Dlg::OnDeltaposSpinpldcnt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	spinPos	= pNMUpDown->iPos;
	int	spinDelta = pNMUpDown->iDelta;
	if( (spinPos <= 0 && spinDelta == -1) || (spinPos >=4 && spinDelta == 1) )
		spinDelta = 0;
	int	spinPosAfterSpinClick = spinPos + spinDelta;
	// если после уменьшения количества ПЛИС номер ПЛИС превышает количество, уменьшаем номер
	if( (m_PldNum >= (UINT)spinPosAfterSpinClick) && (m_PldNum > 0) )
	{
		m_PldNum = spinPosAfterSpinClick - 1;
		UpdateData(FALSE);
	}
	int cboxStyle = m_ctrlPldSramSize.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	// если изменённое количество ПЛИС больше нуля
	if( spinPosAfterSpinClick>0 )
	{
		// если окна ПЛИС выключены, они включаются
		if( pldWindowsDisabled )
		{
			m_ctrlPldNum.EnableWindow(TRUE);
			m_ctrlPldSramSize.EnableWindow(TRUE);
			CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
			pPldNum->EnableWindow(TRUE);
		}
		m_ctrlPldNum.SetRange(0, spinPosAfterSpinClick - 1);
	}
	// если изменённое количество ПЛИС равно нулю и окна ПЛИС включены, они выключаются
	else if( !pldWindowsDisabled )
	{
		m_ctrlPldNum.EnableWindow(FALSE);
		m_ctrlPldSramSize.EnableWindow(FALSE);
		CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
		pPldNum->EnableWindow(FALSE);
	}
	*pResult = 0;
}

// ручная установка количества ПЛИС
void Icr6713Dlg::OnEnKillfocusHostpldcnt()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int cboxStyle = m_ctrlPldSramSize.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	if( m_HostPldCnt > 4 )
		m_HostPldCnt = 4;
	// если окна ПЛИС выключены, а количество ПЛИС становится не нулём, окна ПЛИС включаются
	if( pldWindowsDisabled && m_HostPldCnt>0 )
	{
		m_ctrlPldNum.EnableWindow(TRUE);
		m_ctrlPldSramSize.EnableWindow(TRUE);
		CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
		pPldNum->EnableWindow(TRUE);
	}
	// если окна ПЛИС включены, а количество ПЛИС становится равным нулю, окна ПЛИС выключаются
	else if( !pldWindowsDisabled && m_HostPldCnt==0 )
	{
		m_ctrlPldNum.EnableWindow(FALSE);
		m_ctrlPldSramSize.EnableWindow(FALSE);
		CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
		pPldNum->EnableWindow(FALSE);
	}
	if( (m_PldNum >= m_HostPldCnt) && (m_HostPldCnt!=0) )
		m_PldNum = m_HostPldCnt - 1;
	else if( m_HostPldCnt==0 )
		m_PldNum = 0;
	m_ctrlPldNum.SetRange(0, m_HostPldCnt - 1);
	UpdateData(FALSE);
}

// ручная установка номера ПЛИС
void Icr6713Dlg::OnEnKillfocusPldnum()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// если вручную введённый номер ПЛИС больше количества ПЛИС, устанавливается максимально возможный номер
	if( m_PldNum > m_HostPldCnt - 1 && (m_PldNum > 0) )
		m_PldNum = m_HostPldCnt - 1;
	UpdateData(FALSE);
}

