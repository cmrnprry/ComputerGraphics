#include "Renderable.h"

#include <QtGui>
#include <QtOpenGL>
#include <iostream>


Renderable::Renderable() : vbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer), texture_(QOpenGLTexture::Target2D), numTris_(0), vertexSize_(0), rotationAxis_(0.0, 0.0, 1.0), rotationSpeed_(0.25)
{
	rotationAngle_ = 0.0;
}

Renderable::~Renderable()
{
	if (texture_.isCreated()) {
		texture_.destroy();
	}
	if (vbo_.isCreated()) {
		vbo_.destroy();
	}
	if (ibo_.isCreated()) {
		ibo_.destroy();
	}
	if (vao_.isCreated()) {
		vao_.destroy();
	}
}

void Renderable::createShaders()
{

	QDir directory("C:/Users/Cam/Documents/GitHub/GraphicsForked/ComputerGraphics/Assignment4_TexturedModel");
	QString vertexFilename = directory.absoluteFilePath("vert.glsl");

	//QString vertexFilename = "./vert.glsl";
	bool ok = shader_.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexFilename);
	if (!ok) {
		qDebug() << shader_.log();
	}

	QString fragmentFilename = directory.absoluteFilePath("frag.glsl");
	//QString fragmentFilename = "../frag.glsl";
	ok = shader_.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentFilename);
	if (!ok) {
		qDebug() << shader_.log();
	}
	ok = shader_.link();
	if (!ok) {
		qDebug() << shader_.log();
	}
}

void Renderable::init(const QVector<QVector3D>& positions, const QVector<QVector3D>& normals, const QVector<QVector2D>& texCoords, const QVector<unsigned int>& indexes, const QString& textureFile)
{
	// NOTE:  We do not currently do anything with normals -- we just
	// have it here for a later implementation!
	// We need to make sure our sizes all work out ok.
	if (positions.size() != texCoords.size() ||
		positions.size() != normals.size()) {
		qDebug() << "[Renderable]::init() -- positions size mismatch with normals/texture coordinates";
		return;
	}

	// Set our model matrix to identity
	modelMatrix_.setToIdentity();
	// Load our texture.
	texture_.setData(QImage(textureFile));

	// set our number of trianges.
	numTris_ = indexes.size() / 3;

	// num verts (used to size our vbo)
	int numVerts = positions.size();
	vertexSize_ = 3 + 3 + 2;  // Position + Normals + texCoord
	int numVBOEntries = numVerts * vertexSize_;

	// Setup our shader.
	createShaders();

	// Now we can set up our buffers.
	// The VBO is created -- now we must create our VAO
	vao_.create();
	vao_.bind();
	vbo_.create();
	vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo_.bind();
	// Create a temporary data array
	float* data = new float[numVBOEntries];
	for (int i = 0; i < numVerts; ++i) {
		//positions
		data[i * vertexSize_ + 0] = positions.at(i).x();
		data[i * vertexSize_ + 1] = positions.at(i).y();
		data[i * vertexSize_ + 2] = positions.at(i).z();

		//Normals
		data[i * vertexSize_ + 3] = normals.at(i).x();
		data[i * vertexSize_ + 4] = normals.at(i).y();
		data[i * vertexSize_ + 5] = normals.at(i).z();

		//textures
		data[i * vertexSize_ + 6] = texCoords.at(i).x();
		data[i * vertexSize_ + 7] = texCoords.at(i).y();
	}
	vbo_.allocate(data, numVBOEntries * sizeof(GL_FLOAT));
	delete[] data;

	// Create our index buffer
	ibo_.create();
	ibo_.bind();
	ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	// create a temporary array for our indexes
	unsigned int* idxAr = new unsigned int[indexes.size()];
	for (int i = 0; i < indexes.size(); ++i) {
		idxAr[i] = indexes.at(i);
	}
	ibo_.allocate(idxAr, indexes.size() * sizeof(unsigned int));
	delete[] idxAr;

	// Make sure we setup our shader inputs properly
	//positions
	shader_.enableAttributeArray(0);
	shader_.setAttributeBuffer(0, GL_FLOAT, 0, 3, vertexSize_ * sizeof(GL_FLOAT));

	//normals
	shader_.enableAttributeArray(1);
	shader_.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GL_FLOAT), 3, vertexSize_ * sizeof(GL_FLOAT));

	//textures
	shader_.enableAttributeArray(2);
	shader_.setAttributeBuffer(2, GL_FLOAT, 6 * sizeof(GL_FLOAT), 2, vertexSize_ * sizeof(GL_FLOAT));

	// Release our vao and THEN release our buffers.
	vao_.release();
	vbo_.release();
	ibo_.release();
}

void Renderable::update(const qint64 msSinceLastFrame)
{

	float sec = msSinceLastFrame / 1000.0f;
	float anglePart = sec * rotationSpeed_ * 360.f;
	rotationAngle_ += anglePart;
	while (rotationAngle_ >= 360.0) {
		rotationAngle_ -= 360.0;
	}

	shader_.bind();

	QVector3D pos = QVector3D(0.0f, 0.0f, 2.0f);
	//Set up point lights
	shader_.setUniformValue("pointLights[0].color", 1.0f, 0.0f, 1.0f);
	shader_.setUniformValue("pointLights[0].position", pos);
	shader_.setUniformValue("pointLights[0].ambientIntensity", 0.5f);
	shader_.setUniformValue("pointLights[0].specularStrength", 0.5f);
	shader_.setUniformValue("pointLights[0].constant", 1.0f);
	shader_.setUniformValue("pointLights[0].linear", 0.09f);
	shader_.setUniformValue("pointLights[0].quadratic", 0.032f);

	shader_.release();
}

void Renderable::draw(const QMatrix4x4& view, const QMatrix4x4& projection)
{
	// Create our model matrix.
	QMatrix4x4 rotMatrix;
	rotMatrix.setToIdentity();
	rotMatrix.rotate(rotationAngle_, rotationAxis_);

	QMatrix4x4 modelMat = modelMatrix_ * rotMatrix;
	// Make sure our state is what we want
	shader_.bind();
	// Set our matrix uniforms!
	QMatrix4x4 id;
	id.setToIdentity();
	shader_.setUniformValue("modelMatrix", modelMat);
	shader_.setUniformValue("viewMatrix", view);
	shader_.setUniformValue("projectionMatrix", projection);

	vao_.bind();
	texture_.bind();
	glDrawElements(GL_TRIANGLES, numTris_, GL_UNSIGNED_INT, 0);
	texture_.release();
	vao_.release();
	shader_.release();
}

void Renderable::setModelMatrix(const QMatrix4x4& transform)
{
	modelMatrix_ = transform;
}

void Renderable::setRotationAxis(const QVector3D& axis)
{
	rotationAxis_ = axis;
}

void Renderable::setRotationSpeed(float speed)
{
	rotationSpeed_ = speed;
}