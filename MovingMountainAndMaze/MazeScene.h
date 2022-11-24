#pragma once

#include <Scene.h>

class Shader;
class Object;

class MazeScene : public Scene
{
private:
	enum class DIRECTION
	{
		NONE = 0,
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		MAX
	};
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
	void ViewProjection(std::shared_ptr<class Shader>& shader);
	void Render(std::vector<Object*>* object, std::shared_ptr<Shader>& shader);
	void RenderMaze();

	void CreateMaze();
	void CreatePlayer();
	void ChangeCamera(define::CAMERA_TYPE type);
	void ScalePillar();
	void RotateCamera(int32_t direction);
	void MakeMaze();
	void ShowPlayer();
	void ShowMaze();
	void MovePlayer(DIRECTION direction);
	void ChangePlayerSpeed(int32_t delta);
	void Reset();

private:
	std::unique_ptr<class Camera> _camera;
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
	std::vector<std::vector<char>> _maze;
	std::list<std::pair<int32_t, int32_t>> _block_pos_index;
	std::vector<std::vector<Object*>> _block;
	std::vector<Object*> _player;
	DIRECTION _direction;

	int32_t _block_num;

	bool _render_player;
	float _wait_time;
};
