#include "Emitter.h"
#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>


Emitter::Emitter(const QVector3D& pos, const QVector3D& orientation, Renderable* model):
	location_(pos), orientation_(orientation), model_(model)
{ }

Emitter::~Emitter()
{
	delete model_;
}

Particle* Emitter::emitParticle()
{
	QVector3D velocity = orientation_ * 100.0;

	QMatrix4x4 transform;
	transform.setToIdentity();
	transform.translate(location_);

	float lifetime = 2.5;

	return new Particle(model_, velocity, transform, lifetime);
}