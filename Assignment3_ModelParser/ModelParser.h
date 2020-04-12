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
class ModelParser {

private:
	QVector<GLuint> indices;
	QVector<GLfloat> vertices;
	QVector<GLfloat> normals;

public:
	ModelParser() = default;
	ModelParser(std::string filename);

	//getter functions allow the Widget to add the vertices and faces to the buffer
	QVector<GLuint> getIndices();
	QVector<GLfloat> getVertices();
	QVector<GLfloat> getNormals();
};

#endif