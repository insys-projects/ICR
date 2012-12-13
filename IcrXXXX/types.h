#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QList>

#include "utypes.h"

struct TItem
{
	QString	sVal;
	QString	sDescr;
};

typedef QList<TItem>		ItemList;

struct TIcrParam
// class TIcrParam
{
// public:
	QString sName;		// Имя параметра
	QString sValue;		// Значение параметра
	QString sDefValue;	// Значение по умолчанию 
	U32		nOffset;	// Смещение в структуре
	U32		nSize;		// Размер
	S32		nTag;		// Тэг
	S32		nType;		// Тип параметра

	// Только для "spin_int", "int", "hex"
	S32		nMin; // Минимальное значение 
	S32		nMax; // Максимальное значение
	U32		nInc; // Дельта

	// Только для "spin_double", "double"
	REAL64	dMin;	// Минимальное значение
	REAL64	dMax;	// Максимальное значение
	REAL64	dInc;	// Дельта
	U32		nPrec;	// Точность

	// Только для "list"
	ItemList lrItem;

	QString sGroupName;
	
// 	TIcrParam::TIcrParam()
// 	{
// 		sName     = "";		
// 		sValue    = "";		
// 		sDefValue = "";	
// 		nOffset   = 0;	
// 		nSize     = 0;		
// 		nTag      = 0;		
// 	}
// 
// 	TIcrParam::TIcrParam(const TIcrParam &param)
// 	{
// 		sName     = param.sName;		
// 		sValue    = param.sValue;		
// 		sDefValue = param.sDefValue;	
// 		nOffset   = param.nOffset;	
// 		nSize     = param.nSize;		
// 		nTag      = param.nTag;		
// 	}
};

typedef QList<TIcrParam>	IcrParamList;

#endif // TYPES_H