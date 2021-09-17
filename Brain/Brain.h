#pragma once
#include "pch.h"
#include "BrainFunctions.h"

BOOL InitilizeBrain(void);

enum Functions
{
    LOAD_DLL_FUNCTION = 1,
    PRINT_STRING_FUNCTION = 2
};

struct BrainMessage
{
    DWORD function;
    BYTE parametersBuffer;
};
