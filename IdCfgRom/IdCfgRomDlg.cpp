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
	m_DevType = 0;
	g_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME1);
	m_wDialogFieldsEdited = 0;
	m_wBasemodFieldsEdited = 0;
	m_wSubmodFieldsEdited = 0;
	m_sWriteZakaz = "";
	m_sWriteSurname = "";
	m_sWriteKeyword = "";
	m_pFileBaseDlg = NULL;
}

void CIdCfgRomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABPAGE, m_ctrlTab);
	DDX_CBIndex(pDX, IDC_DEVICETYPE, m_DevType);
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

	SetReadWriteDevs(READ_WRITE_BASEMODULE);

	CComboBox* pDevType = (CComboBox*)GetDlgItem(IDC_DEVICETYPE);
	pDevType->ResetContent();
	if( g_NumOfDevices )
	{
		for(int i = 0; i < g_NumOfDevices; i++)
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

void CIdCfgRomDlg::SetReadWriteDevs(int nReadWriteDevs)
{
	m_ctrlReadWriteDevs.ResetContent();

	if( nReadWriteDevs == READ_WRITE_ALL )
	{
		m_ctrlReadWriteDevs.AddString("Базовый модуль и субмодуль");
		m_ctrlReadWriteDevs.AddString("Базовый модуль");
		m_ctrlReadWriteDevs.AddString("Субмодуль");
	}
	else if( nReadWriteDevs == READ_WRITE_BASEMODULE )
		m_ctrlReadWriteDevs.AddString("Базовый модуль");

	m_ctrlReadWriteDevs.SetCurSel(0);
}

int	CIdCfgRomDlg::GetReadWriteDevs()
{
	CString sDev;
	m_ctrlReadWriteDevs.GetLBText(m_ctrlReadWriteDevs.GetCurSel(), sDev);
	if( sDev == "Базовый модуль" )
		return READ_WRITE_BASEMODULE;
	if( sDev == "Субмодуль" )
		return READ_WRITE_SUBMODULE;
	if( sDev == "Базовый модуль и субмодуль" )
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
	// если поля изменены, предупреждаем пользователя перед выходом
	if( m_wDialogFieldsEdited || m_wBasemodFieldsEdited || m_wSubmodFieldsEdited )
	{
		if(MessageBox( "Некоторые поля изменены!\nВы действительно хотите выйти?", _T("IdCfgRom"), MB_YESNO|MB_ICONWARNING) != IDYES)
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
	// если поля изменены, предупреждаем пользователя перед выходом
	if( m_wDialogFieldsEdited || m_wBasemodFieldsEdited || m_wSubmodFieldsEdited )
	{
		if( MessageBox( "Некоторые поля изменены!\nВы действительно хотите выйти?", _T("IdCfgRom"), MB_YESNO|MB_ICONWARNING) != IDYES)
			return;
	}

	CDialog::OnCancel();
}

void CIdCfgRomDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	for(int i = 0; i < g_NumOfDevices; i++)	{
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

// Заполняет "диалоговые закладки" значениями из буфера
// после считывания в него из файла или устройства
//***************************************************************************************
void CIdCfgRomDlg::CfgMemToDlgItems()
{
	PVOID	pCfgMem;											// указатель на данные файла

	if ( m_readFileExt == ".hex" )								// преобразуем данные типа HEX в данные типа BIN
	{
		m_readFileExt = "";
		char	*binStr = new char[m_sizeCfgMem/2];				// временный массив данных hex файла
		U32		realSizeOfHexCfgMem = 0;
		char	*pCfgMemHex = (char*)m_pCfgMem; 				// указатель на данные HEX файла
		U32		hexByte;
		U08		bytesInHexString;
		U08		writeTypeInHexString;
		for(;;)													// проходим по строкам
		{
			if(	*pCfgMemHex == ':' )							// анализируем тэг
			{
				pCfgMemHex++;									// перепрыгиваем ':'
				LL_hexGetByte(&pCfgMemHex, &hexByte);
				bytesInHexString = hexByte;
				pCfgMemHex += 4;								// перепрыгиваем адрес
				LL_hexGetByte(&pCfgMemHex, &hexByte);
				writeTypeInHexString = hexByte;
				if( writeTypeInHexString == 0x04 )				// первая строка
				{
					pCfgMemHex += 8;							// перепрыгиваем стартовую строку
					continue;									// и перемещаемся к следующей строке
				}
				else if( writeTypeInHexString == 0x00 )			// строка данных
				{
					for( U08 ii = 0; ii<bytesInHexString; ii++ )// проходим по байтам данных
					{
						LL_hexGetByte(&pCfgMemHex, &hexByte);
						char	strTmp[2];
						strcpy(strTmp, (char*)&hexByte);
						memcpy(binStr + realSizeOfHexCfgMem + ii , strTmp, 1);
					}
					realSizeOfHexCfgMem += bytesInHexString;	// рассчитываем количество считанных байт данных в HEX файле
					pCfgMemHex += 4;							// перепрыгиваем суффикс
					continue;									// и перемещаемся к следующей строке
				}
				else if( writeTypeInHexString == 0x01 )			// последняя строка
					break;										// заканчиваем работу с файлом
			}
			pCfgMemHex++;										// если первый символ не ':'
		}
		pCfgMem = (PVOID)binStr;								// установка переменных исходя из результата 
		m_sizeCfgMem = realSizeOfHexCfgMem;						// преобразования HEX в BIN
		memcpy(m_pCfgMem, binStr, m_sizeCfgMem);
		delete [] binStr;
	}

	pCfgMem = (PVOID)m_pCfgMem;

	PVOID pEndCfgMem = (PVOID)((PUCHAR)pCfgMem + m_sizeCfgMem);
	int end_flag = 0;
	do
	{
		USHORT sign;
		sign = *((USHORT*)pCfgMem);

		USHORT size = 0;// = *((USHORT*)pCfgMem + 1);
		switch(sign)
		{
		case END_TAG:
		case ALT_END_TAG:
			end_flag = 1;
			break;
		case BASE_ID_TAG:
			{
				m_RealBaseCfgSize = *((USHORT*)pCfgMem + 2);
				size = (USHORT)m_pAmbPage->SetDataIntoDlg(pCfgMem);
				break;
			}
		case COMMENT_ID_TAG:
			{
				size = (USHORT)m_pAmbPage->SetComment(pCfgMem);
				break;
			}
/*		case ADMIF_CFG_TAG:
			{
				m_pAdmIfPage->SetDataIntoDlg((PICR_CfgAdmIf)pCfgMem);
				size = sizeof(ICR_CfgAdmIf);
				break;
			}*/
		case ADM2IF_CFG_TAG:
			{
				m_pAdmIfPage->SetDataIntoDlg((PICR_CfgAdm2If)pCfgMem);
				size = sizeof(ICR_CfgAdm2If);
				break;
			}
		case ADC_FIFO_TAG:
			{
				m_pFifoPage->SetDataIntoDlg((PICR_CfgAdcFifo)pCfgMem);
				size = sizeof(ICR_CfgAdcFifo);
				break;
			}
		case DAC_CFG_TAG:
			{
				m_pDacPage->SetDataIntoDlg((PICR_CfgDac)pCfgMem);
				size = sizeof(ICR_CfgDac);
				break;
			}
		case DAC_FIFO_TAG:
			{
				m_pFifoPage->SetDataIntoDlg((PICR_CfgDacFifo)pCfgMem);
				size = sizeof(ICR_CfgDacFifo);
				break;
			}
		case PLD_CFG_TAG:
			{
				m_pPldPage->SetDataIntoDlg((PICR_CfgAdmPld)pCfgMem);
				size = sizeof(ICR_CfgAdmPld);
				break;
			}
		default:
				size = *((USHORT*)pCfgMem + 1);
				size += 4;
				break;
		}
		pCfgMem = (PUCHAR)pCfgMem + size;
	} while(!end_flag && pCfgMem < pEndCfgMem);
	

	pCfgMem = (PVOID)(m_pCfgMem + m_RealBaseCfgSize);
//	pEndCfgMem = (PVOID)((PUCHAR)pCfgMem + m_pAdmPage->m_CfgBufSize);
	end_flag = 0;
	do
	{
		USHORT sign = *((USHORT*)pCfgMem);
		USHORT size = 0;
		switch(sign)
		{
		case END_TAG:
		case ALT_END_TAG:
			end_flag = 1;
			break;
		case ADM_ID_TAG:
			{
				size = (USHORT)m_pAdmPage->SetDataIntoDlg(pCfgMem);
				break;
			}
		case COMMENT_ID_TAG:
			{
				size = (USHORT)m_pAdmPage->SetComment(pCfgMem);
				break;
			}
		default:
				size = *((USHORT*)pCfgMem + 1);
				size += 4;
				break;
		}
		pCfgMem = (PUCHAR)pCfgMem + size;
	} while(!end_flag && pCfgMem < pEndCfgMem);
}

void CIdCfgRomDlg::ReadThroughDialog()
{
	// TODO: Add your control notification handler code here
	CString sFilePath = ShowReadDialog();
	if( sFilePath == "" )
		return;
	
	ReadCfgFile(sFilePath);

	if( m_pFileBaseDlg )
		TransferParamsFromMainToFileBaseDlg();
}

CString CIdCfgRomDlg::ShowReadDialog()
{
	CString strFilter;
	GetMsg(MSG_FILE_FILTER_BIN_AND_HEX, strFilter);
	CFileDialog readFileDlg(TRUE, _T(".bin;.hex"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

	// установить директорию для открытия файла исходя из записи в реестре
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
	// если считать из реестра не удалось, указываем директорию, где хранится .exe файл (считываем из командной строки)
	if( status != ERROR_SUCCESS )
	{
		LPTSTR cmdLine = GetCommandLine() + 1;
		LPTSTR ShortFileName = strrchr(cmdLine, '\\') + 1;
		*ShortFileName = 0;
		strcat(cmdLine, "Config");
		readFileDlg.m_ofn.lpstrInitialDir = cmdLine;
		CreateDirectory(cmdLine, NULL);
	}
	
	// устанавливаем заголовок окна открытия файла
	CString strTitle;
	GetMsg(MSG_READ_FILE_CAPTION, strTitle);
	readFileDlg.m_ofn.lpstrTitle = strTitle.GetBuffer(80);

	INT_PTR nID = readFileDlg.DoModal();
	if(nID != IDOK)
		return "";
	CString fileName = readFileDlg.GetPathName();

	// записываем в реестр путь к последнему считанному файлу
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
	m_pAmbPage->m_sComment = "";
	m_pAdmPage->m_sComment = "";

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
	m_pCfgMem = new UCHAR[bFileSize];
	ReadFile(hfile, m_pCfgMem, bFileSize, &dwBytesRead, NULL);
	m_sizeCfgMem = dwBytesRead;
	m_pAdmPage->InitData();
	CfgMemToDlgItems();
	delete [] m_pCfgMem;

	m_pAdmIfPage->SetMaxAdmIf(m_pAmbPage->m_NumOfAdmIf - 1);
	m_pAdmPage->SetMaxAdm(m_pAmbPage->m_NumOfAdmIf - 1);
	m_pPldPage->SetMaxPld(m_pAdmIfPage->m_NumOfPld - 1);
	m_pFifoPage->SetMaxAdcFifo(m_pAdmIfPage->m_NumOfAdcFifo - 1);
	m_pFifoPage->SetMaxDacFifo(m_pAdmIfPage->m_NumOfDacFifo - 1);
	m_pDacPage->SetMaxDac(m_pAdmIfPage->m_NumOfDac - 1);
	m_pAmbPage->InitData();
	CloseHandle(hfile);

	m_pAmbPage->UpdateData(FALSE);
	if( m_pAmbPage->m_NumOfAdmIf == 0 )
		SetReadWriteDevs(READ_WRITE_BASEMODULE);
	else if ( m_pAmbPage->m_NumOfAdmIf > 0 )
	{
		m_pAdmPage->UpdateData(FALSE);
		if( m_pAdmPage->m_AdmType == 0 )
			SetReadWriteDevs(READ_WRITE_BASEMODULE);
		else if ( m_pAdmPage->m_AdmType > 0 )
			SetReadWriteDevs(READ_WRITE_ALL);
	}
	UpdateData(FALSE);

	SaveDialogFieldsValues();
}

// Заполняет буфер значениями из "диалоговых закладок"
// перед записью его в файл или устройство
ULONG CIdCfgRomDlg::DlgItemsToCfgMem()
{
	USHORT* pEndCfgMem = (USHORT*)m_pCfgMem + m_sizeCfgMem/2;
	USHORT* pCurCfgMem = (USHORT*)m_pCfgMem;
	ULONG bCfgSize = m_pAmbPage->GetDataFromDlg(pCurCfgMem);
	pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + bCfgSize);
	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	int numOfADM = m_pAmbPage->m_NumOfAdmIf;
	if( numOfADM>0 )
	{
		for(int i = 0; i < numOfADM; i++)
		{
			m_pAdmIfPage->GetDataFromDlg((PICR_CfgAdm2If)pCurCfgMem, i);
			int numOfADCFIFO = ((PICR_CfgAdm2If)pCurCfgMem)->bAdcFifoCnt;
			int numOfDAC = ((PICR_CfgAdm2If)pCurCfgMem)->bDacCnt;
			int numOfDACFIFO = ((PICR_CfgAdm2If)pCurCfgMem)->bDacFifoCnt;
			int numOfPld = ((PICR_CfgAdm2If)pCurCfgMem)->bPldCnt;
			pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdm2If));
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
			if( numOfADCFIFO )
			{
				for(int idx = 0; idx < numOfADCFIFO; idx++)
				{
					m_pFifoPage->GetDataFromDlg((PICR_CfgAdcFifo)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdcFifo));
					if(pCurCfgMem >= pEndCfgMem)
						return 1;
				}
			}
			if( numOfDAC )
			{
				for(int idx = 0; idx < numOfDAC; idx++)
				{
					m_pDacPage->GetDataFromDlg((PICR_CfgDac)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDac));
					if(pCurCfgMem >= pEndCfgMem)
						return 1;
				}
			}
			if( numOfDACFIFO )
			{
				for(int idx = 0; idx < numOfDACFIFO; idx++)
				{
					m_pFifoPage->GetDataFromDlg((PICR_CfgDacFifo)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgDacFifo));
					if(pCurCfgMem >= pEndCfgMem)
						return 1;
				}
			}
			if(numOfPld)
			{
				for(int idx = 0; idx < numOfPld; idx++)
				{
					m_pPldPage->GetDataFromDlg((PICR_CfgAdmPld)pCurCfgMem, idx, i);
					pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + sizeof(ICR_CfgAdmPld));
					if(pCurCfgMem >= pEndCfgMem)
						return 1;
				}
			}
		}
	}
	*pCurCfgMem = END_TAG;
	pCurCfgMem++;
	m_RealBaseCfgSize = ULONG((PUCHAR)pCurCfgMem - m_pCfgMem);
	USHORT* pSizeAll = (USHORT*)m_pCfgMem;
	pSizeAll[2] = m_RealBaseCfgSize;

	if(numOfADM)
	{
		for(int i = 0; i < numOfADM; i++)
		{
			PUCHAR pAdmCfgMem = (PUCHAR)pCurCfgMem;
			USHORT* pEndCfgMem = (USHORT*)pCurCfgMem + m_pAdmPage->m_CfgBufSize;
			ULONG bCfgSize = m_pAdmPage->GetDataFromDlg(pCurCfgMem, i);
			pCurCfgMem = (USHORT*)((PUCHAR)pCurCfgMem + bCfgSize);
			if(pCurCfgMem >= pEndCfgMem)
				return 1;
			m_RealAdmCfgSize[i] = ULONG((PUCHAR)pCurCfgMem - pAdmCfgMem);
			USHORT* pSizeAll = (USHORT*)pAdmCfgMem;
			pSizeAll[2] = m_RealAdmCfgSize[i];
		}
	}
	for(int i = numOfADM; i < 4; i++)
		m_RealAdmCfgSize[i] = 0;

	return 0;
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

	// установить директорию для сохранения файла исходя из записи в реестре
	CHAR regDir[MAX_PATH];
	CRegKey key;
	LONG status = key.Open(HKEY_CURRENT_USER, "Software\\Instrumental Systems\\IdCfgRom");
	if (status == ERROR_SUCCESS)
	{
		DWORD regDirSize = sizeof(regDir);
		key.QueryValue(regDir, "Load/Save Directory", &regDirSize);
		saveFileDlg.m_ofn.lpstrInitialDir = regDir;
	}
	// если считать из реестра не удалось, указываем директорию, где хранится .exe файл (считываем из командной строки)
	else
	{
		LPTSTR cmdLine = GetCommandLine() + 1;
		LPTSTR ShortFileName = strrchr(cmdLine, '\\') + 1;
		*ShortFileName = 0;
		strcat(cmdLine, "Config");
		saveFileDlg.m_ofn.lpstrInitialDir = cmdLine;
		CreateDirectory(cmdLine, NULL);
	}

	// устанавливаем заголовок окна сохранения файла
	CString strTitle;
	GetMsg(MSG_SAVE_FILE_CAPTION, strTitle);
	saveFileDlg.m_ofn.lpstrTitle = strTitle.GetBuffer(80);

	INT_PTR nID = saveFileDlg.DoModal();
	if(nID != IDOK)
		return "";
	CString fileName = saveFileDlg.GetPathName();
	ParseFileNameExt(fileName);

	// записываем в реестр путь к последнему сохранённому файлу
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
	DWORD dwBytesWritten;
	m_sizeCfgMem = m_pAmbPage->m_CfgBufSize + m_pAdmPage->m_CfgBufSize;
	m_pCfgMem = new UCHAR[m_sizeCfgMem];
	if( DlgItemsToCfgMem() == 0 ) 
	{
		WriteFile(hfile, m_pCfgMem, m_RealBaseCfgSize, &dwBytesWritten, NULL);
		PUCHAR pCurCfgMem = m_pCfgMem + m_RealBaseCfgSize;
		for(int i = 0; i < 4; i++) {
			if(m_RealAdmCfgSize[i]) {
				WriteFile(hfile, pCurCfgMem, m_RealAdmCfgSize[i], &dwBytesWritten, NULL);
				pCurCfgMem += m_RealAdmCfgSize[i];
			}
		}
	}
	else 
	{
//		TCHAR MsgBuf[] = _T("Недостаточно памяти для конфигурационных данных !");
		CString MsgBuf;
//		TCHAR MsgBuf[MAX_PATH];
		GetMsg(MSG_NOT_ENOUGH_MEMORY, MsgBuf);
		AfxMessageBox( MsgBuf, MB_OK|MB_ICONINFORMATION, 0);
		return;
	}
	delete[] m_pCfgMem;

	CloseHandle(hfile);

	SaveDialogFieldsValues();
}

