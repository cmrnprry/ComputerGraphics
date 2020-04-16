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

    model = Render("../../objects/Bunny/ChocoEasterBunny2.obj");

    QDir directory("C:/Users/Cam/Documents/GitHub/GraphicsForked/ComputerGraphics/Assignment6_SceneGraphOrParticleSystem/ParticleSystem/objects/Bunny");
    QString path = directory.filePath(QString::fromUtf8("ChocoEasterBunny2_colormap.ppm"));

    QVector<QVector3D> pos;
    QVector<QVector3D> norm;
    QVector<QVector2D> texCoord;
    QMatrix4x4 m;
    QVector<unsigned int> idx;

    pos = model.getVerts();
    norm = model.getNormals();
    texCoord = model.getTexs();
    idx = model.getIndx();

    Renderable* ren = new Renderable();
    ren->init(pos, norm, texCoord, idx, path);
    renderables_.push_back(ren);
    
    Emitter* emitter = new Emitter(QVector3D(0, 0, 0), QVector3D(0, 1, 0), ren);
    particleSystem_.addEmitter(emitter);

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

    particleSystem_.drawParticles(msSinceRestart, projection_, view_);
    update();
}
