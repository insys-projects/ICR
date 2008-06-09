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
	CIdCfgRomDlg(CWnd* pParent = NULL);

// Dialog Data
	enum { IDD = IDD_IDCFGROM_DIALOG };
	// Controls (переменные контроля объектами окна)
	CMyTabCtrl	m_ctrlTab;
	int			m_DevType;
	BOOL		m_ToSubmoduleOnly;

	CAmbPage* m_pAmbPage;
	CAdm2IfPage* m_pAdmIfPage;
//	CAdmIfPage* m_pAdmIfPage;
	CPldPage* m_pPldPage;
	CFifoPage* m_pFifoPage;
	CDacPage* m_pDacPage;
	CAdmPage* m_pAdmPage;

	// Переменные, уведомляющие, что в диалоговых полях произошли изменения ( в основных вкладках, в подробностях базового модуля и в конфигурации субмодуля)
	USHORT	m_wDialogFieldsEdited;
	USHORT	m_wBasemodFieldsEdited;
	USHORT	m_wSubmodFieldsEdited;
	// Структура, содержащая значения всех диалоговых полей перед их изменением, за исключением DLL
	struct DIALOG_FIELDS_VALUES {
		UINT	AmbSerialNum;
		int		AmbBMType;
		CString AmbstrAmbVersion;
		UINT	AmbNumOfAdmIf;
		UINT	Adm2IfAdmIfNum;
		int		Adm2IfAdmIfType;
		UINT	Adm2IfNumOfPld;
		UINT	Adm2IfNumOfDac;
		UINT	Adm2IfNumOfAdcFifo;
		UINT	Adm2IfNumOfDacFifo;
		double	Adm2IfGen1;
		double	Adm2IfGen2;
		BOOL	Adm2IfPio;
		int		Adm2IfPioType;
		UINT	Adm2IfRefVoltPvs;
		BOOL	Adm2IfStart;
		UINT	PldPldNum;
		USHORT	PldPldType;
		USHORT	PldPldRate;
		UINT	PldPldVolume;
		UINT	PldPldPins;
		UINT	FifoAdcFifoNum;
		int		FifoAdcFifoSize;
		int		FifoAdcFifoBitsWidth;
		UINT	FifoDacFifoNum;
		int		FifoDacFifoSize;
		int		FifoDacFifoBitsWidth;
		BOOL	FifoDacFifoCycling;
		UINT	DacDacNum;
		int		DacDacBits;
		UINT	DacDacRateMin;
		UINT	DacDacRateMax;
		UINT	DacDacRangeAF;
		UINT	DacDacRangePF;
		UINT	DacDacLPFCoff;
		UINT	DacDacHPFCoff;
		UINT	DacDacAFCoff;
		int		DacDacEncoding;
		UINT	AdmAdmPID;
		int		AdmAdmType;
		CString AdmstrAdmVersion;
	} m_rDialogFieldsValues;

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

	ULONG DlgItemsToCfgMem();
	void CfgMemToDlgItems();
	void UpdateStructOfDialogFieldsValues();
	void CheckEditOfStructOfDialogFieldsValues();

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
	afx_msg void OnBnClickedSavehex();
	afx_msg void OnBnClickedOk();
protected:
	virtual void OnCancel();
};
