// Adm2IfPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "Adm2IfPage.h"
#include "IdCfgRomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdm2IfPage property page

IMPLEMENT_DYNAMIC(CAdm2IfPage, CPropertyPage)

CAdm2IfPage::CAdm2IfPage() : CPropertyPage(CAdm2IfPage::IDD)
{
	//{{AFX_DATA_INIT(CAdm2IfPage)
	m_AdmIfNum = 0;
	m_NumOfAdcFifo = 1;
	m_NumOfDacFifo = 1;
	m_NumOfDac = 1;
	m_NumOfPld = 1;
	m_Start = TRUE;
	m_Pio = TRUE;
	m_AdmIfType = 0;
	m_PioType = 0;
	m_RefVoltPvs = 2500;
	m_Gen1 = 60.0;
	m_Gen2 = 50.0;
	//}}AFX_DATA_INIT
}

void CAdm2IfPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdm2IfPage)
	DDX_Control(pDX, IDC_SPINPLD, m_ctrlSpinPld);
	DDX_Control(pDX, IDC_SPINDAC, m_ctrlSpinDac);
	DDX_Control(pDX, IDC_SPINDACFIFO, m_ctrlSpinDacFifo);
	DDX_Control(pDX, IDC_SPINADMIFNUM, m_ctrlSpinAdmIfNum);
	DDX_Control(pDX, IDC_SPINADCFIFO, m_ctrlSpinAdcFifo);
	DDX_Text(pDX, IDC_ADMIFNUM, m_AdmIfNum);
	DDX_Text(pDX, IDC_NUMOFADCFIFO, m_NumOfAdcFifo);
	DDX_Text(pDX, IDC_NUMOFDACFIFO, m_NumOfDacFifo);
	DDX_Text(pDX, IDC_NUMOFDAC, m_NumOfDac);
	DDX_Text(pDX, IDC_NUMOFPLD, m_NumOfPld);
	DDX_Check(pDX, IDC_STARTBE, m_Start);
	DDX_Check(pDX, IDC_PIOBE, m_Pio);
	DDX_CBIndex(pDX, IDC_ADMIFTYPE, m_AdmIfType);
	DDX_CBIndex(pDX, IDC_PIOTYPE, m_PioType);
	DDX_Text(pDX, IDC_REFVOLTPVS, m_RefVoltPvs);
	DDX_Text(pDX, IDC_GEN1, m_Gen1);
	DDX_Text(pDX, IDC_GEN2, m_Gen2);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_AdmIfNum, 0, m_AdmIfMax);
	DDV_MinMaxUInt(pDX, m_NumOfPld, 0, MAX_NUMOFPLD - 1);
	DDV_MinMaxUInt(pDX, m_NumOfAdcFifo, 0, MAX_NUMOFADCFIFO - 1);
	DDV_MinMaxUInt(pDX, m_NumOfDac, 0, MAX_NUMOFDAC - 1);
	DDV_MinMaxUInt(pDX, m_NumOfDacFifo, 0, MAX_NUMOFDACFIFO - 1);
}


