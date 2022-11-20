#include "pch.h"
#include "Shader.h"
#include "Figure.h"
#include "Camera.h"
#include "GameScene.h"
#include "Engine.h"

extern Engine engine;

GameScene::GameScene() :
#pragma region [BASE ATTRIBUTE]
	_camera{ std::make_unique<Camera>(glm::vec3{ 5.f, 5.f, 5.f }, vec3::up(), -35.f, -90.f - 45.f) },
	_color_shader{ std::make_shared<Shader>() },
	_light_shader{ std::make_shared<Shader>() },
	_object{ nullptr },
	_stop_animation{ true },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_old_time{ glutGet(GLUT_ELAPSED_TIME) },
#pragma endregion
	_grid{},
	_cube{},
	_pyramid{},
	_light{},
	_orbit{},
	_draw_cube{ true },
	_turn_on{ true }
{
#if _DEBUG
	_color_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Color.glsl");
	_light_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Light.glsl");
#else
	_2d->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Fragment.glsl");
	_3d->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Color.glsl");
#endif

	_object = &_cube;

	CreateGrid();
	CreateCube();
	CreatePyramid();
	CreateLight();
	CreateOrbit();
}

GameScene::~GameScene()
{
	OnRelease();
}

void GameScene::OnLoad()
{
	LoadObject(&_grid, _color_shader);
	LoadObject(&_cube, _light_shader);
	LoadObject(&_pyramid, _light_shader);
	LoadObject(&_light, _color_shader);
	LoadObject(&_orbit, _color_shader);
}

void GameScene::OnRelease()
{
	ReleaseObject(&_grid);
	ReleaseObject(&_cube);
	ReleaseObject(&_pyramid);
	ReleaseObject(&_light);
	ReleaseObject(&_orbit);
}

void GameScene::LoadObject(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
{
	for (auto& obj : *object)
	{
		obj->OnLoad(shader);
	}
}

void GameScene::ReleaseObject(std::vector<Object*>* object)
{
	for (auto& obj : *object)
	{
		delete obj;
		obj = nullptr;
	}
}

void GameScene::OnIdleMessage()
{
	int32_t time{ glutGet(GLUT_ELAPSED_TIME) };

	_delta_time = Convert::ToFloat((time - _old_time)) / 1000.f;
	_old_time = time;
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'N': FALLTHROUGH
		case 'n':
		{
			ChangeObject();
		}
		break;
		case 'M': FALLTHROUGH
		case 'm':
		{
			ChangeLightState();
		}
		break;
		case 'Y': FALLTHROUGH
		case 'y':
		{
			RotateObject();
		}
		break;
		case 'R':
		{
			RotateLight(-1);
		}
		break;
		case 'r':
		{
			RotateLight(1);
		}
		break;
		case 'Z':
		{
			MoveLight(1);
		}
		break;
		case 'z':
		{
			MoveLight(-1);
		}
		break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	_camera->OnSpecialKeyMessage(key, x, y, 0.1f);
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (engine.GetWindowWidth() / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (engine.GetWindowHeight() / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		_click = true;
	}
}

void GameScene::OnMouseMotionMessage(int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (engine.GetWindowWidth() / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (engine.GetWindowHeight() / 2) };

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
	glClearColor(BLACK, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Render2D(&_grid, _color_shader);
	Render3D(_object, _light_shader);
	Render2D(&_light, _color_shader);
	Render2D(&_orbit, _color_shader);
}

void GameScene::ViewProjection(std::shared_ptr<Shader>& shader)
{
	auto view{ _camera->GetViewMatrix() };
	auto projection{ _camera->GetProjectionMatrix() };

	shader->SetMat4("view", &view);
	shader->SetMat4("projection", &projection);
}

void GameScene::CreateGrid()
{
	_grid.push_back(new Line{ vec3::zero(), vec3::x(100.f) });
	_grid.back()->SetShader(_color_shader);
	_grid.back()->SetColor(RED);

	_grid.push_back(new Line{ vec3::zero(), vec3::y(100.f) });
	_grid.back()->SetShader(_color_shader);
	_grid.back()->SetColor(GREEN);

	_grid.push_back(new Line{ vec3::zero(), vec3::z(100.f) });
	_grid.back()->SetShader(_color_shader);
	_grid.back()->SetColor(BLUE);
}

void GameScene::CreateCube()
{
	_cube.push_back(new Cube{});
	_cube.back()->SetShader(_light_shader);
	_cube.back()->Scale(glm::vec3{ 1.5f });
	_cube.back()->SetLight(0.3f, 0.5f, 128, vec3::back(2.f), vec3::unit());
	_cube.back()->SetColor(RAND_COLOR);
}

void GameScene::CreatePyramid()
{
	_pyramid.push_back(new Pyramid{});
	_pyramid.back()->SetShader(_light_shader);
	_pyramid.back()->Scale(glm::vec3{ 1.5f });
	_pyramid.back()->SetLight(0.3f, 0.5f, 128, vec3::back(2.f), vec3::unit());
	_pyramid.back()->SetColor(RAND_COLOR);
}

void GameScene::CreateLight()
{
	_light.push_back(new Cube{});
	_light.back()->SetShader(_color_shader);
	_light.back()->Scale(glm::vec3{ 0.2f });
	_light.back()->Move(vec3::back(2.f));
	_light.back()->SetColor(WHITE);
}

void GameScene::CreateOrbit()
{
	_orbit.push_back(new Circle{});
	_orbit.back()->SetShader(_color_shader);
	//_orbit.back()->Scale(glm::vec3{ 10.f });
	_orbit.back()->RotateX(-90.f);
	_orbit.back()->SetColor(GREEN);
}

void GameScene::ChangeObject()
{
	_draw_cube = !_draw_cube;

	if (_draw_cube == true)
		_object = &_cube;
	else
		_object = &_pyramid;
}

void GameScene::ChangeLightState()
{
	//for (auto& obj : *_object)
	//{
	//	obj->ChangeLightState();
	//}
	_turn_on = !_turn_on;
}

void GameScene::RotateObject()
{
	for (auto& obj : *_object)
	{
		obj->RotateY(1.f);
	}
}

void GameScene::RotateLight(int32_t direction)
{
	for (auto& light : _light)
	{
		light->RotateY(1.f * direction);
	}
	// 왜 얘는 안 되지?
	//_light->Transform(_color_shader);

	//auto pos{ _light->GetPos() };

	//for (auto& obj : *_object)
	//{
	//	obj->SetLightPos(pos);
	//}
}

void GameScene::MoveLight(int32_t delta)
{
	for (auto& light : _light)
	{
		light->Move(delta * light->GetPos() * glm::vec3{ 0.1f });
	}
}

void GameScene::Render(Object* obj, std::shared_ptr<Shader>& shader)
{
	obj->BindVAO();

	obj->Transform(shader);
	ViewProjection(shader);

	obj->ApplyColor();
	obj->SetLightPos(_light.back()->GetPos());

	glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
}

void GameScene::Render2D(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
{
	shader->OnUse();

	for (auto& obj : *object)
	{
		Render(obj, shader);
	}
}

void GameScene::Render3D(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
{
	glm::vec3 view_pos{ _camera->GetPos() };
	shader->SetVec3("view_pos", &view_pos);

	shader->OnUse();

	for (auto& obj : *object)
	{
		if (_turn_on == true)
			obj->TurnOnLight();
		else
			obj->TurnOffLight();

		Render(obj, shader);
	}
}

void GameScene::OnAnimate(int32_t value)
{
	if (_stop_animation == false)
		glutTimerFunc(10, Engine::OnAnimate, value);
}
