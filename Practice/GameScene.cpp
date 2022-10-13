#include "pch.h"
#include "Line.h"
#include "Triangle.h"
#include "Rect.h"
#include "Cube.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{ -1 },
	_depth_test{ true }
{
	_object.push_back(new Line{ vec3::zero(), 1.f });
	_object.push_back(new Line{ vec3::zero(), 1.f, false });
	_object.push_back(new Cube{});

	_object.back()->RotateY(45.f);
	_object.back()->RotateX(30.f);
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	for (auto& obj : _object)
	{
		obj->OnLoad();
	}
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'C': FALLTHROUGH
		case 'c':
		{

		}
		break;
		case 'P': FALLTHROUGH
		case 'p':
		{

		}
		break;
		case 'H': FALLTHROUGH
		case 'h':
		{

		}
		break;
		case 'x':
		{

		}
		break;
		case 'X':
		{

		}
		break;
		case 'y':
		{

		}
		break;
		case 'Y':
		{

		}
		break;
		case 'w':
		{

		}
		break;
		case 'W':
		{

		}
		break;
		case GLUT_KEY_LEFT:
		{

		}
		break;
		case GLUT_KEY_UP:
		{

		}
		break;
		case GLUT_KEY_RIGHT:
		{

		}
		break;
		case GLUT_KEY_DOWN:
		{

		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{

		}
		break;
	}
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
	Scene::OnRender();

	if (_depth_test == true)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	for (auto& obj : _object)
	{
		obj->GetShader()->Use();
		obj->BindVAO();

		obj->Transform();
		CameraMgr::ViewTransform(obj->GetShader());
		CameraMgr::ProjectionTransform(obj->GetShader());

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::OnAnimate(int32_t value)
{
	//glutTimerFunc(_inst->_info[_inst->_object[value]].first * 10, Engine::OnAnimate, value);
}
