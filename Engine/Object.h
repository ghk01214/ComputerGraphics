﻿#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void OnLoad();

	void Transform();
	
	virtual void Move(float x, float y, float z);
	virtual void Move(glm::vec3 delta);
	virtual void RotateX(float delta);
	virtual void RotateY(float delta);
	virtual void RotateZ(float delta);
	virtual void Scale(float x, float y, float z);
	virtual void Scale(glm::vec3 delta);

	virtual void Teleport(float x, float y, float z);
	virtual void Teleport(glm::vec3 pos);

	void BindVAO() { _mesh->BindVAO(); }

	std::shared_ptr<Shader> GetShader() { return _material->GetShader(); }
	size_t GetIndexNum() { return _mesh->GetIndexNum(); }
	glm::vec3 GetPos() { return _pos; }
	glm::vec3 GetAngle() { return _angle; }
	
	void SetModelMat(glm::mat4 model) { _model = model; }

public:
	friend std::hash<Object>;
	friend std::equal_to<Object>;

protected:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Shader> _shader;

	glm::vec3 _pos;
	glm::vec3 _angle;

	glm::mat4 _model;
	std::list<glm::mat4> _transform;
};

namespace std
{
	template<>
	class hash<Object>
	{
	public:
		size_t operator()(const Object& p) const
		{
			return std::hash<int32_t>()(reinterpret_cast<int32_t>(&*p._shader)) ^ p._shader->ID();
		}
	};

	template<>
	class equal_to<Object>
	{
	public:
		bool operator()(const Object& left, const Object& right) const
		{
			if (left._shader != right._shader)
				return false;

			return true;
		}
	};
}