#pragma once

#include <iostream>
#include <fstream>
#include <format>
#include <string>
#include <random>

#include <vector>
#include <list>
#include <unordered_map>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <Singleton.hpp>

#pragma comment(lib, "glew32")
#pragma comment(lib, "glew32s")
#pragma comment(lib, "freeglut")

#pragma region [MACRO]
#define DEPRECATED [[deprecated]]
#define MAYBE_UNUSED [[maybe_unused]]
#define FALLTHROUGH [[fallthrough]];
#define LIKELY [[likely]]
#define UNLIKELY [[unlikely]]

#ifndef _FAILED
#define _FAILED not
#endif

#ifndef no
#define no not
#endif
#pragma endregion

using uchar = unsigned char;

struct Window
{
	uint32_t width;
	uint32_t height;
	bool windowed;

	Window(uint32_t width, uint32_t height, bool windowed) :
		width{ width }, height{ height }, windowed{ windowed } {}
};

extern std::unique_ptr<class Engine> game_engine;
extern std::default_random_engine dre;

#include <Define.h>
#include <Util.h>

#define SCENE_MGR game_engine->GetSceneMgr()