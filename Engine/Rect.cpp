#include "pch.h"
#include "Rect.h"

Rect::Rect()
{
	std::vector<float> vertex
	{
		0.5f, -0.5f, 0.f,
		0.5f, 0.5f, 0.f,
		-0.5f, 0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
	};

	std::vector<float> color
	{
		WHITE, 1.f,
		WHITE, 1.f,
		WHITE, 1.f,
		WHITE, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 3,
		1, 2, 3
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Rect::~Rect()
{
}