BEGIN_MESSAGE_MAP(CAdm2IfPage, CPropertyPage)
//	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	//{{AFX_MSG_MAP(CAdm2IfPage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINADMIFNUM, OnDeltaposSpinadmifnum)
	ON_EN_KILLFOCUS(IDC_ADMIFNUM, OnKillfocusAdmifnum)
	ON_EN_KILLFOCUS(IDC_GEN1, OnKillfocusGen1)
	ON_EN_KILLFOCUS(IDC_GEN2, OnKillfocusGen2)
	ON_EN_KILLFOCUS(IDC_NUMOFADCFIFO, OnKillfocusNumofadcfifo)
	ON_EN_KILLFOCUS(IDC_NUMOFDAC, OnKillfocusNumofdac)
	ON_EN_KILLFOCUS(IDC_NUMOFDACFIFO, OnKillfocusNumofdacfifo)
	ON_EN_KILLFOCUS(IDC_NUMOFPLD, OnKillfocusNumofpld)
	ON_EN_KILLFOCUS(IDC_REFVOLTPVS, OnKillfocusRefvoltpvs)
	ON_BN_CLICKED(IDC_PIOBE, OnPiobe)
	ON_BN_CLICKED(IDC_STARTBE, OnStartbe)
	ON_CBN_KILLFOCUS(IDC_ADMIFTYPE, OnKillfocusAdmiftype)
	ON_CBN_KILLFOCUS(IDC_PIOTYPE, OnKillfocusPiotype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdm2IfPage message handlers

BOOL CAdm2IfPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	SetMaxAdmIf(pParentWnd->m_pAmbPage->m_NumOfAdmIf - 1);

	m_ctrlSpinPld.SetRange(0, MAX_NUMOFPLD - 1);
	m_ctrlSpinAdcFifo.SetRange(0, MAX_NUMOFADCFIFO - 1);
	m_ctrlSpinDac.SetRange(0, MAX_NUMOFDAC - 1);
	m_ctrlSpinDacFifo.SetRange(0, MAX_NUMOFDACFIFO - 1);
	
	for(int i = 0; i < MAX_ADMIFCFG; i++)
	{
		m_AdmIfCfg[i].bNumber = i;
		m_AdmIfCfg[i].bType = m_AdmIfType;
		m_AdmIfCfg[i].bAdcFifoCnt = m_NumOfAdcFifo;
		m_AdmIfCfg[i].bDacCnt = m_NumOfDac;
		m_AdmIfCfg[i].bDacFifoCnt = m_NumOfDacFifo;
		m_AdmIfCfg[i].bPldCnt = m_NumOfPld;
		m_AdmIfCfg[i].dRefGen[0] = UINT(m_Gen1 * 1000000.);
		m_AdmIfCfg[i].dRefGen[1] = UINT(m_Gen2 * 1000000.);
		m_AdmIfCfg[i].wRefPVS = m_RefVoltPvs;
		m_AdmIfCfg[i].bIsStartSync = m_Start;
		if(m_Pio)
			if(m_PioType)
				m_AdmIfCfg[i].bPioType = 2; // LVDS
			else
				m_AdmIfCfg[i].bPioType = 1; // TTL
		else
			m_AdmIfCfg[i].bPioType = 0; // Non
	}

	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADMIFNUM), IDC_ADMIFNUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_GEN1), IDC_GEN1);
	m_ToolTip.AddTool(GetDlgItem(IDC_GEN2), IDC_GEN2);
	m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADCFIFO), IDC_NUMOFADCFIFO);
	m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFDAC), IDC_NUMOFDAC);
	m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFDACFIFO), IDC_NUMOFDACFIFO);
	m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFPLD), IDC_NUMOFPLD);
	m_ToolTip.AddTool(GetDlgItem(IDC_REFVOLTPVS), IDC_REFVOLTPVS);
	m_ToolTip.AddTool(GetDlgItem(IDC_PIOBE), IDC_PIOBE);
	m_ToolTip.AddTool(GetDlgItem(IDC_STARTBE), IDC_STARTBE);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADMIFTYPE), IDC_ADMIFTYPE);
	m_ToolTip.AddTool(GetDlgItem(IDC_PIOTYPE), IDC_PIOTYPE);
//  EnableToolTips(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
/////////////////////////////////////////////////////////////////////////////
BOOL CAdm2IfPage::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
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
void CAdm2IfPage::OnDeltaposSpinadmifnum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(newVal >=0 && newVal <= (int)m_AdmIfMax)
	{
		m_AdmIfNum = newVal;
		UpdateData(FALSE); // from variable to window
		ChangeAdmIfNum();
	}
	*pResult = 0;
}

void CAdm2IfPage::OnKillfocusAdmifnum() 
{
	// TODO: Add your control notification handler code here
	ChangeAdmIfNum();
}

void CAdm2IfPage::OnKillfocusAdmiftype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].bType = m_AdmIfType;
}

void CAdm2IfPage::OnKillfocusGen1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].dRefGen[0] = UINT(m_Gen1 * 1000000.);
}

void CAdm2IfPage::OnKillfocusGen2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].dRefGen[1] = UINT(m_Gen2 * 1000000.);
}

