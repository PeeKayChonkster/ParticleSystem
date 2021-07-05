#include "transform.h"

Transform::Transform() : position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f) {}

Transform::Transform(glm::vec2 tr, glm::vec2 sc, float rot) : position(tr), scale(sc), rotation(rot) {}

Transform::Transform(float tr_x, float tr_y, float sc_x, float sc_y, float rot) : 
	position(glm::vec2(tr_x, tr_y)), scale(glm::vec2(sc_x, sc_y)), rotation(rot) {}

Transform::~Transform() {}
