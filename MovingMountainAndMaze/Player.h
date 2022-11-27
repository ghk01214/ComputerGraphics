#pragma once

#include <Sphere.h>

class Camera;

class Player : public Sphere
{
public:
	Player();
	~Player();

	void MovePlayer(DIRECTION direction, float distance);
	void RotatePlayer(int32_t direction);
	void Update();

	glm::vec3 GetUp() { return _up; }
	glm::vec3 GetRight() { return _right; }
	glm::vec3 GetLook() { return _look; }

	void ChangeVectors(glm::vec3 front, glm::vec3 up, glm::vec3 right);

private:
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _look;

	float _pitch;
	float _yaw;

	std::shared_ptr<Camera> _camera;
};

