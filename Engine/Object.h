﻿#pragma once

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

	virtual void OnLoad(std::shared_ptr<Shader>& shader);
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

	void ApplyColor() { _material->ApplyColor(); }
	void ApplyLight() { _material->ApplyLight(); }
	void ApplyTexture() { _material->ApplyTexture(); }
	void ApplySkybox() { _material->ApplySkybox(); }
	void CreateTexture(const std::string& path, bool flip_vertical = true, bool flip_horizontal = false) { _material->CreateTexture(path, flip_vertical, flip_horizontal); }
	void CreateSkybox(const std::vector<std::string>* path, bool flip_vertical = true, bool flip_horizontal = false) { _material->CreateSkybox(path, flip_vertical, flip_horizontal); }
	void ChangeLightState() { _material->ChangeLightState(); }
	void TurnOnLight() { _material->TurnOnLight(); }
	void TurnOffLight() { _material->TurnOffLight(); }

	size_t GetIndexNum() { return _mesh->GetIndexNum(); }
	glm::vec3 GetPos() { return _pos = _model[3]; }
	glm::vec3 GetAngle() { return _angle; }
	glm::vec3 GetColor() { return _material->GetColor(); }
	uint32_t GetDrawType() { return _draw_type; }
	
	void SetPos(glm::vec3 pos) { _pos = pos; }
	void SetPos(float x, float y, float z) { SetPos(glm::vec3{ x, y, z }); }
	void SetObjectColor(glm::vec4 color) { _material->SetObjectColor(color); }
	void SetObjectColor(float r, float g, float b, float a) { SetObjectColor(glm::vec4{ r, g, b, a }); }
	void SetObjectAlpha(float alpha) { _material->SetObjectAlpha(alpha); }
	void SetDrawType(uint32_t type) { _draw_type = type; }
	void SetShader(std::shared_ptr<Shader>& shader) { _material->SetShader(shader); }
	void SetLight(Light light) { _material->SetLight(light); }
	void SetLight(float ambient, float specular, int32_t shininess, glm::vec3 pos, glm::vec3 color) { _material->SetLight(ambient, specular, shininess, pos, color); }
	void SetAmbient(float ambient) { _material->SetAmbient(ambient); }
	void SetShininess(int32_t shininess) { _material->SetShininess(shininess); }
	void SetLightPos(glm::vec3 pos) { _material->SetLightPos(pos); }
	void SetLightPos(float x, float y, float z) { _material->SetLightPos(glm::vec3{ x, y, z }); }
	void SetLightColor(glm::vec3 color) { _material->SetLightColor(color); }
	void SetLightColor(float r, float g, float b) { _material->SetLightColor(glm::vec3{ r, g, b }); }
	void SetTexture(uint32_t index) { _material->SetTexture(index); }

protected:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;

	glm::vec3 _pos;
	glm::vec3 _angle;

	glm::mat4 _model;
	std::list<glm::mat4> _transform;

	uint32_t _draw_type;
};
