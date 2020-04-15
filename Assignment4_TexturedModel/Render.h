#ifndef REDNDER
#define REDNDER

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>


//A struct to hold our data for the indicies
struct IndexData {
    unsigned int vIndx, vtIndx, normIndx;

    IndexData(unsigned int _vIndx, unsigned int _vtIndx, unsigned int _normIndx) : vIndx(_vIndx), vtIndx(_vtIndx), normIndx(_normIndx) { }

    // Tests if two VertexData are equal
    bool operator== (const IndexData& rhs) {
        if ((vIndx == rhs.vIndx) && (vtIndx == rhs.vtIndx) && (normIndx == rhs.normIndx)) {
            return true;
        }
        return false;
    }
};

//A class to parse .obj files for rendering.
class Render {

private:
    QVector<IndexData> indxData;
    QVector<unsigned int> indices;
    QVector<QVector3D> vertices;
    QVector<QVector2D> textures;
    QVector<QVector3D> normals;
    std::string mLib;
public:
    Render() = default;
    Render(std::string filename);

    //getter functions allow the Widget to add the vertices and faces to the buffer
    QVector<unsigned int> getIndx();
    QVector<QVector3D> getVerts();
    QVector<QVector2D> getTexs();
    QVector<QVector3D> getNormals();
    IndexData createFace(char* data);
    void ProcessData();

    std::string getMLib();
};
#endif