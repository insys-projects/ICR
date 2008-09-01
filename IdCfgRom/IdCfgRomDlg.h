// IdCfgRomDlg.h : header file
//

#pragma once

#include "MyTabCtrl.h"

#include "About.h"

#include "AmbPage.h"
#include "Adm2IfPage.h"
#include "PldPage.h"
#include "FifoPage.h"
#include "DacPage.h"
#include "AdmPage.h"
#include "WriteReadDlg.h"
#include "afxwin.h"

enum
{
	SAVE_BIN,
	SAVE_HEX,
};

extern HICON g_hIcon;

// CIdCfgRomDlg dialog
class CIdCfgRomDlg : public CDialog
{
// Construction
public:
	CIdCfgRomDlg(CWnd* pParent = NULL);

// Dialog Data
	enum { IDD = IDD_IDCFGROM_DIALOG };

// Implementation
protected:
	CAbout* m_pAboutDlg;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// Generated message map functions
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()

public:
	// Controls (переменные контроля объектами окна)
	CMyTabCtrl	m_ctrlTab;
	CAmbPage	*m_pAmbPage;
	CAdm2IfPage	*m_pAdmIfPage;
	CPldPage	*m_pPldPage;
	CFifoPage	*m_pFifoPage;
	CDacPage	*m_pDacPage;
	CAdmPage	*m_pAdmPage;

	CString	m_readFileExt;

	CWriteReadDlg	*m_pFileBaseDlg;
	CString m_sWriteZakaz;
	CString m_sWriteSurname;
	CString m_sWriteKeyword;

	CComboBox	m_ctrlReadWriteDevs;
	int			m_DevType;

	PUCHAR	m_pCfgMem;
	ULONG	m_sizeCfgMem;
	int		m_RealBaseCfgSize;
	int		m_RealAdmCfgSize[4];

	// Переменные, уведомляющие, что в диалоговых полях произошли изменения ( в основных вкладках, в подробностях базового модуля и в конфигурации субмодуля)
	USHORT	m_wDialogFieldsEdited;
	USHORT	m_wBasemodFieldsEdited;
	USHORT	m_wSubmodFieldsEdited;
	// Структура, содержащая значения всех диалоговых полей перед их изменением, за исключением DLL
	struct DIALOG_FIELDS_VALUES
	{
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

	// ---инициализация
	virtual BOOL OnInitDialog();

	// ---запись/чтение/очистка устройств
	afx_msg void OnBnClickedIntodev();
	afx_msg void OnBnClickedFromdev();
	afx_msg void OnBnClickedClear();

	// ---работа с файлами
	// обработчик базы файлов
	afx_msg void OnBnClickedWriteRead();
	// переслать значения полей из главного окна в окно базы
	void 	TransferParamsFromMainToFileBaseDlg();
	// запись .bin файла через диалог
	void 	SaveBinThroughtDialog();
	// запись .hex файла через диалог
	void 	SaveHexThroughtDialog();
	// диалог записи
	CString ShowSaveDialog(int nSaveType);
	// запись значений полей в .bin файл
	void 	SaveBin(CString sFilePath);
	// запись значений полей в .hex файл
	void 	SaveHex(CString sFilePath);
	// чтение через диалог
	void 	ReadThroughDialog();
	// диалог чтения
	CString ShowReadDialog();
	// чтение значений полей из файла
	void 	ReadCfgFile(CString sFilePath);

	// ---завершение
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();

	// ---вспомогательное
	// заполнение буфера значениями полей
	ULONG	DlgItemsToCfgMem();
	// заполнение полей значениями из буфера
	void 	CfgMemToDlgItems();
	// установить устройства(базовый модуль/субмодуль) для записи/чтения
	void	SetReadWriteDevs(int nReadWriteDevs);
	// узнать устройства(базовый модуль/субмодуль) для записи/чтения
	int		GetReadWriteDevs();
	// сохранение значений полей
	void	SaveDialogFieldsValues();
	// проверка сохранения значений полей
	void 	CheckEditOfStructOfDialogFieldsValues();
	afx_msg void OnBnClickedAbout();
};
