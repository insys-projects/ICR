#pragma once

#define	SUBMOD_API_EXPORTS
#include "submod.h"
#include "afxwin.h"
#include "afxcmn.h"

// Icr008FDlg dialog

class Icr008FDlg : public CDialog
{
	DECLARE_DYNAMIC(Icr008FDlg)

public:
	Icr008FDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Icr008FDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	// Controls (переменные контроля объектами окна)
	CSpinButtonCtrl m_ctrlSpinDac;
	CComboBox m_ctrlDacOutResist;
	CComboBox m_ctrlQuadModType;
	CComboBox m_ctrlOutCasMod;
	BOOL	m_GenTune;
	BOOL	m_ExtClk;
	int		m_OutResist;
	int		m_OutCasMod;
	BOOL	m_IsPll;
	BOOL	m_IsGen;
	BOOL	m_QuadMod;

	// Text-dialog exchanging variables (переменные обмена текстом с дилоговым окном)
	UINT	m_DacRateMax;
	UINT	m_DacRateMin;
	UINT	m_Gen;
	UINT	m_NumOfDac;
	UINT	m_DacRange;
	UINT	m_LpfCutoff;
	UINT	m_OscFreq;
	
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
	afx_msg void OnBnClickedIspll();
public:
	afx_msg void OnEnKillfocusOscfreq();
public:
	afx_msg void OnEnKillfocusGen();
};
