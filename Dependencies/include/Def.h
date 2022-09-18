#pragma once

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
}

namespace mat4
{
	inline const glm::mat4 zero() { return glm::mat4{ 0.f }; }
	inline const glm::mat4 unit() { return glm::mat4{ 1.f }; }
}