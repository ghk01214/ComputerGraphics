#include "pch.h"
#include "Shader.h"
#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up) :
	_pos{ pos },
	_look{ vec3::front() },
	_up{ vec3::zero() },
	_right{ vec3::zero() },
	_pitch{ 0.f },
	_yaw{ -90.f },
	_sensitivity{ 0.1f },
	_world_up{ up },
	_view{ mat4::unit() },
	_projection{ mat4::unit() },
	_fov{ 45.f },
	_near{ 1.f },
	_far{ 1000.f },
	_aspect{ 1.f / 1.f },
	_perspective{ true }
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
			_pos -= _right * velocity;
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			_pos += _right * velocity;
		}
		break;
		case GLUT_KEY_UP:
		{
			_pos += _look * velocity;
		}
		break;
		case GLUT_KEY_DOWN:
		{
			_pos -= _look * velocity;
		}
		break;
		case GLUT_KEY_PAGE_UP:
		{
		}
		break;
		case GLUT_KEY_PAGE_DOWN:
		{
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

	//if (_yaw > 360.f)
	//	_yaw = -360.f;
	//if (_yaw < 0.f)
	//	_yaw = 360.f;

	_pitch += delta_y;

	if (_pitch > 89.f)
		_pitch = 89.f;
	if (_pitch < -89.f)
		_pitch = -89.f;

	Update();
}

void Camera::Rotate()
{
	static float x, y;

	x += 1.f;

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

	_look = glm::normalize(look);
	_right = glm::normalize(glm::cross(_look, _world_up));
	_up = glm::normalize(glm::cross(_right, _look));
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(_pos, _pos + _look, _up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (_perspective == true)
		return glm::perspective(glm::radians(_fov), _aspect, _near, _far);
	else
		return glm::ortho(-2.f, 2.f, -2.f, 2.f, _near, _far);
}
