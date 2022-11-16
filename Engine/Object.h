#pragma once

// NOTE :
// 월드 상에 그려지는 모든 object들의 기본이 되는 object class
// 

#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

class Object
{
public:
	Object();
	Object(glm::vec3 pos);
	virtual ~Object();

	virtual void OnLoad();
	void OnRelease();

	void Transform(std::shared_ptr<Shader>& shader);
	
	virtual void Move(float x, float y, float z);
	virtual void Move(glm::vec3 delta);
	virtual void RotateX(float delta);
	virtual void RotateY(float delta);
	virtual void RotateZ(float delta);
	virtual void Scale(float x, float y, float z);
	virtual void Scale(glm::vec3 delta);

	void BindVAO() { _mesh->BindVAO(); }
	void BindIndex() { _mesh->BindIndex(); }

	virtual bool Collide(Object* obj, int32_t direction) { return false; }

	std::shared_ptr<Mesh> GetMesh() { return _mesh; }
	std::shared_ptr<Shader> GetShader() { return _shader; }
	size_t GetIndexNum() { return _mesh->GetIndexNum(); }
	glm::vec3 GetPos() { return _pos = _model[3]; }
	glm::vec3 GetAngle() { return _angle; }
	glm::vec3 GetColor() { return _color; }
	uint32_t GetDrawType() { return _draw_type; }
	glm::mat4 GetModel() { return _model; }
	
	void SetShader(std::shared_ptr<Shader>& shader) { _shader = shader; }
	void SetModelMat(glm::mat4 model) { _model = model; }
	void SetPos(glm::vec3 pos) { _pos = pos; }
	void SetPos(float x, float y, float z) { SetPos(glm::vec3{ x, y, z }); }
	void SetColor(glm::vec3 color) { _color = color; }
	void SetColor(float x, float y, float z) { SetColor(glm::vec3(x, y, z)); }
	void SetDrawType(uint32_t type) { _draw_type = type; }
	void SetIndex(std::vector<uint32_t>* index) { _mesh->SetIndex(index); }

protected:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Shader> _shader;

	glm::vec3 _pos;
	glm::vec3 _angle;
	glm::vec3 _color;

	glm::mat4 _model;
	std::list<glm::mat4> _transform;

	uint32_t _draw_type;
};
