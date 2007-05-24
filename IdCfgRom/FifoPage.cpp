// FifoPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "FifoPage.h"
#include "IdCfgRomDlg.h"
#include ".\fifopage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFifoPage property page

IMPLEMENT_DYNAMIC(CFifoPage, CPropertyPage)

CFifoPage::CFifoPage() : CPropertyPage(CFifoPage::IDD)
{
	//{{AFX_DATA_INIT(CFifoPage)
	m_AdcFifoBitsWidth = 3;
	m_AdcFifoSize = 11;
	m_DacFifoBitsWidth = 2;
	m_DacFifoSize = 10;
	m_DacFifoCycling = TRUE;
	m_AdcFifoNum = 0;
	m_DacFifoNum = 0;
	//}}AFX_DATA_INIT
	m_AdmIfNum = 0;
}

void CFifoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFifoPage)
	DDX_Control(pDX, IDC_SPINDACFIFONUM, m_ctrlSpinDacFifoNum);
	DDX_Control(pDX, IDC_SPINADCFIFONUM, m_ctrlSpinAdcFifoNum);
	DDX_CBIndex(pDX, IDC_ADCFIFOBITSWIDTH, m_AdcFifoBitsWidth);
	DDX_CBIndex(pDX, IDC_ADCFIFOSIZE, m_AdcFifoSize);
	DDX_CBIndex(pDX, IDC_DACFIFOBITSWIDTH, m_DacFifoBitsWidth);
	DDX_CBIndex(pDX, IDC_DACFIFOSIZE, m_DacFifoSize);
	DDX_Check(pDX, IDC_DACFIFOCYCLING, m_DacFifoCycling);
	DDX_Text(pDX, IDC_ADCFIFONUM, m_AdcFifoNum);
	DDX_Text(pDX, IDC_DACFIFONUM, m_DacFifoNum);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_AdcFifoNum, 0, m_AdcFifoMax);
	DDV_MinMaxUInt(pDX, m_DacFifoNum, 0, m_DacFifoMax);
}


BEGIN_MESSAGE_MAP(CFifoPage, CPropertyPage)
//	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	//{{AFX_MSG_MAP(CFifoPage)
	ON_EN_KILLFOCUS(IDC_ADCFIFONUM, OnKillfocusAdcfifonum)
	ON_EN_KILLFOCUS(IDC_DACFIFONUM, OnKillfocusDacfifonum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINADCFIFONUM, OnDeltaposSpinadcfifonum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINDACFIFONUM, OnDeltaposSpindacfifonum)
	ON_CBN_SELCHANGE(IDC_DACFIFOSIZE, OnSelchangeDacfifosize)
	ON_BN_CLICKED(IDC_DACFIFOCYCLING, OnDacfifocycling)
	ON_CBN_SELCHANGE(IDC_DACFIFOBITSWIDTH, OnSelchangeDacfifobitswidth)
	ON_CBN_SELCHANGE(IDC_ADCFIFOSIZE, OnSelchangeAdcfifosize)
	ON_CBN_SELCHANGE(IDC_ADCFIFOBITSWIDTH, OnSelchangeAdcfifobitswidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFifoPage message handlers

BOOL CFifoPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	SetMaxAdcFifo(pParentWnd->m_pAdmIfPage->m_NumOfAdcFifo - 1);
	SetMaxDacFifo(pParentWnd->m_pAdmIfPage->m_NumOfDacFifo - 1);

	for(int i = 0; i < MAX_ADMIFCFG; i++)
	{
		for(int j = 0; j < MAX_ADCFIFOCFG; j++)
		{
			m_AdcFifo[i][j].bNumber = j;
			m_AdcFifo[i][j].bAdmNum = i;
			m_AdcFifo[i][j].bDepth = m_AdcFifoSize;
			m_AdcFifo[i][j].bBitsWidth = m_AdcFifoBitsWidth;
		}
		for(int j = 0; j < MAX_DACFIFOCFG; j++)
		{
			m_DacFifo[i][j].bNumber = j;
			m_DacFifo[i][j].bAdmNum = i;
			m_DacFifo[i][j].bDepth = m_DacFifoSize;
			m_DacFifo[i][j].bBitsWidth = m_DacFifoBitsWidth;
			m_DacFifo[i][j].bIsCycle = m_DacFifoCycling;
		}
	}

	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCFIFOBITSWIDTH), IDC_ADCFIFOBITSWIDTH);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCFIFOSIZE), IDC_ADCFIFOSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACFIFOBITSWIDTH), IDC_DACFIFOBITSWIDTH);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACFIFOSIZE), IDC_DACFIFOSIZE);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACFIFOCYCLING), IDC_DACFIFOCYCLING);
	m_ToolTip.AddTool(GetDlgItem(IDC_ADCFIFONUM), IDC_ADCFIFONUM);
	m_ToolTip.AddTool(GetDlgItem(IDC_DACFIFONUM), IDC_DACFIFONUM);
