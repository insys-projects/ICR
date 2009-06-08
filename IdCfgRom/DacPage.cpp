// DacPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "DacPage.h"
#include "IdCfgRomDlg.h"
#include ".\dacpage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDacPage property page

IMPLEMENT_DYNAMIC(CDacPage, CPropertyPage)

CDacPage::CDacPage() : CPropertyPage(CDacPage::IDD)
{
	//{{AFX_DATA_INIT(CDacPage)
	m_DacNum = 0;
	m_DacBits = 3;
	m_DacEncoding = 1;
	m_DacAFCoff = 1000000;
	m_DacHPFCoff = 5000;
	m_DacLPFCoff = 3;
	m_DacRangeAF = 1000;
	m_DacRangePF = 500;
	m_DacRateMax = 30000000;
	m_DacRateMin = 0;
	//}}AFX_DATA_INIT
	m_AdmIfNum = 0;
}

void CDacPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDacPage)
	DDX_Control(pDX, IDC_SPINDACNUM, m_ctrlSpinDacNum);
	DDX_CBIndex(pDX, IDC_DACENCODING, m_DacEncoding);
	DDX_Text(pDX, IDC_DACNUM, m_DacNum);
	DDX_Text(pDX, IDC_DACAFCOFF, m_DacAFCoff);
	DDX_Text(pDX, IDC_DACHPFCOFF, m_DacHPFCoff);
	DDX_Text(pDX, IDC_DACLPFCOFF, m_DacLPFCoff);
	DDX_Text(pDX, IDC_DACRANGEAF, m_DacRangeAF);
	DDX_Text(pDX, IDC_DACRANGEPF, m_DacRangePF);
	DDX_Text(pDX, IDC_DACRATEMAX, m_DacRateMax);
	DDX_Text(pDX, IDC_DACRATEMIN, m_DacRateMin);
	DDX_CBIndex(pDX, IDC_DACBITS, m_DacBits);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_DacNum, 0, m_DacMax);
	DDX_Control(pDX, IDC_AFSET, m_btnDacAFSet);
	DDX_Control(pDX, IDC_DACRANGEAF, m_edtDacRangeAF);
	DDX_Control(pDX, IDC_DACAFCOFF, m_edtDacAFCoff);
	DDX_Control(pDX, IDC_DISDACRANGEAF, m_edtDisableDacRangeAF);
	DDX_Control(pDX, IDC_DISDACAFCOFF, m_edtDisableDacAFCoff);
	DDX_Control(pDX, IDC_PFSET, m_btnDacPFSet);
	DDX_Control(pDX, IDC_DACHPFCOFF, m_edtDacHPFCoff);
	DDX_Control(pDX, IDC_DACLPFCOFF, m_edtDacLPFCoff);
	DDX_Control(pDX, IDC_DACRANGEPF, m_edtDacRangePF);
	DDX_Control(pDX, IDC_DISDACRANGEPF, m_edtDisableDacRangePF);
	DDX_Control(pDX, IDC_DISDACLPFCOFF, m_edtDisableDacLPFCoff);
	DDX_Control(pDX, IDC_DISDACHPFCOFF, m_edtDisableDacHPFCoff);
}


BEGIN_MESSAGE_MAP(CDacPage, CPropertyPage)
//	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	//{{AFX_MSG_MAP(CDacPage)
	ON_EN_KILLFOCUS(IDC_DACNUM, OnKillfocusDacnum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINDACNUM, OnDeltaposSpindacnum)
	ON_CBN_SELCHANGE(IDC_DACENCODING, OnSelchangeDacencoding)
	ON_EN_KILLFOCUS(IDC_DACAFCOFF, OnKillfocusDacafcoff)
	ON_EN_KILLFOCUS(IDC_DACHPFCOFF, OnKillfocusDachpfcoff)
	ON_EN_KILLFOCUS(IDC_DACLPFCOFF, OnKillfocusDaclpfcoff)
	ON_EN_KILLFOCUS(IDC_DACRANGEAF, OnKillfocusDacrangeaf)
	ON_EN_KILLFOCUS(IDC_DACRANGEPF, OnKillfocusDacrangepf)
	ON_EN_KILLFOCUS(IDC_DACRATEMAX, OnKillfocusDacratemax)
	ON_EN_KILLFOCUS(IDC_DACRATEMIN, OnKillfocusDacratemin)
	ON_CBN_SELCHANGE(IDC_DACBITS, OnSelchangeDacbits)
	//}}AFX_MSG_MAP
