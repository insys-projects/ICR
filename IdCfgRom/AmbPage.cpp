// AmbPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "AmbPage.h"
#include "IdCfgRomDlg.h"
#include ".\ambpage.h"

#define MAXBASEMODS 256

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
, m_sComment(_T(""))
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
	DDV_MinMaxUInt(pDX, m_SerialNum, 1, 999999);
	DDX_Text(pDX, IDC_NUMOFADMIF, m_NumOfAdmIf);
	DDX_Control(pDX, IDC_SPINADMIF, m_ctrlSpinAdmIf);
	DDX_CBIndex(pDX, IDC_BMTYPE, m_BMType);
	DDX_Text(pDX, IDC_AMBVERSION, m_strAmbVersion);
	//	DDX_Text(pDX, IDC_AMBVERSION, m_AmbVersion);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_NumOfAdmIf, 0, MAX_NUMOFADMIF - 1);
	DDX_Text(pDX, IDC_COMMENT, m_sComment);
	DDX_Control(pDX, IDC_BMTYPE, m_ctrlType);
	DDX_Control(pDX, IDC_NUMOFADMIF, m_ctrlAdmNum);
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
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINADMIF, &CAmbPage::OnDeltaposSpinadmif)
	ON_EN_KILLFOCUS(IDC_COMMENT, &CAmbPage::OnEnKillfocusComment)
	ON_EN_CHANGE(IDC_SERIALNUM, &CAmbPage::OnEnChangeSerialnum)
	ON_EN_CHANGE(IDC_AMBVERSION, &CAmbPage::OnEnChangeAmbversion)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmbPage message handlers

BOOL CAmbPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ограничение комментария на 15 символов
	CEdit* pComment = (CEdit*)GetDlgItem(IDC_COMMENT);
	pComment->SetLimitText(15);

	CComboBox* pDevType = (CComboBox*)GetDlgItem(IDC_BMTYPE);
	pDevType->ResetContent();
	for(int i = 0; i < g_nNumOfBaseModules; i++)
		pDevType->AddString(g_BaseModCtrl[i].devInfo.sName);
	pDevType->InsertString(0, _T("AMBPCI"));
	pDevType->SetCurSel(0);

	// сортируем базовые модули согласно тому, как они помещены в список
	UpdateData(TRUE);
	UpdateData(FALSE);
	BASEMOD_CTRL BaseModCtrlTmp[MAXBASEMODS];
	for( int ii = 0; ii < g_nNumOfBaseModules; ii++ )
	{
		int	nIndex = pDevType->FindString(-1, g_BaseModCtrl[ii].devInfo.sName);
		BaseModCtrlTmp[nIndex-1] = g_BaseModCtrl[ii];
	}
	for( int ii = 0; ii < g_nNumOfBaseModules ; ii++ )
		g_BaseModCtrl[ii] = BaseModCtrlTmp[ii];

	m_ctrlSpinAdmIf.SetRange(0, MAX_NUMOFADMIF - 1);
	
	SetBMTypeData();

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
	for(int i = 0; i < g_nNumOfBaseModules; i++) 
	{
		PBASEMOD_INFO pDeviceInfo = &(g_BaseModCtrl[i].devInfo);
		g_BaseModCtrl[i].pClose(pDeviceInfo);
	}
}

