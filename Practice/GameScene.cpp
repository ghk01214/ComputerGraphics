#include "pch.h"
#include "Figure.h"
#include "CameraMgr.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

GameScene::GameScene() :
	_camera{},
	_object{},
	_index{ -1 },
	_hidden{ new Pyramid{} },
	_depth_test{ true },
	_solid_object{ true },
	_cube{ true },
	_stop_animation{ true }
{
	_object.push_back(new Line{ vec3::zero(), 5.f });
	_object.push_back(new Line{ vec3::zero(), 5.f, false });
	_object.push_back(new Cube{});

	_object.back()->RotateY(45.f);
	_object.back()->RotateX(30.f);

	_hidden->RotateY(45.f);
	_hidden->RotateX(30.f);
}

GameScene::~GameScene()
{
	for (auto& obj : _object)
	{
		delete obj;
	}

	delete _hidden;

	_object.clear();
}

void GameScene::OnLoad()
{
	for (auto& obj : _object)
	{
		obj->OnLoad();
	}

	_hidden->OnLoad();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'C': FALLTHROUGH
		case 'c':
		{
			if (_cube == false)
			{
				_cube = true;
				_stop_animation = true;

				auto change{ _hidden };
				_hidden = _object.back();

				*(--_object.end()) = change;
			}
		}
		break;
		case 'P': FALLTHROUGH
		case 'p':
		{
			if (_cube == true)
			{
				_cube = false;
				_stop_animation = true;

				auto change{ _hidden };
				_hidden = _object.back();

				*(--_object.end()) = change;
			}
		}
		break;
		case 'H': FALLTHROUGH
		case 'h':
		{
			_depth_test = !_depth_test;
		}
		break;
		case 'x':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 1);
		}
		break;
		case 'X':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -1);
		}
		break;
		case 'y':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, 2);
		}
		break;
		case 'Y':
		{
			_stop_animation = false;
			glutTimerFunc(10, Engine::OnAnimate, -2);
		}
		break;
		case 'W': FALLTHROUGH
		case 'w':
		{
			_solid_object = !_solid_object;

			if (_solid_object == true)
				_object.back()->ChangeDrawType(GL_TRIANGLES);
			else
				_object.back()->ChangeDrawType(GL_LINE_LOOP);
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			delete _object.back();

			_object.pop_back();

			if (_cube == true)
			{
				_object.push_back(new Cube{});
				_hidden = new Pyramid{};
			}
			else
			{
				_object.push_back(new Pyramid{});
				_hidden = new Cube{};
			}

			_object.back()->RotateY(45.f);
			_object.back()->RotateX(30.f);

			_object.back()->OnLoad();
			_hidden->OnLoad();

			_stop_animation = true;
		}
		break;
		case 'Q': FALLTHROUGH
		case 'q':
		break;
		default:
			std::cout << std::format("Keyboard default") << std::endl;
			break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			_object.back()->Move(glm::vec3{ -0.1f, 0.f, 0.f });
		}
		break;
		case GLUT_KEY_UP:
		{
			_object.back()->Move(glm::vec3{ 0.f, 0.1f, 0.f });
		}
		break;
		case GLUT_KEY_RIGHT:
		{
			_object.back()->Move(glm::vec3{ 0.1f, 0.f, 0.f });
		}
		break;
		case GLUT_KEY_DOWN:
		{
			_object.back()->Move(glm::vec3{ 0.f, -0.1f, 0.f });
		}
		break;
		default:
			std::cout << std::format("Special Key Debug") << std::endl;
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CW);

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

void GameScene::RotateX(int32_t direction)
{
	_object.back()->RotateX(direction * 1.0f);
}

void GameScene::RotateY(int32_t direction)
{
	_object.back()->RotateY(direction * 1.0f);
}

void GameScene::OnAnimate(int32_t value)
{
	if (value == 1 or value == -1)
		RotateX(value);
	else if (value == 2 or value == -2)
		RotateY(value / 2);

	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
