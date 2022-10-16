#include "pch.h"
#include "Pyramid.h"

Pyramid::Pyramid()
{
	std::vector<float> vertex
	{
		0.f, 0.5f, 0.f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f
	};

	std::vector<float> color
	{
		BLACK, 1.f,
		RED, 1.f,
		GREEN, 1.f,
		BLUE, 1.f,
		WHITE, 1.f
	};

	std::vector<uint32_t> index
	{
		0, 4, 1,
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		1, 2, 4,
		2, 3, 4
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Pyramid::~Pyramid()
{
}
