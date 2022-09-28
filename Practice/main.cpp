#include "pch.h"
#include "GameScene.h"
#include "SceneMgr.h"
#include "Engine.h"

int main(int32_t argc, char** argv)
{
	glutInit(&argc, argv);

	Engine engine;
	Window window{ 800, 800, true };

	engine.Init(&window);

	std::shared_ptr<GameScene> scene{ std::make_shared<GameScene>() };
	engine.GetSceneMgr()->AddScene(SCENE_TYPE::GAME, &*scene);
	engine.GetSceneMgr()->ChangeScene(SCENE_TYPE::GAME);

	engine.Update();
}