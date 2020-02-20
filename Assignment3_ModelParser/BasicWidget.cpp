#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics

BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent)

{
    setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{

    glDeleteProgram(shaderID_);
    glDeleteBuffers(1, &vboID_);
    glDeleteBuffers(1, &iboID_);
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
    QString str =
        "#version 330\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec4 color;\n"
        "out vec4 vertColor;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vec4(position, 1.0);\n"
        "  vertColor = color;\n"
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
    unsigned int prog = glCreateProgram();
    unsigned int vert = compileShader(GL_VERTEX_SHADER, vertexShaderString());
    unsigned int frag = compileShader(GL_FRAGMENT_SHADER, fragmentShaderString());
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glValidateProgram(prog);

    // The shaders are build and ready to use.  We can now detach the individual shaders and destroy them
    glDetachShader(prog, vert);
    glDetachShader(prog, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);

    // Assign here in case there are failures we need to bail on - This has not yet been implemented, though.
    shaderID_ = prog;
}

unsigned int BasicWidget::compileShader(unsigned int type, const QString& shaderSrc)
{
    unsigned int id = glCreateShader(type);
    // Make sure we can create the shader
    if (id == 0) {
        return 0;
    }
    QByteArray ba = shaderSrc.toLocal8Bit();
    const char* src = ba.data();
    // Set the source
    glShaderSource(id, 1, &src, nullptr);
    // Compile
    glCompileShader(id);
    // Retrieve the result of our compilation
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length]; // Could also use alloca here.
        glGetShaderInfoLog(id, length, &length, errorMessages);
        if (type == GL_VERTEX_SHADER) {
            qDebug() << "ERROR: GL_VERTEX_SHADER compilation failed!\n" << errorMessages << "\n";
        }
        else if (type == GL_FRAGMENT_SHADER) {
            qDebug() << "ERROR: GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages << "\n";
        }
        // Reclaim our memory
        delete[] errorMessages;
        // Delete our broken shader
        glDeleteShader(id);
        return 0;
    }

    return id;
}
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    // Handle key events here.
    if (keyEvent->key() == Qt::Key_Q) { //triangle appears
        qDebug() << "Left Arrow Pressed";
        QApplication::quit();
    }
    else if (keyEvent->key() == Qt::Key_W) { //square appears
    //Wireframe Time    
    }
    else if (keyEvent->key() == Qt::Key_1) { //square appears
    //Bunny Time
    }
    else if (keyEvent->key() == Qt::Key_2) { //square appears
    //Monkey Time 
    }
    else {
        qDebug() << "You Pressed an unsupported Key!";
    }
    // ENDTODO
}
void BasicWidget::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();

    QOpenGLContext* curContext = this->context();
    qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
    qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
    qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
    qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    Render test("../../objects/cube.obj");

    // Set up our shaders.
    createShader();

    // Add vertex and index data to draw two triangles
    // Define our verts
    static const GLfloat verts[12] =
    {
      -0.8f, -0.8f, 0.0f, // Left vertex position
      0.8f, -0.8f, 0.0f,  // right vertex position
      -0.8f,  0.8f, 0.0f,  // Top vertex position
      0.8f, 0.8f, 0.0f
    };
    // Define our vert colors
    static const GLfloat colors[16] =
    {
        1.0f, 0.0f, 0.0f, 1.0f, // red
        0.0f, 1.0f, 0.0f, 1.0f, // green
        0.0f, 0.0f, 1.0f, 1.0f, // blue
        1.0f, 1.0f, 0.0f, 1.0f  // yellow
    };
    // Define our indices
    static const GLuint idx[6] =
    {
        0, 1, 2, 2, 1, 3
    };

    vao_.create();
    vao_.bind();

    glGenBuffers(1, &vboID_);
    glBindBuffer(GL_ARRAY_BUFFER, vboID_);
    glBufferData(GL_ARRAY_BUFFER,test.getVerticies().size() * sizeof(Vec3d), &test.getVerticies()[0] , GL_STATIC_DRAW);

    // Generate our index buffer
    glGenBuffers(1, &iboID_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, test.getNormal().size() * sizeof(Vec3d), &test.getNormal()[0], GL_STATIC_DRAW);

    vao_.release();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glUseProgram(shaderID_);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboID_);
    glVertexAttribPointer(0,        // Attribute 0 matches our layout for vertex positions
        3,        // Size
        GL_FLOAT, // Type
        GL_FALSE, // Not normalized
        0,        // Stride - no interleaving
        (void*)0  // nullptr
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,        // Attribute 0 matches our layout for vertex positions
        4,        // Size
        GL_FLOAT, // Type
        GL_FALSE, // Not normalized
        0,        // Stride - no interleaving
        (void*)0  // nullptr
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_);
    // Render
    // TODO: Change number of indices drawn
    glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, nullptr);

    // Unbind everything
    glDisableVertexAttribArray(0);
    glUseProgram(NULL);

}