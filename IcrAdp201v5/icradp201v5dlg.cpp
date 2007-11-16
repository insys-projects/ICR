// IcrAdp201v5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrAdp201v5App.h"
#include "IcrAdp201v5Dlg.h"
#include ".\icradp201v5dlg.h"

// CIcrAdp201v5Dlg dialog

IMPLEMENT_DYNAMIC(CIcrAdp201v5Dlg, CDialog)
CIcrAdp201v5Dlg::CIcrAdp201v5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIcrAdp201v5Dlg::IDD, pParent)
{
	m_BusClock = 100.0;
	m_HostPldCnt = 0;
	m_strPldName = _T("");
	m_PldVolume = 0;
	m_PldNum = 0;
	m_PldPins = 0;
//	m_strSDRCON = _T("");

	m_strSdramRAS = _T("13");
	m_strSdramCAS = _T("9");
	m_strSdramBANK = _T("1");
	m_strSdramCL = _T("6");

	m_sdramRAS = 13;
	m_sdramCAS =  9;
	m_sdramBANK=  1;
	m_sdramCL  =  6;

	m_AdmMask = 0;
	m_Industrial = 0;
}

CIcrAdp201v5Dlg::~CIcrAdp201v5Dlg()
{
}

void CIcrAdp201v5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SDRAMSIZE, m_ctrlSdramSize);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlPldType);
	DDX_Control(pDX, IDC_PLDRATE, m_ctrlPldRate);
	DDX_Control(pDX, IDC_MAXCPUCLOCK, m_ctrlMaxCpuClock);
	DDX_Text(pDX, IDC_BUSCLOCK, m_BusClock);
	DDX_Text(pDX, IDC_PLDNAME, m_strPldName);
	DDX_Text(pDX, IDC_PLDVOLUME, m_PldVolume);
	DDX_Text(pDX, IDC_PLDNUM, m_PldNum);
	DDX_Text(pDX, IDC_PLDPINS, m_PldPins);
//	DDX_Text(pDX, IDC_SDRCON, m_strSDRCON);
	DDX_Text(pDX, IDC_sdramRAS, m_strSdramRAS);
	DDX_Text(pDX, IDC_sdramCAS, m_strSdramCAS);
	DDX_Text(pDX, IDC_sdramBANK, m_strSdramBANK);
	DDX_Text(pDX, IDC_sdramCL, m_strSdramCL);
}


BEGIN_MESSAGE_MAP(CIcrAdp201v5Dlg, CDialog)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_PLDRATE, OnCbnSelchangePldrate)
	ON_CBN_SELCHANGE(IDC_PLDTYPE, OnCbnSelchangePldtype)
	ON_EN_KILLFOCUS(IDC_PLDPINS, OnEnKillfocusPldpins)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, OnEnKillfocusPldvolume)
	ON_BN_CLICKED(IDC_P1, OnBnClickedP1)
END_MESSAGE_MAP()


// CIcrAdp201v5Dlg message handlers

BOOL CIcrAdp201v5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_MAXCPUCLOCK), IDC_MAXCPUCLOCK);
    m_ToolTip.AddTool(GetDlgItem(IDC_BUSCLOCK), IDC_BUSCLOCK);
    m_ToolTip.AddTool(GetDlgItem(IDC_SDRAMSIZE), IDC_SDRAMSIZE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDNUM), IDC_PLDNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDRATE), IDC_PLDRATE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDVOLUME), IDC_PLDVOLUME);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDPINS), IDC_PLDPINS);
    m_ToolTip.AddTool(GetDlgItem(IDOK), IDOK);
    m_ToolTip.AddTool(GetDlgItem(IDCANCEL), IDCANCEL);

	if(m_MaxCpuClock < (500 + (600 - 500) / 2))
		m_ctrlMaxCpuClock.SetCurSel(0);
	else
		m_ctrlMaxCpuClock.SetCurSel(1);

	if(m_SdramSize <= 64 * 1024 * 1024 / 2)
		m_ctrlSdramSize.SetCurSel(0);
	else
		if(m_SdramSize <= 128 * 1024 * 1024 / 2)
			m_ctrlSdramSize.SetCurSel(1);
		else
			if(m_SdramSize <= 256 * 1024 * 1024 / 2)
				m_ctrlSdramSize.SetCurSel(2);
			else
				m_ctrlSdramSize.SetCurSel(3);

	TCHAR buf[40];

//	sprintf(buf, _T("%X"), m_SDRCON);
//	m_strSDRCON = buf;

	sprintf(buf, _T("%d"), m_sdramRAS);
	m_strSdramRAS = buf;

	sprintf(buf, _T("%d"), m_sdramCAS);
	m_strSdramCAS = buf;

	sprintf(buf, _T("%d"), m_sdramBANK);
	m_strSdramBANK = buf;

	sprintf(buf, _T("%d"), m_sdramCL);
	m_strSdramCL = buf;

	m_ctrlPldType.SetCurSel(m_PldType);
	m_ctrlPldRate.SetCurSel(m_PldRate);
	SetPldName();

	SetMaskOnCheckBoxes(m_CpuMask, IDC_P1);
	SetMaskOnCheckBoxes(m_SdramMask, IDC_M1);
	SetMaskOnCheckBoxesP(m_PMask, IDC_CONNECTP2); 
	SetMaskOnCheckBoxesA(m_AdmMask, IDC_A2); 

	CButton* pProc = (CButton*)GetDlgItem(IDC_INDUSTRIAL);
	pProc->SetCheck(m_Industrial);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIcrAdp201v5Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CIcrAdp201v5Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if(m_ctrlMaxCpuClock.GetCurSel())
		m_MaxCpuClock = 600;
	else
		m_MaxCpuClock = 500;
	switch(m_ctrlSdramSize.GetCurSel())
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
	case 3:
		m_SdramSize = 256 * 1024 * 1024;
		break;
	}
	
	LPTSTR stopstring;
