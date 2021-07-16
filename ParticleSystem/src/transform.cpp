#include "transform.h"
#include "gtx/matrix_transform_2d.hpp"

Transform::Transform() : position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f) {}

Transform::Transform(const Transform& other)
{
	position = other.position;
	scale = other.scale;
	rotation = other.rotation;
}

Transform::Transform(glm::vec2 tr, glm::vec2 sc, float rot) : position(tr), scale(sc), rotation(rot) {}

Transform::Transform(float tr_x, float tr_y, float sc_x, float sc_y, float rot) : 
	position(glm::vec2(tr_x, tr_y)), scale(glm::vec2(sc_x, sc_y)), rotation(rot) {}

Transform::~Transform() {}

glm::mat3x3 Transform::GetModelMatrix()
{
	glm::mat3x3 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation);
	modelMatrix = glm::scale(modelMatrix, scale);
	return modelMatrix;
}
