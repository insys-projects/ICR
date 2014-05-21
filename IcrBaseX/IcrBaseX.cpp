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
SUBMOD_API void __stdcall BASEMOD_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo)
{
	XXXX_GetInfo(pNumDev, pDevInfo, 1);
}

//***************************************************************************************
SUBMOD_API void __stdcall BASEMOD_Close(PSUBMOD_INFO pDevInfo)
{
	XXXX_Close(pDevInfo);
}

//***************************************************************************************
SUBMOD_API int __stdcall BASEMOD_SetProperty(PSUBMOD_INFO pDeviceInfo)
{
	return XXXX_SetProperty(pDeviceInfo);
}

//***************************************************************************************
SUBMOD_API int __stdcall BASEMOD_GetProperty(PSUBMOD_INFO pDeviceInfo)
{
	return XXXX_GetProperty(pDeviceInfo);
}

//***************************************************************************************
SUBMOD_API int __stdcall BASEMOD_DialogProperty(PSUBMOD_INFO pDeviceInfo)
{
	return XXXX_DialogProperty(pDeviceInfo);
}