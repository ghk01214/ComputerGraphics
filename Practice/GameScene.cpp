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
	_stop_animation{ false },
	_origin_pos(2, vec3::zero()),
	_count{ 0 }
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
	// x, y : 우측 도형 자전
	// g, b : 좌측 도형 자전
	// t : y축 공전
	// c : 도형 변경
	// r : 초기화
	// +, - : 원점 기준 확대, 축소
	// wasdfv : 좌측 도형 이동
	// ijkl;/ : 우측 도형 이동
	// h : 원점 이동 후 복귀
	// n : 서로의 자리로 이동 후 복귀
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
		case 'g':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 1);
		}
		break;
		case 'G':
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
		case 't':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 10);
		}
		break;
		case 'T':
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
		case 'R': FALLTHROUGH
		case 'r':
		{
			_stop_animation = true;
			_count = 0;

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
		case '+':
		{
			for (auto& obj : _object)
			{
				obj->Scale(1.2f, 1.2f, 1.2f);
			}
		}
		break;
		case '-':
		{
			for (auto& obj : _object)
			{
				obj->Scale(0.8f, 0.8f, 0.8f);
			}
		}
		break;
		case 'W': FALLTHROUGH
		case 'w':
		{
			_object[1]->Move(vec3::front(0.5f));
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			_object[1]->Move(vec3::back(0.5f));
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			_object[1]->Move(vec3::left(0.5f));
		}
		break;
		case 'D': FALLTHROUGH
		case 'd':
		{
			_object[1]->Move(vec3::right(0.5f));
		}
		break;
		case 'F': FALLTHROUGH
		case 'f':
		{
			_object[1]->Move(vec3::up(0.5f));
		}
		break;
		case 'V': FALLTHROUGH
		case 'v':
		{
			_object[1]->Move(vec3::down(0.5f));
		}
		break;
		case 'I': FALLTHROUGH
		case 'i':
		{
			_object[0]->Move(vec3::front(0.5f));
		}
		break;
		case 'K': FALLTHROUGH
		case 'k':
		{
			_object[0]->Move(vec3::back(0.5f));
		}
		break;
		case 'J': FALLTHROUGH
		case 'j':
		{
			_object[0]->Move(vec3::left(0.5f));
		}
		break;
		case 'L': FALLTHROUGH
		case 'l':
		{
			_object[0]->Move(vec3::right(0.5f));
		}
		break;
		case ';':
		{
			_object[0]->Move(vec3::up(0.5f));
		}
		break;
		case '/':
		{
			_object[0]->Move(vec3::down(0.5f));
		}
		break;
		case 'H': FALLTHROUGH
		case 'h':
		{
			_stop_animation = false;

			for (int32_t i = 0; i < _object.size(); ++i)
			{
				_origin_pos[i] = _object[i]->GetPos();
			}

			glutTimerFunc(10, Engine::OnAnimate, 20);
		}
		break;
		case 'N': FALLTHROUGH
		case 'n':
		{
			_stop_animation = false;

			for (int32_t i = 0; i < _object.size(); ++i)
			{
				_origin_pos[i] = _object[i]->GetPos();
			}

			glutTimerFunc(10, Engine::OnAnimate, 40);
		}
		break;
		default:
		break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	// 상하좌우 : 전체 도형 xz 평면 이동
	// PAGE UP, DOWN : 제자리 확대, 축소
	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::left(0.5f));
			}
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::right(0.5f));
			}
		}
		break;
		case GLUT_KEY_UP:
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::front(0.5f));
			}
		}
		break;
		case GLUT_KEY_DOWN:
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::back(0.5f));
			}
		}
		break;
		case GLUT_KEY_PAGE_UP:
		{
			auto pos{ _object[0]->GetPos() };
			_object[0]->Move(-pos);
			_object[0]->Scale(1.2f, 1.2f, 1.2f);
			_object[0]->Move(pos);
			
			pos = _object[1]->GetPos();
			_object[1]->Move(-pos);
			_object[1]->Scale(1.2f, 1.2f, 1.2f);
			_object[1]->Move(pos);
		}
		break;
		case GLUT_KEY_PAGE_DOWN:
		{
			auto pos{ _object[0]->GetPos() };
			_object[0]->Move(-pos);
			_object[0]->Scale(0.8f, 0.8f, 0.8f);
			_object[0]->Move(pos);

			pos = _object[1]->GetPos();
			_object[1]->Move(-pos);
			_object[1]->Scale(0.8f, 0.8f, 0.8f);
			_object[1]->Move(pos);
		}
		break;
		default:
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
	else if (value == 20 or value == 40)
	{
		for (int32_t i = 0; i < _object.size(); ++i)
		{
			auto o_pos{ _origin_pos[i] };
			auto pos{ _object[i]->GetPos() };

			// 왜 이렇게 됐을까...
			if (_count == value * 10)
			{
				value = -value;
				break;
			}

			++_count;
			_object[i]->Move(-(_origin_pos[i] / 100));
		}
	}
	else if (value == -20 or value == -40)
	{
		for (int32_t i = 0; i < _object.size(); ++i)
		{
			auto o_pos{ _origin_pos[i] };
			auto pos{ _object[i]->GetPos() };

			if (_count == 0)
			{
				value = -value;
				break;
			}

			--_count;
			_object[i]->Move(_origin_pos[i] / 100);
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
