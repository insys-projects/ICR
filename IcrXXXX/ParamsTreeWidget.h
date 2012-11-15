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
	// Общие
	QString	sTitle; 
	QString sSection;		// Секция
	QString sName;			// Имя параметра
	QString sComment;		// Комментарий
	QString sGroupName;		// Имя группы
	U32		nType;			// Тип
	U32		isInvisible;	// 1 - параметр неотображаемый
	U32		isNoEdit;		// 1 - параметр нередактируемый

	// Только для "spin_int"
	S32		nMin; // Минимальное значение 
	S32		nMax; // Максимальное значение
	U32		nInc; // Дельта
	
	// Только для "spin_double"
	REAL64	dMin; // Минимальное значение
	REAL64	dMax; // Максимальное значение
	REAL64	dInc; // Дельта

	// Только для "file"
	QString sPattern; // Фильтрация файлов
	QString *psOpenFileDir;

	// Только для "list"
	QVector<TJiniListItem *> vrJiniParamListItem;
} TJiniAttributes; // jini аттрибуты

struct TParam  
{
	QString sName;		// Имя параметра
	QString sValue;		// Значение параметра
	QString sComment;	// Комментарий
	QString sSection;   // Секция
	U08		isEnable;	// 0 - закомментированный параметр
	U08		isFlag;
	TJiniAttributes	*prJiniAttr; // jini аттрибуты

	TParam(){prJiniAttr = 0;}

} ; // Параметр ини файла

typedef struct  
{
	QString	sName;		// Название группы
	QColor	color;		// Цвет группы
	U08		isOpen;	    // 0 - свернуть группу, 1 - развернуть группу 
} TGroup;	// Группа jini файла

class ParamTreeItem : public QTreeWidgetItem
{
	U08		m_isHead; // Является ли item названием группы
	TIcrParam *m_pParam;
	TParam	*m_pOldParam; // Используется для проверки изменений
	QColor	m_ColorGroup; // Цвет группы
	
public:
	ParamTreeItem() : QTreeWidgetItem(){m_pOldParam = new TParam;}

	// Добавить элемент
	void addChild(ParamTreeItem *pItem){QTreeWidgetItem::addChild(dynamic_cast<QTreeWidgetItem *>(pItem));}

	// Узнать является ли item заголовком
	U08 head(){return m_isHead;}
	// Установить тип item-a
	void setHead(U08 isFlag = 1){m_isHead = isFlag;}
	// Установить цвет группы
        void SetColorGroup(const QColor &color){m_ColorGroup = color;}
	// Получить цвет группы
	QColor ColorGroup(){return m_ColorGroup;}
	// Сделать item доступным для редактирования
	void setEnable(U08 isEnable);

	void setCheckState(U08 isCheck);

	// Получить параметр
	TIcrParam *param(){return m_pParam;}
	// Получить первоначальный параметр
	TParam *OldParam(){return m_pOldParam;}
	// Установить параметр
	void setParam(TIcrParam *pParam){m_pParam = pParam;}
};

class ParamsTreeWidget : public QTreeWidget
{
	Q_OBJECT

	QIcon m_icon;
	U08 m_isCheck;
	U08 m_isCheckEnable; // 1 - возможность комментирования/раскомментирования параметров

public:
	ParamsTreeWidget(QWidget *parent = 0);

	QTreeWidgetItem *indexToItem(const QModelIndex &index) const {return itemFromIndex(index);}
	// Добавить параметр
	void AddParam(QString sNameGroup, TIcrParam *pParam);
	// Удалить все параметры
	void DeleteAllParam();
	// Добавить группу
	ParamTreeItem *AddGroup(TGroup *prGroup);
	
	void ExpandedGroups(QList<TGroup *> &lpGroup);

	// Установить возможность комментирования/раскомментирования параметров
	void SetCheckEnable(U08 isCheckEnable){m_isCheckEnable = isCheckEnable;}

	// Обновление дерева
	void Update();

	// Значение параметра изменилось
	void EmitParamChanged(ParamTreeItem *pItem){emit signalParamChanged(pItem);}

protected:
	// Прорисовка рядов
	void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

signals:
	void signalItemRightClicked();

	// Значение параметра изменилось
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
	// Значение параметра изменилось
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
