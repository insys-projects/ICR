// FileBaseFilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "FileBaseFilterDlg.h"
#include "WriteReadDlg.h"


// CFileBaseFilterDlg dialog

IMPLEMENT_DYNAMIC(CFileBaseFilterDlg, CDialog)

CFileBaseFilterDlg::CFileBaseFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileBaseFilterDlg::IDD, pParent)
	, m_sName(_T(""))
	, m_sDevId(_T(""))
	, m_sVer(_T(""))
	, m_sZakaz(_T(""))
	, m_sPId(_T(""))
	, m_sSurname(_T(""))
	, m_sKeyword(_T(""))
	, m_sDayStart(_T(""))
	, m_sMonthStart(_T(""))
	, m_sYearStart(_T(""))
	, m_sDayEnd(_T(""))
	, m_sMonthEnd(_T(""))
	, m_sYearEnd(_T(""))
{

}

CFileBaseFilterDlg::~CFileBaseFilterDlg()
{
}

void CFileBaseFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDX_Text(pDX, IDC_DEVID, m_sDevId);
	DDX_Text(pDX, IDC_VER, m_sVer);
	DDX_Text(pDX, IDC_ZAKAZ, m_sZakaz);
	DDX_Text(pDX, IDC_PID, m_sPId);
	DDX_Text(pDX, IDC_SURNAME, m_sSurname);
	DDX_Text(pDX, IDC_KEYWORD, m_sKeyword);
	DDX_Text(pDX, IDC_DAY_START, m_sDayStart);
	DDX_Text(pDX, IDC_MONTH_START, m_sMonthStart);
	DDX_Text(pDX, IDC_YEAR_START, m_sYearStart);
	DDX_Text(pDX, IDC_DAY_END, m_sDayEnd);
	DDX_Text(pDX, IDC_MONTH_END, m_sMonthEnd);
	DDX_Text(pDX, IDC_YEAR_END, m_sYearEnd);
}


BEGIN_MESSAGE_MAP(CFileBaseFilterDlg, CDialog)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_NAME, &CFileBaseFilterDlg::OnEnChangeName)
	ON_EN_CHANGE(IDC_DEVID, &CFileBaseFilterDlg::OnEnChangeDevid)
	ON_EN_CHANGE(IDC_VER, &CFileBaseFilterDlg::OnEnChangeVer)
	ON_EN_CHANGE(IDC_ZAKAZ, &CFileBaseFilterDlg::OnEnChangeZakaz)
	ON_EN_CHANGE(IDC_PID, &CFileBaseFilterDlg::OnEnChangePid)
	ON_EN_CHANGE(IDC_SURNAME, &CFileBaseFilterDlg::OnEnChangeSurname)
	ON_EN_CHANGE(IDC_KEYWORD, &CFileBaseFilterDlg::OnEnChangeKeyword)
	ON_EN_CHANGE(IDC_DAY_START, &CFileBaseFilterDlg::OnEnChangeDayStart)
	ON_EN_CHANGE(IDC_MONTH_START, &CFileBaseFilterDlg::OnEnChangeMonthStart)
	ON_EN_CHANGE(IDC_YEAR_START, &CFileBaseFilterDlg::OnEnChangeYearStart)
	ON_EN_CHANGE(IDC_DAY_END, &CFileBaseFilterDlg::OnEnChangeDayEnd)
	ON_EN_CHANGE(IDC_MONTH_END, &CFileBaseFilterDlg::OnEnChangeMonthEnd)
	ON_EN_CHANGE(IDC_YEAR_END, &CFileBaseFilterDlg::OnEnChangeYearEnd)
END_MESSAGE_MAP()


// CFileBaseFilterDlg message handlers

void CFileBaseFilterDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}

void CFileBaseFilterDlg::OnEnChangeName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeDevid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeVer()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeZakaz()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangePid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeSurname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeKeyword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeDayStart()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeMonthStart()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeYearStart()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeDayEnd()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeMonthEnd()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}

void CFileBaseFilterDlg::OnEnChangeYearEnd()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWriteReadDlg	*pParentWnd = (CWriteReadDlg*)GetOwner();
	pParentWnd->LoadFileBaseFromDir(GetCurDirFromCommandLine() + FILEBASEDIR, 1);
}
