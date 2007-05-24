// NumEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NumEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumEdit

CNumEdit::CNumEdit()
{
}

CNumEdit::~CNumEdit()
{
}


BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	//{{AFX_MSG_MAP(CNumEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumEdit message handlers

void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString Holder = "`~!@#$%^&*()_+|=\\qwertyuiop[]asdfghjkl;'zxcvbnm,/QWERTYUIOP{}ASDFGHJKL:/ZXCVBNM<>?/";

	// 1st pass on unwanted characters
	if (Holder.Find(nChar) != -1)
		return;


	// length, selection info
	int num_typed = CEdit::GetWindowTextLength();
	int start_char, end_char;
	GetSel(start_char, end_char);

	// current CEdit text
	CString temp_str;
	GetWindowText(temp_str);

	// state variables
	bool  bSignTyped   = false;
	bool  bPeriodTyped = false;
	TCHAR temp_char;

	// most of the work done in here..
	for (int i=0; i<temp_str.GetLength(); i++) 
	{
		// selected chars don't count..
		if ((i>=start_char) && (i<end_char))
			continue;

		temp_char = temp_str[i];

		if ((temp_char == '+') || (temp_char == '-')) {
			bSignTyped = true;
		} else if (temp_char == '.') {
			bPeriodTyped = true;
		}
	}

	// allow sign only once (first char)
	if ((nChar == '+') || (nChar == '-')) {
		if (bSignTyped || (start_char != 0))
			return;
	}

	// allow period only once
	if ((nChar == '.') && bPeriodTyped)
		return;

//	CEdit::OnChar(nChar, nRepCnt, nFlags);

	CString old_str;
	GetWindowText(old_str);
	CEdit::OnChar(nChar, nRepCnt, nFlags);

	// check validity (if the user inserted numbers before the sign for example)
	GetWindowText(temp_str);
	if ( (temp_str.GetLength() > 1) && ( (temp_str[1] == '-') || (temp_str[1] == '+') ) )
	{
		this->SetWindowText( old_str );
	}
}