void CAdm2IfPage::OnKillfocusNumofadcfifo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].bAdcFifoCnt = m_NumOfAdcFifo;

	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->m_pFifoPage->SetMaxAdcFifo(m_NumOfAdcFifo - 1);
}

void CAdm2IfPage::OnKillfocusNumofdac() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].bDacCnt = m_NumOfDac;

	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->m_pDacPage->SetMaxDac(m_NumOfDac - 1);
}

void CAdm2IfPage::OnKillfocusNumofdacfifo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].bDacFifoCnt = m_NumOfDacFifo;

	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->m_pFifoPage->SetMaxDacFifo(m_NumOfDacFifo - 1);
}

void CAdm2IfPage::OnKillfocusNumofpld() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].bPldCnt = m_NumOfPld;

	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->m_pPldPage->SetMaxPld(m_NumOfPld - 1);
}

void CAdm2IfPage::OnKillfocusRefvoltpvs() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].wRefPVS = m_RefVoltPvs;
}

void CAdm2IfPage::OnPiobe() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	if(m_Pio)
	{
		if(m_PioType)
			m_AdmIfCfg[m_AdmIfNum].bPioType = 2; // LVDS
		else
			m_AdmIfCfg[m_AdmIfNum].bPioType = 1; // TTL
	}
	else
	{
		m_AdmIfCfg[m_AdmIfNum].bPioType = 0; // Non
	}
	CWnd* pPioType = (CWnd*)GetDlgItem(IDC_PIOTYPE);
	pPioType->EnableWindow(m_Pio);
//	m_AdmIfCfg[m_AdmIfNum].bIsPio = m_Pio;
}

void CAdm2IfPage::OnKillfocusPiotype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	if(m_Pio)
		if(m_PioType)
			m_AdmIfCfg[m_AdmIfNum].bPioType = 2; // LVDS
		else
			m_AdmIfCfg[m_AdmIfNum].bPioType = 1; // TTL
	else
		m_AdmIfCfg[m_AdmIfNum].bPioType = 0; // Non
}

void CAdm2IfPage::OnStartbe() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmIfCfg[m_AdmIfNum].bIsStartSync = m_Start;
}

void CAdm2IfPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pCurrent = GetFocus();
	CWnd* pNum = (CWnd*)GetDlgItem(IDC_ADMIFNUM);
	if(pCurrent == pNum)
		ChangeAdmIfNum();
//	CPropertyPage::OnOK();
}

