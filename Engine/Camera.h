#pragma once

// NOTE :
// 화면에 그려진 월드를 비추는 카메라 class
// 

class Camera
{
public:
	Camera();
	~Camera();

	void Move(glm::vec3 delta);
	void Rotate(float x, float y, float z = 0.f);
	MAYBE_UNUSED glm::mat4 Zoom();

	glm::vec3 GetPos() { return _pos; }
	glm::vec3 GetLook() { return _look; }
	glm::vec3 GetUp() { return _up; }
	float GetFOV() { return _fov; }

	void SetPos(glm::vec3 pos) { _pos = pos; }
	void SetTarget(glm::vec3 target) { _look = target; }

private:
	glm::vec3 _pos;
	glm::vec3 _look;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _front;

	float _fov;
};
