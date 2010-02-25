// IcrSync_cP6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "IcrSync_cP6App.h"
#include "IcrSync_cP6Dlg.h"


// IcrSync_cP6Dlg dialog

IMPLEMENT_DYNAMIC(IcrSync_cP6Dlg, CDialog)

IcrSync_cP6Dlg::IcrSync_cP6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IcrSync_cP6Dlg::IDD, pParent)
	, m_sIntGenFreq(_T(""))
{

}

IcrSync_cP6Dlg::~IcrSync_cP6Dlg()
{
}

void IcrSync_cP6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Check  (pDX, IDC_INP_TACT_SIGN, m_isInpTactSign);
	DDX_Text   (pDX, IDC_INT_GEN_FREQ,  m_sIntGenFreq);
	DDX_Control(pDX, IDC_INT_GEN_FREQ,  m_ctrlIntGenFreq);
}


BEGIN_MESSAGE_MAP(IcrSync_cP6Dlg, CDialog)
END_MESSAGE_MAP()


// IcrSync_cP6Dlg message handlers

BOOL IcrSync_cP6Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	m_ToolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}



BOOL IcrSync_cP6Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_ToolTip.Create(this);
	m_ToolTip.AddTool(GetDlgItem(IDC_INP_TACT_SIGN), IDC_INP_TACT_SIGN);
	m_ToolTip.AddTool(GetDlgItem(IDC_INT_GEN_FREQ),  IDC_INT_GEN_FREQ);

	m_ctrlIntGenFreq.SetLimitText(13);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
