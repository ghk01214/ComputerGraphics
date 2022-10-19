#include "pch.h"
#include "Object.h"

std::uniform_real_distribution<float> uid_color{ 0.f, 1.f };

Object::Object() :
	_mesh{ std::make_shared<Mesh>() },
	_material{ std::make_shared<Material>() },
	_shader{ _material->GetShader() },
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
	_shader{ _material->GetShader() },
	_pos{ pos },
	_angle{ vec3::zero() },
	_model{ mat4::unit() },
	_transform{},
	_draw_type{ GL_TRIANGLES }
{
}

Object::~Object()
{
}

void Object::OnLoad()
{
	_mesh->CreateBuffer();

#if _DEBUG
	std::string str{ "2 " };
	str += "../Dependencies/shader/Vertex.glsl ";
	str += std::to_string(GL_VERTEX_SHADER);
	str += " ../Dependencies/shader/Fragment.glsl ";
	str += std::to_string(GL_FRAGMENT_SHADER);
#else
	std::string str{ "2 " };
	str += "Dependencies/shader/Vertex.glsl ";
	str += std::to_string(GL_VERTEX_SHADER);
	str += " Dependencies/shader/Fragment.glsl ";
	str += std::to_string(GL_FRAGMENT_SHADER);
#endif

	_shader->Compile(str);
}

void Object::Transform()
{
	auto model{ mat4::unit() };

	for (auto iter = _transform.rbegin(); iter != _transform.rend(); ++iter)
	{
		model *= *iter;
	}

	_model = model * _model;

	_transform.clear();

	_shader->SetMat4("model", glm::value_ptr(_model));
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

void Object::Teleport(float x, float y, float z)
{
	Teleport(glm::vec3{ x, y, z });
}

void Object::Teleport(glm::vec3 pos)
{
	glm::vec3 temp{ pos - _pos };

	_transform.push_back(glm::translate(_model, temp));
}
