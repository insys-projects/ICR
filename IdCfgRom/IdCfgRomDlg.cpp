// IdCfgRomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "IdCfgRomDlg.h"

#pragma warning (disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma setlocale("Russian_Russia.1251")

HICON g_hIcon;

static void GetMsg(DWORD dwMessageId, CString& string) 
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
					AfxGetInstanceHandle(), dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR) &lpMsgBuf, 0, NULL );
	string = (LPTSTR)lpMsgBuf;
	LocalFree( lpMsgBuf );
	string.GetBufferSetLength(string.GetLength() - 2);
}

static void GetMsg(DWORD dwMessageId, LPTSTR strMsg) 
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
					AfxGetInstanceHandle(), dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR) &lpMsgBuf, 0, NULL );
	lstrcpy(strMsg, (LPTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );
	strMsg[lstrlen(strMsg) - 2] = '\0';
}

//=********************** LL_hexGetByte ****************
//=*****************************************************
static S32 LL_hexGetByte( char **ppLine, U32 *pByte )
{
	U32		symb1, symb2;

	symb1 = toupper(*(*ppLine)++);
	//(*ppLine)++;
	symb1 = (symb1>='0' && symb1<='9') ? symb1-'0' :
			(symb1>='A' && symb1<='F') ? symb1-'A'+10 : 0xFE;

	symb2 = toupper(*(*ppLine)++);
	symb2 = (symb2>='0' && symb2<='9') ? symb2-'0' :
			(symb2>='A' && symb2<='F') ? symb2-'A'+10 : 0xFE;

	if( pByte!=NULL )
		*pByte = symb1*16 + symb2;

	return (symb1==0xFE||symb2==0xFE) ? -1 : 0;
}

// CIdCfgRomDlg dialog

CIdCfgRomDlg::CIdCfgRomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIdCfgRomDlg::IDD, pParent)
{
	m_nDevType = 0;
	g_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME1);
	m_wDialogFieldsEdited = 0;
	m_wBasemodFieldsEdited = 0;
	m_wSubmodFieldsEdited = 0;
	m_pFileBaseDlg = NULL;
}

void CIdCfgRomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABPAGE, m_ctrlTab);
	DDX_CBIndex(pDX, IDC_DEVICETYPE, m_nDevType);
	DDX_Control(pDX, IDC_READ_WRITE_DEV, m_ctrlReadWriteDevs);
}

BEGIN_MESSAGE_MAP(CIdCfgRomDlg, CDialog)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ABOUT, OnBnClickedAbout)
	ON_BN_CLICKED(IDC_INTODEV, OnBnClickedIntodev)
	ON_BN_CLICKED(IDC_FROMDEV, OnBnClickedFromdev)
	ON_BN_CLICKED(IDOK, &CIdCfgRomDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_WRITE_READ, &CIdCfgRomDlg::OnBnClickedWriteRead)
	ON_BN_CLICKED(IDC_CLEAR, &CIdCfgRomDlg::OnBnClickedClear)
//	ON_WM_LBUTTONDOWN()
ON_WM_ACTIVATE()
ON_CBN_SELCHANGE(IDC_READ_WRITE_DEV, &CIdCfgRomDlg::OnCbnSelchangeReadWriteDev)
END_MESSAGE_MAP()


// CIdCfgRomDlg message handlers

BOOL CIdCfgRomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(g_hIcon, TRUE);			// Set big icon
	SetIcon(g_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_pAboutDlg = new CAbout;

	m_pAmbPage = new CAmbPage; 
	VERIFY(m_pAmbPage->Create(CAmbPage::IDD, this));
	m_ctrlTab.AddTab(m_pAmbPage, _T("Base"));
	m_pAdmIfPage = new CAdm2IfPage; 
	VERIFY(m_pAdmIfPage->Create(CAdm2IfPage::IDD, this));
	m_ctrlTab.AddTab(m_pAdmIfPage, _T("Adm-I/f"));
		m_pPldPage = new CPldPage; 
	VERIFY(m_pPldPage->Create(CPldPage::IDD, this));
	m_ctrlTab.AddTab(m_pPldPage, _T("PLD"));
	m_pFifoPage = new CFifoPage; 
	VERIFY(m_pFifoPage->Create(CFifoPage::IDD, this));
	m_ctrlTab.AddTab(m_pFifoPage, _T("FIFO"));
	m_pDacPage = new CDacPage; 
	VERIFY(m_pDacPage->Create(CDacPage::IDD, this));
	m_ctrlTab.AddTab(m_pDacPage, _T("DAC"));
	m_pAdmPage = new CAdmPage; 
	VERIFY(m_pAdmPage->Create(CAdmPage::IDD, this));
	m_ctrlTab.AddTab(m_pAdmPage, _T("ADM"));

	m_ctrlReadWriteDevs.AddString("������� ������");
	m_ctrlReadWriteDevs.AddString("���������");
	m_ctrlReadWriteDevs.AddString("������� ������ � ���������");
	DWORD nReg;
	if( ReadRegistryValue("Software\\Instrumental Systems\\IdCfgRom", "ReadWriteDevs", &nReg) == ERROR_SUCCESS )
		m_ctrlReadWriteDevs.SetCurSel(nReg);
	else
		m_ctrlReadWriteDevs.SetCurSel(0);
	
	m_nCanWriteSM = 0;

	CComboBox* pDevType = (CComboBox*)GetDlgItem(IDC_DEVICETYPE);
	pDevType->ResetContent();
	if( g_nNumOfDevices )
	{
		for(int i = 0; i < g_nNumOfDevices; i++)
		{
			CString strDevName;
			PDEVICE_INFO pInfo = &(g_DeviceCtrl[i].devInfo);
			strDevName = pInfo->sName;
			TCHAR strRev[10];
			sprintf_s(strRev, _T(" V%d.%d"), pInfo->bVersion >> 4, pInfo->bVersion & 0x0f);
			strDevName += strRev;
			TCHAR strLoc[40];
			if(pInfo->wSlotNum == 0xffff)
				sprintf_s(strLoc, _T(" (Bus %d, Device %d)"), pInfo->wBusNum, pInfo->wDevNum);
			else
				sprintf_s(strLoc, _T(" (Bus %d, Device %d, Slot %d)"), pInfo->wBusNum, pInfo->wDevNum, pInfo->wSlotNum);
			strDevName += strLoc;
			pDevType->AddString(strDevName);
		}
		pDevType->SetCurSel(0);
	}
	else
	{
		pDevType->EnableWindow(FALSE);
		CWnd* pFromDevBtn = (CWnd*)GetDlgItem(IDC_FROMDEV);
		pFromDevBtn->EnableWindow(FALSE);
		CWnd* pIntoDevBtn = (CWnd*)GetDlgItem(IDC_INTODEV);
		pIntoDevBtn->EnableWindow(FALSE);
		CWnd* pClearBtn = (CWnd*)GetDlgItem(IDC_CLEAR);
		pClearBtn->EnableWindow(FALSE);
		m_ctrlReadWriteDevs.EnableWindow(FALSE);
	}

	CWnd* pOk = (CWnd*)GetDlgItem(IDOK);
	GotoDlgCtrl(pOk);
    EnableToolTips(TRUE);

	SaveDialogFieldsValues();

	return FALSE;  // return TRUE  unless you set the focus to a control
}

int	CIdCfgRomDlg::GetReadWriteDevs()
{
	CString sDev;
	m_ctrlReadWriteDevs.GetLBText(m_ctrlReadWriteDevs.GetCurSel(), sDev);
	if( sDev == "������� ������" )
		return READ_WRITE_BASEMODULE;
	if( sDev == "���������" )
		return READ_WRITE_SUBMODULE;
	if( sDev == "������� ������ � ���������" )
		return READ_WRITE_ALL;

	return -1;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIdCfgRomDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, g_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIdCfgRomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(g_hIcon);
}

BOOL CIdCfgRomDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB && GetKeyState(VK_CONTROL) < 0)
	{
		int nTab = m_ctrlTab.GetCurSel();
		int cntTab = m_ctrlTab.GetItemCount();
		if(GetKeyState(VK_SHIFT) < 0)
		{
			if(nTab - 1 < 0)
				m_ctrlTab.SelectTab(cntTab - 1);
			else
				m_ctrlTab.SelectTab(nTab - 1);
		}
		else
		{
			if(nTab + 1 < cntTab)
				m_ctrlTab.SelectTab(nTab + 1);
			else
				m_ctrlTab.SelectTab(0);
		}
		return true;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIdCfgRomDlg::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT_PTR nID = pNMHDR->idFrom;
    if(pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
//        if(nID != IDC_START && nID != IDC_HL_WWW && nID != IDC_HL_Email)
        if(nID != IDC_TABPAGE)
        {
            pTTT->lpszText = MAKEINTRESOURCE(nID);
//            strcpy(pTTT->szText, "1234567890");
            pTTT->hinst = AfxGetResourceHandle();
            return(TRUE);
        }
    }
    return(FALSE);
}

void CIdCfgRomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CheckEditOfStructOfDialogFieldsValues();
	// ���� ���� ��������, ������������� ������������ ����� �������
	if( m_wDialogFieldsEdited || m_wBasemodFieldsEdited || m_wSubmodFieldsEdited )
	{
		if(MessageBox( "��������� ���� ��������!\n�� ������������� ������ �����?", _T("IdCfgRom"), MB_YESNO|MB_ICONWARNING) != IDYES)
			return;
	}

	OnOK();
}

void CIdCfgRomDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pCurrent = GetFocus();
	CWnd* pOk = (CWnd*)GetDlgItem(IDOK);
	if( pCurrent == pOk )
		CDialog::OnOK();
	else
	{
		m_pAmbPage->OnOK();
		m_pAdmIfPage->OnOK();
		m_pPldPage->OnOK();
		m_pFifoPage->OnOK();
		m_pDacPage->OnOK();
		m_pAdmPage->OnOK();
	}
}

void CIdCfgRomDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	CheckEditOfStructOfDialogFieldsValues();
	// ���� ���� ��������, ������������� ������������ ����� �������
	if( m_wDialogFieldsEdited || m_wBasemodFieldsEdited || m_wSubmodFieldsEdited )
	{
		if( MessageBox( "��������� ���� ��������!\n�� ������������� ������ �����?", _T("IdCfgRom"), MB_YESNO|MB_ICONWARNING) != IDYES)
			return;
	}

	CDialog::OnCancel();
}

void CIdCfgRomDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	for(int i = 0; i < g_nNumOfDevices; i++)
	{
		PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[i].devInfo);
		g_DeviceCtrl[i].pClose(pDeviceInfo);
	}

	delete m_pAboutDlg;

	m_pAmbPage->DestroyWindow();
	m_pAdmIfPage->DestroyWindow();
	m_pPldPage->DestroyWindow();
	m_pFifoPage->DestroyWindow();
	m_pDacPage->DestroyWindow();
	m_pAdmPage->DestroyWindow();

	delete m_pAmbPage;
	delete m_pAdmIfPage;
	delete m_pPldPage;
	delete m_pFifoPage;
	delete m_pDacPage;
	delete m_pAdmPage;

	if( m_pFileBaseDlg )
		delete m_pFileBaseDlg;
}

