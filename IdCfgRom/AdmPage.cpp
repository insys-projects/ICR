// AdmPage.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "AdmPage.h"
#include "IdCfgRomDlg.h"
#include ".\admpage.h"

#pragma warning (disable:4996)

#define NONADM_CFGMEM_SIZE 2
#define MAXSUBMODS 256

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma setlocale("Russian_Russia.1251")

static void GetMsg(DWORD dwMessageId, CString& string) 
{
	LPVOID lpMsgBuf;
	HINSTANCE hinst = AfxGetInstanceHandle();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
					AfxGetInstanceHandle(), dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//					AfxGetInstanceHandle(), dwMessageId, MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT),
					(LPTSTR) &lpMsgBuf, 0, NULL );
	string = (LPTSTR)lpMsgBuf;
	LocalFree( lpMsgBuf );
	string.GetBufferSetLength(string.GetLength() - 2);
}

/////////////////////////////////////////////////////////////////////////////
// CAdmPage dialog

IMPLEMENT_DYNAMIC(CAdmPage, CPropertyPage)

CAdmPage::CAdmPage() : CPropertyPage(CAdmPage::IDD)
, m_sComment(_T(""))
{
	//{{AFX_DATA_INIT(CAdmPage)
	m_nAdmNum = 0;
	m_nAdmType = 0;
	m_nAdmPID = 0;
	//}}AFX_DATA_INIT
	for( int ii=0; ii<MAX_ADMID; ii++ )
		m_CommentId[ii].abComment[0] = 0;
}

void CAdmPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdmPage)
	DDX_Text(pDX, IDC_ADMNUM, m_nAdmNum);
	DDX_CBIndex(pDX, IDC_ADMTYPE, m_nAdmType);
	DDX_Text(pDX, IDC_ADMVERSION, m_strAdmVersion);
	DDX_Text(pDX, IDC_ADMPID, m_nAdmPID);
	//}}AFX_DATA_MAP
	DDV_MinMaxUInt(pDX, m_nAdmNum, 0, m_AdmIdMax);
	DDX_Text(pDX, IDC_COMMENT, m_sComment);
}


BEGIN_MESSAGE_MAP(CAdmPage, CPropertyPage)
//	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	//{{AFX_MSG_MAP(CAdmPage)
	ON_EN_KILLFOCUS(IDC_ADMNUM, OnKillfocusAdmnum)
	ON_BN_CLICKED(IDC_ADMCFG, OnAdmcfg)
	ON_EN_KILLFOCUS(IDC_ADMVERSION, OnKillfocusAdmversion)
	ON_EN_KILLFOCUS(IDC_ADMPID, OnKillfocusAdmpid)
	ON_CBN_SELCHANGE(IDC_ADMTYPE, OnSelchangeAdmtype)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
//	ON_WM_ERASEBKGND()
ON_EN_KILLFOCUS(IDC_COMMENT, &CAdmPage::OnEnKillfocusComment)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdmPage message handlers

BOOL CAdmPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ограничение комментария на 15 символов
	CEdit* pComment = (CEdit*)GetDlgItem(IDC_COMMENT);
	pComment->SetLimitText(15);

	CComboBox* pDevType = (CComboBox*)GetDlgItem(IDC_ADMTYPE);
	pDevType->ResetContent();
	CString StringBuf;
	GetMsg(MSG_NON_ADM, StringBuf);
	for(int i = 0; i < g_nNumOfSubModules; i++)
		pDevType->AddString(g_SubmodCtrl[i].devInfo.sName);
	pDevType->InsertString(0, StringBuf);
	pDevType->SetCurSel(0);

	// сортируем субмодули согласно тому, как они помещены в список
	UpdateData(TRUE);
	UpdateData(FALSE);
	SUBMOD_CTRL SubmodCtrlTmp[MAXSUBMODS];
	for( int ii = 0; ii < g_nNumOfSubModules; ii++ )
	{
		int	nIndex = pDevType->FindString(-1, g_SubmodCtrl[ii].devInfo.sName);
		SubmodCtrlTmp[nIndex-1] = g_SubmodCtrl[ii];
	}
	for( int ii = 0; ii < g_nNumOfSubModules ; ii++ )
		g_SubmodCtrl[ii] = SubmodCtrlTmp[ii];

	SetSMTypeData();

    m_ToolTip.Create(this);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADMNUM), IDC_ADMNUM);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADMCFG), IDC_ADMCFG);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADMVERSION), IDC_ADMVERSION);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADMPID), IDC_ADMPID);
    m_ToolTip.AddTool(GetDlgItem(IDC_ADMTYPE), IDC_ADMTYPE);
