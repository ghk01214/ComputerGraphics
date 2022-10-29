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

	void Revolve();

private:
	std::unique_ptr<class CameraMgr> _camera;
	std::vector<Object*> _object;
	std::vector<Object*> _sub_object;
	std::vector<Object*> _grid;

	uint32_t _index;

	bool _stop_animation;
	float _radius;
};
