#include "particle.h"
#include "GLFW/glfw3.h"
#include "gtx/matrix_transform_2d.hpp"
#include "application.h"

const float Particle::vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
};

const unsigned int Particle::indecies[] = {
	0, 1, 2,
	0, 2, 3,
};


Particle::Particle() : Object(), color(glm::vec4(1.0, 1.0, 1.0, 1.0)), zDepth(0.0f), layer(0)
{
	
}

Particle::Particle(const glm::vec4& color) : Object(), color(color), zDepth(0.0f), layer(0)
{
}

Particle::Particle(const glm::vec2& position): Object(position), color(glm::vec4(1.0, 1.0, 1.0, 1.0)), zDepth(0.0f), layer(0)
{
}

Particle::Particle(const glm::vec2& position, const glm::vec4& color) : Object(position), color(color), zDepth(0.0f), layer(0)
{
}

Particle::Particle(const Transform& transform, const glm::vec4& color) : Object(transform), color(color), zDepth(0.0f), layer(0)
{
}

Particle::~Particle()
{
}

void Particle::SetLayer(const int newLayer)
{
	layer = newLayer;
	zDepth = layer * 0.001f;
}

int Particle::GetLayer() const
{
	return layer;
}

float* Particle::GetData() const
{
	static std::vector<float> data;
	data.clear();
	data.resize(ELEMENTS_IN_VERTEX);
	for (int i = 0, j = 0; i < ELEMENTS_IN_VERTEX; i += 7, j += 3)
	{
		data[i] = vertices[j] * transform.scale.x + transform.position.x;
		data[i + 1] = vertices[j + 1] * transform.scale.y + transform.position.y;
		data[i + 2] = zDepth;
		data[i + 3] = color.r;
		data[i + 4] = color.g;
		data[i + 5] = color.b;
		data[i + 6] = color.a;
	}
	return &data[0];
}

// For static camera only
bool Particle::OnScreen() const
{
	if (transform.position.x > 0.0f && transform.position.x < Application::GetWindowWidth())
		if (transform.position.y > 0.0f && transform.position.y < Application::GetWindowHeight())
			return true;
	return false;
}

