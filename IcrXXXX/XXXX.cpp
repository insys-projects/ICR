#include "XXXX.h"

#include "qwinwidget.h"

#include <QStringList>
#include <QFile>
#include <QTextStream>

typedef QList<TGroup *> GroupList;

QStringList			g_lsNames;	// Названия устройств
QList<U32>			g_lnTypes;	// Типы устройств
QStringList			g_lsFiles;	// Файлы
QList<IcrParamList> g_llIcrParams;
QList<int>			g_lnStructCount;
QList<int>			g_lisBase;
QList<GroupList>	g_llGroup;	// Список групп

void CreateLists(int isBase = 0);
void ParseXml(const QString &sFileName, IcrParamList &lIcrParam, GroupList &lGroup);
TIcrParam ParseField(const QDomElement &cFieldDomEl);
ItemList GetItemsList(const QDomElement &cFieldDomEl);
U08 *FindTag(U08 *pBuf, U32 nTag);

// Получить цвет группы
QColor *GetColorGroup(QDomElement &element);
// Записать в файл цвета группы
void WriteColorGroup(U32 nFileIdx, TGroup *prGroup);

// Установка значения атрибута
void SetAttribute(QString &sTag, const QString &sTagName, const QString &sTagValue);

void XXXX_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo, int isBase)
{
	QByteArray	cArr;
	U32			nCfgMemSize = BASEMOD_CFGMEM_SIZE;
	IcrParamList	lIcrParams;
	GroupList		lGroups;

	if(g_lsNames.isEmpty())
		CreateLists(isBase);

	int curNum = *pNumDev;

	if(curNum == g_lsNames.size())
	{
		*pNumDev = -1;
		return;
	}

	cArr = g_lsNames[curNum].toLocal8Bit();
	lstrcpy(pDevInfo->sName, cArr.data());
	pDevInfo->Type = (ICR_ADMType)g_lnTypes[curNum];

	if(!g_lisBase[curNum])
		nCfgMemSize = SUBMOD_CFGMEM_SIZE;

	pDevInfo->pCfgMem = new UCHAR[nCfgMemSize];
	pDevInfo->nCfgMemSize = nCfgMemSize;

	ParseXml(g_lsFiles[curNum], lIcrParams, lGroups);

	g_llIcrParams << lIcrParams;
	g_llGroup << lGroups;
}

int XXXX_SetProperty(PSUBMOD_INFO pDeviceInfo)
{
	ULONG RealCfgSize = 0;
	UCHAR *pAdmCfgMem = pDeviceInfo->pCfgMem;
//	UCHAR *pEndAdmCfgMem = pAdmCfgMem + SUBMOD_CFGMEM_SIZE;
	UCHAR *pCurCfgMem;
	S32				nIdx = g_lnTypes.indexOf(pDeviceInfo->Type);
	IcrParamList	lIcrParam, lNewIcrParam;
	TIcrParam		rIcrParam;
	U08				isTagFound = 0;
	U32				nVal = 0;

	if(nIdx == -1)
		return 0;

	lIcrParam = g_llIcrParams[nIdx];

	foreach(rIcrParam, lIcrParam)
	{
		if(rIcrParam.nTag != -1)
		{
 			if(rIcrParam.nTag == 0)
 				rIcrParam.nTag = pDeviceInfo->Type;

			pCurCfgMem = FindTag(pAdmCfgMem, rIcrParam.nTag);

			if(pCurCfgMem == 0)
			{
				isTagFound = 0;
				continue;
			}
			else
				isTagFound = 1;

			RealCfgSize += rIcrParam.nSize;
		}
		else if(isTagFound)
		{	// Копирование поля
			nVal = 0;
			memcpy(&nVal, pCurCfgMem + rIcrParam.nOffset, rIcrParam.nSize);

			if((rIcrParam.nType == PARAM_TYPE_DOUBLE) ||
				(rIcrParam.nType == PARAM_TYPE_SPIN_DOUBLE))
				rIcrParam.sValue.setNum((REAL64)nVal / pow(10., (REAL64)rIcrParam.nPrec), 'f', rIcrParam.nPrec);
			else if(rIcrParam.nType == PARAM_TYPE_BIN)
				rIcrParam.sValue.setNum(nVal, 2);
			else if(rIcrParam.nType == PARAM_TYPE_HEX)
				rIcrParam.sValue.setNum(nVal, 16);
			else
				rIcrParam.sValue.setNum(nVal);
		}

		lNewIcrParam << rIcrParam;
	}

	pDeviceInfo->nRealCfgSize = RealCfgSize + 2;

	g_llIcrParams.replace(nIdx, lNewIcrParam);

	return 0;
}

