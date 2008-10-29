#include <atlbase.h>
#include "Tlhelp32.h"

void	ShowError();
void	TerminateChildProcess(HANDLE *hProcess);
int		ReadRegistryString(char *pcRoot, char *pcValueName, char *sReg, DWORD nSize);
int		ReadRegistryHKLMString(char *pcRoot, char *pcValueName, char *sReg, DWORD nSize);
int		ReadRegistryValue(char *pcRoot, char *pcValueName, DWORD *nReg);
void	WriteRegistryString(char *pcRoot, char *pcValueName, CString sReg);
void	WriteRegistryValue(char *pcRoot, char *pcValueName, DWORD nReg);
void	GetDirFromCommandLine(char *pcPath);
CString GetCurDirFromCommandLine();
CString	GetCurDir();
int		ReadFileData(CString sFileName, CString* sData);
int		WriteFileData(CString sFileName, CString sData);
int		FindProcess(PROCESSENTRY32* ppe, char* pcProcess, DWORD nExcludeProcessId = -1);
int		FindChildProcess(PROCESSENTRY32* ppe, char* pcProcess, DWORD nParentProcessId);
CString	GetExtensionOfFile(CString sFileName);
CString	GetFileNameOfPath(CString sFileName);
CString	GetDirOfPath(CString sFilePath);
void	GetMemoryInfo();
