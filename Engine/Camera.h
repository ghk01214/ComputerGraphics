#pragma once

// NOTE :
// 화면에 그려진 월드를 비추는 카메라 class
// 

class Shader;

class Camera
{
public:
	enum class DIRECTION
	{
		NONE = 0,
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		UP,
		DOWN,
		MAX
	};
public:
	Camera() = default;
	Camera(glm::vec3 pos, glm::vec3 up = vec3::up(), float pitch = 0.f, float yaw = -90.f);
	~Camera();

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y);
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y, float delta);
	void OnMouseMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseMotionMessage(float delta_x, float delta_y);

	void Move(DIRECTION direction, float velocity);
	void RotateX(int32_t direction);
	void RotateY(int32_t direction);
	void Rotate90(int32_t direction);
	void Zoom(float delta);
	void Update();

	glm::vec3 GetPos() { return _pos; }
	glm::vec3 GetRight() { return _right; }
	glm::vec3 GetUp() { return _up; }
	glm::vec3 GetFront() { return _front; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void SetPos(glm::vec3 pos) { _pos = pos; }
	void SetPos(float x, float y, float z) { SetPos(glm::vec3{ x, y, z }); }
	void SetLook(glm::vec3 look) { _look = look; }
	void SetLook(float x, float y, float z) { SetLook(glm::vec3{ x, y, z }); }
	void SetRight(glm::vec3 right) { _right = right; }
	void SetUp(glm::vec3 up) { _up = up; }
	void SetFront(glm::vec3 front) { _front = front; }

	void SetCameraMode(bool perspective) { _perspective = perspective; }

private:
	glm::vec3 _pos;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _look;

	float _pitch;
	float _yaw;
	float _sensitivity;

	glm::vec3 _world_up;

	glm::mat4 _view;
	glm::mat4 _projection;
	glm::vec3 _old_pos;

	float _fov;
	float _near;
	float _far;
	float _aspect;

	bool _perspective;
};
