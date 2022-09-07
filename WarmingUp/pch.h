#pragma once

#include <iostream>
#include <format>
#include <random>

#include <vector>

using int8 = char;
using int32 = int;

using uint8 = unsigned char;
using uint32 = unsigned int;

extern std::default_random_engine dre;
extern std::uniform_int_distribution<int32> uid;