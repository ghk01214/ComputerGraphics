#pragma once

#include <iostream>
#include <format>
#include <random>
#include <fstream>
#include <algorithm>
#include <ranges>

#include <vector>
#include <list>

using int8 = char;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint32 = unsigned int;
using uint64 = unsigned long long;

extern std::default_random_engine dre;
extern std::uniform_int_distribution<int32> uid;