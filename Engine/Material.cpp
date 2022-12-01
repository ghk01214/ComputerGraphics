#include "pch.h"
#include "Material.h"
#include "Shader.h"

Material::Material() :
	_color{ glm::vec4{-1} },
	_light{ 0.3f, 0.5f, 128, vec3::back(3.f), vec3::unit(), true },
	_texture{ 0, false, true },
	_have_texture{ false }
{
}

Material::~Material()
{
}

void Material::ApplyColor()
{
	_shader->SetVec4("obj_color", &_color);
}

void Material::ApplyLight()
{
	_shader->SetFloat("ambient_strength", _light.ambient);
	_shader->SetFloat("specular_strength", _light.specular);
	_shader->SetInt("shininess", _light.shininess);
	_shader->SetVec3("light_pos", &_light.pos);
	_shader->SetVec3("light_color", &_light.color);
	_shader->SetBool("light_on", _light.on);
}

void Material::ApplyTexture()
{
	_shader->SetInt("tex_sampler", _texture.id);
	_shader->SetBool("have_texture", _have_texture);
	_shader->SetBool("flip_horizontal", _texture.flip_horizontal);
	_shader->SetBool("flip_vertical", _texture.flip_vertical);

	glActiveTexture(GL_TEXTURE0 + _texture.id);
	glBindTexture(GL_TEXTURE_2D, _texture.id);
}

void Material::ApplySkybox()
{
	_shader->SetInt("tex_sampler", _texture.id);
	_shader->SetBool("flip_horizontal", _texture.flip_horizontal);
	_shader->SetBool("flip_vertical", _texture.flip_vertical);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture.id);
}

void Material::CreateTexture(const std::string& path, bool flip_vertical, bool flip_horizontal)
{
	_texture.flip_horizontal = flip_horizontal;
	_texture.flip_vertical = flip_vertical;
	_have_texture = true;

	int32_t width;
	int32_t height;
	int32_t number_of_channel;

	std::shared_ptr<uint8_t> texture{ stbi_load(path.c_str(), &width, &height, &number_of_channel, 0) };

	glGenTextures(1, &_texture.id);
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + number_of_channel / 4, width, height, 0, GL_RGB + number_of_channel / 4, GL_UNSIGNED_BYTE, texture.get());

	ApplyTexture();
}

void Material::CreateSkybox(const std::vector<std::string>* path, bool flip_vertical, bool flip_horizontal)
{
	_texture.flip_horizontal = flip_horizontal;
	_texture.flip_vertical = flip_vertical;

	int32_t width;
	int32_t height;
	int32_t number_of_channel;

	glGenTextures(1, &_texture.id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture.id);

	for (int32_t i = 0; i < path->size(); ++i)
	{
		std::shared_ptr<uint8_t> texture{ stbi_load((*path)[i].c_str(), &width, &height, &number_of_channel, 0)};

		if (texture != nullptr)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB + number_of_channel / 4, width, height, 0, GL_RGB + number_of_channel / 4, GL_UNSIGNED_BYTE, texture.get());
		else
			std::cout << "error" << std::endl;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	ApplySkybox();
}

void Material::SetObjectColor(glm::vec4 color)
{
	_color = color;

	ApplyColor();
}

void Material::SetObjectAlpha(float alpha)
{
	_color.a = alpha;

	ApplyColor();
}

void Material::SetLight(Light light)
{
	_light = light;

	ApplyLight();
}

void Material::SetAmbient(float ambient)
{
	_light.ambient = ambient;

	_shader->SetFloat("ambient_strength", _light.ambient);
}

void Material::SetSpecular(float specular)
{
	_light.specular = specular;

	_shader->SetFloat("specular_strength", _light.specular);
}

void Material::SetShininess(int32_t shininess)
{
	_light.shininess = shininess;

	_shader->SetInt("shininess", _light.shininess);
}

void Material::SetLightPos(glm::vec3 pos)
{
	_light.pos = pos;

	_shader->SetVec3("light_pos", &_light.pos);
}

void Material::SetLightColor(glm::vec3 color)
{
	_light.color = color;

	_shader->SetVec3("light_color", &_light.color);
}

void Material::SetTexture(uint32_t index)
{
	_texture.id = index;

	_shader->SetInt("tex_sampler", _texture.id);
}

void Material::ChangeLightState()
{
	_light.on = !_light.on;

	_shader->SetBool("light_on", _light.on);
}

void Material::TurnOnLight()
{
	_light.on = true;

	_shader->SetBool("light_on", _light.on);
}

void Material::TurnOffLight()
{
	_light.on = false;

	_shader->SetBool("light_on", _light.on);
}

void Material::FlipTextureHorizontal(bool flip)
{
	_texture.flip_horizontal = flip;

	_shader->SetBool("flip_horizontal", _texture.flip_horizontal);
}

void Material::FlipTextureVertical(bool flip)
{
	_texture.flip_vertical = flip;

	_shader->SetBool("flip_vertical", _texture.flip_vertical);
}
