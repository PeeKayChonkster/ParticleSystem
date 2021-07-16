#pragma once
#include "transform.h"

class Object
{
private:

public:
	Transform transform;
	Object();
	Object(const Transform& transform);
	Object(const glm::vec2& position);
	virtual ~Object();
	void Translate(const glm::vec2& translation);
	void Scale(const glm::vec2& scale);
	void Rotate(float radians);
};

