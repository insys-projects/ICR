#pragma once

#include "icr.h"

UINT const MAX_ADMIFCFG = 4;

UINT const MAX_NUMOFPLD = 4;
UINT const MAX_NUMOFADCFIFO = 4;
UINT const MAX_NUMOFDAC = 4;
UINT const MAX_NUMOFDACFIFO = 4;

// CAdm2IfPage dialog

class CAdm2IfPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAdm2IfPage)

public:
	CAdm2IfPage();
//	virtual ~CAdm2IfPage();

	void SetDataIntoDlg(PICR_CfgAdm2If pAdmIfCfg);
	void GetDataFromDlg(PICR_CfgAdm2If pAdmIfCfg, UINT num);
	void SetMaxAdmIf(int maxAdmIf);

	void PageEnable(U08 isEnable);

// Dialog Data
	enum { IDD = IDD_PP_ADM2IF };
	CSpinButtonCtrl	m_ctrlSpinPld;
	CSpinButtonCtrl	m_ctrlSpinDac;
	CSpinButtonCtrl	m_ctrlSpinDacFifo;
	CSpinButtonCtrl	m_ctrlSpinAdmIfNum;
	CSpinButtonCtrl	m_ctrlSpinAdcFifo;
	UINT	m_AdmIfNum;
	UINT	m_NumOfAdcFifo;
	UINT	m_NumOfDacFifo;
	UINT	m_NumOfDac;
	UINT	m_NumOfPld;
	BOOL	m_Start;
	BOOL	m_Pio;
	int		m_AdmIfType;
	int		m_PioType;
	UINT	m_RefVoltPvs;
	double	m_Gen1;
	double	m_Gen2;

protected:
	ICR_CfgAdm2If m_AdmIfCfg[MAX_ADMIFCFG];
	int	m_AdmIfMax;

	void ChangeAdmIfNum();

    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
//	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	afx_msg void OnDeltaposSpinadmifnum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusAdmifnum();
	afx_msg void OnKillfocusGen1();
	afx_msg void OnKillfocusGen2();
	afx_msg void OnKillfocusNumofadcfifo();
	afx_msg void OnKillfocusNumofdac();
	afx_msg void OnKillfocusNumofdacfifo();
	afx_msg void OnKillfocusNumofpld();
	afx_msg void OnKillfocusRefvoltpvs();
	afx_msg void OnPiobe();
	afx_msg void OnStartbe();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusAdmiftype();
	afx_msg void OnKillfocusPiotype();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
