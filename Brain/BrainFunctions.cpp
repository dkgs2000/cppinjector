#include "pch.h"
#include "Brain.h"

VOID BrainLoadDll(BYTE* input_buffer, OUT BrainAnswer* answer)
{
    answer->function_return_value = 0;
    return;
}


VOID BrainPrintString(BYTE* input_buffer, OUT BrainAnswer* answer)
{
    BYTE unicode_buffer[2048] = { 0 };
    MultiByteToWideChar(CP_ACP,
        NULL,
        (LPCCH)input_buffer,
        -1,
        (LPWSTR)unicode_buffer,
        1024);

    OutputDebugString((LPWSTR)unicode_buffer);

    answer->function_return_value = 0;
    return;
}
