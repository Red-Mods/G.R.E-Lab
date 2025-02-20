#include <pch.h>



BOOL APIENTRY DllMain(HMODULE _Module, DWORD _ReasonForCall, LPVOID _Reserved)
{
    switch (_ReasonForCall)
    {
        case DLL_PROCESS_ATTACH:
        {
            Application::Get()->Initialize(_Module);
        }
        break;
        case DLL_PROCESS_DETACH:
        {
            Application::Get()->Shutdown();
        }
        break;
    }

    return TRUE;
}