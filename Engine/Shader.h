#pragma once

// NOTE :
// GLSL shader를 추가, 컴파일, 사용하는 shader class
// 

class Shader
{
public:
	Shader();
	Shader(const std::string& vertex, const std::string& fragment);
	~Shader();

	bool Add(const std::string& path, uint32_t type);
	int Link();
	void Compile(const std::string& type, ...);

	void OnLoad(const std::string& vertex, const std::string& fragment);
	void OnUse();

	void SetInt(const std::string& name, int32_t value);
	void SetFloat(const std::string& name, float value);
	void SetVec2(const std::string& name, float* value_ptr);
	void SetVec3(const std::string& name, float* value_ptr);
	void SetMat4(const std::string& name, float* value_ptr);

	constexpr uint32_t ID() const { return _id; }

private:
	uint32_t _id;
};
