#pragma once

#include <vector>
#include "particle.h"

class ParticleEffect
{
public:
	ParticleEffect();
	virtual ~ParticleEffect();
	virtual void AffectParticle(Particle* particle);
};