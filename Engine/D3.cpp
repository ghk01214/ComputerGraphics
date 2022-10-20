#include "pch.h"
#include "D3.h"

D3::D3(const std::string& path, glm::vec3 pos)
{
	std::vector<float> vertex;
	std::vector<float> normal;
	std::vector<float> texture;
	std::vector<uint32_t> index;
	int32_t vertex_num;
	int32_t index_num;

	Util::ReadModel(path, &vertex, &normal, &texture, &index, &vertex_num, &index_num);

	_mesh->SetVertex(&vertex);
	_mesh->SetNormal(&normal);
	_mesh->SetTexture(&texture);
	_mesh->SetIndex(&index);

	Move(pos);
}

void D3::OnLoad()
{
	_mesh->CreateBuffer();

#if _DEBUG
	std::string str{ "2 " };
	str += "../Dependencies/shader/Vertex.glsl ";
	str += std::to_string(GL_VERTEX_SHADER);
	str += " ../Dependencies/shader/Color.glsl ";
	str += std::to_string(GL_FRAGMENT_SHADER);
#else
	std::string str{ "2 " };
	str += "Dependencies/shader/Vertex.glsl ";
	str += std::to_string(GL_VERTEX_SHADER);
	str += " Dependencies/shader/Color.glsl ";
	str += std::to_string(GL_FRAGMENT_SHADER);
#endif

	_shader->Compile(str);
	_mesh->CreateModel(_shader);
}
