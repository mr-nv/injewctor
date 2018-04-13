#include "stdafx.h"

void Console::Log(const char* f, const char* type, ...)
{
	/* https://stackoverflow.com/a/16358111 */
	auto GetTimeString = []() -> std::string { 
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "[%H:%M:%S");
		return oss.str();
	};
	va_list args;
	va_start(args, f);
	char pszBuffer[0x400];
	vsprintf_s(pszBuffer, f, args);
	va_end(args);

	if (type != "") std::cout << GetTimeString().c_str() << " - " << type << "] ";
	else std::cout << GetTimeString().c_str() << "] ";
	std::cout << pszBuffer;
}