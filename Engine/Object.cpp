#include "pch.h"
#include "Object.h"

std::uniform_real_distribution<float> uid_color{ 0.f, 1.f };

Object::Object() :
	_mesh{ std::make_shared<Mesh>() },
	_material{ std::make_shared<Material>() },
	_pos{ vec3::zero() },
	_angle{ vec3::zero() },
	_model{ mat4::unit() },
	_transform{},
	_draw_type{ GL_TRIANGLES }
{
}

Object::Object(glm::vec3 pos) :
	_mesh{ std::make_shared<Mesh>() },
	_material{ std::make_shared<Material>() },
	_pos{ pos },
	_angle{ vec3::zero() },
	_model{ mat4::unit() },
	_transform{},
	_draw_type{ GL_TRIANGLES }
{
}

Object::~Object()
{
	OnRelease();
}

void Object::OnLoad(std::shared_ptr<Shader>& shader)
{
	_mesh->CreateBuffer();
}

void Object::OnRelease()
{
	_mesh->OnRelease();
}

void Object::Transform(std::shared_ptr<Shader>& shader)
{
	auto model{ mat4::unit() };

	for (auto iter = _transform.rbegin(); iter != _transform.rend(); ++iter)
	{
		model *= *iter;
	}

	_model = model * _model;

	_transform.clear();

	shader->SetMat4("model", &_model);
}

void Object::Move(float x, float y, float z)
{
	Move(glm::vec3{ x, y, z });
}

void Object::Move(glm::vec3 delta)
{
	_transform.push_back(glm::translate(mat4::unit(), delta));
}

void Object::RotateX(float delta)
{
	_angle.x += delta;

	_transform.push_back(glm::rotate(mat4::unit(), glm::radians(delta), vec3::x()));
}

void Object::RotateY(float delta)
{
	_angle.y += delta;

	_transform.push_back(glm::rotate(mat4::unit(), glm::radians(delta), vec3::y()));
}

void Object::RotateZ(float delta)
{
	_angle.z += delta;
	
	_transform.push_back(glm::rotate(mat4::unit(), glm::radians(delta), vec3::z()));
}

void Object::Scale(float x, float y, float z)
{
	Scale(glm::vec3{ x, y, z });
}

void Object::Scale(glm::vec3 delta)
{
	_transform.push_back(glm::scale(mat4::unit(), delta));
}
