#pragma once

#include "targetver.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <TlHelp32.h>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Log.h"
#include "Utils.h"
#include "Inject.h"

#define GetPID(process) Utilities::GetProcessID(s2ws(process))
#define pause system("pause")
#define failure \
	pause; \
	return EXIT_FAILURE
