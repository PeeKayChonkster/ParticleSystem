#include "particles.h"
#include "renderer.h"
#include <memory>

Particles::Particles(Renderer* renderer) : renderer(renderer), layer(0)
{
}

Particles::~Particles()
{
}

void Particles::RegisterParticle(Particle* particle)
{
	renderer->RegisterParticle(particle);
	particles.push_back(particle);
}

std::vector<Particle*>::iterator Particles::UnregisterParticle(Particle* particle)
{
	auto iter = std::find(particles.begin(), particles.end(), particle);

	renderer->UnregisterParticle(particle);
	delete particle;
	return particles.erase(iter);
}

void Particles::Update()
{	
	auto iter = particles.begin();
	while (iter != particles.end())
	{
		if (!(*iter)->OnScreen())
		{
			iter = UnregisterParticle(*iter);
		}
		else
		{
			// add velocity to particle position
			(*iter)->Translate((*iter)->velocity);

			// account for all effects
			for (ParticleEffect* e : effects)
			{
				e->AffectParticle(*iter);
			}
			iter++;
		}
	}
}


void Particles::CreateParticle(const glm::vec2& position, const glm::vec4& color)
{
	Particle* particle = new Particle(position, color);
	particle->SetLayer(layer);
	RegisterParticle(particle);
}

void Particles::CreateParticle(const Transform& transform, glm::vec4 color)
{
	Particle* particle = new Particle(transform, color);
	particle->SetLayer(layer);
	RegisterParticle(particle);
}

void Particles::SetLayer(const int newLayer)
{
	layer = newLayer;
}

void Particles::AddEffect(ParticleEffect* effect)
{
	effects.push_back(effect);
}

void Particles::RemoveEffect(ParticleEffect* effect)
{
	auto iter = std::find(effects.begin(), effects.end(), effect);
	effects.erase(iter);
}
