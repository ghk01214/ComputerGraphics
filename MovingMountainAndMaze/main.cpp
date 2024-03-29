﻿#include "pch.h"
#include "MazeScene.h"
#include <Engine.h>

Window window{ 1000, 800, true };
Engine engine;

int32_t main(int32_t argc, char** argv)
{
	int32_t width{};
	int32_t height{};
	
	do
	{
		std::cout << std::format("Width : ");
		std::cin >> width;
		std::cout << std::format("Height : ");
		std::cin >> height;

		if (width < 5 or height < 5)
		{
			std::cout << std::format("Set the size of maze greater than 5(click any key to continue)");
			std::system("pause");
			std::system("cls");

			std::cin.clear();
			std::cin.ignore();
		}
		else if (width > 25 or height > 25)
		{
			std::cout << std::format("Set the size of maze less than 25(click any key to continue)");
			std::system("pause");
			std::system("cls");

			std::cin.clear();
			std::cin.ignore();
		}
	} while (width < 5 or width > 25 or height < 5 or height > 25);
	
	glutInit(&argc, argv);

	engine.Init(&window);

	std::shared_ptr<MazeScene> scene{ std::make_shared<MazeScene>(width, height) };
	engine.GetSceneMgr()->AddScene(define::SCENE_TYPE::GAME, &*scene);
	engine.GetSceneMgr()->ChangeScene(define::SCENE_TYPE::GAME);

	engine.Update();
}