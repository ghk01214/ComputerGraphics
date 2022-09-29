#pragma once

#include "Scene.h"
#include "Triangle.h"
#include "Rect.h"

class DebugScene : public Scene
{
public:
	DebugScene();
	~DebugScene();

	void OnLoad() override;

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y) override;
	void OnRender() override;

private:
	std::vector<Triangle> _tri;
	Rect _rect;
};