void CIdCfgRomDlg::OnBnClickedAbout()
{
	// TODO: Add your control notification handler code here
	INT_PTR nResponse = m_pAboutDlg->DoModal();
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

static void ParseFileNameExt(CString& fileName)
{
	int nPos, prevPos = 0;
	while(1) {
		nPos = fileName.ReverseFind('.');
		if(nPos != -1) {
			fileName.SetAt(nPos, 0);
			prevPos = nPos;
		}
		else
			break;
	}
	fileName.SetAt(prevPos, '.');
}

// ��������� "���������� ��������" ���������� �� ������
// ����� ���������� � ���� �� ����� ��� ����������
//***************************************************************************************
void CIdCfgRomDlg::CfgMemToDlgItems(PUCHAR pCfgMem, ULONG nSizeCfgMem)
{
	PVOID	pCfgMemTmp;											// ��������� �� ������ �����

	if ( m_readFileExt == ".hex" )								// ����������� ������ ���� HEX � ������ ���� BIN
	{
		m_readFileExt = "";
		char	*binStr = new char[nSizeCfgMem/2];				// ��������� ������ ������ hex �����
		U32		realSizeOfHexCfgMem = 0;
		char	*pCfgMemHex = (char*)pCfgMem; 					// ��������� �� ������ HEX �����
		U32		hexByte;
		U08		bytesInHexString;
		U08		writeTypeInHexString;
		for(;;)													// �������� �� �������
		{
			if(	*pCfgMemHex == ':' )							// ����������� ���
			{
				pCfgMemHex++;									// ������������� ':'
				LL_hexGetByte(&pCfgMemHex, &hexByte);
				bytesInHexString = hexByte;
				pCfgMemHex += 4;								// ������������� �����
				LL_hexGetByte(&pCfgMemHex, &hexByte);
				writeTypeInHexString = hexByte;
				if( writeTypeInHexString == 0x04 )				// ������ ������
				{
					pCfgMemHex += 8;							// ������������� ��������� ������
					continue;									// � ������������ � ��������� ������
				}
				else if( writeTypeInHexString == 0x00 )			// ������ ������
				{
					for( U08 ii = 0; ii<bytesInHexString; ii++ )// �������� �� ������ ������
					{
						LL_hexGetByte(&pCfgMemHex, &hexByte);
						char	strTmp[2];
						strcpy(strTmp, (char*)&hexByte);
						memcpy(binStr + realSizeOfHexCfgMem + ii , strTmp, 1);
					}
					realSizeOfHexCfgMem += bytesInHexString;	// ������������ ���������� ��������� ���� ������ � HEX �����
					pCfgMemHex += 4;							// ������������� �������
					continue;									// � ������������ � ��������� ������
				}
				else if( writeTypeInHexString == 0x01 )			// ��������� ������
					break;										// ����������� ������ � ������
			}
			pCfgMemHex++;										// ���� ������ ������ �� ':'
		}
		pCfgMemTmp = (PVOID)binStr;								// ��������� ���������� ������ �� ���������� 
		nSizeCfgMem = realSizeOfHexCfgMem;						// �������������� HEX � BIN
		memcpy(pCfgMem, binStr, nSizeCfgMem);
		delete [] binStr;
	}

	pCfgMemTmp = (PVOID)pCfgMem;
	PVOID pEndCfgMem = (PVOID)((PUCHAR)pCfgMemTmp + nSizeCfgMem);
	int nRealBaseCfgSize = 0;
	if( (GetReadWriteDevs() == READ_WRITE_BASEMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
	{
		m_pAmbPage->m_sComment = "";

		int end_flag = 0;
		do
		{
			USHORT sign;
			sign = *((USHORT*)pCfgMemTmp);

			USHORT size = 0;
			switch(sign)
			{
			case END_TAG:
			case ALT_END_TAG:
				end_flag = 1;
				break;
			case BASE_ID_TAG:
				{
					nRealBaseCfgSize = *((USHORT*)pCfgMemTmp + 2);
					size = (USHORT)m_pAmbPage->SetDataIntoDlg(pCfgMemTmp);
					break;
				}
			case COMMENT_ID_TAG:
				{
					size = (USHORT)m_pAmbPage->SetComment(pCfgMemTmp);
					break;
				}
			case ADM2IF_CFG_TAG:
				{
					m_pAdmIfPage->SetDataIntoDlg((PICR_CfgAdm2If)pCfgMemTmp);
					size = sizeof(ICR_CfgAdm2If);
					break;
				}
			case ADC_FIFO_TAG:
				{
					m_pFifoPage->SetDataIntoDlg((PICR_CfgAdcFifo)pCfgMemTmp);
					size = sizeof(ICR_CfgAdcFifo);
					break;
				}
			case DAC_CFG_TAG:
				{
					m_pDacPage->SetDataIntoDlg((PICR_CfgDac)pCfgMemTmp);
					size = sizeof(ICR_CfgDac);
					break;
				}
			case DAC_FIFO_TAG:
				{
					m_pFifoPage->SetDataIntoDlg((PICR_CfgDacFifo)pCfgMemTmp);
					size = sizeof(ICR_CfgDacFifo);
					break;
				}
			case PLD_CFG_TAG:
				{
					m_pPldPage->SetDataIntoDlg((PICR_CfgAdmPld)pCfgMemTmp);
					size = sizeof(ICR_CfgAdmPld);
					break;
				}
			default:
					size = *((USHORT*)pCfgMemTmp + 1);
					size += 4;
					break;
			}
			pCfgMemTmp = (PUCHAR)pCfgMemTmp + size;
		} while(!end_flag && pCfgMemTmp < pEndCfgMem);

		m_pAdmIfPage->SetMaxAdmIf(m_pAmbPage->m_NumOfAdmIf - 1);
		m_pAdmPage->SetMaxAdm(m_pAmbPage->m_NumOfAdmIf - 1);
		m_pPldPage->SetMaxPld(m_pAdmIfPage->m_NumOfPld - 1);
		m_pFifoPage->SetMaxAdcFifo(m_pAdmIfPage->m_NumOfAdcFifo - 1);
		m_pFifoPage->SetMaxDacFifo(m_pAdmIfPage->m_NumOfDacFifo - 1);
		m_pDacPage->SetMaxDac(m_pAdmIfPage->m_NumOfDac - 1);

		m_pAmbPage->SetBMTypeData();
	}
	else
		nRealBaseCfgSize = GetBMCfgSizeIfExist(pCfgMemTmp, pEndCfgMem);

	if( (GetReadWriteDevs() == READ_WRITE_SUBMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
	{
		m_pAdmPage->m_sComment = "";

		pCfgMemTmp = (PVOID)(pCfgMem + nRealBaseCfgSize);
		int end_flag = 0;
		do
		{
			USHORT sign = *((USHORT*)pCfgMemTmp);
			USHORT size = 0;
			switch(sign)
			{
			case END_TAG:
			case ALT_END_TAG:
				end_flag = 1;
				break;
			case ADM_ID_TAG:
				{
					size = (USHORT)m_pAdmPage->SetDataIntoDlg(pCfgMemTmp);
					break;
				}
			case COMMENT_ID_TAG:
				{
					size = (USHORT)m_pAdmPage->SetComment(pCfgMemTmp);
					break;
				}
			default:
					size = *((USHORT*)pCfgMemTmp + 1);
					size += 4;
					break;
			}
			pCfgMemTmp = (PUCHAR)pCfgMemTmp + size;
		} while(!end_flag && pCfgMemTmp < pEndCfgMem);

		m_pAdmPage->SetSMTypeData();
	}

	m_pAmbPage->UpdateData(TRUE);
	if( m_pAmbPage->m_NumOfAdmIf == 0 )
		m_nCanWriteSM = 0;
	else if ( m_pAmbPage->m_NumOfAdmIf > 0 )
	{
		m_pAdmPage->UpdateData(TRUE);
		if( m_pAdmPage->m_nAdmType == 0 )
			m_nCanWriteSM = 0;
		else if ( m_pAdmPage->m_nAdmType > 0 )
			m_nCanWriteSM = 1;
	}
	UpdateData(FALSE);
}

int CIdCfgRomDlg::GetBMCfgSizeIfExist(void *pCfgMem, void *pEndCfgMem)
{
	int nEndFlag = 0;
	int nRealBaseCfgSize = 0;
	do
	{
		USHORT sign;
		sign = *((USHORT*)pCfgMem);

		USHORT size = 0;
		switch(sign)
		{
		case END_TAG:
		case ALT_END_TAG:
			nEndFlag = 1;
			break;
		case BASE_ID_TAG:
			nRealBaseCfgSize = *((USHORT*)pCfgMem + 2);
			nEndFlag = 1;
			break;
		default:
			size = *((USHORT*)pCfgMem + 1);
			size += 4;
			break;
		}
		pCfgMem = (PUCHAR)pCfgMem + size;
	} while(!nEndFlag && pCfgMem < pEndCfgMem);

	return nRealBaseCfgSize;
}

void CIdCfgRomDlg::ReadThroughDialog()
{
	// TODO: Add your control notification handler code here
	CString sFilePath = ShowReadDialog();
	if( sFilePath == "" )
		return;
	
	ReadCfgFile(sFilePath);
}

CString CIdCfgRomDlg::ShowReadDialog()
{
	CString strFilter;
	GetMsg(MSG_FILE_FILTER_BIN_AND_HEX, strFilter);
	CFileDialog readFileDlg(TRUE, _T(".bin;.hex"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

	// ���������� ���������� ��� �������� ����� ������ �� ������ � �������
	CHAR regDir[MAX_PATH];
	CRegKey key;
	LONG status = key.Open(HKEY_CURRENT_USER, "Software\\Instrumental Systems\\IdCfgRom");
	if (status == ERROR_SUCCESS)
	{
		DWORD regDirSize = sizeof(regDir);
		key.QueryValue(regDir, "Load/Save Directory", &regDirSize);
		if( strcmp(regDir, "") == 0 )
			status++;
		else
			readFileDlg.m_ofn.lpstrInitialDir = regDir;
	}
	// ���� ������� �� ������� �� �������, ��������� ����������, ��� �������� .exe ���� (��������� �� ��������� ������)
	if( status != ERROR_SUCCESS )
	{
		LPTSTR cmdLine = GetCommandLine() + 1;
		LPTSTR ShortFileName = strrchr(cmdLine, '\\') + 1;
		*ShortFileName = 0;
		strcat(cmdLine, "Config");
		readFileDlg.m_ofn.lpstrInitialDir = cmdLine;
		CreateDirectory(cmdLine, NULL);
	}
	
	// ������������� ��������� ���� �������� �����
	CString strTitle;
	GetMsg(MSG_READ_FILE_CAPTION, strTitle);
	readFileDlg.m_ofn.lpstrTitle = strTitle.GetBuffer(80);

	INT_PTR nID = readFileDlg.DoModal();
	if(nID != IDOK)
		return "";
	CString fileName = readFileDlg.GetPathName();

	// ���������� � ������ ���� � ���������� ���������� �����
	strcpy(regDir, fileName.GetBuffer());
	LPTSTR editorOfDir = strrchr(regDir, '\\') + 1;
	*editorOfDir = 0;
	key.Create(HKEY_CURRENT_USER, "Software\\Instrumental Systems\\IdCfgRom");
	key.SetValue(regDir, "Load/Save Directory");
	key.Close();

	return fileName;
}

void CIdCfgRomDlg::ReadCfgFile(CString sFilePath)
{
	m_readFileExt = sFilePath.Right(4);
	HANDLE hfile = CreateFile(	sFilePath, 
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hfile == INVALID_HANDLE_VALUE)
	{
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
						NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPTSTR) &lpMsgBuf, 0, NULL );
		AfxMessageBox( (const char *)lpMsgBuf, MB_OK|MB_ICONINFORMATION, 0);
		LocalFree( lpMsgBuf );
		return;
	}

	long lDistanceToMoveLow = 0;
	long lDistanceToMoveHigh = 0;
	ULONG bFileSize = SetFilePointer(hfile, lDistanceToMoveLow, &lDistanceToMoveHigh, FILE_END);
	SetFilePointer(hfile, 0, &lDistanceToMoveHigh, FILE_BEGIN);
	DWORD dwBytesRead;
	PUCHAR	pCfgMem = new UCHAR[bFileSize];
	ReadFile(hfile, pCfgMem, bFileSize, &dwBytesRead, NULL);
	ULONG nSizeCfgMem = dwBytesRead;

	CfgMemToDlgItems(pCfgMem, nSizeCfgMem);
	delete [] pCfgMem;

	CloseHandle(hfile);

	if( m_pFileBaseDlg )
		TransferParamsFromMainToFileBaseDlg();

	SaveDialogFieldsValues();
}

// ��������� ����� ���������� �� "���������� ��������"
// ����� ������� ��� � ���� ��� ����������
ULONG CIdCfgRomDlg::DlgItemsToCfgMem(PUCHAR	pCfgMem, ULONG nSizeCfgMem, int *pRealBaseCfgSize, int aRealAdmCfgSize[4])
{
	USHORT* pEndCfgMem = (USHORT*)pCfgMem + nSizeCfgMem/2;
	USHORT* pCurCfgMem = (USHORT*)pCfgMem;

	// �������� AmbPage
	ULONG nCfgSize = m_pAmbPage->GetDataFromDlg(pCurCfgMem);
	pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + nCfgSize);
	if( pCurCfgMem >= pEndCfgMem )
		return -1;

	int numOfADM = m_pAmbPage->m_NumOfAdmIf;
	if( numOfADM>0 )
	{
		for(int i = 0; i < numOfADM; i++)
		{
			// �������� Adm2If
			m_pAdmIfPage->GetDataFromDlg((PICR_CfgAdm2If)pCurCfgMem, i);
			int numOfADCFIFO = ((PICR_CfgAdm2If)pCurCfgMem)->bAdcFifoCnt;
			int numOfDAC = ((PICR_CfgAdm2If)pCurCfgMem)->bDacCnt;
			int numOfDACFIFO = ((PICR_CfgAdm2If)pCurCfgMem)->bDacFifoCnt;
			int numOfPld = ((PICR_CfgAdm2If)pCurCfgMem)->bPldCnt;
			pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdm2If));
			if(pCurCfgMem >= pEndCfgMem)
				return -1;

			if( numOfADCFIFO )
			{
				for(int idx = 0; idx < numOfADCFIFO; idx++)
				{
					// �������� FifoPage
					m_pFifoPage->GetDataFromDlg((PICR_CfgAdcFifo)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdcFifo));
					if(pCurCfgMem >= pEndCfgMem)
						return -1;
				}
			}

			if( numOfDAC )
			{
				for(int idx = 0; idx < numOfDAC; idx++)
				{
					// �������� DacPage
					m_pDacPage->GetDataFromDlg((PICR_CfgDac)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDac));
					if(pCurCfgMem >= pEndCfgMem)
						return -1;
				}
			}

			if( numOfDACFIFO )
			{
				for(int idx = 0; idx < numOfDACFIFO; idx++)
				{
					// �������� FifoPage
					m_pFifoPage->GetDataFromDlg((PICR_CfgDacFifo)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDacFifo));
					if(pCurCfgMem >= pEndCfgMem)
						return -1;
				}
			}

			if(numOfPld)
			{
				for(int idx = 0; idx < numOfPld; idx++)
				{
					// �������� PldPage
					m_pPldPage->GetDataFromDlg((PICR_CfgAdmPld)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdmPld));
					if(pCurCfgMem >= pEndCfgMem)
						return -1;
				}
			}
		}
	}
	*pCurCfgMem = END_TAG;
	pCurCfgMem++;
	*pRealBaseCfgSize = ULONG((PUCHAR)pCurCfgMem - pCfgMem);
	USHORT* pSizeAll = (USHORT*)pCfgMem;
	pSizeAll[2] = *pRealBaseCfgSize;

	if( numOfADM )
	{
		for(int i = 0; i < numOfADM; i++)
		{
			PUCHAR pAdmCfgMem = (PUCHAR)pCurCfgMem;
			m_pAdmPage->UpdateData(TRUE);
			ULONG nAdmCfgBufSize = m_pAdmPage->m_nAdmType ? g_SubmodCtrl[m_pAdmPage->m_nAdmType - 1].devInfo.nCfgMemSize : NONADM_CFGMEM_SIZE;
			USHORT* pEndCfgMem = (USHORT*)pCurCfgMem + nAdmCfgBufSize;
			// �������� AdmPage
			ULONG nCfgSize = m_pAdmPage->GetDataFromDlg(pCurCfgMem, i);
			pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + nCfgSize);
			if(pCurCfgMem >= pEndCfgMem)
				return -1;
			aRealAdmCfgSize[i] = ULONG((PUCHAR)pCurCfgMem - pAdmCfgMem);
			USHORT* pSizeAll = (USHORT*)pAdmCfgMem;
			pSizeAll[2] = aRealAdmCfgSize[i];
		}
	}
	for(int i = numOfADM; i < 4; i++)
		aRealAdmCfgSize[i] = 0;

	return 1;
}

