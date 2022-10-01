#include "pch.h"
#include "Object.h"

Object::Object() :
	_mesh{ std::make_shared<Mesh>() },
	_material{ std::make_shared<Material>() },
	_shader{ _material->GetShader() },
	_pos{ vec3::zero() },
	_angle{ vec3::zero() },
	_model{ mat4::unit() }
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
	str += "../Dependencies/shader/Fragment.glsl ";
	str += std::to_string(GL_FRAGMENT_SHADER);
#else
	std::string str{ "2 " };
	str += "Dependencies/shader/Vertex.glsl ";
	str += std::to_string(GL_VERTEX_SHADER);
	str += "Dependencies/shader/Fragment.glsl ";
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

	_shader->SetMat4("model", _model);
}

void Object::Move(float x, float y, float z)
{
	_pos.x += x;
	_pos.y += y;
	_pos.z += z;

	_transform.push_back(glm::translate(mat4::unit(), _pos));
}

void Object::Move(glm::vec3 delta)
{
	Move(delta.x, delta.y, delta.z);
}

void Object::RotateX(float delta)
{
	_angle.x += delta;

	_transform.push_back(glm::rotate(mat4::unit(), glm::radians(_angle.x), vec3::right()));
}

void Object::RotateY(float delta)
{
	_angle.y += delta;

	_transform.push_back(glm::rotate(mat4::unit(), glm::radians(_angle.y), vec3::right()));
}

void Object::RotateZ(float delta)
{
	_angle.z += delta;

	_transform.push_back(glm::rotate(mat4::unit(), glm::radians(_angle.z), vec3::right()));
}

void Object::Scale(float x, float y, float z)
{
}

void Object::Scale(glm::vec3 delta)
{
	Scale(delta.x, delta.y, delta.z);
}

void Object::Teleport(float x, float y, float z)
{
	glm::vec3 temp{};
	temp.x = x - _pos.x;
	temp.y = y - _pos.y;
	temp.z = z - _pos.z;

	glm::mat4 new_pos{ glm::translate(mat4::unit(), temp) };
	_transform.push_back(new_pos);

	_pos.x += new_pos[3].x;
	_pos.y += new_pos[3].y;
	_pos.z += new_pos[3].z;
}

void Object::Teleport(glm::vec3 pos)
{
	Teleport(pos.x, pos.y, pos.z);
}
