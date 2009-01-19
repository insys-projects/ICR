// WriteReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "WriteReadDlg.h"
#include "IdCfgRomDlg.h"

int	g_nSortColumnNum = 0;
int	g_nLastArrowType = NO_ARROW;

// CWriteReadDlg dialog

IMPLEMENT_DYNAMIC(CWriteReadDlg, CDialog)

CWriteReadDlg::CWriteReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteReadDlg::IDD, pParent)
	, m_sWriteName(_T(""))
	, m_sWriteDevId(_T(""))
	, m_sWriteVer(_T(""))
	, m_sWritePId(_T(""))
	, m_sWriteDate(_T(""))
	, m_sFileBaseDir(_T(""))
{
	m_nLastClickedColumnNum = -1;
	m_hUpArrow = LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_ARROW_UP));
	m_hDownArrow = LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_ARROW_DOWN));
	m_nCanResize = 0;
	m_pFilterDlg = NULL;
}

CWriteReadDlg::~CWriteReadDlg()
{
}

void CWriteReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BASE, m_ctrlBase);
	DDX_Text(pDX, IDC_WRITE_NAME, m_sWriteName);
	DDX_Text(pDX, IDC_WRITE_DEVID, m_sWriteDevId);
	DDX_Text(pDX, IDC_WRITE_VER, m_sWriteVer);
	DDX_Text(pDX, IDC_WRITE_ZAKAZ, m_sWriteZakaz);
	DDX_Text(pDX, IDC_WRITE_PID, m_sWritePId);
	DDX_Text(pDX, IDC_WRITE_SURNAME, m_sWriteSurname);
	DDX_Text(pDX, IDC_WRITE_KEYWORD, m_sWriteKeyword);
	DDX_Text(pDX, IDC_WRITE_DATE, m_sWriteDate);
	DDX_Control(pDX, IDC_READ_BASE, m_ctrlReadBase);
	DDX_Control(pDX, IDC_EDIT_BASE, m_ctrlEditBase);
	DDX_Control(pDX, IDC_DELETE_BASE, m_ctrlDeleteBase);
	DDX_Control(pDX, IDC_SAVE_BASE, m_ctrlSaveBase);
	DDX_Text(pDX, IDC_FILE_BASE_DIR, m_sFileBaseDir);
}


BEGIN_MESSAGE_MAP(CWriteReadDlg, CDialog)
	ON_BN_CLICKED(IDC_READ_FILE, &CWriteReadDlg::OnBnClickedReadFile)
	ON_BN_CLICKED(IDC_SAVE_BASE, &CWriteReadDlg::OnBnClickedSaveBase)
	ON_BN_CLICKED(IDC_READ_BASE, &CWriteReadDlg::OnBnClickedReadBase)
	ON_BN_CLICKED(IDC_DELETE_BASE, &CWriteReadDlg::OnBnClickedDeleteBase)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_BASE, &CWriteReadDlg::OnLvnColumnclickBase)
	ON_NOTIFY(NM_CLICK, IDC_BASE, &CWriteReadDlg::OnNMClickBase)
	ON_NOTIFY(LVN_KEYDOWN, IDC_BASE, &CWriteReadDlg::OnLvnKeydownBase)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SAVE_FILE_HEX, &CWriteReadDlg::OnBnClickedSaveFileHex)
	ON_BN_CLICKED(IDC_SAVE_FILE_BIN, &CWriteReadDlg::OnBnClickedSaveFileBin)
	ON_BN_CLICKED(IDC_FILTER, &CWriteReadDlg::OnBnClickedFilter)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_EDIT_BASE, &CWriteReadDlg::OnBnClickedEditBase)
	ON_NOTIFY(NM_DBLCLK, IDC_BASE, &CWriteReadDlg::OnNMDblclkBase)
	ON_BN_CLICKED(IDC_FILE_BASE_PATH, &CWriteReadDlg::OnBnClickedFileBasePath)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CWriteReadDlg message handlers

