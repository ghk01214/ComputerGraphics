#include "pch.h"
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
	uint32_t shader{ glCreateShader(type) };

	if (shader == 0)
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
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int32_t success{};
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (_FAILED success)
	{
		std::string log{};
		log.resize(1024);

		glGetShaderInfoLog(shader, log.size(), nullptr, log.data());
		std::cout << std::format("Error compiling shader type {} : {}\n{}", type, log, code);

		return false;
	}

	glAttachShader(_id, shader);
	glDeleteShader(shader);

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
	std::va_list ap;
	int32_t count{ 1 };

	std::string path;
	uint32_t shader_type{};

	va_start(ap, type);

	for (int32_t i = 0; i < std::stoi(std::string{ type[0] }); ++i)
	{
		switch (type[count])
		{
			case 's':
			{
				path = va_arg(ap, char*);
				++count;
			}
			FALLTHROUGH
			case 'i':
			{
				shader_type = va_arg(ap, uint32_t);
				count = 1;
			}
			break;
		}

		if (Add(path, shader_type) == false)
			return;
	}

	va_end(ap);
	int32_t link{ Link() };

	if (link == 1)
	{
		std::cerr << "Error linking shader program\n";
		return;
	}

	if (link == 2)
	{
		std::cerr << "Error validating shader program\n";
		return;
	}

	Use();
	std::cerr << "Shader compiling is done\n";
}

void Shader::Use()
{
}

void Shader::SetBool(const std::string& name, bool value)
{
}

void Shader::SetInt(const std::string& name, int32_t value)
{
}

void Shader::SetFloat(const std::string& name, float value)
{
}

void Shader::SetVec2(const std::string& name, glm::vec2 value)
{
}

void Shader::SetVec3(const std::string& name, glm::vec3 value)
{
}

void Shader::SetMat4(const std::string& name, glm::mat4 value)
{
}
