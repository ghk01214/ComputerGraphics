#pragma once

#include "Scene.h"
#include "Triangle.h"
#include "Rect.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void OnLoad() override;

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y) override;
	void OnRender() override;

private:
	Triangle _tri;
	Rect _rect;
};
