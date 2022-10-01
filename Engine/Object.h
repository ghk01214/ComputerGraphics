#pragma once

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

protected:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Shader> _shader;

	glm::vec3 _pos;
	glm::vec3 _angle;

	glm::mat4 _model;
	std::vector<glm::mat4> _transform;
};