//    EnableToolTips(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdmPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	for(int i = 0; i < g_nNumOfSubModules; i++) {
		PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[i].devInfo);
		g_SubmodCtrl[i].pClose(pDeviceInfo);
	}
}

void CAdmPage::SetSMTypeData() 
{
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	SetMaxAdm(pParentWnd->m_pAmbPage->m_NumOfAdmIf - 1);

	m_nAdmNum = 0;
	m_nAdmType = 0;
	m_nAdmPID = 0;

	for(int i = 0; i < MAX_ADMID; i++)
	{
		m_AdmId[i].bAdmNum = i;
		m_AdmId[i].dSerialNum = m_nAdmPID;
		m_AdmId[i].wType = m_nAdmType;
		m_AdmId[i].bVersion = 0x10;
	}

	int enFlag = m_nAdmType ? 1 : 0;
	CWnd* pAdmPid = (CWnd*)GetDlgItem(IDC_ADMPID);
	CWnd* pAdmVersion = (CWnd*)GetDlgItem(IDC_ADMVERSION);
	CWnd* pAdmCfg = (CWnd*)GetDlgItem(IDC_ADMCFG);
	pAdmPid->EnableWindow(enFlag);
	pAdmVersion->EnableWindow(enFlag);
	pAdmCfg->EnableWindow(enFlag);
	CWnd* pComment = (CWnd*)GetDlgItem(IDC_COMMENT);
	pComment->EnableWindow(enFlag);
	UpdateData(FALSE); // from variable to window
}
/*
/////////////////////////////////////////////////////////////////////////////
BOOL CAdmPage::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
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
void CAdmPage::OnAdmcfg() 
{
	// TODO: Add your control notification handler code here
	//int idx = m_AdmId[num].Type;
	PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[m_nAdmType-1].devInfo);
	int nResponse = (g_SubmodCtrl[m_nAdmType-1].pDlgProperty)(pDeviceInfo);

	// если в "конфигурации" произошли изменения, уведомляем об этом программу
	if( ((nResponse&0x11) == IDOK) && (nResponse&0x100) )
	{
		CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
		pParentWnd->m_wSubmodFieldsEdited = 1;
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

void CAdmPage::OnKillfocusAdmversion()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	char* stopstring;
	int AdmVersion = strtol(m_strAdmVersion, &stopstring, 16);
	m_AdmId[m_nAdmNum].bVersion = AdmVersion;
//	m_AdmId[m_AdmNum].bVersion = m_AdmVersion;
}

void CAdmPage::OnKillfocusAdmpid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmId[m_nAdmNum].dSerialNum = m_nAdmPID;
}

void CAdmPage::OnSelchangeAdmtype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	m_AdmId[m_nAdmNum].wType = m_nAdmType;
	int enFlag = m_nAdmType ? 1 : 0;
	CWnd* pAdmPid = (CWnd*)GetDlgItem(IDC_ADMPID);
	CWnd* pAdmVersion = (CWnd*)GetDlgItem(IDC_ADMVERSION);
	CWnd* pAdmCfg = (CWnd*)GetDlgItem(IDC_ADMCFG);
	pAdmPid->EnableWindow(enFlag);
	pAdmVersion->EnableWindow(enFlag);
	pAdmCfg->EnableWindow(enFlag);
	CWnd* pComment = (CWnd*)GetDlgItem(IDC_COMMENT);
	pComment->EnableWindow(enFlag);
	m_nCfgBufSize = m_nAdmType ? g_SubmodCtrl[m_nAdmType - 1].devInfo.nCfgMemSize : NONADM_CFGMEM_SIZE;
	
	// Разблокировать галочку "Запись только в субмодуль", если субмодуль есть, и наоборот
	CIdCfgRomDlg* pParentWnd = (CIdCfgRomDlg*)GetOwner();
	if( m_nAdmType == 0 )
		pParentWnd->m_nCanWriteSM = 0;
	else if ( m_nAdmType > 0 )
		pParentWnd->m_nCanWriteSM = 1;
	pParentWnd->UpdateData(FALSE);
}

void CAdmPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pCurrent = GetFocus();
	CWnd* pNum = (CWnd*)GetDlgItem(IDC_ADMNUM);
	if(pCurrent == pNum)
		ChangeAdmNum();
//	CPropertyPage::OnOK();
}

void CAdmPage::OnKillfocusAdmnum() 
{
	// TODO: Add your control notification handler code here
	ChangeAdmNum();
}
/*
void CAdmPage::OnDeltaposSpinadmnum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	int newVal = pNMUpDown->iPos + pNMUpDown->iDelta;
	if(newVal >=0 && newVal <= 3)
	{
		m_AdmNum = newVal;
		UpdateData(FALSE); // from variable to window
		ChangeAdmNum();
	}
	*pResult = 0;
}
*/
void CAdmPage::ChangeAdmNum() 
{
	UpdateData(TRUE); // from window to variable
	int num = m_nAdmNum;

	m_nAdmPID = m_AdmId[num].dSerialNum;
	m_nAdmType = m_AdmId[num].wType;
	int AdmVersion = m_AdmId[num].bVersion;
	m_strAdmVersion.Format(_T("%x"), AdmVersion);
//	m_AdmVersion = m_AdmId[num].bVersion;

	UpdateData(FALSE); // from variable to window
}

