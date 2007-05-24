// AmbPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "AmbPage.h"
#include "IdCfgRomDlg.h"
#include ".\ambpage.h"

#define AMBPCI_CFGMEM_SIZE 128

extern BASEMOD_CTRL BaseModCtrl[];
extern int m_NumOfBaseModules;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmbPage property page

IMPLEMENT_DYNAMIC(CAmbPage, CPropertyPage)

CAmbPage::CAmbPage() : CPropertyPage(CAmbPage::IDD)
, m_strAmbVersion(_T("10"))
{
	//{{AFX_DATA_INIT(CAmbPage)
	m_SerialNum = 1;
	m_NumOfAdmIf = 1;
	m_BMType = 0;
//	m_AmbVersion = 0;
	//}}AFX_DATA_INIT
}

CAmbPage::~CAmbPage()
{
}

void CAmbPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmbPage)
	DDX_Text(pDX, IDC_SERIALNUM, m_SerialNum);
	DDV_MinMaxUInt(pDX, m_SerialNum, 1, 99999);
	DDX_Text(pDX, IDC_NUMOFADMIF, m_NumOfAdmIf);
	DDX_Control(pDX, IDC_SPINADMIF, m_ctrlSpinAdmIf);
	DDX_CBIndex(pDX, IDC_BMTYPE, m_BMType);
	DDX_Text(pDX, IDC_AMBVERSION, m_strAmbVersion);
//	DDX_Text(pDX, IDC_AMBVERSION, m_AmbVersion);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_NumOfAdmIf, 0, MAX_NUMOFADMIF - 1);
}


BEGIN_MESSAGE_MAP(CAmbPage, CPropertyPage)
//	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	//{{AFX_MSG_MAP(CAmbPage)
	ON_EN_KILLFOCUS(IDC_NUMOFADMIF, OnKillfocusNumofadmif)
	ON_CBN_SELCHANGE(IDC_BMTYPE, OnSelchangeBmtype)
	ON_BN_CLICKED(IDC_AMBEXT, OnAmbext)
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_AMBVERSION, OnKillfocusAmbversion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmbPage message handlers

BOOL CAmbPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox* pDevType = (CComboBox*)GetDlgItem(IDC_BMTYPE);
	pDevType->ResetContent();
	pDevType->AddString(_T("AMBPCI"));
	for(int i = 0; i < m_NumOfBaseModules; i++)
		pDevType->AddString(BaseModCtrl[i].devInfo.sName);
	pDevType->SetCurSel(0);

	m_ctrlSpinAdmIf.SetRange(0, MAX_NUMOFADMIF - 1);
	
	InitData();

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_SERIALNUM), IDC_SERIALNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_BMTYPE), IDC_BMTYPE);
    m_ToolTip.AddTool(GetDlgItem(IDC_AMBVERSION), IDC_AMBVERSION);
    m_ToolTip.AddTool(GetDlgItem(IDC_NUMOFADMIF), IDC_NUMOFADMIF);
    m_ToolTip.AddTool(GetDlgItem(IDC_AMBEXT), IDC_AMBEXT);
//    EnableToolTips(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAmbPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	for(int i = 0; i < m_NumOfBaseModules; i++) {
		PBASEMOD_INFO pDeviceInfo = &(BaseModCtrl[i].devInfo);
		BaseModCtrl[i].pClose(pDeviceInfo);
	}
}

