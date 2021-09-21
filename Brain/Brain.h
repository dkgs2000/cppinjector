#pragma once
#include "pch.h"

#define REQUEST_BUFFER_SIZE 1024

enum BrainFunctions : DWORD
{
    LOAD_DLL_FUNCTION,
    PRINT_STRING_FUNCTION
};

struct BrainRequest
{
    BrainFunctions function;
    BYTE parametersBuffer[REQUEST_BUFFER_SIZE - sizeof(BrainFunctions)];
};

struct BrainAnswer
{
    DWORD function_return_value;
};

VOID BrainLoadDll(BYTE*, OUT BrainAnswer*);
VOID BrainPrintString(BYTE*, OUT BrainAnswer*);

BOOL InitilizeBrain(VOID);