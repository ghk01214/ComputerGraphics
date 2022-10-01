#include "pch.h"
#include "DebugScene.h"

DebugScene::DebugScene() :
	_tri{},
	_rect{}
{
}

DebugScene::~DebugScene()
{
}

void DebugScene::OnLoad()
{
	//_tri.OnLoad();
	_rect.OnLoad();
}

void DebugScene::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
}

void DebugScene::OnRender()
{
	Scene::OnRender();

	//_tri.BindVAO();
	_rect.BindVAO();

	glDrawElements(GL_TRIANGLES, _rect.GetIndexNum(), GL_UNSIGNED_INT, 0);
}
