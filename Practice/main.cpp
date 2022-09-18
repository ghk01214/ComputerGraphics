#include "pch.h"
#include "Engine.h"

int main(int32_t argc, char** argv)
{
	glutInit(&argc, argv);

	Engine engine;
	Window window{ 800, 600, true };

	engine.Init(&window);
	engine.Update();
}