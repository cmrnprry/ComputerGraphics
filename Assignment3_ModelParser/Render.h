#ifndef MODELPARSER
#define MODELPARSER

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

//A class to parse .obj files for rendering.
class Render {

private:
	QVector<GLuint> indices;
	QVector<GLfloat> vertices;
	QVector<GLfloat> normals;

public:
	Render() = default;
	Render(std::string filename);

	//getter functions allow the Widget to add the vertices and faces to the buffer
	QVector<GLuint> getIndx();
	QVector<GLfloat> getVerts();
	QVector<GLfloat> getNormals();
};
#endif