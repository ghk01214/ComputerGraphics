#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
	Triangle();
	Triangle(float x, float y);
	~Triangle();

	void Load() override;
};