//	ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_AFSET, &CDacPage::OnBnClickedAfset)
ON_BN_CLICKED(IDC_PFSET, &CDacPage::OnBnClickedPfset)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDacPage message handlers

BOOL CDacPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	SetMaxDac(pParentWnd->m_pAdmIfPage->m_NumOfDac - 1);

	for(int i = 0; i < MAX_ADMIFCFG; i++)
	{
		for(int j = 0; j < MAX_DACCFG; j++)
		{
			m_DacCfg[i][j].bNumber = j;
			m_DacCfg[i][j].bAdmNum = i;
			m_DacCfg[i][j].bBits = m_DacBits;
			m_DacCfg[i][j].bEncoding = m_DacEncoding;
			m_DacCfg[i][j].dMinRate = m_DacRateMin;
			m_DacCfg[i][j].dMaxRate = m_DacRateMax;
			m_DacCfg[i][j].wAFRange = m_DacRangeAF;
			m_DacCfg[i][j].wPFRange = m_DacRangePF;
			m_DacCfg[i][j].wAFCutoff = m_DacAFCoff / 100;
			m_DacCfg[i][j].wPFCutoffLo = m_DacLPFCoff;
			m_DacCfg[i][j].wPFCutoffHi = m_DacHPFCoff;
		}
	}

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACNUM), IDC_DACNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACENCODING), IDC_DACENCODING);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACAFCOFF), IDC_DACAFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACHPFCOFF), IDC_DACHPFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACLPFCOFF), IDC_DACLPFCOFF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGEAF), IDC_DACRANGEAF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRANGEPF), IDC_DACRANGEPF);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMAX), IDC_DACRATEMAX);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACRATEMIN), IDC_DACRATEMIN);
    m_ToolTip.AddTool(GetDlgItem(IDC_DACBITS), IDC_DACBITS);

	m_btnDacAFSet.SetCheck(TRUE);
	m_btnDacPFSet.SetCheck(TRUE);

//    EnableToolTips(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
/////////////////////////////////////////////////////////////////////////////
BOOL CDacPage::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT_PTR nID = pNMHDR->idFrom;
    if(pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
        if(nID != IDC_DACRANGEAF && nID != IDC_DACRANGEPF)
//        if(nID != IDC_TABPAGE)
        {
            pTTT->lpszText = MAKEINTRESOURCE(nID);
            pTTT->hinst = AfxGetResourceHandle();
            return(TRUE);
        }
    }
    return(FALSE);
}
*/
BOOL CDacPage::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CDacPage::OnSelchangeDacencoding() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].bEncoding = m_DacEncoding;
}

void CDacPage::OnSelchangeDacbits() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].bBits = m_DacBits;
}

void CDacPage::OnKillfocusDacafcoff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].wAFCutoff = m_DacAFCoff / 100;
}

void CDacPage::OnKillfocusDachpfcoff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].wPFCutoffHi = m_DacHPFCoff;
}

void CDacPage::OnKillfocusDaclpfcoff() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].wPFCutoffLo = m_DacLPFCoff;
}

void CDacPage::OnKillfocusDacrangeaf() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].wAFRange = m_DacRangeAF;
}

void CDacPage::OnKillfocusDacrangepf() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].wPFRange = m_DacRangePF;
}

void CDacPage::OnKillfocusDacratemax() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].dMaxRate = m_DacRateMax;
}

void CDacPage::OnKillfocusDacratemin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_DacCfg[m_AdmIfNum][m_DacNum].dMinRate = m_DacRateMin;
}

void CDacPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pCurrent = GetFocus();
	CWnd* pNum = (CWnd*)GetDlgItem(IDC_DACNUM);
	if(pCurrent == pNum)
		ChangeDacNum();
//	CPropertyPage::OnOK();
}

void CDacPage::OnKillfocusDacnum()
{
	// TODO: Add your control notification handler code here
	ChangeDacNum();
}

