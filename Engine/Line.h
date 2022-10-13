#pragma once

#include "Object.h"

class Line : public Object
{
public:
	Line();
	Line(glm::vec3 pos, float length, bool horizontal = true);
	~Line();
};

