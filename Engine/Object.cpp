#include "pch.h"
#include "Object.h"

Object::Object() :
	_mesh{ std::make_shared<Mesh>() },
	_material{ std::make_shared<Material>() },
	_pos{ vec3::zero() },
	_angle{ vec3::zero() }
{
}

Object::~Object()
{
}

glm::mat4 Object::Move(glm::vec3 delta)
{
	_pos += delta;

	return glm::translate(mat4::unit(), _pos);
}

glm::mat4 Object::RotateX(float delta)
{
	_angle.x += delta;

	return glm::rotate(mat4::unit(), glm::radians(_angle.x), vec3::right());
}

glm::mat4 Object::RotateY(float delta)
{
	_angle.y += delta;

	return glm::rotate(mat4::unit(), glm::radians(_angle.y), vec3::right());
}

glm::mat4 Object::RotateZ(float delta)
{
	_angle.z += delta;

	return glm::rotate(mat4::unit(), glm::radians(_angle.z), vec3::right());
}

glm::mat4 Object::Scale(glm::vec3 delta)
{
	return glm::mat4();
}
