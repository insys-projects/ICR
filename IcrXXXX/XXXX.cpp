#include "XXXX.h"

#include "qwinwidget.h"

#include <QStringList>

QStringList g_lsNames;	// Названия устройств
QList<U32>	g_lnTypes;	// Типы устройств
QStringList g_lsFiles;	// Файлы
QList<IcrParamList> g_llIcrParams;
QList<int> g_lnStructCount;
QList<int> g_lisBase;

void CreateLists(int isBase = 0);
IcrParamList ParseXml(const QString &sFileName);
TIcrParam ParseField(const QDomElement &cFieldDomEl);
ItemList GetItemsList(const QDomElement &cFieldDomEl);
U08 *FindTag(U08 *pBuf, U32 nTag);

void XXXX_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo, int isBase)
{
	QByteArray	cArr;
	U32			nCfgMemSize = BASEMOD_CFGMEM_SIZE;

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

	g_llIcrParams << ParseXml(g_lsFiles[curNum]);
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
	QSize parentSize, dlgSize;
	RECT  pos;
	int   nX, nY;

	if(nIdx == -1)
		return 0;

	int argc = 0;
	int nRet = 0;

	IcrXXXXDlg dlg(g_llIcrParams[nIdx]);

	int k = g_llIcrParams[nIdx].size();

	dlg.resize(500, 124 + 21 * (k - 2 - g_lnStructCount[nIdx]));

	HWND parent = GetForegroundWindow();

	// Вычисление координат размещения диалога
	GetWindowRect(parent, &pos);
	
	dlgSize = dlg.size();

	nX = (pos.right - pos.left - dlgSize.width()) / 2;
	nY = (pos.bottom - pos.top - dlgSize.height()) / 2;

	dlg.move(pos.left + nX, pos.top + nY);
	// ---------------------------------------
	
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251")); 

	dlg.setWindowTitle("Конфигурация " + g_lsNames[nIdx]);

	QWinWidget win( parent );

	Qt::WindowFlags flags = dlg.windowFlags();

	dlg.setParent(&win);

	dlg.setWindowFlags(flags);

	// Показать диалог
	if(dlg.exec())
		g_llIcrParams.replace(nIdx, dlg.GetIcrParams());	

	dlg.setParent(0);

	return 0;
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

IcrParamList ParseXml(const QString &sFileName)
{
	QFile			cFile(sFileName);
	QDomDocument	cXmlDocument; 
	QDomElement		cRoot, cStructDomEl, cFieldDomEl;
	TIcrParam		rIcrParam;
	QString			sStr;
	IcrParamList	lIcrParams;
	int				nStructCount = 0;

	if(!cFile.open(QFile::ReadOnly | QFile::Text)) 
	{
		cFile.close();
		g_lnStructCount << nStructCount;
		return lIcrParams;
	}

	if(!cXmlDocument.setContent(&cFile)) 
	{
		cFile.close();
		g_lnStructCount << nStructCount;
		return lIcrParams;
	}

	cFile.close();

	cRoot = cXmlDocument.documentElement();

	if(cRoot.nodeName() != "icr")
	{
		g_lnStructCount << nStructCount;
		return lIcrParams;
	}

	cStructDomEl = cRoot.firstChildElement("struct");

	while(!cStructDomEl.isNull())
	{	// Перебор всех структур	
		// Получение тэга структуры
		sStr = cStructDomEl.attribute("tag", "");

		if(sStr.isEmpty())
		{
			cStructDomEl = cStructDomEl.nextSiblingElement("struct");
			continue;
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

		cFieldDomEl = cStructDomEl.firstChildElement("field");

		while(!cFieldDomEl.isNull())
		{	// Перебор всех полей структуры
			rIcrParam = ParseField(cFieldDomEl);

			lIcrParams << rIcrParam;

			cFieldDomEl = cFieldDomEl.nextSiblingElement("field");
		}

		cStructDomEl = cStructDomEl.nextSiblingElement("struct");
	}

	g_lnStructCount << nStructCount;

	return lIcrParams;
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