void CIdCfgRomDlg::SaveHex(CString sFilePath)
{
	FILE	*fout = fopen( sFilePath, "wt" );
	if( fout==NULL )
		fout = stdout;

	m_sizeCfgMem = m_pAmbPage->m_CfgBufSize + m_pAdmPage->m_CfgBufSize;
	m_pCfgMem = new UCHAR[m_sizeCfgMem];
	if(DlgItemsToCfgMem() == 0)
	{
		// запись конфигурации базового модуля
		U08 *hex = (U08*)m_pCfgMem;									// байт данных для записи в файл
		U16	hiAddress = 0x0000;										// старшая часть адреса (первая строка)
		U16	loAddress = 0x0000;										// младшая часть адреса (строки данных)
		U08	controlSum;												// контрольная сумма
			controlSum = 0x0 - ( 0x02 + ((hiAddress&0xFF00)>>8) + (hiAddress&0x00FF) + 0x04);
		fprintf(fout, ":02000004%04X%02X\n", hiAddress, controlSum);// запись стартовой строки
		char	str[141] = "";
		char	strTmp[140] = "";
		// "for": вывод строк данных
		for( int ii=0; ii<(m_RealBaseCfgSize+1); ii++ )
		{
			// "if": запись суффикса одной строки и префикса следующей строки данных
			if( !(ii%64) || (ii == m_RealBaseCfgSize) )				//последний байт в строке или последний байт вообще
			{
				// "if": запись суффикса
				if( ii!=0 ) // не начало первой строки данных
				{
					controlSum = 0x40 + ( (loAddress&0xFF00)>>8 ) + (loAddress&0x00FF);
					int bytesCntInStr = ii%64 ? ii%64 : 64;			// расчёт количества байтов в строке для вывода
					for( int jj=0; jj<bytesCntInStr; jj++)
						controlSum += hex[ii-1-jj];
					controlSum = 0x0 - controlSum;
					sprintf_s(strTmp, ("%02X\n"), controlSum);
					strcat(str, strTmp);
					// "if": вывод последней строки данных
					if( ii == m_RealBaseCfgSize )
					{
						sprintf_s(strTmp, (":%02X"), bytesCntInStr);
						strncpy(str, strTmp, 3);
						fprintf(fout, str);							// вывод сформированной строки данных в файл
						str[0] = 0;
						break;
					}
					loAddress+=64;
				}
				fprintf(fout, str); // вывод в файл сформированной строки данных
				str[0] = 0;
				// запись префикса
				sprintf_s(strTmp, (":40%04X00"), loAddress);
				strcat(str, strTmp);
			}
			sprintf_s(strTmp, ("%02X"), hex[ii]);					// запись байта данных
			strcat(str, strTmp);
		}

		// запись конфигурации субмодулей
		PUCHAR pCurCfgMem = m_pCfgMem + m_RealBaseCfgSize;
		for(int i = 0; i < 4; i++)
		{
			if(m_RealAdmCfgSize[i])
			{
				hex = (U08*)pCurCfgMem;
				for( int ii=0; ii<(m_RealAdmCfgSize[i]+1); ii++ )
				{
					if( !(ii%64) || (ii == m_RealAdmCfgSize[i]) )
					{
						if( ii!=0 )
						{
							controlSum = 0x40 + ( (loAddress&0xFF00)>>8 ) + (loAddress&0x00FF);
							int bytesCntInStr = ii%64 ? ii%64 : 64;
							for( int jj=0; jj<bytesCntInStr; jj++)
								controlSum += hex[ii-1-jj];
							controlSum = 0x0 - controlSum;
							sprintf_s(strTmp, ("%02X\n"), controlSum);
							strcat(str, strTmp);
							if( ii == m_RealAdmCfgSize[i] )
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
				pCurCfgMem += m_RealAdmCfgSize[i];
			}
		}
		fprintf(fout, ":00000001FF");
	}
	else
	{
//		TCHAR MsgBuf[] = _T("Недостаточно памяти для конфигурационных данных !");
		CString MsgBuf;
//		TCHAR MsgBuf[MAX_PATH];
		GetMsg(MSG_NOT_ENOUGH_MEMORY, MsgBuf);
		AfxMessageBox( MsgBuf, MB_OK|MB_ICONINFORMATION, 0);
		return;
	}
	delete[] m_pCfgMem;
	fclose(fout);

	SaveDialogFieldsValues();
}

void CIdCfgRomDlg::OnBnClickedIntodev()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[m_DevType].devInfo);
	m_sizeCfgMem = m_pAmbPage->m_CfgBufSize + m_pAdmPage->m_CfgBufSize;
	m_pCfgMem = new UCHAR[m_sizeCfgMem];
	if( DlgItemsToCfgMem() == 0 )
	{
		pDeviceInfo->dRealBaseCfgSize = m_RealBaseCfgSize;
		memcpy(pDeviceInfo->pBaseCfgMem, m_pCfgMem, m_RealBaseCfgSize);
		PUCHAR pCurCfgMem = m_pCfgMem + m_RealBaseCfgSize;
		for( int i = 0; i < 4; i++ )
		{
			pDeviceInfo->dRealAdmCfgSize[i] = m_RealAdmCfgSize[i];
			if( m_RealAdmCfgSize[i] && pDeviceInfo->pAdmCfgMem[i] )
			{
				memcpy(pDeviceInfo->pAdmCfgMem[i], pCurCfgMem, m_RealAdmCfgSize[i]);
				pCurCfgMem += m_RealAdmCfgSize[i];
			}
		}
		CString MsgBuf, MsgBuf0, MsgBuf1;
		GetMsg(MSG_WARN_REWRITE_DATA, MsgBuf0);
		GetMsg(MSG_CONTINUE, MsgBuf1);
		MsgBuf = MsgBuf0 + _T("\n") + MsgBuf1;
		if(MessageBox( MsgBuf, _T("IdCfgRom"), MB_YESNO|MB_ICONWARNING) == IDYES)
		{
			HCURSOR  hCursorWait = LoadCursor(NULL, IDC_WAIT); // курсор-часы
			HCURSOR  hCursorArrow = SetCursor(hCursorWait);
			(g_DeviceCtrl[m_DevType].pWriteIdCfgRom)(pDeviceInfo, GetReadWriteDevs());
			SaveDialogFieldsValues();
			SetCursor(hCursorArrow);
		}
	}
	else
	{
		CString MsgBuf;
		GetMsg(MSG_NOT_ENOUGH_MEMORY, MsgBuf);
		AfxMessageBox(MsgBuf, MB_OK|MB_ICONINFORMATION);
		return;
	}
	delete[] m_pCfgMem;
}

void CIdCfgRomDlg::OnBnClickedFromdev()
{
	// TODO: Add your control notification handler code here
	HCURSOR  hCursorWait	= LoadCursor(NULL, IDC_WAIT); // курсор-часы
	HCURSOR  hCursorArrow	= SetCursor(hCursorWait);

	UpdateData(TRUE); // from window to variable
	m_pAmbPage->m_sComment = "";
	m_pAdmPage->m_sComment = "";
	PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[m_DevType].devInfo);
	(g_DeviceCtrl[m_DevType].pReadIdCfgRom)(pDeviceInfo, GetReadWriteDevs());
	m_sizeCfgMem = pDeviceInfo->dBaseCfgMemSize;
	for(int i = 0; i < 4; i++)
		m_sizeCfgMem += pDeviceInfo->dAdmCfgMemSize[i];
	m_pCfgMem = new UCHAR[m_sizeCfgMem];
	for( ULONG ii=0; ii<m_sizeCfgMem; ii++ )
		m_pCfgMem[ii]=0xFF;
	memcpy(m_pCfgMem, pDeviceInfo->pBaseCfgMem, pDeviceInfo->dBaseCfgMemSize);
	m_RealBaseCfgSize = pDeviceInfo->dRealBaseCfgSize;
	PUCHAR pCurCfgMem = m_pCfgMem + m_RealBaseCfgSize;
	for(int i = 0; i < 4; i++)
	{
//		m_RealAdmCfgSize[i] = pDeviceInfo->RealAdmCfgSize[i];
		if(pDeviceInfo->pAdmCfgMem[i] && pDeviceInfo->dAdmCfgMemSize[i])
		{
			memcpy(pCurCfgMem, pDeviceInfo->pAdmCfgMem[i], pDeviceInfo->dAdmCfgMemSize[i]);
			m_RealAdmCfgSize[i] = pDeviceInfo->dRealAdmCfgSize[i];
			pCurCfgMem += m_RealAdmCfgSize[i];
		}
	}
	m_pAdmPage->InitData();
	CfgMemToDlgItems();
	delete[] m_pCfgMem;
	m_pAdmIfPage->SetMaxAdmIf(m_pAmbPage->m_NumOfAdmIf - 1);
	m_pAdmPage->SetMaxAdm(m_pAmbPage->m_NumOfAdmIf - 1);
	m_pPldPage->SetMaxPld(m_pAdmIfPage->m_NumOfPld - 1);
	m_pFifoPage->SetMaxAdcFifo(m_pAdmIfPage->m_NumOfAdcFifo - 1);
	m_pFifoPage->SetMaxDacFifo(m_pAdmIfPage->m_NumOfDacFifo - 1);
	m_pDacPage->SetMaxDac(m_pAdmIfPage->m_NumOfDac - 1);
	m_pAmbPage->InitData();

	// Разблокировать галочку "Запись только в субмодуль", если субмодуль есть, и наоборот
	m_pAmbPage->UpdateData(FALSE);
	if( m_pAmbPage->m_NumOfAdmIf == 0 )
		SetReadWriteDevs(READ_WRITE_BASEMODULE);
	else if ( m_pAmbPage->m_NumOfAdmIf > 0 )
	{
		m_pAdmPage->UpdateData(FALSE);
		if( m_pAdmPage->m_AdmType == 0 )
			SetReadWriteDevs(READ_WRITE_BASEMODULE);
		else if ( m_pAdmPage->m_AdmType > 0 )
			SetReadWriteDevs(READ_WRITE_ALL);
	}
	UpdateData(FALSE);

	SaveDialogFieldsValues();

	if( m_pFileBaseDlg )
		TransferParamsFromMainToFileBaseDlg();

	SetCursor(hCursorArrow);
}

