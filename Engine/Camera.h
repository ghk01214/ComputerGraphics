#pragma once

// NOTE :
// 화면에 그려진 월드를 비추는 카메라 class
// 

class Shader;

class Camera
{
public:
	Camera(glm::vec3 pos = vec3::back(), glm::vec3 up = vec3::up());
	~Camera();

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y);
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y, float delta);
	void OnMouseMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseMotionMessage(float delta_x, float delta_y);

	void Rotate();
	void Zoom(float delta);
	void Update();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

private:
	glm::vec3 _pos;
	glm::vec3 _look;
	glm::vec3 _up;
	glm::vec3 _right;

	float _pitch;
	float _yaw;
	float _sensitivity;

	glm::vec3 _world_up;

	glm::mat4 _view;
	glm::mat4 _projection;

	float _fov;
	float _near;
	float _far;
	float _aspect;

	bool _perspective;
};
