#include "pch.h"
#include "InheritCamera.h"
#include "Player.h"

InterfaceCamera::InterfaceCamera()
{
}

InterfaceCamera::~InterfaceCamera()
{
}

void InterfaceCamera::UpdateCamera()
{
}

//==========================================

FirstPersonCamera::FirstPersonCamera()
{
}

FirstPersonCamera::~FirstPersonCamera()
{
}

//==========================================

ThirdPersonCamera::ThirdPersonCamera() :
	_offset{ vec3::zero() }
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::UpdateCamera()
{
	if (_player == nullptr)
		return;

	glm::vec3 right{ _player->GetRight() };
	glm::vec3 up{ _player->GetUp() };
	glm::vec3 look{ _player->GetLook() };

	glm::mat4 rotate_mat
	{
		right.x, right.y, right.z, 0.f,
		up.x, up.y, up.z, 0.f,
		look.x, look.y, look.z, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	
}
