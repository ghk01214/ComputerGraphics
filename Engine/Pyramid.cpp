﻿#include "pch.h"
#include "Pyramid.h"

Pyramid::Pyramid(glm::vec3 pos)
{
	_pos = pos;

	std::vector<float> vertex
	{
		pos.x + 0.f, pos.y + 0.5f, pos.z + 0.f,
		pos.x + 0.5f, pos.y + (-0.5f), pos.z + 0.5f,
		pos.x + 0.5f, pos.y + (-0.5f), pos.z + (-0.5f),
		pos.x + (-0.5f), pos.y + (-0.5f), pos.z + (-0.5f),
		pos.x + (-0.5f), pos.y + (-0.5f), pos.z + 0.5f
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
