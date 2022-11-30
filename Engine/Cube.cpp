#include "pch.h"
#include "Cube.h"
#include "Rect.h"

Cube::Cube(glm::vec3 pos) :
	D3{ "../Dependencies/model/cube.obj", pos }
{
}

Cube::~Cube()
{
}

Skybox::Skybox(glm::vec3 pos)
{
	// 바깥에서 볼 때 반시계
	std::vector<float> vertex
	{
		1.f, -1.f, -1.f,
		1.f, 1.f, -1.f,
		-1.f, 1.f, -1.f,
		-1.f, -1.f, -1.f,
		
		1.f, -1.f, 1.f,
		1.f, 1.f, 1.f,
		-1.f, 1.f, 1.f,
		-1.f, -1.f, 1.f,
		
		-1.f, 1.f, -1.f,
		-1.f, -1.f, -1.f,
		-1.f, -1.f, 1.f,
		-1.f, 1.f, 1.f,
		
		1.f, -1.f, 1.f,
		1.f, -1.f, -1.f,
		1.f, 1.f, -1.f,
		1.f, 1.f, 1.f,
		
		1.f, 1.f, 1.f,
		1.f, 1.f, -1.f,
		-1.f, 1.f, -1.f,
		-1.f, 1.f, 1.f,

		1.f, -1.f, 1.f,
		-1.f, -1.f, 1.f,
		-1.f, -1.f, -1.f,
		1.f, -1.f, -1.f,
	};

	std::vector<uint32_t> index
	{
		0, 3, 2,
		0, 2, 1,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetIndex(&index);

	Move(pos);
}

Skybox::~Skybox()
{
}
