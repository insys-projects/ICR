// IdCfgRomDlg.h : header file
//

#ifndef ID_CFG_ROM_DLG_H
#define ID_CFG_ROM_DLG_H

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

class CWriteReadDlg;

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
	// Controls (���������� �������� ��������� ����)
	CMyTabCtrl		m_ctrlTab;
	CAmbPage		*m_pAmbPage;
	CAdm2IfPage		*m_pAdmIfPage;
	CPldPage		*m_pPldPage;
	CFifoPage		*m_pFifoPage;
	CDacPage		*m_pDacPage;
	CAdmPage		*m_pAdmPage;
	CWriteReadDlg	*m_pFileBaseDlg;
	CComboBox		m_ctrlReadWriteDevs;

	CString	m_readFileExt;
	int		m_nDevType;
	int		m_nCanWriteSM;

	//int		m_nRealAdmCfgSize[4];

	// ����������, ������������, ��� � ���������� ����� ��������� ��������� ( � �������� ��������, � ������������ �������� ������ � � ������������ ���������)
	USHORT	m_wDialogFieldsEdited;
	USHORT	m_wBasemodFieldsEdited;
	USHORT	m_wSubmodFieldsEdited;
	// ���������, ���������� �������� ���� ���������� ����� ����� �� ����������, �� ����������� DLL
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

	// ---�������������
	virtual BOOL OnInitDialog();

	// ---������/������/������� ���������
	afx_msg void	OnBnClickedIntodev();
	void			VerifyEquiv(DEVICE_INFO DeviceInfoWrite, DEVICE_INFO DeviceInfoRead);
	void			ShowEquivMessage(int nBaseErrByteNum, int nSubErrByteNum, int nBaseSizeCorrect, int nSubSizeCorrect);
	afx_msg void	OnBnClickedFromdev();
	afx_msg void	OnBnClickedClear();

	// ---������ � �������
	// ���������� ���� ������
	afx_msg void OnBnClickedWriteRead();
	// ��������� �������� ����� �� �������� ���� � ���� ����
	void 	TransferParamsFromMainToFileBaseDlg();
	// ������ .bin ����� ����� ������
	void 	SaveBinThroughtDialog();
	// ������ .hex ����� ����� ������
	void 	SaveHexThroughtDialog();
	// ������ ������
	CString ShowSaveDialog(int nSaveType);
	// ������ �������� ����� � .bin ����
	void 	SaveBin(CString sFilePath);
	// ������ �������� ����� � .hex ����
	void 	SaveHex(CString sFilePath);
	// ������ ����� ������
	void 	ReadThroughDialog();
	// ������ ������
	CString ShowReadDialog();
	// ������ �������� ����� �� �����
	void 	ReadCfgFile(CString sFilePath);
	// �������� ������ ���������� � ������� ������, ���� ��� ����������
	int GetBMCfgSizeIfExist(void *pCfgMem, void *pEndCfgMem);

	// ---����������
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();

	// ---���������������
	// ���������� ������ ���������� �����
	ULONG	DlgItemsToCfgMem(PUCHAR	pCfgMem, ULONG nSizeCfgMem, int *pRealBaseCfgSize, int aRealAdmCfgSize[4]);
	// ���������� ����� ���������� �� ������
	void 	CfgMemToDlgItems(PUCHAR	pCfgMem, ULONG nSizeCfgMem);
	// ������ ����������(������� ������/���������) ��� ������/������
	int		GetReadWriteDevs();
	// ���������� �������� �����
	void	SaveDialogFieldsValues();
	// �������� ���������� �������� �����
	void 	CheckEditOfStructOfDialogFieldsValues();
	// ���������� About'�
	afx_msg void OnBnClickedAbout();

	afx_msg void OnCbnSelchangeReadWriteDev();
};

#endif // ID_CFG_ROM_DLG_H
