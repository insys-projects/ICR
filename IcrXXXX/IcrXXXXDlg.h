#ifndef ICRXXXXDLG_H
#define ICRXXXXDLG_H

#include <QtGui/QMainWindow>

#include "ui_IcrXXXXDlg.h"

class IcrXXXXDlg : public QDialog, public Ui::IcrXXXXDlgClass
{
	Q_OBJECT

	QList<TIcrParam *>	m_lpIcrParams;
	QList<TGroup *> m_lpGroup;
	QMultiMap<QString, ParamTreeItem *> m_mpGroupItems;

public:
	IcrXXXXDlg(const IcrParamList &lIcrParams, QList<TGroup *> &lpGroup, QWidget *parent = 0, Qt::WFlags flags = 0);
	~IcrXXXXDlg();

	IcrParamList GetIcrParams();
	QList<TGroup *> GetGroups();
 
private:
	void FillTree();
	void SetIcrParams(const IcrParamList &lIcrParams);

protected:
	virtual void showEvent(QShowEvent * pEvent);

private slots:
	// Щелчок правой кнопкой
	void slotItemRightClicked();
	// Изменить цвет группы
	void slotColorGroup();
	// Изменить шрифт
	void slotFontChange();
};

#endif // ICRXXXXDLG_H
