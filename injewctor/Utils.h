#pragma once
#include "stdafx.h"

namespace Utilities
{
	bool EnableDebugPrivilege(HANDLE process);
	bool FileExists(const char* f);
	DWORD GetProcessID(LPCTSTR process);
}