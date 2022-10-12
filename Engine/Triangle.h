#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
	Triangle();
	Triangle(glm::vec3 pos, bool reverse);
	~Triangle();
	
	void Move(glm::vec3 delta) override;
	void Move(float x, float y, float z) override;
	void RotateZ(float delta) override;

	void ChangeColor();
};
