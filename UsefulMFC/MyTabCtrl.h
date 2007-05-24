#if !defined(AFX_MYTABCTRL_H__F3E8650F_019C_479F_9E0F_60FE1181F49F__INCLUDED_)
#define AFX_MYTABCTRL_H__F3E8650F_019C_479F_9E0F_60FE1181F49F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl window
#define WM_MY_TAB_MESSAGE WM_USER+1

class CMyTabCtrl : public CTabCtrl
{
// Construction
public:
	CMyTabCtrl();
//	CDialog *m_tabPages[3];
//	int m_tabCurrent;
//	int m_nNumberOfPages;

// Attributes
public:

// Operations
public:
	void AddTab(CWnd* pWnd, LPTSTR lpszCaption);
//	void DeleteTab(int iIndex);
//	void ChangeTab(int iIndex, CWnd *pWnd, LPTSTR lpszCaption);
	BOOL SelectTab(int iIndex);
//	BOOL ShowCurTab();
//	BOOL HideCurTab();

//	void SetDisabledColor(COLORREF cr);
//	void SetSelectedColor(COLORREF cr);
//	void SetNormalColor(COLORREF cr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTabCtrl();

	// Generated message map functions
protected:
	void SetRectangle(CWnd* pWnd);

//	COLORREF m_crSelected;
//	COLORREF m_crDisabled;
//	COLORREF m_crNormal;

//	bool m_bColorNormal;
//	bool m_bColorDisabled;
//	bool m_bColorSelected;
	//{{AFX_MSG(CMyTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTABCTRL_H__F3E8650F_019C_479F_9E0F_60FE1181F49F__INCLUDED_)
