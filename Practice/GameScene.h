#pragma once

#include "Scene.h"

enum class DIRECTION
{
	NONE = 0,
	LEFT,
	RIGHT,
	FRONT,
	BACK,
	MAX
};

class Object;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

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

	void ViewProjection(std::shared_ptr<class Shader>& shader);
public:
	void CreateRobot();
	void CreateStage();
	
	void RenderObject(std::vector<Object*>* object);

	void MoveRobot(uchar key);
	void Jump();
	void Orbit();

	void Reset();

private:
	std::unique_ptr<class Camera> _camera;
	std::vector<Object*> _robot;
	std::vector<Object*> _stage;

	bool _stop_animation;
	bool _click;

	int32_t _old_x;
	int32_t _old_y;
private:
	DIRECTION _direction;
	float _camera_angle;

	float _gravity;
	float _jump_speed;
	float _jump_pos;

	float _delta_time;
	int32_t _old_time;
};