BOOL CWriteReadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetIcon(g_hIcon, TRUE);			// Set big icon
	SetIcon(g_hIcon, FALSE);		// Set small icon

	m_ctrlBase.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlBase.InsertColumn(0, "Имя устройства", LVCFMT_LEFT, 100);
	m_ctrlBase.InsertColumn(1, "ID устройства", LVCFMT_LEFT, 90);
	m_ctrlBase.InsertColumn(2, "Версия", LVCFMT_LEFT, 50);
	m_ctrlBase.InsertColumn(3, "Номер заказа", LVCFMT_LEFT, 90);
	m_ctrlBase.InsertColumn(4, "PID", LVCFMT_LEFT, 70);
	m_ctrlBase.InsertColumn(5, "Фамилия", LVCFMT_LEFT, 90);
	m_ctrlBase.InsertColumn(6, "Ключевое слово", LVCFMT_LEFT, 100);
	m_ctrlBase.InsertColumn(7, "Дата", LVCFMT_LEFT, 80);

	m_ctrlReadBase.EnableWindow(FALSE);
	m_ctrlEditBase.EnableWindow(FALSE);
	m_ctrlDeleteBase.EnableWindow(FALSE);

	// заполнение таблицы базой файлов
	m_sFileBaseDir = GetFileBasePathFromRegistry();
	UpdateData(FALSE);
	LoadFileBaseFromDir(m_sFileBaseDir);

	// установка размера и положения окна
	WINDOWPLACEMENT place;
	GetWindowPlacement(&place);
	m_nDefaultDialogLeft = place.rcNormalPosition.left;
	m_nDefaultDialogRight = place.rcNormalPosition.right;
	m_nDefaultDialogTop = place.rcNormalPosition.top;
	m_nDefaultDialogBottom = place.rcNormalPosition.bottom;

	SaveItemPosition(this, IDC_BASE, FIELD);
	SaveItemPosition(this, IDC_BASE_WORK_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_NAME_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_DEVID_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_VER_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_ZAKAZ_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_PID_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_SURNAME_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_KEYWORD_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_DATE_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_NAME, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_DEVID, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_VER, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_ZAKAZ, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_PID, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_SURNAME, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_KEYWORD, TOP_RIGHT);
	SaveItemPosition(this, IDC_WRITE_DATE, TOP_RIGHT);
	SaveItemPosition(this, IDC_SAVE_BASE, TOP_RIGHT);
	SaveItemPosition(this, IDC_READ_BASE, TOP_RIGHT);
	SaveItemPosition(this, IDC_EDIT_BASE, TOP_RIGHT);
	SaveItemPosition(this, IDC_DELETE_BASE, TOP_RIGHT);
	SaveItemPosition(this, IDC_FILTER, TOP_RIGHT);
	SaveItemPosition(this, IDC_HAND_WORK_STATIC, TOP_RIGHT);
	SaveItemPosition(this, IDC_SAVE_FILE_BIN, TOP_RIGHT);
	SaveItemPosition(this, IDC_SAVE_FILE_HEX, TOP_RIGHT);
	SaveItemPosition(this, IDC_READ_FILE, TOP_RIGHT);
	SaveItemPosition(this, IDC_STATIC_FILE_BASE_DIR, TOP_RIGHT);
	SaveItemPosition(this, IDC_FILE_BASE_DIR, TOP_RIGHT);
	SaveItemPosition(this, IDC_FILE_BASE_PATH, TOP_RIGHT);

	for( int ii=0; ii<(int)m_vItemsPositions.size(); ii++ )
		MoveItemRelativePosition(m_vItemsPositions[ii]);
	m_nCanResize = 1;

	// окно отображается чуть ниже основного
	{
		WINDOWPLACEMENT	place;
		GetWindowPlacement(&place);
		WINDOWPLACEMENT	placeParent;
		m_poIdCfgRomWindow->GetWindowPlacement(&placeParent);

		WINDOWPLACEMENT placeNew = place;
		placeNew.rcNormalPosition.left = (placeParent.rcNormalPosition.right + placeParent.rcNormalPosition.left)/2 - (place.rcNormalPosition.right)/2;
		placeNew.rcNormalPosition.right = (placeParent.rcNormalPosition.right + placeParent.rcNormalPosition.left)/2 + (place.rcNormalPosition.right)/2;
		placeNew.rcNormalPosition.top = placeParent.rcNormalPosition.top + 80;
		placeNew.rcNormalPosition.bottom = placeParent.rcNormalPosition.top + 80 + place.rcNormalPosition.bottom;

		SetWindowPlacement(&placeNew);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CString CWriteReadDlg::GetFileBasePathFromRegistry()
{
	CString sFileBasePath = "";

	char acFileBasePath[MAX_PATH];
	acFileBasePath[0] = 0;
	ReadRegistryString("Software\\Instrumental Systems\\IdCfgRom", "FileBaseDirectory", acFileBasePath, MAX_PATH);
	if( acFileBasePath[0] != 0 )
	{
		sFileBasePath = acFileBasePath;
	}
	else
	{
		sFileBasePath = GetCurDirFromCommandLine() + "ConfigBase\\";
	}

	return sFileBasePath;
}

void CWriteReadDlg::SetFileBasePathToRegistry(CString sFileBasePath)
{
	WriteRegistryString("Software\\Instrumental Systems\\IdCfgRom", "FileBaseDirectory", sFileBasePath);
}

void CWriteReadDlg::OnBnClickedSaveFileBin()
{
	// TODO: Add your control notification handler code here
	m_poIdCfgRomWindow->SaveBinThroughtDialog();
	
}

void CWriteReadDlg::OnBnClickedSaveFileHex()
{
	// TODO: Add your control notification handler code here
	m_poIdCfgRomWindow->SaveHexThroughtDialog();
}

void CWriteReadDlg::OnBnClickedReadFile()
{
	// TODO: Add your control notification handler code here
	m_poIdCfgRomWindow->ReadThroughDialog();
}

void CWriteReadDlg::OnBnClickedSaveBase()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sFilePath = MakeFilePathForFileBase();
	
	if( IsFileExist(m_sFileBaseDir, GetFileNameOfPath(sFilePath)) )
	{
		int nRes = AfxMessageBox("Файл с таким именем уже существует! Перезаписать этот файл?", MB_YESNO|MB_ICONQUESTION);
		if( nRes==IDNO )
			return;
		m_ctrlBase.SetSelectionMark(FindFileInFileBaseList());
	}
	else
	{
		AddRowToList(m_sWriteName, m_sWriteDevId, m_sWriteVer, m_sWriteZakaz, m_sWritePId, m_sWriteSurname, m_sWriteKeyword, m_sWriteDate);
		m_ctrlBase.SetSelectionMark(m_ctrlBase.GetItemCount()-1);
	}

	if(!IsDirExist(GetDirOfPath(sFilePath)))
		CreateDirectory(GetDirOfPath(sFilePath), NULL);
	m_poIdCfgRomWindow->SaveBin(sFilePath);

	m_ctrlReadBase.EnableWindow(TRUE);
	m_ctrlEditBase.EnableWindow(TRUE);
	m_ctrlDeleteBase.EnableWindow(TRUE);
}