int XXXX_GetProperty(PSUBMOD_INFO pDeviceInfo)
{
	UCHAR*			pEndCfgMem = pDeviceInfo->pCfgMem + SUBMOD_CFGMEM_SIZE/2;
	UCHAR*			pCurCfgMem = pDeviceInfo->pCfgMem;
	S32				nIdx       = g_lnTypes.indexOf(pDeviceInfo->Type);
	IcrParamList	lIcrParam;
	TIcrParam		rIcrParam;
	U08				isFirst = 1;
	U32				nVal = 0;
	REAL64			dVal = 0;		
	U32				nStructSize;

	if(nIdx == -1)
		return 0;

	if(g_lisBase[nIdx])
		pEndCfgMem = pDeviceInfo->pCfgMem + BASEMOD_CFGMEM_SIZE/2;

	lIcrParam = g_llIcrParams[nIdx];

	foreach(rIcrParam, lIcrParam)
	{
		if(rIcrParam.nTag != -1)
		{
			if(!isFirst)
			{	// Не первая структура
				pCurCfgMem = pCurCfgMem + nStructSize;

				if(pCurCfgMem >= pEndCfgMem)
					return 1;
			}
			else
				isFirst = 0;

			if(rIcrParam.nTag == 0)
				rIcrParam.nTag = pDeviceInfo->Type;

			// Копирование тэга
			memcpy(pCurCfgMem, &(rIcrParam.nTag), 2);
			// Копирование размера следующих данных
			nVal = rIcrParam.nSize - 4;
			memcpy(pCurCfgMem + 2, &nVal, 2);

			nStructSize = rIcrParam.nSize;
		}
		else
		{	// Копирование поля
			if((rIcrParam.nType == PARAM_TYPE_DOUBLE) ||
				(rIcrParam.nType == PARAM_TYPE_SPIN_DOUBLE))
			{
				dVal = rIcrParam.sValue.toDouble();
				nVal = dVal * pow(10.,(REAL64)rIcrParam.nPrec);
			}
			else if(rIcrParam.nType == PARAM_TYPE_BIN)
				nVal = rIcrParam.sValue.toInt(0, 2);
			else if(rIcrParam.nType == PARAM_TYPE_HEX)
				nVal = rIcrParam.sValue.toInt(0, 16);
			else
				nVal = rIcrParam.sValue.toInt();

			memcpy(pCurCfgMem + rIcrParam.nOffset, &nVal, rIcrParam.nSize);
		}
	}

	pCurCfgMem = (UCHAR*)pCurCfgMem + nStructSize;

	if(pCurCfgMem >= pEndCfgMem)
		return 1;

	if(!g_lisBase[nIdx])
	{
		*(USHORT *)pCurCfgMem = END_TAG;
		pCurCfgMem += 2;
	}
	
	pDeviceInfo->nRealCfgSize = ULONG(pCurCfgMem - pDeviceInfo->pCfgMem);

	return 0;
}

int XXXX_DialogProperty(PSUBMOD_INFO pDeviceInfo)
{
	S32 nIdx = g_lnTypes.indexOf(pDeviceInfo->Type);

	TGroup *pGroup;

	if(nIdx == -1)
		return 0;

	int argc = 0;
	int nRet = 0;

	IcrXXXXDlg dlg(g_llIcrParams[nIdx], g_llGroup[nIdx]);

	int k  = g_llIcrParams[nIdx].size();
	int k1 = g_llGroup[nIdx].size();

	dlg.resize(500, 124 + 21 * (k - 2 - g_lnStructCount[nIdx]) + 22 * k1);

	HWND parent = GetForegroundWindow();

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251")); 

	dlg.setWindowTitle("Конфигурация " + g_lsNames[nIdx]);

	QWinWidget win( parent );

	Qt::WindowFlags flags = dlg.windowFlags();

	dlg.setParent(&win);

	dlg.setWindowFlags(flags);

	// Показать диалог
	if(dlg.exec())
	{
		g_llIcrParams.replace(nIdx, dlg.GetIcrParams());	

		foreach(pGroup, g_llGroup[nIdx])
			WriteColorGroup(nIdx, pGroup);
	}

	dlg.setParent(0);

	return 0;
}

void XXXX_Close(PSUBMOD_INFO pDevInfo)
{
	TGroup *pGroup;
	GroupList lGroup;
	S32 nIdx = g_lnTypes.indexOf(pDevInfo->Type);

	if(nIdx != -1)
	{
		foreach(pGroup, lGroup)
			delete	pGroup;
	}

	delete[] pDevInfo->pCfgMem;
}

