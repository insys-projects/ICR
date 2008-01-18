// IdCfgRomDlg.h : header file
//

#pragma once

#include "MyTabCtrl.h"

#include "About.h"

#include "AmbPage.h"
//#include "AdmIfPage.h"
#include "Adm2IfPage.h"
#include "PldPage.h"
#include "FifoPage.h"
#include "DacPage.h"
#include "AdmPage.h"

// CIdCfgRomDlg dialog
class CIdCfgRomDlg : public CDialog
{
// Construction
public:
	CIdCfgRomDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IDCFGROM_DIALOG };
	CMyTabCtrl	m_ctrlTab;
	int		m_DevType;

	CAmbPage* m_pAmbPage;
	CAdm2IfPage* m_pAdmIfPage;
//	CAdmIfPage* m_pAdmIfPage;
	CPldPage* m_pPldPage;
	CFifoPage* m_pFifoPage;
	CDacPage* m_pDacPage;
	CAdmPage* m_pAdmPage;


// Implementation
protected:
	HICON m_hIcon;
	CAbout* m_pAboutDlg;

	PUCHAR m_pCfgMem;
	ULONG m_sizeCfgMem;
//	UCHAR m_BaseCfgMem[1024];
	int m_RealBaseCfgSize;
//	UCHAR m_AdmCfgMem[4][1024];
	int m_RealAdmCfgSize[4];

	CString	m_readFileExt;

	ULONG SetCfgMem();
	void GetCfgMem();

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedRead();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedIntodev();
	afx_msg void OnBnClickedFromdev();
public:
	afx_msg void OnBnClickedSavehex();
};
