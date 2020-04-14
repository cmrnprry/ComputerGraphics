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
    unsigned int x, y, z;
    unsigned int s, t;

    IndexData(unsigned int _x, unsigned int _y, unsigned int _z, unsigned int _s, unsigned int _t) : x(_x), y(_y), z(_z), s(_s), t(_t) { }

    // Tests if two VertexData are equal
    bool operator== (const IndexData& rhs) {
        if ((x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (s == rhs.s) && (t == rhs.t)) {
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