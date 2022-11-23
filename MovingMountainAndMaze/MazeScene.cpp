#include "pch.h"
#include <Shader.h>
#include <Figure.h>
#include <Camera.h>
#include "MazeScene.h"
#include <Engine.h>
#include "MazeGenerator.h"

extern Engine engine;

std::uniform_real_distribution<float> urd_scale{ 5.f, 15.f };

MazeScene::MazeScene(int32_t width, int32_t height) :
#pragma region [BASE ATTRIBUTE]
	_camera{ std::make_unique<Camera>(glm::vec3{ 0.f, 1.f, 3.f }, vec3::up(), 0.f, -90.f) },
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
	_maze{},
	_block_num{},
	_direction{ DIRECTION::NONE },
	_render_player{ true },
	_wait_time{ 0.f }
{
#if _DEBUG
	_color_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Color.glsl");
	_light_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Light.glsl");
#else
	_color_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Color.glsl");
	_light_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Light.glsl");
#endif
	MazeGenerator generator{ _maze, width, height };

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
	LoadObject(&_block, _light_shader);
	LoadObject(&_player, _light_shader);
}

void MazeScene::OnRelease()
{
	ReleaseObject(&_block);
	ReleaseObject(&_player);
}

void MazeScene::OnIdleMessage()
{
	CalculateDeltaTime();
}

void MazeScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	if (_wait_time < 0.002f)
	{
		_wait_time += _delta_time;
		return;
	}

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
			ScalePillar();
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
		// 미로 제작
		case 'R': FALLTHROUGH
		case 'r':
		{
			RemakeMaze();
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
			ChangePlayerSpeed(1);
		}
		break;
		// 육면체 이동 속도 감소
		case '-':
		{
			ChangePlayerSpeed(-1);
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
	_wait_time = 0.f;
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

	_camera->OnSpecialKeyMessage(key, x, y, 1.f);
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

	_camera->OnMouseMotionMessage(delta_x, delta_y);
}

void MazeScene::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
}

void MazeScene::OnAnimate(int32_t index)
{
	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, index);
}

void MazeScene::OnRender()
{
	glClearColor(BLACK, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// TODO : Object render
	Render(&_block, _light_shader);
	if (_render_player)
		Render(&_player, _light_shader);
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

void MazeScene::CreateMaze()
{
	for (int32_t z = 0; z < _maze.size(); ++z)
	{
		for (int32_t x = 0; x < _maze[z].size(); ++x)
		{
			if (_maze[z][x] == ' ')
				continue;

			float scale_size{ urd_scale(dre) };

			_block.push_back(new Cube{});
			_block.back()->SetShader(_light_shader);
			_block.back()->Scale(2.f, scale_size, 2.f);
			_block.back()->SetColor(RAND_COLOR);
			_block.back()->Move((x - 1) * 2, scale_size / 2, -(z * 2));
		}
	}
}

void MazeScene::CreatePlayer()
{
	_player.push_back(new Sphere{});
	_player.back()->SetShader(_light_shader);
	_player.back()->SetColor(RAND_COLOR);
	_player.back()->ApplyColor();
	_player.back()->Scale(glm::vec3{ 0.05f });
	_player.back()->Move(0.f, 0.025f, 0.f);
}

void MazeScene::ChangeCamera(define::CAMERA_TYPE type)
{
	if (type == define::CAMERA_TYPE::PERSPECTIVE)
		_camera->SetCameraMode(true);
	else if (type == define::CAMERA_TYPE::ORTHOGRAPHIC)
		_camera->SetCameraMode(false);

}

void MazeScene::ScalePillar()
{
}

void MazeScene::RotateCamera(int32_t direction)
{
	_camera->RotateY(2 * direction);
}

void MazeScene::RemakeMaze()
{
}

void MazeScene::ShowPlayer()
{
	_render_player = !_render_player;
}

void MazeScene::ShowMaze()
{
	_stop_animation = true;

	for (auto& obj : _block)
	{
		auto pos{ obj->GetPos() };

		obj->Move(-pos);
		obj->Scale(2.f, 0.1f, 2.f);
		obj->Move(pos.x, pos.y, pos.z);
	}
}

void MazeScene::MovePlayer(DIRECTION direction)
{
	switch (direction)
	{
		case DIRECTION::LEFT:
		{
			_camera->RotateY(-90);
			_player.back()->Move(vec3::left(1.f));
		}
		break;
		case DIRECTION::RIGHT:
		{
			_camera->RotateY(90);
			_player.back()->Move(vec3::right(1.f));
		}
		break;
		case DIRECTION::FRONT:
		{
			_player.back()->Move(vec3::front(1.f));
		}
		break;
		case DIRECTION::BACK:
		{
			_player.back()->Move(vec3::back(1.f));
		}
		break;
	}
}

void MazeScene::ChangePlayerSpeed(int32_t delta)
{
}

void MazeScene::Reset()
{
}

#pragma endregion