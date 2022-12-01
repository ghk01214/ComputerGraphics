#pragma once

#include "Scene.h"

class Shader;
class Object;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void OnLoad() override;
	void OnRelease() override;

	void OnIdleMessage() override;
	void OnKeyboardMessage(uchar key, int32_t x, int32_t y) override;
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y) override;
	void OnMouseMessage(int32_t button, int32_t x, int32_t y) override;
	void OnMouseMotionMessage(int32_t x, int32_t y) override;
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y) override;
	void OnAnimate(int32_t index) override;
	void OnRender() override;

	void ViewProjection(std::shared_ptr<class Shader>& shader);
private:
	void CalculateDeltaTime();
	void LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void ReleaseObject(std::vector<Object*>* object);
	void Render(std::vector<Object*>* object, std::shared_ptr<Shader>& shader, bool apply_light);
	void RenderSkybox(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);

	void CreateCrane();
	void CreatePlane();
	void CreateLight();

	void MoveCrane(glm::vec3 direction);
	void RotateCamera();
	void ChangeLightColor();
	void RotateLight(int32_t direction);

private:
	std::unique_ptr<class Camera> _camera;
	std::shared_ptr<Shader> _color_shader;
	std::shared_ptr<Shader> _light_shader;
	std::shared_ptr<Shader> _skybox_shader;

	bool _stop_animation;
	bool _click;

	int32_t _old_x;
	int32_t _old_y;

	int32_t _time;
	int32_t _old_time;
	float _delta_time;

	glm::vec3 _light_pos;
	bool _apply_light;
private:
	std::vector<Object*> _crane;
	std::vector<Object*> _plane;
	std::vector<Object*> _light;
};
