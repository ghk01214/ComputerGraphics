#pragma once

// NOTE :
// Debugging을 위한 Scene class
// 평소엔 빌드에 포함되진 않고 엔진 내부를 디버깅할 때만 빌드에 포함
// 

#include "Scene.h"

class Object;

class DebugScene : public Scene
{
public:
	DebugScene();
	~DebugScene();

	void OnLoad() override;

	void OnKeyboardMessage(uchar key, int32_t x, int32_t y) override;
	void OnMouseMessage(int32_t button, int32_t x, int32_t y) override;
	void OnRender() override;

	static void Animate(int32_t value);
	void Moving(int32_t index);

private:
	static std::shared_ptr<DebugScene> _inst;

	std::unique_ptr<class CameraMgr> _camera;
	std::vector<Object*> _tri;
	std::unordered_map<Object*, std::pair<int32_t, int32_t>> _info;

	uint32_t _index;
	uint32_t _type;
};
