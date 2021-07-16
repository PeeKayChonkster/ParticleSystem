#include "tools.h"

glm::vec4&& Tools::RandomColor(bool alpha)
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float a = alpha? static_cast <float> (rand()) / static_cast <float> (RAND_MAX) : 1.0f;
	return std::move(glm::vec4(r, g, b, a));
}