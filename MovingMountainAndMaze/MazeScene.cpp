#include "pch.h"
#include <Shader.h>
#include <Figure.h>
#include <Camera.h>
#include "Player.h"
#include "MazeScene.h"
#include <Engine.h>
#include "MazeGenerator.h"

extern Engine engine;

std::uniform_real_distribution<float> urd_scale{ 5.f, 15.f };
std::uniform_real_distribution<float> urd_speed{ 0.1f, 0.5f };

MazeScene::MazeScene(int32_t width, int32_t height) :
#pragma region [BASE ATTRIBUTE]
	_color_shader{ std::make_shared<Shader>() },
	_light_shader{ std::make_shared<Shader>() },
	_stop_animation{ true },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_time{ glutGet(GLUT_ELAPSED_TIME) },
	_old_time{ _time },
	_delta_time{ 0.f },
#pragma endregion
	_first_camera{ std::make_shared<Camera>(glm::vec3{ 0.f, 1.f, 0.f }, vec3::up(), 0.f, -90.f) },
	_third_camera{ std::make_shared<Camera>(glm::vec3{ 0.f, 1.f, 2.f }, vec3::up(), 0.f, -90.f) },
	_top_camera{ std::make_shared<Camera>(glm::vec3{ width / 2 + 10.f, 50.f, -(height / 2) - 10.f }, vec3::up(), -90.f, 90.f) },
	_camera{},
	_maze{},
	_maze_width{ width },
	_maze_height{ height },
	_render_player{ true },
	_wait_time{ 0.f },
	_show_maze{ false },
	_player_speed{ 5.f },
	_scale_size{},
	_scale_speed{},
	_scale_up{},
	_player{},
	_current_scale{},
	_animation_speed{ 100 }
{
#if _DEBUG
	_color_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Color.glsl");
	_light_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Light.glsl");
#else
	_color_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Color.glsl");
	_light_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Light.glsl");
#endif
	MazeGenerator generator{ _maze, width, height };

	_camera = _third_camera;

	CreateMaze();
	CreatePlayer();
}

MazeScene::~MazeScene()
{
	OnRelease();
}

#pragma region [PUBLIC]
void MazeScene::OnLoad()
{
	for (int32_t z = 0; z < _block.size(); ++z)
	{
		LoadObject(&_block[z], _light_shader);
	}

	for (auto& obj : _player)
	{
		obj->OnLoad(_light_shader);
	}
}

void MazeScene::OnRelease()
{
	for (int32_t z = 0; z < _block.size(); ++z)
	{
		ReleaseObject(&_block[z]);
	}

	for (auto& obj : _player)
	{
		delete obj;
		obj = nullptr;
	}
}

void MazeScene::OnIdleMessage()
{
	CalculateDeltaTime();
}

void MazeScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		// 직각 투영
		case 'O': FALLTHROUGH
		case 'o':
		{
			ChangeCamera(define::CAMERA_TYPE::ORTHOGRAPHIC);
		}
		break;
		// 원근 투영
		case 'P': FALLTHROUGH
		case 'p':
		{
			ChangeCamera(define::CAMERA_TYPE::PERSPECTIVE);
		}
		break;
		// 육면체 팽창/수축
		case 'M': FALLTHROUGH
		case 'm':
		{
			_stop_animation = !_stop_animation;

			if (_stop_animation == false)
				glutTimerFunc(_animation_speed, Engine::OnAnimate, 1);
		}
		break;
		// 카메라 회전(반시계)
		case 'Y':
		{
			RotateCamera(1);
		}
		break;
		// 카메라 회전(시계)
		case 'y':
		{
			RotateCamera(-1);
		}
		break;
		// 플레이어 반시계 방향 회전
		case 'J': FALLTHROUGH
		case 'j':
		{
			RotatePlayer(-1);
		}
		break;
		// 플레이어 시계 방향 회전
		case 'L': FALLTHROUGH
		case 'l':
		{
			RotatePlayer(1);
		}
		break;
		// 미로 제작
		case 'R': FALLTHROUGH
		case 'r':
		{
			MakeMaze();
		}
		break;
		// 육면체 움직임 멈춤, 낮은 높이로 변환
		case 'V': FALLTHROUGH
		case 'v':
		{
			ShowMaze();
		}
		break;
		// 객체 생성
		case 'S': FALLTHROUGH
		case 's':
		{
			ShowPlayer();
		}
		break;
		// 카메라 시점 변경
		case '1':
		{
			ChangeCamera(define::CAMERA_TYPE::FIRST);
		}
		break;
		case '3':
		{
			ChangeCamera(define::CAMERA_TYPE::THIRD);
		}
		break;
		// 육면체 이동 속도 증가
		case '+':
		{
			ChangeBlockSpeed(-10);
		}
		break;
		// 육면체 이동 속도 감소
		case '-':
		{
			ChangeBlockSpeed(10);
		}
		break;
		// 초기화
		case 'C': FALLTHROUGH
		case 'c':
		{
			Reset();
			system("clear");
		}
		break;
	}

	std::cout << std::format("Key : {:c}\n", key);
}

void MazeScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	if (_wait_time < 0.002f)
	{
		_wait_time += _delta_time;
		return;
	}

	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			MovePlayer(DIRECTION::LEFT);
			std::cout << std::format("Key : Left\n");
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			MovePlayer(DIRECTION::RIGHT);
			std::cout << std::format("Key : Right\n");
		}
		break;
		case GLUT_KEY_UP:
		{
			MovePlayer(DIRECTION::FRONT);
			std::cout << std::format("Key : Up\n");
		}
		break;
		case GLUT_KEY_DOWN:
		{
			MovePlayer(DIRECTION::BACK);
			std::cout << std::format("Key : Down\n");
		}
		break;
	}

	_camera->OnSpecialKeyMessage(key, x, y, _delta_time * _player_speed);
	_wait_time = 0.f;
}

void MazeScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (engine.GetWindowWidth() / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (engine.GetWindowHeight() / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		_click = true;
	}
}

void MazeScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (engine.GetWindowWidth() / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (engine.GetWindowHeight() / 2) };

	if (_click)
	{
		_old_x = x;
		_old_y = y;
		_click = false;
	}

	float delta_x{ Convert::ToFloat(x - _old_x) };
	float delta_y{ Convert::ToFloat(_old_y - y) };
	_old_x = x;
	_old_y = y;

	//_camera->OnMouseMotionMessage(delta_x, delta_y);
}

void MazeScene::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
}

void MazeScene::OnAnimate(int32_t index)
{
	ScalePillar();

	if (_stop_animation == false)
		glutTimerFunc(_animation_speed, Engine::OnAnimate, index);
}