void CDacPage::OnDeltaposSpindacnum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(newVal >=0 && newVal <= (int)m_DacMax)
	{
		m_DacNum = newVal;
		UpdateData(FALSE); // from variable to window
		ChangeDacNum();
	}
	*pResult = 0;
}

void CDacPage::ChangeDacNum() 
{
	UpdateData(TRUE); // from window to variable
	int num = m_DacNum;
	m_DacBits = m_DacCfg[m_AdmIfNum][num].bBits;
	m_DacEncoding = m_DacCfg[m_AdmIfNum][num].bEncoding;
	m_DacRateMin = m_DacCfg[m_AdmIfNum][num].dMinRate;
	m_DacRateMax = m_DacCfg[m_AdmIfNum][num].dMaxRate;
	m_DacRangeAF = m_DacCfg[m_AdmIfNum][num].wAFRange;
	m_DacRangePF = m_DacCfg[m_AdmIfNum][num].wPFRange;
	m_DacAFCoff = m_DacCfg[m_AdmIfNum][num].wAFCutoff * 100;
	m_DacLPFCoff = m_DacCfg[m_AdmIfNum][num].wPFCutoffLo;
	m_DacHPFCoff = m_DacCfg[m_AdmIfNum][num].wPFCutoffHi;
	SetFiltersParamDlg();
	UpdateData(FALSE); // from variable to window
}

void CDacPage::SetMaxDac(int maxDac)
{
	m_DacMax = maxDac;
	BOOL enFlag = TRUE;
	if(m_DacMax >= 0) {
		m_ctrlSpinDacNum.SetRange(0, m_DacMax);
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		CWnd* pNumOfDac = (CWnd*)pParentWnd->m_pAdmIfPage->GetDlgItem(IDC_NUMOFDAC);
		enFlag = pNumOfDac->IsWindowEnabled();
	}
	else
		enFlag = FALSE;
	CWnd* pDacNum = (CWnd*)GetDlgItem(IDC_DACNUM);
	CWnd* pDacBits = (CWnd*)GetDlgItem(IDC_DACBITS);
	CWnd* pDacEncoding = (CWnd*)GetDlgItem(IDC_DACENCODING);
	CWnd* pDacAFCoff = (CWnd*)GetDlgItem(IDC_DACAFCOFF);
	CWnd* pDacHPFCoff = (CWnd*)GetDlgItem(IDC_DACHPFCOFF);
	CWnd* pDacLPFCoff = (CWnd*)GetDlgItem(IDC_DACLPFCOFF);
	CWnd* pDacRangeAF = (CWnd*)GetDlgItem(IDC_DACRANGEAF);
	CWnd* pDacRangePF = (CWnd*)GetDlgItem(IDC_DACRANGEPF);
	CWnd* pDacRateMax = (CWnd*)GetDlgItem(IDC_DACRATEMAX);
	CWnd* pDacRateMin = (CWnd*)GetDlgItem(IDC_DACRATEMIN);
	
	pDacNum->EnableWindow(enFlag);
	pDacBits->EnableWindow(enFlag);
	pDacEncoding->EnableWindow(enFlag);
	pDacAFCoff->EnableWindow(enFlag);
	pDacHPFCoff->EnableWindow(enFlag);
	pDacLPFCoff->EnableWindow(enFlag);
	pDacRangeAF->EnableWindow(enFlag);
	pDacRangePF->EnableWindow(enFlag);
	pDacRateMax->EnableWindow(enFlag);
	pDacRateMin->EnableWindow(enFlag);
}