int	CWriteReadDlg::IsFileExist(CString sSearchDir, CString sFileName)
{
	if( sSearchDir.GetAt(sSearchDir.GetLength()-1) != '\\' )
	sSearchDir.Append("\\");
	CString sSearchFilePath = sSearchDir + "*.*";
	HANDLE	hFind;
	WIN32_FIND_DATA	findData;
	hFind = FindFirstFile(sSearchFilePath, &findData);
	if( hFind != INVALID_HANDLE_VALUE )
	{
		do
		{
			CString sFoundFileName = findData.cFileName;
			if( (sFoundFileName.Compare(".") ==0 ) || (sFoundFileName.Compare("..") == 0) )
				continue;
			if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				CString	sSubSearchDir = sSearchDir + sFoundFileName;
				if( IsFileExist(sSubSearchDir, sFileName) )
					return 1;
			}
			if( IsCfgFile(sFoundFileName) )
			{
				if( sFileName.Compare(sFoundFileName) == 0 )
					return 1;
			}
		} while( FindNextFile(hFind, &findData) != 0 );
	}

	return 0;
}

int	CWriteReadDlg::IsDirExist(CString sSearchDir)
{
	if( sSearchDir.GetAt(sSearchDir.GetLength()-1) == '\\' )
		sSearchDir.Delete(sSearchDir.GetLength()-1);
	HANDLE	hFind;
	WIN32_FIND_DATA	findData;
	hFind = FindFirstFile(sSearchDir, &findData);
	if( hFind != INVALID_HANDLE_VALUE )
		return 1;
	else
		return 0;
}

void CWriteReadDlg::OnNMDblclkBase(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	OnBnClickedReadBase();
	*pResult = 0;
}

void CWriteReadDlg::OnBnClickedReadBase()
{
	// TODO: Add your control notification handler code here
	int nSelNum = m_ctrlBase.GetSelectionMark();
	m_poIdCfgRomWindow->ReadCfgFile(FindFilePathInFileBase(nSelNum));

	m_sWriteName = m_ctrlBase.GetItemText(nSelNum, 0);
	m_sWriteDevId = m_ctrlBase.GetItemText(nSelNum, 1);
	m_sWriteVer = m_ctrlBase.GetItemText(nSelNum, 2);
	m_sWriteZakaz = m_ctrlBase.GetItemText(nSelNum, 3);
	m_sWritePId = m_ctrlBase.GetItemText(nSelNum, 4);
	m_sWriteSurname = m_ctrlBase.GetItemText(nSelNum, 5);
	m_sWriteKeyword = m_ctrlBase.GetItemText(nSelNum, 6);
	m_sWriteDate = m_ctrlBase.GetItemText(nSelNum, 7);

	UpdateData(FALSE);
}

void CWriteReadDlg::OnBnClickedEditBase()
{
	// TODO: Add your control notification handler code here
	if( MessageBox("Вы уверены, что хотите изменить запись и перезаписать файл?", "IdCfgRom", MB_YESNO|MB_ICONQUESTION) != IDYES )
		return;

	UpdateData(TRUE);
	CString sFilePath = MakeFilePathForFileBase();
	int nFileExist = 0;
	if( IsFileExist(m_sFileBaseDir, GetFileNameOfPath(sFilePath)) )
	{
		int nRes = AfxMessageBox("Файл с таким именем уже существует! Перезаписать этот файл?", MB_YESNO|MB_ICONQUESTION);
		if( nRes==IDNO )
			return;
		nFileExist = 1;
	}

	int nSelNum = m_ctrlBase.GetSelectionMark();
	DeleteFile(FindFilePathInFileBase(nSelNum));

	if( nFileExist )
	{
		m_ctrlBase.DeleteItem(nSelNum);
		nSelNum = FindFileInFileBaseList();
		m_ctrlBase.SetSelectionMark(nSelNum);
		DeleteFile(FindFilePathInFileBase(nSelNum));
	}
	else
		EditRowInList(nSelNum, m_sWriteName, m_sWriteDevId, m_sWriteVer, m_sWriteZakaz, m_sWritePId, m_sWriteSurname, m_sWriteKeyword, m_sWriteDate);

	m_poIdCfgRomWindow->SaveBin(sFilePath);
}

