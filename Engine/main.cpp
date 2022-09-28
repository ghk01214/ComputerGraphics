#include "pch.h"
#include "DebugScene.h"
#include "SceneMgr.h"
#include "Engine.h"

int main(int32_t argc, char** argv)
{
	glutInit(&argc, argv);

	Engine engine;
	Window window{ 800, 800, true };

	engine.Init(&window);

	std::shared_ptr<DebugScene> scene{ std::make_shared<DebugScene>() };
	engine.GetSceneMgr()->AddScene(SCENE_TYPE::START, &*scene);
	engine.GetSceneMgr()->ChangeScene(SCENE_TYPE::START);

	engine.Update();
}