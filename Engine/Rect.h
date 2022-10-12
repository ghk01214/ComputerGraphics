#pragma once

#include "Object.h"

class Rect : public Object
{
public:
	Rect();
	Rect(glm::vec3 pos);
	~Rect();

	const std::vector<glm::vec3>& GetVertex() const { return _vertex; }

	void SetVertex(int32_t index, glm::vec3 pos);
	void SetVertex(glm::vec3 pos);

private:
	std::vector<glm::vec3> _vertex;
};