void CAmbPage::InitData() 
{
	int enFlag = m_BMType ? 1 : 0;
	CWnd* pAmbExt = (CWnd*)GetDlgItem(IDC_AMBEXT);
	pAmbExt->EnableWindow(enFlag);
//	m_CfgBufSize = m_BMType ? BaseModCtrl[m_BMType - 1].devInfo.dCfgMemSize : AMBPCI_CFGMEM_SIZE;
	m_CfgBufSize = m_BMType ? BaseModCtrl[m_BMType - 1].devInfo.dCfgMemSize : AMBPCI_CFGMEM_SIZE;
	CComboBox* pType = (CComboBox*)GetDlgItem(IDC_BMTYPE);
	CString BaseModuleName;
	pType->GetLBText(m_BMType, BaseModuleName);
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	CString Title;
//	pParentWnd->GetWindowText(Title);
//	CString str = Title.SpanExcluding(" ");
	Title = _T("IdCfgRom (") + BaseModuleName + _T(")");
	pParentWnd->SetWindowText(Title);
}
/*
/////////////////////////////////////////////////////////////////////////////
BOOL CAmbPage::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
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
void CAmbPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CPropertyPage::OnOK();
}

void CAmbPage::OnKillfocusNumofadmif() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->m_pAdmIfPage->SetMaxAdmIf(m_NumOfAdmIf - 1);
	pParentWnd->m_pAdmPage->SetMaxAdm(m_NumOfAdmIf - 1);

	pParentWnd->m_pPldPage->SetMaxPld(pParentWnd->m_pAdmIfPage->m_NumOfPld - 1);
	pParentWnd->m_pFifoPage->SetMaxAdcFifo(pParentWnd->m_pAdmIfPage->m_NumOfAdcFifo - 1);
	pParentWnd->m_pFifoPage->SetMaxDacFifo(pParentWnd->m_pAdmIfPage->m_NumOfDacFifo - 1);
	pParentWnd->m_pDacPage->SetMaxDac(pParentWnd->m_pAdmIfPage->m_NumOfDac - 1);
}

void CAmbPage::OnAmbext() 
{
	// TODO: Add your control notification handler code here
	PBASEMOD_INFO pDeviceInfo = &(BaseModCtrl[m_BMType-1].devInfo);
	int nResponse = (BaseModCtrl[m_BMType-1].pDlgProperty)(pDeviceInfo);
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
//		m_pAdvPciBus->UpdateData(TRUE);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
}

void CAmbPage::OnSelchangeBmtype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	InitData();
}

void CAmbPage::OnKillfocusAmbversion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	
}
/*
// Data from BASE_ID into dialog control
//void CAmbPage::GetDataFromModule(BASE_ID& BaseId, BASE_CFG& BaseCfg) 
void CAmbPage::SetDataIntoDlg(PBASE_ID pBaseId)
{
	m_SerialNum = pBaseId->SerNum;
	m_BMType = pBaseId->Type;
//	m_Version = pBaseId->Version;

	UpdateData(FALSE);
}

// Data from dialog control into BASE_ID
//void CAmbPage::SetDataIntoModule(BASE_ID& BaseId, BASE_CFG& BaseCfg) 
void CAmbPage::GetDataFromDlg(PBASE_ID pBaseId) 
{
	UpdateData(TRUE);

	pBaseId->SerNum = m_SerialNum;
	pBaseId->Type = m_BMType;
//	pBaseId->Version = m_Version;
}

// Data from BASE_CFG into dialog control
void CAmbPage::SetDataIntoDlg(PAMBPCI_CFG pBaseCfg)
{
	m_NumOfAdmIf = pBaseCfg->NumOfADM;
//	m_NumOfSdram = pBaseCfg->NumOfCfgDRAM;

	UpdateData(FALSE);
}

// Data from dialog control into BASE_CFG
void CAmbPage::GetDataFromDlg(PAMBPCI_CFG pBaseCfg) 
{
	UpdateData(TRUE);

	pBaseCfg->NumOfADM = m_NumOfAdmIf;
//	pBaseCfg->NumOfCfgDRAM = m_NumOfSdram;
//	pBaseCfg->Reserve = 0;
}
*/
// Data from ICR_IdBase & ICR_CfgAmbpci(ICR_CfgAmbpcm, ICR_CfgAdp101pci) into dialog control
ULONG CAmbPage::SetDataIntoDlg(PVOID pCfgMem)
{
	ULONG ret;
	PICR_IdBase pBaseId = (PICR_IdBase)pCfgMem;
	m_SerialNum = pBaseId->dSerialNum;
	int size = pBaseId->wSizeAll;
	int AmbVersion = pBaseId->bVersion;
	m_strAmbVersion.Format(_T("%x"), AmbVersion);

	m_BMType = 0;
	if(pBaseId->wDeviceId != AMBPCI_CFG_TAG) {
		for(int i = 0; i < m_NumOfBaseModules; i++) {
			PBASEMOD_INFO pDeviceInfo = &(BaseModCtrl[i].devInfo);
			if(pBaseId->wDeviceId == pDeviceInfo->dType) {
				m_BMType = i + 1;
				break;
			}
		}
	}
	PUCHAR pBaseCfg = (PUCHAR)pCfgMem + sizeof(ICR_IdBase);
	ret  = sizeof(ICR_IdBase);

	if(m_BMType) {
		int idx = m_BMType - 1;
		PBASEMOD_INFO pDeviceInfo = &(BaseModCtrl[idx].devInfo);
		memcpy(pDeviceInfo->pCfgMem, pBaseCfg, size);
		int	retCode = (BaseModCtrl[idx].pSetProperty)(pDeviceInfo);
//		m_SerialNum = pDeviceInfo->SerNum;
		m_NumOfAdmIf = pDeviceInfo->bAdmIfCnt;
		ret += pDeviceInfo->dRealCfgSize;
	}
	else
	{
		PICR_CfgAmbpci pAmbpciCfg = (PICR_CfgAmbpci)pBaseCfg;
		m_NumOfAdmIf = pAmbpciCfg->bAdmIfCnt;
		ret += sizeof(ICR_CfgAmbpci);
	}
	UpdateData(FALSE);
	return ret;
}

