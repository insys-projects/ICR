#include "IcrXXXXDlg.h"

#include <Windows.h>

#include <QFile>
#include <QtXml/QDomDocument>
#include <QColorDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QFontDialog>

IcrXXXXDlg::IcrXXXXDlg(const IcrParamList &lIcrParams,  QList<TGroup *> &lpGroup, QWidget *parent, Qt::WFlags flags)
			: QDialog(parent, flags | Qt::WindowCloseButtonHint)
{
	setupUi(this);

	QSettings settings("Instrumental Systems", "IdCfgRom");

	QVariant variant = settings.value("FontXXXX");

	QFont fn;

	if(variant.isValid())
	{
		fn = variant.value<QFont>();	
		m_pParamTreeWidget->setFont(fn);
	}

	m_lpGroup = lpGroup;

	SetIcrParams(lIcrParams);
	FillTree();

	m_pParamTreeWidget->header()->resizeSections(QHeaderView::ResizeToContents);

	connect(m_pParamTreeWidget, SIGNAL(signalItemRightClicked()), this, SLOT(slotItemRightClicked()));
	
	// Выбор цвета группы
	connect(m_pActionColorGroup, SIGNAL(triggered()), this, SLOT(slotColorGroup()));

	connect(m_pFontButton, SIGNAL(clicked()), this, SLOT(slotFontChange()));
}

IcrXXXXDlg::~IcrXXXXDlg()
{
	QSettings settings("Instrumental Systems", "IdCfgRom");

	settings.setValue("FontXXXX", m_pParamTreeWidget->font());

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

QList<TGroup *> IcrXXXXDlg::GetGroups()
{
	return m_lpGroup;
}

void IcrXXXXDlg::FillTree()
{
	TIcrParam		*pIcrParam;
	ParamTreeItem	*pTreeItem;
	QList<QTreeWidgetItem *> lpTree;
	TGroup			*pGroup;
	QString			sOther;

	// Добавление в дерево групп
	foreach(pGroup, m_lpGroup)
		m_mpGroupItems.insert(pGroup->sName, m_pParamTreeWidget->AddGroup(pGroup));	

	m_pParamTreeWidget->ExpandedGroups(m_lpGroup);

	foreach(pIcrParam, m_lpIcrParams)
	{
		if((pIcrParam->nTag != -1) || pIcrParam->isInvisible)
			continue;
		
		pTreeItem = new ParamTreeItem;

		m_pParamTreeWidget->AddParam(pIcrParam->sGroupName, pIcrParam);	
	}

	if(m_lpGroup.size() > 0)
	{
		sOther = m_lpGroup[m_lpGroup.size() - 1]->sName;

		lpTree = m_pParamTreeWidget->findItems(sOther, Qt::MatchFixedString, 0);

		pTreeItem = dynamic_cast<ParamTreeItem *>(lpTree[0]);

		if(pTreeItem->childCount() == 0)
			delete pTreeItem;
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

void IcrXXXXDlg::showEvent(QShowEvent * pEvent)
{
	QList<QTreeWidgetItem *> lpTree;
	QString sOther;
	
	if(m_lpGroup.size() > 0)
	{
		sOther = m_lpGroup[m_lpGroup.size() - 1]->sName;

		lpTree = m_pParamTreeWidget->findItems(sOther, Qt::MatchFixedString, 0);

		int h = QFontMetrics(m_pParamTreeWidget->font()).height();

 		if(lpTree.size() == 0)
 			resize(size().width(), size().height() - h + 9);
	}

	if(size().height() > (QApplication::desktop()->height() - 100))
		resize(size().width(), QApplication::desktop()->height() - 100);

	HWND parent = GetForegroundWindow();

	RECT  pos;

	// Вычисление координат размещения диалога
	GetWindowRect(parent, &pos);

	QSize dlgSize = size();

	U32 nX = (pos.right - pos.left - dlgSize.width()) / 2;
	U32 nY = (pos.bottom - pos.top - dlgSize.height()) / 2;

	move(pos.left + nX, pos.top + nY);
	// ---------------------------------------
}

// Щелчок правой кнопкой
void IcrXXXXDlg::slotItemRightClicked()
{
	ParamsTreeWidget *pTreeWidget = dynamic_cast<ParamsTreeWidget *>(sender());
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(pTreeWidget->currentItem());
	QString str = pItem->text(0);
	S32 idx = str.indexOf("[");

	if((pItem->childCount() != 0) && (idx != 0))
	{
		pTreeWidget->addAction(m_pActionColorGroup);
	}
	else
		pTreeWidget->removeAction(m_pActionColorGroup);
}

// Изменить цвет группы
void IcrXXXXDlg::slotColorGroup()
{
	TGroup *prGroup;
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(m_pParamTreeWidget->currentItem());
	ParamTreeItem *pChild;
	QString sGroupName = pItem->text(0);
	U32 i;

	// Диалог выбора цвета
	QColor color = QColorDialog::getColor(pItem->ColorGroup(), this, tr("Выберите цвет группы"));

	if(!color.isValid())
		// Цвет не выбран
		return;

	if((color.red() == pItem->ColorGroup().red()) &&
		(color.green() == pItem->ColorGroup().green()) &&
		(color.blue() == pItem->ColorGroup().blue()))
		// Цвет не изменился
		return;

	// Установка цвета
	foreach(prGroup, m_lpGroup)
		if(prGroup->sName == sGroupName)
		{
			prGroup->color = color;

			foreach(pItem, m_mpGroupItems.values(prGroup->sName))
			{
				pItem->SetColorGroup(color);

				for(i = 0; i < pItem->childCount(); i++)
				{
					pChild = dynamic_cast<ParamTreeItem *>(pItem->child(i));
					pChild->SetColorGroup(color);
				}
			}

//			WriteJiniFile(prGroup); // Сохранение атрибутов группы в jini-файл
			break;
		}

		m_pParamTreeWidget->setAttribute(Qt::WA_WState_InPaintEvent);
		m_pParamTreeWidget->setUpdatesEnabled(true);
		m_pParamTreeWidget->repaint(); // Перерисовка
		m_pParamTreeWidget->update();  // Обновление
}

// Изменить шрифт
void IcrXXXXDlg::slotFontChange()
{
	bool ok;

	QFont font = QFontDialog::getFont(&ok, m_pParamTreeWidget->font(), this);

	if(ok)
	{
		m_pParamTreeWidget->setFont(font);
		m_pParamTreeWidget->header()->resizeSections(QHeaderView::ResizeToContents);
	}
}