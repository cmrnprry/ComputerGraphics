#include "ParticleSystem.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::drawParticles(const unsigned int msSinceUpdate, const QMatrix4x4& projection, const QMatrix4x4& view)
{
	for (auto emitter : emitters_)
	{
		if (particles_.size() <= 10)
		{
			particles_.push_back(emitter->emitParticle());
		}
		
	}

	for (auto particle : particles_)
	{
		std::cout << "i am a particle" << std::endl;
		particle->draw(projection, view);
	}
	updateParticles(msSinceUpdate);
}

ParticleSystem::~ParticleSystem()
{
	for (auto e : emitters_) {
		delete e;
	}

	emitters_.clear();

	for (auto p : particles_) {
		delete p;
	}

	particles_.clear();
}

void ParticleSystem::updateParticles(const unsigned int msSinceUpdate)
{
	for (auto particle : particles_)
	{
		if (particle->isDead() && particles_.size() > 0)
		{
			delete particles_.at(0);
			particles_.pop_front();
		}
		else 
		{
			particle->update(msSinceUpdate);
		}
		
	}
}