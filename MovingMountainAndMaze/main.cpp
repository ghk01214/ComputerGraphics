#include "pch.h"
#include "MazeScene.h"
#include <Engine.h>

Window window{ 800, 800, true };
Engine engine;

int32_t main(int32_t argc, char** argv)
{
	int32_t size{};
	
	do
	{
		std::cout << std::format("Size : ");
		std::cin >> size;

		if (size < 5)
		{
			std::cout << std::format("Set the size of maze greater than 5(click any key to continue)");
			std::system("pause");
			std::system("cls");
		}
		else if (size > 25)
		{
			std::cout << std::format("Set the size of maze less than 25(click any key to continue)");
			std::system("pause");
			std::system("cls");
		}
	} while (size < 5 or size > 25);
	
	glutInit(&argc, argv);

	engine.Init(&window);

	std::shared_ptr<MazeScene> scene{ std::make_shared<MazeScene>(size) };
	engine.GetSceneMgr()->AddScene(SCENE_TYPE::GAME, &*scene);
	engine.GetSceneMgr()->ChangeScene(SCENE_TYPE::GAME);

	engine.Update();
}