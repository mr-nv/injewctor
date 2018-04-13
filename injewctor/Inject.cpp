#include "stdafx.h"
#include "Inject.h"
using namespace std;

bool Inject::LoadLib(DWORD pID, string DLLName)
{
	char DLLPath[MAX_PATH];
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
	if (!process)
	{
		Console::Log("OpenProcess failed!", "ERROR");
		std::cout << std::endl;
		failure;
	}

	LPVOID library = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	if (!library)
	{
		Console::Log("Failed to get LoadLibrary!", "ERROR");
		std::cout << std::endl;
		failure;
	}

	GetFullPathNameA(DLLName.c_str(), MAX_PATH, DLLPath, NULL);
	if (DLLPath == "")
	{
		Console::Log("Failed to get full DLL path!", "ERROR");
		std::cout << std::endl;
		failure;
	}

	LPVOID allstring = VirtualAllocEx(process, NULL, strlen(DLLPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!WriteProcessMemory(process, allstring, DLLPath, strlen(DLLPath), NULL))
	{
		Console::Log("WriteProcessMemory failed!", "ERROR");
		std::cout << std::endl;
		failure;
	}
	
	/* inject */
	if (!CreateRemoteThread(process, NULL, NULL, (LPTHREAD_START_ROUTINE)library, allstring, NULL, NULL))
	{
		Console::Log("CreateRemoteThread failed!", "ERROR");
		std::cout << std::endl;
		failure;
	}

	CloseHandle(process);
	return EXIT_SUCCESS;
}