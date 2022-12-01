#include "pch.h"
#include "Shader.h"
#include "Figure.h"
#include "Camera.h"
#include "GameScene.h"
#include "Engine.h"

extern Engine engine;

GameScene::GameScene() :
#pragma region [BASE ATTRIBUTE]
	_camera{ std::make_unique<Camera>(glm::vec3{ 0.f, 3.f, 7.f }, -90.f, -30.f) },
	_color_shader{ std::make_shared<Shader>() },
	_light_shader{ std::make_shared<Shader>() },
	_skybox_shader{ std::make_shared<Shader>() },
	_stop_animation{ true },
	_click{ false },
	_old_x{ 0 },
	_old_y{ 0 },
	_time{ 0 },
	_old_time{ 0 },
#pragma endregion
	_light_pos{ glm::vec3{ 0.f, 1.f, 3.f } },
	_apply_light{ true }
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

	CreateCrane();
	CreatePlane();
	CreateLight();

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
	LoadObject(&_crane, _light_shader);
	LoadObject(&_plane, _light_shader);
	LoadObject(&_light, _light_shader);
}

void GameScene::OnRelease()
{
	ReleaseObject(&_crane);
	ReleaseObject(&_plane);
	ReleaseObject(&_light);
}

void GameScene::OnIdleMessage()
{
	CalculateDeltaTime();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
	switch (key)
	{
		case 'M': FALLTHROUGH
		case 'm':
		{
			_apply_light = !_apply_light;
		}
		break;
		case 'C': FALLTHROUGH
		case 'c':
		{
			ChangeLightColor();
		}
		break;
		case 'R':
		{
			_stop_animation = true;

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			_stop_animation = false;

			glutTimerFunc(10, Engine::OnAnimate, 1);
		}
		break;
		case 'r':
		{
			_stop_animation = true;

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			_stop_animation = false;

			glutTimerFunc(10, Engine::OnAnimate, -1);
		}
		break;
		case 'B': FALLTHROUGH
		case 'b':
		{
			_stop_animation = true;
		}
		break;
		case 'W': FALLTHROUGH
		case 'w':
		{
			MoveCrane(vec3::front(0.1f));
		}
		break;
		case 'A': FALLTHROUGH
		case 'a':
		{
			MoveCrane(vec3::left(0.1f));
		}
		break;
		case 'S': FALLTHROUGH
		case 's':
		{
			MoveCrane(vec3::back(0.1f));
		}
		break;
		case 'D': FALLTHROUGH
		case 'd':
		{
			MoveCrane(vec3::right(0.1f));
		}
		break;
		case 'G': FALLTHROUGH
		case 'g':
		{
			RotateCamera();
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
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Render(&_crane, _light_shader, true);
	Render(&_plane, _light_shader, true);
	Render(&_light, _light_shader, false);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void GameScene::ViewProjection(std::shared_ptr<Shader>&shader)
{
	auto view{ _camera->GetViewMatrix() };
	auto projection{ _camera->GetProjectionMatrix() };

	shader->SetMat4("view", &view);
	shader->SetMat4("projection", &projection);
}

void GameScene::OnAnimate(int32_t value)
{
	if (_stop_animation == false)
	{
		RotateLight(value);

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

void GameScene::LoadObject(std::vector<Object*>*object, std::shared_ptr<Shader>&shader)
{
	for (auto& obj : *object)
	{
		obj->OnLoad(shader);
	}
}

void GameScene::ReleaseObject(std::vector<Object*>*object)
{
	for (auto& obj : *object)
	{
		delete obj;
		obj = nullptr;
	}
}

void GameScene::Render(std::vector<Object*>*object, std::shared_ptr<Shader>&shader, bool apply_light)
{
	glm::vec3 view_pos{ _camera->GetPos() };
	shader->SetVec3("view_pos", &view_pos);

	shader->OnUse();
	ViewProjection(shader);

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
		}

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::RenderSkybox(std::vector<Object*>*object, std::shared_ptr<Shader>&shader)
{
	glDepthFunc(GL_LEQUAL);

	shader->OnUse();
	ViewProjection(shader);

	for (auto& obj : *object)
	{
		obj->BindVAO();

		obj->ApplySkybox();

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}

	glDepthFunc(GL_LESS);
}

void GameScene::CreateCrane()
{
	_crane.push_back(new Cube{});
	_crane.back()->Scale(glm::vec3{ 1.f, 0.3f, 1.f });
	_crane.back()->Move(vec3::up(0.15f));

	_crane.push_back(new Cube{});
	_crane.back()->Scale(glm::vec3{ 0.5f, 0.2f, 0.5f });
	_crane.back()->Move(vec3::up(0.35f));

	_crane.push_back(new Cylinder{});
	_crane.back()->Scale(glm::vec3{ 0.07f });
	_crane.back()->Move(glm::vec3{ -0.1f, 0.59f, 0.f });

	_crane.push_back(new Cylinder{});
	_crane.back()->Scale(glm::vec3{ 0.07f });
	_crane.back()->Move(glm::vec3{ 0.1f, 0.59f, 0.f });

	for (auto& obj : _crane)
	{
		obj->SetShader(_light_shader);
		obj->SetLightPos(_light_pos);
		obj->SetObjectColor(RAND_COLOR, 1.f);
	}
}

void GameScene::CreatePlane()
{
	_plane.push_back(new Cube{});
	_plane.back()->Scale(glm::vec3{ 10.f });
	_plane.back()->Move(vec3::down(5.f));

	_plane.back()->SetShader(_light_shader);
	_plane.back()->SetObjectColor(RAND_COLOR, 1.f);
	_plane.back()->SetLightPos(_light_pos);
}

void GameScene::CreateLight()
{
	_light.push_back(new Sphere{});
	_light.back()->Scale(glm::vec3{ 0.005f });
	_light.back()->Move(_light_pos);
	_light.back()->SetShader(_light_shader);
	_light.back()->SetObjectColor(WHITE, 1.f);
}

void GameScene::MoveCrane(glm::vec3 direction)
{
	for (auto& obj : _crane)
	{
		obj->Move(direction);
	}
}

void GameScene::RotateCamera()
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

void GameScene::ChangeLightColor()
{
	glm::vec3 color{ RAND_COLOR };

	for (auto& obj : _crane)
	{
		obj->SetLightColor(color);
	}

	for (auto& obj : _plane)
	{
		obj->SetLightColor(color);
	}

	for (auto& obj : _light)
	{
		obj->SetObjectColor(glm::vec4{ color, 1.f });
	}
}

void GameScene::RotateLight(int32_t direction)
{
	for (auto& obj : _light)
	{
		obj->RotateY(1.f * direction);
		_light_pos = obj->GetPos();
	}
}