void CAdm2IfPage::ChangeAdmIfNum() 
{
	UpdateData(TRUE); // from window to variable
	int num = m_AdmIfNum;

	m_AdmIfType = m_AdmIfCfg[num].bType;

	m_NumOfAdcFifo = m_AdmIfCfg[num].bAdcFifoCnt;
	m_NumOfDac = m_AdmIfCfg[num].bDacCnt;
	m_NumOfDacFifo = m_AdmIfCfg[num].bDacFifoCnt;
	m_NumOfPld = m_AdmIfCfg[num].bPldCnt;

	m_Gen1 = m_AdmIfCfg[num].dRefGen[0] / 1000000.;
	m_Gen2 = m_AdmIfCfg[num].dRefGen[1] / 1000000.;
	m_RefVoltPvs = m_AdmIfCfg[num].wRefPVS;
	m_Start = m_AdmIfCfg[num].bIsStartSync;

	switch(m_AdmIfCfg[num].bPioType)
	{
	case 0: // Non
		m_Pio = FALSE;
		m_PioType = 0;
		break;
	case 1: // TTL
		m_Pio = TRUE;
		m_PioType = 0;
		break;
	case 2: // LVDS
		m_Pio = TRUE;
		m_PioType = 1;
		break;
	}
	CWnd* pPioType = (CWnd*)GetDlgItem(IDC_PIOTYPE);
	pPioType->EnableWindow(m_Pio);

//	m_Pio = m_AdmIfCfg[num].bIsPio;

	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->m_pDacPage->m_AdmIfNum = m_AdmIfNum;
	pParentWnd->m_pFifoPage->m_AdmIfNum = m_AdmIfNum;
	pParentWnd->m_pPldPage->m_AdmIfNum = m_AdmIfNum;
	pParentWnd->m_pAdmPage->m_AdmNum = m_AdmIfNum;
	UpdateData(FALSE); // from variable to window

	ICR_IdAdm AdmId;
	ICR_IdComment CommentId;
	pParentWnd->m_pAdmPage->GetIdDataFromDlg(&AdmId, &CommentId, m_AdmIfNum);
	pParentWnd->m_pAdmPage->SetIdDataIntoDlg(&AdmId, &CommentId);
	pParentWnd->m_pAdmPage->UpdateData(FALSE);

	ICR_CfgAdcFifo AdcFifo;
	pParentWnd->m_pFifoPage->GetDataFromDlg(&AdcFifo, pParentWnd->m_pFifoPage->m_AdcFifoNum, m_AdmIfNum);
	pParentWnd->m_pFifoPage->SetDataIntoDlg(&AdcFifo);
	ICR_CfgDacFifo DacFifo;
	pParentWnd->m_pFifoPage->GetDataFromDlg(&DacFifo, pParentWnd->m_pFifoPage->m_DacFifoNum, m_AdmIfNum);
	pParentWnd->m_pFifoPage->SetDataIntoDlg(&DacFifo);
	pParentWnd->m_pFifoPage->UpdateData(FALSE);

	ICR_CfgDac DacCfg;
	pParentWnd->m_pDacPage->GetDataFromDlg(&DacCfg, pParentWnd->m_pDacPage->m_DacNum, m_AdmIfNum);
	pParentWnd->m_pDacPage->SetDataIntoDlg(&DacCfg);
	pParentWnd->m_pDacPage->UpdateData(FALSE);

	ICR_CfgAdmPld PldCfg;
	pParentWnd->m_pPldPage->GetDataFromDlg(&PldCfg, pParentWnd->m_pPldPage->m_PldNum, m_AdmIfNum);
	pParentWnd->m_pPldPage->SetDataIntoDlg(&PldCfg);
	pParentWnd->m_pPldPage->UpdateData(FALSE);
}

void CAdm2IfPage::SetMaxAdmIf(int maxAdmIf)
{
	m_AdmIfMax = maxAdmIf;
	BOOL enFlag = TRUE;
	if(m_AdmIfMax >= 0)
		m_ctrlSpinAdmIfNum.SetRange(0, m_AdmIfMax);
	else
		enFlag = FALSE;
	CWnd* pAdmIfNum = (CWnd*)GetDlgItem(IDC_ADMIFNUM);
	CWnd* pAdmIfType = (CWnd*)GetDlgItem(IDC_ADMIFTYPE);
	CWnd* pNumOfPld = (CWnd*)GetDlgItem(IDC_NUMOFPLD);
	CWnd* pNumOfAdcFifo = (CWnd*)GetDlgItem(IDC_NUMOFADCFIFO);
	CWnd* pNumOfDac = (CWnd*)GetDlgItem(IDC_NUMOFDAC);
	CWnd* pNumOfDacFifo = (CWnd*)GetDlgItem(IDC_NUMOFDACFIFO);
	CWnd* pStart = (CWnd*)GetDlgItem(IDC_STARTBE);
	CWnd* pPio = (CWnd*)GetDlgItem(IDC_PIOBE);
	CWnd* pPioType = (CWnd*)GetDlgItem(IDC_PIOTYPE);
	CWnd* pGen1 = (CWnd*)GetDlgItem(IDC_GEN1);
	CWnd* pGen2 = (CWnd*)GetDlgItem(IDC_GEN2);
	CWnd* pRefVoltsPvs = (CWnd*)GetDlgItem(IDC_REFVOLTPVS);
	
	pAdmIfNum->EnableWindow(enFlag);
	pAdmIfType->EnableWindow(enFlag);
	pNumOfPld->EnableWindow(enFlag);
	pNumOfAdcFifo->EnableWindow(enFlag);
	pNumOfDac->EnableWindow(enFlag);
	pNumOfDacFifo->EnableWindow(enFlag);
	pStart->EnableWindow(enFlag);
	pPio->EnableWindow(enFlag);
	pPioType->EnableWindow(enFlag);
	pGen1->EnableWindow(enFlag);
	pGen2->EnableWindow(enFlag);
	pRefVoltsPvs->EnableWindow(enFlag);
}

