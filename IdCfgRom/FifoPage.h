#pragma once

#include "icr.h"

//#include "AdmIfPage.h"
#include "Adm2IfPage.h"

UINT const MAX_ADCFIFOCFG = 4;
UINT const MAX_DACFIFOCFG = 4;

// CFifoPage dialog

class CFifoPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CFifoPage)

public:
	CFifoPage();
//	virtual ~CFifoPage();

	void SetDataIntoDlg(PICR_CfgAdcFifo pAdcFifo);
	void SetDataIntoDlg(PICR_CfgDacFifo pDacFifo);
	void GetDataFromDlg(PICR_CfgAdcFifo pAdcFifo, UINT num, UINT AdmNum);
	void GetDataFromDlg(PICR_CfgDacFifo pDacFifo, UINT num, UINT AdmNum);
	void SetMaxAdcFifo(int maxAdcFifo);
	void SetMaxDacFifo(int maxDacFifo);

// Dialog Data
	enum { IDD = IDD_PP_FIFO };
	CSpinButtonCtrl	m_ctrlSpinDacFifoNum;
	CSpinButtonCtrl	m_ctrlSpinAdcFifoNum;
	int		m_AdcFifoBitsWidth;
	int		m_AdcFifoSize;
	int		m_DacFifoBitsWidth;
	int		m_DacFifoSize;
	BOOL	m_DacFifoCycling;
	UINT	m_AdcFifoNum;
	UINT	m_DacFifoNum;

	UINT	m_AdmIfNum;

protected:
	ICR_CfgAdcFifo m_AdcFifo[MAX_ADMIFCFG][MAX_ADCFIFOCFG];
	ICR_CfgDacFifo m_DacFifo[MAX_ADMIFCFG][MAX_DACFIFOCFG];
	int m_AdcFifoMax;
	int m_DacFifoMax;

	void ChangeAdcFifoNum();
	void ChangeDacFifoNum();

	CToolTipCtrl m_ToolTip;                         // The tooltip

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
//	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	afx_msg void OnKillfocusAdcfifonum();
	afx_msg void OnKillfocusDacfifonum();
	afx_msg void OnDeltaposSpinadcfifonum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpindacfifonum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeDacfifosize();
	afx_msg void OnDacfifocycling();
	afx_msg void OnSelchangeDacfifobitswidth();
	afx_msg void OnSelchangeAdcfifosize();
	afx_msg void OnSelchangeAdcfifobitswidth();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