// Data from DAC_CFG into dialog control
//void CDacPage::GetDataFromModule(DAC_CFG& DacCfg) 
void CDacPage::SetDataIntoDlg(PICR_CfgDac pDacCfg)
{
	UINT AdmNum = pDacCfg->bAdmNum;
	UINT num = pDacCfg->bNumber;
	m_DacCfg[AdmNum][num].bAdmNum = pDacCfg->bAdmNum;

	m_DacCfg[AdmNum][num].bNumber = pDacCfg->bNumber;
	
	if(pDacCfg->bBits < 24)
		m_DacCfg[AdmNum][num].bBits = (pDacCfg->bBits >> 1) - 4;
	else
		m_DacCfg[AdmNum][num].bBits = (pDacCfg->bBits >> 3) - 1;
//	m_DacCfg[num].Bits = pDacCfg->Bits;
	m_DacCfg[AdmNum][num].bEncoding = pDacCfg->bEncoding;
	m_DacCfg[AdmNum][num].dMinRate = pDacCfg->dMinRate;
	m_DacCfg[AdmNum][num].dMaxRate = pDacCfg->dMaxRate;
	m_DacCfg[AdmNum][num].wAFRange = pDacCfg->wAFRange;
	m_DacCfg[AdmNum][num].wPFRange = pDacCfg->wPFRange;
	m_DacCfg[AdmNum][num].wAFCutoff = pDacCfg->wAFCutoff;
	m_DacCfg[AdmNum][num].wPFCutoffLo = pDacCfg->wPFCutoffLo;
	m_DacCfg[AdmNum][num].wPFCutoffHi = pDacCfg->wPFCutoffHi;

	if(num == m_DacNum && AdmNum == m_AdmIfNum)
	{
		m_DacBits = m_DacCfg[AdmNum][num].bBits;
		m_DacEncoding = m_DacCfg[AdmNum][num].bEncoding;
		m_DacRateMin = m_DacCfg[AdmNum][num].dMinRate;
		m_DacRateMax = m_DacCfg[AdmNum][num].dMaxRate;
		m_DacRangeAF = m_DacCfg[AdmNum][num].wAFRange;
		m_DacRangePF = m_DacCfg[AdmNum][num].wPFRange;
		m_DacAFCoff = m_DacCfg[AdmNum][num].wAFCutoff * 100;
		m_DacLPFCoff = m_DacCfg[AdmNum][num].wPFCutoffLo;
		m_DacHPFCoff = m_DacCfg[AdmNum][num].wPFCutoffHi;
		SetFiltersParamDlg();
		UpdateData(FALSE);
	}
}

// Data from dialog control into DAC_CFG
//void CDacPage::SetDataIntoModule(DAC_CFG& DacCfg) 
void CDacPage::GetDataFromDlg(PICR_CfgDac pDacCfg, UINT num, UINT AdmNum) 
{
	UpdateData(TRUE);

	pDacCfg->wTag = DAC_CFG_TAG;
	pDacCfg->wSize = sizeof(ICR_CfgDac) - 4;
	pDacCfg->bAdmNum = AdmNum;

	pDacCfg->bNumber = m_DacCfg[AdmNum][num].bNumber;

	if(m_DacCfg[AdmNum][num].bBits < 7)
		pDacCfg->bBits = (m_DacCfg[AdmNum][num].bBits + 4) << 1;
	else
		pDacCfg->bBits = (m_DacCfg[AdmNum][num].bBits + 1) << 3;
	pDacCfg->bEncoding = m_DacCfg[AdmNum][num].bEncoding;
	pDacCfg->dMinRate = m_DacCfg[AdmNum][num].dMinRate;
	pDacCfg->dMaxRate = m_DacCfg[AdmNum][num].dMaxRate;
	pDacCfg->wAFRange = m_DacCfg[AdmNum][num].wAFRange;
	pDacCfg->wPFRange = m_DacCfg[AdmNum][num].wPFRange;
	pDacCfg->wAFCutoff = m_DacCfg[AdmNum][num].wAFCutoff;
	pDacCfg->wPFCutoffLo = m_DacCfg[AdmNum][num].wPFCutoffLo;
	pDacCfg->wPFCutoffHi = m_DacCfg[AdmNum][num].wPFCutoffHi;
}


//HBRUSH CDacPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  Change any attributes of the DC here
//    // Set the text color to red
//    pDC->SetBkColor(RGB(255, 0, 0));
//
//	// TODO:  Return a different brush if the default is not desired
//	return hbr;
//}

