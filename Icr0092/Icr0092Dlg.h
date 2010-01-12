#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "utypes.h"
#include "d:\andrej\work\_icr\usefulmfc\numedit.h"

// Icr0092Dlg dialog

class Icr0092Dlg : public CDialog
{
	DECLARE_DYNAMIC(Icr0092Dlg)

public:
	Icr0092Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr0092Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	U08		m_bNumOfDac;

	// Controls (переменные контроля объектами окна)
	CSpinButtonCtrl m_ctrlSpinDac;
	CComboBox m_ctrlDacOutResist;
	CComboBox m_ctrlQuadModType;
	S32 	m_isFreqTune;
	BOOL	m_ExtClk;
	CString	m_sOutResist;
	S32  	m_isPll;
	S32	    m_isGen;
	BOOL	m_QuadMod;

	// Text-dialog exchanging variables (переменные обмена текстом с дилоговым окном)
	U32	    m_nDacRateMax;
	U32  	m_nDacRateMin;
	U32  	m_nGen;
	U32		m_nDacRange;
	U32		m_nLpfCutoff;
	U32	    m_nOscFreq;
	
	// Controls associated variables (переменные, ассоциированные с переменными контроля)
	//int		m_OutResist;
	
	UINT	m_QuadModType;

	SUBMOD_INFO subInfo;

protected:
	CToolTipCtrl m_ToolTip;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedQuadmod();
	afx_msg void OnBnClickedIsgen();
//	afx_msg void OnBnClickedIspll();
public:
//	afx_msg void OnEnKillfocusOscfreq();
public:
	afx_msg void OnEnKillfocusGen();
public:
	CString m_sGenPrec;
public:
	CNumEdit m_ctrlGenPrec;
public:
	S32 m_isClkOut;
public:
	S32 m_isIndustrial;
public:
	afx_msg void OnBnClickedIspll();
};
