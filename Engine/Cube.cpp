#include "pch.h"
#include "Cube.h"

Cube::Cube(glm::vec3 pos) :
	D3{ "../Dependencies/model/cube.obj", pos },
	_width{ 1.f },
	_height{ 1.f },
	_depth{ 1.f }
{
}

Cube::~Cube()
{
}

bool Cube::Collide(Object* object, int32_t direction)
{
	auto obj{ dynamic_cast<Cube*>(object) };
	auto obj_pos{ obj->GetPos() };
	float width, depth, height;

	switch (direction)
	{
		case 1: FALLTHROUGH
		case 2: // left or right
		{
			width = _width / 2;
			height = _height / 2;
			depth = _depth / 2;
		}
		break;
		case 3: FALLTHROUGH
		case 4: // front or back
		{
			width = _depth / 2;
			height = _height / 2;
			depth = _width / 2;
		}
		break;
	}

	auto left{ obj_pos.x - obj->GetWidth() / 2 };
	auto right{ obj_pos.x + obj->GetWidth() / 2 };
	auto top{ obj_pos.y + obj->GetHeight() / 2 };
	auto front{ obj_pos.z - obj->GetDepth() / 2 };
	auto back{ obj_pos.z + obj->GetDepth() / 2 };

	auto pos{ GetPos() };

	if (left < pos.x + width and pos.x + width < right)
	{
		if (front < pos.z + depth and pos.z + depth < back)
		{
			if (pos.y < top + height)
				return true;
		}
	}

	return false;
}

void Cube::SetScaleSize(float x, float y, float z)
{
	_width *= x;
	_height *= y;
	_depth *= z;
}