void CreateLists(int isBase)
{
	QStringList		lsNameFilters;
	QStringList		lsFiles;
	QString			sFile;
	QString			sName;
	QString			sType;
	QString			sBase;
	QString			sComp;
	QDir			cDir;
	QFile			cFile;
	QDomDocument	cXmlDocument; 
	QDomElement		cRoot, cElement;

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251"));

	lsNameFilters << "Icr*.xml";
	lsFiles = cDir.entryList(lsNameFilters, QDir::Files);

	if(isBase)
		sComp = "1";

	foreach(sFile, lsFiles)
	{	// Перебор всех файлов
		cFile.setFileName(sFile);

		if(!cFile.open(QFile::ReadOnly | QFile::Text)) 
		{
			cFile.close();
			return;
		}

		if(!cXmlDocument.setContent(&cFile)) 
		{
			cFile.close();

			continue;
		}

		cFile.close();

		cRoot = cXmlDocument.documentElement();

		if(cRoot.nodeName() != "icr")
			continue;

		cElement = cRoot.firstChildElement("dev");

		while(!cElement.isNull())
		{	
			sName = cElement.attribute("name", "");
			sType = cElement.attribute("type", "");
			sBase = cElement.attribute("base", "");

			if((!sName.isEmpty()) && (!sType.isEmpty()) && (sBase == sComp))
			{
				g_lsNames << sName;
				g_lnTypes << sType.toUInt(0, 16);
				g_lsFiles << sFile;

				if(sBase == "1")
					g_lisBase << 1;
				else
					g_lisBase << 0;
			}

			cElement = cElement.nextSiblingElement("dev");
		}
	}
}

void ParseXml(const QString &sFileName, IcrParamList &lIcrParams, GroupList &lGroup)
{
	QFile			cFile(sFileName);
	QDomDocument	cXmlDocument; 
	QDomElement		cRoot, cStructDomEl, cFieldDomEl, cGroupDomEl, child;
	TIcrParam		rIcrParam;
	QString			sStr;
	int				nStructCount = 0;
	TGroup			*prGroup;
	QColor			*pColor;

	if(!cFile.open(QFile::ReadOnly | QFile::Text)) 
	{
		cFile.close();
		g_lnStructCount << nStructCount;
		return;
	}

	if(!cXmlDocument.setContent(&cFile)) 
	{
		cFile.close();
		g_lnStructCount << nStructCount;
		return;
	}

	cFile.close();

	cRoot = cXmlDocument.documentElement();

	if(cRoot.nodeName() != "icr")
	{
		g_lnStructCount << nStructCount;
		return;
	}

	cStructDomEl = cRoot.firstChildElement("struct");

	while(!cStructDomEl.isNull())
	{	// Перебор всех структур	
		// Получение тэга структуры
		sStr = cStructDomEl.attribute("tag", "");

		if(sStr.isEmpty())
		{
			sStr = "0";
			//cStructDomEl = cStructDomEl.nextSiblingElement("struct");
			//continue;
		}

		rIcrParam.nTag = sStr.toUInt(0, 16);
		// ------------------------

		// Получение размера структуры
		sStr = cStructDomEl.attribute("size", "");

		if(sStr.isEmpty())
		{
			cStructDomEl = cStructDomEl.nextSiblingElement("struct");
			continue;
		}

		nStructCount++;

		rIcrParam.nSize = sStr.toUInt();
		// ---------------------------

		lIcrParams << rIcrParam;

		cGroupDomEl  = cStructDomEl.firstChildElement("group");

		while(!cGroupDomEl.isNull())
		{	// Создаем группу
			prGroup = new TGroup;
			pColor = GetColorGroup(cGroupDomEl);
			prGroup->color   = *pColor; // Цвет группы
			prGroup->sName   = cGroupDomEl.attribute("title"); // Название группы
			prGroup->isOpen  = cGroupDomEl.attribute("open", "1").toInt(); // Свернута или развернута группа
			lGroup << prGroup;

			cFieldDomEl = cGroupDomEl.firstChildElement("field");

			while(!cFieldDomEl.isNull())
			{	// Перебор всех полей структуры
				rIcrParam = ParseField(cFieldDomEl);
				rIcrParam.sGroupName = prGroup->sName;
				lIcrParams << rIcrParam;

				cFieldDomEl = cFieldDomEl.nextSiblingElement("field");
			}

			cGroupDomEl = cGroupDomEl.nextSiblingElement("group");
		}

		cFieldDomEl = cStructDomEl.firstChildElement("field");

		while(!cFieldDomEl.isNull())
		{	// Перебор всех полей структуры
			rIcrParam = ParseField(cFieldDomEl);

			if(lGroup.size() > 0)
				rIcrParam.sGroupName = "Прочее";

			lIcrParams << rIcrParam;

			cFieldDomEl = cFieldDomEl.nextSiblingElement("field");
		}

		cStructDomEl = cStructDomEl.nextSiblingElement("struct");
	}

	g_lnStructCount << nStructCount;

	if(lGroup.size() > 0)
	{
		prGroup = new TGroup;
		prGroup->color   = QColor(255, 255, 255); // Цвет группы
		prGroup->sName   = "Прочее"; // Название группы
		prGroup->isOpen  = 1; // Свернута или развернута группа
		lGroup << prGroup;
	}
}

