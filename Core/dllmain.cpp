// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            MessageBoxA(NULL, "Succesfully injected Core.dll inside Red Dead Redemption !", "Info", MB_OK | MB_ICONINFORMATION);
        }
        break;
        case DLL_PROCESS_DETACH:
        {

        }
        break;
    }
    return TRUE;
}

