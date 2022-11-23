#pragma once

#include <Sphere.h>

class Camera;

class Player : public Sphere
{
private:
	enum class DIRECTION
	{
		NONE = 0,
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		MAX
	};
public:
	Player(std::shared_ptr<Camera>& camera);
	~Player();

	void Move(DIRECTION direction, float distance);
	void Rotate(int32_t direction);

	glm::vec3 GetUp() { return _up; }
	glm::vec3 GetRight() { return _right; }
	glm::vec3 GetLook() { return _look; }

private:
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _look;

	float _pitch;
	float _yaw;

	std::shared_ptr<Camera> _camera;
};