//    EnableToolTips(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
/////////////////////////////////////////////////////////////////////////////
BOOL CFifoPage::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
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
void CFifoPage::OnSelchangeDacfifosize() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacFifo[m_AdmIfNum][m_DacFifoNum].bDepth = m_DacFifoSize;
}

void CFifoPage::OnDacfifocycling() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacFifo[m_AdmIfNum][m_DacFifoNum].bIsCycle = m_DacFifoCycling;
}

void CFifoPage::OnSelchangeDacfifobitswidth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacFifo[m_AdmIfNum][m_DacFifoNum].bBitsWidth = m_DacFifoBitsWidth;
}

void CFifoPage::OnSelchangeAdcfifosize() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdcFifo[m_AdmIfNum][m_AdcFifoNum].bDepth = m_AdcFifoSize;
}

void CFifoPage::OnSelchangeAdcfifobitswidth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdcFifo[m_AdmIfNum][m_AdcFifoNum].bBitsWidth = m_AdcFifoBitsWidth;
}

void CFifoPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pCurrent = GetFocus();
	CWnd* pAdcNum = (CWnd*)GetDlgItem(IDC_ADCFIFONUM);
	if(pCurrent == pAdcNum)
		ChangeAdcFifoNum();
	CWnd* pDacNum = (CWnd*)GetDlgItem(IDC_DACFIFONUM);
	if(pCurrent == pDacNum)
		ChangeDacFifoNum();
//	CPropertyPage::OnOK();
}

void CFifoPage::OnKillfocusAdcfifonum() 
{
	// TODO: Add your control notification handler code here
	ChangeAdcFifoNum();
}

void CFifoPage::OnKillfocusDacfifonum() 
{
	// TODO: Add your control notification handler code here
	ChangeDacFifoNum();
}

void CFifoPage::OnDeltaposSpinadcfifonum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(newVal >=0 && newVal <= (int)m_AdcFifoMax)
	{
		m_AdcFifoNum = newVal;
		UpdateData(FALSE); // from variable to window
		ChangeAdcFifoNum();
	}
	*pResult = 0;
}

void CFifoPage::OnDeltaposSpindacfifonum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(newVal >=0 && newVal <= (int)m_DacFifoMax)
	{
		m_DacFifoNum = newVal;
		UpdateData(FALSE); // from variable to window
		ChangeDacFifoNum();
	}
	*pResult = 0;
}

void CFifoPage::ChangeAdcFifoNum() 
{
	UpdateData(TRUE); // from window to variable
	int num = m_AdcFifoNum;
	m_AdcFifoSize = m_AdcFifo[m_AdmIfNum][num].bDepth;
	m_AdcFifoBitsWidth = m_AdcFifo[m_AdmIfNum][num].bBitsWidth;
	UpdateData(FALSE); // from variable to window
}

