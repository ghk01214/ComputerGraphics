#include "pch.h"
#include "Cube.h"

extern std::uniform_real_distribution<float> uid_color;

Cube::Cube()
{
	std::vector<float> vertex
	{
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
	};

	std::vector<float> color
	{
		0.f, 0.f, 0.f, 1.f,
		1.f, 0.f, 0.f, 1.f,
		0.f, 1.f, 0.f, 1.f,
		0.f, 0.f, 1.f, 1.f,
		1.f, 1.f, 0.f, 1.f,
		1.f, 0.f, 1.f, 1.f,
		0.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 3,
		1, 2, 3,
		0, 1, 4,
		1, 5, 4,
		4, 5, 7,
		5, 6, 7,
		7, 6, 3,
		6, 2, 3,
		0, 4, 3,
		4, 7, 3,
		1, 5, 2,
		5, 6, 2
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Cube::~Cube()
{
}
