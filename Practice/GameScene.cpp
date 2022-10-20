#include "pch.h"
#include "Figure.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{ 0 },
	_grid{},
	_sub_object{},
	_stop_animation{ false }
{
	_grid.push_back(new Line{ vec3::zero(), vec3::x(100.f) });
	_grid.push_back(new Line{ vec3::zero(), vec3::y(100.f) });
	_grid.push_back(new Line{ vec3::zero(), vec3::z(100.f) });

	_object.push_back(new Rect{ vec3::left(0.5f), glm::vec3{ 0.f, 0.5f, 0.5f } });
	_object.push_back(new Rect{ vec3::right(0.5f), glm::vec3{ 0.f, 0.5f, 0.5f } });
	_object.push_back(new Rect{ vec3::up(0.5f), glm::vec3{ 0.5f, 0.f, 0.5f } });
	_object.push_back(new Rect{ vec3::down(0.5f), glm::vec3{ 0.5f, 0.f, 0.5f } });
	_object.push_back(new Rect{ vec3::front(0.5f), glm::vec3{ 0.5f, 0.5f, 0.f } });
	_object.push_back(new Rect{ vec3::back(0.5f), glm::vec3{ 0.5f, 0.5f, 0.f } });

	_sub_object.push_back(new Rect{ vec3::down(10.5f) });
	_sub_object.push_back(new Triangle{ vec3::left(1.5f) });
	_sub_object.push_back(new Triangle{ vec3::left(1.5f) });
	_sub_object.push_back(new Triangle{ vec3::left(1.5f) });

	_camera->Move(3.f, 3.f, 5.f - 1.f);
}

GameScene::~GameScene()
{
	for (auto& line : _grid)
	{
		delete line;
	}

	for (auto& obj : _object)
	{
		delete obj;
	}

	for (auto& obj : _sub_object)
	{
		delete obj;
	}

	_grid.clear();
	_object.clear();
}

void GameScene::OnLoad()
{
	for (auto& line : _grid)
	{
		line->OnLoad();
	}

	for (auto& obj : _object)
	{
		obj->OnLoad();
	}

	for (auto& obj : _sub_object)
	{
		obj->OnLoad();
	}
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{

	}
}

void GameScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

}

void GameScene::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

	}
}

void GameScene::OnRender()
{
	glClearColor(GRAY, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto& line : _grid)
	{
		line->GetShader()->Use();
		line->BindVAO();

		line->Transform();
		CameraMgr::ViewTransform(line->GetShader());
		CameraMgr::ProjectionTransform(line->GetShader());

		glDrawElements(line->GetDrawType(), line->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}

	for (auto& obj : _object)
	{
		obj->GetShader()->Use();
		obj->BindVAO();

		obj->Transform();
		CameraMgr::ViewTransform(obj->GetShader());
		CameraMgr::ProjectionTransform(obj->GetShader());

		glDrawElements(GL_LINE_LOOP, obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::OnAnimate(int32_t value)
{

	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
