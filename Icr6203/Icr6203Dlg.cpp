// Icr6203Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Icr6203App.h"
#include "Icr6203Dlg.h"


// Icr6203Dlg dialog

IMPLEMENT_DYNAMIC(Icr6203Dlg, CDialog)

Icr6203Dlg::Icr6203Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Icr6203Dlg::IDD, pParent)
	, m_MaxCpuClock(0)
	, m_FifoCnt(0)
	, m_FifoNum(0)
{

}

Icr6203Dlg::~Icr6203Dlg()
{
}

void Icr6203Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SDRAMSIZE, m_ctrlSdramSize);
	DDX_Control(pDX, IDC_DPRAMSIZE, m_ctrlDpramSize);
	DDX_Control(pDX, IDC_SSRAMSIZE, m_ctrlSsramSize);
	DDX_Control(pDX, IDC_FIFOSIZE, m_ctrlFifoSize);
	DDX_Control(pDX, IDC_FIFOWIDTH, m_ctrlFifoWidth);
	DDX_Control(pDX, IDC_SPINFIFOCNT, m_ctrlFifoCnt);
	DDX_Control(pDX, IDC_SPINFIFONUM, m_ctrlFifoNum);
	DDX_Text(pDX, IDC_MAXCPUCLOCK, m_MaxCpuClock);
	DDX_Text(pDX, IDC_FIFOCNT, m_FifoCnt);
	DDX_Text(pDX, IDC_FIFONUM, m_FifoNum);
}


BEGIN_MESSAGE_MAP(Icr6203Dlg, CDialog)
	ON_WM_DESTROY()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINFIFOCNT, &Icr6203Dlg::OnDeltaposSpinfifocnt)
	ON_EN_KILLFOCUS(IDC_FIFOCNT, &Icr6203Dlg::OnEnKillfocusFifocnt)
	ON_EN_KILLFOCUS(IDC_FIFONUM, &Icr6203Dlg::OnEnKillfocusFifonum)
	
END_MESSAGE_MAP()


// Icr6203Dlg message handlers

BOOL Icr6203Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ctrlFifoCnt.SetRange(0, MAX_FIFOHOSTCNT);
	m_ctrlFifoNum.SetRange(0, m_FifoCnt - 1);

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZE), IDC_SDRAMSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_DPRAMSIZE), IDC_DPRAMSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_SSRAMSIZE), IDC_SSRAMSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_FIFOCNT), IDC_FIFOCNT);
    m_ToolTip.AddTool(GetDlgItem(IDC_FIFONUM), IDC_FIFONUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_FIFOSIZE), IDC_FIFOSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_FIFOWIDTH), IDC_FIFOWIDTH);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	if(m_SdramSize <= 16 * 1024 * 1024 / 2)
		m_ctrlSdramSize.SetCurSel(0);
	else
		if(m_SdramSize <= 32 * 1024 * 1024 / 2)
			m_ctrlSdramSize.SetCurSel(1);
		else
			m_ctrlSdramSize.SetCurSel(2);

	if(m_DpramSize <= 128 * 1024 / 2)
		m_ctrlDpramSize.SetCurSel(0);
	else
		if(m_DpramSize <= 256 * 1024 / 2)
			m_ctrlDpramSize.SetCurSel(1);
		else
			m_ctrlDpramSize.SetCurSel(2);

	if(m_SsramSize <= 2 * 1024 * 1024 / 2)
		m_ctrlSsramSize.SetCurSel(0);
	else
		if(m_SsramSize <= 4 * 1024 * 1024 / 2)
			m_ctrlSsramSize.SetCurSel(1);
		else
			if(m_SsramSize <= 6 * 1024 * 1024 / 2)
				m_ctrlSsramSize.SetCurSel(2);
			else
				if(m_SsramSize <= 4 * 1024 * 1024 / 2)
					m_ctrlSsramSize.SetCurSel(3);
				else
					m_ctrlSsramSize.SetCurSel(4);

	m_ctrlFifoSize.SetCurSel(m_FifoSize);
	m_ctrlFifoWidth.SetCurSel(m_FifoWidth);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Icr6203Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void Icr6203Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	switch(m_ctrlSdramSize.GetCurSel())
	{
	case 0:
		m_SdramSize = 0;
		break;
	case 1:
		m_SdramSize = 16 * 1024 * 1024;
		break;
	case 2:
		m_SdramSize = 32 * 1024 * 1024;
		break;
	}
	switch(m_ctrlDpramSize.GetCurSel())
	{
	case 0:
		m_DpramSize = 0;
		break;
	case 1:
		m_DpramSize = 128 * 1024;
		break;
	case 2:
		m_DpramSize = 256 * 1024;
		break;
	}
	switch(m_ctrlSsramSize.GetCurSel())
	{
	case 0:
		m_SsramSize = 0;
		break;
	case 1:
		m_SsramSize = 2 * 1024 * 1024;
		break;
	case 2:
		m_SsramSize = 4 * 1024 * 1024;
		break;
	case 3:
		m_SsramSize = 6 * 1024 * 1024;
		break;
	case 4:
		m_SsramSize = 8 * 1024 * 1024;
		break;
	}
	m_FifoSize = m_ctrlFifoSize.GetCurSel();
	m_FifoWidth = m_ctrlFifoWidth.GetCurSel();
}

