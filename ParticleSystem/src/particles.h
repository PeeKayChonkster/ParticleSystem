#pragma once

#include "particle.h"
#include "particle_effect.h"
#include <vector>

class Particles
{
private:
	Renderer* renderer;
	std::vector<Particle*> particles;
	std::vector<ParticleEffect*> effects;
	int layer;

	void Trim();
public:
	Particles() = delete;
	Particles(Renderer* renderer);
	~Particles();
	void RegisterParticle(Particle* particle);
	std::vector<Particle*>::iterator UnregisterParticle(Particle* particle);
	void Update();
	void CreateParticle(const glm::vec2& position, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	void CreateParticle(const Transform& transform, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	void SetLayer(const int layer);
	void AddEffect(ParticleEffect* effect);
	void RemoveEffect(ParticleEffect* effect);
};