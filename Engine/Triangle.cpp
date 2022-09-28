#include "pch.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

std::uniform_real_distribution<float> uid_color{ 0.f, 1.f };

Triangle::Triangle()
{
	std::vector<float> vertex
	{
		0.1f, -0.1f, 0.f,
		0.f, 0.2f, 0.f,
		-0.1f, -0.1f, 0.f
	};

	float rand_color{ uid_color(dre) };
	float rand_color2{ uid_color(dre) };
	float rand_color3{ uid_color(dre) };

	std::vector<float> color
	{
		rand_color, rand_color2, rand_color3, 1.f,
		rand_color, rand_color2, rand_color3, 1.f,
		rand_color, rand_color2, rand_color3, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 2
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Triangle::Triangle(float x, float y)
{
	std::vector<float> vertex
	{
		x + 0.1f, y + (-0.1f), 0.f,
		x + 0.f, y + 0.2f, 0.f,
		x + (-0.1f), y + (-0.1f), 0.f
	};

	float rand_color{ uid_color(dre) };
	float rand_color2{ uid_color(dre) };
	float rand_color3{ uid_color(dre) };

	std::vector<float> color
	{
		rand_color, rand_color2, rand_color3, 1.f,
		rand_color, rand_color2, rand_color3, 1.f,
		rand_color, rand_color2, rand_color3, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 2
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Triangle::~Triangle()
{
}

void Triangle::Load()
{
	_mesh->CreateBuffer();

	std::string str{ "2 " };
	str += "../Dependencies/shader/Vertex.glsl ";
	str += std::to_string(GL_VERTEX_SHADER);
	str += "../Dependencies/shader/Fragment.glsl ";
	str += std::to_string(GL_FRAGMENT_SHADER);

	_material->GetShader()->Compile(str);
	_mesh->CreateVertex(_material->GetShader());
}
