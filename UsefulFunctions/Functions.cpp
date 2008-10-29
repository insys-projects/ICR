#include "stdafx.h"
#include "functions.h"

#pragma warning (disable:4996)

// отображение последней ошибки
void	ShowError()
{ 
    TCHAR szBuf[80]; 
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    wsprintf(szBuf,	"Ошибка: %d: %s", dw, lpMsgBuf); 
 
	AfxMessageBox(szBuf);
}

void TerminateChildProcess(HANDLE *hProcess)
{
	if( *hProcess != 0 )
	{
		DWORD exit = STILL_ACTIVE;
		GetExitCodeProcess(*hProcess, &exit);
		if (exit == STILL_ACTIVE)
		{
			TerminateProcess(*hProcess, 0);
			CloseHandle(*hProcess);
		}
		*hProcess = 0;
	}
}

int ReadRegistryString(char *pcRoot, char *pcValueName, char *sReg, DWORD nSize)
{
	CRegKey key;
	LONG status = key.Open(HKEY_CURRENT_USER, pcRoot);
	if( status == ERROR_SUCCESS )
		status = key.QueryValue(sReg, pcValueName, &nSize);
	key.Close();

	return (int)status;
}

int ReadRegistryHKLMString(char *pcRoot, char *pcValueName, char *sReg, DWORD nSize)
{
	CRegKey key;
	LONG status = key.Open(HKEY_LOCAL_MACHINE, pcRoot);
	if( status == ERROR_SUCCESS )
		status = key.QueryValue(sReg, pcValueName, &nSize);
	key.Close();

	return (int)status;
}

int ReadRegistryValue(char *pcRoot, char *pcValueName, DWORD *nReg)
{
	CRegKey key;
	LONG status = key.Open(HKEY_CURRENT_USER, pcRoot);
	if( status == ERROR_SUCCESS )
		status = key.QueryValue(*nReg, pcValueName);
	key.Close();

	return (int)status;
}

void WriteRegistryString(char *pcRoot, char *pcValueName, CString sReg)
{
	CRegKey key;
	key.Create(HKEY_CURRENT_USER, pcRoot);
	key.SetValue((LPCTSTR)sReg, pcValueName);
	key.Close();
}

void WriteRegistryValue(char *pcRoot, char *pcValueName, DWORD nReg)
{
	CRegKey key;
	key.Create(HKEY_CURRENT_USER, pcRoot);
	key.SetValue(nReg, pcValueName);
	key.Close();
}

void GetDirFromCommandLine(char *pcDir)
{
	CString sCmdLine = GetCommandLine() + 1;
	sCmdLine = sCmdLine.Left(sCmdLine.Find('\"'));
	sCmdLine = sCmdLine.Left(sCmdLine.ReverseFind('\\')+1);
	strcpy(pcDir, sCmdLine.GetBuffer());
}

CString GetCurDirFromCommandLine()
{
	CString sCurDir = GetCommandLine() + 1;
	sCurDir = sCurDir.Left(sCurDir.Find('\"'));
	sCurDir = sCurDir.Left(sCurDir.ReverseFind('\\')+1);
	return sCurDir;
}

CString	GetCurDir()
{
	char acCurDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, acCurDir);
	CString sCurDir = "";
	sCurDir.SetString(acCurDir);
	
	return sCurDir;
}

int ReadFileData(CString sFileName, CString* sData)
{
	HANDLE hFile = CreateFile(	sFileName, 
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	
	int	nFileSize = GetFileSize(hFile, 0);
	if( nFileSize < 0 )
		return -1;
	
	int	nBytesRead = 0;
	char	*pcFileData = new char[nFileSize+20];
	
	ReadFile(hFile, pcFileData, nFileSize, (LPDWORD)&nBytesRead, NULL);
	pcFileData[nBytesRead] = 0;
	*sData = pcFileData;
	CloseHandle(hFile);
	delete [] pcFileData;

	return 1;
}

int WriteFileData(CString sFileName, CString sData)
{
	HANDLE hfile = CreateFile(	sFileName, 
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	DWORD dwBytesWritten;
	WriteFile(hfile, (LPCVOID)sData, sData.GetLength(), &dwBytesWritten, NULL);
	CloseHandle(hfile);

	return 1;
}

int FindProcess(PROCESSENTRY32* ppe, char* pcProcess, DWORD nExcludeProcessId)
{
	HANDLE	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	int	nRes = Process32First(hSnapshot, ppe);
	while( nRes )
	{
		if( strcmp(ppe->szExeFile, pcProcess) == 0 )
		{
			if( nExcludeProcessId != ppe->th32ProcessID )
				break;
		}
		nRes = Process32Next(hSnapshot, ppe);
	}
	return nRes;
}

int		FindChildProcess(PROCESSENTRY32* ppe, char* pcProcess, DWORD nParentProcessId)
{
	HANDLE	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	int	nRes = Process32First(hSnapshot, ppe);
	while( nRes )
	{
		if( strcmp(ppe->szExeFile, pcProcess) == 0 )
		{
			if( ppe->th32ParentProcessID == nParentProcessId )
				break;
		}
		nRes = Process32Next(hSnapshot, ppe);
	}
	return nRes;
}

CString GetExtensionOfFile(CString sFileName)
{
	CString sExtension = "";
	if( sFileName.ReverseFind('.') != -1 )
		sExtension = sFileName.Mid(sFileName.ReverseFind('.'));
	return sExtension;
}

CString	GetFileNameOfPath(CString sFilePath)
{
	CString sFileName = "";
	if( sFilePath.ReverseFind('\\') != -1 )
		sFileName = sFilePath.Mid(sFilePath.ReverseFind('\\')+1);
	return sFileName;
}

CString	GetDirOfPath(CString sFilePath)
{
	CString sFileDir = "";
	if( sFilePath.ReverseFind('\\') != -1 )
		sFileDir = sFilePath.Left(sFilePath.ReverseFind('\\') + 1);
	return sFileDir;
}

void GetMemoryInfo()
{
	int WIDTH = 7;
	int DIV = 1024;
	char *divisor = "K";

	MEMORYSTATUS stat;
	GlobalMemoryStatus (&stat);

	CString sOut = "";
	CString sTmp = "";
	sTmp.Format("%ld percent of memory is in use.\n", stat.dwMemoryLoad);
	sOut += sTmp;
	sTmp.Format("There are %*ld total %sbytes of physical memory.\n",WIDTH, stat.dwTotalPhys/DIV, divisor);
	sOut += sTmp;
	sTmp.Format("There are %*ld free %sbytes of physical memory.\n",WIDTH, stat.dwAvailPhys/DIV, divisor);
	sOut += sTmp;
	sTmp.Format("There are %*ld total %sbytes of paging file.\n",WIDTH, stat.dwTotalPageFile/DIV, divisor);
	sOut += sTmp;
	sTmp.Format("There are %*ld free %sbytes of paging file.\n",WIDTH, stat.dwAvailPageFile/DIV, divisor);
	sOut += sTmp;
	sTmp.Format("There are %*ld total %sbytes of virtual memory.\n",WIDTH, stat.dwTotalVirtual/DIV, divisor);
	sOut += sTmp;
	sTmp.Format("There are %*ld free %sbytes of virtual memory.\n",WIDTH, stat.dwAvailVirtual/DIV, divisor);
	sOut += sTmp;

	AfxMessageBox(sOut);
}
