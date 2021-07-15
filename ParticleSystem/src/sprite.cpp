#include "sprite.h"
#include "GLFW/glfw3.h"
#include "gtx/matrix_transform_2d.hpp"

const float Sprite::vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
};

const unsigned int Sprite::indecies[] = {
	0, 1, 2,
	0, 2, 3,
};

Sprite::Sprite() : Object()
{
	color = glm::vec4(1.0, 1.0, 1.0, 1.0);
}

Sprite::Sprite(const glm::vec4& color) : color(color)
{
}

Sprite::~Sprite()
{
}

float* Sprite::GetData() const
{
	static float data[ELEMENTS_IN_VERTEX];
	for (int i = 0, j = 0; i < ELEMENTS_IN_VERTEX; i += 7, j += 3)
	{
		data[i] = vertices[j] * transform.scale.x + transform.position.x;
		data[i + 1] = vertices[j + 1] * transform.scale.y + transform.position.y;
		data[i + 3] = color.r;
		data[i + 4] = color.g;
		data[i + 5] = color.b;
		data[i + 6] = color.a;
	}
	return data;
}

