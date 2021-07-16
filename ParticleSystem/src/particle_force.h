#pragma once

#include "particle_effect.h"


class ParticleForce : ParticleEffect
{
private:
	glm::vec2 force;
public:
	ParticleForce() = delete;
	ParticleForce(const glm::vec2& force);

	void AffectParticle(Particle* particle) override;
};