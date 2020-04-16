#ifndef PARTICLE
#define PARTICLE

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Renderable.h"

class Particle {
protected:
    Renderable* model_;
    QMatrix4x4 particleTransform_;
    QVector3D velocity_;
    float secondsLeftToLive_;

public:
    Particle(Renderable* model, const QVector3D& velocity, QMatrix4x4 transform, float lifespan);
    virtual ~Particle();

    void update(unsigned int msSinceLastFrame);
    void draw(const QMatrix4x4& projection, const QMatrix4x4& view);
    bool isDead() const { return secondsLeftToLive_ > 0.0; }
};
#endif