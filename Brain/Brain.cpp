#include "pch.h"

VOID BrainMain(HANDLE hPipe)
{
    BYTE buffer[1024];
    DWORD dwRead;
    
    BYTE temp_unicode_buffer[2048] = { 0 };

    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
            {
                /* add terminating zero */
                buffer[dwRead] = '\0';

                MultiByteToWideChar(CP_ACP,
                    NULL,
                    (LPCCH)buffer,
                    -1,
                    (LPWSTR)temp_unicode_buffer,
                    1024);

                /* do something with data in buffer */
                OutputDebugString((LPWSTR)temp_unicode_buffer);
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