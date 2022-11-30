#include "pch.h"
#include "Shader.h"
#include "Figure.h"
#include "Camera.h"
#include "GameScene.h"
#include "Engine.h"

extern Engine engine;

GameScene::GameScene() :
#pragma region [BASE ATTRIBUTE]
	_camera{ std::make_unique<Camera>(glm::vec3{ 0.f, 0.f, 5.f }) },
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
	_light_pos{ vec3::back(3.f) }
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

	_rect.push_back(new Cube{});
	_rect.back()->SetShader(_light_shader);
	_rect.back()->ApplyLight();
	_rect.back()->SetObjectColor(WHITE, 1.f);

	_rect.back()->CreateTexture("rgb.jpg");

	_sky.push_back(new Skybox{});
	_sky.back()->SetShader(_skybox_shader);
	_sky.back()->ApplyLight();
	_sky.back()->SetObjectColor(WHITE, 1.f);

	std::vector<std::string> path
	{
		"rgba.jpg",
		"rgba.jpg",
		"rgba.jpg",
		"rgba.jpg",
		"rgba.jpg",
		"rgba.jpg"
	};

	_sky.back()->CreateSkybox(&path);

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
	LoadObject(&_rect, _light_shader);
	LoadObject(&_sky, _skybox_shader);
}

void GameScene::OnRelease()
{
	ReleaseObject(&_rect);
	ReleaseObject(&_sky);
}

void GameScene::OnIdleMessage()
{
	CalculateDeltaTime();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
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
	glClearColor(GRAY, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Render(&_rect, _light_shader);
	RenderSkybox(&_sky, _skybox_shader);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void GameScene::ViewProjection(std::shared_ptr<Shader>& shader)
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
}

void GameScene::Render(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
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
		obj->TurnOffLight();
		obj->SetLightPos(_light_pos);
		obj->ApplyTexture();

		glDrawElements(obj->GetDrawType(), obj->GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}

void GameScene::RenderSkybox(std::vector<Object*>* object, std::shared_ptr<Shader>& shader)
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