// сохранение значений диалоговых полей
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
	m_rDialogFieldsValues.AdmAdmPID = m_pAdmPage->m_AdmPID;
	m_rDialogFieldsValues.AdmAdmType = m_pAdmPage->m_AdmType;
	m_rDialogFieldsValues.AdmstrAdmVersion = m_pAdmPage->m_strAdmVersion;

	m_wDialogFieldsEdited = 0;
	m_wBasemodFieldsEdited = 0;
	m_wSubmodFieldsEdited = 0;
}

void CIdCfgRomDlg::CheckEditOfStructOfDialogFieldsValues()
{
	// проверяем, изменились ли диалоговые поля
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
		m_rDialogFieldsValues.AdmAdmPID != m_pAdmPage->m_AdmPID ||
		m_rDialogFieldsValues.AdmAdmType != m_pAdmPage->m_AdmType ||
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
		return;
	}

	m_pFileBaseDlg = new CWriteReadDlg();
	m_pFileBaseDlg->Create(IDD_WRITE_READ_DIALOG, this);
	TransferParamsFromMainToFileBaseDlg();
	m_pFileBaseDlg->m_sWriteZakaz = m_sWriteZakaz;
	m_pFileBaseDlg->m_sWriteSurname = m_sWriteSurname;
	m_pFileBaseDlg->m_sWriteKeyword = m_sWriteKeyword;
	m_pFileBaseDlg->UpdateData(FALSE);

	m_pFileBaseDlg->ShowWindow(SW_SHOW);
}

