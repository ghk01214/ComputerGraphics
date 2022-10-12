#include "pch.h"
#include "Triangle.h"
#include "Rect.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{ -1 },
	_move_vertex{ false },
	_move_rect{ false }
{
	_object.push_back(new Rect{});
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	_object[0]->OnLoad();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'O': FALLTHROUGH
		case 'o':
			break;
		case 'I': FALLTHROUGH
		case 'i':
			break;
	}
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };
	auto rect{ dynamic_cast<Rect*>(_object[0]) };
	auto ver{ rect->GetVertex() };
	std::vector<bool> in_rect(4, false);

	if (button == GLUT_LEFT_BUTTON)
	{
		for (int32_t i = 0; i < ver.size(); ++i)
		{
			if (std::abs(x2 - ver[i].x) < 0.05f)
			{
				if (std::abs(y2 - ver[i].y) < 0.05f)
				{
					_move_vertex = true;
					_index = i;
				}
			}
		}

		if (x2 < ver[0].x and y2 > ver[0].y)
		{
			if (x2 < ver[1].x and y2 < ver[1].y)
			{
				if (x2 > ver[2].x and y2 < ver[2].y)
				{
					if (x2 > ver[3].x and y2 > ver[3].y)
					{
						_move_rect = true;
					}
				}
			}
		}
	}
}

void GameScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };
	auto rect{ dynamic_cast<Rect*>(_object[0]) };

	if (_move_vertex == true)
	{
		rect->SetVertex(_index, glm::vec3{ x2, y2, 0.f });
		rect->GetMesh()->CreateVertex(rect->GetShader());
	}
	else if (_move_rect == true)
	{
		rect->SetVertex(glm::vec3{ x2, y2, 0.f });
		rect->GetMesh()->CreateVertex(rect->GetShader());
	}
}

void GameScene::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		_move_vertex = false;
		_move_rect = false;
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& obj : _object)
	{
		obj->GetShader()->Use();
		obj->BindVAO();

		//obj->Transform();
		//CameraMgr::ViewTransform(obj->GetShader());
		//CameraMgr::ProjectionTransform(obj->GetShader());

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::OnAnimate(int32_t value)
{
	//glutTimerFunc(_inst->_info[_inst->_object[value]].first * 10, Engine::OnAnimate, value);
}
