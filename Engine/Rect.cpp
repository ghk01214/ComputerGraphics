#include "pch.h"
#include "Rect.h"

Rect::Rect(glm::vec3 pos, glm::vec3 size)
{
	std::vector<float> vertex
	{
		 size.x, -size.y, 0.f,
		 size.x, size.y, 0.f,
		 -size.x, size.y, 0.f,
		 -size.x, -size.y, 0.f,
	};

	glm::vec3 rand_color{ RAND_COLOR };

	std::vector<float> color
	{
		rand_color.r, rand_color.g, rand_color.b, 1.f,
		rand_color.r, rand_color.g, rand_color.b, 1.f,
		rand_color.r, rand_color.g, rand_color.b, 1.f,
		rand_color.r, rand_color.g, rand_color.b, 1.f
	};

	std::vector<uint32_t> index
	{
		0, 1, 2,
		0, 2, 3
	};

	std::vector<float> texture
	{
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f,
		0.f, 0.f
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetTexture(&texture);
	_mesh->SetIndex(&index);

	Move(pos);
}

Rect::~Rect()
{
}

void Rect::OnLoad(std::shared_ptr<Shader>& shader)
{
	Object::OnLoad(shader);

	_mesh->CreateVertex2(shader);
}
