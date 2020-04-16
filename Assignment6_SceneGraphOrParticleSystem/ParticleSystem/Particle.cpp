#include "Particle.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>

Particle::Particle(Renderable* model, const QVector3D& velocity, QMatrix4x4 transform, float lifespan): 
	model_(model), velocity_(velocity), particleTransform_(transform), secondsLeftToLive_(lifespan)
{

}

Particle::~Particle()
{
	delete model_;
}

void Particle::update(unsigned int msSinceUpdate)
{
	secondsLeftToLive_ -= (float)msSinceUpdate / 1000.0;

	particleTransform_.translate(velocity_);

	velocity_ *= 0.95;
}

void Particle::draw(const QMatrix4x4& projection, const QMatrix4x4& view)
{
	if (secondsLeftToLive_ <= 0.0)
	{
		return;
	}

	model_->draw(view, projection);
}
