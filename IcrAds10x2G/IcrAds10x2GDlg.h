#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CIcrAds10x2GDlg dialog

class CIcrAds10x2GDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAds10x2GDlg)

public:
	CIcrAds10x2GDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAds10x2GDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	UINT m_SysGen;
	UINT m_PllRefGen;
	UINT m_PllFreq;

	UINT	m_NumOfAdc;
	CSpinButtonCtrl	m_ctrlSpinAdc;
	UINT	m_AdcRange;
	UINT	m_AdcRateMax;
	UINT	m_AdcRateMin;

	UINT m_SdramCnt;
	CSpinButtonCtrl m_ctrlSpinSdram;
	UINT m_SdramNum;
	CSpinButtonCtrl m_ctrlSpinSdramNum;
	int m_SdramModules;
	int m_SdramRowAddrBits;
	int m_SdramColAddrBits;
	int m_SdramModuleBanks;
	int m_SdramChipBanks;
	int m_SdramCasLat;
	int m_SdramPrimWidth;
};