void CFifoPage::ChangeDacFifoNum() 
{
	UpdateData(TRUE); // from window to variable
	int num = m_DacFifoNum;
	m_DacFifoSize = m_DacFifo[m_AdmIfNum][num].bDepth;
	m_DacFifoBitsWidth = m_DacFifo[m_AdmIfNum][num].bBitsWidth;
	m_DacFifoCycling = m_DacFifo[m_AdmIfNum][num].bIsCycle;
	UpdateData(FALSE); // from variable to window
}

void CFifoPage::SetMaxAdcFifo(int maxAdcFifo)
{
	m_AdcFifoMax = maxAdcFifo;
	BOOL enFlag = TRUE;
	if(m_AdcFifoMax >= 0) {
		m_ctrlSpinAdcFifoNum.SetRange(0, m_AdcFifoMax);
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		CWnd* pNumOfAdcFifo = (CWnd*)pParentWnd->m_pAdmIfPage->GetDlgItem(IDC_NUMOFADCFIFO);
		enFlag = pNumOfAdcFifo->IsWindowEnabled();
	}
	else
		enFlag = FALSE;
	CWnd* pAdcFifoNum = (CWnd*)GetDlgItem(IDC_ADCFIFONUM);
	CWnd* pAdcFifoSize = (CWnd*)GetDlgItem(IDC_ADCFIFOSIZE);
	CWnd* pAdcFifoBitsWidth = (CWnd*)GetDlgItem(IDC_ADCFIFOBITSWIDTH);

	pAdcFifoNum->EnableWindow(enFlag);
	pAdcFifoSize->EnableWindow(enFlag);
	pAdcFifoBitsWidth->EnableWindow(enFlag);
}

void CFifoPage::SetMaxDacFifo(int maxDacFifo)
{
	m_DacFifoMax = maxDacFifo;
	BOOL enFlag = TRUE;
	if(m_DacFifoMax >= 0) {
		m_ctrlSpinDacFifoNum.SetRange(0, m_DacFifoMax);
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		CWnd* pNumOfDacFifo = (CWnd*)pParentWnd->m_pAdmIfPage->GetDlgItem(IDC_NUMOFDACFIFO);
		enFlag = pNumOfDacFifo->IsWindowEnabled();
	}
	else
		enFlag = FALSE;
	CWnd* pDacFifoNum = (CWnd*)GetDlgItem(IDC_DACFIFONUM);
	CWnd* pDacFifoSize = (CWnd*)GetDlgItem(IDC_DACFIFOSIZE);
	CWnd* pDacFifoBitsWidth = (CWnd*)GetDlgItem(IDC_DACFIFOBITSWIDTH);
	CWnd* pDacFifoCycling = (CWnd*)GetDlgItem(IDC_DACFIFOCYCLING);

	pDacFifoNum->EnableWindow(enFlag);
	pDacFifoSize->EnableWindow(enFlag);
	pDacFifoBitsWidth->EnableWindow(enFlag);
	pDacFifoCycling->EnableWindow(enFlag);
}

// Data from ADC_FIFO into dialog control
//void CFifoPage::GetDataFromModule(ADC_FIFO& AdcFifo, DAC_FIFO& DacFifo) 
void CFifoPage::SetDataIntoDlg(PICR_CfgAdcFifo pAdcFifo)
{
	UINT AdmNum = pAdcFifo->bAdmNum;
	UINT num = pAdcFifo->bNumber;
	m_AdcFifo[AdmNum][num].bAdmNum = pAdcFifo->bAdmNum;

	m_AdcFifo[AdmNum][num].bNumber = pAdcFifo->bNumber;
	
	if(pAdcFifo->bDepth)
	{
		if(pAdcFifo->bDepth < 5)
			pAdcFifo->bDepth = 5;
		if(pAdcFifo->bDepth > 20)
			pAdcFifo->bDepth = 20;
		m_AdcFifo[AdmNum][num].bDepth = pAdcFifo->bDepth - 4;
	}
	else
		m_AdcFifo[AdmNum][num].bDepth = 0;
	m_AdcFifo[AdmNum][num].bBitsWidth = pAdcFifo->bBitsWidth;

	if(num == m_AdcFifoNum && AdmNum == m_AdmIfNum)
	{
		m_AdcFifoSize = m_AdcFifo[AdmNum][num].bDepth;
		m_AdcFifoBitsWidth = m_AdcFifo[AdmNum][num].bBitsWidth;
		UpdateData(FALSE);
	}
}

