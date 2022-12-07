#pragma once

#include "Scene.h"

class Shader;
class Camera;
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

	void ViewProjection(std::unique_ptr<Camera>& camera, std::shared_ptr<Shader>& shader);
private:
	void CalculateDeltaTime();
	void LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void ReleaseObject(std::vector<Object*>* object);
	void Render(std::vector<Object*>* object, std::unique_ptr<Camera>& camera, std::shared_ptr<Shader>& shader, bool apply_light, bool apply_texture);
	void RenderSkybox(std::vector<Object*>* object, std::unique_ptr<Camera>& camera, std::shared_ptr<Shader>& shader);

	void CreateSkybox();
	void CreateGrid();
	void CreateCube();
	void CreatePyramid();
	void RotateX(int32_t direction);
	void RotateY(int32_t direction);
	void Reset();

private:
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<Camera> _ui_camera;
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
	float _wait_time;

	glm::vec3 _light_pos;
	bool _apply_light;
	bool _apply_texture;
private:
	std::vector<Object*> _skybox;
	std::vector<Object*> _grid;
	std::vector<Object*> _cube;
	std::vector<Object*> _pyramid;
	std::vector<Object*>* _render_object;
};
