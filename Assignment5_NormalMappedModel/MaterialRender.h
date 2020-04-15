#ifndef MATERIALREDNDER
#define MATERIALREDNDER

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

//A class to parse .obj files for rendering.
class MaterialRender {

private:
    std::string matName;
    std::string diffuseColor;
public:
    MaterialRender() = default;
    MaterialRender(std::string filename);

    std::string getDiffuse() { return diffuseColor; }
    std::string getMatName() { return matName; }
};
#endif