void CWriteReadDlg::OnBnClickedDeleteBase()
{
	// TODO: Add your control notification handler code here
	vector <TDeleteFile>	vDeleteFiles;
	POSITION  pos = m_ctrlBase.GetFirstSelectedItemPosition();
	while( pos )
	{
		TDeleteFile rDeleteFile;
		int nFileIndex = m_ctrlBase.GetNextSelectedItem(pos);
		rDeleteFile.nIndex = nFileIndex;
		CString sFilePath = "";
		rDeleteFile.sFilePath = FindFilePathInFileBase(nFileIndex);
		vDeleteFiles.push_back(rDeleteFile);
	}

	if( DeleteFilesFromBase(vDeleteFiles) )
	{
		m_ctrlReadBase.EnableWindow(FALSE);
		m_ctrlEditBase.EnableWindow(FALSE);
		m_ctrlDeleteBase.EnableWindow(FALSE);
	}

	vDeleteFiles.clear();
}

CString CWriteReadDlg::FindFilePathInFileBase(int nFileIndex)
{
	CString sFileName = "{" + m_ctrlBase.GetItemText(nFileIndex, 0) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 1) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 2) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 3) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 4) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 5) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 6) + "}" +
						"{" + m_ctrlBase.GetItemText(nFileIndex, 7) + "}" +
						".bin";
	return FindFileInDir(m_sFileBaseDir, sFileName);
}

int CWriteReadDlg::FindFileInFileBaseList()
{
	for(int ii=0; ii<m_ctrlBase.GetItemCount(); ii++ )
	{
		if( (m_ctrlBase.GetItemText(ii, 0) == m_sWriteName) &&
			(m_ctrlBase.GetItemText(ii, 1) == m_sWriteDevId) &&
			(m_ctrlBase.GetItemText(ii, 2) == m_sWriteVer) &&
			(m_ctrlBase.GetItemText(ii, 3) == m_sWriteZakaz) &&
			(m_ctrlBase.GetItemText(ii, 4) == m_sWritePId) &&
			(m_ctrlBase.GetItemText(ii, 5) == m_sWriteSurname) &&
			(m_ctrlBase.GetItemText(ii, 6) == m_sWriteKeyword) &&
			(m_ctrlBase.GetItemText(ii, 7) == m_sWriteDate) )
			return ii;
	}
	return -1;
}

CString CWriteReadDlg::FindFileInDir(CString sSearchDir, CString sFileName)
{
	if( sSearchDir.GetAt(sSearchDir.GetLength()-1) != '\\' )
	sSearchDir.Append("\\");
	CString sSearchFilePath = sSearchDir + "*.*";
	HANDLE	hFind;
	WIN32_FIND_DATA	findData;
	hFind = FindFirstFile(sSearchFilePath, &findData);
	if( hFind != INVALID_HANDLE_VALUE )
	{
		do
		{
			CString sFoundFileName = findData.cFileName;
			if( (sFoundFileName.Compare(".") ==0 ) || (sFoundFileName.Compare("..") == 0) )
				continue;
			if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				CString	sSubSearchDir = sSearchDir + sFoundFileName;
				return FindFileInDir(sSubSearchDir, sFileName);
			}
			if( IsCfgFile(sFoundFileName) )
			{
				if( sFileName.Compare(sFoundFileName) == 0 )
					return sSearchDir + sFileName;
			}
		} while( FindNextFile(hFind, &findData) != 0 );
	}

	return "";
}

int CWriteReadDlg::DeleteFilesFromBase(vector <TDeleteFile>	vDeleteFiles)
{
	int nRes = IDNO;
	if( (int)vDeleteFiles.size()==1 )
		nRes = AfxMessageBox("Вы уверены, что хотите удалить выделенный файл?", MB_YESNO|MB_ICONQUESTION);
	else if( (int)vDeleteFiles.size()>1 )
		nRes = AfxMessageBox("Вы уверены, что хотите удалить выделенные файлы?", MB_YESNO|MB_ICONQUESTION);
	if( nRes!=IDYES )
		return 0;

	for( int ii=(int)vDeleteFiles.size()-1; ii>=0; ii-- )
	{
		DeleteFile(vDeleteFiles[ii].sFilePath);
		m_ctrlBase.DeleteItem(vDeleteFiles[ii].nIndex);
	}
	return 1;
}

CString CWriteReadDlg::MakeFilePathForFileBase()
{
	CString sFileName = "";

	sFileName = m_sFileBaseDir + 
				"{" + m_sWriteName + "}" + 
				"{" + m_sWriteDevId + "}" + 
				"{" + m_sWriteVer + "}" + 
				"{" + m_sWriteZakaz + "}" + 
				"{" + m_sWritePId + "}" + 
				"{" + m_sWriteSurname + "}" + 
				"{" + m_sWriteKeyword + "}" + 
				"{" + m_sWriteDate + "}" + 
				".bin";

	return sFileName;
}

