#pragma once
#include "glm.hpp"

struct Transform
{
private:
public:
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

	Transform();
	Transform(glm::vec2 tr, glm::vec2 sc, float rot);
	Transform(float tr_x, float tr_y, float sc_x, float sc_y, float rot);
	~Transform();
};

