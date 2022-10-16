#pragma once

// NOTE :
// 월드 상에 생성된 object의 질감, 텍스처 등을 결정하는 material class
// 

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
