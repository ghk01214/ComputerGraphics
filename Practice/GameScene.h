#pragma once

#include "Scene.h"

enum class CUBE
{
	NONE = 0,
	LEFT = 0,
	RIGHT,
	TOP,
	BOTTOM,
	FRONT,
	BACK,
	MAX
};

enum class TETRA
{
	NONE = 0,
	BOTTOM = 0,
	FRONT,
	LEFT,
	RIGHT,
	MAX
};

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

private:
	std::unique_ptr<class CameraMgr> _camera;
	std::vector<Object*> _object;

	std::vector<std::vector<uint32_t>> _cube_face;
	std::vector<std::vector<uint32_t>> _tetra_face;

	uint32_t _index;
	uint32_t _rendered;
};
