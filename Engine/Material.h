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

struct Texture
{
	uint32_t id;
	bool flip_horizontal;
	bool flip_vertical;
};

class Material
{
public:
	Material();
	virtual ~Material();

	void ApplyColor();
	void ApplyLight();
	void ApplyTexture();
	void ApplySkybox();

	void CreateTexture(const std::string& path, bool flip_vertical = true, bool flip_horizontal = false);
	void CreateSkybox(const std::vector<std::string>* path, bool flip_vertical = true, bool flip_horizontal = false);
	void BindTexture();

	glm::vec3 GetColor() { return _color; }
	Light GetLight() { return _light; }

	void SetShader(std::shared_ptr<Shader>& shader) { _shader = shader; }
	void SetObjectColor(glm::vec4 color);
	void SetObjectAlpha(float alpha);
	void SetLight(Light light);
	void SetLight(float ambient, float specular, int32_t shininess, glm::vec3 pos, glm::vec3 color) { SetLight(Light{ ambient, specular, shininess, pos, color }); }
	void SetAmbient(float ambient);
	void SetSpecular(float specular);
	void SetShininess(int32_t shininess);
	void SetLightPos(glm::vec3 pos);
	void SetLightColor(glm::vec3 color);
	void SetTexture(uint32_t index);

	void ChangeLightState();
	void TurnOnLight();
	void TurnOffLight();
	
	void FlipTextureHorizontal(bool flip);
	void FlipTextureVertical(bool flip);

private:
	std::shared_ptr<Shader> _shader;
	Light _light;
	glm::vec4 _color;

	Texture _texture;
	bool _have_texture;
};
