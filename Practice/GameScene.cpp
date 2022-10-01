#include "pch.h"
#include "CameraMgr.h"
#include "Triangle.h"
#include "GameScene.h"

extern Window window;

GameScene::GameScene() :
	_tri{},
	_index{},
	_camera{}
{
	_tri.emplace_back(glm::vec3{ -0.5f, 0.5f, 0.f });
	_tri.emplace_back(glm::vec3{ 0.5f, 0.5f, 0.f });
	_tri.emplace_back(glm::vec3{ 0.5f, -0.5f, 0.f });
	_tri.emplace_back(glm::vec3{ -0.5f, -0.5f, 0.f });
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	for (auto& tri : _tri)
	{
		tri.OnLoad();
	}
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GLUT_LEFT_BUTTON)
	{
		if (_index >= _tri.size())
			_index = 0;

		_tri[_index++].Teleport(x2, y2, 0.f);
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& tri : _tri)
	{
		tri.BindVAO();

		tri.Transform();
		CameraMgr::ViewTransform(tri.GetShader());
		CameraMgr::ProjectionTransform(tri.GetShader());

		glDrawElements(GL_TRIANGLES, tri.GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}
