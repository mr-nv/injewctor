#include "stdafx.h"

bool Utilities::EnableDebugPrivilege(HANDLE process)
{
	LUID luid;
	HANDLE token;
	TOKEN_PRIVILEGES newPrivileges;

	if (!OpenProcessToken(process, TOKEN_ADJUST_PRIVILEGES, &token))
		return false;

	if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
		return false;

	newPrivileges.PrivilegeCount = 1;
	newPrivileges.Privileges[0].Luid = luid;
	newPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	return AdjustTokenPrivileges(
		token,                     // TokenHandle
		FALSE,                     // DisableAllPrivileges
		&newPrivileges,            // NewPrivileges
		sizeof(newPrivileges),     // BufferLength
		nullptr,                   // PreviousState (OPTIONAL)
		nullptr                    // ReturnLength (OPTIONAL)
	);
}

bool Utilities::FileExists(const char* f)
{
	std::ifstream file{ f };
	return file.good();
}

DWORD Utilities::GetProcessID(LPCTSTR process)
{
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) { // must call this first
		do {
			if (!lstrcmpi(pt.szExeFile, process)) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap); // close handle on failure
	return 0;
}