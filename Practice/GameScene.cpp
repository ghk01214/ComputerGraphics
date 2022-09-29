#include "pch.h"
#include "GameScene.h"

extern Window window;

GameScene::GameScene() :
	_tri{},
	_index{}
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
		tri.Load();
	}
}

void GameScene::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
	float x2{ Convert::ToFloat(x) / (window.width / 2) - 1.f };
	float y2{ 1.f - Convert::ToFloat(y) / (window.height / 2) };

	if (button == GL_LEFT)
	{
		_tri[_index++].Teleport(glm::vec3{ x2, y2, 0.f });
	}
}

void GameScene::OnRender()
{
	Scene::OnRender();

	for (auto& tri : _tri)
	{
		tri.BindVAO();
		glDrawElements(GL_TRIANGLES, tri.GetIndexNum(), GL_UNSIGNED_INT, 0);
	}
}
