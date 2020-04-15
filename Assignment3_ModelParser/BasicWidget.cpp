#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer),
nbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer)
{
	setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
	vbo_.release();
	vbo_.destroy();
	nbo_.release();
	nbo_.destroy();
	ibo_.release();
	ibo_.destroy();
	vao_.release();
	vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
	QString str =
		"#version 330\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec4 color;\n"

		"uniform vec4 wireFrameColor = vec4(1.0, 1.0, 1.0, 1.0);"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"

		"out vec4 vertColor;\n"

		"void main()\n"
		"{\n"
		"  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);\n"
		"  vertColor = wireFrameColor;\n"
		"}\n";
	return str;
}

QString BasicWidget::fragmentShaderString() const
{
	QString str =
		"#version 330\n"
		"in vec4 vertColor;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"  color = vertColor;\n"
		"}\n";
	return str;
}

void BasicWidget::createShader()
{
	QOpenGLShader vert(QOpenGLShader::Vertex);
	vert.compileSourceCode(vertexShaderString());
	QOpenGLShader frag(QOpenGLShader::Fragment);
	frag.compileSourceCode(fragmentShaderString());
	bool ok = shaderProgram_.addShader(&vert);
	if (!ok) {
		qDebug() << shaderProgram_.log();
	}
	ok = shaderProgram_.addShader(&frag);
	if (!ok) {
		qDebug() << shaderProgram_.log();
	}
	ok = shaderProgram_.link();
	if (!ok) {
		qDebug() << shaderProgram_.log();
	}
}

void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent) {
	// Handle key events here.
	if (keyEvent->key() == Qt::Key_1) {
		fillMode = GL_FILL;
		verts.clear();
		indx.clear();
		normals.clear();

		verts = bunny.getVerts();
		indx = bunny.getIndx();
		normals = bunny.getNormals();

		vbo_.bind();
		vbo_.allocate(verts.constData(), verts.size() * sizeof(GL_FLOAT));

		ibo_.bind();
		ibo_.allocate(indx.constData(), indx.size() * sizeof(GL_UNSIGNED_INT));
		
		/*
		nbo_.bind();
		nbo_.allocate(&vertices[0], normals.size() * sizeof(GL_FLOAT));
		*/
		update();

	}
	//switch to the monkey model if 2 is pressed
	//return fillMode to fill
	else if (keyEvent->key() == Qt::Key_2) {
		fillMode = GL_FILL;
		verts.clear();
		indx.clear();
		normals.clear();

		verts = monkey.getVerts();
		indx = monkey.getIndx();
		normals = monkey.getNormals();
		
		vbo_.bind();
		vbo_.allocate(verts.constData(), verts.size() * sizeof(GL_FLOAT));
		
		ibo_.bind();
		ibo_.allocate(indx.constData(), indx.size() * sizeof(GL_UNSIGNED_INT));
		
		/*
		nbo_.bind();
		nbo_.allocate(&vertices[0], normals.size() * sizeof(GL_FLOAT));
		*/
		update();

	}
	//switch the fillMode to wireframe if W is pressed
	else if (keyEvent->key() == Qt::Key_W) {
		if (fillMode == GL_LINE)
		{
			fillMode = GL_FILL;
		}
		else
		{
			fillMode = GL_LINE;
		}
		update();
	}
	else if (keyEvent->key() == Qt::Key_Q) {
		exit(1);
	}
	else {
		qDebug() << "You Pressed an unsupported Key!";
	}
}


void BasicWidget::initializeGL()
{
	makeCurrent();
	initializeOpenGLFunctions();

	model_.setToIdentity();
	view_.setToIdentity();
	projection_.setToIdentity();

	QOpenGLContext* curContext = this->context();
	qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
	qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
	qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
	qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
	qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

	createShader();
	
	//initialize our models
	bunny = Render("../../objects/bunny.obj");
	monkey = Render("../../objects/monkey.obj");
	indx = bunny.getIndx();
	verts = bunny.getVerts();
	normals = bunny.getNormals();

	shaderProgram_.bind();

	//set up the vertex buffer
	vbo_.create();
	vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo_.bind();
	vbo_.allocate(verts.constData(), verts.size() * sizeof(GL_FLOAT));
	
	//set up the normal buffer/
	/*
	nbo_.create();
	nbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	nbo_.bind();
	nbo_.allocate(normals.constData(), normals.size() * sizeof(GL_FLOAT));
	*/

	//set up the index buffer
	ibo_.create();
	ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	ibo_.bind();
	ibo_.allocate(indx.constData(), indx.size() * sizeof(GL_UNSIGNED_INT));

	vao_.create();
	vao_.bind();
	vbo_.bind();
	shaderProgram_.enableAttributeArray(0);
	shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(GL_FLOAT));

	ibo_.bind();
	vao_.release();
	shaderProgram_.release();

	glViewport(0, 0, width(), height());

}

void BasicWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	model_ = QMatrix4x4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	view_.lookAt(QVector3D(1, 0.5f, 3),
		QVector3D(0, 0.5f, 0),
		QVector3D(0, 1, 0)
	);

	projection_.perspective(45.0f, (float)w/h, 0.1f, 100.0f);
	shaderProgram_.bind();
	shaderProgram_.setUniformValue("modelMatrix", model_);
	shaderProgram_.setUniformValue("viewMatrix", view_);
	shaderProgram_.setUniformValue("projectionMatrix", projection_);
	shaderProgram_.release();
}

void BasicWidget::paintGL()
{

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram_.bind();
	vao_.bind();

	glPolygonMode(GL_FRONT_AND_BACK, fillMode);

	glDrawElements(GL_TRIANGLES, indx.size(), GL_UNSIGNED_INT, 0);
	vao_.release();
	shaderProgram_.release();
}