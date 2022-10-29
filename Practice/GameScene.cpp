#include "pch.h"
#include "Figure.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

enum
{
	NONE = 0,
	BASE = 0,
	SPINDLE,
	LEFT,
	RIGHT,
	MAX
};

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{ 0 },
	_grid{},
	_sub_object{},
	_stop_animation{ false },
	_radius{ 0.f }
{
	_grid.push_back(new Line{ vec3::zero(), vec3::x(100.f) });
	_grid.push_back(new Line{ vec3::zero(), vec3::y(100.f) });
	_grid.push_back(new Line{ vec3::zero(), vec3::z(100.f) });

	_object.push_back(new Cube{});
	_object.back()->Scale(glm::vec3{ 1.f, 0.3f, 1.f });
	_object.back()->Move(vec3::up(0.25f));
	
	_object.push_back(new Cube{});
	_object.back()->Scale(glm::vec3{ 0.5f, 0.2f, 0.5f });
	_object.back()->Move(vec3::up(0.5f));

	_object.push_back(new Cylinder{});
	_object.back()->Scale(glm::vec3{ 0.07f });
	_object.back()->Move(glm::vec3{ -0.1f, 0.74f, 0.f });

	_object.push_back(new Cylinder{});
	_object.back()->Scale(glm::vec3{ 0.07f });
	_object.back()->Move(glm::vec3{ 0.1f, 0.74f, 0.f });

	_sub_object.push_back(new Rect{});
	_sub_object.back()->Scale(glm::vec3{ 10.f });
	_sub_object.back()->RotateX(-90.f);

	//_camera->Move(3.f, 3.f, 5.f - 1.f);

	_radius = 3.f - 1.f;
	_camera->Move(0.f, 0.5f, _radius);
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

		glm::vec3 color{ RAND_COLOR };
		obj->GetShader()->SetVec3("f_color", glm::value_ptr(color));
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
		case 'B': FALLTHROUGH
		case 'b': FALLTHROUGH
		case 'M': FALLTHROUGH
		case 'm': FALLTHROUGH
		case 'T': FALLTHROUGH
		case 't':
		{
			_stop_animation = false;
			glutTimerFunc(20, Engine::OnAnimate, key);
		}
		break;
		case 'Y': FALLTHROUGH
		case 'y':
		{
			Revolve();
		}
		break;
		case 'R': FALLTHROUGH
		case 'r':
		{

		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{

		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			_stop_animation = true;
		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{
		}
		break;
		default:
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
			_radius = _camera->GetPos().z;
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			_camera->Move(vec3::right(0.1f));
			_radius = _camera->GetPos().z;
		}
		break;
		case GLUT_KEY_UP:
		{
			_camera->Move(vec3::front(0.1f));
			_radius = _camera->GetPos().z;
		}
		break;
		case GLUT_KEY_DOWN:
		{
			_camera->Move(vec3::back(0.1f));
			_radius = _camera->GetPos().z;
		}
		break;
		case GLUT_KEY_PAGE_UP:
		{
			_camera->Move(vec3::up(0.1f));
			_radius = _camera->GetPos().z;
		}
		break;
		case GLUT_KEY_PAGE_DOWN:
		{
			_camera->Move(vec3::down(0.1f));
			_radius = _camera->GetPos().z;
		}
		break;
		case GLUT_KEY_HOME:
		{
			_camera->Zoom(1.f);
		}
		break;
		case GLUT_KEY_END:
		{
			_camera->Zoom(-1.f);
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

	for (auto& obj : _object)
	{
		auto shader{ obj->GetShader() };

		shader->Use();
		obj->BindVAO();

		obj->Transform();
		CameraMgr::ViewTransform(shader);
		CameraMgr::ProjectionTransform(shader);

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}

	for (auto& obj : _sub_object)
	{
		auto shader{ obj->GetShader() };

		shader->Use();
		obj->BindVAO();

		obj->Transform();
		CameraMgr::ViewTransform(shader);
		CameraMgr::ProjectionTransform(shader);

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::Revolve()
{
	static float d = 0.1f;
	d += 0.1f;

	float x{ std::sin(d) * _radius };
	float z{ std::cos(d) * _radius };

	_camera->SetPos(x, _camera->GetPos().y, z);
}

void GameScene::OnAnimate(int32_t value)
{


	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