void CAdmPage::SetMaxAdm(int maxAdm)
{
	m_AdmIdMax = maxAdm;
	BOOL enFlag = TRUE;
	if(m_AdmIdMax < 0)
		enFlag = FALSE;
	CWnd* pAdmNum = (CWnd*)GetDlgItem(IDC_ADMNUM);
	CWnd* pAdmType = (CWnd*)GetDlgItem(IDC_ADMTYPE);
	CWnd* pAdmPid = (CWnd*)GetDlgItem(IDC_ADMPID);
	CWnd* pAdmVersion = (CWnd*)GetDlgItem(IDC_ADMVERSION);
	CWnd* pAdmCfg = (CWnd*)GetDlgItem(IDC_ADMCFG);
	pAdmNum->EnableWindow(enFlag);
	pAdmType->EnableWindow(enFlag);
	pAdmPid->EnableWindow(enFlag);
	pAdmVersion->EnableWindow(enFlag);
	pAdmCfg->EnableWindow(enFlag);
	CWnd* pComment = (CWnd*)GetDlgItem(IDC_COMMENT);
	pComment->EnableWindow(enFlag);
	if(enFlag) {
		enFlag = m_nAdmType ? 1 : 0;
		pAdmPid->EnableWindow(enFlag);
		pAdmVersion->EnableWindow(enFlag);
		pAdmCfg->EnableWindow(enFlag);
		pComment->EnableWindow(enFlag);
	}
	m_nCfgBufSize = m_nAdmType ? g_SubmodCtrl[m_nAdmType - 1].devInfo.nCfgMemSize : NONADM_CFGMEM_SIZE;
}
/*
// Data from ADM_ID into dialog control
//void CAdmPage::GetDataFromModule(ADM_ID& admId) 
void CAdmPage::SetDataIntoDlg(PADM_ID pAdmId, UINT num)
{
	m_AdmId[num].SerNum = pAdmId->SerNum;
	m_AdmId[num].Version = pAdmId->Version;

	m_AdmId[num].Type = 0;
	if(pAdmId->Type)
		for(int i = 0; i < g_NumOfSubModules; i++)
		{
			PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[i].devInfo);
			if(pAdmId->Type == pDeviceInfo->Type)
				m_AdmId[num].Type = i + 1;
		}
//	m_AdmId[num].Type = pAdmId->Type;

	if(num == m_AdmNum)
	{
		m_AdmPID = m_AdmId[num].SerNum;
		m_AdmVersion = m_AdmId[num].Version;
		m_AdmType = m_AdmId[num].Type;
		UpdateData(FALSE);
	}
}

// Data from dialog control into ADM_ID
//void CAdmPage::SetDataIntoModule(ADM_ID& admId) 
void CAdmPage::GetDataFromDlg(PADM_ID pAdmId, UINT num) 
{
//	if(m_AdmId[num].Type)
//	{
	UpdateData(TRUE);

//		*pSignSize = ADM_ID_SIGN;
//		*(pSignSize+1) = sizeof(ADM_ID);
//		PADM_ID pAdmId = (PADM_ID)((UCHAR*)pSignSize + 4);

	pAdmId->SerNum = m_AdmId[num].SerNum;
	pAdmId->Version = m_AdmId[num].Version;

	if(m_AdmId[num].Type) {
		int idx = m_AdmId[num].Type - 1;
		PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[idx].devInfo);
		pAdmId->Type = pDeviceInfo->Type;
	}
	else
		pAdmId->Type = 0;
//	pAdmId->Type = m_AdmId[num].Type;
//	pAdmId->Reserve = 0;
}

// Data from ADM_CFG into dialog control
ULONG CAdmPage::SetDataIntoDlg(PVOID pAdmCfg, UINT num, UINT size)
{
	ULONG ret;
	if(m_AdmId[num].Type) {
		int idx = m_AdmId[num].Type - 1;
		PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[idx].devInfo);
		size = size < SUBMOD_CFGMEM_SIZE ? size : SUBMOD_CFGMEM_SIZE;
		memcpy(pDeviceInfo->CfgMem, pAdmCfg, size);
		int	retCode = (g_SubmodCtrl[idx].pSetProperty)(pDeviceInfo);
		ret = pDeviceInfo->RealCfgSize;
	}
	else
		ret = 0;
	return ret;
}

// Data from dialog control into ADM_CFG
ULONG CAdmPage::GetDataFromDlg(PVOID pAdmCfg, UINT num)
{
	ULONG ret;
	if(m_AdmId[num].Type) {
		int idx = m_AdmId[num].Type - 1;
		PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[idx].devInfo);
		int	retCode = (g_SubmodCtrl[idx].pGetProperty)(pDeviceInfo);
		if(retCode)
			pDeviceInfo->RealCfgSize = 0;
		else
			memcpy(pAdmCfg, pDeviceInfo->CfgMem, pDeviceInfo->RealCfgSize);
		ret = pDeviceInfo->RealCfgSize;
	}
	else
		ret = 0;
	return ret;
}
*/

