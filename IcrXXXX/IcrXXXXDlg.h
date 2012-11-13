#ifndef ICRXXXXDLG_H
#define ICRXXXXDLG_H

#include <QtGui/QMainWindow>

#include "ui_IcrXXXXDlg.h"

class IcrXXXXDlg : public QDialog, public Ui::IcrXXXXDlgClass
{
	QList<TIcrParam *> m_lpIcrParams;

public:
	IcrXXXXDlg(const IcrParamList &lIcrParams, QWidget *parent = 0, Qt::WFlags flags = 0);
	~IcrXXXXDlg();

	IcrParamList GetIcrParams();
 
private:
	void FillTree();
	void SetIcrParams(const IcrParamList &lIcrParams);
};

#endif // ICRXXXXDLG_H
