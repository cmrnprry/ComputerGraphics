#ifndef EMITTER
#define EMITTER

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Particle.h"
#include "Renderable.h"



class Emitter {
protected:
    QVector3D location_;
    QVector3D orientation_;
    
    Renderable* model_;

public:
    Emitter(const QVector3D& pos, const QVector3D& orientation, Renderable* model);
    virtual ~Emitter();
    
    void moveEmitterTo(const QVector3D& newPos) { std::cout << "ahh" << std::endl; }
    void moveEmitterBy(const QVector3D& delta) { std::cout << "ahh" << std::endl; }
    void rotateEmitter(float angle, const QVector3D& axis) { std::cout << "ahh" << std::endl; }
    void setEmitterTransformation(const QMatrix4x4& tramsform) { std::cout << "ahh" << std::endl; }

    Particle* emitParticle();
};
#endif