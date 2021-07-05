#include "sprite.h"
#include "GLFW/glfw3.h"

const float Sprite::vertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, 0.0f, 1.0f
};

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
}

const float* Sprite::GetVertices()
{
	return vertices;
}
