#include "pch.h"
#include "GameScene.h"
#include "Engine.h"

Window window{ 800, 800, true };
Engine engine;

int main(int32_t argc, char** argv)
{
	glutInit(&argc, argv);


	engine.Init(&window);

	std::shared_ptr<GameScene> scene{ std::make_shared<GameScene>() };
	engine.GetSceneMgr()->AddScene(SCENE_TYPE::GAME, &*scene);
	engine.GetSceneMgr()->ChangeScene(SCENE_TYPE::GAME);

	engine.Update();
}