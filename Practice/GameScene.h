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
	void OnAnimate(int32_t index) override;
	void OnRender() override;

	void Outside(int32_t index);
	void Inside(int32_t index);
	void Move(class Triangle* obj, int32_t direction, glm::vec3 pos, float angle);

private:
	static std::shared_ptr<GameScene> _inst;

	std::unique_ptr<class CameraMgr> _camera;
	std::vector<Object*> _object;
	std::unordered_map<Object*, std::pair<int32_t, int32_t>> _info;

	uint32_t _index;
	uint32_t _type;
	int32_t _dir;
};
