#include "pch.h"
#include "Rect.h"

Rect::Rect() :
	_vertex
	{
		glm::vec3{ 0.5f, -0.5f, 0.f },
		glm::vec3{ 0.5f, 0.5f, 0.f },
		glm::vec3{ -0.5f, 0.5f, 0.f },
		glm::vec3{ -0.5f, -0.5f, 0.f }
	}
{
	_draw_type = GL_LINE_LOOP;

	_pos = glm::vec3{ 0.f, 0.f, 0.f };

	std::vector<float> vertex =
	{
		_vertex[0].x, _vertex[0].y, _vertex[0].z,
		_vertex[1].x, _vertex[1].y, _vertex[1].z,
		_vertex[2].x, _vertex[2].y, _vertex[2].z,
		_vertex[3].x, _vertex[3].y, _vertex[3].z
	};

	std::vector<float> color
	{
		RED, 1.f,
		GREEN, 1.f,
		BLUE, 1.f,
		RAND_COLOR, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 2, 3
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Rect::Rect(glm::vec3 pos) :
	_vertex
	{
		glm::vec3{ pos.x + 0.5f, pos.y + -0.5f, 0.f },
		glm::vec3{ pos.x + 0.5f, pos.y + 0.5f, 0.f },
		glm::vec3{ pos.x + -0.5f, pos.y + 0.5f, 0.f },
		glm::vec3{ pos.x + -0.5f, pos.y + -0.5f, 0.f }
	}
{
	_draw_type = GL_LINE_LOOP;

	std::vector<float> vertex =
	{
		_vertex[0].x, _vertex[0].y, _vertex[0].z,
		_vertex[1].x, _vertex[1].y, _vertex[1].z,
		_vertex[2].x, _vertex[2].y, _vertex[2].z,
		_vertex[3].x, _vertex[3].y, _vertex[3].z,
	};

	std::vector<float> color
	{
		RED, 1.f,
		GREEN, 1.f,
		BLUE, 1.f,
		RAND_COLOR, 1.f,
	};

	std::vector<uint32_t> index
	{
		0, 1, 2, 3
	};

	_mesh->SetVertex(&vertex);
	_mesh->SetColor(&color);
	_mesh->SetIndex(&index);
}

Rect::~Rect()
{
}

void Rect::SetVertex(int32_t index, glm::vec3 pos)
{
	_vertex[index] = pos;

	std::vector<float> vertex =
	{
		_vertex[0].x, _vertex[0].y, _vertex[0].z,
		_vertex[1].x, _vertex[1].y, _vertex[1].z,
		_vertex[2].x, _vertex[2].y, _vertex[2].z,
		_vertex[3].x, _vertex[3].y, _vertex[3].z,
	};

	_mesh->SetVertex(&vertex);
}

void Rect::SetVertex(glm::vec3 pos)
{
	//TODO: 수식 수정
	std::cout << pos.x << ", " << pos.y << std::endl;
	for (auto& ver : _vertex)
	{
		std::cout << ver.x << ", " << ver.y << std::endl;
		ver += pos;
	}
	std::cout << std::endl;
	std::vector<float> vertex =
	{
		_vertex[0].x, _vertex[0].y, _vertex[0].z,
		_vertex[1].x, _vertex[1].y, _vertex[1].z,
		_vertex[2].x, _vertex[2].y, _vertex[2].z,
		_vertex[3].x, _vertex[3].y, _vertex[3].z,
	};

	_mesh->SetVertex(&vertex);
}
