#pragma once

#pragma warning (disable:4996)

#include "icr.h"
#include "afxwin.h"

UINT const MAX_NUMOFADMIF = 4;
UINT const MAX_NUMOFSDRAM = 4;

#define AMBPCI_CFGMEM_SIZE 256
//#define AMBPCI_CFGMEM_SIZE 128

// CAmbPage dialog

class CAmbPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAmbPage)

public:
	CAmbPage();
	virtual ~CAmbPage();

	ULONG SetDataIntoDlg(PVOID pCfgMem);
	ULONG SetComment(PVOID pCfgMem);
	ULONG GetDataFromDlg(PVOID pCfgMem);
	void SetBMTypeData(); 

// Dialog Data
	enum { IDD = IDD_PP_AMB };
	UINT	m_SerialNum;
	UINT	m_NumOfAdmIf;
	CSpinButtonCtrl	m_ctrlSpinAdmIf;
	int		m_BMType;
	CString m_strAmbVersion;
	CString m_sComment;

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
//	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusNumofadmif();
	afx_msg void OnSelchangeBmtype();
	afx_msg void OnAmbext();
	afx_msg void OnDestroy();
	afx_msg void OnKillfocusAmbversion();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnDeltaposSpinadmif(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnEnKillfocusComment();
public:
	afx_msg void OnEnChangeSerialnum();
public:
	afx_msg void OnEnChangeAmbversion();
public:
	CComboBox m_ctrlType;
public:
	CEdit m_ctrlAdmNum;
};
