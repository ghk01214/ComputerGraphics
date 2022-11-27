#include "pch.h"
#include <Camera.h>
#include "Player.h"

Player::Player() :
	_right{ vec3::right() },
	_up{ vec3::up() },
	_look{ vec3::front() },
	_pitch{ 0.f },
	_yaw{ -90.f }
{
}

Player::~Player()
{
}

void Player::MovePlayer(DIRECTION direction, float distance)
{
	glm::vec3 shift{ vec3::zero() };

	switch (direction)
	{
		case DIRECTION::LEFT:
		{
			shift -= _right * distance;
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

	Update();
	Object::Move(shift);
}

void Player::RotatePlayer(int32_t direction)
{
	_yaw += 90.f * direction;

	Update();
}

void Player::Update()
{
	glm::vec3 look{ vec3::zero() };
	look.x = std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
	look.z = std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));

	_front = glm::normalize(look);
	_right = glm::normalize(glm::cross(_front, vec3::up()));
	_up = glm::normalize(glm::cross(_right, _front));
	_look = _pos + _front;
}

void Player::ChangeVectors(glm::vec3 front, glm::vec3 up, glm::vec3 right)
{
	_front = front;
	_up = up;
	_right = right;
}
