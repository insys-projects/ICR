// PldPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "PldPage.h"
#include "IdCfgRomDlg.h"
#include ".\pldpage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPldPage property page

IMPLEMENT_DYNAMIC(CPldPage, CPropertyPage)

CPldPage::CPldPage() : CPropertyPage(CPldPage::IDD)
{
	//{{AFX_DATA_INIT(CPldPage)
	m_strPldName = _T("");
	m_PldNum = 0;
	m_PldPins = 256;
	m_PldVolume = 10;
	//}}AFX_DATA_INIT
	m_AdmIfNum = 0;
}

void CPldPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPldPage)
	DDX_Control(pDX, IDC_SPINPLDNUM, m_ctrlSpinPldNum);
	DDX_Control(pDX, IDC_PLDTYPE, m_ctrlPldType);
	DDX_Control(pDX, IDC_PLDRATE, m_ctrlPldRate);
	DDX_Text(pDX, IDC_PLDNAME, m_strPldName);
	DDX_Text(pDX, IDC_PLDNUM, m_PldNum);
	DDX_Text(pDX, IDC_PLDPINS, m_PldPins);
	DDX_Text(pDX, IDC_PLDVOLUME, m_PldVolume);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_PldNum, 0, m_PldMax);
}


BEGIN_MESSAGE_MAP(CPldPage, CPropertyPage)
//	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	//{{AFX_MSG_MAP(CPldPage)
	ON_CBN_SELCHANGE(IDC_PLDRATE, OnSelchangePldrate)
	ON_CBN_SELCHANGE(IDC_PLDTYPE, OnSelchangePldtype)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINPLDNUM, OnDeltaposSpinpldnum)
	ON_EN_KILLFOCUS(IDC_PLDNUM, OnKillfocusPldnum)
	ON_EN_KILLFOCUS(IDC_PLDPINS, OnKillfocusPldpins)
	ON_EN_KILLFOCUS(IDC_PLDVOLUME, OnKillfocusPldvolume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPldPage message handlers

BOOL CPldPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	SetMaxPld(pParentWnd->m_pAdmIfPage->m_NumOfPld - 1);

	for(int i = 0; i < MAX_ADMIFCFG; i++)
	{
		for(int j = 0; j < MAX_PLDCFG; j++)
		{
			m_PldCfg[i][j].bNumber = j;
			m_PldCfg[i][j].bAdmNum = i;
			m_PldCfg[i][j].bType = 0;
			m_PldCfg[i][j].wVolume = m_PldVolume;
			m_PldCfg[i][j].wPins = m_PldPins;
			m_PldCfg[i][j].bSpeedGrade = 0;
		}
	}

	m_ctrlPldType.SetCurSel(0);
	m_ctrlPldRate.SetCurSel(0);
	SetPldName();

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDRATE), IDC_PLDRATE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDTYPE), IDC_PLDTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDNUM), IDC_PLDNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDPINS), IDC_PLDPINS);
    m_ToolTip.AddTool(GetDlgItem(IDC_PLDVOLUME), IDC_PLDVOLUME);
//    EnableToolTips(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
/////////////////////////////////////////////////////////////////////////////
BOOL CPldPage::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT_PTR nID = pNMHDR->idFrom;
    if(pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
//        if(nID != IDC_START && nID != IDC_HL_WWW && nID != IDC_HL_Email)
//        if(nID != IDC_TABPAGE)
        {
            pTTT->lpszText = MAKEINTRESOURCE(nID);
//            strcpy(pTTT->szText, "1234567890");
            pTTT->hinst = AfxGetResourceHandle();
            return(TRUE);
        }
    }
    return(FALSE);
}
*/
void CPldPage::OnKillfocusPldpins() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
	m_PldCfg[m_AdmIfNum][m_PldNum].wPins = m_PldPins;
}

void CPldPage::OnKillfocusPldvolume() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetPldName();
	m_PldCfg[m_AdmIfNum][m_PldNum].wVolume = m_PldVolume;
}

void CPldPage::OnSelchangePldrate() 
{
	// TODO: Add your control notification handler code here
	SetPldName();
	m_PldCfg[m_AdmIfNum][m_PldNum].bSpeedGrade = m_ctrlPldRate.GetCurSel();
}

void CPldPage::OnSelchangePldtype() 
{
	// TODO: Add your control notification handler code here
	SetPldName();
	m_PldCfg[m_AdmIfNum][m_PldNum].bType = m_ctrlPldType.GetCurSel();
}

void CPldPage::SetPldName() 
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

void CPldPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pCurrent = GetFocus();
	CWnd* pNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
	if(pCurrent == pNum)
		ChangePldNum();
//	CPropertyPage::OnOK();
}

void CPldPage::OnKillfocusPldnum() 
{
	// TODO: Add your control notification handler code here
	ChangePldNum();
}

void CPldPage::OnDeltaposSpinpldnum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(newVal >=0 && newVal <= (int)m_PldMax)
	{
		m_PldNum = newVal;
		UpdateData(FALSE); // from variable to window
		ChangePldNum();
	}
	*pResult = 0;
}

void CPldPage::ChangePldNum() 
{
	UpdateData(TRUE); // from window to variable
	int num = m_PldNum;
	m_ctrlPldType.SetCurSel(m_PldCfg[m_AdmIfNum][num].bType);
	m_ctrlPldRate.SetCurSel(m_PldCfg[m_AdmIfNum][num].bSpeedGrade);
	m_PldPins = m_PldCfg[m_AdmIfNum][num].wPins;
	m_PldVolume = m_PldCfg[m_AdmIfNum][num].wVolume;
	SetPldName();
//	UpdateData(FALSE); // from variable to window
}

