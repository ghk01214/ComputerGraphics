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

	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int32_t value);
	void SetFloat(const std::string& name, float value);
	void SetVec2(const std::string& name, glm::vec2 value);
	void SetVec3(const std::string& name, glm::vec3 value);
	void SetMat4(const std::string& name, glm::mat4 value);

	constexpr uint32_t ID() const { return _id; }

private:
	uint32_t _id;
};

