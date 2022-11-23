#pragma once

#include <Camera.h>

class Player;

class InterfaceCamera : public Camera
{
public:
	InterfaceCamera();
	~InterfaceCamera();

	virtual void UpdateCamera();

protected:
	std::shared_ptr<Player> _player;
};

class FirstPersonCamera : public InterfaceCamera
{
public:
	FirstPersonCamera();
	~FirstPersonCamera();

private:
	
};

class ThirdPersonCamera : public InterfaceCamera
{
public:
	ThirdPersonCamera();
	~ThirdPersonCamera();

	void UpdateCamera() override;

private:
	glm::vec3 _offset;
};
