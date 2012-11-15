#include "utypes.h"

#include "types.h"

#include <QTreeWidget>
#include <QItemDelegate>
#include <QDoubleSpinBox>
#include <QLineEdit>

enum
{
	PARAM_TYPE_STRING,
	PARAM_TYPE_INT,
	PARAM_TYPE_DOUBLE,
	PARAM_TYPE_SPIN_INT,
	PARAM_TYPE_SPIN_DOUBLE,
	PARAM_TYPE_LIST,
	PARAM_TYPE_CHECK,
	PARAM_TYPE_HEX,
	PARAM_TYPE_BIN
};

typedef struct 
{
	QString	sVal;
	QString	sDescr;
} TJiniListItem;

typedef struct 
{
	// �����
	QString	sTitle; 
	QString sSection;		// ������
	QString sName;			// ��� ���������
	QString sComment;		// �����������
	QString sGroupName;		// ��� ������
	U32		nType;			// ���
	U32		isInvisible;	// 1 - �������� ��������������
	U32		isNoEdit;		// 1 - �������� ���������������

	// ������ ��� "spin_int"
	S32		nMin; // ����������� �������� 
	S32		nMax; // ������������ ��������
	U32		nInc; // ������
	
	// ������ ��� "spin_double"
	REAL64	dMin; // ����������� ��������
	REAL64	dMax; // ������������ ��������
	REAL64	dInc; // ������

	// ������ ��� "file"
	QString sPattern; // ���������� ������
	QString *psOpenFileDir;

	// ������ ��� "list"
	QVector<TJiniListItem *> vrJiniParamListItem;
} TJiniAttributes; // jini ���������

struct TParam  
{
	QString sName;		// ��� ���������
	QString sValue;		// �������� ���������
	QString sComment;	// �����������
	QString sSection;   // ������
	U08		isEnable;	// 0 - ������������������ ��������
	U08		isFlag;
	TJiniAttributes	*prJiniAttr; // jini ���������

	TParam(){prJiniAttr = 0;}

} ; // �������� ��� �����

typedef struct  
{
	QString	sName;		// �������� ������
	QColor	color;		// ���� ������
	U08		isOpen;	    // 0 - �������� ������, 1 - ���������� ������ 
} TGroup;	// ������ jini �����

class ParamTreeItem : public QTreeWidgetItem
{
	U08		m_isHead; // �������� �� item ��������� ������
	TIcrParam *m_pParam;
	TParam	*m_pOldParam; // ������������ ��� �������� ���������
	QColor	m_ColorGroup; // ���� ������
	
public:
	ParamTreeItem() : QTreeWidgetItem(){m_pOldParam = new TParam;}

	// �������� �������
	void addChild(ParamTreeItem *pItem){QTreeWidgetItem::addChild(dynamic_cast<QTreeWidgetItem *>(pItem));}

	// ������ �������� �� item ����������
	U08 head(){return m_isHead;}
	// ���������� ��� item-a
	void setHead(U08 isFlag = 1){m_isHead = isFlag;}
	// ���������� ���� ������
        void SetColorGroup(const QColor &color){m_ColorGroup = color;}
	// �������� ���� ������
	QColor ColorGroup(){return m_ColorGroup;}
	// ������� item ��������� ��� ��������������
	void setEnable(U08 isEnable);

	void setCheckState(U08 isCheck);

	// �������� ��������
	TIcrParam *param(){return m_pParam;}
	// �������� �������������� ��������
	TParam *OldParam(){return m_pOldParam;}
	// ���������� ��������
	void setParam(TIcrParam *pParam){m_pParam = pParam;}
};

class ParamsTreeWidget : public QTreeWidget
{
	Q_OBJECT

	QIcon m_icon;
	U08 m_isCheck;
	U08 m_isCheckEnable; // 1 - ����������� ���������������/������������������ ����������

public:
	ParamsTreeWidget(QWidget *parent = 0);

	QTreeWidgetItem *indexToItem(const QModelIndex &index) const {return itemFromIndex(index);}
	// �������� ��������
	void AddParam(QString sNameGroup, TIcrParam *pParam);
	// ������� ��� ���������
	void DeleteAllParam();
	// �������� ������
	ParamTreeItem *AddGroup(TGroup *prGroup);
	
	void ExpandedGroups(QList<TGroup *> &lpGroup);

	// ���������� ����������� ���������������/������������������ ����������
	void SetCheckEnable(U08 isCheckEnable){m_isCheckEnable = isCheckEnable;}

	// ���������� ������
	void Update();

	// �������� ��������� ����������
	void EmitParamChanged(ParamTreeItem *pItem){emit signalParamChanged(pItem);}

protected:
	// ���������� �����
	void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

signals:
	void signalItemRightClicked();

	// �������� ��������� ����������
	void signalParamChanged(ParamTreeItem *);
};

class ParamDelegate : public QItemDelegate
{
	Q_OBJECT

	ParamsTreeWidget *m_pTree;
	QString m_sValueOld;

public:
	ParamDelegate(QObject *parent = 0) : QItemDelegate(parent){m_sValueOld ="";}
	void setParamsTree(ParamsTreeWidget * tree){m_pTree = tree;}
	QWidget*createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const; 

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
	// �������� ��������� ����������
	void signalParamChanged(ParamTreeItem *);

private slots:
        void slotTextChanged();
};

class DoubleSpinBoxEx : public QDoubleSpinBox
{
	Q_OBJECT

	U08 m_isFirst;

public:
	DoubleSpinBoxEx(QWidget *parent = 0) : QDoubleSpinBox(parent)
	{
		setSingleStep(0.1);
	}

	QString textFromValue(double value) const
	{
		QString str = QDoubleSpinBox::textFromValue(value);

		if(str.indexOf(",") != -1)
			while(str[str.length() - 1] == '0')
				str = str.left(str.length() - 1);

		if(str[str.length() - 1] == ',')
			str = str.left(str.length() - 1);

		return str;
	}

// 	 void stepBy(int steps)
// 	{
// 		double oldValue = value();
// 
// 		QDoubleSpinBox::stepBy(steps);
// 
// 		float step = singleStep();
// 
// 		if(steps == 1)
// 			setValue(oldValue - singleStep());
// 		else
// 			setValue(oldValue + singleStep());
// 
// 		selectAll();
// 	}

	QLineEdit *lineEdit(){return QDoubleSpinBox::lineEdit();}
};
