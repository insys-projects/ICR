#pragma once

#include "HyperLink.h"

// CAbout dialog

class CAbout : public CDialog
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // standard constructor
//	virtual ~CAbout();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	CHyperLink* m_pHlWWW;
	CHyperLink* m_pHlEmail;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};
