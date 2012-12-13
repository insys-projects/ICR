#include "ParamsTreeWidget.h"

#include <QTreeWidgetItem>
#include <QWidget>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QPainter>
#include <QColor>
#include <QRgb>
#include <QApplication>
#include <QMouseEvent>
#include <QHeaderView>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QStyle>

#include "DoubleValidator.h"
#include "ValidatorEx.h"

// Иконка плюс-минус для дерева
static QIcon drawIndicatorIcon(const QPalette &palette, QStyle *style)
{
	QPixmap pix(14, 14);
	pix.fill(Qt::transparent);
	QStyleOption branchOption;
	QRect r(QPoint(0, 0), pix.size());
	branchOption.rect = QRect(2, 2, 9, 9); // ### hardcoded in qcommonstyle.cpp
	branchOption.palette = palette;
	branchOption.state = QStyle::State_Children;

	QPainter p;
	// Draw closed state
	p.begin(&pix);
	style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
	p.end();
	QIcon rc = pix;
	rc.addPixmap(pix, QIcon::Selected, QIcon::Off);
	// Draw opened state
	branchOption.state |= QStyle::State_Open;
	pix.fill(Qt::transparent);
	p.begin(&pix);
	style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
	p.end();

	rc.addPixmap(pix, QIcon::Normal, QIcon::On);
	rc.addPixmap(pix, QIcon::Selected, QIcon::On);
	return rc;
}

// Сделать item доступным для редактирования
void ParamTreeItem::setEnable(U08 isEnable)
{
	if(isEnable)
	{
		setTextColor(0, QColor(0, 0, 0));
		setTextColor(1, QColor(0, 0, 0));

		setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
			Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | 
			Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	}
	else
	{
		setTextColor(0, QColor(120, 120, 120));
		setTextColor(1, QColor(120, 120, 120));

		setFlags(Qt::ItemIsSelectable | 
			Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | 
			Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	}
}

void ParamTreeItem::setCheckState(U08 isCheck)
{
	setEnable(isCheck);

	if(isCheck)
		QTreeWidgetItem::setCheckState(0, Qt::Checked);
	else
		QTreeWidgetItem::setCheckState(0, Qt::Unchecked);
}

ParamsTreeWidget::ParamsTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
	QTreeWidgetItem *pItem = headerItem();
	ParamDelegate *pDelegate = new ParamDelegate(parent);

	setItemDelegate(pDelegate);
	pDelegate->setParamsTree(this);

	connect(pDelegate, SIGNAL(signalParamChanged(ParamTreeItem *)), this, SIGNAL(signalParamChanged(ParamTreeItem *)));

	pItem->setText(0, tr("Параметр"));
	pItem->setText(1, tr("Значение"));
	header()->setDefaultSectionSize(250);
	header()->setMovable(false);
	//setAlternatingRowColors(true);
	setRootIsDecorated(false);

	setItemsExpandable(true);
	setExpandsOnDoubleClick(true);

	m_isCheck = 1;
}

