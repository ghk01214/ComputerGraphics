﻿#pragma once

extern std::uniform_real_distribution<float> uid_color;

#define RED 1.f, 0.f, 0.f
#define GREEN 0.f, 1.f, 0.f
#define BLUE 0.f, 0.f, 1.f
#define BLACK 0.f, 0.f, 0.f
#define WHITE 1.f, 1.f, 1.f
#define GRAY 0.5f, 0.5f, 0.5f
#define YELLOW 1.f, 1.f, 0.f
#define RAND_COLOR uid_color(dre), uid_color(dre), uid_color(dre)

namespace define
{
	enum class SCENE_TYPE
	{
		NONE = 0,
		START,
		GAME,
		END,
		MAX
	};

	enum class CAMERA_TYPE
	{
		NONE = 0,
		ORTHOGRAPHIC,
		PERSPECTIVE,
		FIRST,
		THIRD,
		TOP,
		MAX
	};
}

namespace glm
{
	template<typename T>
	inline glm::vec2 ToVec2(T value) { return glm::vec2{ value.x, value.y }; }

	template<typename T>
	inline glm::vec3 ToVec3(T value) { return glm::vec3{ value.x, value.y, value.x }; }
}

namespace vec3
{
	inline const glm::vec3 zero() { return glm::vec3{ 0.f }; }
	inline const glm::vec3 unit() { return glm::vec3{ 1.f }; }
	inline const glm::vec3 front() { return glm::vec3{ 0.f, 0.f, -1.f }; }
	inline const glm::vec3 front(float delta) { return front() * delta; }
	inline const glm::vec3 back() { return glm::vec3{ 0.f, 0.f, 1.f }; }
	inline const glm::vec3 back(float delta) { return back() * delta; }
	inline const glm::vec3 left() { return glm::vec3{ -1.f, 0.f, 0.f }; }
	inline const glm::vec3 left(float delta) { return left() * delta; }
	inline const glm::vec3 right() { return glm::vec3{ 1.f, 0.f, 0.f }; }
	inline const glm::vec3 right(float delta) { return right() * delta; }
	inline const glm::vec3 up() { return glm::vec3{ 0.f, 1.f, 0.f }; }
	inline const glm::vec3 up(float delta) { return up() * delta; }
	inline const glm::vec3 down() { return glm::vec3{ 0.f, -1.f, 0.f }; }
	inline const glm::vec3 down(float delta) { return down() * delta; }
	inline const glm::vec3 x() { return right(); }
	inline const glm::vec3 x(float delta) { return right(delta); }
	inline const glm::vec3 y() { return up(); }
	inline const glm::vec3 y(float delta) { return up(delta); }
	inline const glm::vec3 z() { return back(); }
	inline const glm::vec3 z(float delta) { return back(delta); }
}

namespace mat4
{
	inline const glm::mat4 zero() { return glm::mat4{ 0.f }; }
	inline const glm::mat4 unit() { return glm::mat4{ 1.f }; }
}