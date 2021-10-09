#include "pch.h"
#include "Brain.h"

VOID BrainLoadDll(LPBYTE input_buffer, OUT BrainAnswer* answer)
{
    if (!LoadLibrary((LPWSTR)input_buffer))
        answer->function_return_value = -1;
    else
    {
        answer->function_return_value = 0;
    }
    return;
}

VOID BrainPrintString(LPBYTE input_buffer, OUT BrainAnswer* answer)
{
    OutputDebugString((LPWSTR)input_buffer);
    answer->function_return_value = 0;
    return;
}
