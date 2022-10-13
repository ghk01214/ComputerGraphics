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
	void OnMouseMessage(int32_t button, int32_t x, int32_t y) override;
	void OnMouseMotionMessage(int32_t x, int32_t y) override;
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y) override;
	void OnAnimate(int32_t index) override;
	void OnRender() override;

private:
	std::unique_ptr<class CameraMgr> _camera;
	std::vector<Object*> _object;

	int32_t _index;

	bool _move_vertex;
	bool _move_rect;

	glm::vec3 _old_pos;
};