// Функция в зависимости от типа выбранного Базового Модуля:
// - устанавливает видимость кнопки "Подробности..."
// - устанавливает заголовок окна
void CAmbPage::SetBMTypeData()
{
	UpdateData(TRUE);
	int enFlag = m_BMType ? 1 : 0;
	CWnd* pAmbExt = (CWnd*)GetDlgItem(IDC_AMBEXT);
	pAmbExt->EnableWindow(enFlag);

	CString sBaseModuleName;
	CComboBox* pType = (CComboBox*)GetDlgItem(IDC_BMTYPE);
	pType->GetLBText(m_BMType, sBaseModuleName);
	CString sTitle;
	sTitle = _T("IdCfgRom (") + sBaseModuleName + _T(")");
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	pParentWnd->SetWindowText(sTitle);
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
	PBASEMOD_INFO pDeviceInfo = &(g_BaseModCtrl[m_BMType-1].devInfo);
	int nResponse = (g_BaseModCtrl[m_BMType-1].pDlgProperty)(pDeviceInfo);

	// если в "подробностях" произошли изменения, уведомляем об этом программу
	if( ((nResponse&0x11) == IDOK) && (nResponse&0x100) )
	{
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		pParentWnd->m_wBasemodFieldsEdited = 1;
		nResponse &=~0x100;
	}
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
	CString str;

	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	SetBMTypeData();

	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	if( pParentWnd->m_pFileBaseDlg )
		pParentWnd->TransferParamsFromMainToFileBaseDlg();

	m_ctrlType.GetLBText(m_ctrlType.GetCurSel(), str);

	if(!str.Compare("VK3"))
	{
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		pParentWnd->m_ctrlReadWriteDevs.SetCurSel(0);
		pParentWnd->m_ctrlReadWriteDevs.EnableWindow(FALSE);
 	}
	else if(!str.Compare("DR-16"))
	{
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		pParentWnd->m_ctrlReadWriteDevs.SetCurSel(0);
		pParentWnd->m_ctrlReadWriteDevs.EnableWindow(FALSE);
	}
	else
	{
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		pParentWnd->m_ctrlReadWriteDevs.EnableWindow(TRUE);
	}

	m_NumOfAdmIf = 1;
	pParentWnd->m_nCanWriteSM = 1;
	m_ctrlAdmNum.EnableWindow(FALSE);

	UpdateData(FALSE);

	UpdateData(TRUE); // from window to variable

	pParentWnd->m_pAdmIfPage->SetMaxAdmIf(m_NumOfAdmIf - 1);
	pParentWnd->m_pAdmPage->SetMaxAdm(m_NumOfAdmIf - 1);
	pParentWnd->m_pPldPage->SetMaxPld(pParentWnd->m_pAdmIfPage->m_NumOfPld - 1);

	if(!str.Compare("DR16"))
	{
		pParentWnd->m_pPldPage->PageEnable(1);
		pParentWnd->m_pAdmIfPage->PageEnable(0);
	}

	if(!str.Compare("VK3"))
	{
		pParentWnd->m_pPldPage->PageEnable(0);
		pParentWnd->m_pAdmIfPage->PageEnable(0);
	}

		
	pParentWnd->m_pFifoPage->SetMaxAdcFifo(pParentWnd->m_pAdmIfPage->m_NumOfAdcFifo - 1);
	pParentWnd->m_pFifoPage->SetMaxDacFifo(pParentWnd->m_pAdmIfPage->m_NumOfDacFifo - 1);
	pParentWnd->m_pDacPage->SetMaxDac(pParentWnd->m_pAdmIfPage->m_NumOfDac - 1);
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
	// установка полей кроме "Подробности..." и "Особые отметки"
	PICR_IdBase pBaseId = (PICR_IdBase)pCfgMem;
	m_SerialNum = pBaseId->dSerialNum;
	int size = pBaseId->wSizeAll;
	int AmbVersion = pBaseId->bVersion;
	m_strAmbVersion.Format(_T("%x"), AmbVersion);

	m_BMType = 0;
	if(pBaseId->wDeviceId != AMBPCI_CFG_TAG)
	{
		for(int i = 0; i < g_nNumOfBaseModules; i++)
		{
			PBASEMOD_INFO pDeviceInfo = &(g_BaseModCtrl[i].devInfo);
			if(pBaseId->wDeviceId == pDeviceInfo->dType)
			{
				m_BMType = i + 1;
				break;
			}
		}
	}
	PUCHAR pBaseCfg = (PUCHAR)pCfgMem + sizeof(ICR_IdBase);
	ret  = sizeof(ICR_IdBase);

	// установка полей в "Подробности..."
	if(m_BMType)
	{
		int idx = m_BMType - 1;
		PBASEMOD_INFO pDeviceInfo = &(g_BaseModCtrl[idx].devInfo);
		memcpy(pDeviceInfo->pCfgMem, pBaseCfg, size);
		int	retCode = (g_BaseModCtrl[idx].pSetProperty)(pDeviceInfo);
//		m_SerialNum = pDeviceInfo->SerNum;
		if( pDeviceInfo->dType == 0x6610 ||  // FMC110PDSP
			pDeviceInfo->dType == 0x6611 ||  // FMC111PDSP
			pDeviceInfo->dType == 0x6612 ||  // FMC112cPDSP
			pDeviceInfo->dType == 0x6614 ||  // FMC114vPDSP
			pDeviceInfo->dType == 0x6615 ||  // PEXSRIO
			pDeviceInfo->dType == 0x6617	 // FMC117cPDSP
			)
			pDeviceInfo->bAdmIfCnt = 0;

		if(pDeviceInfo->dType == 0x5516) // XM416x250M
			pDeviceInfo->bAdmIfCnt = 1;
		if(pDeviceInfo->dType == 0x53B2)	// FMC112cP
			pDeviceInfo->bAdmIfCnt = 2;
		if(pDeviceInfo->dType == 0x53B3 ||	// FMC117cP
			pDeviceInfo->dType == 0x53B5 ||	// FMC121cP
			pDeviceInfo->dType == 0x53B6)	// FMC125cP
			pDeviceInfo->bAdmIfCnt = 1;
		if(pDeviceInfo->dType == 0x551C ||	// FMC122P
			pDeviceInfo->dType == 0x551E)	// FMC124P
			pDeviceInfo->bAdmIfCnt = 1;
		if(pDeviceInfo->dType == 0x3018 ||	// FMC118E
			pDeviceInfo->dType == 0x3019)	// FMC119E
			pDeviceInfo->bAdmIfCnt = 1;
		m_NumOfAdmIf = pDeviceInfo->bAdmIfCnt;
		ret += pDeviceInfo->nRealCfgSize;
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

ULONG CAmbPage::SetComment(PVOID pCfgMem)
{
	ULONG	ret = 0;
	PICR_IdComment pCommentId = (PICR_IdComment)pCfgMem;
	if( pCommentId->bInterfaceNum == 0xFF )
	{
		m_sComment.SetString((char*)pCommentId->abComment);
		UpdateData(FALSE);
	}
	ret = sizeof(ICR_IdComment);
	return ret;
}

// Data from dialog control into ICR_IdBase & ICR_CfgAmbpci(ICR_CfgAmbpcm, ICR_CfgAdp101pci)
ULONG CAmbPage::GetDataFromDlg(PVOID pCfgMem)
{
	ULONG ret;
	UpdateData(TRUE);

	// считывание с вкладки "Base" кроме "Подробности..." и "Особые отметки"
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

	// считывание из "Подробности..."
	if(m_BMType)
	{
		int idx = m_BMType - 1;
		PBASEMOD_INFO pDeviceInfo = &(g_BaseModCtrl[idx].devInfo);
		pBaseId->wDeviceId = pDeviceInfo->dType;
//		pDeviceInfo->SerNum = m_SerialNum;
		pDeviceInfo->bAdmIfCnt = m_NumOfAdmIf;
		int	retCode = (g_BaseModCtrl[idx].pGetProperty)(pDeviceInfo);
		if(retCode)
			pDeviceInfo->nRealCfgSize = 0;
		else
			memcpy(pCfgMem, pDeviceInfo->pCfgMem, pDeviceInfo->nRealCfgSize);
		ret += pDeviceInfo->nRealCfgSize;

		pCfgMem = (PUCHAR)pCfgMem + pDeviceInfo->nRealCfgSize;
	}
	else
	{
		PICR_CfgAmbpci pBaseCfg = (PICR_CfgAmbpci)pCfgMem;
		pBaseCfg->wTag = AMBPCI_CFG_TAG;
		pBaseCfg->wSize = sizeof(ICR_CfgAmbpci) - 4;
		pBaseId->wDeviceId = AMBPCI_CFG_TAG;
		pBaseCfg->bAdmIfCnt = m_NumOfAdmIf;

//		pSignSize = (USHORT*)((PUCHAR)pSignSize + (sizeof(AMBPCI_CFG) + 4));
		ret += sizeof(ICR_CfgAmbpci);
		
		pCfgMem = (PUCHAR)pCfgMem + sizeof(ICR_CfgAmbpci);
	}

	// считывание из "Особые отметки"
	PICR_IdComment pCommentId = (PICR_IdComment)pCfgMem;
	pCommentId->wTag = COMMENT_ID_TAG;
	pCommentId->wSize = sizeof(ICR_IdComment) - 4;
	pCommentId->bInterfaceNum = 0xFF;
	strcpy((char*)pCommentId->abComment, m_sComment);
	ret += sizeof(ICR_IdComment);

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

void CAmbPage::OnDeltaposSpinadmif(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;

	// Разблокировать галочку "Запись только в субмодуль", если субмодуль есть, и наоборот
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	if( newVal == 0 || pParentWnd->m_pAdmPage->m_nAdmType == 0 )
		pParentWnd->m_nCanWriteSM = 0;
	else if ( newVal > 0 && pParentWnd->m_pAdmPage->m_nAdmType > 0 )
		pParentWnd->m_nCanWriteSM = 1;
	pParentWnd->UpdateData(FALSE);
	UpdateData(FALSE);

	*pResult = 0;
}

void CAmbPage::OnEnKillfocusComment()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
}

void CAmbPage::OnEnChangeSerialnum()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	if( pParentWnd->m_pFileBaseDlg )
		pParentWnd->TransferParamsFromMainToFileBaseDlg();
}

void CAmbPage::OnEnChangeAmbversion()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	if( pParentWnd->m_pFileBaseDlg )
		pParentWnd->TransferParamsFromMainToFileBaseDlg();
}
