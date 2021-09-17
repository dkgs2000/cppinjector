#include "pch.h"
#include "Brain.h"

VOID BrainMain(HANDLE hPipe)
{
    BYTE input_buffer[MESSAGE_BUFFER_SIZE] = {};
    BrainMessage* brain_message = (BrainMessage*)input_buffer;
    BYTE* parameters_buffer = NULL;
    BYTE answer_buffer[sizeof(BrainAnswer)] = {};
    DWORD dwRead = 0;

    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            while (ReadFile(hPipe, input_buffer, sizeof(input_buffer) - 1, &dwRead, NULL) != FALSE)
            {
                parameters_buffer = (BYTE*)VirtualAlloc(NULL, sizeof(brain_message->parametersBuffer), MEM_COMMIT | MEM_RESERVE, NULL);
                if (parameters_buffer == NULL)
                {
                    OutputDebugString(L"[-] Failed to allocate parameters buffer.\n");
                    continue;
                }

                switch (brain_message->function)
                {
                case LOAD_DLL_FUNCTION:
                    BrainLoadDll(parameters_buffer);
                    break;

                case PRINT_STRING_FUNCTION:
                    BrainPrintString(parameters_buffer);
                    break;

                default:
                    OutputDebugString(L"[!] Got unknown function in message.\n");
                    break;
                }

                VirtualFree(parameters_buffer, 0, MEM_RELEASE);
                RtlZeroMemory(input_buffer, sizeof(input_buffer));
            }
        }

        DisconnectNamedPipe(hPipe);
    }
    return;
}

BOOL InitilizeBrain(void)
{
    HANDLE hPipe;

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
        NULL))
    {
        return FALSE;
    }

	return TRUE;
}