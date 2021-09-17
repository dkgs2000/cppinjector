#include "pch.h"
#include"Brain.h"

VOID BrainMain(HANDLE hPipe)
{
    BYTE buffer[1024] = { 0 };
    DWORD dwRead = 0;

    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            RtlZeroMemory(buffer, sizeof(buffer));

            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
            {
                switch (((BrainMessage*)buffer)->function)
                {
                case LOAD_DLL_FUNCTION:
                    break;

                case PRINT_STRING_FUNCTION:
                    BrainPrintString(((BrainMessage*)buffer)->parametersBuffer);
                    break;
                default:
                    break;
                }
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
        return FALSE;

	return TRUE;
}