//	m_SDRCON = (USHORT)strtol(m_strSDRCON.GetBuffer(10), &stopstring, 16 );
	m_sdramRAS = (USHORT)strtol(m_strSdramRAS.GetBuffer(10), &stopstring, 10 );
	m_sdramCAS = (USHORT)strtol(m_strSdramCAS.GetBuffer(10), &stopstring, 10 );
	m_sdramBANK = (USHORT)strtol(m_strSdramBANK.GetBuffer(10), &stopstring, 10 );
	m_sdramCL = (USHORT)strtol(m_strSdramCL.GetBuffer(10), &stopstring, 10 );

	m_PldType = m_ctrlPldType.GetCurSel();
	m_PldRate = m_ctrlPldRate.GetCurSel();

	GetMaskOnCheckBoxes(m_CpuMask, IDC_P1);
	GetMaskOnCheckBoxes(m_SdramMask, IDC_M1);
	GetMaskOnCheckBoxesP(m_PMask, IDC_CONNECTP2);
	GetMaskOnCheckBoxesA(m_AdmMask, IDC_A2);

	CButton* pProc = (CButton*)GetDlgItem(IDC_INDUSTRIAL);
	m_Industrial = pProc->GetCheck();

}

void CIcrAdp201v5Dlg::OnCbnSelchangePldrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAdp201v5Dlg::OnCbnSelchangePldtype()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

//void CIcrAdp201v5Dlg::OnEnKillfocusPldnum()
//{
//	// TODO: Add your control notification handler code here
//}

void CIcrAdp201v5Dlg::OnEnKillfocusPldpins()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}

void CIcrAdp201v5Dlg::OnEnKillfocusPldvolume()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
}


void CIcrAdp201v5Dlg::SetMaskOnCheckBoxes(UINT mask, int idx)
{
	for(int i = 0; i < 5; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		int stat = (mask >> i) & 0x1;
		pProc->SetCheck(stat);
	}
}

void CIcrAdp201v5Dlg::SetMaskOnCheckBoxesP(UINT mask, int idx)
{
	for(int i = 0; i < 1; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		int stat = (mask >> i) & 0x1;
		pProc->SetCheck(stat);
	}
}

void CIcrAdp201v5Dlg::SetMaskOnCheckBoxesA(UINT mask, int idx)
{
	for(int i = 0; i < 2; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		int stat = (mask >> i) & 0x1;
		pProc->SetCheck(stat);
	}
}

void CIcrAdp201v5Dlg::GetMaskOnCheckBoxes(UINT& mask, int idx)
{
	mask = 0;
	for(int i = 0; i < 5; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		UINT stat = pProc->GetCheck();
		mask |= (stat << i);
	}
}

void CIcrAdp201v5Dlg::GetMaskOnCheckBoxesP(UINT& mask, int idx)
{
	mask = 0;
	for(int i = 0; i < 1; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		UINT stat = pProc->GetCheck();
		mask |= (stat << i);
	}
}

void CIcrAdp201v5Dlg::GetMaskOnCheckBoxesA(UINT& mask, int idx)
{
	mask = 0;
	for(int i = 0; i < 2; i++)
	{
		CButton* pProc = (CButton*)GetDlgItem(idx++);
		UINT stat = pProc->GetCheck();
		mask |= (stat << i);
	}
}

void CIcrAdp201v5Dlg::SetPldName() 
{
	int nIndex = m_ctrlPldType.GetCurSel();
	CString strPldType;
	m_ctrlPldType.GetLBText(nIndex, strPldType);

	CString strPldPins;
	strPldPins.Format(_T("%d"), m_PldPins);

	nIndex = m_ctrlPldRate.GetCurSel();
	CString strPldRate;
	m_ctrlPldRate.GetLBText(nIndex, strPldRate);

	CString strPldVolume;
	strPldVolume.Format(_T("%d"), m_PldVolume);

	CString strPldTypeVolume;

	if(strPldType.Find("...") != -1)
		strPldTypeVolume = strPldType.SpanExcluding("...") + strPldVolume + strPldType.Right(1);
	else
		strPldTypeVolume = strPldType + strPldVolume;

	if(strPldType.GetAt(0) == 'E')
		m_strPldName = strPldTypeVolume + ".." + strPldPins + "-" + strPldRate;
	if(strPldType.GetAt(0) == 'X')
		m_strPldName = strPldTypeVolume + "-" + strPldRate + ".." + strPldPins;

	UpdateData(FALSE); // from variable to window
}


void CIcrAdp201v5Dlg::OnBnClickedP1()
{
	// TODO: Add your control notification handler code here
}

void CIcrAdp201v5Dlg::OnBnClickedM8()
{
	// TODO: Add your control notification handler code here
}
