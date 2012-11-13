#include "XXXX.h"

//***************************************************************************************
SUBMOD_API void __stdcall BASEMOD_GetInfo(int* pNumDev, PSUBMOD_INFO pDevInfo)
{
	XXXX_GetInfo(pNumDev, pDevInfo, 1);
}

//***************************************************************************************
SUBMOD_API void __stdcall BASEMOD_Close(PSUBMOD_INFO pDevInfo)
{
	delete[] pDevInfo->pCfgMem;
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