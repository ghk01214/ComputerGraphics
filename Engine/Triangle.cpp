#include "pch.h"
#include "Triangle.h"

extern std::uniform_real_distribution<float> uid_color;

Triangle::Triangle(glm::vec3 pos)
{
	std::vector<float> vertex
	{
		0.5f, -0.5f, 0.f,
		0.f, 1.f, 0.f,
		-0.5f, -0.5f, 0.f
	};

	float rand_color{ uid_color(dre) };
	float rand_color2{ uid_color(dre) };
	float rand_color3{ uid_color(dre) };

	std::vector<uint32_t> index
	{
		0, 1, 2
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetIndex(&index);

	Move(pos);
}

Triangle::~Triangle()
{
}
