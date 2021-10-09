// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Brain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugString(L"[*] Brain Initilizing...");
        if (InitilizeBrain())
        {
            OutputDebugString(L"[+] Brain Initilized successfully");
        }
        else
        {
            OutputDebugString(L"[-] Brain initialization Failed");
        }
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        OutputDebugString(L"[+] Brain Detached");
        break;
    }
    return TRUE;
}

