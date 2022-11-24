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

	void Render2D(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void Render3D(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
private:
	void LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void ReleaseObject(std::vector<Object*>* object);
	void Render(Object* obj, std::shared_ptr<Shader>& shader);

public:
	void CreateGrid();
	void CreatePlanets();

	void ChangeLightColor();
	void RotateLight();

private:
	std::unique_ptr<class Camera> _camera;
	std::shared_ptr<Shader> _color_shader;
	std::shared_ptr<Shader> _light_shader;

	std::vector<Object*>* _object;

	bool _stop_animation;
	bool _click;

	int32_t _old_x;
	int32_t _old_y;

	float _delta_time;
	int32_t _old_time;

	glm::vec3 _light_pos;

private:
	std::vector<Object*> _grid;
	std::vector<Object*> _planets;

	glm::mat4 _light_mat;
};
