#include "str_fun.h"

#include <string.h>

int STR_Clear(char *pSrc)
{
	if(pSrc == 0)
		return -1;

	pSrc[0] = '\0';

	return 0;
}

int STR_Fill(char *pSrc, char cFill)
{
	int i;
	int nSize;

	if(pSrc == 0)
		return -1;

	nSize = strlen(pSrc);

	for(i = 0; i < nSize; i++)
		pSrc[i] = cFill;

	return 0;
}

int STR_IndexOf(char *pSrc, char *pFind, int nFrom)
{
	char *pStr;
	int nSize;
	int nIdx;

	if(pSrc == 0)
		return -2;

	if(pFind == 0)
		return -3;

	if(nFrom < 0)
		return -4;

	nSize = strlen(pSrc);

	if(nFrom > (nSize - 1))
		return -5;

	pStr = pSrc + nFrom;

	nIdx = strstr(pStr, pFind) - pStr + nFrom;

	if(nIdx < 0)
		return -1;

	return nIdx;
}

int STR_Insert(char *pSrc, char *pDst, char *pInsert, int nPos)
{
	char *pStr, *pStrEnd;
	int nSize;

	if(pSrc == 0)
		return -1;

	if(pInsert == 0)
		return -2;

	if(nPos < 0)
		return -3;

	if(pDst == 0)
		pStr = pSrc;
	else
		pStr = pDst;

	if(pStr != pSrc)
		strcpy(pStr, pSrc);

	nSize = strlen(pStr); 

	if(nPos > nSize)
		return -4;

	pStrEnd = new char[nSize + 1];
	
	strcpy(pStrEnd, pStr + nPos);
	pStr[nPos] = '\0';
	strcat(pStr, pInsert);
	strcat(pStr, pStrEnd);

	delete [] pStrEnd;

	return 0;
}

int STR_LastIndexOf(char *pSrc, char *pFind, int nFrom)
{
	int nIdx;
	int nRetIdx = -1;

	for(;;)
	{
		nIdx = STR_IndexOf(pSrc, pFind, nFrom);

		if(nIdx < 0)
			break;

		nFrom = nIdx + 1;
		nRetIdx = nIdx;
	}

	if((nRetIdx < 0) && (nIdx < 0))
		nRetIdx = nIdx;

	return nRetIdx;
}

int STR_Left(char *pSrc, char *pDst, int n)
{
	int nRet = STR_Mid(pSrc, pDst, 0, n);

	return nRet;

// 	char *pStr;
// 	int  nSize;
// 
// 	if(pSrc == 0)
// 		return -1;
// 
// 	if(n < 0)
// 		return -2;
// 
// 	if(pDst == 0)
// 		pStr = pSrc;
// 	else
// 		pStr = pDst;
// 
// 	if(pStr != pSrc)
// 		strcpy(pStr, pSrc);
// 
// 	nSize = strlen(pStr); 
// 
// 	if(n > nSize)
// 		return -3;
// 
// 	pStr[nSize - n] = '\0';
// 
// 	return 0;
}

int STR_Mid(char *pSrc, char *pDst, int nPos, int n)
{
	char *pStr;
	int  nSize;

	if(pSrc == 0)
		return -1;

	if(n < 0)
		return -2;

	if(pDst == 0)
		pStr = pSrc;
	else
		pStr = pDst;

	if(pStr != pSrc)
		strcpy(pStr, pSrc);

	nSize = strlen(pStr); 

	if((n + nPos) > nSize)
		return -3;

	if(nPos < 0)
		return -4;

	strcpy(pStr, pStr + nPos);
	
	pStr[n] = '\0';

	return 0;
}

int STR_Remove(char *pSrc, char *pDst, int nPos, int n)
{
	char *pStr;
	int  nSize;

	if(pSrc == 0)
		return -1;

	if(n < 0)
		return -2;

	if(pDst == 0)
		pStr = pSrc;
	else
		pStr = pDst;

	if(pStr != pSrc)
		strcpy(pStr, pSrc);

	nSize = strlen(pStr); 

	if((n + nPos) > nSize)
		return -3;

	if(nPos < 0)
		return -4;

	if((n - nPos) == nSize)
		return STR_Clear(pStr);
	else
	{
		strncpy(pStr + nPos, pStr + nPos + n, nSize - nPos - n);
		pStr[nSize - n] = '\0';
	}

	return 0;
}

int STR_Remove(char *pSrc, char *pDst, char *pRemove)
{	
	char *pStr;
	int nSize;
	int nIdx;

	if(pSrc == 0)
		return -1;

	if(pRemove == 0)
		return -2;

	nSize = strlen(pRemove);

	if(pDst == 0)
		pStr = pSrc;
	else
		pStr = pDst;

	if(pStr != pSrc)
		strcpy(pStr, pSrc);

	for(;;)
	{
		nIdx = STR_IndexOf(pStr, pRemove);

		if(nIdx < 0)
			break;

		STR_Remove(pStr, 0, nIdx, nSize);
	}

	return 0;
}

int STR_Replace(char *pSrc, char *pDst, char *pBefore, char *pAfter)
{
	char *pStr;
	int nIdx;
	int nSize;
	int nPos = 0;

	if(pSrc == 0)
		return -1;

	if(pBefore == 0)
		return -2;

	if(pAfter == 0)
		return -3;
	
	if(pDst == 0)
		pStr = pSrc;
	else
		pStr = pDst;

	if(pStr != pSrc)
		strcpy(pStr, pSrc);

	nSize = strlen(pBefore);

	for(;;)
	{
		nIdx = STR_IndexOf(pStr, pBefore, nPos);

		if(nIdx < 0)
			break;

		STR_Remove(pStr, 0, nIdx, nSize);

		STR_Insert(pStr, 0, pAfter, nIdx);

		nPos = nIdx + strlen(pAfter); 
	}

	return 0;
}

int STR_Right(char *pSrc, char *pDst, int n)
{
	int nRet;
	int nSize;

	if(pSrc == 0)
		return -1;

	if(n < 0)
		return -2;

	nSize = strlen(pSrc) - n; 

	if(nSize < 0)
		return -3;

	nRet = STR_Mid(pSrc, pDst, nSize, n);

	return nRet;
}

int STR_Trimmed(char *pSrc, char *pDst)
{
	char *pStr;
	int i;

	if(pSrc == 0)
		return -1;

	if(pDst == 0)
		pStr = pSrc;
	else
		pStr = pDst;

	if(pStr != pSrc)
		strcpy(pStr, pSrc);

	for(i = 0; i < strlen(pStr); i++)
	{
		if((pStr[0] == '\n') || (pStr[0] == '\r') || (pStr[0] == '\t') || (pStr[0] == ' '))
		{
			STR_Remove(pStr, 0, 0, 1);
			i--;
		}
		else
			break;
	}

	i = strlen(pStr) - 1;

	for(i = strlen(pStr) - 1; i > 0; i--)
	{
		if((pStr[i] == '\n') || (pStr[i] == '\r') || (pStr[i] == '\t') || (pStr[i] == ' '))
			STR_Remove(pStr, 0, i, 1);
		else
			break;
	}

	return 0;
}