// добавление строки в таблицу
void CWriteReadDlg::AddRowToList(CString sWriteName, CString sWriteDevId, CString sWriteVer, CString sWriteZakaz, 
								 CString sWritePId, CString sWriteSurname, CString sWriteKeyword, CString sWriteDate)
{
	LVITEM lvi;
	CString strItem;
	lvi.mask = LVIF_IMAGE | LVIF_TEXT;
	lvi.iItem = m_ctrlBase.GetItemCount();
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteName;
	int index = m_ctrlBase.InsertItem(&lvi);

	lvi.iItem = index;
	lvi.iSubItem = 1;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteDevId;
	m_ctrlBase.SetItem(&lvi);

	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteVer;
	m_ctrlBase.SetItem(&lvi);

	lvi.iSubItem = 3;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteZakaz;
	m_ctrlBase.SetItem(&lvi);

	lvi.iSubItem = 4;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWritePId;
	m_ctrlBase.SetItem(&lvi);

	lvi.iSubItem = 5;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteSurname;
	m_ctrlBase.SetItem(&lvi);

	lvi.iSubItem = 6;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteKeyword;
	m_ctrlBase.SetItem(&lvi);

	lvi.iSubItem = 7;
	lvi.pszText = (LPTSTR)(LPCTSTR)sWriteDate;
	m_ctrlBase.SetItem(&lvi);

	m_ctrlBase.SetItemData(index, index);
}

// изменение строки в таблице
void CWriteReadDlg::EditRowInList(int nItem, CString sWriteName, CString sWriteDevId, CString sWriteVer, CString sWriteZakaz, 
								 CString sWritePId, CString sWriteSurname, CString sWriteKeyword, CString sWriteDate)
{
	m_ctrlBase.SetItemText(nItem, 0, sWriteName);
	m_ctrlBase.SetItemText(nItem, 1, sWriteDevId);
	m_ctrlBase.SetItemText(nItem, 2, sWriteVer);
	m_ctrlBase.SetItemText(nItem, 3, sWriteZakaz);
	m_ctrlBase.SetItemText(nItem, 4, sWritePId);
	m_ctrlBase.SetItemText(nItem, 5, sWriteSurname);
	m_ctrlBase.SetItemText(nItem, 6, sWriteKeyword);
	m_ctrlBase.SetItemText(nItem, 7, sWriteDate);
}

void CWriteReadDlg::LoadFileBaseFromDir(CString sSearchDir, int nFilter)
{
	m_ctrlBase.DeleteAllItems();

	if( sSearchDir.GetAt(sSearchDir.GetLength()-1) != '\\' )
	sSearchDir.Append("\\");
	CString sSearchFilePath = sSearchDir + "*.*";
	HANDLE	hFind;
	WIN32_FIND_DATA	findData;
	hFind = FindFirstFile(sSearchFilePath, &findData);
	if( hFind == INVALID_HANDLE_VALUE )
		return;

	do
	{
		CString sFoundFileName = findData.cFileName;
		if( (sFoundFileName.Compare(".") ==0 ) || (sFoundFileName.Compare("..") == 0) )
			continue;
		if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			//CString	sSubSearchDir = sSearchDir + sFoundFileName;
			//LoadFileBaseFromDir(sSubSearchDir);
			continue;
		}
		if( IsCfgFile(sFoundFileName) )
		{
			if( nFilter && (Filter(sFoundFileName)==0) )
				continue;
			AddCfgFileToList(sFoundFileName);
		}
	} while( FindNextFile(hFind, &findData) != 0 );
}

int CWriteReadDlg::IsCfgFile(CString sFoundFileName)
{
	int nCurParamPos = 0;
	for(int ii=0; ii<CFG_FILE_PARAMS_CNT; ii++)
	{
		if( sFoundFileName.Find('{', nCurParamPos) < 0 )
			return 0;
		nCurParamPos = sFoundFileName.Find('{', nCurParamPos) + 1;
		if( sFoundFileName.Find('}', nCurParamPos) < 0 )
			return 0;
		nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	}

	return 1;
}

void CWriteReadDlg::AddCfgFileToList(CString sCfgFileName)
{
	CString sWriteName = "";
	CString sWriteDevId = "";
	CString sWriteVer = "";
	CString sWriteZakaz = "";
	CString sWritePId = "";
	CString sWriteSurname = "";
	CString sWriteKeyword = "";
	CString sWriteDate = "";
	int nCurParamPos = 0;
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteName = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteDevId = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteVer = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteZakaz = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWritePId = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteSurname = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteKeyword = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);
	nCurParamPos = sCfgFileName.Find('{', nCurParamPos) + 1;
	sWriteDate = sCfgFileName.Mid(nCurParamPos, sCfgFileName.Find('}', nCurParamPos) - nCurParamPos);

	AddRowToList(sWriteName, sWriteDevId, sWriteVer, sWriteZakaz, sWritePId, sWriteSurname, sWriteKeyword, sWriteDate);
}

