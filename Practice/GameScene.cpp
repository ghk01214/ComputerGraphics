#include "pch.h"
#include "Triangle.h"
#include "Rect.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

enum
{
	NONE = 0,
	C_LEFT,
	C_TOP,
	C_RIGHT,
	C_BOTTOM,
	MAX
};

extern Window window;
std::uniform_int_distribution<int32_t> uid_time{ 1, 3 };
std::uniform_real_distribution<float> uid_out_x{ -0.5f, 0.5f };
std::uniform_real_distribution<float> uid_out_y{ -1.f, -0.5f };

std::shared_ptr<GameScene> GameScene::_inst{ nullptr };

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{},
	_type{ GL_TRIANGLES },
	_info{},
	_dir{ C_LEFT }
{
	_object.push_back(new Triangle{ glm::vec3{ uid_out_x(dre), uid_out_y(dre), 0.f }, false });
	_object.push_back(new Triangle{ glm::vec3{ 0.f, -0.4f, 0.f }, false });
	_object.push_back(new Triangle{ glm::vec3{ 0.f, 0.4f, 0.f }, true });
	_object.push_back(new Rect{});

	_inst.reset(this);
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	_info.insert(std::make_pair(_object[0], std::make_pair(1, C_LEFT)));
	_info.insert(std::make_pair(_object[1], std::make_pair(uid_time(dre), C_LEFT)));
	_info.insert(std::make_pair(_object[2], std::make_pair(uid_time(dre), C_RIGHT)));

	for (int32_t i = 0; i < _object.size() - 1; ++i)
	{
		_object[i]->OnLoad();

		glutTimerFunc(_info[_object[i]].first * 10, Engine::OnAnimate, i);
	}

	_object[3]->OnLoad();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'A': FALLTHROUGH
		case 'a':
			_type = GL_LINE_LOOP;
			break;
		case 'B': FALLTHROUGH
		case 'b':
			_type = GL_TRIANGLES;
			break;
	}
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		if (_index >= _object.size())
			_index = 0;

		//_object[_index++]->Teleport(x2, y2, 0.f);
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& obj : _object)
	{
		obj->GetShader()->Use();
		obj->BindVAO();

		obj->Transform();
		//CameraMgr::ViewTransform(obj->GetShader());
		//CameraMgr::ProjectionTransform(obj->GetShader());

		glDrawElements(_type, obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::OnAnimate(int32_t value)
{
	if (value == 0)
		_inst->Outside(value);
	else
		_inst->Inside(value);

	glutTimerFunc(_inst->_info[_inst->_object[value]].first * 10, Engine::OnAnimate, value);
}

void GameScene::Outside(int32_t index)
{
	auto triangle{ dynamic_cast<Triangle*>(_object[0]) };
	glm::vec3 pos{ triangle->GetPos() };

	switch (_info[triangle].second)
	{
		case C_LEFT:
		{
#pragma region [OUTER BOUNDARY]
			if (pos.x < -0.9f)
			{
				if (_dir == C_LEFT)
				{
					Move(triangle, C_TOP, glm::vec3{ -0.9f, pos.y, 0.f }, -90.f);
					_dir = C_TOP;
				}
				else
					Move(triangle, C_TOP, glm::vec3{ -0.9f, pos.y, 0.f }, -180.f);

				break;
			}
#pragma endregion
#pragma region [INNER BOUNDARY]
			if (pos.y > -0.7f)
			{
				if (-0.5f < pos.x and pos.x < 0.5f)
					Move(triangle, C_BOTTOM, glm::vec3{ pos.x, -0.7f, 0.f }, -180.f);
				else
					triangle->Move(-0.01f, 0.01f, 0.f);

				break;
			}
#pragma endregion

			triangle->Move(-0.01f, 0.01f, 0.f);
		}
		break;
		case C_TOP:
		{
#pragma region [OUTER BOUNDARY]
			if (pos.y > 0.8f)
			{
				if (_dir == C_TOP)
				{
					Move(triangle, C_RIGHT, glm::vec3{ pos.x, 0.8f, 0.f }, -90.f);
					_dir = C_RIGHT;
				}
				else
					Move(triangle, C_RIGHT, glm::vec3{ pos.x, 0.8f, 0.f }, -180.f);

				break;
			}
#pragma endregion
#pragma region [INNER BOUNDARY]
			if (pos.x > -0.7f)
			{
				if (-0.5f < pos.y and pos.y < 0.5f)
					Move(triangle, C_LEFT, glm::vec3{ -0.7, pos.y, 0.f }, -180.f);
				else
					triangle->Move(0.01f, 0.01f, 0.f);

				break;
			}
#pragma endregion

			triangle->Move(0.01f, 0.01f, 0.f);
		}
		break;
		case C_RIGHT:
		{
#pragma region [OUTER BOUNDARY]
			if (pos.x > 0.9f)
			{
				if (_dir == C_RIGHT)
				{
					Move(triangle, C_BOTTOM, glm::vec3{ 0.9f, pos.y, 0.f }, -90.f);
					_dir = C_BOTTOM;
				}
				else
					Move(triangle, C_BOTTOM, glm::vec3{ 0.9f, pos.y, 0.f }, -180.f);

				break;
			}
#pragma endregion
#pragma region [INNER BOUNDARY]
			if (pos.y < 0.7f)
			{
				if (-0.5f < pos.x and pos.x < 0.5f)
					Move(triangle, C_TOP, glm::vec3{ pos.x, 0.7f, 0.f }, -180.f);
				else
					triangle->Move(0.01f, -0.01f, 0.f);

				break;
			}
#pragma endregion

			triangle->Move(0.01f, -0.01f, 0.f);
		}
		break;
		case C_BOTTOM:
		{
#pragma region [OUTER BOUNDARY]
			if (pos.y < -0.8f)
			{
				if (_dir == C_BOTTOM)
				{
					Move(triangle, C_LEFT, glm::vec3{ pos.x, -0.8f, 0.f }, -90.f);
					_dir = C_LEFT;
				}
				else
					Move(triangle, C_LEFT, glm::vec3{ pos.x, -0.8f, 0.f }, -180.f);

				break;
			}
#pragma endregion
#pragma region [INNER BOUNDARY]
			if (pos.x < 0.7f)
			{
				if (-0.5f < pos.y and pos.y < 0.5f)
					Move(triangle, C_RIGHT, glm::vec3{ 0.7f, pos.y, 0.f }, -180.f);
				else
					triangle->Move(-0.01f, -0.01f, 0.f);

				break;
			}
#pragma endregion

			triangle->Move(-0.01f, -0.01f, 0.f);
		}
		break;
	}

	std::cout << _info[triangle].second << ", " << triangle->GetPos().x << ", " << triangle->GetPos().y << std::endl;
	triangle->GetMesh()->CreateVertex(triangle->GetShader());
	glutPostRedisplay();
}

void GameScene::Inside(int32_t index)
{
	auto triangle{ dynamic_cast<Triangle*>(_object[index]) };
	glm::vec3 pos{ triangle->GetPos() };

	if (_info[triangle].second == C_LEFT)
	{
		triangle->Move(-0.01f, 0.f, 0.f);

		if (pos.x <= -0.4f)
		{
			triangle->SetPos(glm::vec3{ -0.4f, pos.y, pos.z });
			triangle->ChangeColor();
			_info[triangle].second = C_RIGHT;
		}
	}
	else
	{
		triangle->Move(0.01f, 0.f, 0.f);

		if (pos.x >= 0.4f)
		{
			triangle->SetPos(glm::vec3{ 0.4f, pos.y, pos.z });
			triangle->ChangeColor();
			_info[triangle].second = C_LEFT;
		}
	}

	triangle->GetMesh()->CreateVertex(triangle->GetShader());
	glutPostRedisplay();
}

void GameScene::Move(Triangle* obj, int32_t direction, glm::vec3 pos, float angle)
{
	_info[obj].second = direction;
	obj->SetPos(pos);
	obj->RotateZ(angle);
}