void Icr6203Dlg::OnDeltaposSpinfifocnt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	spinPos	= pNMUpDown->iPos;
	int	spinDelta = pNMUpDown->iDelta;
	if( (spinPos <= 0 && spinDelta == -1) || (spinPos >=1 && spinDelta == 1) )
		spinDelta = 0;
	int	spinPosAfterSpinClick = spinPos + spinDelta;
	// если после уменьшения количества FIFO номер FIFO превышает количество, уменьшаем номер
	if( (m_FifoNum >= (UINT)spinPosAfterSpinClick) && (m_FifoNum > 0) )
	{
		m_FifoNum = spinPosAfterSpinClick - 1;
		UpdateData(FALSE);
	}

	int cboxStyle = m_ctrlFifoSize.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	// если изменённое количество FIFO больше нуля
	if( spinPosAfterSpinClick>0 )
	{
		// если окна FIFO выключены, они включаются
		if( pldWindowsDisabled )
		{
			m_ctrlFifoNum.EnableWindow(TRUE);
			m_ctrlFifoSize.EnableWindow(TRUE);
			m_ctrlFifoWidth.EnableWindow(TRUE);
			CWnd* pFifoNum = (CWnd*)GetDlgItem(IDC_FIFONUM);
			pFifoNum->EnableWindow(TRUE);
		}
		m_ctrlFifoNum.SetRange(0, spinPosAfterSpinClick - 1);
	}
	// если изменённое количество FIFO равно нулю и окна FIFO включены, они выключаются
	else if( !pldWindowsDisabled )
	{
		m_ctrlFifoNum.EnableWindow(FALSE);
		m_ctrlFifoSize.EnableWindow(FALSE);
		m_ctrlFifoWidth.EnableWindow(FALSE);
		CWnd* pFifoNum = (CWnd*)GetDlgItem(IDC_FIFONUM);
		pFifoNum->EnableWindow(FALSE);
	}
	*pResult = 0;
}

void Icr6203Dlg::OnEnKillfocusFifocnt()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int cboxStyle = m_ctrlFifoSize.GetStyle();
	int	pldWindowsDisabled = (cboxStyle &= WS_DISABLED) ? 1 : 0;
	if( m_FifoCnt > 1 )
		m_FifoCnt = 1;
	// если окна FIFO выключены, а количество FIFO становится не нулём, окна FIFO включаются
	if( pldWindowsDisabled && m_FifoCnt>0 )
	{
		m_ctrlFifoNum.EnableWindow(TRUE);
		m_ctrlFifoSize.EnableWindow(TRUE);
		m_ctrlFifoWidth.EnableWindow(TRUE);
		CWnd* pFifoNum = (CWnd*)GetDlgItem(IDC_FIFONUM);
		pFifoNum->EnableWindow(TRUE);
	}
	// если окна FIFO включены, а количество FIFO становится равным нулю, окна FIFO выключаются
	else if( !pldWindowsDisabled && m_FifoCnt==0 )
	{
		m_ctrlFifoNum.EnableWindow(FALSE);
		m_ctrlFifoSize.EnableWindow(FALSE);
		m_ctrlFifoWidth.EnableWindow(FALSE);
		CWnd* pFifoNum = (CWnd*)GetDlgItem(IDC_FIFONUM);
		pFifoNum->EnableWindow(FALSE);
	}
	if( (m_FifoNum >= m_FifoCnt) && (m_FifoCnt!=0) )
		m_FifoNum = m_FifoCnt - 1;
	else if( m_FifoCnt==0 )
		m_FifoNum = 0;
	m_ctrlFifoNum.SetRange(0, m_FifoCnt - 1);
	UpdateData(FALSE);
}

void Icr6203Dlg::OnEnKillfocusFifonum()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// если вручную введённый номер FIFO больше количества FIFO, устанавливается максимально возможный номер
	if( m_FifoNum > m_FifoCnt - 1 && (m_FifoNum > 0) )
		m_FifoNum = m_FifoCnt - 1;
	UpdateData(FALSE);
}
