#include "pch.h"

DWORD BrainPrintString(BYTE* input_buffer)
{
    BYTE unicode_buffer[2048] = { 0 };
    MultiByteToWideChar(CP_ACP,
        NULL,
        (LPCCH)input_buffer,
        -1,
        (LPWSTR)unicode_buffer,
        1024);

    /* do something with data in buffer */
    OutputDebugString((LPWSTR)unicode_buffer);
    return 0;
}

DWORD BrainLoadDll(BYTE* input_buffer)
{
    return 0;
}