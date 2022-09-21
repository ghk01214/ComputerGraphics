#include "pch.h"
#include "Engine.h"

int main(int32_t argc, char** argv)
{
	glutInit(&argc, argv);

	Engine engine;
	Window window{ 1280, 720, true };

	engine.Init(&window);
	engine.Update();
}