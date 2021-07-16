#pragma once
#include "transform.h"
#include "object.h"

#define ELEMENTS_IN_VERTEX 28

class Renderer;

class Particle : public Object
{
private:
	unsigned char* texture = nullptr;
	float zDepth;
	int layer;
public:
	static const float vertices[ELEMENTS_IN_VERTEX];
	static const unsigned int indecies[6];

	glm::vec4 color;
	glm::vec2 velocity;

	Particle();
	Particle(const glm::vec4& color);
	Particle(const glm::vec2& position);
	Particle(const glm::vec2& position, const glm::vec4& color);
	Particle(const Transform& transform, const glm::vec4& color);
	~Particle();

	void SetLayer(const int layer);
	int GetLayer() const;
	float* GetData() const;
	bool OnScreen() const;
};