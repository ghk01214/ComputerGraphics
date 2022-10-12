#include "pch.h"
#include "Triangle.h"

extern std::uniform_real_distribution<float> uid_color;

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

Triangle::Triangle(glm::vec3 pos, bool reverse)
{
	_pos = pos;
	std::vector<float> vertex;

	if (reverse == false)
	{
		vertex =
		{
			_pos.x + 0.1f, _pos.y + (-0.1f), 0.f,
			_pos.x + 0.f, _pos.y + 0.2f, 0.f,
			_pos.x + (-0.1f), _pos.y + (-0.1f), 0.f
		};
	}
	else
	{
		vertex =
		{
			_pos.x - 0.1f, _pos.y + 0.1f, 0.f,
			_pos.x, _pos.y - 0.2f, 0.f,
			_pos.x + 0.1f, _pos.y + 0.1f, 0.f
		};

		_angle.z = -180.f;
	}

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

void Triangle::Move(glm::vec3 delta)
{
	_pos += delta;

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
	}

	_mesh->SetVertex(&vertex);
}

void Triangle::Move(float x, float y, float z)
{
	Move(glm::vec3{ x, y, z });
}

void Triangle::RotateZ(float delta)
{
	_angle.z += delta;
}

void Triangle::ChangeColor()
{
	float rand_color{ uid_color(dre) };
	float rand_color2{ uid_color(dre) };
	float rand_color3{ uid_color(dre) };

	std::vector<float> color
	{
		rand_color, rand_color2, rand_color3, 1.f,
		rand_color, rand_color2, rand_color3, 1.f,
		rand_color, rand_color2, rand_color3, 1.f,
	};

	_mesh->SetColor(&color);
}
