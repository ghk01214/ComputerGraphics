#include "pch.h"
#include "Scene.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::AddScene(SCENE type, Scene scene)
{
	inst->_scene.insert(std::make_pair(type, scene));
}

void SceneMgr::OnIdleMessage()
{
}

void SceneMgr::OnKeyboardMessage(uchar key, int32_t x, int32_t y)
{
}

void SceneMgr::OnSpecialKeyMessage(int32_t key, int32_t x, int32_t y)
{
}

void SceneMgr::OnKeyboardUpMessage(uchar key, int32_t x, int32_t y)
{
}

void SceneMgr::OnSpecialKeyUpMessage(int32_t key, int32_t x, int32_t y)
{
}

void SceneMgr::OnMouseMessage(int32_t button, int32_t x, int32_t y)
{
}

void SceneMgr::OnMouseUpMessage(int32_t button, int32_t x, int32_t y)
{
}

void SceneMgr::OnMouseMotionMessage(int32_t x, int32_t y)
{
}

void SceneMgr::OnMousePassiveMotionMessage(int32_t x, int32_t y)
{
}

void SceneMgr::OnRender()
{
}
