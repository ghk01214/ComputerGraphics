#pragma once

// NOTE :
// 월드 상에 육면체를 그려주는 object class를 상속받은 cube class
// 

#include "D3.h"

class Cube : public D3
{
public:
	Cube(glm::vec3 pos = vec3::zero());
	~Cube();

	bool Collide(Object* object, int32_t direction) override;
	void SetScaleSize(float x, float y, float z);

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }
	float GetDepth() { return _depth; }

private:
	float _width;	// 가로
	float _height;	// 높이
	float _depth;	// 세로
};

