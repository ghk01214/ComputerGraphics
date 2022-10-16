#include "pch.h"
#include "Line.h"

extern std::uniform_real_distribution<float> uid_color;

Line::Line(glm::vec3 pos, float length, bool horizontal)
{
	_draw_type = GL_LINES;
	_pos = pos;

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

	std::vector<float> color
	{
		BLACK, 1.f,
		BLACK, 1.f,
		BLACK, 1.f,
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
