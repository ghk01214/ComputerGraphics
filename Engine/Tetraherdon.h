﻿#pragma once

// NOTE :
// 월드 상에 사면체를 그리는 object class를 상속받은 tetraherdon class
// 

#include "Object.h"

class Tetraherdon : public Object
{
public:
	Tetraherdon(glm::vec3 pos = vec3::zero());
	~Tetraherdon();
};