void CDacPage::OnBnClickedAfset()
{
	// TODO: Add your control notification handler code here

	if(m_btnDacAFSet.GetCheck() == BST_CHECKED)
	{
		m_DacRangeAF = 1000;
		m_DacAFCoff  = 1000000;

		m_edtDacRangeAF.ShowWindow(TRUE);
		m_edtDacAFCoff.ShowWindow(TRUE);
		
		m_edtDisableDacRangeAF.ShowWindow(FALSE);
		m_edtDisableDacAFCoff.ShowWindow(FALSE);

		UpdateData(FALSE);	
	}
	else
	{
		m_DacRangeAF = 0xFFFF;
		m_DacAFCoff  = 0xFFFF;

		m_edtDacRangeAF.ShowWindow(FALSE);
		m_edtDacAFCoff.ShowWindow(FALSE);

		m_edtDisableDacRangeAF.ShowWindow(TRUE);
		m_edtDisableDacAFCoff.ShowWindow(TRUE);
	}

	m_DacCfg[m_AdmIfNum][m_DacNum].wAFRange  = m_DacRangeAF;
	m_DacCfg[m_AdmIfNum][m_DacNum].wAFCutoff = m_DacAFCoff;
}

void CDacPage::OnBnClickedPfset()
{
	// TODO: Add your control notification handler code here

	if(m_btnDacPFSet.GetCheck() == BST_CHECKED)
	{
		m_DacHPFCoff = 5000;
		m_DacLPFCoff = 3;
		m_DacRangePF = 500;

		m_edtDacHPFCoff.ShowWindow(TRUE);
		m_edtDacLPFCoff.ShowWindow(TRUE);
		m_edtDacRangePF.ShowWindow(TRUE);

		m_edtDisableDacHPFCoff.ShowWindow(FALSE);
		m_edtDisableDacLPFCoff.ShowWindow(FALSE);
		m_edtDisableDacRangePF.ShowWindow(FALSE);
		
		UpdateData(FALSE);	
	}
	else
	{
		m_DacHPFCoff = 0xFFFF;
		m_DacLPFCoff = 0xFFFF;
		m_DacRangePF = 0xFFFF;

		m_edtDacHPFCoff.ShowWindow(FALSE);
		m_edtDacLPFCoff.ShowWindow(FALSE);
		m_edtDacRangePF.ShowWindow(FALSE);

		m_edtDisableDacHPFCoff.ShowWindow(TRUE);
		m_edtDisableDacLPFCoff.ShowWindow(TRUE);
		m_edtDisableDacRangePF.ShowWindow(TRUE);
	}

	m_DacCfg[m_AdmIfNum][m_DacNum].wPFCutoffHi = m_DacHPFCoff;
	m_DacCfg[m_AdmIfNum][m_DacNum].wPFCutoffLo = m_DacLPFCoff;
	m_DacCfg[m_AdmIfNum][m_DacNum].wPFRange	   = m_DacRangePF;
}

void CDacPage::SetFiltersParamDlg(void)
{
	if(m_DacRangeAF == 0xFFFF)
	{
		m_edtDacRangeAF.ShowWindow(FALSE);
		m_edtDacAFCoff.ShowWindow(FALSE);

		m_edtDisableDacRangeAF.ShowWindow(TRUE);
		m_edtDisableDacAFCoff.ShowWindow(TRUE);

		m_btnDacAFSet.SetCheck(FALSE);
	}
	else
	{
		m_edtDacRangeAF.ShowWindow(TRUE);
		m_edtDacAFCoff.ShowWindow(TRUE);

		m_edtDisableDacRangeAF.ShowWindow(FALSE);
		m_edtDisableDacAFCoff.ShowWindow(FALSE);

		m_btnDacAFSet.SetCheck(TRUE);
	}

	if(m_DacRangePF == 0xFFFF)
	{
		m_edtDacHPFCoff.ShowWindow(FALSE);
		m_edtDacLPFCoff.ShowWindow(FALSE);
		m_edtDacRangePF.ShowWindow(FALSE);

		m_edtDisableDacHPFCoff.ShowWindow(TRUE);
		m_edtDisableDacLPFCoff.ShowWindow(TRUE);
		m_edtDisableDacRangePF.ShowWindow(TRUE);

		m_btnDacPFSet.SetCheck(FALSE);
	}
	else
	{
		m_edtDacHPFCoff.ShowWindow(TRUE);
		m_edtDacLPFCoff.ShowWindow(TRUE);
		m_edtDacRangePF.ShowWindow(TRUE);

		m_edtDisableDacHPFCoff.ShowWindow(FALSE);
		m_edtDisableDacLPFCoff.ShowWindow(FALSE);
		m_edtDisableDacRangePF.ShowWindow(FALSE);

		m_btnDacPFSet.SetCheck(TRUE);
	}
}