// Data from ADM_ID & ADM_CFG into dialog control
ULONG CAdmPage::SetDataIntoDlg(PVOID pCfgMem)
{
	ULONG ret = 0;
	PICR_IdAdm pAdmId = (PICR_IdAdm)pCfgMem;
	UINT num = pAdmId->bAdmNum;
	int size = pAdmId->wSizeAll;
	m_AdmId[num].dSerialNum = pAdmId->dSerialNum;
	m_AdmId[num].bVersion = pAdmId->bVersion;
	m_AdmId[num].wType = 0;
	if(pAdmId->wType)
	{
		for(int i = 0; i < g_nNumOfSubModules; i++)
		{
			PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[i].devInfo);
			if(pAdmId->wType == pDeviceInfo->Type)
			{
				m_AdmId[num].wType = i + 1;
				break;
			}
		}
	}
	if(num == m_nAdmNum)
	{
		m_nAdmPID = m_AdmId[num].dSerialNum;
		int AdmVersion = m_AdmId[num].bVersion;
		m_strAdmVersion.Format(_T("%x"), AdmVersion);
//		m_AdmVersion = m_AdmId[num].bVersion;
		m_nAdmType = m_AdmId[num].wType;
		UpdateData(FALSE);
	}
	ret = sizeof(ICR_IdAdm);
	if(m_AdmId[num].wType)
	{
		int idx = m_AdmId[num].wType - 1;
		PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[idx].devInfo);
		PUCHAR pAdmCfg = (PUCHAR)pCfgMem + sizeof(ICR_IdAdm);
		memcpy(pDeviceInfo->pCfgMem, pAdmCfg, size);
		int	retCode = (g_SubmodCtrl[idx].pSetProperty)(pDeviceInfo);
		ret += pDeviceInfo->nRealCfgSize;
	}

	return ret;
}

ULONG CAdmPage::SetComment(PVOID pCfgMem)
{
	ULONG ret = 0;
	PICR_IdComment pCommentId = (PICR_IdComment)pCfgMem;
	UINT num = pCommentId->bInterfaceNum;
	if( num != 0xFF )
	{
		strcpy((char*)m_CommentId[num].abComment, (char*)pCommentId->abComment);
		if(num == m_nAdmNum)
		{
			m_sComment.SetString((char*)pCommentId->abComment);
			UpdateData(FALSE);
		}
	}
	ret = sizeof(ICR_IdComment);
	return ret;
}

