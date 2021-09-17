#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD getProcess(char* processName) {
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(procEntry);

	do {
		if (!strcmp(procEntry.szExeFile, processName)) {
			DWORD dwPID = procEntry.th32ProcessID;
			CloseHandle(hPID);

			return dwPID;
		}
	} while (Process32Next(hPID, &procEntry));
}

int main(int argc, char * argv[]) {
	DWORD dwProcess;
	char dllPath[MAX_PATH];

	if (argc != 3)
	{
		printf_s("[-] Bad Args");
		return -1;
	}

	// get path of DLL
	GetFullPathNameA(argv[2], MAX_PATH, dllPath, NULL);

	// get process
	dwProcess = getProcess(argv[1]);

	// open handle and allocate memory
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProcess);

	if (!hProcess)
	{
		printf_s("[-] Failed to open injectee.\n");
		return -1;
	}

	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!allocatedMem)
	{
		printf_s("[-] Failed to allocate memory in injectee.\n");
		return -1;
	}

	// actually "inject" DLL into process memory
	WriteProcessMemory(hProcess, allocatedMem, dllPath, sizeof(dllPath), NULL);

	// launch DLL
	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);

	// close handle
	CloseHandle(hProcess);

	printf_s("[+] Injected \"%s\" to \"%s\" (PID: %d) successfully", dllPath, argv[1], dwProcess);

	// done
	return 0;
}
