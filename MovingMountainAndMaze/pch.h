#pragma once

#include <EnginePch.h>
#include <chrono>

#if _DEBUG
#pragma comment(lib, "Debug/Engine")
#else
#pragma comment(lib, "Engine")
#endif

using uchar = unsigned char;