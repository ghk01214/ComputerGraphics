#pragma once

#include <Scene.h>
#include "Maze.h"

class Shader;
class Object;


class MazeScene : public Scene
{
public:
	MazeScene(int32_t size = 5);
	~MazeScene();

	void OnLoad() override;
	void OnRelease() override;

	void OnIdleMessage() override;
	void OnKeyboardMessage(uchar key, int32_t x, int32_t y) override;
	void OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y) override;
	void OnMouseMessage(int32_t button, int32_t x, int32_t y) override;
	void OnMouseMotionMessage(int32_t x, int32_t y) override;
	void OnMouseUpMessage(int32_t button, int32_t x, int32_t y) override;
	void OnAnimate(int32_t index) override;
	void OnRender() override;
private:
	void LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);

	void ViewProjection(std::shared_ptr<class Shader>& shader);

private:
	std::unique_ptr<class Camera> _camera;
	std::shared_ptr<Shader> _color_shader;
	std::shared_ptr<Shader> _light_shader;

	std::vector<Object*>* _object;

	bool _stop_animation;
	bool _click;

	int32_t _old_x;
	int32_t _old_y;

	int32_t _time;
	int32_t _old_time;
	float _delta_time;

	Maze _maze;
};
