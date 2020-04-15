#include "BasicWidget.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this)
{
    setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
    for (auto renderable : renderables_) {
        delete renderable;
    }
    renderables_.clear();
}

//////////////////////////////////////////////////////////////////////
// Privates
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    // Handle key events here.
    if (keyEvent->key() == Qt::Key_W) {
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

    qDebug() << QDir::currentPath();

    house = Render("../../../objects/house/house_obj.obj");
    mat = MaterialRender("../../../objects/house/house_obj.mtl");

    QDir directory("C:/Users/Cam/Documents/GitHub/GraphicsForked/ComputerGraphics/Assignment4_TexturedModel/objects/house");
    QString path = directory.filePath(QString::fromUtf8(mat.getDiffuse().c_str()));

    QVector<QVector3D> pos;
    QVector<QVector3D> norm;
    QVector<QVector2D> texCoord;
    QMatrix4x4 m;
    QVector<unsigned int> idx;

    pos = house.getVerts();
    norm = house.getNormals();
    texCoord = house.getTexs();
    idx = house.getIndx();

    Renderable* ren = new Renderable();
    ren->init(pos, norm, texCoord, idx, path);
    renderables_.push_back(ren);

    glViewport(0, 0, width(), height());
    frameTimer_.start();
}

void BasicWidget::resizeGL(int w, int h)
{
    if (!logger_.isLogging()) {
        logger_.initialize();
        // Setup the logger for real-time messaging
        connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=]() {
            const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
            for (auto msg : messages) {
                qDebug() << msg;
            }
            });
        logger_.startLogging();
    }
    glViewport(0, 0, w, h);
    view_.setToIdentity();
    view_.lookAt(QVector3D(2.0f, 2.0f, 2.0f),
        QVector3D(0.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 1.0f, 0.0f));
    projection_.setToIdentity();
    projection_.perspective(70.f, (float)w / (float)h, 0.001, 1000.0);
    glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
    qint64 msSinceRestart = frameTimer_.restart();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, fillMode);

    for (auto renderable : renderables_) {
        renderable->update(msSinceRestart);
        renderable->draw(view_, projection_);
    }
    update();
}
