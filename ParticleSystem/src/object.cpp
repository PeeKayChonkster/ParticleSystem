#include "object.h"
#include "application.h"

Object::Object()
{
}

Object::Object(const Transform& transform) : transform(transform)
{
}

Object::Object(const glm::vec2& position)
{
	transform.position = position;
}

Object::~Object()
{
}

void Object::Translate(const glm::vec2& translation)
{
	transform.position += translation;
}

void Object::Scale(const glm::vec2& scale)
{
	transform.scale *= scale;
}

void Object::Rotate(float radians)
{
	transform.rotation += radians;
}
