#pragma once

// NOTE :
// 월드 상에 사각 뿔을 그려주는 object class를 상속받은 pyramid class
// 

#include "Object.h"

class Pyramid : public Object
{
public:
	Pyramid(glm::vec3 pos = vec3::zero());
	~Pyramid();
};

