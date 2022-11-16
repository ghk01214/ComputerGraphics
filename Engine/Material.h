#pragma once

// NOTE :
// 월드 상에 생성된 object의 질감, 텍스처 등을 결정하는 material class
// 

class Shader;

struct Light
{
	float ambient;
	float specular;
	int32_t shininess;
	glm::vec3 pos;
	glm::vec3 color;
	bool on{ true };
};

class Material
{
public:
	Material();
	virtual ~Material();

	void ApplyColor();
	void ApplyLight();

	glm::vec3 GetColor() { return _color; }
	Light GetLight() { return _light; }

	void SetShader(std::shared_ptr<Shader>& shader) { _shader = shader; }
	void SetColor(glm::vec3 color) { _color = color; }
	void SetObjectColor(glm::vec3 color);
	void SetLight(Light light);
	void SetLight(float ambient, float specular, int32_t shininess, glm::vec3 pos, glm::vec3 color) { SetLight(Light{ ambient, specular, shininess, pos, color }); }
	void SetAmbient(float ambient);
	void SetSpecular(float specular);
	void SetShininess(int32_t shininess);
	void SetLightPos(glm::vec3 pos);
	void SetLightColor(glm::vec3 color);

	void ChangeLightState();
	void TurnOnLight();
	void TurnOffLight();

private:
	std::shared_ptr<Shader> _shader;
	Light _light;
	glm::vec3 _color;
};
