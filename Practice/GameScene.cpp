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

	_orbit.push_back(new Circle{});
	_orbit.push_back(new Circle{});
	_orbit.back()->RotateZ(-45.f);
	_orbit.push_back(new Circle{});
	_orbit.back()->RotateZ(45.f);

	for (auto& circle : _orbit)
	{
		circle->Scale(glm::vec3{ 2.5f });
	}

	_orbit.push_back(new Circle{});
	_orbit.push_back(new Circle{});
	_orbit.push_back(new Circle{});

	for (auto iter = _orbit.begin(); iter != _orbit.end(); ++iter)
	{
		if (iter == _orbit.begin())
			std::advance(iter, 3);

		(*iter)->Scale(glm::vec3{ 1.f });
		(*iter)->Move(vec3::back(2.5f));
	}

	_object.push_back(new Sphere{});
	_object.back()->Scale(glm::vec3{ 0.1f });

	_object.push_back(new Sphere{});
	_object.push_back(new Sphere{});
	_object.push_back(new Sphere{});

	for (auto iter = ++_object.begin(); iter != _object.end(); ++iter)
	{
		(*iter)->Scale(glm::vec3{ 0.05f });
		(*iter)->Move(vec3::back(2.5f));
	}

	_object.push_back(new Sphere{});
	_object.push_back(new Sphere{});
	_object.push_back(new Sphere{});

	for (auto iter = _object.begin(); iter != _object.end(); ++iter)
	{
		if (iter == _object.begin())
			std::advance(iter, 4);

		(*iter)->Scale(glm::vec3{ 0.01f });
		(*iter)->Move(vec3::back(1.f));
		(*iter)->RotateY(-90.f);
		(*iter)->Move(vec3::back(2.5f));
	}

	_camera->Move(3.f, 3.f, 5.f - 1.f);

	glutTimerFunc(10, Engine::OnAnimate, 1);
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

	for (auto& circle : _orbit)
	{
		circle->OnLoad();
	}

	for (auto& obj : _object)
	{
		obj->OnLoad();

		glm::vec3 color{ RAND_COLOR };
		obj->GetShader()->SetVec3("f_color", glm::value_ptr(color));	
		obj->ChangeDrawType(GL_LINE_LOOP);
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
		case 'P': FALLTHROUGH
		case 'p':
		{
			_camera->ChangeProjection();
		}
		break;
		case 'M':
		{
			for (auto& obj : _object)
			{
				obj->ChangeDrawType(GL_TRIANGLES);
			}
		}
		break;
		case 'm':
		{
			for (auto& obj : _object)
			{
				obj->ChangeDrawType(GL_LINE_LOOP);
			}
		}
		break;
		case 'W': FALLTHROUGH
		case 'w':
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::up(0.1f));
			}
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::left(0.1f));
			}
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::down(0.1f));
			}
		}
		break;
		case 'D': FALLTHROUGH
		case 'd':
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::right(0.1f));
			}
		}
		break;
		case 'Z': FALLTHROUGH
		case 'z':
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::back(0.1f));
			}
		}
		break;
		case 'X': FALLTHROUGH
		case 'x':
		{
			for (auto& obj : _object)
			{
				obj->Move(vec3::front(0.1f));
			}
		}
		break;
		case 'Y':
		{
			auto pos{ _object[0]->GetPos() };

			for (auto& obj : _object)
			{
				obj->Move(-pos);
				obj->RotateY(-2.f);
				obj->Move(pos);
			}
		}
		break;
		case 'y':
		{
			auto pos{ _object[0]->GetPos() };

			for (auto& obj : _object)
			{
				obj->Move(-pos);
				obj->RotateY(2.f);
				obj->Move(pos);
			}
		}
		break;
		default:
		break;
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

	//_camera->OnMouseMotionMessage(x, y);
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

	//for (auto& line : _grid)
	//{
	//	line->GetShader()->Use();
	//	line->BindVAO();

	//	line->Transform();
	//	CameraMgr::ViewTransform(line->GetShader());
	//	CameraMgr::ProjectionTransform(line->GetShader());

	//	glDrawElements(line->GetDrawType(), line->GetIndexNum(), GL_UNSIGNED_INT, 0);
	//}

	for (auto& circle : _orbit)
	{
		circle->GetShader()->Use();
		circle->BindVAO();

		circle->Transform();
		CameraMgr::ViewTransform(circle->GetShader());
		CameraMgr::ProjectionTransform(circle->GetShader());

		glDrawArrays(GL_LINE_STRIP, 0, 87);
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

	for (auto& obj : _sub_object)
	{
		obj->GetShader()->Use();
		obj->BindVAO();

		obj->Transform();
		CameraMgr::ViewTransform(obj->GetShader());
		CameraMgr::ProjectionTransform(obj->GetShader());

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::RotateInnerMoon()
{
	auto pos{ _object[0]->GetPos() };
	std::vector<float> angle;
	angle.reserve(3);
	angle.push_back(0.f);
	angle.push_back(0.5f);
	angle.push_back(-0.5f);

	for (int32_t i = 1; i < 4; ++i)
	{
		_object[i]->Move(-pos);
		_object[i]->RotateY(0.5f);
		_object[i]->RotateX(angle[i - 1]);
		_object[i]->Move(pos);
	}

	for (int32_t i = 3; i < _orbit.size(); ++i)
	{
		_orbit[i]->Move(-pos);
		_orbit[i]->RotateY(0.5f);
		//_orbit[i]->RotateX(angle[i - 3]);
		_orbit[i]->Move(pos);
	}
}

void GameScene::RotateOuterMoon()
{
	auto start{ _object[0]->GetPos() };
	std::vector<float> angle;
	angle.reserve(3);
	angle.push_back(0.f);
	angle.push_back(0.5f);
	angle.push_back(-0.5f);

	for (int32_t i = 4; i < _object.size(); ++i)
	{
		auto pos{ _object[i - 3]->GetPos() };

		_object[i]->Move(-start);
		_object[i]->Move(-pos);
		_object[i]->RotateY(0.5f);
		_object[i]->Move(pos);
		_object[i]->Move(start);

		_object[i]->RotateY(0.5f);
		_object[i]->RotateX(angle[i - 4]);
	}
}

void GameScene::OnAnimate(int32_t value)
{
	RotateInnerMoon();
	RotateOuterMoon();

	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
