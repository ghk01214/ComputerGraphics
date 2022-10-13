#include "pch.h"
#include "Line.h"

extern std::uniform_real_distribution<float> uid_color;

Line::Line()
{
	_draw_type = GL_LINES;

	std::vector<float> vertex
	{
		0.5f, 0.f, 0.f,
		-0.5f, 0.f, 0.f
	};
}

Line::Line(glm::vec3 pos, float length, bool horizontal)
{
	_draw_type = GL_LINES;
	std::vector<float> vertex;

	if (horizontal == true)
	{
		vertex =
		{
			pos.x + length, pos.y, pos.z,
			pos.x - length, pos.y, pos.z
		};
	}
	else
	{
		vertex =
		{
			pos.x, pos.y + length, pos.z,
			pos.x, pos.y - length, pos.z
		};
	}

	float random_color{ uid_color(dre) };
	float random_color2{ uid_color(dre) };
	float rand_color3{ uid_color(dre) };

	std::vector<float> color
	{
		random_color, random_color2, rand_color3, 1.f,
		random_color, random_color2, rand_color3, 1.f,
		random_color, random_color2, rand_color3, 1.f
	};

	std::vector<uint32_t> index
	{
		0, 1
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Line::~Line()
{
}