TIcrParam ParseField(const QDomElement &cFieldDomEl)
{
	TIcrParam rIcrParam;
	QString sStr;
	bool	isOk;

	rIcrParam.nTag = -1;

	rIcrParam.sName = cFieldDomEl.attribute("name", "");

	sStr = cFieldDomEl.attribute("offset", "4");
	rIcrParam.nOffset = sStr.toInt();

	sStr = cFieldDomEl.attribute("size", "4");
	rIcrParam.nSize = sStr.toInt();

	rIcrParam.sValue = cFieldDomEl.attribute("default", "");

	rIcrParam.nType = PARAM_TYPE_STRING;

	rIcrParam.isInvisible = cFieldDomEl.attribute("invisible", "0").toInt();

	if(rIcrParam.isInvisible)
		return rIcrParam;

	sStr = cFieldDomEl.attribute("type", "");

	if(sStr == "")
		return rIcrParam;

	if((cFieldDomEl.attribute("type") == "int") ||
		(cFieldDomEl.attribute("type") == "spin-int"))
	{
		// Минимальное значение
		sStr.setNum(INT_MIN);
		rIcrParam.nMin = cFieldDomEl.attribute("min", sStr).toInt();

		// Максимальное значение
		sStr.setNum(INT_MAX);
		rIcrParam.nMax = cFieldDomEl.attribute("max", sStr).toInt();

		if(cFieldDomEl.attribute("type") == "int")
			// Тип
			rIcrParam.nType = PARAM_TYPE_INT;
		else
		{
			// Тип
			rIcrParam.nType = PARAM_TYPE_SPIN_INT;

			// Дельта
			rIcrParam.nInc = cFieldDomEl.attribute("inc", "1").toInt();
		}
	}
	else if(cFieldDomEl.attribute("type") == "hex")
	{
		// Минимальное значение
		sStr.setNum(INT_MIN);
		rIcrParam.nMin = cFieldDomEl.attribute("min", sStr).toInt(&isOk, 16);

		if(!isOk)
			rIcrParam.nMin = INT_MIN;

		// Максимальное значение
		sStr.setNum(INT_MAX);
		rIcrParam.nMax = cFieldDomEl.attribute("max", sStr).toInt(&isOk, 16);

		if(!isOk)
			rIcrParam.nMin = INT_MAX;

		// Тип
		rIcrParam.nType = PARAM_TYPE_HEX;
	}
	else if(cFieldDomEl.attribute("type") == "bin")
	{
		// Минимальное значение
		sStr.setNum(INT_MIN);
		rIcrParam.nMin = cFieldDomEl.attribute("min", sStr).toInt(&isOk, 2);

		if(!isOk)
			rIcrParam.nMin = INT_MIN;

		// Максимальное значение
		sStr.setNum(INT_MAX);
		rIcrParam.nMax = cFieldDomEl.attribute("max", sStr).toInt(&isOk, 2);

		if(!isOk)
			rIcrParam.nMin = INT_MAX;

		// Тип
		rIcrParam.nType = PARAM_TYPE_BIN;
	}
	else if((cFieldDomEl.attribute("type") == "double") || 
		(cFieldDomEl.attribute("type") == "spin-double"))
	{
		// Минимальное значение
		//double limit = std::numeric_limits<double>::min();
		double limit = std::numeric_limits<double>::max();
		sStr.setNum(1.0 - limit);
		rIcrParam.dMin = cFieldDomEl.attribute("min", sStr).toDouble();

		// Максимальное значение
		//limit = std::numeric_limits<double>::max();
		sStr.setNum(limit);
		rIcrParam.dMax = cFieldDomEl.attribute("max", sStr).toDouble();

		// Точность
		rIcrParam.nPrec = cFieldDomEl.attribute("prec", "3").toInt();

		if(cFieldDomEl.attribute("type") == "double")
			// Тип
			rIcrParam.nType = PARAM_TYPE_DOUBLE;
		else
		{
			// Тип
			rIcrParam.nType = PARAM_TYPE_SPIN_DOUBLE;

			// Дельта
			rIcrParam.dInc = cFieldDomEl.attribute("inc", "0.1").toDouble();
		}
	}
	else if(cFieldDomEl.attribute("type") == "list")
	{
		// Тип
		rIcrParam.nType = PARAM_TYPE_LIST;
		rIcrParam.lrItem = GetItemsList(cFieldDomEl);
	}

	return rIcrParam;
}

