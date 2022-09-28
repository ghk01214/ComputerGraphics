#include "pch.h"
#include "Object.h"

Object::Object() :
	_mesh{ std::make_unique<Mesh>() },
	_material{ std::make_unique<Material>() },
	_pos{ vec3::zero() },
	_angle{ vec3::zero() }
{
}

Object::~Object()
{
}
