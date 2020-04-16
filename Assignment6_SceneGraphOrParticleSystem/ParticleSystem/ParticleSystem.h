#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Emitter.h"
#include "Particle.h"

//A class to parse .obj files for rendering.
class ParticleSystem {
protected:
    QVector<Emitter*> emitters_;
    QVector<Particle*> particles_;

    void updateParticles(const unsigned int msSinceUpdate);

public:
    ParticleSystem();
    virtual ~ParticleSystem();

    void addEmitter(Emitter* emitter) { emitters_.push_back(emitter); }
    void removeEmitter(Emitter* emitter) {
        for (int i = 0; i < emitters_.size(); i++)
        {
            if (emitter == emitters_[i])
            {
                emitters_.erase(emitters_.begin() + i);
            }
        } 
    }

    void drawParticles(const unsigned int msSinceUpdate, const QMatrix4x4& projection, const QMatrix4x4& view);
};
#endif