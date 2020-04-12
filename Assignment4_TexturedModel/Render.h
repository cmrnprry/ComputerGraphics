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
    float x, y, z;
    float s, t;

    IndexData(float _x, float _y, float _z, float _s, float _t) : x(_x), y(_y), z(_z), s(_s), t(_t) { }

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
    QVector<GLfloat> indices;
    QVector<GLfloat> vertices;
    QVector<GLfloat> textures;
    QVector<GLfloat> normals;
    std::string mLib;
public:
    Render() = default;
    Render(std::string filename);

    //getter functions allow the Widget to add the vertices and faces to the buffer
    QVector<GLfloat> getIndx();
   // QVector<GLfloat> getIndx();
    QVector<GLfloat> getVerts();
    QVector<GLfloat> getTexs();
    QVector<GLfloat> getNormals();
    IndexData createFace(char* data);
    void ProcessData();

    std::string getMLib();
};
#endif