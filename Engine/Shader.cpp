#include "pch.h"
#include <sstream>
#include "Shader.h"

Shader::Shader() :
	_id{ glCreateProgram() }
{
}

Shader::~Shader()
{
}

bool Shader::Add(const std::string& path, uint32_t type)
{
	uint32_t _shader{ glCreateShader(type) };

	if (_shader == 0)
	{
		std::cout << std::format("Error creating shader type\n");
		return false;
	}

	std::string code{ Util::ReadFile(path) };

	if (code.empty())
	{
		std::cout << std::format("Error compiling {} shader\n", path);
		return false;
	}

	auto source{ code.data() };
	glShaderSource(_shader, 1, &source, nullptr);
	glCompileShader(_shader);

	int32_t success{};
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	if (_FAILED success)
	{
		std::string log{};
		log.resize(1024);

		glGetShaderInfoLog(_shader, log.size(), nullptr, log.data());
		std::cout << std::format("Error compiling shader type {} : {}\n{}", type, log, code);

		return false;
	}

	glAttachShader(_id, _shader);
	glDeleteShader(_shader);

	return true;
}

int Shader::Link()
{
	int32_t success{};
	std::string log{};
	log.resize(1024);

	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &success);

	if (_FAILED success)
	{
		glGetProgramInfoLog(_id, log.size(), nullptr, log.data());

		return 1;
	}

	success = 0;
	log.clear();
	log.resize(1024);

	glValidateProgram(_id);
	glGetProgramiv(_id, GL_VALIDATE_STATUS, &success);

	if (_FAILED success)
	{
		glGetProgramInfoLog(_id, log.size(), nullptr, log.data());

		return 2;
	}

	return 0;
}

void Shader::Compile(const std::string& type, ...)
{
	std::stringstream attribute;
	attribute.str(type);

	std::string path;
	uint32_t shader_type{};

	int32_t count{};
	attribute >> count;

	for (int32_t i = 0; i < count; ++i)
	{
		attribute >> path >> shader_type;

		if (Add(path, shader_type) == false)
			return;
	}

	int32_t link{ Link() };

	if (link == 1)
	{
		std::cout << std::format("Error linking shader program\n");
		return;
	}

	if (link == 2)
	{
		std::cout << std::format("Error valid shader program\n");
		return;
	}

	std::cout << std::format("Shader compiling is done\n");
	Use();
}

void Shader::Use()
{
	glUseProgram(_id);
}

void Shader::SetInt(const std::string& name, int32_t value)
{
	auto location{ glGetUniformLocation(_id, name.c_str()) };
	glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	auto location{ glGetUniformLocation(_id, name.c_str()) };
	glUniform1f(location, value);
}

void Shader::SetVec2(const std::string& name, glm::vec2 value)
{
	auto location{ glGetUniformLocation(_id, name.c_str()) };
	glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, glm::vec3 value)
{
	auto location{ glGetUniformLocation(_id, name.c_str()) };
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, glm::mat4 value)
{
	auto location{ glGetUniformLocation(_id, name.c_str()) };
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
