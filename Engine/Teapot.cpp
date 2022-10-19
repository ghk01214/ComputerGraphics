#include "pch.h"
#include "Teapot.h"

Teapot::Teapot(glm::vec3 pos)
{
	std::vector<float> vertex;
	std::vector<float> normal;
	std::vector<float> texture;
	std::vector<uint32_t> index;
	int32_t vertex_num;
	int32_t index_num;

	Util::ReadModel("../Dependencies/model/teapot.obj", &vertex, &normal, &texture, &index, &vertex_num, &index_num);

	_mesh->SetVertex(&vertex);
	_mesh->SetNormal(&normal);
	_mesh->SetTexture(&texture);
	_mesh->SetIndex(&index);
}

Teapot::~Teapot()
{
}