void CPldPage::SetMaxPld(int maxPld)
{
	m_PldMax = maxPld;
	BOOL enFlag = TRUE;
	if(m_PldMax >= 0) {
		m_ctrlSpinPldNum.SetRange(0, m_PldMax);
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		CWnd* pNumOfPld = (CWnd*)pParentWnd->m_pAdmIfPage->GetDlgItem(IDC_NUMOFPLD);
		enFlag = pNumOfPld->IsWindowEnabled();
	}
	else
		enFlag = FALSE;

	CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
	CWnd* pPldType = (CWnd*)GetDlgItem(IDC_PLDTYPE);
	CWnd* pPldPins = (CWnd*)GetDlgItem(IDC_PLDPINS);
	CWnd* pPldRate = (CWnd*)GetDlgItem(IDC_PLDRATE);
	CWnd* pPldSize = (CWnd*)GetDlgItem(IDC_PLDSIZE);
	pPldNum->EnableWindow(enFlag);
	pPldType->EnableWindow(enFlag);
	pPldPins->EnableWindow(enFlag);
	pPldRate->EnableWindow(enFlag);
	pPldSize->EnableWindow(enFlag);
}

// Data from PLD_CFG into dialog control
void CPldPage::SetDataIntoDlg(PICR_CfgAdmPld pPldCfg)
{
	UINT AdmNum = pPldCfg->bAdmNum;
	UINT num = pPldCfg->bNumber;
	m_PldCfg[AdmNum][num].bAdmNum = pPldCfg->bAdmNum;

	m_PldCfg[AdmNum][num].bNumber = pPldCfg->bNumber;

	m_PldCfg[AdmNum][num].bType = pPldCfg->bType;
/*
	switch(pPldCfg->Size)
	{
	case 10:
		m_PldCfg[num].Size = 0;
		break;
	case 30:
		m_PldCfg[num].Size = 1;
		break;
	case 50:
		m_PldCfg[num].Size = 2;
		break;
	case 100:
		m_PldCfg[num].Size = 3;
		break;
	case 200:
		m_PldCfg[num].Size = 4;
		break;
	case 300:
		m_PldCfg[num].Size = 5;
		break;
	case 400:
		m_PldCfg[num].Size = 6;
		break;
	case 600:
		m_PldCfg[num].Size = 7;
		break;
	}*/
	m_PldCfg[AdmNum][num].wVolume = pPldCfg->wVolume;
/*
	switch(pPldCfg->Pins)
	{
	case 256:
		m_PldCfg[num].Pins = 0;
		break;
	case 676:
		m_PldCfg[num].Pins = 1;
		break;
	}*/
	m_PldCfg[AdmNum][num].wPins = pPldCfg->wPins;

	m_PldCfg[AdmNum][num].bSpeedGrade = pPldCfg->bSpeedGrade - 1;

	if(num == m_PldNum && AdmNum == m_AdmIfNum)
	{
		m_ctrlPldType.SetCurSel(m_PldCfg[AdmNum][num].bType);
		m_ctrlPldRate.SetCurSel(m_PldCfg[AdmNum][num].bSpeedGrade);
		m_PldVolume = m_PldCfg[AdmNum][num].wVolume;
		m_PldPins = m_PldCfg[AdmNum][num].wPins;
		SetPldName();
	}
}

// Data from dialog control into PLD_CFG
void CPldPage::GetDataFromDlg(PICR_CfgAdmPld pPldCfg, UINT num, UINT AdmNum) 
{
	UpdateData(TRUE); // from window to variable

	pPldCfg->wTag = PLD_CFG_TAG;
	pPldCfg->wSize = sizeof(ICR_CfgAdmPld) - 4;
	pPldCfg->bAdmNum = AdmNum;

	pPldCfg->bNumber = m_PldCfg[AdmNum][num].bNumber;

	pPldCfg->bType = m_PldCfg[AdmNum][num].bType;

/*	TCHAR szPldSize[40];
	m_ctrlPldSize.GetLBText(m_PldCfg[num].Size, szPldSize);
	pPldCfg->Size = atoi(szPldSize);*/
	pPldCfg->wVolume = m_PldCfg[AdmNum][num].wVolume;

/*	TCHAR szPldPins[40];
	m_ctrlPldPins.GetLBText(m_PldCfg[num].Pins, szPldPins);
	pPldCfg->Pins = atoi(szPldPins);*/
	pPldCfg->wPins = m_PldCfg[AdmNum][num].wPins;

	pPldCfg->bSpeedGrade = m_PldCfg[AdmNum][num].bSpeedGrade + 1;
}

//INT_PTR CPldPage::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	return CPropertyPage::OnToolHitTest(point, pTI);
//}

BOOL CPldPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CPldPage::PageEnable(U08 isEnable)
{
	CWnd* pPldNum = (CWnd*)GetDlgItem(IDC_PLDNUM);
	CWnd* pPldType = (CWnd*)GetDlgItem(IDC_PLDTYPE);
	CWnd* pPldPins = (CWnd*)GetDlgItem(IDC_PLDPINS);
	CWnd* pPldRate = (CWnd*)GetDlgItem(IDC_PLDRATE);
	CWnd* pPldSize = (CWnd*)GetDlgItem(IDC_PLDSIZE);
	pPldNum->EnableWindow(0);
	pPldType->EnableWindow(isEnable);
	pPldPins->EnableWindow(isEnable);
	pPldRate->EnableWindow(isEnable);
	pPldSize->EnableWindow(isEnable);
}
