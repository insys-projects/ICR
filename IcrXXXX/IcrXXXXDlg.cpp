#include "IcrXXXXDlg.h"

#include <Windows.h>

#include <QFile>
#include <QtXml/QDomDocument>

IcrXXXXDlg::IcrXXXXDlg(const IcrParamList &lIcrParams, QWidget *parent, Qt::WFlags flags)
			: QDialog(parent, flags | Qt::WindowCloseButtonHint)
{
	setupUi(this);

	SetIcrParams(lIcrParams);
	FillTree();

	m_pParamTreeWidget->header()->resizeSections(QHeaderView::ResizeToContents);
}

IcrXXXXDlg::~IcrXXXXDlg()
{
	TIcrParam *pIcrParam;

	foreach(pIcrParam, m_lpIcrParams)
		delete pIcrParam;
}

IcrParamList IcrXXXXDlg::GetIcrParams()
{
	TIcrParam *pIcrParam;
	IcrParamList lIcrParams;

	foreach(pIcrParam, m_lpIcrParams)
		lIcrParams << (*pIcrParam);

	return lIcrParams;
}

void IcrXXXXDlg::FillTree()
{
	TIcrParam		*pIcrParam;
	ParamTreeItem	*pTreeItem;

	foreach(pIcrParam, m_lpIcrParams)
	{
		if(pIcrParam->nTag != -1)
			continue;

		pTreeItem = new ParamTreeItem;

		m_pParamTreeWidget->AddParam("", pIcrParam);	
	}
}

void IcrXXXXDlg::SetIcrParams(const IcrParamList &lIcrParams)
{
	TIcrParam *pIcrParam;
	TIcrParam rIcrParam;

	foreach(rIcrParam, lIcrParams)
	{
		pIcrParam = new TIcrParam;
		*pIcrParam = rIcrParam;
		m_lpIcrParams << pIcrParam;
	}
}