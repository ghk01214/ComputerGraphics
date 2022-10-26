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
	_depth_test{ true },
	_show_cube{ true },
	_open_front{ false },
	_open_side(2, false),
	_open_pyramid{ false },
	_angle{ 0.f }
{
	_grid.push_back(new Line{ vec3::zero(), vec3::x(100.f) });
	_grid.push_back(new Line{ vec3::zero(), vec3::y(100.f) });
	_grid.push_back(new Line{ vec3::zero(), vec3::z(100.f) });
#pragma region [CUBE]
	_object.push_back(new Rect{});
	_object.back()->RotateY(90.f);
	_object.back()->Move(vec3::left(0.5f));

	_object.push_back(new Rect{});
	_object.back()->RotateY(-90.f);
	_object.back()->Move(vec3::right(0.5f));

	_object.push_back(new Rect{});
	_object.back()->RotateX(90.f);
	_object.back()->Move(vec3::up(0.5f));

	_object.push_back(new Rect{});
	_object.back()->RotateX(-90.f);
	_object.back()->Move(vec3::down(0.5f));

	_object.push_back(new Rect{});
	_object.back()->Move(vec3::front(0.5f));

	_object.push_back(new Rect{});
	_object.back()->Move(vec3::back(0.5f));
#pragma endregion
#pragma region [PYRAMID]
	_sub_object.push_back(new Rect{});
	_sub_object.back()->RotateX(90.f);
	_sub_object.back()->Move(vec3::down(0.5f));

	_sub_object.push_back(new Triangle{});
	_sub_object.back()->RotateY(90.f);
	_sub_object.back()->RotateZ(-19.5f);
	_sub_object.back()->Move(glm::vec3{ -0.333f, -0.028f, 0.f });

	_sub_object.push_back(new Triangle{});
	_sub_object.back()->RotateY(-90.f);
	_sub_object.back()->RotateZ(19.5f);
	_sub_object.back()->Move(glm::vec3{ 0.333f, -0.028f, 0.f });

	_sub_object.push_back(new Triangle{});
	_sub_object.back()->RotateX(19.5f);
	_sub_object.back()->Move(glm::vec3{ 0.f, -0.028f, -0.333f });

	_sub_object.push_back(new Triangle{});
	_sub_object.back()->RotateX(-19.5f);
	_sub_object.back()->Move(glm::vec3{ 0.f, -0.028f, 0.333f });
#pragma endregion
	_camera->SetDistance(0.1f, 50.f);
	_camera->Move(3.f, 3.f, 5.f - 1.f);
	//_camera->Move(0.f, 0.f, 3.f - 1.f);
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
		case 'H': FALLTHROUGH
		case 'h':
		_depth_test = !_depth_test;
		break;
		case 'Y': FALLTHROUGH
		case 'y': FALLTHROUGH
		case 'T': FALLTHROUGH
		case 't':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case 'F': FALLTHROUGH
		case 'f':
		{
			_open_front = true;
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case '1': FALLTHROUGH
		case '2':
		{
			for (auto side : _open_side)
			{
				side = true;
			}

			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case 'O': FALLTHROUGH
		case 'o':
		{
			if (_show_cube == false)
			{
				_open_pyramid = true;
				_stop_animation = false;
				glutTimerFunc(10, Engine::OnAnimate, key);
			}
		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{
			_stop_animation = true;
			_show_cube = !_show_cube;

			auto temp{ _object };
			_object = _sub_object;
			_sub_object = _object;
		}
		break;
		case 'P': FALLTHROUGH
		case 'p':
		_camera->ChangeProjection();
		break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			_camera->Move(vec3::left(0.1f));
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			_camera->Move(vec3::right(0.1f));
		}
		break;
		case GLUT_KEY_UP:
		{
			_camera->Move(vec3::front(0.1f));
		}
		break;
		case GLUT_KEY_DOWN:
		{
			_camera->Move(vec3::back(0.1f));
		}
		break;
		case GLUT_KEY_PAGE_UP:
		{
			_camera->Move(vec3::up(0.1f));
		}
		break;
		case GLUT_KEY_PAGE_DOWN:
		{
			_camera->Move(vec3::down(0.1f));
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

	_camera->OnMouseMotionMessage(x, y);
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
	if (_depth_test == true)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
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

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::RotateY(char key)
{
	for (auto& obj : _object)
	{
		if (key == 'y')
			obj->RotateY(1.f);
		else if (key == 'Y')
			obj->RotateY(-1.f);
	}
}

void GameScene::RotateTop(char key)
{
	auto obj{ _object[2] };
	auto pos{ _object[2]->GetPos() };

	obj->Move(-pos);
	if (key == 't')
		obj->RotateX(1.f);
	else if (key == 'T')
		obj->RotateX(-1.f);
	obj->Move(pos);
}

void GameScene::OpenFront()
{
	auto obj{ _object[5] };

	if (obj->GetAngle().x > 90.f and _open_front == true)
	{
		_open_front = false;
	}
	else if (obj->GetAngle().x < 0.f and _open_front == false)
	{
		_open_front = true;
	}

	obj->Move(vec3::front(0.5f));
	obj->Move(vec3::up(0.5f));
	if (_open_front == true)
		obj->RotateX(1.f);
	else
		obj->RotateX(-1.f);
	obj->Move(vec3::down(0.5f));
	obj->Move(vec3::back(0.5f));
}

void GameScene::OpenSide()
{
	for (int32_t i = 0; i < 2; ++i)
	{
		auto obj{ _object[i] };
		auto pos{ obj->GetPos() };

		if (pos.y > 0.98f and _open_side[i] == true)
			_open_side[i] = false;
		else if (pos.y < 0.02f and _open_side[i] == false)
			_open_side[i] = true;

		if (_open_side[i] == true)
			obj->Move(vec3::up(0.01f));
		else
			obj->Move(vec3::down(0.01f));
	}
}

void GameScene::OpenPyramid()
{
	static float delta{ 1.f };

	for (int32_t i = 1; i < _object.size(); ++i)
	{
		auto obj{ _object[i] };

		if (_angle > 180.f and _open_pyramid == true)
		{
			_open_pyramid = false;
			delta = -delta;
		}
		else if (_angle < 0.f and _open_pyramid == false)
		{
			_open_pyramid = true;
			delta = -delta;
		}

		if (i == 1)
		{
			obj->Move(-glm::vec3{ -0.333f, -0.028f, 0.f });
			obj->Move(vec3::up(0.5f));
			obj->RotateZ(delta);
			obj->Move(vec3::down(0.5f));
			obj->Move(glm::vec3{ -0.333f, -0.028f, 0.f });

			_angle += delta;
		}
		else if (i == 2)
		{
			obj->Move(-glm::vec3{ 0.333f, -0.028f, 0.f });
			obj->Move(vec3::up(0.5f));
			obj->RotateZ(-delta);
			obj->Move(vec3::down(0.5f));
			obj->Move(glm::vec3{ 0.333f, -0.028f, 0.f });
		}
		else if (i == 3)
		{
			obj->Move(-glm::vec3{ 0.f, -0.028f, -0.333f });
			obj->Move(vec3::up(0.5f));
			obj->RotateX(-delta);
			obj->Move(vec3::down(0.5f));
			obj->Move(glm::vec3{ 0.f, -0.028f, -0.333f });
		}
		else
		{
			obj->Move(-glm::vec3{ 0.f, -0.028f, 0.333f });
			obj->Move(vec3::up(0.5f));
			obj->RotateX(delta);
			obj->Move(vec3::down(0.5f));
			obj->Move(glm::vec3{ 0.f, -0.028f, 0.333f });
		}
	}
}

void GameScene::OnAnimate(int32_t value)
{
	switch (value)
	{
		case 'Y': FALLTHROUGH
		case 'y':
		RotateY(value);
		break;
		case 'T': FALLTHROUGH
		case 't':
		RotateTop(value);
		break;
		case 'F': FALLTHROUGH
		case 'f':
		OpenFront();
		break;
		case '1': FALLTHROUGH
		case '2':
		OpenSide();
		break;
		case 'O': FALLTHROUGH
		case 'o':
		OpenPyramid();
		break;
	}

	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
