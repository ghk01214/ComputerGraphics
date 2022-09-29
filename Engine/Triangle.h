#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
	Triangle();
	Triangle(glm::vec3 pos);
	~Triangle();

	glm::mat4 Teleport(glm::vec3 pos);

	void Load() override;
};

