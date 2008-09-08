#pragma once

#include "icr.h"

UINT const MAX_ADMID = 4;

#define NONADM_CFGMEM_SIZE 2

// CAdmPage dialog

class CAdmPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAdmPage)

public:
	CAdmPage();
//	virtual ~CAdmPage();

	ULONG SetDataIntoDlg(PVOID pCfgMem);
	ULONG SetComment(PVOID pCfgMem);
	ULONG GetDataFromDlg(PVOID pCfgMem, UINT num);
	void SetSMTypeData(); 
	void SetMaxAdm(int maxAdm);

	void SetIdDataIntoDlg(PICR_IdAdm pAdmId, PICR_IdComment pCommentId);
	void GetIdDataFromDlg(PICR_IdAdm pAdmId, PICR_IdComment pCommentId, UINT num);
// Dialog Data
	enum { IDD = IDD_PP_ADM };
	UINT	m_nAdmNum;
	int		m_nAdmType;
	CString m_strAdmVersion;
	UINT	m_nAdmPID;
	CString m_sComment;

protected:
	ICR_IdAdm m_AdmId[MAX_ADMID];
	ICR_IdComment m_CommentId[MAX_ADMID];
	int m_AdmIdMax;
	
	void ChangeAdmNum();
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	virtual BOOL OnInitDialog();
//	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	afx_msg void OnKillfocusAdmnum();
	afx_msg void OnAdmcfg();
	afx_msg void OnKillfocusAdmversion();
	afx_msg void OnKillfocusAdmpid();
	afx_msg void OnSelchangeAdmtype();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnEnKillfocusComment();
public:
	afx_msg void OnEnChangeAdmpid();
public:
	afx_msg void OnEnChangeAdmversion();
};
