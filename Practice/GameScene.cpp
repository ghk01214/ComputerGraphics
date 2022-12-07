#include "pch.h"
#include "Shader.h"
#include "Figure.h"
#include "Camera.h"
#include "GameScene.h"
#include "Engine.h"

using namespace std::chrono_literals;

extern Engine engine;

GameScene::GameScene() :
#pragma region [BASE ATTRIBUTE]
	_camera{ std::make_unique<Camera>(glm::vec3{ 3.f, 3.f, 3.f }, -90 - 45.f, -40.f) },
	_ui_camera{ std::make_unique<Camera>(vec3::back(3.f)) },
	_color_shader{ std::make_shared<Shader>() },
	_light_shader{ std::make_shared<Shader>() },
	_skybox_shader{ std::make_shared<Shader>() },
	_stop_animation{ true },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_time{ 0 },
	_old_time{ 0 },
	_wait_time{ 0.f },
	_light_pos{ glm::vec3{ 0.f, 0.f, 3.f } },
	_apply_light{ false },
	_apply_texture{ false },
#pragma endregion
	_skybox{},
	_grid{},
	_cube{},
	_pyramid{},
	_render_object{ nullptr }
{
#if _DEBUG
	_color_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Color.glsl");
	_light_shader->OnLoad("../Dependencies/shader/Vertex.glsl", "../Dependencies/shader/Light.glsl");
	_skybox_shader->OnLoad("../Dependencies/shader/Skybox_v.glsl", "../Dependencies/shader/Skybox_f.glsl");
#else
	_color_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Color.glsl");
	_light_shader->OnLoad("Data/Shader/Vertex.glsl", "Data/Shader/Light.glsl");
	_skybox_shader->OnLoad("Data/Shader/Skybox_v.glsl", "Data/Shader/Skybox_f.glsl");
#endif

	CreateSkybox();
	CreateGrid();
	CreateCube();
	CreatePyramid();

	_apply_texture = true;
	_render_object = &_cube;
	_ui_camera->SetCameraMode(false);

	_old_time = glutGet(GLUT_ELAPSED_TIME);
	CalculateDeltaTime();
}

GameScene::~GameScene()
{
	OnRelease();
}

#pragma region [PUBLIC]
void GameScene::OnLoad()
{
	LoadObject(&_skybox, _skybox_shader);
	LoadObject(&_grid, _light_shader);
	LoadObject(&_cube, _light_shader);
	LoadObject(&_pyramid, _light_shader);
}

void GameScene::OnRelease()
{
	ReleaseObject(&_skybox);
	ReleaseObject(&_grid);
	ReleaseObject(&_cube);
	ReleaseObject(&_pyramid);
}

void GameScene::OnIdleMessage()
{
	CalculateDeltaTime();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'C': FALLTHROUGH
		case 'c':
		{
			_render_object = &_cube;
		}
		break;
		case 'P': FALLTHROUGH
		case 'p':
		{
			_render_object = &_pyramid;
		}
		break;
		case 'X':
		{
			_stop_animation = true;

			std::this_thread::sleep_for(1ms);
			_stop_animation = false;

			glutTimerFunc(10, Engine::OnAnimate, 1);
		}
		break;
		case 'x':
		{
			_stop_animation = true;

			std::this_thread::sleep_for(1ms);
			_stop_animation = false;

			glutTimerFunc(10, Engine::OnAnimate, -1);
		}
		break;
		case 'Y':
		{
			_stop_animation = true;

			std::this_thread::sleep_for(1ms);
			_stop_animation = false;

			glutTimerFunc(10, Engine::OnAnimate, 2);
		}
		break;
		case 'y':
		{
			_stop_animation = true;

			std::this_thread::sleep_for(1ms);
			_stop_animation = false;

			glutTimerFunc(10, Engine::OnAnimate, -2);
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			Reset();
		}
		break;
	}
}

