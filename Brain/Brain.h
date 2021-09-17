#pragma once
#include "pch.h"
#include "BrainFunctions.h"

#define MESSAGE_BUFFER_SIZE 1024

enum Functions
{
    LOAD_DLL_FUNCTION = 1,
    PRINT_STRING_FUNCTION = 2
};

struct BrainMessage
{
    DWORD function;
    BYTE parametersBuffer[MESSAGE_BUFFER_SIZE - sizeof(function)];
};

struct BrainAnswer
{
    DWORD function_return_value;
};

BOOL InitilizeBrain(void);