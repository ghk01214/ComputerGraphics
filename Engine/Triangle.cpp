#include "pch.h"
#include "Triangle.h"

Triangle::Triangle(glm::vec3 pos) :
	D3{ "../Dependencies/model/triangle.obj", pos }
{
}

Triangle::~Triangle()
{
}
