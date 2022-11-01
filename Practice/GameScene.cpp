#include "pch.h"
#include "Figure.h"
#include "Camera.h"
#include "GameScene.h"
#include "Engine.h"

extern Window window;

enum
{
	NONE = 0,
	BASE = 0,
	CENTER ,
	LEFT_ARM,
	RIGHT_ARM,
	MAX
};

GameScene::GameScene() :
	_camera{ std::make_unique<Camera>(glm::vec3{0.f, 0.5f, 3.f}, vec3::up(), 0.f, -90.f) },
	//_camera{ std::make_unique<Camera>(glm::vec3{0.f, 5.f, 0.f}, vec3::up(), -90.f, 90.f) },
	_object{},
	_grid{},
	_sub_object{},
	_stop_animation{ false },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_rotate_base{ false },
	_rotate_center{ false },
	_rotate_arm{ false },
	_rotate_camera{ false }
{
	//_grid.push_back(new Line{ vec3::zero(), vec3::x(100.f) });
	//_grid.push_back(new Line{ vec3::zero(), vec3::y(100.f) });
	//_grid.push_back(new Line{ vec3::zero(), vec3::z(100.f) });

	_object.push_back(new Cube{});
	_object.back()->Scale(glm::vec3{ 1.f, 0.3f, 1.f });
	_object.back()->Move(vec3::up(0.15f));
	
	_object.push_back(new Cube{});
	_object.back()->Scale(glm::vec3{ 0.5f, 0.2f, 0.5f });
	_object.back()->Move(vec3::up(0.35f));

	_object.push_back(new Cylinder{});
	_object.back()->Scale(glm::vec3{ 0.07f });
	_object.back()->Move(glm::vec3{ -0.1f, 0.59f, 0.f });

	_object.push_back(new Cylinder{});
	_object.back()->Scale(glm::vec3{ 0.07f });
	_object.back()->Move(glm::vec3{ 0.1f, 0.59f, 0.f });

	_sub_object.push_back(new Rect{});
	_sub_object.back()->Scale(glm::vec3{ 10.f });
	_sub_object.back()->RotateX(-90.f);
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
	//for (auto& line : _grid)
	//{
	//	line->OnLoad();
	//}

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
	static int32_t direction{ 1 };

	switch (key)
	{
		case 'B': FALLTHROUGH
		case 'b': FALLTHROUGH
		{
			_stop_animation = false;
			_rotate_base = !_rotate_base;
			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case 'M': FALLTHROUGH
		case 'm': FALLTHROUGH
		{
			_stop_animation = false;
			_rotate_center = !_rotate_center;
			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case 'T': FALLTHROUGH
		case 't':
		{
			_stop_animation = false;
			_rotate_arm = !_rotate_arm;
			glutTimerFunc(10, Engine::OnAnimate, key);
		}
		break;
		case 'Y':
		{
			direction = -1;
			_camera->RotateY(direction);
		}
		break;
		case 'y':
		{
			direction = 1;
			_camera->RotateY(direction);
		}
		break;
		case 'R': FALLTHROUGH
		case 'r':
		{
			Orbit();
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			_stop_animation = false;
			_rotate_camera = !_rotate_camera;
			glutTimerFunc(10, Engine::OnAnimate, key);
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
			_stop_animation = true;
			_rotate_base = false;
			_rotate_center = false;
			_rotate_camera = false;
			_rotate_arm = false;
			_click = false;

			_object.clear();
			_sub_object.clear();

			_object.reserve(4);
			_sub_object.reserve(1);

			_camera = std::make_unique<Camera>(glm::vec3{0.f, 0.5f, 3.f}, vec3::up(), 0.f, -90.f);
			
			_object.push_back(new Cube{});
			_object.back()->Scale(glm::vec3{ 1.f, 0.3f, 1.f });
			_object.back()->Move(vec3::up(0.15f));

			_object.push_back(new Cube{});
			_object.back()->Scale(glm::vec3{ 0.5f, 0.2f, 0.5f });
			_object.back()->Move(vec3::up(0.35f));

			_object.push_back(new Cylinder{});
			_object.back()->Scale(glm::vec3{ 0.07f });
			_object.back()->Move(glm::vec3{ -0.1f, 0.59f, 0.f });

			_object.push_back(new Cylinder{});
			_object.back()->Scale(glm::vec3{ 0.07f });
			_object.back()->Move(glm::vec3{ 0.1f, 0.59f, 0.f });

			_sub_object.push_back(new Rect{});
			_sub_object.back()->Scale(glm::vec3{ 10.f });
			_sub_object.back()->RotateX(-90.f);

			OnLoad();
		}
		break;
		default:
		break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	_camera->OnSpecialKeyMessage(key, x, y, 0.1f);
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		_click = true;
	}
}

void GameScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (_click)
	{
		_old_x = x;
		_old_y = y;
		_click = false;
	}

	float delta_x{ Convert::ToFloat(x - _old_x) };
	float delta_y{ Convert::ToFloat(_old_y - y) };
	_old_x = x;
	_old_y = y;

	_camera->OnMouseMotionMessage(delta_x, delta_y);
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
	//	ViewProjection(shader);

	//	glDrawElements(line->GetDrawType(), line->GetIndexNum(), GL_UNSIGNED_INT, 0);
	//}

	for (auto& obj : _object)
	{
		auto shader{ obj->GetShader() };

		shader->Use();
		obj->BindVAO();

		obj->Transform();
		ViewProjection(shader);

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}

	for (auto& obj : _sub_object)
	{
		auto shader{ obj->GetShader() };

		shader->Use();
		obj->BindVAO();

		obj->Transform();
		ViewProjection(shader);

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::ViewProjection(std::shared_ptr<Shader>& shader)
{
	auto view{ _camera->GetViewMatrix() };
	auto projection{ _camera->GetProjectionMatrix() };

	shader->SetMat4("view", glm::value_ptr(view));
	shader->SetMat4("projection", glm::value_ptr(projection));
}

void GameScene::RotateBase()
{
	auto obj{ _object[BASE] };
	auto pos{ obj->GetPos() };
	
	obj->Move(-pos);
	obj->RotateY(1.f);
	obj->Move(pos);
}

void GameScene::RotateCenter()
{
	auto obj{ _object[CENTER] };
	auto pos{ obj->GetPos() };

	obj->Move(-pos);
	obj->RotateY(1.f);
	obj->Move(pos);
}

void GameScene::RotateArm()
{
	static bool rotate{ true };
	static float angle{ 1.f };
	auto left{ _object[LEFT_ARM] };
	auto l_pos{ left->GetPos() };

	auto right{ _object[RIGHT_ARM] };
	auto r_pos{ right->GetPos() };

	if (left->GetAngle().x > 90.f and rotate == true)
	{
		rotate = false;
		angle = -angle;
	}
	else if (left->GetAngle().x < -90.f and rotate == false)
	{
		rotate = true;
		angle = -angle;
	}
	
	left->Move(-glm::vec3{ -0.1f, 0.59f, 0.f });
	left->Move(vec3::up(0.14f));
	left->RotateX(angle);
	left->Move(vec3::down(0.14f));
	left->Move(glm::vec3{ -0.1f, 0.59f, 0.f });

	right->Move(-glm::vec3{ 0.1f, 0.59f, 0.f });
	right->Move(vec3::up(0.14f));
	right->RotateX(-angle);
	right->Move(vec3::down(0.14f));
	right->Move(glm::vec3{ 0.1f, 0.59f, 0.f });
}

void GameScene::Orbit()
{
	static float angle{ 0.f };
	static auto pos{ _camera->GetPos() };
	float radius{ Convert::ToFloat(std::sqrt((pos.x * pos.x) + (pos.z * pos.z))) };
	float x{ std::sin(angle) * radius };
	float z{ std::cos(angle) * radius };

	_camera->RotateY(1.f);
	_camera->SetPos(x, pos.y, z);
	angle -= 0.0175f;
}

void GameScene::OnAnimate(int32_t value)
{
	switch (value)
	{
		case 'B': FALLTHROUGH
		case 'b':
		{
			RotateBase();
		}
		break;
		case 'M': FALLTHROUGH
		case 'm':
		{
			RotateCenter();
		}
		break;
		case 'T': FALLTHROUGH
		case 't':
		{
			RotateArm();
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			Orbit();
		}
		break;
	}

	if (_stop_animation == false)
	{
		if (_rotate_base == true or
			_rotate_center == true or
			_rotate_arm == true or
			_rotate_camera == true)
			glutTimerFunc(10, Engine::OnAnimate, value);
	}
}
