#include "pch.h"
#include "Brain.h"

VOID BrainHandleCall(BrainFunctions function, LPBYTE parameters_buffer, BrainAnswer* answer)
{
    switch (function)
    {
    case BrainFunctions::LOAD_DLL_FUNCTION:
        BrainLoadDll(parameters_buffer, answer);
        break;

    case BrainFunctions::PRINT_STRING_FUNCTION:
        BrainPrintString(parameters_buffer, answer);
        break;

    default:
        OutputDebugString(L"[!] Got unknown function in message.");
        answer->function_return_value = -1;
        break;
    }
    return;
}

VOID BrainMain(HANDLE hPipe)
{
    BYTE input_buffer[REQUEST_BUFFER_SIZE] = { 0 };
    BrainRequest* brain_request = (BrainRequest*)input_buffer;
    LPBYTE parameters_buffer = NULL;
    BrainAnswer* brain_answer_buffer = NULL;
    DWORD dwRead = 0;
    DWORD dwWrite = 0;

    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            OutputDebugString(L"[*] Client Connected\n");
            while (ReadFile(hPipe, input_buffer, sizeof(input_buffer), &dwRead, NULL) != FALSE)
            {
                if (dwRead != sizeof(input_buffer))
                {
                    OutputDebugString(L"[-] Got invalid request size, skipping...\n");
                    continue;
                }

                parameters_buffer = (LPBYTE)VirtualAlloc(NULL, sizeof(brain_request->parametersBuffer), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                if (parameters_buffer == NULL)
                {
                    OutputDebugString(L"[-] Failed to allocate parameters buffer.\n");
                    continue;
                }
                
                RtlCopyMemory(parameters_buffer, brain_request->parametersBuffer, sizeof(brain_request->parametersBuffer));

                brain_answer_buffer = (BrainAnswer*)VirtualAlloc(NULL, sizeof(BrainAnswer), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                if (brain_answer_buffer == NULL)
                {
                    OutputDebugString(L"[-] Failed to allocate answer buffer.\n");
                    VirtualFree(parameters_buffer, 0, MEM_RELEASE);
                    continue;
                }

                BrainHandleCall(brain_request->function, parameters_buffer, brain_answer_buffer);

                if (!WriteFile(hPipe, brain_answer_buffer, sizeof(BrainAnswer), &dwWrite, NULL))
                    OutputDebugString(L"Failed to write answer.\n");

                VirtualFree(parameters_buffer, 0, MEM_RELEASE);
                VirtualFree(brain_answer_buffer, 0, MEM_RELEASE);
                RtlZeroMemory(input_buffer, sizeof(input_buffer));
            }
        }

        DisconnectNamedPipe(hPipe);
        OutputDebugString(L"[*] Client Disconnected\n");
    }
    return;
}

BOOL InitilizeBrain(VOID)
{
    HANDLE hPipe;
    DWORD threadId = 0;

    hPipe = CreateNamedPipe(L"\\\\.\\pipe\\BrainPipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
        1,
        1024 * 16,
        1024 * 16,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE)
        return FALSE;

    if (!CreateThread(NULL,
        0,
        (LPTHREAD_START_ROUTINE)BrainMain,
        hPipe,
        0,
        &threadId))
    {
        return FALSE;
    }

	return TRUE;
}