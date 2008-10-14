// NumSpinCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "NumSpinCtrl.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumSpinCtrl

//IMPLEMENT_DYNAMIC(CNumSpinCtrl, CSpinButtonCtrl)

CNumSpinCtrl::CNumSpinCtrl()
{
}

CNumSpinCtrl::~CNumSpinCtrl()
{
}


BEGIN_MESSAGE_MAP(CNumSpinCtrl, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CNumSpinCtrl)
	ON_NOTIFY_REFLECT(UDN_DELTAPOS, OnDeltapos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumSpinCtrl message handlers

void CNumSpinCtrl::SetRange(double nLower, double nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	int MinVal = (int)floor(nLower);
	int MaxVal = (int)ceil(nUpper);
	CSpinButtonCtrl::SetRange32(MinVal, MaxVal);
}

void CNumSpinCtrl::GetRange(double& lower, double& upper) const
{
	lower = m_nLower;
	upper = m_nUpper;
}

void CNumSpinCtrl::OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	double deltaVal = pNMUpDown->iDelta * m_nDelta;
	CNumEdit* pEdit = (CNumEdit*)GetBuddy();
	TCHAR buf[32];
	pEdit->GetWindowText(buf, 32);
	double Value = atof(buf);
	Value += deltaVal;
	if(Value < m_nLower)
		Value = m_nLower;
	if(Value > m_nUpper)
		Value = m_nUpper;
	sprintf(buf, "%3.4f", Value);
	pEdit->SetWindowText(buf);

	*pResult = 0;
}

double CNumSpinCtrl::GetDelta()
{
	return m_nDelta;
}

void CNumSpinCtrl::SetDelta(double delta)
{
	m_nDelta = delta;
}
