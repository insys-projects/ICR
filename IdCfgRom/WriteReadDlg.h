#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyListCtrl.h"
#include "FileBaseFilterDlg.h"

#include <vector>
using namespace std;

#define	FILEBASEDIR	"ConfigBase\\"
#define	CFG_FILE_PARAMS_CNT	8

enum
{
	NO_ARROW,
	ARROW_UP,
	ARROW_DOWN,
};

enum
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	FIELD,
	WINDOW,
	BOTTOM,
};

struct TDeleteFile
{
	int		nIndex;
	CString	sFilePath;
};

struct TItemPosition
{
	int	nID;
	int nWidth;
	int nHeight;
	int nDeltaLeft;
	int nDeltaRight;
	int nDeltaTop;
	int nDeltaBottom;
	int nRelationToParent;
	CWnd	*pWnd;
};

// CWriteReadDlg dialog

class CWriteReadDlg : public CDialog
{
	DECLARE_DYNAMIC(CWriteReadDlg)

public:
	CWriteReadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWriteReadDlg();

// Dialog Data
	enum { IDD = IDD_WRITE_READ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveFileBin();
	afx_msg void OnBnClickedSaveFileHex();
	afx_msg void OnBnClickedReadFile();
	afx_msg void OnBnClickedSaveBase();
	afx_msg void OnNMDblclkBase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedReadBase();
	afx_msg void OnBnClickedEditBase();
	afx_msg void OnBnClickedDeleteBase();
	afx_msg void OnLvnColumnclickBase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickBase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownBase(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFilter();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CMyListCtrl m_ctrlBase;
	CEdit m_ctrlSurname;
	CButton m_ctrlSaveBase;
	CButton m_ctrlReadBase;
	CButton m_ctrlEditBase;
	CButton m_ctrlDeleteBase;
	HBITMAP m_hUpArrow;
	HBITMAP m_hDownArrow;

	CString m_sWriteName;
	CString m_sWriteDevId;
	CString m_sWriteVer;
	CString m_sWriteZakaz;
	CString m_sWritePId;
	CString m_sWriteSurname;
	CString m_sWriteKeyword;
	CString m_sWriteDate;

	int		m_nLastClickedColumnNum;
	CFileBaseFilterDlg	*m_pFilterDlg;

	int	m_nDefaultDialogLeft;
	int	m_nDefaultDialogRight;
	int	m_nDefaultDialogTop;
	int	m_nDefaultDialogBottom;
	int	m_nCanResize;
	vector <TItemPosition> m_vItemsPositions;
	
	int		IsFileExist(CString sSearchDir, CString sFileName);
	int		IsDirExist(CString sSearchDir);
	CString	MakeFilePathForFileBase();
	void	AddRowToList(CString sWriteName, CString sWriteDevId, CString sWriteVer, CString sWriteZakaz, 
							CString sWritePId, CString sWriteSurname, CString sWriteKeyword, CString sWriteDate);
	void	EditRowInList(int nItem, CString sWriteName, CString sWriteDevId, CString sWriteVer, CString sWriteZakaz, 
							CString sWritePId, CString sWriteSurname, CString sWriteKeyword, CString sWriteDate);

	// заполнить список файлами из базы
	void	LoadFileBaseFromDir(CString sSearchDir, int nFilter = 0);
	int		IsCfgFile(CString sFoundFileName);
	// добавить один файл в список
	void	AddCfgFileToList(CString sCfgFileName);
	// найти файл таблицы в базе
	CString FindFilePathInFileBase(int nIndex);
	// найти файл в таблице
	int FindFileInFileBaseList();
	// найти файл в директории
	CString FindFileInDir(CString sSearchDir, CString sFileName);
	// удалить файлы из базы
	int DeleteFilesFromBase(vector <TDeleteFile>	vDeleteFiles);
	// фильтрация файла
	int Filter(CString sFoundFileName);
	// две функции для изменения размера окна
	void SaveItemPosition(CWnd* pWnd, int nID, int nRelativeCorner);
	void MoveItemRelativePosition(TItemPosition rItemPosition);

	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};

static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2,
            LPARAM lParamSort);

static int CALLBACK DateCompareFunc(LPARAM lParam1, LPARAM lParam2,
								LPARAM lParamSort);
