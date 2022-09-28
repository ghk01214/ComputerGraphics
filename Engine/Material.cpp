#include "pch.h"
#include "Material.h"
#include "Shader.h"

Material::Material() :
	_shader{ std::make_shared<Shader>() }
{
}

Material::~Material()
{
}
