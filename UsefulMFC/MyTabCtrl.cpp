// MyTabCtrl.cpp : implementation file
//
/////////////////////////////////////////////////////
// This class is provided as is and Ben Hill takes no
// responsibility for any loss of any kind in connection
// to this code.
/////////////////////////////////////////////////////
// Is is meant purely as a educational tool and may
// contain bugs.
/////////////////////////////////////////////////////
// ben@shido.fsnet.co.uk
// http://www.shido.fsnet.co.uk
/////////////////////////////////////////////////////
// Thanks to a mystery poster in the C++ forum on 
// www.codeguru.com I can't find your name to say thanks
// for your Control drawing code. If you are that person 
// thank you very much. I have been able to use some of 
// you ideas to produce this sample application.
/////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl

CMyTabCtrl::CMyTabCtrl()
{
//	m_crSelected = 0;
//	m_crDisabled = 0;
//	m_crNormal = 0;

//	m_bColorSelected  = false;
//	m_bColorDisabled  = false;
//	m_bColorNormal    = false;
}

CMyTabCtrl::~CMyTabCtrl()
{
//	for(int nCount=0; nCount < m_nNumberOfPages; nCount++){
//		delete m_tabPages[nCount];
//	}
}

void CMyTabCtrl::AddTab(CWnd* pWnd, LPTSTR lpszCaption)
{
//	m_tabCurrent=0;

	int nTab = GetItemCount();
	TCITEM item;
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.lParam = (LPARAM) pWnd;
	item.pszText = lpszCaption;
	InsertItem(nTab, &item);

	SetRectangle(pWnd);
	pWnd->ShowWindow(nTab ? SW_HIDE : SW_SHOW);
//	ASSERT_VALID(pWnd);
	pWnd->Invalidate();
}

void CMyTabCtrl::SetRectangle(CWnd* pWnd)
{
	CRect tabParentWndRect, tabWndRect, tabRect, itemRect;
	int nX, nY/*, nXc, nYc*/;

	CWnd* pParentWnd = GetParent();
	pParentWnd->GetWindowRect(&tabParentWndRect);

	GetWindowRect(&tabWndRect);
	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

//	nX = itemRect.left; // left
//	nY = itemRect.bottom + 1; // top
	nX = itemRect.left + (tabWndRect.left - tabParentWndRect.left); // left
	nY = (tabWndRect.top - tabParentWndRect.top) - 1;// + 1; // top
//	nXc = tabRect.right - itemRect.left - 1; // width
//	nYc = tabRect.bottom - nY - 1; // hight

	pWnd->SetWindowPos(NULL, nX, nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
//	pWnd->SetWindowPos(NULL, nX, nY, nXc, nYc, SWP_NOZORDER);
}
/*
void CMyTabCtrl::ChangeTab(int iIndex, CWnd *pWnd, LPTSTR lpszCaption)
{
	ASSERT_VALID(pWnd);

	TCITEM item;
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.lParam = (LPARAM) pWnd;
	item.pszText = lpszCaption;

	//** update item 
	VERIFY(SetItem(iIndex, &item));

	SetRectangle(pWnd);
//	pWnd->SetWindowPos(NULL, m_ptTabs.x, m_ptTabs.y , 0, 0,
//						SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	
	pWnd->ShowWindow(SW_HIDE);

	//** the initial status is enabled
//	m_arrayStatusTab[iIndex] = TRUE; 

	//** updates the screen
//	GetItem(GetCurSel(), &item);
//	((CWnd*)item.lParam)->ShowWindow(SW_SHOW);
	int nTab = GetCurSel();
	//** show the selected tab --------
	GetItem(nTab, &item);
	CWnd* pCurWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pCurWnd);
	pCurWnd->ShowWindow(SW_SHOW);
	pCurWnd->Invalidate();
}

void CMyTabCtrl::DeleteTab(int iIndex)
{
	ASSERT(iIndex < GetItemCount());

	DeleteItem(iIndex);
	//** updates the screen
	int nTab = GetCurSel();
	TCITEM item;
	item.mask = TCIF_PARAM;
	//** show the selected tab --------
	GetItem(nTab, &item);
	CWnd* pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	pWnd->Invalidate();
//	Invalidate();
//	pWnd->UpdateWindow();
//	pWnd->ShowWindow(SW_SHOW);
}
*/
BOOL CMyTabCtrl::SelectTab(int iIndex)
{
	ASSERT(iIndex < GetItemCount());

	if (GetCurSel() == iIndex)
		return TRUE;

	//** check if the tab is enabled --------
//	if (m_arrayStatusTab[iIndex])
//	{
		TCITEM item;
		CWnd* pWnd;
		item.mask = TCIF_PARAM;

		GetItem(GetCurSel(), &item);
		pWnd = reinterpret_cast<CWnd*> (item.lParam);
		ASSERT_VALID(pWnd);
		pWnd->ShowWindow(SW_HIDE);

		SetCurSel(iIndex);
		GetItem(iIndex, &item);
		pWnd = reinterpret_cast<CWnd*> (item.lParam);
		ASSERT_VALID(pWnd);
		pWnd->ShowWindow(SW_SHOW);

		return TRUE;
//	}

//	return FALSE;
}
/*
BOOL CMyTabCtrl::ShowCurTab()
{
	TCITEM item;
	CWnd* pWnd;
	item.mask = TCIF_PARAM;

	GetItem(GetCurSel(), &item);
	pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	pWnd->ShowWindow(SW_SHOW);

	return TRUE;
}

BOOL CMyTabCtrl::HideCurTab()
{
	TCITEM item;
	CWnd* pWnd;
	item.mask = TCIF_PARAM;

	GetItem(GetCurSel(), &item);
	pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	pWnd->ShowWindow(SW_HIDE);

	return TRUE;
}
*/
BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, OnSelchanging)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers

void CMyTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nTab = GetCurSel();
	TCITEM item;
	item.mask = TCIF_PARAM;
	//** show the selected tab --------
	GetItem(nTab, &item);
	CWnd* pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	pWnd->ShowWindow(SW_SHOW);
	pWnd->SetFocus();
//	pWnd->SetActiveWindow();
//	pWnd->Invalidate();
	CWnd* pParentWnd = GetOwner();
	::SendMessage(pParentWnd->m_hWnd, // handle to destination window
					WM_MY_TAB_MESSAGE, // message
						0, // first message parameter
						0  // second message parameter
						);

	*pResult = 0;
}

void CMyTabCtrl::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nTab = GetCurSel();
	TCITEM item;
	item.mask = TCIF_PARAM;
	//** hide the current tab ---------
	GetItem(nTab, &item);
	CWnd* pWnd = reinterpret_cast<CWnd*> (item.lParam);
	ASSERT_VALID(pWnd);
	pWnd->ShowWindow(SW_HIDE);
//	pWnd->ShowWindow(SW_SHOW);

	*pResult = 0;
}
/*
HBRUSH CMyTabCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CTabCtrl::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
    // Set the text color to red
    pDC->SetBkColor(RGB(255, 0, 0));

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}*/
//void CMyTabCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
/*void CMyTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	int nTabIndex = lpDrawItemStruct->itemID;
	
	if (nTabIndex < 0) return;

	BOOL bSelected = (nTabIndex == GetCurSel());

	COLORREF crSelected = m_bColorSelected ? m_crSelected : GetSysColor(COLOR_BTNTEXT);
	COLORREF crNormal  = m_bColorNormal   ? m_crNormal   : GetSysColor(COLOR_BTNTEXT);
	COLORREF crDisabled = m_bColorDisabled ? m_crDisabled : GetSysColor(COLOR_GRAYTEXT);


	char label[64];
	TC_ITEM item;
//	item.mask = TCIF_TEXT|TCIF_IMAGE;
	item.mask = TCIF_TEXT;
	item.pszText = label;     
	item.cchTextMax = 63;    	
	if (!GetItem(nTabIndex, &item))
		return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	if (!pDC)
		return;

	int nSavedDC = pDC->SaveDC();

	CRect rect = lpDrawItemStruct->rcItem;
	rect.top -= ::GetSystemMetrics(SM_CYEDGE);
//	if (!IsTabEnabled(nTabIndex))
//	{
//		pDC->SetTextColor(crDisabled);
//	}
//	else
	{
		//** selected item -----
		if (bSelected)
		{
			pDC->SetTextColor(crSelected);
//			pDC->DrawText(label, rect, DT_SINGLELINE|DT_BOTTOM|DT_CENTER);
//			pDC->DrawText(label, rect, DT_SINGLELINE|DT_TOP|DT_CENTER);
			pDC->DrawText(label, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		}
		else //** other item ---
		{
//			if (m_bColorMouseOver && nTabIndex == m_iIndexMouseOver) 
//				pDC->SetTextColor(m_crMouseOver);	
//			else
				pDC->SetTextColor(crNormal);
//				pDC->DrawText(label, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
				pDC->DrawText(label, rect, DT_SINGLELINE|DT_BOTTOM|DT_CENTER);
		}
	}

	pDC->RestoreDC(nSavedDC);
	
//	CTabCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
//	CTabCtrl::DrawItem(lpDrawItemStruct);
}

/*void CMyTabCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CTabCtrl::PreSubclassWindow();
	ModifyStyle(0, TCS_OWNERDRAWFIXED);
}

void CMyTabCtrl::SetDisabledColor(COLORREF cr) 
{
	m_bColorDisabled = true;
	m_crDisabled = cr;
}

void CMyTabCtrl::SetSelectedColor(COLORREF cr)
{
	m_bColorSelected = true;
	m_crSelected = cr;
}


void CMyTabCtrl::SetNormalColor(COLORREF cr)
{
	m_bColorNormal = true;
	m_crNormal = cr;
}
*/