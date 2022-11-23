#include "pch.h"
#include <Camera.h>
#include "Player.h"

Player::Player(std::shared_ptr<Camera>& camera) :
	_camera{ camera },
	_right{ vec3::right() },
	_up{ vec3::up() },
	_look{ vec3::front() },
	_pitch{ 0.f },
	_yaw{ 0.f }
{
}

Player::~Player()
{
}

void Player::Move(DIRECTION direction, float distance)
{
	glm::vec3 shift{ vec3::zero() };

	switch (direction)
	{
		case DIRECTION::LEFT:
		{
			shift += _right * (-distance);
		}
		break;
		case DIRECTION::RIGHT:
		{
			shift += _right * distance;
		}
		break;
		case DIRECTION::FRONT:
		{
			shift += _look * distance;
		}
		break;
		case DIRECTION::BACK:
		{
			shift += _look * (-distance);
		}
		break;
	}

	Object::Move(shift);
	_look = GetPos() + shift + _front;
}

void Player::Rotate(int32_t direction)
{
	glm::vec3 look{ vec3::zero() };
	look.x = std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
	look.z = std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));

	_front = glm::normalize(look);
	_right = glm::normalize(glm::cross(_front, vec3::up()));
	_up = glm::normalize(glm::cross(_right, _front));
	_look = _pos + _front;
}