ItemList GetItemsList(const QDomElement &cFieldDomEl)
{
	TItem rItem;
	QDomElement child = cFieldDomEl.firstChildElement("item");
	ItemList lItems;

	while(!child.isNull())
	{
		rItem.sDescr = child.attribute("descr");
		rItem.sVal   = child.attribute("val");
		lItems << rItem;
		child = child.nextSiblingElement("item");
	}

	return lItems;
}

U08 *FindTag(U08 *pBuf, U32 nTag)
{
	while((*(U16 *)pBuf != nTag) && (*(U16 *)pBuf != END_TAG))
	{
		pBuf += 2;
		pBuf += *(U16 *)pBuf + 2;
	}

	return pBuf;
}

// Получить цвет группы
QColor *GetColorGroup(QDomElement &element)
{
	U32 r, g, b;
	QString str = element.attribute("color");

	if(str.isEmpty())
		return new QColor(255, 255, 255, 255);


	QStringList sList = str.split(",");

	foreach(QString str, sList)
		str = str.trimmed();

	r = sList[0].toInt();
	g = sList[1].toInt();
	b = sList[2].toInt();

	return new QColor(r, g, b, 255);
}

// Записать в файл цвета группы
void WriteColorGroup(U32 nFileIdx, TGroup *prGroup)
{
	QFile file(g_lsFiles[nFileIdx]);
	QDomDocument XmlDocument; 
	QDomElement root, group;
	QString sColor, str, str1, sFileData, sOpen;
	/*	U32 nOpenIdx, nColorIdx, nEndIdx;*/
	QStringList sList;

	if(!file.open(QFile::ReadWrite | QFile::Text)) 
	{
		file.close();
		return;
	}

	QTextStream strm(&file);
	strm.setCodec(QTextCodec::codecForName("UTF8"));

	// Ищем нужную группу
	str = strm.readLine();

	while(!str.isNull())
	{
		if((str.indexOf("title=\"" + prGroup->sName + "\"") != -1) && (str.indexOf("group") != -1))
			break; // Нужная группа найдена

		sFileData += str + '\n';

		str = strm.readLine(); // Чтение новой строки
	}
	// ------------------

	// Установка атрибута color
	str1.setNum(prGroup->color.red());
	sColor = str1 + ",";

	str1.setNum(prGroup->color.green());
	sColor += str1 + ",";

	str1.setNum(prGroup->color.blue());
	sColor += str1;

	SetAttribute(str, QString("color"), sColor);	
	sFileData += str + '\n';
	// -------------------

	sFileData += strm.readAll();

	file.close();

	file.remove();

	if(!file.open(QFile::ReadWrite | QFile::Text)) 
	{
		file.close();
		return;
	}

	strm.setDevice(&file);
	strm.setCodec(QTextCodec::codecForName("UTF8"));
	strm << sFileData;

	file.close();
}

// Установка значения атрибута
void SetAttribute(QString &sTag, const QString &sAttrName, const QString &sTagValue)
{
	QString sOpen, str;
	QStringList sList;
	U32 nStartIdx, nEndIdx, nLen;

	nStartIdx = sTag.indexOf(sAttrName + "=");

	if(nStartIdx == -1)
	{	// Атрибут отсутствует
		sOpen = sTagValue;
		nEndIdx = sTag.indexOf('>');
		sOpen = " " + sAttrName +"=\"" + sOpen + "\"";
		sTag.insert(nEndIdx, sOpen);
	}
	else
	{	// Атрибут присутствует
		str = sTag.right(sTag.length() - nStartIdx); 
		nEndIdx = str.indexOf('\"');
		nEndIdx = str.indexOf('\"', nEndIdx + 1);
		str = str.left(nEndIdx);
		nLen = str.length() + 1;
		sList = str.split("=\"");
		sList[1] = sTagValue;
		str = sList.join("=\"") + '\"';
		sTag.remove(nStartIdx, nLen);
		sTag.insert(nStartIdx, str);
	}
}