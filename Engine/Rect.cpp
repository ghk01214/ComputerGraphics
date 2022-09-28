#include "pch.h"
#include "Rect.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

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

void Rect::Load()
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
