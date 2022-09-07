#include "pch.h"

std::default_random_engine dre{ std::random_device{}() };
std::uniform_int_distribution<int32> uid{ 0, 2 };