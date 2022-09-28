#pragma once

class Shader;

class Material
{
public:
	Material();
	virtual ~Material();

	std::shared_ptr<Shader> GetShader() { return _shader; }

private:
	std::shared_ptr<Shader> _shader;
};
