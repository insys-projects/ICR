#ifndef XXXX_H
#define XXXX_H

#include <windows.h>

#include <QString>
#include <QDir>
#include <QtXml/QDomDocument>
#include <QApplication>
#include <QWidget>
#include <QTextCodec>
#include <QMessageBox>

#include <limits>

#undef min
#undef max

#define	SUBMOD_API_EXPORTS
#include "submod.h"

#include "icr.h"

#include "IcrXXXXDlg.h"

#include "types.h"

void XXXX_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo, int isBase = 0);
int XXXX_SetProperty(PSUBMOD_INFO pDeviceInfo);
int XXXX_GetProperty(PSUBMOD_INFO pDeviceInfo);
int XXXX_DialogProperty(PSUBMOD_INFO pDeviceInfo);

#endif // XXXX_H