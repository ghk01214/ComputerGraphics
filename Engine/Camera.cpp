#include "pch.h"
#include "Shader.h"
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float pitch, float yaw) :
	_pos{ pos },
	_front{ vec3::front() },
	_up{ vec3::zero() },
	_right{ vec3::zero() },
	_look{ _pos + _front },
	_pitch{ pitch },
	_yaw{ yaw },
	_sensitivity{ 0.1f },
	_world_up{ up },
	_view{ mat4::unit() },
	_projection{ mat4::unit() },
	_fov{ 45.f },
	_near{ 1.f },
	_far{ 1000.f },
	_aspect{ 1.f / 1.f },
	_perspective{ true },
	_old_pos{ pos }
{
	Update();
}

Camera::~Camera()
{
}

void Camera::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
}

void Camera::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y, float delta)
{
	float velocity{ 2.5f * delta };

	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			Move(DIRECTION::LEFT, velocity);
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			Move(DIRECTION::RIGHT, velocity);
		}
		break;
		case GLUT_KEY_UP:
		{
			Move(DIRECTION::FRONT, velocity);
		}
		break;
		case GLUT_KEY_DOWN:
		{
			Move(DIRECTION::BACK, velocity);
		}
		break;
		case GLUT_KEY_PAGE_UP:
		{
			Move(DIRECTION::UP, velocity);
		}
		break;
		case GLUT_KEY_PAGE_DOWN:
		{
			Move(DIRECTION::DOWN, velocity);
		}
		break;
		case GLUT_KEY_HOME:
		{
			Zoom(1.f);
		}
		break;
		case GLUT_KEY_END:
		{
			Zoom(-1.f);
		}
		break;
		default:
		break;
	}
}

void Camera::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
}

void Camera::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
}

void Camera::OnMouseMotionMessage(float delta_x, float delta_y)
{
	delta_x *= _sensitivity;
	delta_y *= _sensitivity;

	_yaw += delta_x;
	_pitch += delta_y;

	if (_pitch > 89.f)
		_pitch = 89.f;
	if (_pitch < -89.f)
		_pitch = -89.f;

	Update();
}

void Camera::Move(DIRECTION direction, float velocity)
{
	switch (direction)
	{
		case DIRECTION::LEFT:
		{
			_pos -= _right * velocity;
		}
		break;
		case DIRECTION::RIGHT:
		{
			_pos += _right * velocity;
		}
		break;
		case DIRECTION::FRONT:
		{
			_pos += _front * velocity;
		}
		break;
		case DIRECTION::BACK:
		{
			_pos -= _front * velocity;
		}
		break;
		case DIRECTION::UP:
		{
			_pos += _up * velocity;
		}
		break;
		case DIRECTION::DOWN:
		{
			_pos -= _up * velocity;
		}
		break;
	}

	_look = _pos + _front;
}

void Camera::RotateX(int32_t direction)
{
	_pitch += _sensitivity * 10 * direction;

	Update();
}

void Camera::RotateY(int32_t direction)
{
	_yaw += _sensitivity * 10 * direction;

	Update();
}

void Camera::Rotate90(int32_t direction)
{
	_yaw += 90.f * direction;

	Update();
}

void Camera::Zoom(float delta)
{
	_fov -= delta;

	if (_fov < 1.f)
		_fov = 1.f;
	if (_fov > 45.f)
		_fov = 45.f;
}

void Camera::Update()
{
	glm::vec3 look{ vec3::zero() };
	look.x = std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
	look.y = std::sin(glm::radians(_pitch));
	look.z = std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));

	_front = glm::normalize(look);
	_right = glm::normalize(glm::cross(_front, _world_up));
	_up = glm::normalize(glm::cross(_right, _front));
	_look = _pos + _front;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(_pos, _look, _up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (_perspective == false)
		return glm::ortho(-10.f, 10.f, -10.f, 10.f, _near, _far);

	return glm::perspective(glm::radians(_fov), _aspect, _near, _far);
}