// Data from ICR_CfgAdm2If into dialog control
void CAdm2IfPage::SetDataIntoDlg(PICR_CfgAdm2If pAdmIfCfg)
{
	UINT num = pAdmIfCfg->bNumber;
	m_AdmIfCfg[num].bNumber = pAdmIfCfg->bNumber;

	m_AdmIfCfg[num].bType = pAdmIfCfg->bType;

	m_AdmIfCfg[num].bAdcFifoCnt = pAdmIfCfg->bAdcFifoCnt;
	m_AdmIfCfg[num].bDacCnt = pAdmIfCfg->bDacCnt;
	m_AdmIfCfg[num].bDacFifoCnt = pAdmIfCfg->bDacFifoCnt;
	m_AdmIfCfg[num].bPldCnt = pAdmIfCfg->bPldCnt;

	m_AdmIfCfg[num].dRefGen[0] = pAdmIfCfg->dRefGen[0];
	m_AdmIfCfg[num].dRefGen[1] = pAdmIfCfg->dRefGen[1];
	m_AdmIfCfg[num].wRefPVS = pAdmIfCfg->wRefPVS;
	m_AdmIfCfg[num].bIsStartSync = pAdmIfCfg->bIsStartSync;
	m_AdmIfCfg[num].bPioType = pAdmIfCfg->bPioType;

	if(num == m_AdmIfNum)
	{
		m_AdmIfType = m_AdmIfCfg[num].bType;
		m_NumOfAdcFifo = m_AdmIfCfg[num].bAdcFifoCnt;
		m_NumOfDac = m_AdmIfCfg[num].bDacCnt;
		m_NumOfDacFifo = m_AdmIfCfg[num].bDacFifoCnt;
		m_NumOfPld = m_AdmIfCfg[num].bPldCnt;

		m_Gen1 = m_AdmIfCfg[num].dRefGen[0] / 1000000.;
		m_Gen2 = m_AdmIfCfg[num].dRefGen[1] / 1000000.;
		m_RefVoltPvs = m_AdmIfCfg[num].wRefPVS;
		m_Start = m_AdmIfCfg[num].bIsStartSync;
		switch(m_AdmIfCfg[num].bPioType)
		{
		case 0: // Non
			m_Pio = FALSE;
			m_PioType = 0;
			break;
		case 1: // TTL
			m_Pio = TRUE;
			m_PioType = 0;
			break;
		case 2: // LVDS
			m_Pio = TRUE;
			m_PioType = 1;
			break;
		}
//		m_Pio = m_AdmIfCfg[num].bIsPio;
		UpdateData(FALSE); // from variable to window
	}
}

// Data from dialog control into ICR_CfgAdm2If
void CAdm2IfPage::GetDataFromDlg(PICR_CfgAdm2If pAdmIfCfg, UINT num) 
{
	UpdateData(TRUE); // from window to variable

	pAdmIfCfg->wTag = ADM2IF_CFG_TAG;
	pAdmIfCfg->wSize = sizeof(ICR_CfgAdm2If) - 4;

	pAdmIfCfg->bNumber = m_AdmIfCfg[num].bNumber;

	pAdmIfCfg->bType = m_AdmIfCfg[num].bType;

	pAdmIfCfg->bAdcFifoCnt = m_AdmIfCfg[num].bAdcFifoCnt;
	pAdmIfCfg->bDacCnt = m_AdmIfCfg[num].bDacCnt;
	pAdmIfCfg->bDacFifoCnt = m_AdmIfCfg[num].bDacFifoCnt;
	pAdmIfCfg->bPldCnt = m_AdmIfCfg[num].bPldCnt;

	pAdmIfCfg->dRefGen[0] = m_AdmIfCfg[num].dRefGen[0];
	pAdmIfCfg->dRefGen[1] = m_AdmIfCfg[num].dRefGen[1];
	pAdmIfCfg->wRefPVS = m_AdmIfCfg[num].wRefPVS;
	pAdmIfCfg->bIsStartSync = m_AdmIfCfg[num].bIsStartSync;
	pAdmIfCfg->bPioType = m_AdmIfCfg[num].bPioType;
}

BOOL CAdm2IfPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}