// Добавление элемента
// sNameGroup - имя группы
// pParam - параметр
void ParamsTreeWidget::AddParam(QString sNameGroup, TIcrParam *pParam)
{
	QList<QTreeWidgetItem *> pListItem = findItems(sNameGroup, Qt::MatchFixedString, 0);
	ParamTreeItem *pGroupItem = 0;
	ParamTreeItem *pParamItem = new ParamTreeItem;
//	TSection *prSection;
	QString sText;

	if(pListItem.size() > 0)
		pGroupItem = dynamic_cast<ParamTreeItem *>(pListItem[0]);

	pParamItem->setHead(0);
	pParamItem->setEnable(1);

	if(pGroupItem)
		pParamItem->SetColorGroup(pGroupItem->ColorGroup());
	
// 	if(pParam->prJiniAttr != 0)
// 	{
//		if(pParam->prJiniAttr->isNoEdit)
//		{
//			// Нередактируемый параметр
//			pParamItem->setTextColor(0, QColor(0, 0, 0));
//			//pParamItem->setTextColor(1, QColor(0, 0, 255));
//			pParamItem->setTextColor(1, QColor(0, 0, 0));
//			pParamItem->setBackgroundColor(1, QColor(236, 233, 216));
//		}
//
//		if(!pParam->prJiniAttr->sTitle.isEmpty())
//			sText = pParam->prJiniAttr->sTitle;
//		else		
//			sText = pParam->sName;
//
//		pParamItem->setText(0, sText);
//
// 		if(pParam->prJiniAttr->nType == PARAM_TYPE_LIST)
// 			foreach(TJiniListItem *item, pParam->prJiniAttr->vrJiniParamListItem)
// 			{
// 				if(item->sVal == pParam->sValue)
// 				{
// 					if(!item->sDescr.isEmpty())
// 						sText = pParam->sValue + " [" + item->sDescr + "]";
// 					else
// 						sText = pParam->sValue;
// 
// 					break;
// 				}
// 				else
// 					sText = pParam->sValue;
// 			}
// 		else
//			sText = pParam->sValue;
//		
//		if(pParam->prJiniAttr->nType == PARAM_TYPE_CHECK)
//		{
//// 			switch(pParam->sValue.toInt())
//// 			{
//// 				case 0:
//// 				{
//// 					pParamItem->setCheckState(1, Qt::Unchecked);
//// 					break;
//// 				}
//// 
//// 				case 1:
//// 				{
//// 					pParamItem->setCheckState(1, Qt::Checked);
//// 					break;
//// 				}
//// 			}
//			
//		}
//		else
//			pParamItem->setText(1, sText);
//	}

	pParamItem->setText(0, pParam->sName);
	
	if(pParam->sValue.isEmpty())
		pParam->sValue = pParam->sDefValue;

	if(pParam->nType == PARAM_TYPE_LIST)
	{
		foreach(TItem rItem, pParam->lrItem)
		{
			if(rItem.sVal == pParam->sValue)
			{
				pParamItem->setText(1, rItem.sDescr);

				break;
			}
		}
	}
	else
	{
		pParamItem->setText(1, pParam->sValue);
	}
	
	//pParamItem->setText(1, sText);
	
	pParamItem->setParam(pParam);

	if(pGroupItem)
	{
		pGroupItem->addChild(pParamItem);
		pGroupItem->setExpanded(true);
	}
	else
		invisibleRootItem()->addChild(pParamItem);
}

// Удалить все параметры
void ParamsTreeWidget::DeleteAllParam()
{
	QTreeWidgetItem *pRoot = invisibleRootItem();
	
	while(pRoot->childCount() != 0)
		pRoot->removeChild(pRoot->child(0));
}

// Добавить группу
ParamTreeItem *ParamsTreeWidget::AddGroup(TGroup *prGroup)
{
	QTreeWidgetItem *pRoot  = invisibleRootItem();
	ParamTreeItem	*pGroup = new ParamTreeItem;

	pGroup->SetColorGroup(prGroup->color);
	pGroup->setHead();
	pGroup->setParam(0);
	pGroup->setText(0, prGroup->sName);
	pGroup->setIcon(0, drawIndicatorIcon(palette(), style()));
	pRoot->addChild(pGroup);
	viewport()->update();

	return pGroup;
}

void ParamsTreeWidget::ExpandedGroups(QList<TGroup *> &lpGroup)
{
	QList<QTreeWidgetItem *> pListItem;
	ParamTreeItem *pGroupItem;
	TGroup *prGroup;

	foreach(prGroup, lpGroup)
	{
		pListItem = findItems(prGroup->sName, Qt::MatchFixedString, 0);
		pGroupItem = dynamic_cast<ParamTreeItem *>(pListItem[0]);
		pGroupItem->setExpanded(prGroup->isOpen);
	}
}

// Обновление дерева
void ParamsTreeWidget::Update()
{
	QTreeWidgetItem *pRoot = invisibleRootItem();
	U32 i;

	for(i = 0; i < pRoot->childCount(); i++)
		pRoot->child(i)->setFirstColumnSpanned(true);
}

// Прорисовка рядов
void ParamsTreeWidget::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(itemFromIndex(index));
	QStyleOptionViewItemV3 opt = option;

	if(pItem->head()) 
	{
		const QColor c = option.palette.color(QPalette::Dark);
		painter->fillRect(option.rect, c);
		opt.palette.setColor(QPalette::AlternateBase, c);
	}
	else
	{
		const QColor c = pItem->ColorGroup();

		if (c.isValid()) {
			painter->fillRect(option.rect, c);
			opt.palette.setColor(QPalette::AlternateBase, c.lighter(112));
		}
	}

	QTreeWidget::drawRow(painter, opt, index);
	QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
	painter->save();
	painter->setPen(QPen(color));
	painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
	painter->restore();
}

