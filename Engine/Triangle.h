#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
	Triangle();
	Triangle(glm::vec3 pos);
	~Triangle();
};

