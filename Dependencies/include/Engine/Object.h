#pragma once

#include "Mesh.h"
#include "Material.h"

class Shader;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Load() {}
	
	virtual glm::mat4 Move(glm::vec3 delta) { return mat4::zero(); }
	virtual glm::mat4 RotateX(float delta) { return mat4::zero(); }
	virtual glm::mat4 RotateY(float delta) { return mat4::zero(); }
	virtual glm::mat4 RotateZ(float delta) { return mat4::zero(); }
	virtual glm::mat4 Scale(glm::vec3 delta) { return mat4::zero(); }

	void BindVAO() { _mesh->BindVAO(); }

	std::shared_ptr<Shader> GetShader() { return _material->GetShader(); }
	size_t GetIndexNum() { return _mesh->GetIndexNum(); }

protected:
	std::unique_ptr<Mesh> _mesh;
	std::unique_ptr<Material> _material;

	glm::vec3 _pos;
	glm::vec3 _angle;
};
