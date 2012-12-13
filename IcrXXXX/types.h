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
	QString sName;		// ��� ���������
	QString sValue;		// �������� ���������
	QString sDefValue;	// �������� �� ��������� 
	U32		nOffset;	// �������� � ���������
	U32		nSize;		// ������
	S32		nTag;		// ���
	S32		nType;		// ��� ���������

	// ������ ��� "spin_int", "int", "hex"
	S32		nMin; // ����������� �������� 
	S32		nMax; // ������������ ��������
	U32		nInc; // ������

	// ������ ��� "spin_double", "double"
	REAL64	dMin;	// ����������� ��������
	REAL64	dMax;	// ������������ ��������
	REAL64	dInc;	// ������
	U32		nPrec;	// ��������

	// ������ ��� "list"
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