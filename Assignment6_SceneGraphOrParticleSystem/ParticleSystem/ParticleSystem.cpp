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
		particles_.push_back(emitter->emitParticle());
	}

	for (auto particle : particles_)
	{
		particle->draw(projection, view);
	}

	updateParticles(msSinceUpdate);
}

ParticleSystem::~ParticleSystem()
{
	for (auto e : emitters_) {
		delete e;
	}

	for (auto p : particles_) {
		delete p;
	}
}

void ParticleSystem::updateParticles(const unsigned int msSinceUpdate)
{
	for (auto particle : particles_)
	{
		particle->update(msSinceUpdate);
	}

	while (!particles_.at(0)->isDead() && particles_.size() > 0)
	{
		delete particles_.at(0);

		particles_.pop_front();
	}
}