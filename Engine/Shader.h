#pragma once

class Shader
{
public:
	Shader();
	~Shader();

	bool Add(const std::string& path, uint32_t type);
	int Link();
	void Compile(const std::string& type, ...);

	void Use();

	void SetInt(const std::string& name, int32_t value);
	void SetFloat(const std::string& name, float value);
	void SetVec2(const std::string& name, float* value_ptr);
	void SetVec3(const std::string& name, float* value_ptr);
	void SetMat4(const std::string& name, float* value_ptr);

	constexpr uint32_t ID() const { return _id; }

private:
	uint32_t _id;
};