void CIdCfgRomDlg::TransferParamsFromMainToFileBaseDlg()
{
	m_pFileBaseDlg->UpdateData(TRUE);

	CString sBMType = "";
	int nDevId = -1;
	int nVer = -1;
	int nPId = -1;

	UpdateData(TRUE);
	CComboBox	*pBMType = (CComboBox*)m_pAmbPage->GetDlgItem(IDC_BMTYPE);
	pBMType->GetWindowTextA(sBMType);
	int nBMType = m_pAmbPage->m_BMType;
	if( nBMType )
	{
		for(int ii = 0; ii < g_NumOfBaseModules; ii++)
		{
			if( sBMType.Compare(g_BaseModCtrl[ii].devInfo.sName) == 0 )
			{
				nDevId = g_BaseModCtrl[ii].devInfo.dType;
				break;
			}
		}
	}
	else
		nDevId = AMBPCI;
	char	*pcc;
	nVer = strtol(m_pAmbPage->m_strAmbVersion, &pcc, 16);
	nPId = m_pAmbPage->m_SerialNum;

	CTime theTime = CTime::GetCurrentTime();
	int nDay = theTime.GetDay();
	int nMonth = theTime.GetMonth();
	int nYear = theTime.GetYear();

	m_pFileBaseDlg->m_sWriteName = sBMType;
	m_pFileBaseDlg->m_sWriteDevId.Format("0x%04X", nDevId);
	m_pFileBaseDlg->m_sWriteVer.Format("0x%02X", nVer);
	m_pFileBaseDlg->m_sWritePId.Format("%d", nPId);
	m_pFileBaseDlg->m_sWriteDate.Format("%02d.%02d.%04d", nDay, nMonth, nYear);

	m_pFileBaseDlg->UpdateData(FALSE);
}