void CIdCfgRomDlg::SaveBinThroughtDialog()
{
	// TODO: Add your control notification handler code here
	CString sFilePath = ShowSaveDialog(SAVE_BIN);
	
	if( sFilePath.Compare("") != 0 )
		SaveBin(sFilePath);
}

void CIdCfgRomDlg::SaveHexThroughtDialog()
{
	// TODO: Add your control notification handler code here
	CString sFileName = ShowSaveDialog(SAVE_HEX);
	
	if( sFileName.Compare("") != 0 )
		SaveHex(sFileName);
}

CString CIdCfgRomDlg::ShowSaveDialog(int nSaveType)
{
	CString strFilter;
	CString sDefExt = "";
	if( nSaveType == SAVE_BIN )
	{
		GetMsg(MSG_FILE_FILTER, strFilter);
		sDefExt	= ".bin";
	}
	else if( nSaveType == SAVE_HEX )
	{
		GetMsg(MSG_FILE_FILTER_HEX, strFilter);
		sDefExt	= ".hex";
	}
	CFileDialog saveFileDlg(FALSE, sDefExt, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

	// ���������� ���������� ��� ���������� ����� ������ �� ������ � �������
	CHAR regDir[MAX_PATH];
	CRegKey key;
	LONG status = key.Open(HKEY_CURRENT_USER, "Software\\Instrumental Systems\\IdCfgRom");
	if (status == ERROR_SUCCESS)
	{
		DWORD regDirSize = sizeof(regDir);
		key.QueryValue(regDir, "Load/Save Directory", &regDirSize);
		saveFileDlg.m_ofn.lpstrInitialDir = regDir;
	}
	// ���� ������� �� ������� �� �������, ��������� ����������, ��� �������� .exe ���� (��������� �� ��������� ������)
	else
	{
		LPTSTR cmdLine = GetCommandLine() + 1;
		LPTSTR ShortFileName = strrchr(cmdLine, '\\') + 1;
		*ShortFileName = 0;
		strcat(cmdLine, "Config");
		saveFileDlg.m_ofn.lpstrInitialDir = cmdLine;
		CreateDirectory(cmdLine, NULL);
	}

	// ������������� ��������� ���� ���������� �����
	CString strTitle;
	GetMsg(MSG_SAVE_FILE_CAPTION, strTitle);
	saveFileDlg.m_ofn.lpstrTitle = strTitle.GetBuffer(80);

	INT_PTR nID = saveFileDlg.DoModal();
	if(nID != IDOK)
		return "";
	CString fileName = saveFileDlg.GetPathName();
	ParseFileNameExt(fileName);

	// ���������� � ������ ���� � ���������� ����������� �����
	strcpy(regDir, fileName.GetBuffer());
	LPTSTR editorOfDir = strrchr(regDir, '\\') + 1;
	*editorOfDir = 0;
	key.Create(HKEY_CURRENT_USER, "Software\\Instrumental Systems\\IdCfgRom");
		key.SetValue(regDir, "Load/Save Directory");
	key.Close();

	return fileName;
}

void CIdCfgRomDlg::SaveBin(CString sFilePath)
{
	HANDLE hfile = CreateFile(	sFilePath, 
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if(hfile == INVALID_HANDLE_VALUE) {
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
						NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPTSTR) &lpMsgBuf, 0, NULL );
		AfxMessageBox( (const char *)lpMsgBuf, MB_OK|MB_ICONINFORMATION, 0);
		LocalFree( lpMsgBuf );
		return;
	}

	m_pAmbPage->UpdateData(TRUE);
	m_pAdmPage->UpdateData(TRUE);
	ULONG nAmbCfgBufSize = m_pAmbPage->m_BMType ? g_BaseModCtrl[m_pAmbPage->m_BMType - 1].devInfo.nCfgMemSize : AMBPCI_CFGMEM_SIZE;
	ULONG nAdmCfgBufSize = m_pAdmPage->m_nAdmType ? g_SubmodCtrl[m_pAdmPage->m_nAdmType - 1].devInfo.nCfgMemSize : NONADM_CFGMEM_SIZE;
	ULONG nSizeCfgMem = nAmbCfgBufSize + nAdmCfgBufSize;
	PUCHAR	pCfgMem = new UCHAR[nSizeCfgMem];

	int nRealBaseCfgSize = 0;
	int aRealAdmCfgSize[4] = {0, 0, 0, 0};
	if( DlgItemsToCfgMem(pCfgMem, nSizeCfgMem, &nRealBaseCfgSize, aRealAdmCfgSize) ) 
	{
		// ������� ������
		if( (GetReadWriteDevs() == READ_WRITE_BASEMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
		{
			DWORD dwBytesWritten;
			WriteFile(hfile, pCfgMem, nRealBaseCfgSize, &dwBytesWritten, NULL);
		}

		// ���������
		if( (GetReadWriteDevs() == READ_WRITE_SUBMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
		{
			PUCHAR pCurCfgMem = pCfgMem + nRealBaseCfgSize;
			for(int i = 0; i < 4; i++) 
			{
				if(aRealAdmCfgSize[i]) 
				{
					DWORD dwBytesWritten;
					WriteFile(hfile, pCurCfgMem, aRealAdmCfgSize[i], &dwBytesWritten, NULL);
					pCurCfgMem += aRealAdmCfgSize[i];
				}
			}
		}
	}
	else 
	{
		CString MsgBuf;
		GetMsg(MSG_NOT_ENOUGH_MEMORY, MsgBuf);
		AfxMessageBox( MsgBuf, MB_OK|MB_ICONINFORMATION, 0);
		return;
	}
	delete[] pCfgMem;

	CloseHandle(hfile);

	SaveDialogFieldsValues();
}

void CIdCfgRomDlg::SaveHex(CString sFilePath)
{
	FILE	*fout = fopen( sFilePath, "wt" );
	if( fout==NULL )
		fout = stdout;

	m_pAmbPage->UpdateData(TRUE);
	m_pAdmPage->UpdateData(TRUE);
	ULONG nAmbCfgBufSize = m_pAmbPage->m_BMType ? g_BaseModCtrl[m_pAmbPage->m_BMType - 1].devInfo.nCfgMemSize : AMBPCI_CFGMEM_SIZE;
	ULONG nAdmCfgBufSize = m_pAdmPage->m_nAdmType ? g_SubmodCtrl[m_pAdmPage->m_nAdmType - 1].devInfo.nCfgMemSize : NONADM_CFGMEM_SIZE;
	ULONG nSizeCfgMem = nAmbCfgBufSize + nAdmCfgBufSize;
	PUCHAR	pCfgMem = new UCHAR[nSizeCfgMem];

	int nRealBaseCfgSize = 0;
	int aRealAdmCfgSize[4] = {0, 0, 0, 0};
	if( DlgItemsToCfgMem(pCfgMem, nSizeCfgMem, &nRealBaseCfgSize, aRealAdmCfgSize) )
	{
		// ������� ������
		if( (GetReadWriteDevs() == READ_WRITE_BASEMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
		{
			// ������ ������������ �������� ������
			U08 *hex = (U08*)pCfgMem;									// ���� ������ ��� ������ � ����
			U16	hiAddress = 0x0000;										// ������� ����� ������ (������ ������)
			U16	loAddress = 0x0000;										// ������� ����� ������ (������ ������)
			U08	controlSum;												// ����������� �����
				controlSum = 0x0 - ( 0x02 + ((hiAddress&0xFF00)>>8) + (hiAddress&0x00FF) + 0x04);
			fprintf(fout, ":02000004%04X%02X\n", hiAddress, controlSum);// ������ ��������� ������
			char	str[141] = "";
			char	strTmp[140] = "";
			// "for": ����� ����� ������
			for( int ii=0; ii<(nRealBaseCfgSize+1); ii++ )
			{
				// "if": ������ �������� ����� ������ � �������� ��������� ������ ������
				if( !(ii%64) || (ii == nRealBaseCfgSize) )				//��������� ���� � ������ ��� ��������� ���� ������
				{
					// "if": ������ ��������
					if( ii!=0 ) // �� ������ ������ ������ ������
					{
						controlSum = 0x40 + ( (loAddress&0xFF00)>>8 ) + (loAddress&0x00FF);
						int bytesCntInStr = ii%64 ? ii%64 : 64;			// ������ ���������� ������ � ������ ��� ������
						for( int jj=0; jj<bytesCntInStr; jj++)
							controlSum += hex[ii-1-jj];
						controlSum = 0x0 - controlSum;
						sprintf_s(strTmp, ("%02X\n"), controlSum);
						strcat(str, strTmp);
						// "if": ����� ��������� ������ ������
						if( ii == nRealBaseCfgSize )
						{
							sprintf_s(strTmp, (":%02X"), bytesCntInStr);
							strncpy(str, strTmp, 3);
							fprintf(fout, str);							// ����� �������������� ������ ������ � ����
							str[0] = 0;
							break;
						}
						loAddress+=64;
					}
					fprintf(fout, str); // ����� � ���� �������������� ������ ������
					str[0] = 0;
					// ������ ��������
					sprintf_s(strTmp, (":40%04X00"), loAddress);
					strcat(str, strTmp);
				}
				sprintf_s(strTmp, ("%02X"), hex[ii]);					// ������ ����� ������
				strcat(str, strTmp);
			}
		}

		// ���������
		if( (GetReadWriteDevs() == READ_WRITE_SUBMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
		{
			U16	loAddress = 0x0000;
			char	str[141] = "";
			char	strTmp[140] = "";
			// ������ ������������ ����������
			PUCHAR pCurCfgMem = pCfgMem + nRealBaseCfgSize;
			for(int i = 0; i < 4; i++)
			{
				if(aRealAdmCfgSize[i])
				{
					U08 *hex = (U08*)pCurCfgMem;
					for( int ii=0; ii<(aRealAdmCfgSize[i]+1); ii++ )
					{
						if( !(ii%64) || (ii == aRealAdmCfgSize[i]) )
						{
							if( ii!=0 )
							{
								U08	controlSum = 0x40 + ( (loAddress&0xFF00)>>8 ) + (loAddress&0x00FF);
								int bytesCntInStr = ii%64 ? ii%64 : 64;
								for( int jj=0; jj<bytesCntInStr; jj++)
									controlSum += hex[ii-1-jj];
								controlSum = 0x0 - controlSum;
								
								sprintf_s(strTmp, ("%02X\n"), controlSum);
								strcat(str, strTmp);
								if( ii == aRealAdmCfgSize[i] )
								{
									sprintf_s(strTmp, (":%02X"), bytesCntInStr);
									strncpy(str, strTmp, 3);
									fprintf(fout, str);
									str[0] = 0;
									break;
								}
								loAddress+=64;
							}
							fprintf(fout, str);
							str[0] = 0;
							sprintf_s(strTmp, (":40%04X00"), loAddress);
							strcat(str, strTmp);
						}
						sprintf_s(strTmp, ("%02X"), hex[ii]);
						strcat(str, strTmp);
					}
					pCurCfgMem += aRealAdmCfgSize[i];
				}
			}
		}
		fprintf(fout, ":00000001FF");
	}
	else
	{
		CString MsgBuf;
		GetMsg(MSG_NOT_ENOUGH_MEMORY, MsgBuf);
		AfxMessageBox( MsgBuf, MB_OK|MB_ICONINFORMATION, 0);
		return;
	}
	delete[] pCfgMem;
	fclose(fout);

	SaveDialogFieldsValues();
}

void CIdCfgRomDlg::OnBnClickedIntodev()
{
	// TODO: Add your control notification handler code here
	// ���� � ���� ��� ���������� � ���������, ��������� ������ "������ � ���������"
	if( (GetReadWriteDevs()==READ_WRITE_SUBMODULE) && !m_nCanWriteSM )
	{
		AfxMessageBox("�� ������� ���������������� ������ ��� ���������!");
		return;
	}

	// ��������� �����
	m_pAmbPage->UpdateData(TRUE);
	m_pAdmPage->UpdateData(TRUE);
	ULONG nAmbCfgBufSize = m_pAmbPage->m_BMType ? g_BaseModCtrl[m_pAmbPage->m_BMType - 1].devInfo.nCfgMemSize : AMBPCI_CFGMEM_SIZE;
	ULONG nAdmCfgBufSize = m_pAdmPage->m_nAdmType ? g_SubmodCtrl[m_pAdmPage->m_nAdmType - 1].devInfo.nCfgMemSize : NONADM_CFGMEM_SIZE;
	ULONG nSizeCfgMem = nAmbCfgBufSize + nAdmCfgBufSize;
	PUCHAR	pCfgMem = new UCHAR[nSizeCfgMem];

	// ���������� ���������� ������ ICR ����������� �� ����� ����
	int nRealBaseCfgSize = 0;
	int aRealAdmCfgSize[4] = {0, 0, 0, 0};
	if( DlgItemsToCfgMem(pCfgMem, nSizeCfgMem, &nRealBaseCfgSize, aRealAdmCfgSize) )
	{
		UpdateData(TRUE);
		PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[m_nDevType].devInfo);

		// ���������� ������� � pDeviceInfo ��������� �������
		// ����� �������� ������
		pDeviceInfo->nRealBaseCfgSize = nRealBaseCfgSize;
		memcpy(pDeviceInfo->pBaseCfgMem, pCfgMem, nRealBaseCfgSize);

		// ������ ����������
		PUCHAR pCurCfgMem = pCfgMem + nRealBaseCfgSize;
		for( int i = 0; i < 4; i++ )
		{
			pDeviceInfo->nRealAdmCfgSize[i] = aRealAdmCfgSize[i];
			if( aRealAdmCfgSize[i] && pDeviceInfo->pAdmCfgMem[i] )
			{
				memcpy(pDeviceInfo->pAdmCfgMem[i], pCurCfgMem, aRealAdmCfgSize[i]);
				pCurCfgMem += aRealAdmCfgSize[i];
			}
		}

		CString MsgBuf, MsgBuf0, MsgBuf1;
		GetMsg(MSG_WARN_REWRITE_DATA, MsgBuf0);
		GetMsg(MSG_CONTINUE, MsgBuf1);
		MsgBuf = MsgBuf0 + _T("\n") + MsgBuf1;
		if(MessageBox( MsgBuf, _T("IdCfgRom"), MB_YESNO|MB_ICONWARNING) == IDYES)
		{
			HCURSOR  hCursorWait = LoadCursor(NULL, IDC_WAIT); // ������-����
			HCURSOR  hCursorArrow = SetCursor(hCursorWait);

			DEVICE_INFO DeviceInfoVerify;// = g_DeviceCtrl[m_nDevType].devInfo;
			CopyDeviceInfoDataAndClearBuffers(&DeviceInfoVerify, g_DeviceCtrl[m_nDevType].devInfo);
			(g_DeviceCtrl[m_nDevType].pWriteIdCfgRom)(pDeviceInfo, GetReadWriteDevs());

			// ����������� ���� ���������� � ���������
			(g_DeviceCtrl[m_nDevType].pReadIdCfgRom)(&DeviceInfoVerify, GetReadWriteDevs());
			VerifyEquiv(*pDeviceInfo, DeviceInfoVerify);
			DeleteDeviceInfoData(DeviceInfoVerify);

			SaveDialogFieldsValues();

			SetCursor(hCursorArrow);
		}
	}
	else
	{
		CString MsgBuf;
		GetMsg(MSG_NOT_ENOUGH_MEMORY, MsgBuf);
		AfxMessageBox(MsgBuf, MB_OK|MB_ICONINFORMATION);
	}

	delete[] pCfgMem;
}

void CIdCfgRomDlg::CopyDeviceInfoDataAndClearBuffers(DEVICE_INFO *pDeviceInfoTo, DEVICE_INFO DeviceInfoFrom)
{
	*(pDeviceInfoTo) = DeviceInfoFrom;

	// ������ � ������� ������ �������� ������
	{
		pDeviceInfoTo->pBaseCfgMem = new UCHAR[BASEMOD_CFGMEM_SIZE];

		for( int jj=0; jj<BASEMOD_CFGMEM_SIZE; jj++ )
		{
			pDeviceInfoTo->pBaseCfgMem[jj] = 0xFF;
		}
	}

	// ������ � ������� ������ ���������
	{
		pDeviceInfoTo->pAdmCfgMem[0] = new UCHAR[SUBMOD_CFGMEM_SIZE];

		for( int jj=0; jj<SUBMOD_CFGMEM_SIZE; jj++ )
		{
			pDeviceInfoTo->pAdmCfgMem[0][jj] = 0xFF;
		}
	}
}

void CIdCfgRomDlg::VerifyEquiv(DEVICE_INFO DeviceInfoWrite, DEVICE_INFO DeviceInfoRead)
{
	int nBaseErrByteNum = -1;
	int nSubErrByteNum = -1;
	int nBaseSizeCorrect = 0;
	int nSubSizeCorrect = 0;
	int nDevs = GetReadWriteDevs();

	// ������������ ������ �������� ������
	if( (nDevs == READ_WRITE_BASEMODULE) || (nDevs == READ_WRITE_ALL) )
	{
		int nSize = DeviceInfoWrite.nRealBaseCfgSize;
		int nSize2 = DeviceInfoRead.nRealBaseCfgSize;

		if( nSize == nSize2 )
		{
			nBaseSizeCorrect = 1;

			for( int jj=0; jj<nSize; jj++ )
			{
				if( DeviceInfoWrite.pBaseCfgMem[jj] != DeviceInfoRead.pBaseCfgMem[jj] )
				{
					nBaseErrByteNum = jj;
					break;
				}
			}
		}
		else
			nBaseErrByteNum = 0;
	}

	// ������������ ������ ���������
	if( (nDevs == READ_WRITE_SUBMODULE) || (nDevs == READ_WRITE_ALL) )
	{
		int nSize = DeviceInfoWrite.nRealAdmCfgSize[0];
		int nSize2 = DeviceInfoRead.nRealAdmCfgSize[0];

		if( nSize == nSize2 )
		{
			int nSubSizeCorrect = 1;

			for( int ii=0; ii<nSize; ii++ )
			{
				if( DeviceInfoWrite.pAdmCfgMem[0][ii] != DeviceInfoRead.pAdmCfgMem[0][ii] )
				{
					nSubErrByteNum = ii;
					break;
				}
			}
		}
		else
		{
			nSubErrByteNum = 0;
		}
	}

	ShowEquivMessage(nBaseErrByteNum, nSubErrByteNum, nBaseSizeCorrect, nSubSizeCorrect);
}

void CIdCfgRomDlg::DeleteDeviceInfoData(DEVICE_INFO DeviceInfoDelete)
{
	// ������� ������ �������� ������
	{
		delete [] DeviceInfoDelete.pBaseCfgMem;
	}

	// ������� ������ ���������
	{
		delete [] DeviceInfoDelete.pAdmCfgMem[0];
	}
}

void CIdCfgRomDlg::ShowEquivMessage(int nBaseErrByteNum, int nSubErrByteNum, int nBaseSizeCorrect, int nSubSizeCorrect)
{
	CString sMessage = "";
	int nErr = 0;

	int nDevs = GetReadWriteDevs();

	if( (nDevs == READ_WRITE_BASEMODULE) || (nDevs == READ_WRITE_ALL) )
	{
		CString sBaseMsg = "������� ������: ";

		if( nBaseErrByteNum != -1 )
		{
			CString sErr;
			sErr.Format("������ ������! ������������� ����: %d", nBaseErrByteNum);
			sBaseMsg += sErr;

			if( nBaseSizeCorrect == 0 )
			{
				sBaseMsg += ". ������� �� ���������!";
			}

			nErr = 1;
		}
		else
		{
			sBaseMsg += "�������� ������!";
		}

		sMessage += sBaseMsg;
	}

	if( (nDevs == READ_WRITE_SUBMODULE) || (nDevs == READ_WRITE_ALL) )
	{
		CString sSubMsg = "���������: ";

		if( nSubErrByteNum != -1 )
		{
			CString sErr;
			sErr.Format("������ ������! ������������� ����: %d", nSubErrByteNum);
			sSubMsg += sErr;

			if( nSubSizeCorrect == 0 )
			{
				sSubMsg += ". ������� �� ���������!";
			}

			nErr = 1;
		}
		else
		{
			sSubMsg += "�������� ������!";
		}

		sMessage += "\n" + sSubMsg;
	}

	if( nErr == 0 )
	{
		MessageBox(sMessage, "IdCfgRom", MB_OK|MB_ICONINFORMATION);
	}
	else if( nErr == 1 )
	{

		MessageBox(sMessage, "IdCfgRom", MB_OK|MB_ICONERROR);
	}
}

void CIdCfgRomDlg::OnBnClickedFromdev()
{
	// TODO: Add your control notification handler code here
	HCURSOR  hCursorWait	= LoadCursor(NULL, IDC_WAIT); // ������-����
	HCURSOR  hCursorArrow	= SetCursor(hCursorWait);

	UpdateData(TRUE);
	PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[m_nDevType].devInfo);
	(g_DeviceCtrl[m_nDevType].pReadIdCfgRom)(pDeviceInfo, GetReadWriteDevs());

	if( (pDeviceInfo->nRealBaseCfgSize==0) && (GetReadWriteDevs()==READ_WRITE_BASEMODULE) )
	{
		AfxMessageBox("ICR �������� ������ ����!");

		SetCursor(hCursorArrow);
		return;
	}
	if( (pDeviceInfo->nRealAdmCfgSize[0]==0) && /*(pDeviceInfo->nRealAdmCfgSize[1]==0) && 
		(pDeviceInfo->nRealAdmCfgSize[2]==0) && (pDeviceInfo->nRealAdmCfgSize[3]==0) &&*/
		(GetReadWriteDevs()==READ_WRITE_SUBMODULE) )
	{
		AfxMessageBox("ICR ��������� ����!");

		SetCursor(hCursorArrow);
		return;
	}
	if( ((pDeviceInfo->nRealBaseCfgSize==0) || (pDeviceInfo->nRealAdmCfgSize[0]==0)) && 
		/*(pDeviceInfo->nRealAdmCfgSize[1]==0) && (pDeviceInfo->nRealAdmCfgSize[2]==0) && 
		(pDeviceInfo->nRealAdmCfgSize[3]==0) &&*/	(GetReadWriteDevs()==READ_WRITE_ALL) )
	{
		if( (pDeviceInfo->nRealBaseCfgSize==0) && (pDeviceInfo->nRealAdmCfgSize[0]!=0) )
		{
			AfxMessageBox("ICR �������� ������ ����!\nICR ��������� ������ �������!");
		}
		else if( (pDeviceInfo->nRealBaseCfgSize!=0) && (pDeviceInfo->nRealAdmCfgSize[0]==0) )
		{
			AfxMessageBox("ICR �������� ������ ������ �������!\nICR ��������� ����!");
		}
		else if( (pDeviceInfo->nRealBaseCfgSize==0) && (pDeviceInfo->nRealAdmCfgSize[0]==0) )
		{
			AfxMessageBox("ICR �������� ������ � ��������� �����!");

			SetCursor(hCursorArrow);
			return;
		}
	}

	// ��������� �����
	ULONG nSizeCfgMem = pDeviceInfo->nBaseCfgMemSize;
	for(int i = 0; i < 4; i++)
		nSizeCfgMem += pDeviceInfo->nAdmCfgMemSize[i];
	PUCHAR	pCfgMem = new UCHAR[nSizeCfgMem];

	// ��������� ���������� ������
	for( ULONG ii=0; ii<nSizeCfgMem; ii++ )
		pCfgMem[ii]=0xFF;

	// ���������� ���������� ������ �������� �� pDeviceInfo
	// ������ �������� ������ �� pDeviceInfo
	memcpy(pCfgMem, pDeviceInfo->pBaseCfgMem, pDeviceInfo->nBaseCfgMemSize);
	PUCHAR pCurCfgMem = pCfgMem + pDeviceInfo->nRealBaseCfgSize;

	// ������ ���������� �� pDeviceInfo
	int aRealAdmCfgSize = 0;
	for( int i = 0; i < 4; i++ )
	{
		if( pDeviceInfo->pAdmCfgMem[i] && pDeviceInfo->nAdmCfgMemSize[i] )
		{
			memcpy(pCurCfgMem, pDeviceInfo->pAdmCfgMem[i], pDeviceInfo->nAdmCfgMemSize[i]);
			pCurCfgMem += pDeviceInfo->nRealAdmCfgSize[i];
		}
	}

	// ��������� ���� ���� ICR ����������� �� ���������� ������
	CfgMemToDlgItems(pCfgMem, nSizeCfgMem);
	delete[] pCfgMem;

	SaveDialogFieldsValues();

	if( m_pFileBaseDlg )
		TransferParamsFromMainToFileBaseDlg();

	SetCursor(hCursorArrow);
}

// ���������� �������� ���������� �����
void CIdCfgRomDlg::SaveDialogFieldsValues()
{
	m_rDialogFieldsValues.AmbSerialNum = m_pAmbPage->m_SerialNum;
	m_rDialogFieldsValues.AmbBMType = m_pAmbPage->m_BMType;
	m_rDialogFieldsValues.AmbstrAmbVersion = m_pAmbPage->m_strAmbVersion;
	m_rDialogFieldsValues.AmbNumOfAdmIf = m_pAmbPage->m_NumOfAdmIf;
	m_rDialogFieldsValues.Adm2IfAdmIfNum = m_pAdmIfPage->m_AdmIfNum;
	m_rDialogFieldsValues.Adm2IfAdmIfType = m_pAdmIfPage->m_AdmIfType;
	m_rDialogFieldsValues.Adm2IfNumOfPld = m_pAdmIfPage->m_NumOfPld;
	m_rDialogFieldsValues.Adm2IfNumOfDac = m_pAdmIfPage->m_NumOfDac;
	m_rDialogFieldsValues.Adm2IfNumOfAdcFifo = m_pAdmIfPage->m_NumOfAdcFifo;
	m_rDialogFieldsValues.Adm2IfNumOfDacFifo = m_pAdmIfPage->m_NumOfDacFifo;
	m_rDialogFieldsValues.Adm2IfGen1 = m_pAdmIfPage->m_Gen1;
	m_rDialogFieldsValues.Adm2IfGen2 = m_pAdmIfPage->m_Gen2;
	m_rDialogFieldsValues.Adm2IfPio = m_pAdmIfPage->m_Pio;
	m_rDialogFieldsValues.Adm2IfPioType = m_pAdmIfPage->m_PioType;
	m_rDialogFieldsValues.Adm2IfRefVoltPvs = m_pAdmIfPage->m_RefVoltPvs;
	m_rDialogFieldsValues.Adm2IfStart = m_pAdmIfPage->m_Start;
	m_rDialogFieldsValues.PldPldNum = m_pPldPage->m_PldNum;
	m_rDialogFieldsValues.PldPldType = m_pPldPage->m_ctrlPldType.GetCurSel();
	m_rDialogFieldsValues.PldPldRate = m_pPldPage->m_ctrlPldRate.GetCurSel();
	m_rDialogFieldsValues.PldPldVolume = m_pPldPage->m_PldVolume;
	m_rDialogFieldsValues.PldPldPins = m_pPldPage->m_PldPins;
	m_rDialogFieldsValues.FifoAdcFifoNum = m_pFifoPage->m_AdcFifoNum;
	m_rDialogFieldsValues.FifoAdcFifoSize = m_pFifoPage->m_AdcFifoSize;
	m_rDialogFieldsValues.FifoAdcFifoBitsWidth = m_pFifoPage->m_AdcFifoBitsWidth;
	m_rDialogFieldsValues.FifoDacFifoNum = m_pFifoPage->m_DacFifoNum;
	m_rDialogFieldsValues.FifoDacFifoSize = m_pFifoPage->m_DacFifoSize;
	m_rDialogFieldsValues.FifoDacFifoBitsWidth = m_pFifoPage->m_DacFifoBitsWidth;
	m_rDialogFieldsValues.FifoDacFifoCycling = m_pFifoPage->m_DacFifoCycling;
	m_rDialogFieldsValues.DacDacNum = m_pDacPage->m_DacNum;
	m_rDialogFieldsValues.DacDacBits = m_pDacPage->m_DacBits;
	m_rDialogFieldsValues.DacDacRateMin = m_pDacPage->m_DacRateMin;
	m_rDialogFieldsValues.DacDacRateMax = m_pDacPage->m_DacRateMax;
	m_rDialogFieldsValues.DacDacRangeAF = m_pDacPage->m_DacRangeAF;
	m_rDialogFieldsValues.DacDacRangePF = m_pDacPage->m_DacRangePF;
	m_rDialogFieldsValues.DacDacLPFCoff = m_pDacPage->m_DacLPFCoff;
	m_rDialogFieldsValues.DacDacHPFCoff = m_pDacPage->m_DacHPFCoff;
	m_rDialogFieldsValues.DacDacAFCoff = m_pDacPage->m_DacAFCoff;
	m_rDialogFieldsValues.DacDacEncoding = m_pDacPage->m_DacEncoding;
	m_rDialogFieldsValues.AdmAdmPID = m_pAdmPage->m_nAdmPID;
	m_rDialogFieldsValues.AdmAdmType = m_pAdmPage->m_nAdmType;
	m_rDialogFieldsValues.AdmstrAdmVersion = m_pAdmPage->m_strAdmVersion;

	m_wDialogFieldsEdited = 0;
	m_wBasemodFieldsEdited = 0;
	m_wSubmodFieldsEdited = 0;
}

void CIdCfgRomDlg::CheckEditOfStructOfDialogFieldsValues()
{
	// ���������, ���������� �� ���������� ����
	m_pAmbPage->UpdateData(TRUE);
	m_pAdmIfPage->UpdateData(TRUE);
	m_pPldPage->UpdateData(TRUE);
	m_pFifoPage->UpdateData(TRUE);
	m_pDacPage->UpdateData(TRUE);
	m_pAdmPage->UpdateData(TRUE);
	if( 
		m_rDialogFieldsValues.AmbSerialNum != m_pAmbPage->m_SerialNum ||
		m_rDialogFieldsValues.AmbBMType != m_pAmbPage->m_BMType ||
		m_rDialogFieldsValues.AmbstrAmbVersion != m_pAmbPage->m_strAmbVersion ||
		m_rDialogFieldsValues.AmbNumOfAdmIf != m_pAmbPage->m_NumOfAdmIf ||
		m_rDialogFieldsValues.Adm2IfAdmIfNum != m_pAdmIfPage->m_AdmIfNum ||
		m_rDialogFieldsValues.Adm2IfAdmIfType != m_pAdmIfPage->m_AdmIfType ||
		m_rDialogFieldsValues.Adm2IfNumOfPld != m_pAdmIfPage->m_NumOfPld ||
		m_rDialogFieldsValues.Adm2IfNumOfDac != m_pAdmIfPage->m_NumOfDac ||
		m_rDialogFieldsValues.Adm2IfNumOfAdcFifo != m_pAdmIfPage->m_NumOfAdcFifo ||
		m_rDialogFieldsValues.Adm2IfNumOfDacFifo != m_pAdmIfPage->m_NumOfDacFifo ||
		m_rDialogFieldsValues.Adm2IfGen1 != m_pAdmIfPage->m_Gen1 ||
		m_rDialogFieldsValues.Adm2IfGen2 != m_pAdmIfPage->m_Gen2 ||
		m_rDialogFieldsValues.Adm2IfPio != m_pAdmIfPage->m_Pio ||
		m_rDialogFieldsValues.Adm2IfPioType != m_pAdmIfPage->m_PioType ||
		m_rDialogFieldsValues.Adm2IfRefVoltPvs != m_pAdmIfPage->m_RefVoltPvs ||
		m_rDialogFieldsValues.Adm2IfStart != m_pAdmIfPage->m_Start ||
		m_rDialogFieldsValues.PldPldNum != m_pPldPage->m_PldNum ||
		m_rDialogFieldsValues.PldPldType != m_pPldPage->m_ctrlPldType.GetCurSel() ||
		m_rDialogFieldsValues.PldPldRate != m_pPldPage->m_ctrlPldRate.GetCurSel() ||
		m_rDialogFieldsValues.PldPldVolume != m_pPldPage->m_PldVolume ||
		m_rDialogFieldsValues.PldPldPins != m_pPldPage->m_PldPins ||
		m_rDialogFieldsValues.FifoAdcFifoNum != m_pFifoPage->m_AdcFifoNum ||
		m_rDialogFieldsValues.FifoAdcFifoSize != m_pFifoPage->m_AdcFifoSize ||
		m_rDialogFieldsValues.FifoAdcFifoBitsWidth != m_pFifoPage->m_AdcFifoBitsWidth ||
		m_rDialogFieldsValues.FifoDacFifoNum != m_pFifoPage->m_DacFifoNum ||
		m_rDialogFieldsValues.FifoDacFifoSize != m_pFifoPage->m_DacFifoSize ||
		m_rDialogFieldsValues.FifoDacFifoBitsWidth != m_pFifoPage->m_DacFifoBitsWidth ||
		m_rDialogFieldsValues.FifoDacFifoCycling != m_pFifoPage->m_DacFifoCycling ||
		m_rDialogFieldsValues.DacDacNum != m_pDacPage->m_DacNum ||
		m_rDialogFieldsValues.DacDacBits != m_pDacPage->m_DacBits ||
		m_rDialogFieldsValues.DacDacRateMin != m_pDacPage->m_DacRateMin ||
		m_rDialogFieldsValues.DacDacRateMax != m_pDacPage->m_DacRateMax ||
		m_rDialogFieldsValues.DacDacRangeAF != m_pDacPage->m_DacRangeAF ||
		m_rDialogFieldsValues.DacDacRangePF != m_pDacPage->m_DacRangePF ||
		m_rDialogFieldsValues.DacDacLPFCoff != m_pDacPage->m_DacLPFCoff ||
		m_rDialogFieldsValues.DacDacHPFCoff != m_pDacPage->m_DacHPFCoff ||
		m_rDialogFieldsValues.DacDacAFCoff != m_pDacPage->m_DacAFCoff ||
		m_rDialogFieldsValues.DacDacEncoding != m_pDacPage->m_DacEncoding ||
		m_rDialogFieldsValues.AdmAdmPID != m_pAdmPage->m_nAdmPID ||
		m_rDialogFieldsValues.AdmAdmType != m_pAdmPage->m_nAdmType ||
		m_rDialogFieldsValues.AdmstrAdmVersion != m_pAdmPage->m_strAdmVersion
	)
		m_wDialogFieldsEdited = 1;
	else
		m_wDialogFieldsEdited = 0;
}

void CIdCfgRomDlg::OnBnClickedWriteRead()
{
	// TODO: Add your control notification handler code here
	if( m_pFileBaseDlg )
	{
		if( !m_pFileBaseDlg->IsWindowVisible() )
			m_pFileBaseDlg->ShowWindow(SW_SHOW);
		m_pFileBaseDlg->BringWindowToTop();
	}
	else
	{
		m_pFileBaseDlg = new CWriteReadDlg();
		//m_pFileBaseDlg->Create(IDD_WRITE_READ_DIALOG, this);
		//m_pFileBaseDlg->Create(IDD_WRITE_READ_DIALOG, NULL);
		m_pFileBaseDlg->m_poIdCfgRomWindow = this;
		m_pFileBaseDlg->Create(IDD_WRITE_READ_DIALOG, CWnd::GetDesktopWindow());
		m_pFileBaseDlg->ShowWindow(SW_SHOW);
	}

	TransferParamsFromMainToFileBaseDlg();
}

void CIdCfgRomDlg::TransferParamsFromMainToFileBaseDlg()
{
	m_pFileBaseDlg->UpdateData(TRUE);
	UpdateData(TRUE);

	// ������� ������
	CString sBMType = "";
	int nBMDevId = -1;
	int nBMVer = -1;
	int nBMPId = -1;
	if( (GetReadWriteDevs() == READ_WRITE_BASEMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
	{
		// Name
		CComboBox	*pBMType = (CComboBox*)m_pAmbPage->GetDlgItem(IDC_BMTYPE);
		pBMType->GetWindowTextA(sBMType);

		// DevId
		int nBMType = m_pAmbPage->m_BMType;
		if( nBMType )
		{
			for(int ii = 0; ii < g_nNumOfBaseModules; ii++)
			{
				if( sBMType.Compare(g_BaseModCtrl[ii].devInfo.sName) == 0 )
				{
					nBMDevId = g_BaseModCtrl[ii].devInfo.dType;
					break;
				}
			}
		}
		else
			nBMDevId = AMBPCI;

		// Ver
		char	*pcc;
		nBMVer = strtol(m_pAmbPage->m_strAmbVersion, &pcc, 16);

		// PId
		nBMPId = m_pAmbPage->m_SerialNum;
	}
	
	// ���������
	CString sSMType = "";
	int nSMDevId = -1;
	int nSMVer = -1;
	int nSMPId = -1;
	if( (GetReadWriteDevs() == READ_WRITE_SUBMODULE) || (GetReadWriteDevs() == READ_WRITE_ALL) )
	{
		int nSMType = m_pAdmPage->m_nAdmType;
		if( nSMType )
		{
			// Name
			CComboBox	*pSMType = (CComboBox*)m_pAdmPage->GetDlgItem(IDC_ADMTYPE);
			pSMType->GetWindowTextA(sSMType);

			// DevId
			for(int ii = 0; ii < g_nNumOfSubModules; ii++)
			{
				if( sSMType.Compare(g_SubmodCtrl[ii].devInfo.sName) == 0 )
				{
					nSMDevId = g_SubmodCtrl[ii].devInfo.Type;
					break;
				}
			}

			// Ver
			char	*pcc;
			nSMVer = strtol(m_pAdmPage->m_strAdmVersion, &pcc, 16);

			// PId
			nSMPId = m_pAdmPage->m_nAdmPID;
		}
	}

	// ��������� ���������� �������
	CString sType = "";
	CString sDevId = "";
	CString sVer = "";
	CString sPId = "";

	// Name
	if( sBMType!="" )
		sType = sBMType;
	if( sSMType!="" )
	{
		if( sType!="" )
			sType += "-";
		sType += sSMType;
	}
	// �������� �����('/') �� �������� ����������
	for(;;)
	{
		if( sType.Find('/')<0 )
			break;

		sType.Delete(sType.Find('/'));
	}

	// DevId
	if( nBMDevId!=-1 )
		sDevId.Format("0x%04X", nBMDevId);
	if( nSMDevId!=-1 )
	{
		if( sDevId!="" )
			sDevId += "-";
		CString sSMDevId = "";
		sSMDevId.Format("0x%04X", nSMDevId);
		sDevId += sSMDevId;
	}

	// Ver
	if( nBMVer!=-1 )
		sVer.Format("0x%02X", nBMVer);
	if( nSMVer!=-1 )
	{
		if( sVer!="" )
			sVer += "-";
		CString sSMVer = "";
		sSMVer.Format("0x%02X", nSMVer);
		sVer += sSMVer;
	}

	// PId
	if( nBMPId!=-1 )
		sPId.Format("%d", nBMPId);
	if( nSMPId!=-1 )
	{
		if( sPId!="" )
			sPId += "-";
		CString sSMPId = "";
		sSMPId.Format("%d", nSMPId);
		sPId += sSMPId;
	}

	CTime theTime = CTime::GetCurrentTime();
	int nDay = theTime.GetDay();
	int nMonth = theTime.GetMonth();
	int nYear = theTime.GetYear();

	m_pFileBaseDlg->m_sWriteName = sType;
	m_pFileBaseDlg->m_sWriteDevId = sDevId;
	m_pFileBaseDlg->m_sWriteVer = sVer;
	m_pFileBaseDlg->m_sWritePId = sPId;
	m_pFileBaseDlg->m_sWriteDate.Format("%02d.%02d.%04d", nDay, nMonth, nYear);
	
	if( m_pFileBaseDlg->m_sWriteDevId == "" )
		m_pFileBaseDlg->m_ctrlSaveBase.EnableWindow(FALSE);
	else
		m_pFileBaseDlg->m_ctrlSaveBase.EnableWindow(TRUE);

	m_pFileBaseDlg->UpdateData(FALSE);
}

void CIdCfgRomDlg::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	int nRes = AfxMessageBox("�� �������, ��� ������ �������� ���?", MB_YESNO|MB_ICONQUESTION);
	if( nRes==IDNO )
		return;

	PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[m_nDevType].devInfo);
	
	// ��������� �����
	ULONG nSizeCfgMem = BASEMOD_CFGMEM_SIZE + 4*SUBMOD_CFGMEM_SIZE;
	PUCHAR	pCfgMem = new UCHAR[nSizeCfgMem];

	// �������� ��������� �����
	for( int ii=0; ii<(int)nSizeCfgMem; ii++ )
		pCfgMem[ii] = 0xFF;

	// ������� ������
	pDeviceInfo->nRealBaseCfgSize = BASEMOD_CFGMEM_SIZE;
	memcpy(pDeviceInfo->pBaseCfgMem, pCfgMem, BASEMOD_CFGMEM_SIZE);

	// ���������
	PUCHAR pCurCfgMem = pCfgMem + BASEMOD_CFGMEM_SIZE;
	for( int ii = 0; ii < 4; ii++ )
	{
		pDeviceInfo->nRealAdmCfgSize[ii] = SUBMOD_CFGMEM_SIZE;
		if( pDeviceInfo->pAdmCfgMem[ii] )
		{
			memcpy(pDeviceInfo->pAdmCfgMem[ii], pCurCfgMem, SUBMOD_CFGMEM_SIZE);
			pCurCfgMem += SUBMOD_CFGMEM_SIZE;
		}
	}
	
	HCURSOR  hCursorWait	= LoadCursor(NULL, IDC_WAIT); // ������-����
	HCURSOR  hCursorArrow	= SetCursor(hCursorWait);
	(g_DeviceCtrl[m_nDevType].pWriteIdCfgRom)(pDeviceInfo, GetReadWriteDevs());
	SetCursor(hCursorArrow);
	
	delete [] pCfgMem;

	SaveDialogFieldsValues();
}

void CIdCfgRomDlg::OnCbnSelchangeReadWriteDev()
{
	// TODO: Add your control notification handler code here
	WriteRegistryValue("Software\\Instrumental Systems\\IdCfgRom", "ReadWriteDevs", m_ctrlReadWriteDevs.GetCurSel());

	if( m_pFileBaseDlg )
		TransferParamsFromMainToFileBaseDlg();
}
