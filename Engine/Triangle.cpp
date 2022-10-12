#include "pch.h"
#include "Triangle.h"

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

void Triangle::Move(float x, float y, float z)
{
	_pos.x += x;
	_pos.y += y;
	_pos.z += z;

	int32_t direction{ Convert::ToInt32(_angle.z / 90.f) };
	std::vector<float> vertex;

	switch (direction % 4)
	{
		case 0:
		{
			vertex =
			{
				_pos.x + 0.1f, _pos.y - 0.1f, 0.f,
				_pos.x, _pos.y + 0.2f, 0.f,
				_pos.x - 0.1f, _pos.y - 0.1f, 0.f
			};
		}
		break;
		case 1: FALLTHROUGH
		case -3:
		{
			vertex =
			{
				_pos.x + 0.1f, _pos.y + 0.1f, 0.f,
				_pos.x - 0.2f, _pos.y, 0.f,
				_pos.x + 0.1f, _pos.y - 0.1f, 0.f
			};
		}
		break;
		case 2: FALLTHROUGH
		case -2:
		{
			vertex =
			{
				_pos.x - 0.1f, _pos.y + 0.1f, 0.f,
				_pos.x, _pos.y - 0.2f, 0.f,
				_pos.x + 0.1f, _pos.y + 0.1f, 0.f
			};
		}
		break;
		case 3: FALLTHROUGH
		case -1:
		{
			vertex =
			{
				_pos.x - 0.1f, _pos.y - 0.1f, 0.f,
				_pos.x + 0.2f, _pos.y, 0.f,
				_pos.x - 0.1f, _pos.y + 0.1f, 0.f
			};
		}
		break;
	}

	_mesh->SetVertex(&vertex);
}

void Triangle::RotateZ(float delta)
{
	_angle.z += delta;
}