// Data from DAC_FIFO into dialog control
void CFifoPage::SetDataIntoDlg(PICR_CfgDacFifo pDacFifo)
{
	UINT AdmNum = pDacFifo->bAdmNum;
	UINT num = pDacFifo->bNumber;
	m_DacFifo[AdmNum][num].bAdmNum = pDacFifo->bAdmNum;

	m_DacFifo[AdmNum][num].bNumber = pDacFifo->bNumber;

	if(pDacFifo->bDepth)
	{
		if(pDacFifo->bDepth < 5)
			pDacFifo->bDepth = 5;
		if(pDacFifo->bDepth > 20)
			pDacFifo->bDepth = 20;
		m_DacFifo[AdmNum][num].bDepth = pDacFifo->bDepth - 4;
	}
	else
		m_DacFifo[AdmNum][num].bDepth = 0;
	m_DacFifo[AdmNum][num].bBitsWidth = pDacFifo->bBitsWidth;
	m_DacFifo[AdmNum][num].bIsCycle = pDacFifo->bIsCycle;

	if(num == m_DacFifoNum && AdmNum == m_AdmIfNum)
	{
		m_DacFifoSize = m_DacFifo[AdmNum][num].bDepth;
		m_DacFifoBitsWidth = m_DacFifo[AdmNum][num].bBitsWidth;
		m_DacFifoCycling = m_DacFifo[AdmNum][num].bIsCycle;
		UpdateData(FALSE);
	}
}

// Data from dialog control into ADC_FIFO
//void CFifoPage::SetDataIntoModule(ADC_FIFO& AdcFifo, DAC_FIFO& DacFifo) 
void CFifoPage::GetDataFromDlg(PICR_CfgAdcFifo pAdcFifo, UINT num, UINT AdmNum)
{
	UpdateData(TRUE);

	pAdcFifo->wTag = ADC_FIFO_TAG;
	pAdcFifo->wSize = sizeof(ICR_CfgAdcFifo) - 4;
	pAdcFifo->bAdmNum = AdmNum;

	pAdcFifo->bNumber = m_AdcFifo[AdmNum][num].bNumber;

	if(m_AdcFifoSize)
		pAdcFifo->bDepth = m_AdcFifo[AdmNum][num].bDepth + 4;
	else
		pAdcFifo->bDepth = 0;
	pAdcFifo->bBitsWidth = m_AdcFifo[AdmNum][num].bBitsWidth;
}

// Data from dialog control into DAC_FIFO
void CFifoPage::GetDataFromDlg(PICR_CfgDacFifo pDacFifo, UINT num, UINT AdmNum) 
{
	UpdateData(TRUE);

	pDacFifo->wTag = DAC_FIFO_TAG;
	pDacFifo->wSize = sizeof(ICR_CfgDacFifo) - 4;
	pDacFifo->bAdmNum = AdmNum;

	pDacFifo->bNumber = m_DacFifo[AdmNum][num].bNumber;

	if(m_DacFifoSize)
		pDacFifo->bDepth = m_DacFifo[AdmNum][num].bDepth + 4;
	else
		pDacFifo->bDepth = 0;
	pDacFifo->bBitsWidth = m_DacFifo[AdmNum][num].bBitsWidth;
	pDacFifo->bIsCycle = m_DacFifo[AdmNum][num].bIsCycle;
}

BOOL CFifoPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}