// Data from dialog control into ADM_ID & ADM_CFG
ULONG CAdmPage::GetDataFromDlg(PVOID pCfgMem, UINT num)
{
	ULONG ret;

	if(m_AdmId[num].wType)
	{
		USHORT* pCurCfgMem = (USHORT*)pCfgMem;
		PICR_IdAdm pAdmId = (PICR_IdAdm)pCurCfgMem;
		pAdmId->wTag = ADM_ID_TAG;
		pAdmId->wSize = sizeof(ICR_IdAdm) - 4;
		pAdmId->bAdmNum = num;

		SYSTEMTIME today;
		GetLocalTime(&today);
		pAdmId->bDay = (UCHAR)today.wDay;
		pAdmId->bMon = (UCHAR)today.wMonth;
		pAdmId->wYear = today.wYear;

		UpdateData(TRUE);
		pAdmId->dSerialNum = m_AdmId[num].dSerialNum;
		pAdmId->bVersion = m_AdmId[num].bVersion;
		int idx = m_AdmId[num].wType - 1;
		PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[idx].devInfo);
		pAdmId->wType = pDeviceInfo->Type;
		int	retCode = (g_SubmodCtrl[idx].pGetProperty)(pDeviceInfo);

		PUCHAR pAdmCfg = (PUCHAR)pCfgMem + sizeof(ICR_IdAdm);
		if(retCode)
			pDeviceInfo->nRealCfgSize = 0;
		else
			memcpy(pAdmCfg, pDeviceInfo->pCfgMem, pDeviceInfo->nRealCfgSize);
		ret = pDeviceInfo->nRealCfgSize + sizeof(ICR_IdAdm);

		pCfgMem = (PUCHAR)pCfgMem + sizeof(ICR_IdAdm) + pDeviceInfo->nRealCfgSize;

		// считывание из "Особые отметки"
		PICR_IdComment pCommentId = (PICR_IdComment)pCfgMem;
		pCommentId->wTag = COMMENT_ID_TAG;
		pCommentId->wSize = sizeof(ICR_IdComment) - 4;
		pCommentId->bInterfaceNum = num;
		strcpy((char*)pCommentId->abComment, (char*)m_CommentId[num].abComment);
		ret += sizeof(ICR_IdComment);
	}
	else
		ret = 0;

	return ret;
}

// Data from ADM_ID into dialog control
void CAdmPage::SetIdDataIntoDlg(PICR_IdAdm pAdmId, PICR_IdComment pCommentId)
{
//	ULONG ret;
	UINT num = pAdmId->bAdmNum;
	if(num == m_nAdmNum)
	{
		m_nAdmPID = m_AdmId[num].dSerialNum;
		int AdmVersion = m_AdmId[num].bVersion;
		m_strAdmVersion.Format(_T("%x"), AdmVersion);
//		m_AdmVersion = m_AdmId[num].bVersion;
		m_nAdmType = m_AdmId[num].wType;

		m_sComment.SetString((char*)m_CommentId[num].abComment);
	}

	CWnd* pPid = (CWnd*)GetDlgItem(IDC_ADMPID);
	CWnd* pVer = (CWnd*)GetDlgItem(IDC_ADMVERSION);
	CWnd* pComment = (CWnd*)GetDlgItem(IDC_COMMENT);
	if( m_AdmId[num].wType == 0 )
	{
		pPid->EnableWindow(FALSE);
		pVer->EnableWindow(FALSE);
		pComment->EnableWindow(FALSE);
	}
	else
	{
		pPid->EnableWindow(TRUE);
		pVer->EnableWindow(TRUE);
		pComment->EnableWindow(TRUE);
	}
}

// Data from dialog control into ADM_ID
void CAdmPage::GetIdDataFromDlg(PICR_IdAdm pAdmId, PICR_IdComment pCommentId, UINT num)
{
	pAdmId->wTag = ADM_ID_TAG;
	pAdmId->wSize = sizeof(ICR_IdAdm) - 4;
	pAdmId->bAdmNum = num;

	SYSTEMTIME today;
	GetLocalTime(&today);
	pAdmId->bDay = (UCHAR)today.wDay;
	pAdmId->bMon = (UCHAR)today.wMonth;
	pAdmId->wYear = today.wYear;

	pAdmId->dSerialNum = m_AdmId[num].dSerialNum;
	pAdmId->bVersion = m_AdmId[num].bVersion;
	int idx = m_AdmId[num].wType - 1;
	PSUBMOD_INFO pDeviceInfo = &(g_SubmodCtrl[idx].devInfo);
	pAdmId->wType = pDeviceInfo->Type;

	pCommentId->wTag = COMMENT_ID_TAG;
	pCommentId->wSize = sizeof(ICR_IdComment) - 4;
	pCommentId->bInterfaceNum = m_CommentId[num].bInterfaceNum;
	strcpy((char*)pCommentId->abComment, (char*)m_CommentId[num].abComment);
}

BOOL CAdmPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    m_ToolTip.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}

//BOOL CAdmPage::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	return CPropertyPage::OnEraseBkgnd(pDC);
//}

void CAdmPage::OnEnKillfocusComment()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // from window to variable
	strcpy((char*)m_CommentId[m_nAdmNum].abComment, m_sComment.GetBuffer());
}
