#pragma once
#include "transform.h"
#include "object.h"

#define ELEMENTS_IN_VERTEX 28

class Sprite : public Object
{
private:
	unsigned char* texture = nullptr;
public:
	static const float vertices[ELEMENTS_IN_VERTEX];
	static const unsigned int indecies[6];

	glm::vec4 color;

	Sprite();
	Sprite(const glm::vec4& color);
	~Sprite();

	float* GetData() const;
};