// Data from dialog control into ICR_IdBase & ICR_CfgAmbpci(ICR_CfgAmbpcm, ICR_CfgAdp101pci)
ULONG CAmbPage::GetDataFromDlg(PVOID pCfgMem)
{
	ULONG ret;
	UpdateData(TRUE);

	PICR_IdBase pBaseId = (PICR_IdBase)pCfgMem;
	pBaseId->wTag = BASE_ID_TAG;
	pBaseId->wSize = sizeof(ICR_IdBase) - 4;
	pBaseId->dSerialNum = m_SerialNum;
	pBaseId->wDeviceId = m_BMType;
	char* stopstring;
	int AmbVersion = strtol(m_strAmbVersion, &stopstring, 16);
	pBaseId->bVersion = AmbVersion;

	SYSTEMTIME today;
	GetLocalTime(&today);
	pBaseId->bDay = (UCHAR)today.wDay;
	pBaseId->bMon = (UCHAR)today.wMonth;
	pBaseId->wYear = today.wYear;

	pCfgMem = (PUCHAR)pCfgMem + sizeof(ICR_IdBase);
	ret = sizeof(ICR_IdBase);

	if(m_BMType) {
		int idx = m_BMType - 1;
		PBASEMOD_INFO pDeviceInfo = &(BaseModCtrl[idx].devInfo);
		pBaseId->wDeviceId = pDeviceInfo->dType;
//		pDeviceInfo->SerNum = m_SerialNum;
		pDeviceInfo->bAdmIfCnt = m_NumOfAdmIf;
		int	retCode = (BaseModCtrl[idx].pGetProperty)(pDeviceInfo);
		if(retCode)
			pDeviceInfo->dRealCfgSize = 0;
		else
			memcpy(pCfgMem, pDeviceInfo->pCfgMem, pDeviceInfo->dRealCfgSize);
		ret += pDeviceInfo->dRealCfgSize;
	}
	else {
		PICR_CfgAmbpci pBaseCfg = (PICR_CfgAmbpci)pCfgMem;
		pBaseCfg->wTag = AMBPCI_CFG_TAG;
		pBaseCfg->wSize = sizeof(ICR_CfgAmbpci) - 4;
		pBaseId->wDeviceId = AMBPCI_CFG_TAG;
		pBaseCfg->bAdmIfCnt = m_NumOfAdmIf;

//		pSignSize = (USHORT*)((PUCHAR)pSignSize + (sizeof(AMBPCI_CFG) + 4));
		ret += sizeof(ICR_CfgAmbpci);
	}
	return ret;
}

BOOL CAmbPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);
	return CPropertyPage::PreTranslateMessage(pMsg);
	// allow sheet to translate Ctrl+Tab, Shift+Ctrl+Tab,
	//  Ctrl+PageUp, and Ctrl+PageDown
/*	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
	   (pMsg->wParam == VK_TAB ||
		pMsg->wParam == VK_PRIOR ||
		pMsg->wParam == VK_NEXT
	   ))
	{
		return CPropertyPage::PreTranslateMessage(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);*/
}
