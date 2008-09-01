#pragma once

// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

	CMapStringToString m_ToolTipMap; 
	WORD m_wHitMask;
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
    virtual BOOL DeleteAllItems( );
    virtual BOOL DeleteItem( int nItem );
	WORD SetToolTipHitMask(WORD wHitMask);
	virtual void DeleteAllToolTips();
	virtual BOOL SetItemToolTipText( int nItem, int nSubItem, LPCTSTR lpszToolTipText ); 
	virtual CString GetItemToolTipText( int nItem, int nSubItem ); 
	virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ); 

protected:
	DECLARE_MESSAGE_MAP()
};


