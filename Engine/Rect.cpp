#include "pch.h"
#include "Rect.h"

Rect::Rect(glm::vec3 pos, glm::vec3 size)
{
	std::vector<float> vertex
	{
		 size.x,  -size.y, 0.f,
		 size.x, size.y, 0.f,
		 -size.x, size.y, 0.f,
		 -size.x, -size.y, 0.f,
	};

	std::vector<float> color
	{
		RED, 1.f,
		GREEN, 1.f,
		BLUE, 1.f,
		RAND_COLOR, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 2,
		0, 2, 3
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);

	Move(pos);
}

Rect::~Rect()
{
}
