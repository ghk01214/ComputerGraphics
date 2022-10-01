#pragma once

#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void OnLoad() override;

	void OnMouseMessage(int32_t button, int32_t x, int32_t y) override;
	void OnRender() override;

private:
	std::unique_ptr<class CameraMgr> _camera;
	std::vector<class Triangle> _tri;
	int32_t _index;
};
