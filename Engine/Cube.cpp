#include "pch.h"
#include "Cube.h"

Cube::Cube(glm::vec3 pos)
{
	_pos = pos;

	std::vector<float> vertex
	{
		pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f,
		pos.x + 0.5f, pos.y + (-0.5f), pos.z + 0.5f,
		pos.x + (-0.5f), pos.y + (-0.5f), pos.z + 0.5f,
		pos.x + (-0.5f), pos.y + 0.5f, pos.z + 0.5f,
		pos.x + 0.5f, pos.y + 0.5f, pos.z + (-0.5f),
		pos.x + 0.5f, pos.y + (-0.5f), pos.z + (-0.5f),
		pos.x + (-0.5f), pos.y + (-0.5f), pos.z + (-0.5f),
		pos.x + (-0.5f), pos.y + 0.5f, pos.z + (-0.5f),
	};

	std::vector<float> color
	{
		BLACK, 1.f,
		RED, 1.f,
		GREEN, 1.f,
		BLUE, 1.f,
		1.f, 1.f, 0.f, 1.f,
		1.f, 0.f, 1.f, 1.f,
		0.f, 1.f, 1.f, 1.f,
		WHITE, 1.f,
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
