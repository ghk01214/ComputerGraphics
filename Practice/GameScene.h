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

	void RotateX(int32_t direction);
	void RotateY(int32_t direction);

private:
	std::unique_ptr<class CameraMgr> _camera;
	std::list<Object*> _object;
	Object* _hidden;

	int32_t _index;

	bool _depth_test;
	bool _solid_object;
	bool _cube;
	bool _stop_animation;
};
