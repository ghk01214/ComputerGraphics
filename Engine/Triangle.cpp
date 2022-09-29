#include "pch.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

std::uniform_real_distribution<float> uid_color{ 0.f, 1.f };

Triangle::Triangle()
{
	
}

Triangle::Triangle(glm::vec3 pos)
{
	_pos = pos;

	std::vector<float> vertex
	{
		_pos.x + 0.1f, _pos.y + (-0.1f), 0.f,
		_pos.x + 0.f, _pos.y + 0.2f, 0.f,
		_pos.x + (-0.1f), _pos.y + (-0.1f), 0.f
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

glm::mat4 Triangle::Teleport(glm::vec3 pos)
{
	_pos = pos;

	return glm::translate(mat4::unit(), _pos);
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
