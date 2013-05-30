#ifndef STRFUN_H
#define STRFUN_H

int STR_Clear(char *pSrc);
int STR_Fill(char *pSrc, char cFill);
int STR_IndexOf(char *pSrc, char *pFind, int nFrom = 0);
int STR_Insert(char *pSrc, char *pDst, char *pInsert, int nPos);
int STR_LastIndexOf(char *pSrc, char *pFind, int nFrom = 0);
int STR_Left(char *pSrc, char *pDst, int n);
int STR_Mid(char *pSrc, char *pDst, int nPos, int n);
int STR_Remove(char *pSrc, char *pDst, int nPos, int n);
int STR_Remove(char *pSrc, char *pDst, char *pRemove);
int STR_Replace(char *pSrc, char *pDst, char *pBefore, char *pAfter);
int STR_Right(char *pSrc, char *pDst, int n);
int STR_Trimmed(char *pSrc, char *pDst);

#endif // STRFUN_H