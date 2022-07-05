#include "stdafx.h"
#include "pch.h"
#include "Renderer.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	std::unique_ptr<Renderer> renderer{ std::make_unique<Renderer>() };

	renderer->Run();
}