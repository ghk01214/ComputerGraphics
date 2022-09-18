#include "pch.h"
#include "Engine.h"
#include "EnginePch.h"

std::unique_ptr<Engine> game_engine{ nullptr };
std::default_random_engine dre{ std::random_device{}() };