#pragma once

#include <Scene.h>

class Shader;
class Camera;
class Object;
class Player;

class MazeScene : public Scene
{
public:
	MazeScene(int32_t width = 5, int32_t height = 5);
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
	void CalculateDeltaTime();
	void LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void ReleaseObject(std::vector<Object*>* object);
	void ViewProjection(std::shared_ptr<Shader>& shader);
	void Render(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void RenderMaze();
	void RenderPlayer();
	void TopViewProjection(std::shared_ptr<Shader>& shader);

	void CreateMaze();
	void CreatePlayer();
	void ChangeCamera(define::CAMERA_TYPE type);
	void ScalePillar();
	void RotateCamera(int32_t direction);
	void MakeMaze();
	void ShowPlayer();
	void ShowMaze();
	void MovePlayer(DIRECTION direction);
	void RotatePlayer(int32_t direction);
	void ChangeBlockSpeed(int32_t delta);
	void Reset();

private:
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Shader> _color_shader;
	std::shared_ptr<Shader> _light_shader;

	bool _stop_animation;
	bool _click;

	int32_t _old_x;
	int32_t _old_y;

	int32_t _time;
	int32_t _old_time;
	float _delta_time;
private:
	std::shared_ptr<Camera> _first_camera;
	std::shared_ptr<Camera> _third_camera;
	std::shared_ptr<Camera> _top_camera;
	std::vector<std::vector<char>> _maze;
	std::vector<std::vector<Object*>> _block;
	std::vector<std::vector<float>> _scale_size;
	std::vector<std::vector<std::pair<float, float>>> _scale_min_max;
	std::vector<std::vector<float>> _scale_speed;
	std::vector<std::vector<float>> _current_scale;
	std::vector<std::vector<bool>> _scale_up;
	std::vector<Player*> _player;

	int32_t _maze_width;
	int32_t _maze_height;

	float _player_speed;
	int32_t _animation_speed;

	bool _render_player;
	float _wait_time;
	bool _show_maze;
};
