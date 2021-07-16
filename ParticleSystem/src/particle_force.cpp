#include "particle_force.h"
#include "glm.hpp"

ParticleForce::ParticleForce(const glm::vec2& force) : force(force)
{
}

void ParticleForce::AffectParticle(Particle* particle)
{
	particle->velocity += force;
}
