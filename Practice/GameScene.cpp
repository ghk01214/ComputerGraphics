#include "pch.h"
#include "GameScene.h"

GameScene::GameScene() :
	_tri{},
	_rect{}
{
}

GameScene::~GameScene()
{
}

void GameScene::OnLoad()
{
	//_tri.Load();
	_rect.Load();
}

void GameScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
}

void GameScene::OnRender()
{
	Scene::OnRender();

	//_tri.BindVAO();
	_rect.BindVAO();

	glDrawElements(GL_TRIANGLES, _rect.GetIndexNum(), GL_UNSIGNED_INT, 0);
}
