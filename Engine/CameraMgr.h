#pragma once

// NOTE :
// 생성된 카메라를 관리하는 manager class
// 

class Shader;

class CameraMgr : public Singleton<CameraMgr>
{
public:
	CameraMgr();
	~CameraMgr();

	void OnLoad();

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y);
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y);
	void OnMouseMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y);
	void OnMouseMotionMessage(int32_t x, int32_t y);

	static void ViewTransform(std::shared_ptr<Shader> shader);
	static void ProjectionTransform(std::shared_ptr<Shader> shader);

	void SetAspect(float aspect) { inst->_aspect = aspect; }

	void Move(glm::vec3 delta);
	void Move(float x, float y, float z);

private:
	std::unique_ptr<class Camera> _camera;

	glm::mat4 _view;
	glm::mat4 _projection;

	float _pitch;
	float _yaw;
	float _roll;

	int32_t _old_x;
	int32_t _old_y;
	float _sensitivity;
	bool _click;

	float _aspect;
};

