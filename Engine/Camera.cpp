#include "pch.h"
#include "Camera.h"

Camera::Camera() :
	_pos{ glm::vec3{ 0.f, 0.f, 1.f } },
	_look{ vec3::zero() },
	_up{ vec3::up() },
	_right{ vec3::zero() },
	_front{ vec3::back() },
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
	_front += delta;

	//_look += delta;
}

void Camera::Move(float x, float y, float z)
{
	Move(glm::vec3{ x, y, z });
}

void Camera::Rotate(float x, float y, float z)
{
	_front.x = std::cos(glm::radians(y)) * std::cos(glm::radians(x));
	_front.y = std::sin(glm::radians(x));
	_front.z = std::sin(glm::radians(y)) * std::cos(glm::radians(x));

	_front = glm::normalize(_front);
	_right = glm::normalize(glm::cross(_front, vec3::up()));
	_up = glm::normalize(glm::cross(_right, _front));

	//_look = _pos + _front;
}

glm::mat4 Camera::Zoom()
{
	return glm::mat4();
}