void ParamsTreeWidget::mousePressEvent(QMouseEvent *event)
{
	QTreeWidget::mousePressEvent(event);

	QTreeWidgetItem *item = itemAt(event->pos());
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(item);

	if(event->button() == Qt::RightButton)
	{
		// Выдаем сигнал о нажатии правой кнопки мыши
		emit(signalItemRightClicked()); 
	
		return;
	}

	if(item == 0)
		return;

	if(item->childCount() != 0)
		if (event->pos().x() + header()->offset() < 20)
		{
			emit itemDoubleClicked(item, header()->logicalIndexAt(event->pos().x()));
			item->setExpanded(!item->isExpanded());
		}

// 	if(header()->logicalIndexAt(event->pos().x()) == 0)
// 	{
// 		m_isCheck = pItem->checkState(0);
// 	}
}

void ParamsTreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
 	QTreeWidget::mouseReleaseEvent(event);

 	QTreeWidgetItem *item = itemAt(event->pos());
 	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(item);
 	
 	if(event->button() != Qt::LeftButton)
 		return;
 
 	if(item == 0)
 		return;

// 	if((m_isCheck != pItem->checkState(0)) && (m_isCheck == Qt::Unchecked))
// 		if(pItem->param()->isFlag)
// 		{
// 			QMessageBox msgBox;
// 			msgBox.setText(tr("Параметр отсутствует в некоторых файлах"));
// 			msgBox.setInformativeText(tr("Добавить параметр во все файлы?"));
// 			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
// 			msgBox.setDefaultButton(QMessageBox::Yes);
// 			int ret = msgBox.exec();
// 
// 			if(ret != QMessageBox::Yes)
// 				return;
// 			else
// 				pItem->param()->isFlag = 0;
// 		}
// 
// 		TParam *pParam = (TParam *)pItem->param();
// 
// 		if(pParam == 0)
// 			return;
// 
// 		if(header()->logicalIndexAt(event->pos().x()) == 0)
// 		{
// 			pParam = pItem->param();
// 
// 			switch(pItem->checkState(0))
// 			{
// 			case Qt::Unchecked: 
// 				{
// 					pItem->setEnable(0);
// 
// 					pParam->isEnable = 0; 
// 					break;
// 				}
// 
// 			case Qt::Checked:
// 				{
// 					pItem->setEnable(1);
// 
// 					pParam->isEnable = 1; 
// 				}
// 
// 			}
// 		}
}

void ParamsTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{	emit(itemDoubleClicked(itemAt(event->pos()), header()->logicalIndexAt(event->pos().x())));
	QTreeWidget::mousePressEvent(event);
	QTreeWidgetItem *item = itemAt(event->pos());
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(item);

	if(event->button() != Qt::LeftButton)
		return;

	if(item == 0)
		return;

	TParam *pParam = (TParam *)pItem->param();

	if(pItem->head())
	{
		pItem->setExpanded(!pItem->isExpanded());
		return;
	}

	if(pParam == 0)
		return;

	if(header()->logicalIndexAt(event->pos().x()) == 1)
	{
	//	if(pItem->param()->isFlag)
	//	{
	//		QMessageBox msgBox;
	//		msgBox.setText(tr("Параметр отсутствует в некоторых файлах"));
	//		msgBox.setInformativeText(tr("Добавить параметр во все файлы?"));
	//		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	//		msgBox.setDefaultButton(QMessageBox::Yes);
	//		int ret = msgBox.exec();

	//		if(ret != QMessageBox::Yes)
	//			return;
	//		else
	//		{
	//			pItem->param()->isFlag = 0;
	//			pItem->param()->isEnable = 1; 
	//			pItem->setCheckState(1);
	//		}
	//	}

		if(pParam->isEnable)
			editItem(item, 1);
	}
}

