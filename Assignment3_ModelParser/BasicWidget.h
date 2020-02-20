#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include "Render.h"

// TODO:  This macro should work when both true AND false
#define USE_QT_OPENGL true
// ENDTODO

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QString vertexShaderString() const;
    QString fragmentShaderString() const;
    void createShader();
    QOpenGLVertexArrayObject vao_;

    int numIdx = 6;

protected:
    // Required interaction overrides
    void keyReleaseEvent(QKeyEvent* keyEvent) override;

    // Required overrides form QOpenGLWidget
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    GLuint vboID_;
    GLuint iboID_;
    unsigned int shaderID_;

    unsigned int compileShader(unsigned int type, const QString& shaderSrc);



public:
    BasicWidget(QWidget* parent = nullptr);
    virtual ~BasicWidget();

    // Make sure we have some size that makes sense.
    QSize sizeHint() const { return QSize(800, 600); }
};