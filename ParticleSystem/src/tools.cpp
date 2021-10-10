#include "tools.h"


/// <summary>
/// Random float from 0 to 1
/// </summary>
/// <returns></returns>
float RandomFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


glm::vec4&& Tools::RandomColor(bool alpha)
{
	float r = RandomFloat();
	float g = RandomFloat();
	float b = RandomFloat();
	float a = alpha? RandomFloat() : 1.0f;
	return std::move(glm::vec4(r, g, b, a));
}

glm::vec2&& Tools::RandVec2(float amplitude)
{
	return std::move(glm::vec2(RandomFloat() * amplitude, RandomFloat() * amplitude));
}