void MazeScene::OnRender()
{
	glClearColor(BLACK, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// TODO : Object render
	glViewport(0, 0, engine.GetWindowWidth() - 200, engine.GetWindowHeight());
	ViewProjection(_light_shader);
	RenderMaze();

	if (_render_player == true)
		RenderPlayer();

	glViewport(engine.GetWindowWidth() - 200, engine.GetWindowHeight() - 200, 200, 200);
	TopViewProjection(_light_shader);
	RenderMaze();

	if (_render_player == true)
		RenderPlayer();
}
#pragma endregion

#pragma region [PRIVATE]
void MazeScene::CalculateDeltaTime()
{
	_time = glutGet(GLUT_ELAPSED_TIME);

	_delta_time = Convert::ToFloat((_time - _old_time)) / 1000.f;
	_old_time = _time;
}

void MazeScene::LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
{
	for (auto& obj : *object)
	{
		obj->OnLoad(shader);
	}
}

void MazeScene::ReleaseObject(std::vector<Object*>* object)
{
	for (auto& obj : *object)
	{
		if (obj == nullptr)
			continue;

		delete obj;
		obj = nullptr;
	}
}

void MazeScene::ViewProjection(std::shared_ptr<class Shader>& shader)
{
	auto view{ _camera->GetViewMatrix() };
	auto projection{ _camera->GetProjectionMatrix() };

	shader->SetMat4("view", &view);
	shader->SetMat4("projection", &projection);
}

void MazeScene::Render(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
{
	glm::vec3 view_pos{ _camera->GetPos() };
	shader->SetVec3("view_pos", &view_pos);

	shader->OnUse();

	for (auto& obj : *object)
	{
		obj->BindVAO();

		obj->Transform(shader);
		ViewProjection(shader);

		obj->ApplyColor();
		//obj->SetLightPos(_light.back()->GetPos());

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void MazeScene::RenderMaze()
{
	glm::vec3 view_pos{ _camera->GetPos() };
	_light_shader->SetVec3("view_pos", &view_pos);

	_light_shader->OnUse();

	//ViewProjection(_light_shader);
	//TopViewProjection(_light_shader);

	for (int32_t z = 0; z < _block.size(); ++z)
	{
		for (int32_t x = 0; x < _block[z].size(); ++x)
		{
			if (_block[z][x] == nullptr)
				continue;

			auto obj{ _block[z][x] };

			obj->BindVAO();

			obj->Transform(_light_shader);

			obj->ApplyColor();
			//obj->SetLightPos(_light.back()->GetPos());

			glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
		}
	}
}

void MazeScene::RenderPlayer()
{
	glm::vec3 view_pos{ _camera->GetPos() };
	_light_shader->SetVec3("view_pos", &view_pos);

	_light_shader->OnUse();

	//ViewProjection(_light_shader);
	//TopViewProjection(_light_shader);

	for (auto& obj : _player)
	{
		obj->BindVAO();

		obj->Transform(_light_shader);

		obj->ApplyColor();
		//obj->SetLightPos(_light.back()->GetPos());

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void MazeScene::TopViewProjection(std::shared_ptr<Shader>& shader)
{
	auto view{ _top_camera->GetViewMatrix() };
	auto projection{ _top_camera->GetProjectionMatrix() };

	shader->SetMat4("view", &view);
	shader->SetMat4("projection", &projection);
}

void MazeScene::CreateMaze()
{
	std::vector<Object*> temp;
	_block.resize(_maze.size(), temp);

	std::vector<float> temp2;
	_scale_size.resize(_block.size(), temp2);
	_scale_speed.resize(_block.size(), temp2);

	std::vector<bool> temp3;
	_scale_up.resize(_block.size(), temp3);

	std::vector<std::pair<float, float>> temp4;
	_scale_min_max.resize(_block.size(), temp4);

	std::uniform_real_distribution<float> urd_min{ 1.f, 5.f };
	std::uniform_real_distribution<float> urd_max{ 5.f, 15.f };

	for (int32_t z = 0; z < _maze.size(); ++z)
	{
		_block[z].resize(_maze[z].size(), nullptr);
		_scale_size[z].resize(_block[z].size(), 0.f);
		_scale_speed[z].resize(_block[z].size(), 0.f);
		_scale_up[z].resize(_block[z].size(), false);
		_scale_min_max[z].resize(_block[z].size(), std::make_pair(0.f, 0.f));

		for (int32_t x = 0; x < _maze[z].size(); ++x)
		{
			_scale_size[z][x] = urd_scale(dre);
			_scale_speed[z][x] = urd_speed(dre);
			_scale_up[z][x] = false;
			_scale_min_max[z][x] = std::make_pair(urd_min(dre), urd_max(dre));

			_block[z][x] = new Cube{};
			_block[z][x]->SetShader(_light_shader);
			_block[z][x]->Scale(2.f, _scale_size[z][x], 2.f);
			_block[z][x]->SetColor(RAND_COLOR);
			_block[z][x]->Move((x - 1) * 2, _scale_size[z][x] / 2, -(z * 2));
		}
	}

	_current_scale = _scale_size;
}

void MazeScene::CreatePlayer()
{
	_player.push_back(new Player{});
	_player.back()->SetShader(_light_shader);
	_player.back()->SetColor(RAND_COLOR);
	_player.back()->ApplyColor();
	_player.back()->Scale(glm::vec3{ 0.05f });
	_player.back()->Move(0.f, 0.025f, 0.f);
}

void MazeScene::ChangeCamera(define::CAMERA_TYPE type)
{
	if (type == define::CAMERA_TYPE::PERSPECTIVE)
	{
		_camera->SetCameraMode(true);
	}
	else if (type == define::CAMERA_TYPE::ORTHOGRAPHIC)
	{
		_camera->SetCameraMode(false);
	}
	else if (type == define::CAMERA_TYPE::FIRST)
	{
		_render_player = false;
		_camera = _first_camera;
	}
	else
	{
		_render_player = true;
		_camera = _third_camera;
	}
}

void MazeScene::ScalePillar()
{
	for (int32_t z = 0; z < _block.size(); ++z)
	{
		for (int32_t x = 0; x < _block[z].size(); ++x)
		{
			if (_block[z][x] == nullptr)
				continue;

			auto min{ _scale_min_max[z][x].first };
			auto max{ _scale_min_max[z][x].second };
			auto pos{ _block[z][x]->GetPos() };

			if (_scale_up[z][x] == true and _current_scale[z][x] > max)
				_scale_up[z][x] = false;
			else if (_scale_up[z][x] == false and _current_scale[z][x] < min)
				_scale_up[z][x] = true;

			_block[z][x]->Move(-pos);
			
			if (_scale_up[z][x] == true)
			{
				_block[z][x]->Scale(1.f, 1.f + _scale_speed[z][x], 1.f);
				_current_scale[z][x] *= (1.f + _scale_speed[z][x]);
			}
			else
			{
				_block[z][x]->Scale(1.f, 1.f - _scale_speed[z][x], 1.f);
				_current_scale[z][x] *= (1.f - _scale_speed[z][x]);
			}

			_block[z][x]->Move(pos.x, _current_scale[z][x] / 2, pos.z);
		}
	}
}

void MazeScene::RotateCamera(int32_t direction)
{
	_first_camera->RotateY(2 * direction);
	_third_camera->RotateY(2 * direction);
}

void MazeScene::MakeMaze()
{
	for (int32_t z = 0; z < _maze.size(); ++z)
	{
		for (int32_t x = 0; x < _maze[z].size(); ++x)
		{
			if (_maze[z][x] == ' ')
			{
				delete _block[z][x];
				_block[z][x] = nullptr;
			}
		}
	}
}

void MazeScene::ShowPlayer()
{
	_render_player = !_render_player;
}

void MazeScene::ShowMaze()
{
	_stop_animation = !_stop_animation;
	float scale;

	for (int32_t z = 0; z < _maze.size(); ++z)
	{
		for (int32_t x = 0; x < _maze[z].size(); ++x)
		{
			auto obj{ _block[z][x] };

			if (obj == nullptr)
				continue;

			auto pos{ obj->GetPos() };

			if (_show_maze == false)
				scale = 1.f / _scale_size[z][x];
			else
				scale = _scale_size[z][x];

			obj->Move(-pos);
			obj->Scale(1.f, scale, 1.f);
			obj->Move(pos.x, scale * 0.5f, pos.z);
		}
	}

	_show_maze = !_show_maze;
}

void MazeScene::MovePlayer(DIRECTION direction)
{
	_player.back()->MovePlayer(direction, _delta_time * _player_speed * 2.5f);
}

void MazeScene::RotatePlayer(int32_t direction)
{
	_third_camera->Move(Camera::DIRECTION::FRONT, 2.f);
	_third_camera->RotateY(90.f * direction);
	_third_camera->Move(Camera::DIRECTION::BACK, 2.f);

	_first_camera->RotateY(90.f * direction);
	_player.back()->RotatePlayer(1 * direction);
}

void MazeScene::ChangeBlockSpeed(int32_t delta)
{
	if (delta < 0 and _animation_speed == 10)
		return;

	_animation_speed += delta;
}

void MazeScene::Reset()
{
	OnRelease();

	_render_player = true;
	_wait_time = 0.f;
	_show_maze = false;
	_player_speed = 5.f;
	_delta_time = 0.f;

	_first_camera.reset();
	_third_camera.reset();

	_first_camera = std::make_shared<Camera>(glm::vec3{ 0.f, 1.f, 0.f }, vec3::up(), 0.f, -90.f);
	_third_camera = std::make_shared<Camera>(glm::vec3{ 0.f, 1.f, 3.f }, vec3::up(), 0.f, -90.f);

	_camera = _third_camera;

	MazeGenerator generator{ _maze, _maze_width, _maze_height };

	CreateMaze();
	CreatePlayer();

	OnLoad();
}

#pragma endregion