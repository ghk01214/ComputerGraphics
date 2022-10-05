#include "pch.h"
#include "Triangle.h"
#include "CameraMgr.h"
#include "GameScene.h"

enum
{
	NONE = 0,
	LT,
	LB,
	TR,
	TL,
	RB,
	RT,
	BL,
	BR,
	MAX
};

extern Window window;
std::uniform_int_distribution<int32_t> uid_left{ LT, LB };
std::uniform_int_distribution<int32_t> uid_top{ TR, TL };
std::uniform_int_distribution<int32_t> uid_right{ RB, RT };
std::uniform_int_distribution<int32_t> uid_bottom{ BL, BR };
std::uniform_int_distribution<int32_t> uid_direction{ LT, BR };
std::uniform_int_distribution<int32_t> uid_time{ 1, 4 };
std::uniform_real_distribution<float> uid_pos{ -1.f, 1.f };

std::shared_ptr<GameScene> GameScene::_inst{ nullptr };

GameScene::GameScene() :
	_camera{},
	_tri{},
	_index{},
	_type{ GL_TRIANGLES },
	_info{}
{
	_tri.push_back(Triangle{});
	_tri.back().Teleport(glm::vec3{ uid_pos(dre), uid_pos(dre), 0.f});

	//_tri.push_back(Triangle{});
	//_tri.back().Teleport(glm::vec3{ 0.5f, 0.5f, 0.f });

	//_tri.push_back(Triangle{});
	//_tri.back().Teleport(glm::vec3{ 0.5f, -0.5f, 0.f });

	//_tri.push_back(Triangle{});
	//_tri.back().Teleport(glm::vec3{ -0.5f, -0.5f, 0.f });

	_inst.reset(this);
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	for (int32_t i = 0; i < _tri.size(); ++i)
	{
		_tri[i].OnLoad();
		_info.insert(std::make_pair(_tri[i], std::make_pair(uid_time(dre), uid_direction(dre))));

		glutTimerFunc(_info[_tri[i]].first * 10, Animate, i);
	}
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
		if (_index >= _tri.size())
			_index = 0;

		_tri[_index++].Teleport(x2, y2, 0.f);
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& tri : _tri)
	{
		tri.BindVAO();

		tri.Transform();
		//CameraMgr::ViewTransform(tri.GetShader());
		//CameraMgr::ProjectionTransform(tri.GetShader());

		glDrawElements(_type, tri.GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::Animate(int32_t value)
{
	_inst->Moving(value);
	glutTimerFunc(_inst->_info[_inst->_tri[value]].first * 10, Animate, value);
}

void GameScene::Moving(int32_t index)
{
	switch (_info[_tri[index]].second)
	{
		case LT:
		{
			if (_tri[index].GetPos().x > 0.9f)
			{
				_info[_tri[index]].second = uid_right(dre);
				RotateX(index, 1, 1);

				break;
			}

			if (_tri[index].GetPos().y > 0.9f)
			{
				_info[_tri[index]].second = uid_top(dre);
				RotateY(index, 1, 1);

				break;
			}

			_tri[index].Move(0.01f, 0.02f, 0.f);
		}
		break;
		case LB:
		{
			if (_tri[index].GetPos().x > 0.9f)
			{
				_info[_tri[index]].second = uid_right(dre);
				RotateX(index, -1, 1);

				break;
			}

			if (_tri[index].GetPos().y < -0.9f)
			{
				_info[_tri[index]].second = uid_bottom(dre);
				RotateY(index, -1, -1);

				break;
			}

			_tri[index].Move(0.01f, -0.02f, 0.f);
		}
		break;
		case TR:
		{
			if (_tri[index].GetPos().x > 0.9f)
			{
				_info[_tri[index]].second = uid_right(dre);
				RotateX(index, 1, 1);

				break;
			}

			if (_tri[index].GetPos().y < -0.9f)
			{
				_info[_tri[index]].second = uid_bottom(dre);
				RotateY(index, -1, -1);

				break;
			}

			_tri[index].Move(0.01f, -0.02f, 0.f);
		}
		break;
		case TL:
		{
			if (_tri[index].GetPos().x < -0.9f)
			{
				_info[_tri[index]].second = uid_left(dre);
				RotateX(index, -1, -1);

				break;
			}

			if (_tri[index].GetPos().y < -0.9f)
			{
				_info[_tri[index]].second = uid_bottom(dre);
				RotateY(index, -1, -1);

				break;
			}

			_tri[index].Move(-0.01f, -0.02f, 0.f);
		}
		break;
		case RB:
		{
			if (_tri[index].GetPos().x < -0.9f)
			{
				_info[_tri[index]].second = uid_left(dre);
				RotateX(index, 1, -1);

				break;
			}

			if (_tri[index].GetPos().y < -0.9f)
			{
				_info[_tri[index]].second = uid_bottom(dre);
				RotateY(index, 1, -1);

				break;
			}

			_tri[index].Move(-0.01f, -0.02f, 0.f);
		}
		break;
		case RT:
		{
			if (_tri[index].GetPos().x < -0.9f)
			{
				_info[_tri[index]].second = uid_left(dre);
				RotateX(index, -1, -1);

				break;
			}

			if (_tri[index].GetPos().y > 0.9f)
			{
				_info[_tri[index]].second = uid_top(dre);
				RotateY(index, -1, 1);

				break;
			}

			_tri[index].Move(-0.01f, 0.02f, 0.f);
		}
		break;
		case BL:
		{
			if (_tri[index].GetPos().x < -0.9f)
			{
				_info[_tri[index]].second = uid_left(dre);
				RotateX(index, -1, -1);

				break;
			}

			if (_tri[index].GetPos().y > 0.9f)
			{
				_info[_tri[index]].second = uid_top(dre);
				RotateY(index, 1, 1);

				break;
			}

			_tri[index].Move(-0.01f, 0.02f, 0.f);
		}
		break;
		case BR:
		{
			if (_tri[index].GetPos().x > 0.9f)
			{
				_info[_tri[index]].second = uid_right(dre);
				RotateX(index, -1, 1);

				break;
			}

			if (_tri[index].GetPos().y > 0.9f)
			{
				_info[_tri[index]].second = uid_top(dre);
				RotateY(index, -1, 1);

				break;
			}

			_tri[index].Move(0.01f, 0.02f, 0.f);
		}
		break;
	}

	std::cout << std::format("{}, x : {}, y : {}\n", _info[_tri[index]].second, _tri[index].GetPos().x, _tri[index].GetPos().y);
	glutPostRedisplay();
}

void GameScene::RotateX(int32_t index, int32_t sign, int32_t sign2)
{
	glm::vec3 old_pos{ _tri[index].GetPos() };

	_tri[index].Teleport(vec3::zero());
	_tri[index].RotateZ(sign * 90.f);
	old_pos.x = sign2 * 0.9f;

	_tri[index].Teleport(old_pos);
}

void GameScene::RotateY(int32_t index, int32_t sign, int32_t sign2)
{
	glm::vec3 old_pos{ _tri[index].GetPos() };

	_tri[index].Teleport(vec3::zero());
	_tri[index].RotateZ(sign * 90.f);
	old_pos.y = sign2 * 0.9f;

	_tri[index].Teleport(old_pos);
}
