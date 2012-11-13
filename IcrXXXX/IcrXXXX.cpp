// #pragma once
// 
// // Modify the following defines if you have to target a platform prior to the ones specified below.
// // Refer to MSDN for the latest info on corresponding values for different platforms.
// #ifndef WINVER				// Allow use of features specific to Windows XP or later.
// #define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
// #endif
// 
// #ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
// #define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
// #endif						
// 
// #ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
// #define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
// #endif
// 
// #ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
// #define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
// #endif
// 
// #define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// // Windows Header Files:

#include "XXXX.h"

#include "qmfcapp.h"

BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/ )
{
	static bool ownApplication = FALSE;

	if ( dwReason == DLL_PROCESS_ATTACH )
		ownApplication = QMfcApp::pluginInstance( hInstance );
	if ( dwReason == DLL_PROCESS_DETACH && ownApplication )
		delete qApp;

	return TRUE;
}

//***************************************************************************************
SUBMOD_API void __stdcall SUBMOD_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo)
{
	XXXX_GetInfo(pNumDev, pDevInfo);
}

//***************************************************************************************
SUBMOD_API void __stdcall SUBMOD_Close(PSUBMOD_INFO pDevInfo)
{
	delete[] pDevInfo->pCfgMem;
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_SetProperty(PSUBMOD_INFO pDeviceInfo)
{
	return XXXX_SetProperty(pDeviceInfo);
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_GetProperty(PSUBMOD_INFO pDeviceInfo)
{
	return XXXX_GetProperty(pDeviceInfo);
}

//***************************************************************************************
SUBMOD_API int __stdcall SUBMOD_DialogProperty(PSUBMOD_INFO pDeviceInfo)
{
	return XXXX_DialogProperty(pDeviceInfo);
}