#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CIcrAmbpDlg dialog

class CIcrAmbpDlg : public CDialog
{
	DECLARE_DYNAMIC(CIcrAmbpDlg)

public:
	CIcrAmbpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIcrAmbpDlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

protected:
    CToolTipCtrl m_ToolTip;                         // The tooltip
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void SetPldName();
	
#define LOCK	0
#define UNLOCK	1
	void LockUnlockSdramWindows(USHORT wLock);
	void LockUnlockDspWindows(USHORT wLock);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusPldpins();
	afx_msg void OnCbnSelchangePldtype();
	afx_msg void OnEnKillfocusPldvolume();
	afx_msg void OnCbnSelchangePldrate();

	UINT m_SysGen;
	int m_SlotCnt;
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

	UINT m_DspNodeCnt;
	CSpinButtonCtrl m_ctrlSpinDspNode;
	UINT m_DspNodeNum;
	CSpinButtonCtrl m_ctrlSpinDspNodeNum;
	UINT m_DspPldVolume;
	UINT m_DspPldPins;
	int m_LoadRom;
	CComboBox m_ctrlDspPldType;
	CComboBox m_ctrlDspPldRate;
	int m_DspPldType;
	int m_DspPldRate;

	CString m_strDspPldName;
	BOOL m_isPio;
	int m_PioType;
	BOOL m_isSRAM;
	int m_SramChips;
	int m_SramSize;
	int m_SramBitsWidth;
	afx_msg void OnBnClickedPiobe();
	afx_msg void OnBnClickedSrambe();
	int m_SdramPrimWidth;
public:
	afx_msg void OnDeltaposSpinsdram(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnEnKillfocusSdramcnt();
public:
	afx_msg void OnEnKillfocusDspcnt();
public:
	CComboBox m_ctrlSdramDimms;
public:
	afx_msg void OnDeltaposSpindspcnt(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnEnKillfocusDspnum();
public:
	afx_msg void OnEnKillfocusSdramnum();
};