void CWriteReadDlg::OnLvnColumnclickBase(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HDITEM	hItem;
	// если стрелка установлена на другой колонке, удаляем её
	if( (m_nLastClickedColumnNum != pNMLV->iSubItem) && (m_nLastClickedColumnNum != -1) )
	{
		m_ctrlBase.GetHeaderCtrl()->GetItem(m_nLastClickedColumnNum, &hItem);
		hItem.mask = HDI_FORMAT;
		hItem.fmt = HDF_STRING;
		m_ctrlBase.GetHeaderCtrl()->SetItem(m_nLastClickedColumnNum, &hItem);
		g_nLastArrowType = NO_ARROW;
	}
	
	// рисуем стрелку
	m_nLastClickedColumnNum = pNMLV->iSubItem;
	m_ctrlBase.GetHeaderCtrl()->GetItem(m_nLastClickedColumnNum, &hItem);
	hItem.mask = HDI_BITMAP | HDI_FORMAT;
	hItem.fmt = HDF_STRING | HDF_BITMAP | HDF_BITMAP_ON_RIGHT;
	if( g_nLastArrowType == ARROW_UP )
	{
		hItem.hbm = m_hDownArrow;
		g_nLastArrowType = ARROW_DOWN;
	}
	else
	{
		hItem.hbm = m_hUpArrow;
		g_nLastArrowType = ARROW_UP;
	}
	m_ctrlBase.GetHeaderCtrl()->SetItem(m_nLastClickedColumnNum, &hItem);

	// сортировка
	g_nSortColumnNum = pNMLV->iSubItem;

	// для даты отдельная функция сортировки
	int cnt = m_ctrlBase.GetHeaderCtrl()->GetItemCount();
	if( pNMLV->iSubItem == (cnt-1) )
		m_ctrlBase.SortItems(DateCompareFunc, (LPARAM)&m_ctrlBase);
	else
		m_ctrlBase.SortItems(CompareFunc, (LPARAM)&m_ctrlBase);

	*pResult = 0;
}

static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
            LPARAM lParamSort)
{
	CMyListCtrl*	pListCtrl = (CMyListCtrl*) lParamSort;
	LV_FINDINFO		a1;
	LV_FINDINFO		a2;

	a1.flags = LVFI_PARAM;
	a2.flags = LVFI_PARAM;
	a1.lParam = lParam1;
	a2.lParam = lParam2;

	CString	strItem1 = pListCtrl->GetItemText(pListCtrl->FindItem(&a1), g_nSortColumnNum);
	CString	strItem2 = pListCtrl->GetItemText(pListCtrl->FindItem(&a2), g_nSortColumnNum);
	
	if( g_nLastArrowType == ARROW_DOWN )
		return -strItem1.CompareNoCase(strItem2);
	else if( g_nLastArrowType == ARROW_UP )
		return strItem1.CompareNoCase(strItem2);

	return 0;
}

static int CALLBACK DateCompareFunc(LPARAM lParam1, LPARAM lParam2,
								LPARAM lParamSort)
{
	CMyListCtrl*	pListCtrl = (CMyListCtrl*) lParamSort;
	LV_FINDINFO		a1;
	LV_FINDINFO		a2;

	a1.flags = LVFI_PARAM;
	a2.flags = LVFI_PARAM;
	a1.lParam = lParam1;
	a2.lParam = lParam2;

	CString	strItem1 = pListCtrl->GetItemText(pListCtrl->FindItem(&a1), g_nSortColumnNum);
	CString	strItem2 = pListCtrl->GetItemText(pListCtrl->FindItem(&a2), g_nSortColumnNum);

	CString sYear1 = strItem1.Mid(strItem1.ReverseFind('.')+1);
	CString sYear2 = strItem2.Mid(strItem2.ReverseFind('.')+1);
	CString sMon1 = strItem1.Mid(strItem1.Find(".")+1);
	sMon1 = sMon1.Left(sMon1.Find("."));
	CString sMon2 = strItem2.Mid(strItem2.Find(".")+1);
	sMon2 = sMon2.Left(sMon2.Find("."));
	CString sDay1 = strItem1.Left(strItem1.Find("."));
	CString sDay2 = strItem2.Left(strItem2.Find("."));

	int comp = sYear1.Compare(sYear2);
	if( comp == 0 )
	{
		comp = sMon1.Compare(sMon2);
		if( comp == 0 )
		{
			comp = sDay1.Compare(sDay2);
		}
	}

	if( g_nLastArrowType == ARROW_DOWN )
		return -comp;
	else if( g_nLastArrowType == ARROW_UP )
		return comp;

	return 0;
}

void CWriteReadDlg::OnNMClickBase(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pItem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int nSelCnt = m_ctrlBase.GetSelectedCount();
	if( nSelCnt )
	{
		if( nSelCnt == 1 )
		{
			m_ctrlReadBase.EnableWindow();
			m_ctrlEditBase.EnableWindow();
		}
		else
		{
			m_ctrlReadBase.EnableWindow(FALSE);
			m_ctrlEditBase.EnableWindow(FALSE);
		}
		m_ctrlDeleteBase.EnableWindow();
	}
	else
	{
		m_ctrlReadBase.EnableWindow(FALSE);
		m_ctrlEditBase.EnableWindow(FALSE);
		m_ctrlDeleteBase.EnableWindow(FALSE);
	}

	*pResult = 0;
}

void CWriteReadDlg::OnLvnKeydownBase(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if( pLVKeyDow->wVKey == VK_DELETE )
		OnBnClickedDeleteBase();
	else
		return;
}

void CWriteReadDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_nCanResize = 0;

	CDialog::OnClose();
}

void CWriteReadDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	delete m_pFilterDlg;
}

void CWriteReadDlg::OnBnClickedFilter()
{
	// TODO: Add your control notification handler code here
	if( m_pFilterDlg )
	{
		if( !m_pFilterDlg->IsWindowVisible() )
			m_pFilterDlg->ShowWindow(SW_SHOW);
		return;
	}

	m_pFilterDlg = new CFileBaseFilterDlg();
	m_pFilterDlg->Create(IDD_FILE_BASE_FILTER, this);
	m_pFilterDlg->ShowWindow(SW_SHOW);

	m_ctrlReadBase.EnableWindow(FALSE);
	m_ctrlEditBase.EnableWindow(FALSE);
	m_ctrlDeleteBase.EnableWindow(FALSE);
}

int CWriteReadDlg::Filter(CString sFoundFileName)
{
	m_pFilterDlg->UpdateData(TRUE);
	
	CString sParam = "";
	int nCurParamPos = 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sName.MakeLower()) < 0 )
		return 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sDevId.MakeLower()) < 0 )
		return 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sVer.MakeLower()) < 0 )
		return 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sZakaz.MakeLower()) < 0 )
		return 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sPId.MakeLower()) < 0 )
		return 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sSurname.MakeLower()) < 0 )
		return 0;
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	nCurParamPos = sFoundFileName.Find('}', nCurParamPos) + 1;	
	if( sParam.MakeLower().Find(m_pFilterDlg->m_sKeyword.MakeLower()) < 0 )
		return 0;
	// Дата
	sParam = sFoundFileName.Mid(sFoundFileName.Find('{', nCurParamPos)+1, sFoundFileName.Find('}', nCurParamPos)-sFoundFileName.Find('{', nCurParamPos)-1);
	int nDay = atoi(sParam.Left(sParam.Find('.')));
	int nMonth = atoi(sParam.Mid(sParam.Find('.')+1, sParam.ReverseFind('.')-sParam.Find('.')-1));
	int nYear = atoi(sParam.Mid(sParam.ReverseFind('.')+1));
	int nDayStart = atoi(m_pFilterDlg->m_sDayStart);
	int nMonthStart = atoi(m_pFilterDlg->m_sMonthStart);
	int nYearStart = atoi(m_pFilterDlg->m_sYearStart);
	if( nDayStart && nMonthStart && nYearStart )
	{
		if( nYear<nYearStart )
			return 0;
		if( nYear==nYearStart )
		{
			if( nMonth<nMonthStart )
				return 0;
			if( nMonth==nMonthStart )
			{
				if( nDay<nDayStart )
					return 0;
			}
		}
	}
	
	int nDayEnd = atoi(m_pFilterDlg->m_sDayEnd);
	int nMonthEnd = atoi(m_pFilterDlg->m_sMonthEnd);
	int nYearEnd = atoi(m_pFilterDlg->m_sYearEnd);
	if( nDayEnd && nMonthEnd && nYearEnd )
	{
		if( nYear>nYearEnd )
			return 0;
		if( nYear==nYearEnd )
		{
			if( nMonth>nMonthEnd )
				return 0;
			if( nMonth==nMonthEnd )
			{
				if( nDay>nDayEnd )
					return 0;
			}
		}
	}

	return 1;
}

void CWriteReadDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if( m_nCanResize )
	{
		for( int ii=0; ii<(int)m_vItemsPositions.size(); ii++ )
		{
			MoveItemRelativePosition(m_vItemsPositions[ii]);
			if( ii==((int)m_vItemsPositions.size()-1) )
				this->RedrawWindow();
		}
	}
}

// Сохранение расположения элементов окна при запуске программы
void CWriteReadDlg::SaveItemPosition(CWnd* pWnd, int nID, int nRelationToParent)
{
	WINDOWPLACEMENT itemPlace;
	if( nRelationToParent == WINDOW )
		pWnd->GetWindowPlacement(&itemPlace);
	else
	{
		CWnd	*pItem = pWnd->GetDlgItem(nID);
		pItem->GetWindowPlacement(&itemPlace);
	}
	TItemPosition	rItemPosition;
	rItemPosition.nID = nID;
	int nDeltaLeft = -1;
	int nDeltaRight = -1;
	int nDeltaTop = -1;
	int nDeltaBottom = -1;
	rItemPosition.nWidth = itemPlace.rcNormalPosition.right - itemPlace.rcNormalPosition.left;
	rItemPosition.nHeight = itemPlace.rcNormalPosition.bottom - itemPlace.rcNormalPosition.top;
	switch( nRelationToParent )
	{
	case TOP_LEFT:
		break;
	case TOP_RIGHT:
		nDeltaRight = m_nDefaultDialogRight - itemPlace.rcNormalPosition.right - m_nDefaultDialogLeft;
		break;
	case BOTTOM_LEFT:
		nDeltaBottom = m_nDefaultDialogBottom - itemPlace.rcNormalPosition.bottom - m_nDefaultDialogTop;
		break;
	case BOTTOM_RIGHT:
	case FIELD:
	case WINDOW:
	case BOTTOM:
		nDeltaRight = m_nDefaultDialogRight - itemPlace.rcNormalPosition.right - m_nDefaultDialogLeft;
		nDeltaBottom = m_nDefaultDialogBottom - itemPlace.rcNormalPosition.bottom - m_nDefaultDialogTop;
		break;
	}
	rItemPosition.nDeltaLeft = nDeltaLeft;
	rItemPosition.nDeltaRight = nDeltaRight;
	rItemPosition.nDeltaTop = nDeltaTop;
	rItemPosition.nDeltaBottom = nDeltaBottom;
	rItemPosition.nRelationToParent = nRelationToParent;
	rItemPosition.pWnd = pWnd;
	m_vItemsPositions.push_back(rItemPosition);
}