void CIdCfgRomDlg::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	int nRes = AfxMessageBox("Вы уверены, что хотите очистить ПЗУ?", MB_YESNO|MB_ICONQUESTION);
	if( nRes==IDNO )
		return;

	PDEVICE_INFO pDeviceInfo = &(g_DeviceCtrl[m_DevType].devInfo);
	m_sizeCfgMem = BASEMOD_CFGMEM_SIZE + 4*SUBMOD_CFGMEM_SIZE;
	m_pCfgMem = new UCHAR[m_sizeCfgMem];
	pDeviceInfo->dRealBaseCfgSize = BASEMOD_CFGMEM_SIZE;
	for( int ii=0; ii<(int)m_sizeCfgMem; ii++ )
		m_pCfgMem[ii] = 0xFF;
	memcpy(pDeviceInfo->pBaseCfgMem, m_pCfgMem, BASEMOD_CFGMEM_SIZE);
	PUCHAR pCurCfgMem = m_pCfgMem + BASEMOD_CFGMEM_SIZE;
	for( int ii = 0; ii < 4; ii++ )
	{
		pDeviceInfo->dRealAdmCfgSize[ii] = SUBMOD_CFGMEM_SIZE;
		if( m_RealAdmCfgSize[ii] && pDeviceInfo->pAdmCfgMem[ii] )
		{
			for( int jj=0; jj<SUBMOD_CFGMEM_SIZE; jj++ )
				pCurCfgMem[jj] = 0xFF;
			memcpy(pDeviceInfo->pAdmCfgMem[ii], pCurCfgMem, SUBMOD_CFGMEM_SIZE);
			pCurCfgMem += SUBMOD_CFGMEM_SIZE;
		}
	}
	
	HCURSOR  hCursorWait	= LoadCursor(NULL, IDC_WAIT); // курсор-часы
	HCURSOR  hCursorArrow	= SetCursor(hCursorWait);
	(g_DeviceCtrl[m_DevType].pWriteIdCfgRom)(pDeviceInfo, GetReadWriteDevs());
	SetCursor(hCursorArrow);
	
	delete [] m_pCfgMem;

	SaveDialogFieldsValues();
}
