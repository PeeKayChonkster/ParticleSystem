#pragma once
#include "glm.hpp"

class Tools
{
public:
	static glm::vec4&& RandomColor(bool alpha = false);
	static glm::vec2&& RandVec2(float amplitude = 1.0f);
};