// Относительный сдвиг всех элементов окна при изменении места расположения
void CWriteReadDlg::MoveItemRelativePosition(TItemPosition rItemPosition)
{
	RECT	rect;
	GetWindowRect(&rect);
	WINDOWPLACEMENT itemPlace;
	CWnd	*pItem = (CWnd*)0;
	if( rItemPosition.nRelationToParent == WINDOW )
		rItemPosition.pWnd->GetWindowPlacement(&itemPlace);
	else
	{
		pItem = rItemPosition.pWnd->GetDlgItem(rItemPosition.nID);
		pItem->GetWindowPlacement(&itemPlace);
	}
	switch( rItemPosition.nRelationToParent )
	{
	case TOP_LEFT:
		break;
	case TOP_RIGHT:
		itemPlace.rcNormalPosition.right = rect.right - rItemPosition.nDeltaRight - rect.left;
		itemPlace.rcNormalPosition.left = itemPlace.rcNormalPosition.right - rItemPosition.nWidth;
		break;
	case BOTTOM_LEFT:
		itemPlace.rcNormalPosition.bottom = rect.bottom - rItemPosition.nDeltaBottom - rect.top;
		itemPlace.rcNormalPosition.top = itemPlace.rcNormalPosition.bottom - rItemPosition.nHeight;
		break;
	case BOTTOM_RIGHT:
		itemPlace.rcNormalPosition.right = rect.right - rItemPosition.nDeltaRight - rect.left;
		itemPlace.rcNormalPosition.bottom = rect.bottom - rItemPosition.nDeltaBottom - rect.top;
		itemPlace.rcNormalPosition.left = itemPlace.rcNormalPosition.right - rItemPosition.nWidth;
		itemPlace.rcNormalPosition.top = itemPlace.rcNormalPosition.bottom - rItemPosition.nHeight;
		break;
	case FIELD:
	case WINDOW:
		itemPlace.rcNormalPosition.right = rect.right - rItemPosition.nDeltaRight - rect.left;
		itemPlace.rcNormalPosition.bottom = rect.bottom - rItemPosition.nDeltaBottom - rect.top;
		break;
	case BOTTOM:
		itemPlace.rcNormalPosition.right = rect.right - rItemPosition.nDeltaRight - rect.left;
		itemPlace.rcNormalPosition.bottom = rect.bottom - rItemPosition.nDeltaBottom - rect.top;
		itemPlace.rcNormalPosition.top = itemPlace.rcNormalPosition.bottom - rItemPosition.nHeight;
		break;
	}
	
	pItem->SetWindowPlacement(&itemPlace);
	pItem->RedrawWindow();
}

void CWriteReadDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMinTrackSize.x = 401;
	lpMMI->ptMinTrackSize.y = 740*2/3;

	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CWriteReadDlg::OnBnClickedFileBasePath()
{
	BROWSEINFO bi;
	bi.hwndOwner = 0;
	bi.pidlRoot = NULL;//ConvertPathToLpItemIdList("C:\\JenyaWork\\_ICR\\");
	char pszBuffer[MAX_PATH];
	bi.pszDisplayName = pszBuffer;
	bi.lpszTitle = "Выбирите директорию базы файлов";
	bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	
	LPITEMIDLIST pidl;
	if( (pidl = ::SHBrowseForFolder(&bi)) == NULL )
		return;

	char acFileBaseDir[MAX_PATH];
	if( ::SHGetPathFromIDList(pidl, acFileBaseDir) == FALSE )
		return;

	m_sFileBaseDir = acFileBaseDir;
	if (m_sFileBaseDir.GetAt(m_sFileBaseDir.GetLength() - 1) != '\\')
	{
		m_sFileBaseDir += "\\";
	}

	UpdateData(FALSE);
	LoadFileBaseFromDir(m_sFileBaseDir);

	SetFileBasePathToRegistry(m_sFileBaseDir);
}

LPITEMIDLIST CWriteReadDlg::ConvertPathToLpItemIdList(const char *pszPath)
{
	LPITEMIDLIST  pidl;
	LPSHELLFOLDER pDesktopFolder;
	OLECHAR       olePath[MAX_PATH];
	ULONG         chEaten;
	ULONG         dwAttributes;
	HRESULT       hr;

	if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
	{
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszPath, -1, olePath, 
			MAX_PATH);
		hr = pDesktopFolder->ParseDisplayName(NULL,NULL,olePath,&chEaten,
			&pidl,&dwAttributes);
		pDesktopFolder->Release();
	}
	return pidl;
}
