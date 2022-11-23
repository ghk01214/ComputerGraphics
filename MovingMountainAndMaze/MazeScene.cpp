#include "pch.h"
#include <Shader.h>
#include <Figure.h>
#include <Camera.h>
#include "MazeScene.h"
#include <Engine.h>
#include "MazeGenerator.h"

extern Engine engine;

MazeScene::MazeScene(int32_t width, int32_t height) :
#pragma region [BASE ATTRIBUTE]
	_camera{ std::make_unique<Camera>(glm::vec3{ 0.f, 3.f, 0.f }) },
	_color_shader{ std::make_shared<Shader>() },
	_light_shader{ std::make_shared<Shader>() },
	_object{ nullptr },
	_stop_animation{ true },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_time{ glutGet(GLUT_ELAPSED_TIME) },
	_old_time{ _time },
	_delta_time{ 0.f },
	_maze{}
#pragma endregion
{
#if _DEBUG
	_color_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Color.glsl");
	_light_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Light.glsl");
#else
	_color_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Color.glsl");
	_light_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Light.glsl");
#endif
	MazeGenerator generator{ width, height };

	_maze = generator.GetMaze();
}

MazeScene::~MazeScene()
{
	OnRelease();
}

// =======================================PUBLIC METHOD=======================================

void MazeScene::OnLoad()
{
}

void MazeScene::OnRelease()
{
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

		}
		break;
		// 원근 투영
		case 'P': FALLTHROUGH
		case 'p':
		{

		}
		break;
		// 
		case 'M':
		{

		}
		break;
		case 'm':
		{

		}
		break;
		case 'Y':
		{

		}
		break;
		case 'y':
		{

		}
		break;
		// 미로 제작
		case 'R': FALLTHROUGH
		case 'r':
		{

		}
		break;
		case 'V': FALLTHROUGH
		case 'v':
		{

		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{

		}
		break;
		case '1': FALLTHROUGH
		case '3':
		{

		}
		break;
		case '+':
		{

		}
		break;
		case '-':
		{

		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{

		}
		break;
	}
}

void MazeScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	_camera->OnSpecialKeyMessage(key, x, y, 0.1f);
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
}

// =======================================PRIVATE METHOD=======================================

void MazeScene::CalculateDeltaTime()
{
	_time = glutGet(GLUT_ELAPSED_TIME);

	_delta_time = Convert::ToFloat((_time - _old_time)) / 1000.f;
	_old_time = _time;
}

void MazeScene::LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
{
}

void MazeScene::ViewProjection(std::shared_ptr<class Shader>& shader)
{
	auto view{ _camera->GetViewMatrix() };
	auto projection{ _camera->GetProjectionMatrix() };

	shader->SetMat4("view", &view);
	shader->SetMat4("projection", &projection);
}
