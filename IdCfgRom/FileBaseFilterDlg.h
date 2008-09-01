#pragma once


// CFileBaseFilterDlg dialog

class CFileBaseFilterDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileBaseFilterDlg)

public:
	CFileBaseFilterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileBaseFilterDlg();

// Dialog Data
	enum { IDD = IDD_FILE_BASE_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnEnChangeName();
	afx_msg void OnEnChangeDevid();
	afx_msg void OnEnChangeVer();
	afx_msg void OnEnChangePid();
	afx_msg void OnEnChangeZakaz();
	afx_msg void OnEnChangeSurname();
	afx_msg void OnEnChangeKeyword();
	afx_msg void OnEnChangeDayStart();
	afx_msg void OnEnChangeMonthStart();
	afx_msg void OnEnChangeYearStart();
	afx_msg void OnEnChangeDayEnd();
	afx_msg void OnEnChangeMonthEnd();
	afx_msg void OnEnChangeYearEnd();

	CString m_sName;
	CString m_sDevId;
	CString m_sVer;
	CString m_sZakaz;
	CString m_sPId;
	CString m_sSurname;
	CString m_sKeyword;
	CString m_sDayStart;
	CString m_sMonthStart;
	CString m_sYearStart;
	CString m_sDayEnd;
	CString m_sMonthEnd;
	CString m_sYearEnd;
};
