#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include "ModelParser.h"

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

private:
	ModelParser bunny;
	ModelParser monkey;
	QVector<GLuint> indices;
	QVector<GLfloat> vertices;
	QVector<GLfloat> normals;

	QOpenGLBuffer vbo_;
	QOpenGLBuffer nbo_;
	QOpenGLBuffer ibo_;
	QOpenGLShaderProgram shaderProgram_;
	QOpenGLVertexArrayObject vao_;

	QString vertexShaderString() const;
	QString fragmentShaderString() const;
	void createShader();

	QMatrix4x4 model_;
	QMatrix4x4 view_;
	QMatrix4x4 projection_;

	GLenum fillMode = GL_FILL;

protected:
  // Required interaction overrides
  void keyReleaseEvent(QKeyEvent* keyEvent) override;

  // Required overrides form QOpenGLWidget
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

public:
  BasicWidget(QWidget* parent=nullptr);
  virtual ~BasicWidget();
  
  // Make sure we have some size that makes sense.
  QSize sizeHint() const {return QSize(800,600);}
};
