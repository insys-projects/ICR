#pragma once

// CSplash dialog

class CSplash : public CDialog
{
	DECLARE_DYNAMIC(CSplash)

public:
	CSplash(CWnd* pParent = NULL);   // standard constructor
//	virtual ~CAbout();
	void Create();
// Dialog Data
	enum { IDD = IDD_SPLASHSCREEN };

protected:
	//CHyperLink* m_pHlWWW;
	//CHyperLink* m_pHlEmail;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//virtual BOOL OnInitDialog();
	//afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};
