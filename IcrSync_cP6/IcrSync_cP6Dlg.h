#ifndef _ICRSYNCCP6DLG_H
#define _ICRSYNCCP6DLG_H

#include "utypes.h"
#include "resource.h"		// main symbols
#include "NumEdit.h"

#pragma once

// IcrSync_cP6Dlg dialog

class IcrSync_cP6Dlg : public CDialog
{
	DECLARE_DYNAMIC(IcrSync_cP6Dlg)

public:
	IcrSync_cP6Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~IcrSync_cP6Dlg();

// Dialog Data
	enum { IDD = IDD_DLG_CFG };

	CString m_sIntGenFreq;
	S32		m_isInpTactSign;

	CNumEdit m_ctrlIntGenFreq;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

protected:
	CToolTipCtrl m_ToolTip; 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

#endif // _ICRSYNCCP6DLG_H