void GameScene::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
	if (_wait_time < 0.002f)
	{
		_wait_time += _delta_time;
		return;
	}

	_camera->OnSpecialKeyMessage(key, x, y, 0.1f);
	_wait_time = 0.f;
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
	glClearColor(GRAY, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderSkybox(&_skybox, _camera, _skybox_shader);
	Render(&_grid, _camera, _light_shader, false, false);
	Render(_render_object, _camera, _light_shader, _apply_light, _apply_texture);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void GameScene::ViewProjection(std::unique_ptr<Camera>& camera, std::shared_ptr<Shader>& shader)
{
	auto view{ camera->GetViewMatrix() };
	auto projection{ camera->GetProjectionMatrix() };

	shader->SetMat4("view", &view);
	shader->SetMat4("projection", &projection);
}

void GameScene::OnAnimate(int32_t value)
{
	if (_stop_animation == false)
	{
		if (abs(value) % 2 == 1)
			RotateX(value);
		else
			RotateY(value / 2);

		glutTimerFunc(10, Engine::OnAnimate, value);
	}
}
#pragma endregion

void GameScene::CalculateDeltaTime()
{
	_time = glutGet(GLUT_ELAPSED_TIME);

	_delta_time = Convert::ToFloat((_time - _old_time)) / 1000.f;
	_old_time = _time;
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

	object->clear();
}

void GameScene::Render(std::vector<Object*>* object, std::unique_ptr<Camera>& camera, std::shared_ptr<Shader>& shader, bool apply_light, bool apply_texture)
{
	glm::vec3 view_pos{ _camera->GetPos() };
	shader->SetVec3("view_pos", &view_pos);

	shader->OnUse();
	ViewProjection(camera, shader);

	for (auto& obj : *object)
	{
		obj->BindVAO();
		obj->Transform(shader);

		obj->ApplyColor();

		if (apply_light == true)
		{
			obj->ApplyLight();
			obj->SetLightPos(_light_pos);
		}
		else
		{
			obj->TurnOffLight();
			shader->SetBool("have_texture", false);
		}

		if (apply_texture)
			obj->ApplyTexture();

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::RenderSkybox(std::vector<Object*>* object, std::unique_ptr<Camera>& camera, std::shared_ptr<Shader>& shader)
{
	glDepthFunc(GL_LEQUAL);

	shader->OnUse();
	ViewProjection(camera, shader);

	for (auto& obj : *object)
	{
		obj->BindVAO();
		obj->ApplySkybox();

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}

	glDepthFunc(GL_LESS);
}

void GameScene::CreateGrid()
{
	_grid.resize(3, nullptr);

	// x축
	_grid[0] = new Line{};
	_grid[0]->SetShader(_light_shader);
	_grid[0]->SetObjectColor(RED, 1.f);

	// y축
	_grid[1] = new Line{};
	_grid[1]->RotateZ(90.f);
	_grid[1]->SetShader(_light_shader);
	_grid[1]->SetObjectColor(GREEN, 1.f);

	// z축
	_grid[2] = new Line{};
	_grid[2]->RotateY(90.f);
	_grid[2]->SetShader(_light_shader);
	_grid[2]->SetObjectColor(BLUE, 1.f);
}

void GameScene::CreateSkybox()
{
	_skybox.resize(6, nullptr);

	std::vector<std::string> path
	{
		"../Dependencies/texture/sky.jpg",
		"../Dependencies/texture/sky.jpg",
		"../Dependencies/texture/sky.jpg",
		"../Dependencies/texture/sky.jpg",
		"../Dependencies/texture/sky.jpg",
		"../Dependencies/texture/sky.jpg"
	};

	for (auto& obj : _skybox)
	{
		obj = new Rect{};
		obj->SetShader(_skybox_shader);
		obj->CreateSkybox(&path);
		//obj->CreateTexture("../Dependencies/texture/sky.jpg");
		obj->Scale(glm::vec3{ 10.f });
	}

	_apply_texture = true;
}

void GameScene::CreateCube()
{
	_cube.resize(6, nullptr);

	int32_t i{ 0 };
	for (auto& obj : _cube)
	{
		obj = new Rect{};
		obj->SetShader(_light_shader);
		obj->CreateTexture("../Dependencies/texture/" + std::to_string(++i) + ".png");
	}

	_apply_texture = true;

	_cube[0]->RotateY(-90.f);
	_cube[0]->Move(vec3::left(0.5f));

	_cube[1]->RotateY(90.f);
	_cube[1]->Move(vec3::right(0.5f));

	_cube[2]->RotateX(-90.f);
	_cube[2]->Move(vec3::up(0.5f));

	_cube[3]->RotateX(90.f);
	_cube[3]->Move(vec3::down(0.5f));

	_cube[4]->RotateY(180.f);
	_cube[4]->Move(vec3::front(0.5f));

	_cube[5]->Move(vec3::back(0.5f));
}

void GameScene::CreatePyramid()
{
	_pyramid.resize(5, nullptr);

	_pyramid[0] = new Rect{};
	_pyramid[0]->RotateX(90.f);
	_pyramid[0]->Move(vec3::down(0.233f));

	for (auto iter = ++_pyramid.begin(); iter != _pyramid.end(); ++iter)
	{
		(*iter) = new Triangle{};
	}

	_pyramid[1]->RotateY(-90.f);
	_pyramid[1]->RotateZ(-35.46f);
	_pyramid[1]->Move(vec3::left(0.333f));

	_pyramid[2]->RotateY(90.f);
	_pyramid[2]->RotateZ(35.46f);
	_pyramid[2]->Move(vec3::right(0.333f));

	_pyramid[3]->RotateY(180.f);
	_pyramid[3]->RotateX(35.46f);
	_pyramid[3]->Move(vec3::front(0.333f));

	_pyramid[4]->RotateX(-35.46f);
	_pyramid[4]->Move(vec3::back(0.333f));

	int32_t i{ 0 };
	for (auto& obj : _pyramid)
	{
		obj->SetShader(_light_shader);
		obj->CreateTexture("../Dependencies/texture/" + std::to_string(++i) + ".png");
		obj->SetObjectColor(RAND_COLOR, 1.f);
	}
}

void GameScene::RotateX(int32_t direction)
{
	for (auto& obj : *_render_object)
	{
		obj->RotateX(1.f * direction);
	}
}

void GameScene::RotateY(int32_t direction)
{
	for (auto& obj : *_render_object)
	{
		obj->RotateY(1.f * direction);
	}
}

void GameScene::Reset()
{
	OnRelease();

	_camera.reset();
	_stop_animation = true;
	_click = false;
	_old_x = 0;
	_old_y = 0;
	_time = 0;
	_old_time = 0;
	_wait_time = 0.f;
	_light_pos = glm::vec3{ 0.f, 0.f, 3.f };
	_apply_light = false;

	_camera = std::make_unique<Camera>(glm::vec3{ 3.f, 3.f, 3.f }, -90 - 45.f, -40.f);
	_ui_camera = std::make_unique<Camera>(vec3::back(3.f));
	_ui_camera->SetCameraMode(false);

	CreateSkybox();
	CreateGrid();
	CreateCube();
	CreatePyramid();

	_apply_texture = true;
	_render_object = &_cube;

	OnLoad();
}