QWidget *ParamDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(m_pTree->indexToItem(index));
	TIcrParam *pParam = pItem->param();
	QWidget *pEditor;
	QSpinBox *pSpinIntEditor;
	DoubleSpinBoxEx *pSpinDoubleEditor;
	QComboBox *pComboBoxEditor;
	QLineEdit *pEdit;

	U32 nType;
	QString str;
	U32 i = 0;
	U08 flg = 0;
			
	if(pParam->nType == -1)
		nType = PARAM_TYPE_STRING;
 	else
 		nType = pParam->nType;

	switch(nType)
	{
		case PARAM_TYPE_INT:
		{
			pEdit = new QLineEdit(parent);
			
			QIntValidator *pValidator = new QIntValidator(pParam->nMin, pParam->nMax, pEdit);
			
			pEdit->setValidator(pValidator);

			pEditor = pEdit;

			break;
		}

		case PARAM_TYPE_SPIN_INT:
		{
			pSpinIntEditor = new QSpinBox(parent);
			pSpinIntEditor->setRange(pParam->nMin, pParam->nMax);

 			if(pParam->nInc != 0)
 				pSpinIntEditor->setSingleStep(pParam->nInc);

			pEditor = pSpinIntEditor;

			break;
		}

		case PARAM_TYPE_DOUBLE:
		{
			pEdit = new QLineEdit(parent);

			DoubleValidator *pValidator = new DoubleValidator(pParam->dMin, pParam->dMax, pParam->nPrec, pEdit);

			pEdit->setValidator(pValidator);

			pEditor = pEdit;

			break;
		}

		case PARAM_TYPE_SPIN_DOUBLE:
		{
			pSpinDoubleEditor = new DoubleSpinBoxEx(parent);
 			pSpinDoubleEditor->setRange(pParam->dMin, pParam->dMax);
 
 			if(pParam->dInc != 0)
 				pSpinDoubleEditor->setSingleStep(pParam->dInc);

			pSpinDoubleEditor->setDecimals(pParam->nPrec);

			pEditor = pSpinDoubleEditor;
			break;
		}

		case PARAM_TYPE_LIST:
		{
			pComboBoxEditor = new QComboBox(parent);
			//pComboBoxEditor->setEditable(true);

			pComboBoxEditor->setInsertPolicy(QComboBox::NoInsert);

 			foreach(TItem rItem, pParam->lrItem)
 				pComboBoxEditor->addItem(rItem.sDescr);
 			
			pComboBoxEditor->setCurrentIndex(pComboBoxEditor->findText(pItem->text(1)));
			
			pEditor = pComboBoxEditor;

			break;
		}

		case PARAM_TYPE_HEX:
		{
			pEdit = new QLineEdit(parent);

			ValidatorEx *pValidator = new ValidatorEx(pParam->nMin, pParam->nMax, 16, pEdit);

			pEdit->setValidator(pValidator);

			pEditor = pEdit;

			break;
		}

		case PARAM_TYPE_BIN:
		{
			pEdit = new QLineEdit(parent);

			ValidatorEx *pValidator = new ValidatorEx(pParam->nMin, pParam->nMax, 2, pEdit);

			pEdit->setValidator(pValidator);

			pEditor = pEdit;

			break;
		}

		default:
		{
			pEdit = new QLineEdit(parent);
			pEdit->setText(pParam->sValue);
			QFont font = m_pTree->font();
			pEdit->setFont(font);

            connect(pEdit, SIGNAL(editingFinished()), this, SLOT(slotTextChanged()));

			pEditor = pEdit;
		}
	}
		
	// 			if (editor) {
			//	if()
					if(pItem->head()) 
	 				pEditor->setAutoFillBackground(true);
	// 				editor->installEventFilter(const_cast<QtPropertyEditorDelegate *>(this));
	// 				connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
	// 				m_propertyToEditor[property] = editor;
	// 				m_editorToProperty[editor] = property;
	// 				m_editedItem = item;
	// 				m_editedWidget = editor;
	// 			}
	// 			return editor;
	// 		}
	// 	}
	return pEditor;
}

void ParamDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(m_pTree->indexToItem(index));
	QLineEdit *edit = dynamic_cast<QLineEdit *>(editor);
	TIcrParam *pParam = pItem->param();
	QLineEdit *pEdit;
	QSpinBox *pSpinIntEditor;
	DoubleSpinBoxEx *pSpinDoubleEditor;
	QComboBox *pComboBoxEditor;
	U32 nType;
	QString str;
	QStringList lsStr;
	U08 isChanged = 0;

	if(pParam->nType == -1)
		nType = PARAM_TYPE_STRING;
	else
		nType = pParam->nType;

	switch(nType)
	{
		case PARAM_TYPE_SPIN_INT:
		{
			pSpinIntEditor = dynamic_cast<QSpinBox *>(editor);
			pParam->sValue = pSpinIntEditor->text();
			break;
		}

		case PARAM_TYPE_SPIN_DOUBLE:
		{
			pSpinDoubleEditor = dynamic_cast<DoubleSpinBoxEx *>(editor);
			double d = pSpinDoubleEditor->value();
			
			QString str = pSpinDoubleEditor->lineEdit()->text();
			str.sprintf("%50.10f", d);
			str = str.trimmed();
			
			pParam->sValue = str;
			pParam->sValue.replace(",", ".");
			
			if(pParam->sValue.indexOf(".") != -1)
				while(pParam->sValue[pParam->sValue.length() - 1] == '0')
					pParam->sValue = pParam->sValue.left(pParam->sValue.length() - 1);

			if(pParam->sValue[pParam->sValue.length() - 1] == '.')
				pParam->sValue = pParam->sValue.left(pParam->sValue.length() - 1);

			pItem->setText(1, pParam->sValue);

			break;
		}

		case PARAM_TYPE_LIST:
		{
			pComboBoxEditor = dynamic_cast<QComboBox *>(editor);
			str = pComboBoxEditor->currentText();

			foreach(TItem rItem, pParam->lrItem)
			{
				if(rItem.sDescr == pComboBoxEditor->currentText())
				{
					pParam->sValue = rItem.sVal;
					pItem->setText(1, rItem.sDescr);
					break;
				}
			}

			break;
		}

		case PARAM_TYPE_INT:
		case PARAM_TYPE_DOUBLE:
		case PARAM_TYPE_HEX:
		case PARAM_TYPE_BIN:
		default:
		{
			pEdit = dynamic_cast<QLineEdit *>(editor);
			pParam->sValue = pEdit->text();
		}	
	}

// 	if(pParam->sValue != pOldParam->sValue)
// 	{
// 		pItem->setTextColor(1, QColor(255, 0, 0, 255));
// 		isChanged = 1;
// 	}
// 	else
		pItem->setTextColor(1, QColor(0, 0, 0, 255));

	if(nType != PARAM_TYPE_LIST)
		pItem->setText(1, pParam->sValue);

	if(isChanged)
		m_pTree->EmitParamChanged(pItem);

	//QItemDelegate::setModelData(editor, model, index);
}

void ParamDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(m_pTree->indexToItem(index));

 	QStyleOptionViewItemV3 opt = option;
 	if((index.column() == 0) && pItem->head()) 
	{
	 			opt.font.setBold(true);
 			opt.fontMetrics = QFontMetrics(opt.font);
	}

 	QColor c;
 	if(pItem->head()) 
	{
 		c = opt.palette.color(QPalette::Dark);
 		opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::BrightText));
	}

	if(c.isValid())
		painter->fillRect(option.rect, c);
	 	
	opt.state &= ~QStyle::State_HasFocus;
	QItemDelegate::paint(painter, opt, index);
	 
	opt.palette.setCurrentColorGroup(QPalette::Active);
 	QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
 	painter->save();
 	painter->setPen(QPen(color));
 	
	if(!pItem->head()) 
	{
 		int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
 		painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
 	}

 	painter->restore();
}

QSize ParamDelegate::sizeHint(const QStyleOptionViewItem &option,
										 const QModelIndex &index) const
{
//	return QItemDelegate::sizeHint(option, index) + QSize(3, 4);
	return QItemDelegate::sizeHint(option, index) + QSize(3, 8);
}

void ParamDelegate::updateEditorGeometry(QWidget *editor,
													const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(index)
		editor->setGeometry(option.rect.adjusted(0, 0, 0, -1));

//	ParamTreeItem *pItem = dynamic_cast<ParamTreeItem *>(m_pTree->indexToItem(index));

// 	if(pItem->param()->prJiniAttr == 0)
// 		return;

//  	if(pItem->param()->prJiniAttr->nType == PARAM_TYPE_FILE)
//  	{
//   		FilePathWidget *pWidget = dynamic_cast<FilePathWidget *>(editor);
//  		QPushButton *pButton = pWidget->GetButton();
//   		
//  		U32 w = pWidget->height();
//  		
//  		if(w < 26)
//  			w = 26; 
//  
//  		pButton->setFixedWidth(w);
//  	}
}

void ParamDelegate::slotTextChanged()
{
    QLineEdit		*pLineEdit = dynamic_cast<QLineEdit *>(sender());
    QString			text = pLineEdit->text();
	ParamTreeItem	*pItem = dynamic_cast<ParamTreeItem *>(m_pTree->currentItem());
	TIcrParam		*pParam = pItem->param();
	
	pParam->sValue = text;
}