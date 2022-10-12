#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
	Triangle();
	Triangle(glm::vec3 pos);
	~Triangle();

	void Move(float x, float y, float z) override;
	void RotateZ(float delta) override;
};
