#pragma once

#include "Scene.h"

class Object;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void OnLoad() override;

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y) override;
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y) override;
	void OnMouseMessage(int32_t button, int32_t x, int32_t y) override;
	void OnMouseMotionMessage(int32_t x, int32_t y) override;
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y) override;
	void OnAnimate(int32_t index) override;
	void OnRender() override;

	void ViewProjection(std::shared_ptr<class Shader>& shader);

	void RotateBase();
	void RotateCenter();
	void RotateArm();
	void Orbit();

private:
	std::unique_ptr<class Camera> _camera;
	std::vector<Object*> _object;
	std::vector<Object*> _sub_object;
	std::vector<Object*> _grid;

	bool _stop_animation;
	bool _click;

	int32_t _old_x;
	int32_t _old_y;

	bool _rotate_base;
	bool _rotate_center;
	bool _rotate_arm;
	bool _rotate_camera;
};
