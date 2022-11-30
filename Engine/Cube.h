#pragma once

// NOTE :
// 월드 상에 육면체를 그려주는 object class를 상속받은 cube class
// 

#include "D2.h"
#include "D3.h"

class Cube : public D3
{
public:
	Cube(glm::vec3 pos = vec3::zero());
	~Cube();
};

class Skybox : public D2
{
public:
	Skybox(glm::vec3 pos = vec3::zero());
	~Skybox();
};