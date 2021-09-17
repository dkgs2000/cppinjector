#include "pch.h"

DWORD KeepAlive(void)
{
	OutputDebugString(L"[*] Keeping Alive...");
	Sleep(60 * 10);
	return 256;
}