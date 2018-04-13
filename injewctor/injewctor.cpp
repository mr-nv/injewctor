#include "stdafx.h"

using namespace std;

string pName;
string DLLName;
char DLLPath[MAX_PATH];

int main()
{
	auto s2ws = [](const std::string& s)
	{
		LPWSTR ws = new wchar_t[s.size() + 1]; // +1 for zero at the end
		copy(s.begin(), s.end(), ws);
		ws[s.size()] = 0; // zero at the end
		return ws;
	};

	Console::Log("injewctor - loadlibrary edition");
	std::cout << std::endl;
	Console::Log("Process name: ");
	getline(cin, pName);
	if (pName.empty())
	{
		/* load from previous injection */
	}
	Console::Log("DLL name: ");
	getline(cin, DLLName);
	if (DLLName.empty())
	{
		/* load from previous injection */
	}

	if (!Utilities::FileExists(DLLName.c_str()))
	{
		Console::Log("DLL was not found!", "ERROR");
		std::cout << std::endl;
		failure;
	}

	DWORD pID = GetPID(pName);

	if (pID)
	{
		Utilities::EnableDebugPrivilege(GetCurrentProcess());

		/* alright, so we have process name and dll name, everything should be ok, so lets inject */
		if (!Inject::LoadLib(pID, DLLName))
		{
			Console::Log("Injected!");
			std::cout << std::endl;
		}
		else
		{
			Console::Log("Failed to inject!", "ERROR");
			std::cout << std::endl;
			failure;
		}
	}
	else
	{
		Console::Log("Process is not running!", "ERROR");
		std::cout << std::endl;
		failure;
	}
	pause;
	return EXIT_SUCCESS;
}

