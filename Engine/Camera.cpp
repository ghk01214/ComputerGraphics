﻿#include "pch.h"
#include "Camera.h"

Camera::Camera() :
	_pos{ glm::vec3{ 0.f, 0.f, 1.f } },
	_look{ vec3::front() },
	_up{ vec3::up() },
	_right{ vec3::zero() },
	_fov{ 45.f }
{
	glm::vec3 direction{ glm::normalize(_pos - _look) };
	_right = glm::normalize(glm::cross(vec3::up(), direction));
	_up = glm::cross(direction, _right);
}

Camera::~Camera()
{
}

void Camera::Move(glm::vec3 delta)
{
	_pos += delta;
	_look += delta;
}

void Camera::Move(float x, float y, float z)
{
	Move(glm::vec3{ x, y, z });
}

void Camera::Rotate()
{
	static float x, y;

	x += 1.f;

	Update(x, y);
}

void Camera::Zoom(float delta)
{
	_fov -= delta;

	if (_fov < 1.f)
		_fov = 1.f;
	if (_fov > 45.f)
		_fov = 45.f;
}

void Camera::Update(float x, float y)
{
	glm::vec3 look{ vec3::zero() };
	look.x = std::cos(glm::radians(y)) * std::cos(glm::radians(x));
	look.y = std::sin(glm::radians(x));
	look.z = std::sin(glm::radians(y)) * std::cos(glm::radians(x));

	_look = glm::normalize(look);
	//_right = glm::normalize(glm::cross(_look, vec3::up()));
	//_up = glm::normalize(glm::cross(_right, _look));
}
