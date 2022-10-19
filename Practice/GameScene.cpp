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
	_grid.push_back(new Line{ vec3::zero(), 5.f });
	_grid.push_back(new Line{ vec3::zero(), 5.f, false });

	_object.push_back(new Cube{ vec3::right(1.5f) });
	_object.push_back(new Cone{ vec3::left(1.5f) });

	_sub_object.push_back(new Teapot{ vec3::right(1.5f) });
	_sub_object.push_back(new Sphere{ vec3::left(1.5f) });

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
	switch (key)
	{
		case 'x':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 2);
		}
		break;
		case 'X':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -2);
		}
		break;
		case 'y':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 4);
		}
		break;
		case 'Y':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -4);
		}
		break;
		case 'a':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 1);
		}
		break;
		case 'A':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -1);
		}
		break;
		case 'b':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 3);
		}
		break;
		case 'B':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -3);
		}
		break;
		case 'r':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 10);
		}
		break;
		case 'R':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -10);
		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{
			_stop_animation = true;

			auto temp{ _object };
			_object = _sub_object;
			_sub_object = temp;
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			_stop_animation = true;

			for (auto& obj : _object)
			{
				delete obj;
			}

			for (auto& obj : _sub_object)
			{
				delete obj;
			}

			_object.clear();
			_sub_object.clear();

			_object.push_back(new Cube{ vec3::right(1.5f) });
			_object.push_back(new Cone{ vec3::left(1.5f) });

			_sub_object.push_back(new Teapot{ vec3::right(1.5f) });
			_sub_object.push_back(new Sphere{ vec3::left(1.5f) });

			for (auto& obj : _object)
			{
				obj->OnLoad();
			}

			for (auto& obj : _sub_object)
			{
				obj->OnLoad();
			}
		}
	}
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
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
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
	int32_t index{ std::abs(value % 2) };

	if (value == 10 or value == -10)
	{
		for (auto& obj : _object)
		{
			obj->RotateY((value / 10) * 0.5f);
		}
	}
	else if (index == 0)
	{
		// x
		if (value / 4 == 0)
		{
			_object[index]->RotateX((value / 2) * 1.f);
		}
		// y
		else
		{
			_object[index]->Move(vec3::left(1.5f));
			_object[index]->RotateY(value * 0.5f);
			_object[index]->Move(vec3::right(1.5f));
		}
	}
	else if (index == 1)
	{
		// a
		if (value / 3 == 0)
		{
			_object[index]->RotateX(value * 1.f);
		}
		// b
		else
		{
			_object[index]->Move(vec3::right(1.5f));
			_object[index]->RotateY((value / 3) * 0.5f);
			_object[index]->Move(vec3::left(1.5f));
		}
	}

	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
