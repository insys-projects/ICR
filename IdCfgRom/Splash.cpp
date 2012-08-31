// About.cpp : implementation file
//

#include "stdafx.h"
#include "IdCfgRom.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog

IMPLEMENT_DYNAMIC(CSplash, CDialog)

CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CSplash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplash, CDialog)
	//{{AFX_MSG_MAP(CAbout)
	//ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbout message handlers
/*
BOOL CSplash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pHlWWW = new CHyperLink;
	m_pHlEmail = new CHyperLink;

	// TODO: Add extra initialization here
	m_pHlWWW->SubclassDlgItem(IDC_HL_WWW, this);
	m_pHlEmail->SubclassDlgItem(IDC_HL_Email, this);
	m_pHlEmail->SetURL(_T("mailto:info@insys.ru"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSplash::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_pHlWWW;
	delete m_pHlEmail;
}
*/
void CSplash::Create()
{
	CDialog::Create(CSplash::IDD);
}