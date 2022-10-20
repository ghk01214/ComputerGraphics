#include "pch.h"
#include "Rect.h"

Rect::Rect(glm::vec3 pos, glm::vec3 size)
{
	std::vector<float> vertex;

	if (size.z == 0)
	{
		vertex =
		{
			 size.x,  -size.y, 0.f,
			 size.x, size.y, 0.f,
			 -size.x, size.y, 0.f,
			 -size.x, -size.y, 0.f,
		};
	}
	else if (size.y == 0)
	{
		vertex =
		{
			size.x, 0.f, -size.z,
			size.x, 0.f, size.z,
			-size.x, 0.f, size.z,
			-size.x, 0.f, -size.z,
		};
	}
	else if (size.x == 0)
	{
		vertex =
		{
			 0.f, -size.y, size.x,
			 0.f, size.y, size.x,
			 0.f, size.y, -size.x,
			 0.f, -size.y, -size.x,
		};
	}

	std::vector<float> color
	{
		RED, 1.f,
		GREEN, 1.f,
		BLUE, 1.f,
		RAND_COLOR, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 2, 3
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);

	Move(pos);
}

Rect::~Rect()
{
}
