#include "pch.h"
#include "Object.h"

Object::Object() :
	_mesh{ std::make_shared<Mesh>() },
	_material{ std::make_shared<Material>() },
	_shader{ _material->GetShader() },
	_pos{ vec3::zero() },
	_angle{ vec3::zero() },
	_model{ mat4::unit() },
	_transform{}
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
	_mesh->CreateVertex(_shader);
}

void Object::Transform()
{
	for (auto iter = _transform.rbegin(); iter != _transform.rend(); ++iter)
	{
		_model *= *iter;
	}

	_transform.clear();

	_shader->SetMat4("model", glm::value_ptr(_model));
}

void Object::Move(float x, float y, float z)
{
	Move(glm::vec3{ x, y, z });
}

void Object::Move(glm::vec3 delta)
{
	_pos += delta;

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
	//_angle.z += delta;
	//
	//_transform.push_back(glm::rotate(mat4::unit(), glm::radians(delta), vec3::z()));
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
	glm::vec3 temp{};
	temp.x = x - _pos.x;
	temp.y = y - _pos.y;
	temp.z = z - _pos.z;

	glm::mat4 temp_mat{ glm::translate(_model, temp) };
	_transform.push_back(temp_mat);

	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
}

void Object::Teleport(glm::vec3 pos)
{
	Teleport(pos.x, pos.y, pos.z);
}
